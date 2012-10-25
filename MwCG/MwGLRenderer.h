#pragma once
#include "MwGLContent.h"
#include <gl/gl.h>   
#include <gl/glu.h> 

class MwGLRenderer
{
public:
	MwGLRenderer(void);
	~MwGLRenderer(void);
	
	bool Initialize(const HDC& hDC);
	void Finalize(void);
	void Draw(MwGLContent* pContent);
	BOOL Activate(const HDC& hDC);
protected:
	BOOL SetWindowPixelFormat(const HDC& hDC);
	BOOL CreateGLContext(const HDC& hDC);
public:
	void DestoryGLContext(void);
protected:
	//The render context
	HGLRC m_hRC;
public:
	bool IsValid(void);
	void SetViewSize(int cx, int cy);
};

