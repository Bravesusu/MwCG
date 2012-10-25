#pragma once
#include "mwx.h"
#include "MwGLElement.h"
#include "MwCanvas.h"

using namespace std;

class MwGLContent : public CObject
{
	DECLARE_SERIAL(MwGLContent);
public:
	MwGLContent(void);
	~MwGLContent(void);
	virtual void Serialize(CArchive& ar);

public:
	MwCanvas* GetCanvas() const {return m_pCanvas;}
protected:
	MwCanvas* m_pCanvas;
public:
	vector<MwElementSafePtr> Elements;
public:
};
