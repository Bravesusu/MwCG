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

void mw::Transform::LocalToWorld( Vector2& localPos ) const
{
	//Apply position
	localPos += pos_;
}

mw::Vector2 mw::Transform::LocalToWorld( const Vector2& localPos ) const
{
	return localPos + pos_;
}

void mw::Transform::WorldToLocal( Vector2& worldPos ) const
{
	//Apply position
	worldPos -= pos_;
}

mw::Vector2 mw::Transform::WorldToLocal( const Vector2& worldPos ) const
{
	return worldPos - pos_;
}
