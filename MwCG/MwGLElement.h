#pragma once
#include "mwx.h"
#include "Stroke.h"
#include "IDrawable.h"
#include "MwColor.h"
#include "MwTransform.h"
#include "IAnchorable.h"

using namespace std;

namespace mw 
{
	class Rect;
	class Decorator;
	class GlScreen;
	class GlElement :
		public GlObject, 
		public IDrawable,
		public IAnchorable
	{
		DECLARE_SERIAL(GlElement); 
	private:
		Color color_;
		int size_;
		Stroke stroke_;
		Transform transform_;
	public:
		int size() const { return size_; }
		void set_size(int size) { size_ = size; }
		Stroke stroke() const { return stroke_; }
		void set_stroke(Stroke stroke) { stroke_ = stroke; }
	public:
		Transform& transform() { return transform_; }
		const Transform& transform() const { return transform_; }
		void set_position(const Vector2& pos) { transform_.position().set(pos); }
		void set_position(float x, float y) { transform_.position().set(x, y); }
	private:
		list<weak_ptr<Decorator>> decorators_;
	public:
		void RemoveDecorator(shared_ptr<Decorator> decorator);
		void AddDecorator(shared_ptr<Decorator> decorator);
		//shared_ptr<GlElement> operator+(shared_ptr<Decorator> decorator);
		//shared_ptr<GlElement> operator+(Decorator* decorator);
		//shared_ptr<GlElement> operator-(shared_ptr<Decorator> decorator);
		void ClearAllDecorators();
		//NOTE: a raw pointer means possibility of memory leak, should not be encouraged.
		//shared_ptr<GlElement> operator-(const Decorator* decorator);
		//NOTE: doesn't make much sense. 
		//An instance will be allocated on stack space, its address is not unique for identification
		//However they might be useful in a very long method body
		//And also an overload on the == operator of Decorator class might be utilized.
		//TBD.
		//GlElement& operator+(Decorator& decorator);
		//GlElement& operator-(Decorator& decorator);

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
		virtual bool HitTest(const Vector2& worldPos) const { return false; }
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

	public:
		//Default implementation of IAnchorable

		//Default to 1. The transform's position.
		virtual int anchor_count() const;

		//0 == transform's position
		virtual void set_anchor( int index, const Vector2& localPos );

		//0 == transform's position
		virtual Vector2 anchor( int index ) const;

	};

	typedef shared_ptr<GlElement> GlElementPtr;
}
