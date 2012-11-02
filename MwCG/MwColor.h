#pragma once
#include "mwx.h"
#define MwRGB(r, g, b) new MwColor(r, g, b)
#define MwRGBA(r, g, b, a) new MwColor(r, g, b, a)
#define MW_WHITE			1, 1, 1
#define MW_BLACK			0, 0, 0
#define MW_RED				1, 0, 0
#define MW_BLUE				0, 1, 0
#define MW_GREEN			0, 0, 1

class MwColor :
	public MwGLObject
{
	DECLARE_SERIAL(MwColor);
protected:
	float r_;
	float g_;
	float b_;
	float a_;
public:
	void set(float r, float g, float b, float a = 1.0);
	void set(COLORREF color);
	void set(const MwColor& color);
	COLORREF get_color_ref();
	float r() const { return r_; }
	float g() const { return g_; }
	float b() const { return b_; }
	float a() const { return a_; }
public:
	MwColor& operator =(const MwColor & rhs);
public:
	MwColor(void);
	MwColor(const MwColor & color) { set(color); }
	MwColor(float fr, float fg, float fb) 
		: r_(fr), g_(fg), b_(fb), a_(1.0) {};
	MwColor(float fr, float fg, float fb, float fa)  
		: r_(fr), g_(fg), b_(fb), a_(fa) {};
	~MwColor(void);
	inline void GL();
	void Clear() { glClearColor(r_, g_, b_, a_); }
	void Serialize(CArchive& ar);
};

