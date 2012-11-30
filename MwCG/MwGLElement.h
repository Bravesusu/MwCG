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

	//Base class of all graphic element
	class GlElement :
		public GlObject,		//Serialization
		public IDrawable,		//Draw
		public IAnchorable		//Anchor manipulation
	{
		DECLARE_SERIAL(GlElement); 

		//////////////////////////////////////////////////////////////////////////
		// Color 
		// * Color context is enforced before actually drawing each element  
	private:
		Color color_;
	public:
		Color color() const { return color_; }
		void set_color(float r, float g, float b, float a = 1.0) { color_.set(r, g, b, a); }
		void set_color(COLORREF color) { color_.set(color); }
		void set_color(const Color& color) { color_.set(color); }
		//////////////////////////////////////////////////////////////////////////
		// Size
		// * The size property of the element
		// * The meaning and usage is decided in each concrete element implementation
		// * e.g. Point -> Point's size; Line -> Line Width
	private:
		int size_;
	public:
		//Gets size
		int size() const { return size_; }
		//Gets size in float
		float size_f() const { return (float)size_; }
		//Sets size
		void set_size(int size) { size_ = size; }
		//////////////////////////////////////////////////////////////////////////
		// Stroke
		// * The type of line
		// * Implementation should be provided by concrete elements
		// * See Stroke.h
	private:
		Stroke stroke_;
	public:
		//Gets the stroke
		Stroke stroke() const { return stroke_; }
		//Sets the stroke
		void set_stroke(Stroke stroke) { stroke_ = stroke; }
		//////////////////////////////////////////////////////////////////////////
		// Transform
		// * Define and manage the transformation matrix of the element
		// * Position
		// * TODO: Rotation
		// * TODO: Scale
	private:
		Transform transform_;
	public:
		//Gets the reference to the transform
		Transform& transform() { return transform_; }
		//Gets the reference to the transform (read-only)
		const Transform& transform() const { return transform_; }
		//Short cut for transform::set_position
		void set_position(const Vector2& pos) { transform_.position().set(pos); }
		//Short cut for transform::set_position
		void set_position(float x, float y) { transform_.position().set(x, y); }
		//////////////////////////////////////////////////////////////////////////
		// Decorator Pattern
		// * Note for decorator implementors:
		// * Must provide +,-,+=,-= operator 
		// * See decorator.h for more information
	private:
		list<weak_ptr<Decorator>> decorators_;
	public:
		//Removes a decorator (no exception thrown when not exists)
		void RemoveDecorator(shared_ptr<Decorator> decorator);
		//Adds a decorator (will not check for replication)
		void AddDecorator(shared_ptr<Decorator> decorator);
		//Clears all attached decorators
		void ClearAllDecorators();
		//////////////////////////////////////////////////////////////////////////

	public:
		GlElement(void);
		virtual ~GlElement(void);

		//Serialization
	public:
		virtual void Serialize(CArchive& ar);

		//////////////////////////////////////////////////////////////////////////
		// IDrawable Interface
	private:
		// Concrete elements should implement DoDraw() for actual drawing
		virtual void DoDraw() {};
	public:
		// Instead of the Draw().
		// Necessary code for maintaining drawing context is wrapped around 
		// the call to DoDraw()
		void Draw();
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// HitTest
		// TODO: requires concrete elements to implement a method to calculate
		// distance from a point to it.
		// And then do the hit test with consideration of error tolerance taken. 
		virtual bool HitTest(const Vector2& worldPos) const { return false; }
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// Holds the pointer to the GlScreen instance
		// TODO: use singleton pattern instead
	private:
		shared_ptr<GlScreen> screen_;
	public:
		const shared_ptr<GlScreen>& screen() const { return screen_; }
		void set_screen(const shared_ptr<GlScreen>& screen) { screen_ = screen; }
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
	public:
		//Gets the rectangular bound of each elements.
		virtual Rect bound() const;
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// Visibility control
	private:
		bool hidden_;
	public:
		//Gets a bool indicating whether the element is hidden
		bool hidden() const { return hidden_; }
		//Sets a bool indicating whether to hide the element
		void set_hidden(bool hidden) { hidden_ = hidden; }
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// IAnchorable
		// * Provide a default implementation which only manipulates the transform
		// * Concrete elements should implement one of its own
	public:
		//Only 1; The transform's position.
		virtual int anchor_count() const;

		//0 == transform's position
		virtual void set_anchor( int index, const Vector2& localPos );

		//0 == transform's position
		virtual Vector2 anchor( int index ) const;

		void ResetTransformToAnchor(int anchor_index);
		//////////////////////////////////////////////////////////////////////////
	};

	typedef shared_ptr<GlElement> GlElementPtr;
}
