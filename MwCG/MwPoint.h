#pragma once
#include "mwglelement.h"
#include "MwVector2.h"
class MwPoint :
	public MwGLElement
{
	DECLARE_SERIAL(MwPoint)
public:
	MwPoint(void);
	~MwPoint(void);
	MwPoint(float x, float y, float size = 1.0);
	//Serialization
	MwVector2 Position;
	float Size;
public:
	virtual void Serialize(CArchive& ar);
	inline void Draw();
};

