#pragma once
#include "MwGLContent.h"

class MwGLRenderer
{
public:
	MwGLRenderer(void);
	~MwGLRenderer(void);
	
	bool Initialize(HDC hDC);
	void Finalize(void);
	void Draw(const MwGLContent* pContent);
};

