#pragma once
#include "mwx.h" 

namespace mw
{
	class GlObject : public CObject
	{
		DECLARE_SERIAL(GlObject)
	public:
		GlObject(void);
		~GlObject(void);
		virtual void Serialize(CArchive& ar);
		//Execute GL command
		virtual void GL() {  };
		void operator ()() { GL(); }
	};
}
