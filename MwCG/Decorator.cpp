#include "stdafx.h"
#include "Decorator.h"
#include "MwGLElement.h"

using namespace mw;

Decorator::Decorator(void)
{
}


Decorator::~Decorator(void)
{
}

void mw::Decorator::Decorate()
{
	DoDecorate();
}
//
//shared_ptr<GlElement>& mw::Decorator::operator+( shared_ptr<GlElement>& rhs ) 
//{
//	rhs->AddDecorator(shared_ptr<Decorator>(this));
//	return rhs;
//}
//
//GlElement& mw::Decorator::operator+( GlElement& rhs ) 
//{
//	rhs.AddDecorator(shared_ptr<Decorator>(this));
//	return rhs;
//}
