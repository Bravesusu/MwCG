#pragma once
#include "MwGLContent.h"
#include <gl/gl.h>   
#include <gl/glu.h> 

class MwGLRenderer
{
public:
	MwGLRenderer(void);
	~MwGLRenderer(void);
	
	bool Initialize(HDC hDC);
	void Finalize(void);
	void Draw(const MwGLContent* pContent);
protected:
	BOOL SetWindowPixelFormat(void);
	BOOL CreateGLContext(void);
public:
	void DestoryGLContext(void);
protected:
	//The DC of View to render
	HDC m_hViewDC;
	//The render context
	HGLRC m_hRC;
public:
	bool IsValid(void);
	void SetViewSize(int cx, int cy);
};

