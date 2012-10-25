#pragma once
#include "mwx.h"

class MwGLContent : public CObject
{
	DECLARE_SERIAL(MwGLContent);
public:
	MwGLContent(void);
	~MwGLContent(void);
	virtual void Serialize(CArchive& ar);

public:
	MwVector2* FooPoint;
	MwColor* ClearColor;
};

typedef MwGLContent* MwPGLContent;
