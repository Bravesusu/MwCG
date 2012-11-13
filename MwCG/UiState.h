#pragma once

namespace mw
{
	template<class TView, class TDoc>
	class UiState
	{
	private:
		TView* pView_;
		TDoc* pDoc_;
	public:
		const TView* view() const { return pView_; }
		const TDoc* doc() const { return pDoc_; }
	public:
		UiState(void)
		{
			Initilize(NULL, NULL);
		}

		~UiState(void) {};
	private:
	public:
		void Initilize(TView* pView, TDoc* pDoc)
		{
			static_assert(std::is_base_of<CView, TView>::value, "TView must be CView based.");
			static_assert(std::is_base_of<CDocument, TDoc>::value, "TView must be CView based.");
			pView_ = pView;
			pDoc_ = pDoc;
		}
	public:
		virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
	};
}

