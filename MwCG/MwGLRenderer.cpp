#include "stdafx.h"
#include "MwGLRenderer.h"

MwGLRenderer::MwGLRenderer(void)
{
}


MwGLRenderer::~MwGLRenderer(void)
{
}


bool MwGLRenderer::Initialize(HDC hDC)
{
	m_hViewDC = hDC;
	if (!hDC)
	{
		TRACE0("Cannot Initialize(NULL)\n");
		return false;
	}

	if (!SetWindowPixelFormat())
	{
		TRACE0("Failed to SetWindowPixelFormat\n");
		return false;
	}
	if (!CreateGLContext())
	{
		TRACE0("Failed to CreateGLContext\n");
		return false;
	}

	ASSERT(m_hRC);
	return true;
}


void MwGLRenderer::Finalize(void)
{
	DestoryGLContext();
}


void MwGLRenderer::Draw(const MwGLContent* pContent)
{
	glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
   /* glBegin(GL_POLYGON);
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        glVertex2f(100.0f,50.0f);
        glColor4f(0.0f,1.0f,0.0f,1.0f);
        glVertex2f(450.0f,400.0f);
        glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex2f(450.0f,50.0f);
    glEnd();*/
	glColor3f(1, 0, 0);
	glBegin(GL_LINES); 
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 50.0);
	glEnd(); 
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 50.0);
	glEnd();
    glFlush();
}


BOOL MwGLRenderer::SetWindowPixelFormat(void)
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

	int nGLPixelIndex = ChoosePixelFormat(m_hViewDC,&pixelDesc);
	if (!nGLPixelIndex)
	{
		//nGLPixelIndex = 1;
		if(!DescribePixelFormat(m_hViewDC, nGLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc))
		{
			return FALSE;
		}
	}

	if(!SetPixelFormat(m_hViewDC, nGLPixelIndex, &pixelDesc))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL MwGLRenderer::CreateGLContext(void)
{
	m_hRC = wglCreateContext(m_hViewDC);
    if(!m_hRC)
	{
        return FALSE;
    }

    if(!wglMakeCurrent(m_hViewDC, m_hRC))
    {
        return FALSE;
    }

    return TRUE;
}


void MwGLRenderer::DestoryGLContext(void)
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


bool MwGLRenderer::IsValid(void)
{
	return m_hRC;
}


void MwGLRenderer::SetViewSize(int cx, int cy)
{
	GLsizei width, height;
    GLdouble aspect;
    width = cx;
    height = cy;
    if(cy == 0)
    {
        aspect = (GLdouble)width;
    }
    else
    {
        aspect = (GLdouble)width / (GLdouble)height;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0*aspect, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
