#pragma once
#include "mwglobject.h"

namespace mw
{
	class Transform :
		public GlObject
	{
	private:
		Vector2 pos_;
	public:
		Vector2& Position() { return pos_; }
	public:
		Transform(void);
		~Transform(void);
	public:
		//NOTE: need a mechanism to forbid classes other than GlElement to call  
		void Push() const;
		void Pop() const;
	};

}
