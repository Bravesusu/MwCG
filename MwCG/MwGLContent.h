#pragma once
#include "mwx.h"
#include "MwGLElement.h"
#include "MwCanvas.h"
#include "MwPoint.h"

using namespace std;

namespace mw
{
	class GlContent : public CObject
	{
		DECLARE_SERIAL(GlContent);
	public:
		GlContent(void);
		~GlContent(void);
		virtual void Serialize(CArchive& ar);
	
	public:
		Canvas* GetCanvas() const {return m_pCanvas;}
		Point Mouse;
	protected:
		Canvas* m_pCanvas;
	public:
		vector<MwElementSafePtr> Elements;
		//vector<MwGLElement> Elements;
		//vector<MwGLElement*> Elements;
	public:
	};
}
