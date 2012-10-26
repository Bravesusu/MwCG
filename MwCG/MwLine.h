#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

class MwLine :
	public MwGLElement
{
	DECLARE_SERIAL(MwLine);
public:
	MwLine(void);
	MwLine(float x1, float y1, float x2, float y2);
	~MwLine(void);
	//Serialization
	MwVector2 Point1;
	MwVector2 Point2;
public:
	virtual void Serialize(CArchive& ar);
	inline void Draw();
};

