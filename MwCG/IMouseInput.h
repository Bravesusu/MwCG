#pragma once

namespace mw
{
	class IMouseInput
	{
	public:
		virtual void BeginInput(const Vector2& worldPos) = 0;
		virtual void UpdateInput(const Vector2& worldPos) = 0;
		virtual void EndInput(const Vector2& worldPos) = 0;

	};


	//class MouseInput :
	//	public IMouseInput
	//{
	//private:
	//	Vector2 mouse_;
	//	Vector2 mouse_down_;
	//	Vector2 mouse_last_;
	//protected:
	//	//The pos of last update
	//	Vector2 mouse_last_pos() const { return mouse_last_; }
	//	Vector2 mouse_down_pos() const { return mouse_down_; }
	//	Vector2 mouse_pos() const { return mouse_; }
	//	Vector2 mouse_delta() const { return mouse_ - mouse_down_; }
	//	Vector2 mouse_inst_delta() const { return mouse_ - mouse_last_; }

	//public:
	//	void BeginInput( const Vector2& worldPos );

	//	void UpdateInput( const Vector2& worldPos );

	//	void EndInput( const Vector2& worldPos );
	//protected:

	//	virtual void DoBeginInput() {};
	//	virtual void DoUpdateInput() {};
	//	virtual void DoEndInput() {};

	//};
}
