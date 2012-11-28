#include "stdafx.h"
#include "MwGLRenderer.h"


using namespace mw;

GlRenderer::GlRenderer(void)
{
}


GlRenderer::~GlRenderer(void)
{
}


bool GlRenderer::Initialize(const HDC& hDC)
{
	//m_hViewDC = hDC;
	if (!hDC)
	{
		TRACE0("Cannot Initialize(NULL)\n");
		return false;
	}

	if (!SetWindowPixelFormat(hDC))
	{
		TRACE0("Failed to SetWindowPixelFormat\n");
		return false;
	}
	if (!CreateGLContext(hDC))
	{
		TRACE0("Failed to CreateGLContext\n");
		return false;
	}

	ASSERT(m_hRC);
	return true;
}


void GlRenderer::Finalize(void)
{
	DestoryGLContext();
}

//
//void GlRenderer::Draw(const shared_ptr<GlContent>& pContent)
//{
//	glLoadIdentity();
//
//	pContent->Draw();
//	
//	glFlush();
//}

void mw::GlRenderer::Draw( const shared_ptr<IDrawable>& drawable )
{
	glLoadIdentity();

	drawable->Draw();

	glFlush();
}


BOOL GlRenderer::SetWindowPixelFormat(const HDC& hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int nGLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (!nGLPixelIndex)
	{
		//nGLPixelIndex = 1;
		if(!DescribePixelFormat(hDC, nGLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc))
		{
			return FALSE;
		}
	}

	if(!SetPixelFormat(hDC, nGLPixelIndex, &pixelDesc))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL GlRenderer::CreateGLContext(const HDC& hDC)
{
	m_hRC = wglCreateContext(hDC);
	if(!m_hRC)
	{
		return FALSE;
	}

	if(!Activate(hDC))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL GlRenderer::Activate(const HDC& hDC)
{
	return wglMakeCurrent(hDC, m_hRC);
}


void GlRenderer::DestoryGLContext(void)
{
	if(wglGetCurrentContext())
	{
		wglMakeCurrent(NULL, NULL);
	}

	if(m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}


bool GlRenderer::IsValid(void)
{
	return m_hRC != NULL;
}


//void GlRenderer::SetViewSize(int x, int y, int width, int height)
//{
//	GLdouble hw = width / 2;
//	GLdouble hh = height / 2;
//	glViewport(0, 0, width, height);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-hw - x, hw - x, -hh - y, hh - y);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//}
