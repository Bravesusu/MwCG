#pragma once
#include "mwx.h" 

class MwGLObject : public CObject
{
	DECLARE_SERIAL(MwGLObject)
public:
	MwGLObject(void);
	~MwGLObject(void);
	virtual void Serialize(CArchive& ar);
	//Execute GL command
	virtual void GL() { TRACE0("MwGLObject::GL()\n"); };
	void operator ()() { GL(); }
};

