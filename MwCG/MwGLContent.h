#pragma once
#include "mwx.h"
#include "MwGLElement.h"
#include "MwCanvas.h"
#include "MwPoint.h"

using namespace std;

namespace mw
{
	class MwGLContent : public CObject
	{
		DECLARE_SERIAL(MwGLContent);
	public:
		MwGLContent(void);
		~MwGLContent(void);
		virtual void Serialize(CArchive& ar);
	
	public:
		MwCanvas* GetCanvas() const {return m_pCanvas;}
		MwPoint Mouse;
	protected:
		MwCanvas* m_pCanvas;
	public:
		vector<MwElementSafePtr> Elements;
		//vector<MwGLElement> Elements;
		//vector<MwGLElement*> Elements;
	public:
	};
}
