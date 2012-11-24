#include "stdafx.h"
#include "MwTransform.h"

using namespace mw;

IMPLEMENT_SERIAL(Transform, GlObject, 1);

Transform::Transform(void)
{
}


Transform::~Transform(void)
{
}

void mw::Transform::Push() const
{
	glPushMatrix();

	//TODO: Translate
	glTranslatef(pos_.x(), pos_.y(), 0);

	//TODO: Rotation
}

void mw::Transform::Pop() const
{
	glPopMatrix();
}

void mw::Transform::Serialize( CArchive& ar )
{
	GlObject::Serialize(ar);

	pos_.Serialize(ar);
}
