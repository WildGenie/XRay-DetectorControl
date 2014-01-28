#ifndef PIXELORDERCONVERTER_H
#define PIXELORDERCONVERTER_H
#include <assert.h>
#include "../FrameObject.h"
#include <omp.h>
class PixelOrderConverter
{
public:
    PixelOrderConverter(int bNum, int pNum);

    virtual ~PixelOrderConverter() {}
    virtual void process(IFrameObject* src)=0;
protected:
    int boardNum;
    int pixelNum;
};

class DualToSingleConverter: public PixelOrderConverter
{
public:
    DualToSingleConverter(int boardNum, int pixelNum);
    ~DualToSingleConverter() { }
    virtual void process(IFrameObject* src);
 private:

    void copyBlock(WORD* dest, WORD* src, int srcIndex, int destIndex);
    void convertLine(WORD* src, int width);
};

#endif // PIXELORDERCONVERTER_H
