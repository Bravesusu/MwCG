#pragma once
#include "decorator.h"

namespace mw
{
	class Point;
	class PointDecorator :
		public Decorator,
		public DecoratorOp<Point>
	{
	private:
		shared_ptr<Point> dec_;
	public:	
		PointDecorator(void);
		~PointDecorator(void);

		virtual void DoDecorate();

	};
	DECLARE_DECORATOR_OP(Point, PointDecorator);
	//shared_ptr<Point> operator +(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	//shared_ptr<Point> operator -(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	//shared_ptr<Point> operator +=(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	//shared_ptr<Point> operator -=(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
}
