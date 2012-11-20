#pragma once

#include "RenderContext.h"

namespace mw
{
	enum StrokeType : GLushort
	{
		ST_FULL		= 0xFFFF,
		ST_DOT		= 0xAAAA,
		ST_DASH		= 0xCCCC
	};
	struct Stroke 
	{
		GLushort pattern;
	};

	const struct Stroke FullStroke = { ST_FULL };
	const struct Stroke DotStroke = { ST_DOT };
	const struct Stroke DashStroke = { ST_DASH };
	const int StrokeCount = 3;
	const Stroke Strokes[] = { FullStroke, DotStroke, DashStroke };
}

