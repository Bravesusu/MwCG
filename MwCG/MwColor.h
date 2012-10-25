#pragma once
#include "mwglobject.h"

#define MwRGB(r, g, b) new MwColor(r, g, b)
#define MwRGBA(r, g, b, a) new MwColor(r, g, b, a)

class MwColor :
	public MwGLObject
{
	DECLARE_SERIAL(MwColor);
public:
	float r;
	float g;
	float b;
	float a;
public:
	void SetColorRef(COLORREF color);
	COLORREF GetColorRef();
public:
	MwColor(void);
	MwColor(float fr, float fg, float fb) 
		: r(fr), g(fg), b(fb), a(1.0) {};
	MwColor(float fr, float fg, float fb, float fa)  
		: r(fr), g(fg), b(fb), a(fa) {};
	~MwColor(void);
	void GL();
	void GL(bool clear);
	void operator ()(bool clear) { GL(true); };
	void Serialize(CArchive& ar);
};

