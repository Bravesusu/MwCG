#pragma once
#include "mwglelement.h"
class MwPoint :
	public MwGLElement
{
	DECLARE_SERIAL(MwPoint)
public:
	MwPoint(void);
	~MwPoint(void);
	//Serialization
public:
	virtual void Serialize(CArchive& ar);
};

