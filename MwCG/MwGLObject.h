#pragma once
#include "afx.h"
#include <gl/gl.h>   
#include <gl/glu.h> 

class MwGLObject : public CObject
{
	DECLARE_SERIAL(MwGLObject)
public:
	MwGLObject(void);
	~MwGLObject(void);
	virtual void Serialize(CArchive& ar);
	//Execute GL command
	virtual void GL() { TRACE0("MwGLObject::GL()\n"); };
};

