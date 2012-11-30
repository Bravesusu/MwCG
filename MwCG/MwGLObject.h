#pragma once
#include "mwx.h" 

namespace mw
{
	// The base class of all. Defines interfaces for 
	//* Serialization (inherited from CObject)
	//* OpenGL Command Method
	class GlObject : public CObject
	{
		DECLARE_SERIAL(GlObject)
	public:
		GlObject(void);
		virtual ~GlObject(void) {};
		virtual void Serialize(CArchive& ar);
		//Execute GL command
		virtual void GL() {  };
		//Make it a callable object
		void operator ()() { GL(); }
	};
}
