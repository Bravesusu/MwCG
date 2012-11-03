#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

namespace mw
{
	class MwSierpinski :
		public MwGLElement
	{
		DECLARE_SERIAL(MwSierpinski);
	private:
		int point_count_;
		MwVector2 vertex_[3];
	public:
		MwVector2& operator[] (int index);
		const MwVector2& operator[] (int index) const;
		MwSierpinski(void) : point_count_(5000) {};
		MwSierpinski(const MwVector2& v1, const MwVector2& v2, const MwVector2& v3);
		~MwSierpinski(void);
		int point_count() { return point_count_; }
		void set_point_count(int count) { point_count_ = count; }
		//Serialization
	public:
		virtual void Serialize(CArchive& ar);
		void Draw();
	};
	
}
