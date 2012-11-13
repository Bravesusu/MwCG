#pragma once
#include "uieditor.h"

namespace mw
{
	class UiCreator :
		public UiEditor
	{
	public:
		UiCreator(void);
		~UiCreator(void);
	public:
		virtual void CommitInput() = 0;
		virtual bool IsFinished() const = 0;
	};
}

