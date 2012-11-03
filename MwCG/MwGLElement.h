#pragma once
#include "mwx.h"
#include "MwColor.h"

#define MwElementSafePtr unique_ptr<GlElement>
using namespace std;

namespace mw 
{
	class GlElement :
		public CObject
	{
		DECLARE_SERIAL(GlElement);
	private:
		Color color_;
	public:
		GlElement(void);
		~GlElement(void);
		Color color() const { return color_; }
		void set_color(float r, float g, float b, float a = 1.0) { color_.set(r, g, b, a); }
		void set_color(COLORREF color) { color_.set(color); }
		void set_color(const Color& color) { color_.set(color); }

		//Serialization
	public:
		virtual void Serialize(CArchive& ar);

		//Rendering
	public:
		inline virtual void Draw() {};
		virtual bool HitTest() { return false; };

		//TODO: components
	public:

		//Hierarchy
	private:
		//MwGLContent *m_pContent;
	public:
		//void AttachToContent(MwGLContent* content) {};
		void SetParent(GlElement& parent) {};
	};
}
