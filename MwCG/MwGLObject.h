#pragma once
#include "mwx.h" 

namespace mw
{
	class MwGLObject : public CObject
	{
		DECLARE_SERIAL(MwGLObject)
	public:
		MwGLObject(void);
		~MwGLObject(void);
		virtual void Serialize(CArchive& ar);
		//Execute GL command
		inline virtual void GL() {  };
		inline virtual void operator ()() { GL(); }
	};
}
