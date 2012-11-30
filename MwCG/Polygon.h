#pragma once
#include "mwglelement.h"
#include "LineFactory.h"
namespace mw
{
	class Line;
	class BresLine;

	
	class MwPolygon :
		public GlElement
	{
		DECLARE_SERIAL(MwPolygon);
	private:
		list<shared_ptr<Vector2>> vertex_;
		shared_ptr<Line> line_;
		shared_ptr<LineFactory> line_factory_;
	public:
		void set_line(LineFactory* factory);
	public:
		int count() const { return vertex_.size(); }
		void NewVertex(const Vector2& localPos);
		void UpdateLastVertex(const Vector2& localPos);
		void SetVertex(size_t index, const Vector2& localPos);
		Vector2 vertex(int index) const;
	public:
		MwPolygon(void);
		MwPolygon(LineFactory* factory);
		MwPolygon(shared_ptr<LineFactory> factory);
		virtual ~MwPolygon(void);

		virtual void Serialize( CArchive& ar );

		virtual void DoDraw();

		//virtual bool HitTest();

		Rect bound() const;

		virtual void Draw();
	public:
		int anchor_count() const;

		void set_anchor( int index, const Vector2& localPos );

		Vector2 anchor( int index ) const;

		virtual bool HitTest( const Vector2& worldPos ) const;

	};
	
}
