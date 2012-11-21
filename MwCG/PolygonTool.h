#pragma once
#include "uieditortool.h"
#include "LineFactory.h"

namespace mw
{
	class Polygon;
	class PolygonTool :
		public UiEditorTool
	{
	private:
		bool recvEnter_;
		shared_ptr<Polygon> polygon_;
		shared_ptr<LineFactory> line_factory_;
	public:
		PolygonTool(LineFactory* lineFactory);
		~PolygonTool(void);

		virtual shared_ptr<GlElement> GetEditingElement();

		virtual OperationPtr PopNewOperation();

		virtual void DoNew();

		virtual void DoNextInput();

		virtual void DoUpdateInput();

		virtual void DoFixInput( const int index );

		virtual bool IsFinished() const;

		virtual void Draw();

		virtual bool CanFinishByEnter();

	};
	
}
