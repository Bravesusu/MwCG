#include "stdafx.h"
#include "MwGLRenderer.h"

MwGLRenderer::MwGLRenderer(void)
{
}


MwGLRenderer::~MwGLRenderer(void)
{
}


bool MwGLRenderer::Initialize(const HDC& hDC)
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


void MwGLRenderer::Finalize(void)
{
	DestoryGLContext();
}


void MwGLRenderer::Draw(MwGLContent* pContent)
{
	glLoadIdentity();
	pContent->GetCanvas()->Draw();
    //glClear(GL_COLOR_BUFFER_BIT);
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
	//v.GL();
	glEnd(); 
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 50.0);
	//v.GL();
	glEnd();
    glFlush();
}


BOOL MwGLRenderer::SetWindowPixelFormat(const HDC& hDC)
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


BOOL MwGLRenderer::CreateGLContext(const HDC& hDC)
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


BOOL MwGLRenderer::Activate(const HDC& hDC)
{
    return wglMakeCurrent(hDC, m_hRC);
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


void MwGLRenderer::SetViewSize(int x, int y, int width, int height)
{
    //if(cy == 0)
    //{
    //    aspect = (GLdouble)width;
    //}
    //else
    //{
    //    aspect = (GLdouble)width / (GLdouble)height;
    //}
    glViewport(x, y, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0.0, 500.0*aspect, 0.0, 500.0);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

}
