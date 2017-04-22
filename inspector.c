#include "bmp.h"

#define numOutput 4
#define diffLimit 4000

char *outputNames[numOutput] = {
	"Output/blurObsceneBug.bmp",
	"Output/blurDeeHuiGray.bmp",	
	"Output/LoGObsceneBug.bmp",
	"Output/LoGDeeHuiGray.bmp"
};

char *goldenOutputNames[numOutput] = {
	"GoldenOutput/blurObsceneBug.bmp",
	"GoldenOutput/blurDeeHuiGray.bmp",	
	"GoldenOutput/LoGObsceneBug.bmp",
	"GoldenOutput/LoGDeeHuiGray.bmp"
};

int check(BMP *bmptr1, BMP *bmptr2)
{
	BYTE byte1, byte2;
	int i, size;
	int count = 0;

	size = bmptr1->height*bmptr2->width*3;

	for(i = 0; i < size; i++){
		byte1 = bmptr1->data[i*sizeof(BYTE)];
		byte2 = bmptr2->data[i*sizeof(BYTE)];
		if(byte1 != byte2)
			count++;
	}

	return count;
}

int main()
{
	BMP bmp1, bmp2;
	int i, diffCount;
	int pass = 1;

	for(i = 0; i < numOutput; i++){
		diffCount = 0;
		bmpLoad(&bmp1, outputNames[i]);
		bmpLoad(&bmp2, goldenOutputNames[i]);
		diffCount = check(&bmp1, &bmp2);
		if(diffCount > diffLimit){
			pass = 0;
			break;
		}	
	}

	if(pass == 0)
		printf("Sorry, your results are wrong!\n");
	else
		printf("Congratulations! You have passed the checking.\n");

	return 0;
}
