#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

class MwSierpinski :
	public MwGLElement
{
	DECLARE_SERIAL(MwSierpinski);
public:
	MwSierpinski(void);
	~MwSierpinski(void);
	//Serialization
	MwVector2 Vertex[3];
public:
	virtual void Serialize(CArchive& ar);
	void Draw();
};

