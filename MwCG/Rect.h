#pragma once

namespace mw
{
	class MwGLObject;
	class Rect :
		public MwGLObject
	{
		DECLARE_SERIAL(Rect);
	private:
		float left_, right_, top_, bottom_;
	public:
		Rect(void);
		~Rect(void);

		virtual void Serialize( CArchive& ar );

		virtual void GL();

	};
}

