#pragma once

class IRecvView
{
public:
	virtual void SendMouseMove(UINT nFlags, CPoint screenPoint) = 0;
};

