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
	MwPoint(float x, float y);
	//Serialization
	MwVector2 Position;
public:
	virtual void Serialize(CArchive& ar);
	inline void Draw();
};

