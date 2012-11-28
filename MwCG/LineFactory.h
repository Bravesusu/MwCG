#pragma once

namespace mw
{
	class Line;
	class BresLine;
	class LineFactory
	{
	public:
		virtual Line* Get() const;;
	};
	
	class BresLineFactory : public LineFactory
	{
		virtual Line* Get() const;
	};
}
