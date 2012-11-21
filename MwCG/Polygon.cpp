#include "stdafx.h"
#include "Polygon.h"
#include "Rect.h"
#include "mwline.h"
#include "BresLine.h"


using namespace mw;

IMPLEMENT_SERIAL(MwPolygon, GlElement, 1);

MwPolygon::MwPolygon(void)
{
	if (line_factory_ == NULL)
		line_factory_.reset(new LineFactory());
	line_.reset(line_factory_->Get());
}

mw::MwPolygon::MwPolygon( LineFactory* factory ) : line_factory_(factory)
{
	line_.reset(line_factory_->Get());
}

mw::MwPolygon::MwPolygon( shared_ptr<LineFactory> factory ) : line_factory_(factory)
{
	line_.reset(line_factory_->Get());
}

MwPolygon::~MwPolygon(void)
{
}

void mw::MwPolygon::Serialize( CArchive& ar )
{
	GlElement::Serialize(ar);

	CObArray arr;

	if (ar.IsStoring())
	{
		for (list<shared_ptr<Vector2>>::const_iterator it = vertex_.begin(); it != vertex_.end(); it++)
		{
			arr.Add(it->get());
		}
		arr.Serialize(ar);
	}
	else
	{
		arr.Serialize(ar);
		for (int i = 0; i < arr.GetSize(); i++)
		{			
			shared_ptr<Vector2> v = shared_ptr<Vector2>(DYNAMIC_DOWNCAST(Vector2, arr[i]));
			vertex_.push_back(v);
		}
		line_factory_.reset(new LineFactory());
	}
}

void mw::MwPolygon::DoDraw()
{
}

//bool mw::Polygon::HitTest()
//{
//}

Rect mw::MwPolygon::bound() const
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

void mw::MwPolygon::Draw()
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

void mw::MwPolygon::NewVertex(const Vector2& pos)
{
	vertex_.push_back(shared_ptr<Vector2>(new Vector2(pos)));
}

void mw::MwPolygon::UpdateLastVertex( const Vector2& pos )
{
	if (vertex_.size() == 0)
		NewVertex(pos);
	vertex_.back()->set(pos);
}

void mw::MwPolygon::set_line( LineFactory* factory )
{
	line_factory_.reset(factory);
	line_.reset(line_factory_->Get());
}

void mw::MwPolygon::SetVertex( int index, const Vector2& pos )
{
	if (index < 0 || index > vertex_.size())
		return;
	int i = 0;
	for(list<shared_ptr<Vector2>>::const_iterator it = vertex_.begin(); 
		it != vertex_.end(); it++)
	{
		if (i == index)
		{
			(*it)->set(pos);
			break;
		}
		i++;
	}
}

Line* mw::BresLineFactory::Get() const
{
	return new BresLine();
}

Line* mw::LineFactory::Get() const
{
	return new Line();
}
