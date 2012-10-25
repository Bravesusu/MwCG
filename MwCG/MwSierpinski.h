#pragma once
#include "mwglelement.h"
class MwSierpinski :
	public MwGLElement
{
	DECLARE_SERIAL(MwSierpinski);
public:
	MwSierpinski(void);
	~MwSierpinski(void);
	//Serialization
public:
	virtual void Serialize(CArchive& ar);
};

