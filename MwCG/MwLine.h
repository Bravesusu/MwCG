#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

namespace mw
{
	class MwLine :
		public MwGLElement
	{
		DECLARE_SERIAL(MwLine);
	private:
		MwVector2 point_from_, point_to_;
	public:
		MwLine(void);
		MwLine(float x1, float y1, float x2, float y2);
		MwLine(const MwVector2& from, const MwVector2& to) : point_from_(from), point_to_(to) {} ;
		~MwLine(void);
		//Serialization
		MwVector2 point_from() const { return point_from_; }
		MwVector2 point_to() const { return point_to_; }
		void set(float x1, float y1, float x2, float y2) { point_from_.set(x1, y1); point_to_.set(x2, y2); }
		void set(const MwVector2& from, const MwVector2& to) { point_from_ = from; point_to_ = to; }
		void set_from(float x, float y) { point_from_.set(x, y);}
		void set_from(const MwVector2& from) { point_from_ = from; }
		void set_to(float x, float y) { point_to_.set(x, y);}
		void set_to(const MwVector2& to) { point_to_ = to; }
	public:
		virtual void Serialize(CArchive& ar);
		inline void Draw();
	};
	
}
