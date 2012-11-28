#pragma once
#include "glcmd.h"
namespace mw {
	class GlVertex :
		public GlCmd
	{
	public:
		GlVertex(void);
		~GlVertex(void);
	public:
		void operator()() {}
	};
};

