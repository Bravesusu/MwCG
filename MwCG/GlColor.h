#pragma once
#include "glcmd.h"
namespace mw {
	class GlColor :
		public GlCmd
	{
	public:
		GlColor(void);
		~GlColor(void);
	public:
		void operator()() {};
	};
};

