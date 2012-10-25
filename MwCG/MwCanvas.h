#pragma once
#include "mwglelement.h"
#include "MwColor.h"

class MwCanvas :
	public MwGLElement
{
	DECLARE_SERIAL(MwCanvas);
public:
	static const int DefaultWidth = 800;
	static const int DefaultHeight = 600;
public:
	int Width;
	int Height;
//Serialization
public:
	virtual void Serialize(CArchive& ar);

public:
	void Draw();
public:
	MwCanvas(void);
	MwCanvas(int width, int height);
	~MwCanvas(void);
};

