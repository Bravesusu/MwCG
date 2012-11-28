#pragma once
#include "mwx.h"
#include "MwGLElement.h"
using namespace std;

namespace mw
{
	class Canvas;
	class GlScreen;
	class Mouse;
	class GlContent;
	typedef function<void(const shared_ptr<GlElement>)> GlContentCallback;
	class GlContent : public GlElement//, public enable_shared_from_this<GlContent>
	{
		DECLARE_SERIAL(GlContent);
	public:
		GlContent(void);
		~GlContent(void);
		virtual void Serialize(CArchive& ar);

	public:
		const shared_ptr<Canvas>& canvas() const { return canvas_; }
	private:
		shared_ptr<Canvas> canvas_;
		shared_ptr<Mouse> mouse_;
		shared_ptr<GlScreen> theScreen_;
	private:
		list<GlElementPtr> elements_;
	public:
		void AddElement(GlElementPtr element);
		void RemoveElement(GlElementPtr element);
	private:
		void DoDraw();
	public:
		Vector2 set_mouse(const CPoint& viewPoint) const;

		virtual bool HitTest( const Vector2& worldPos ) const;

		//Return true if hits and set the hit pointer. hit == NULL if false
		bool HitTest( const Vector2& worldPos, shared_ptr<GlElement>& hit ) const;
	private:
		list<shared_ptr<GlElement>> selectedElements_;
		GlContentCallback onSelectEvtHandler_;
		GlContentCallback onDeselectEvtHandler_;
	public:
		void set_on_select(const GlContentCallback handler) { onSelectEvtHandler_ = handler; }
		void set_on_deselect(const GlContentCallback handler) { onDeselectEvtHandler_ = handler; }
	protected:
		bool IsAlreadySelected( const shared_ptr<GlElement>& element ) const;
		void InvokeSelectHandler( const shared_ptr<GlElement>& element );
		void InvokeDeselectHandler( const shared_ptr<GlElement>& element );
	public:
		const list<shared_ptr<GlElement>>& selected_elements() const { return selectedElements_; }
		void SingleSelect(const shared_ptr<GlElement>& element);
		void Select(const shared_ptr<GlElement>& element);
		void Deselect(const shared_ptr<GlElement>& element);
		void DeselectAll();

		virtual Rect bound() const;

	};
}
