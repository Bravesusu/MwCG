#pragma once
#include "decorator.h"

namespace mw
{
	class Point;
	class PointDecorator :
		public Decorator
	{
	private:
		shared_ptr<Point> point_;
		shared_ptr<Point> dec_;
	public:
		void set(shared_ptr<Point> point) { point_ = point; }
	public:	
		PointDecorator(void);
		~PointDecorator(void);

		virtual void DoDecorate();

	public:
		shared_ptr<Point> operator +(shared_ptr<Point> rhs);
	};
	
	shared_ptr<Point> operator +(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	shared_ptr<Point> operator -(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	shared_ptr<Point> operator +=(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
	shared_ptr<Point> operator -=(shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs);
}
