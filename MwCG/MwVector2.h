#pragma once
#include "mwglobject.h"
class MwVector2 :
	public MwGLObject
{
	DECLARE_SERIAL(MwVector2)
public:
	float x;
	float y;
public:
	MwVector2(void);
	MwVector2(float fx, float fy);
	~MwVector2(void);
	void GL();
	void Trace();
	virtual void Serialize(CArchive& ar);
};

