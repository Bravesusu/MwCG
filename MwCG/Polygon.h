#pragma once
#include "mwglelement.h"

namespace mw
{
	class Polygon :
		public GlElement
	{
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
