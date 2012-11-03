#pragma once
#include "MwGLContent.h"
#include <gl/gl.h>   
#include <gl/glu.h> 

namespace mw
{
	class GlRenderer
	{
	public:
		GlRenderer(void);
		~GlRenderer(void);
		
		bool Initialize(const HDC& hDC);
		void Finalize(void);
		void Draw(GlContent* pContent);
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
		void SetViewSize(int x, int y, int width, int height);
	};
	
}
