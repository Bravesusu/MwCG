#pragma once

#include "RenderContext.h"

namespace mw
{
	class Stroke 
		//: public RenderContext
	{
	public:
		Stroke(void);
		~Stroke(void);
	private:
		GLushort pattern_;
	public:

		GLushort pattern() const { return pattern_; }
		void set_pattern(GLushort pattern) { pattern_ = pattern; }
	};
}

