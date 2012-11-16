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

		void Decorate();

		virtual void DoDecorate() = 0;
		virtual void Removed() {};
	//public:
	//	shared_ptr<GlElement>& operator+(shared_ptr<GlElement>& rhs);
	//	GlElement& operator+(GlElement& rhs);
	};

	typedef shared_ptr<Decorator> DecoratorPtr;
}
