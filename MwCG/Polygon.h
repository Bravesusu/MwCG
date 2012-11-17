#pragma once
#include "mwglelement.h"

namespace mw
{
	class Polygon :
		public GlElement
	{
	private:
		list<Vector2> vertex_;
	public:
		int count() const { return vertex_.size(); }
	public:
		Polygon(void);
		~Polygon(void);

		virtual void Serialize( CArchive& ar );

		virtual void DoDraw();

		virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Draw();

	};
	
}
