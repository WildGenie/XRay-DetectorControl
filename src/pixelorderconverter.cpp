#include "pixelorderconverter.h"


PixelOrderConverter::PixelOrderConverter(int bNum, int pNum)
{
    boardNum = bNum;
    pixelNum = pNum;
}

DualToSingleConverter::DualToSingleConverter(int boardNum, int pixelNum): PixelOrderConverter(boardNum,pixelNum)
{
    int size = boardNum*pixelNum;

}

void DualToSingleConverter::process(IFrameObject* src)
{
    long width = 0;
	src->get_Width(&width);
    long height = 0;
	src->get_Height(&height);
        
    if (width != boardNum*pixelNum) {
		//printf("boardNum*pixelNum != width\n cannot do the process");
		return;
	}
	int i=0;

#pragma omp parallel for private(i) shared( width, height) 
    for(i=0; i< height; i++) {
		long pline = 0;
		src->get_ImageLineAddress(i, &pline);
        convertLine((WORD*)pline, width);
    }
#pragma omp barrier
}


void DualToSingleConverter::copyBlock(WORD* dest, WORD* src, int srcIndex, int destIndex)
{
    memcpy (dest+destIndex*pixelNum, src+srcIndex*pixelNum, pixelNum*2);
}

void DualToSingleConverter::convertLine(WORD* src, int width)
{
	WORD* buffer = new WORD[width];
    int blockNum = boardNum ;
    //Low Energy Area. First half part
    for(int i=0; i < blockNum/2 ; i++) {
        copyBlock(buffer, src, i, i*2);
    }
    //High Energy Area. Sencond half part
    for(int i = blockNum/2; i < blockNum ; i++) {
        copyBlock(buffer, src, i, i*2-blockNum+1);
    }
    memcpy(src, buffer, width*2);
	delete[] buffer;
}
