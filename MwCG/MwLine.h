#pragma once
#include "mwglelement.h"
class MwLine :
	public MwGLElement
{
	DECLARE_SERIAL(MwLine);
public:
	MwLine(void);
	~MwLine(void);
	//Serialization
public:
	virtual void Serialize(CArchive& ar);
};

