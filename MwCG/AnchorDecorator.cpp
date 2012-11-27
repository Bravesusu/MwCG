#include "stdafx.h"
#include "AnchorDecorator.h"
#include "MwGLElement.h"

using namespace mw;

IMPLEMENT_DECORATOR_OP(GlElement, AnchorDecorator);

AnchorDecorator::AnchorDecorator(void)
{
}


AnchorDecorator::~AnchorDecorator(void)
{
}

void mw::AnchorDecorator::DoDecorate()
{
}

void mw::AnchorDecorator::BeginInput( const Vector2& worldPos )
{
}

void mw::AnchorDecorator::UpdateInput( const Vector2& worldPos )
{
}

void mw::AnchorDecorator::EndInput( const Vector2& worldPos )
{
}
