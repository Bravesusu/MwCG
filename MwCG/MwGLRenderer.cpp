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
}


BOOL MwGLRenderer::SetWindowPixelFormat(void)
{
	PIXELFORMATDESCRIPTOR pixelDesc = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
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
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}

	if(m_hRC!=NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}


bool MwGLRenderer::IsValid(void)
{
	return m_hRC;
}
