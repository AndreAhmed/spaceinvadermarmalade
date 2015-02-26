#pragma once 
 
class cRect
{
public:
	cRect();
	~cRect();
	void SetRect(int x, int y, int width, int height);
	bool IsOverlap(const cRect &r1);
public:
	int x; 
	int y;
	int w;
	int h;
};