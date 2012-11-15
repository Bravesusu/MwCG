#pragma once
#include "mwx.h"
#include "MwGLElement.h"
//#include "MwGlScreen.h"
#include "MwCanvas.h"
#include "MwPoint.h"
#include "MwMouse.h"

using namespace std;

namespace mw
{
	class GlContent : public GlElement
	{
		DECLARE_SERIAL(GlContent);
	public:
		GlContent(void);
		~GlContent(void);
		virtual void Serialize(CArchive& ar);

	public:
		const shared_ptr<Canvas>& canvas() const { return canvas_; }
		const shared_ptr<GlScreen>& screen() const { return screen_; }
	private:
		shared_ptr<Canvas> canvas_;
		shared_ptr<GlScreen> screen_;
		shared_ptr<Mouse> mouse_;
	private:
		list<GlElementPtr> elements_;
	public:
		void AddElement(GlElementPtr element);
		void RemoveElement(GlElementPtr element);
	private:
		void DoDraw();
	public:
		bool HitTest();
		Vector2 set_mouse(const CPoint& viewPoint) const;

	};
}
