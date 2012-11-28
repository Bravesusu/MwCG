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
	line_->transform().position().set(transform().position());
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

void mw::MwPolygon::NewVertex(const Vector2& localPos)
{
	vertex_.push_back(shared_ptr<Vector2>(new Vector2(localPos)));
}

void mw::MwPolygon::UpdateLastVertex( const Vector2& localPos )
{
	if (vertex_.size() == 0)
		NewVertex(localPos);
	vertex_.back()->set(localPos);
}

void mw::MwPolygon::set_line( LineFactory* factory )
{
	line_factory_.reset(factory);
	line_.reset(line_factory_->Get());
}

void mw::MwPolygon::SetVertex( int index, const Vector2& localPos )
{
	if (index < 0 || index > vertex_.size())
		return;
	int i = 0;
	for(list<shared_ptr<Vector2>>::const_iterator it = vertex_.begin(); 
		it != vertex_.end(); it++)
	{
		if (i == index)
		{
			(*it)->set(localPos);
			break;
		}
		i++;
	}
}

int mw::MwPolygon::anchor_count() const
{
	return count();
}

void mw::MwPolygon::set_anchor( int index, const Vector2& localPos )
{
	SetVertex(index, localPos);
}

mw::Vector2 mw::MwPolygon::anchor( int index ) const
{
	return vertex(index);
}

mw::Vector2 mw::MwPolygon::vertex( int index ) const
{
	int i = 0;
	for(list<shared_ptr<Vector2>>::const_iterator it = vertex_.begin(); 
		it != vertex_.end(); it++)
	{
		if (i == index)
		{
			return Vector2(**it);
		}
		i++;
	}
}

bool mw::MwPolygon::HitTest( const Vector2& worldPos ) const
{
	if (vertex_.size() <= 1)
		return false;
	line_->transform().position().set(transform().position());
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
		if (line_->HitTest(worldPos))
			return true;

	}
	if (vertex_.size() < 3)
		return false;
	//Last line
	line_->set(*vertex_.back(), *vertex_.front());
	if (line_->HitTest(worldPos))
		return true;
	return false;
}

Line* mw::BresLineFactory::Get() const
{
	return new BresLine();
}

Line* mw::LineFactory::Get() const
{
	return new Line();
}
