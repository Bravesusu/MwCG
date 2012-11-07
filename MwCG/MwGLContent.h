#pragma once
#include "mwx.h"
#include "MwGLElement.h"
#include "MwGlScreen.h"
#include "MwCanvas.h"
#include "MwPoint.h"

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
		shared_ptr<Point> mouse_;
	public:
		vector<GlElementPtr> Elements;
	public:
		void Draw();
		bool HitTest();
		Vector2 set_mouse(const CPoint& viewPoint) const;

	};
}
