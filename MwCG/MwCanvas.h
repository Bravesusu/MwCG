#pragma once
#include "mwglelement.h"
#include "MwColor.h"

namespace mw
{
	class MwCanvas :
		public MwGLElement
	{
		DECLARE_SERIAL(MwCanvas);
	//Serialization
	public:
		virtual void Serialize(CArchive& ar);
	
	public:
		void Draw();
	public:
		MwCanvas(void);
		~MwCanvas(void);
	};
}

