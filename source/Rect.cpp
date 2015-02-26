#include "Rect.h"

bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

void cRect::SetRect(int x, int y, int width, int height)
{
	//srcX = x;
	//SrcY = y;
	//Width = width;
	//Height = height;
}

cRect::cRect()
{

}


bool cRect::IsOverlap(const cRect &r1)
{
	/*bool xOverlap = valueInRange(r1.srcX, srcX, srcX + Width) ||
		valueInRange(srcX, r1.srcX, r1.srcX + r1.Width);

	bool yOverlap = valueInRange(r1.SrcY, SrcY, SrcY + Height) ||
		valueInRange(SrcY, r1.SrcY, r1.SrcY + r1.Height);*/
	return true; // xOverlap && yOverlap;
}

cRect::~cRect()
{

}
 