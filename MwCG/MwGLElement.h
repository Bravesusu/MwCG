#pragma once
#include "mwx.h"
#include "MwColor.h"

using namespace std;

#define MwElementSafePtr unique_ptr<MwGLElement>

class MwGLElement :
	public MwGLObject
{
	DECLARE_SERIAL(MwGLElement);
public:
	MwGLElement(void);
	~MwGLElement(void);
	MwColor Color;

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
