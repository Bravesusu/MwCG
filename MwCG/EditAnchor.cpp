#include "stdafx.h"
#include "EditAnchor.h"

#include "MwGLElement.h"

using namespace mw;

EditAnchor::EditAnchor(shared_ptr<GlElement> element, int anchor_index) : anchor_index_(anchor_index)
{
	Initialize(element);
}


EditAnchor::~EditAnchor(void)
{
}

void mw::EditAnchor::Undo()
{
	Vector2 localPos = old_world_pos_;
	element()->transform().WorldToLocal(localPos);
	element()->set_anchor(anchor_index_, localPos);
	element()->ResetTransformToAnchor(0);

}

void mw::EditAnchor::Redo()
{
	Vector2 localPos = new_world_pos_;
	element()->transform().WorldToLocal(localPos);
	element()->set_anchor(anchor_index_, localPos);
	element()->ResetTransformToAnchor(0);
}

void mw::EditAnchor::set_old_anchor( const Vector2& worldPos )
{
	old_world_pos_ = worldPos;
}

void mw::EditAnchor::set_new_anchor( const Vector2& worldPos )
{
	new_world_pos_ = worldPos;
}
