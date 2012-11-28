#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

namespace mw
{
	class Line :
		public GlElement
	{
		DECLARE_SERIAL(Line);
	private:
		Vector2 point_from_, point_to_;
	public:
		Line(void);
		Line(float x1, float y1, float x2, float y2) ;
		Line(const Vector2& from, const Vector2& to) : point_from_(from), point_to_(to) {} ;
		~Line(void);
		//Serialization
		Vector2 point_from() const { return point_from_; }
		Vector2 point_to() const { return point_to_; }
		void set(float x1, float y1, float x2, float y2) { point_from_.set(x1, y1); point_to_.set(x2, y2); }
		void set(const Vector2& from, const Vector2& to) { point_from_ = from; point_to_ = to; }
		void set_from(float x, float y) { point_from_.set(x, y);}
		void set_from(const Vector2& from) { point_from_ = from; }
		void set_to(float x, float y) { point_to_.set(x, y);}
		void set_to(const Vector2& to) { point_to_ = to; }
	public:
		virtual void Serialize(CArchive& ar);
		virtual Rect bound() const;
	private:
		virtual void DoDraw();
	public:
		virtual bool HitTest( const Vector2& worldPos ) const;

	public:
		int anchor_count() const;

		void set_anchor( int index, const Vector2& localPos );

		Vector2 anchor( int index ) const;
	};
	
}
