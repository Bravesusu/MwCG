#pragma once

using namespace std;

namespace mw
{
	class RectBase
	{
	private:
		float left_, right_, top_, bottom_;
	public:
		float left() const { return left_; }
		float right() const { return right_; }
		float top() const { return top_; }
		float bottom() const { return bottom_; }
		void set_left(float left) { left_ = left; }
		void set_right(float right) { right_ = right; }
		void set_top(float top) { top_ = top; }
		void set_bottom(float bottom) { bottom_ = bottom; }
		void set(float left, float right, float top, float bottom);
		void set(const RectBase& rect);
	protected:
		void DoGL() const;
		void DoSerialize( CArchive& ar );
		template<class TRect>
		TRect get() const
		{
			static_assert(is_base_of<RectBase, TRect>::value, "TRect must be derived from RectBase");
			TRect rect;
			rect.set(left_, right_, top_, bottom_);
			return rect;
		};
	public:
		RectBase(float left, float right, float top, float bottom);
		RectBase(const Vector2& point1, const Vector2& point2);
		RectBase(const RectBase& rect);
		RectBase(void);
		virtual ~RectBase(void);
	};
}
