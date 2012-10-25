#pragma once
#include "mwx.h"

#define VECTOR2F(x, y) new MwVector2(x, y)

class MwVector2 :
	public MwGLObject
{
	DECLARE_SERIAL(MwVector2)
public:
	float x;
	float y;
public:
	MwVector2(void);
	MwVector2(float fx, float fy);
	~MwVector2(void);
	void GL();
	void Trace();
	void Serialize(CArchive& ar);
public:
	MwVector2 operator+(const MwVector2& other) const;
	MwVector2& operator+=(const MwVector2& other);
	MwVector2 operator/(float f) const;
	MwVector2& operator/=(float f);
};

