#pragma once
#include "mwx.h"

using namespace std;

class MwGLElement :
	public MwGLObject
{
	DECLARE_SERIAL(MwGLElement);
public:
	MwGLElement(void);
	~MwGLElement(void);

//Serialization
public:
	virtual void Serialize(CArchive& ar);
	
//Rendering
public:
	virtual void Draw() {};
	virtual bool HitTest() { return false; };

//ID
public:
	int index;
	CString name;

//TODO: components
public:

//Hierarchy
protected:
	//MwGLContent *m_pContent;
public:
	//void AttachToContent(MwGLContent* content) {};
	void SetParent(MwGLElement& parent) {};
};

