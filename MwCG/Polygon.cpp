#include "stdafx.h"
#include "Polygon.h"
#include "Rect.h"
#include "mwline.h"

using namespace mw;

//IMPLEMENT_SERIAL(Polygon, GlElement, 1);

Polygon::Polygon(void)
{
	line_.reset(new Line());
}


Polygon::~Polygon(void)
{
}

void mw::Polygon::Serialize( CArchive& ar )
{
}

void mw::Polygon::DoDraw()
{
}

//bool mw::Polygon::HitTest()
//{
//}

Rect mw::Polygon::bound() const
{
	float left = (*vertex_.begin())->x();
	float right = left;
	float top = (*vertex_.begin())->y();
	float bottom = top;

	for(list<shared_ptr<Vector2>>::const_iterator it = vertex_.begin(); it != vertex_.end(); it++)
	{
		left = min(left, (*it)->x());
		right = max(right, (*it)->x());
		top = max(top, (*it)->y());
		bottom = min(bottom, (*it)->y());
	}

	return Rect(left, right, top, bottom);
}

void mw::Polygon::Draw()
{
	if (vertex_.size() <= 1)
		return;
	line_->set_color(color());
	line_->set_size(size());
	line_->set_stroke(stroke());
	for(list<shared_ptr<Vector2>>::const_iterator 
			it_from = vertex_.begin(), 
			it_to	= vertex_.begin()
		; it_from != vertex_.end() && it_to != vertex_.end(); it_from++, it_to++)
	{
		if (it_from == it_to)
		{
			it_to++;
			if (it_to == vertex_.end())
				break;
		}
		line_->set(**it_from, **it_to);
		line_->Draw();
	}
	if (vertex_.size() < 3)
		return;
	//Last line
	line_->set(*vertex_.back(), *vertex_.front());
	line_->Draw();
}

void mw::Polygon::NewVertex(const Vector2& pos)
{
	vertex_.push_back(shared_ptr<Vector2>(new Vector2(pos)));
}

void mw::Polygon::UpdateLastVertext( const Vector2& pos )
{
	if (vertex_.size() == 0)
		NewVertex(pos);
	vertex_.back()->set(pos);
}
