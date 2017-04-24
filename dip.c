#include "bmp.h"
#include "cnv.h"
#define numInput 2
#define numFilter 2


char *inputNames[numInput] = {
	"Images/ObsceneBug.bmp",
	"Images/DeeHuiGray.bmp"
};

char *outputNames[numFilter][numInput] = {
	"Output/blurObsceneBug.bmp",
	"Output/blurDeeHuiGray.bmp",	
	"Output/LoGObsceneBug.bmp",
	"Output/LoGDeeHuiGray.bmp"
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
