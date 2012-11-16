#pragma once
#include "idrawable.h"

namespace mw
{
	class GlElement;

	class Decorator
	{
	public:
		Decorator(void);
		~Decorator(void);

		void Decorate(const shared_ptr<GlElement>);

		virtual void DoDecorate(const shared_ptr<GlElement>) = 0;
	public:
		shared_ptr<GlElement>& operator+(shared_ptr<GlElement>& rhs);
		GlElement& operator+(GlElement& rhs);
	};

}
