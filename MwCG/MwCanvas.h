#pragma once
#include "mwglelement.h"
#include "MwColor.h"

namespace mw
{
	class Canvas :
		public GlElement
	{
		DECLARE_SERIAL(Canvas);
	//Serialization
	public:
		virtual void Serialize(CArchive& ar);
	
	public:
		void Draw();
	public:
		Canvas(void);
		~Canvas(void);
	};
}

