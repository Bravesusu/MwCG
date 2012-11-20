#pragma once
#include "mwglelement.h"

namespace mw
{
	class Line;
	class Polygon :
		public GlElement
	{
		//DECLARE_SERIAL(Polygon);
	private:
		list<shared_ptr<Vector2>> vertex_;
		shared_ptr<Line> line_;
	public:
		int count() const { return vertex_.size(); }
	public:
		Polygon(void);
		~Polygon(void);

		virtual void Serialize( CArchive& ar );

		virtual void DoDraw();

		//virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Draw();

	};
	
}
