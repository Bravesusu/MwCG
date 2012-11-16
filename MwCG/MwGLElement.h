#pragma once
#include "mwx.h"
#include "IDrawable.h"
#include "MwColor.h"
#include "MwGlScreen.h"

using namespace std;

namespace mw 
{
	class Rect;
	class Decorator;
	class GlElement :
		public CObject, 
		public IDrawable
	{
		DECLARE_SERIAL(GlElement); 
	private:
		Color color_;
	private:
		list<shared_ptr<Decorator>> decorators_;
	public:
		void RemoveDecorator(shared_ptr<Decorator> decorator);
		void AddDecorator(shared_ptr<Decorator> decorator);
		shared_ptr<GlElement> operator+(shared_ptr<Decorator> decorator);
		shared_ptr<GlElement> operator+(Decorator* decorator);
		shared_ptr<GlElement> operator-(shared_ptr<Decorator> decorator);
		void ClearAllDecorators();
		//NOTE: a raw pointer means possibility of memory leak, should not be encouraged.
		//shared_ptr<GlElement> operator-(const Decorator* decorator);
		//NOTE: doesn't make much sense. 
		//An instance will be allocated on stack space, its address is not unique for identification
		//However they might be useful in a very long method body
		//And also an overload on the == operator of Decorator class might be utilized.
		//TBD.
		GlElement& operator+(Decorator& decorator);
		GlElement& operator-(Decorator& decorator);

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

	private:
		bool hidden_;

	public:
		bool hidden() const { return hidden_; }
		void set_hidden(bool hidden) { hidden_ = hidden; }
	};

	typedef shared_ptr<GlElement> GlElementPtr;
}
