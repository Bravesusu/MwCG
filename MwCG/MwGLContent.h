#pragma once
class MwGLContent : public CObject
{
	DECLARE_SERIAL(MwGLContent);
public:
	MwGLContent(void);
	~MwGLContent(void);
	virtual void Serialize(CArchive& ar);
};

typedef MwGLContent* MwPGLContent;
