#include "bmp.h"
#include "cnv.h"
#define kernSize 5
#define numInput 3
#define numFilter 2

int filters[numFilter][kernSize][kernSize] = {
   8,    34,    56,    34,    8,
  34,   153,  253,  153,   34,
  56,  253,  417,  253,  56,
  34,   153,  253,  153,   34,
   8,    34,    56,    34,    8,

	 0,     1,     2,   1,    0,
	 1,     5,     0,   5,    1,
	 2,     0,   -88,   0,    2,
	 1,     5,     0,   5,    1,
	 0,     1,     2,   1,    0/*
448 ,   468 ,   564 ,   468 ,   448,
        468  ,  3167 ,   7146 ,   3167  ,  468,
            564  ,  7146  , -49048  ,  7146 ,   564,
                468  ,  3167  ,  7146  ,  3167 ,   468,
                    448  ,  468  ,  564  ,  468  ,  448,
*/




};

int weights[numFilter] = {2433, 1};

char *inputNames[numInput] = {
	"Images/lake.bmp",
	"Images/maple.bmp",
	"Images/tree.bmp"
};

char *outputNames[numFilter][numInput] = {
	"Output/blurLake.bmp",
	"Output/blurMaple.bmp",
	"Output/blurTree.bmp",
	"Output/sharpLake.bmp",
	"Output/sharpMaple.bmp",
	"Output/sharpTree.bmp"
};

BMP bmpFiles[numInput];
BYTE *data[numInput];
BYTE *results[numFilter][numInput];

int imgHeight, imgWidth, imgSize;

void setImageInfo()
{
	imgHeight = bmpFiles[0].height;
	imgWidth = bmpFiles[0].width;
	imgSize = imgHeight * imgWidth * 3;
}

void loadImages()
{
	int i;
	
	for(i = 0; i < numInput; i++){
		bmpLoad(&bmpFiles[i], inputNames[i]);
	}
}

void saveImages()
{
	BMP bmpTemp;
	int i, j;

	bmpTemp = bmpFiles[0];

	for(i = 0; i < numFilter; i++){
		for(j = 0; j < numInput; j++){
			bmpTemp.data = results[i][j];	
			bmpSave(&bmpTemp, outputNames[i][j]);
		}
	}
}

void initData()
{
	int i;

	for(i = 0; i < numInput; i++){
		data[i] = malloc(imgSize * sizeof(BYTE));
		memcpy(data[i], bmpFiles[i].data, imgSize * sizeof(BYTE));
	}
}

void initResults()
{
	int i, j;

	for(i = 0; i < numFilter; i++)
		for(j = 0; j < numInput; j++)
			results[i][j] = malloc(imgSize * sizeof(BYTE));
}

void freeMem()
{
	int i, j;

	for(i = 0; i < numInput; i++)
		free(data[i]);

	for(i = 0; i < numFilter; i++)
		for(j = 0; j < numInput; j++)
			free(results[i][j]);
}

void checkPixelValue(int *arr, int weight)
{
	int i;

	for(i = 0; i < 3; i++){
		if(weight != 0)
			arr[i] = arr[i] / weight;
		if(arr[i] < 0)
			arr[i] = 0;
		else if(arr[i] > 255)
			arr[i] = 255;
	}
}

int getIdx(int y, int x)
{
	return y*imgWidth + x;
}

void setPixel(BYTE *data, int idx, int *rgb)
{
	Pixel *pixelPtr;

	pixelPtr = (Pixel *) &data[idx*sizeof(Pixel)];
	pixelPtr->R = rgb[0]; 
	pixelPtr->G = rgb[1]; 
	pixelPtr->B = rgb[2];
}

/*void cross2DConv()
{
	int i, j, k, l;
	int filIdx, inIdx;
	int weight, kernLen;
	int rgb[3], idx[3];
	Pixel *pixelPtr;

	kernLen = kernSize/2;

	for(i = 0; i < imgWidth; i++){
		for(j = 0; j <= i && j < imgHeight; j++){
			for(inIdx = 0; inIdx < numInput; inIdx++){
				for(filIdx = 0; filIdx < numFilter; filIdx++){
					rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;
					weight = weights[filIdx];
					for(k = 0; k < kernSize; k++){
						for(l = 0; l < kernSize; l++){
							idx[0] = getIdx(j, i - j);
							idx[1] = idx[0]%imgWidth - kernLen + l;
							idx[2] = idx[0]/imgWidth - kernLen + k;
							if((idx[1] >= 0) && (idx[2] >= 0) && 
								 (idx[1] < imgWidth) && (idx[2] < imgHeight)){
								pixelPtr = (Pixel *) &data[inIdx][getIdx(idx[2], idx[1])
																									* sizeof(Pixel)];
								rgb[0] += filters[filIdx][k][l] * (pixelPtr->R - 0);
								rgb[1] += filters[filIdx][k][l] * (pixelPtr->G - 0);
								rgb[2] += filters[filIdx][k][l] * (pixelPtr->B - 0);
							}                               
							else                            
								weight -= filters[filIdx][k][l];
						}
					}		
					checkPixelValue(rgb, weight);
					setPixel(results[filIdx][inIdx], idx[0], rgb);
				}
			}
		}
	}
	for(i = 0; i < imgHeight+1; i++){
		for(j = 0; j <= i; j++){
			for(inIdx = 0; inIdx < numInput; inIdx++){
				for(filIdx = 0; filIdx < numFilter; filIdx++){
					rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;
					weight = weights[filIdx];
					for(k = 0; k < kernSize; k++){
						for(l = 0; l < kernSize; l++){
							idx[0] = getIdx(imgHeight - j, imgWidth - i + j);
							idx[1] = idx[0]%imgWidth - kernLen + l;
							idx[2] = idx[0]/imgWidth - kernLen + k;
							if((idx[1] >= 0) && (idx[2] >=0) && 
								 (idx[1] < imgWidth) && (idx[2] < imgHeight)){
								pixelPtr = (Pixel *) &data[inIdx][getIdx(idx[2], idx[1])
																									* sizeof(Pixel)];
								rgb[0] += filters[filIdx][l][k] * (pixelPtr->R - 0);
								rgb[1] += filters[filIdx][l][k] * (pixelPtr->G - 0);
								rgb[2] += filters[filIdx][l][k] * (pixelPtr->B - 0);
							}                               
							else                            
								weight -= filters[filIdx][l][k];
						}
					}		
					checkPixelValue(rgb, weight);
					setPixel(results[filIdx][inIdx], idx[0], rgb);
				}
			}
		}
	}
}
*/
int main() {
	loadImages();
	setImageInfo();
	initData();
	initResults();
	cross2DConv();
	saveImages();
	freeMem();

  return 0;
}
