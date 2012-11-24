#pragma once
#include "mwglobject.h"

namespace mw
{
	class Transform :
		public GlObject
	{
		DECLARE_SERIAL(Transform);
	private:
		Vector2 pos_;
	public:
		Vector2& position() { return pos_; }
		Vector2 position() const { return pos_; }
	public:
		void LocalToWorld(Vector2& localPos) const;
		void WorldToLocal(Vector2& worldPos) const;
	public:
		Transform(void);
		~Transform(void);
	public:
		//NOTE: need a mechanism to forbid classes other than GlElement to call  
		void Push() const;
		void Pop() const;

		virtual void Serialize( CArchive& ar );

	};

}
