#pragma once
#include "mwx.h"
#include "MwColor.h"
#include "MwGlScreen.h"

using namespace std;

namespace mw 
{
	class Rect;
	class GlElement :
		public CObject
	{
		DECLARE_SERIAL(GlElement); 
	private:
		Color color_;
	public:
		GlElement(void);
		~GlElement(void);
		Color color() const { return color_; }
		void set_color(float r, float g, float b, float a = 1.0) { color_.set(r, g, b, a); }
		void set_color(COLORREF color) { color_.set(color); }
		void set_color(const Color& color) { color_.set(color); }

		//Serialization
	public:
		virtual void Serialize(CArchive& ar);

		//Rendering
	private:
		virtual void DoDraw() {};
	public:
		void Draw();
		virtual bool HitTest() { return false; };

		//TODO: components
	public:

		//Hierarchy
	private:
		shared_ptr<GlScreen> screen_;
	public:
		const shared_ptr<GlScreen>& screen() const { return screen_; }
		void set_screen(const shared_ptr<GlScreen>& screen) { screen_ = screen; }

	public:
		virtual Rect bound() const;
	};

	typedef shared_ptr<GlElement> GlElementPtr;
}
