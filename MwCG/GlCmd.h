#pragma once
#include "afx.h"

namespace mw {
	class GlCmd :
		public CObject
	{
	public:
		GlCmd(void);
		~GlCmd(void);
	public:
		virtual void operator()() = 0;
	};
};

