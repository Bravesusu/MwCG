#pragma once
#include "mwglelement.h"
#include "MwVector2.h"
#include <vector>
class MwPoint :
	public MwGLElement
{
	DECLARE_SERIAL(MwPoint)
	vector<int> test;
public:
	MwPoint(void) : size_(1) {};
	~MwPoint(void);
	MwPoint(float x, float y, float size = 1.0) : position_(x, y), size_(size) {} ;
	//Serialization
protected:
	MwVector2 position_;
	float size_;
public:
	MwVector2 position() const { return position_; }
	float size() const { return size_; }
	void set_position(float x, float y) { position_.set(x, y); }
	void set_size(float size) { size_ = size; }
public:
	virtual void Serialize(CArchive& ar);
	inline void Draw();
};

