#pragma once
namespace mw
{
	template <class TBase>
	class RectType : TBase
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
		void set(float left, float right, float top, float bottom)
		{
			left_ = left;
			right_ = right;
			top_ = top;
			bottom_ = bottom;
		};

		void set(const RectType& rect)
		{
			set(rect.left(), rect.right(), rect.top(), rect.bottom());
		};

	protected:
		void DoGL() const
		{
			glRectf(left_, top_, right_, bottom_);
		};

		void DoSerialize( CArchive& ar )
		{
			if (ar.IsStoring())
			{
				ar<<left_<<right_<<top_<<bottom_;
			}
			else
			{
				ar>>left_>>right_>>top_>>bottom_;
			}
		};

		template<class TRect>
		TRect get() const
		{
			static_assert(is_base_of<RectType, TRect>::value, "TRect must be derived from RectType");
			TRect rect;
			rect.set(left_, right_, top_, bottom_);
			return rect;
		};
	public:
		RectType(float left, float right, float top, float bottom) :
			left_(left),
			right_(right),
			top_(top),
			bottom_(bottom) {};

		RectType(const Vector2& point1, const Vector2& point2)
		{
			left_ = min(point1.x(),point2.x());
			right_ = max(point1.x(),point2.x());
			top_ = max(point1.y(),point2.y());
			bottom_ = min(point1.y(),point2.y());
		};

		RectType(const RectType& rect)
		{
			set(rect);
		};

		RectType(void):
			left_(0),
			right_(0),
			top_(0),
			bottom_(0){};

		virtual ~RectType(void) {};
	};

}
