#pragma once
#include "mwx.h"

namespace mw
{
	#define MwRGB(r, g, b) new Color(r, g, b)
	#define MwRGBA(r, g, b, a) new Color(r, g, b, a)
	#define MW_WHITE			1, 1, 1
	#define MW_BLACK			0, 0, 0
	#define MW_RED				1, 0, 0
	#define MW_BLUE				0, 1, 0
	#define MW_GREEN			0, 0, 1
	
	class Color :
		public GlObject
	{
		DECLARE_SERIAL(Color);
	private:
		float r_;
		float g_;
		float b_;
		float a_;
	public:
		void set(float r, float g, float b, float a = 1.0);
		void set(COLORREF color);
		void set(const Color& color);
		COLORREF get_color_ref();
		float r() const { return r_; }
		float g() const { return g_; }
		float b() const { return b_; }
		float a() const { return a_; }
	public:
		Color& operator =(const Color & rhs);
	public:
		Color(void);
		Color(COLORREF colorRef);
		Color(const Color & color) { set(color); }
		Color(float fr, float fg, float fb) 
			: r_(fr), g_(fg), b_(fb), a_(1.0) {};
		Color(float fr, float fg, float fb, float fa)  
			: r_(fr), g_(fg), b_(fb), a_(fa) {};
		~Color(void);
		void GL();
		void ChangeColor() const { ::glColor4f(r_, g_, b_, a_); }
		void Clear() const { ::glClearColor(r_, g_, b_, a_); }
		void Serialize(CArchive& ar);
	};
	
	void glColor(const Color& color);
	void glClearColor(const Color& color);
}
