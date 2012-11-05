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
		const shared_ptr<Canvas>& canvas() const {return canvas_;}
		Point Mouse;
	protected:
		shared_ptr<Canvas> canvas_;
	public:
		vector<GlElementPtr> Elements;
	public:
	};
}
