#pragma once
#include "mwglelement.h"
#include "MwColor.h"
#include "MwLine.h"

namespace mw
{
	class Canvas :
		public GlElement
	{
		DECLARE_SERIAL(Canvas);
	//Serialization
	public:
		virtual void Serialize(CArchive& ar);
	
	private:
		void DoDraw();
	public:
		Canvas(void);
		~Canvas(void);

	private:
		Line gird_line_;
		void DrawAxisGird();
	private:
		bool enable_gird_;

	public:
		bool gird_enabled() const { return enable_gird_; }
		void set_enable_gird(bool enabled) { enable_gird_ = enabled; } 
		void toggle_gird() { enable_gird_ = !enable_gird_; }

		virtual Rect bound() const;

	};
}

