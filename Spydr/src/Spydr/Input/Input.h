#pragma once

#include "Spydr/Core.h"

namespace Spydr
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;				 //Gets implemented by platform-specific code
		virtual bool IsMouseButtonPressedImpl(int button) = 0;		 //Gets implemented by platform-specific code
		virtual float GetMouseXImpl() = 0;			   				 //Gets implemented by platform-specific code
		virtual float GetMouseYImpl() = 0;							 //Gets implemented by platform-specific code
		virtual std::pair <float, float> GetMousePositionImpl() = 0; //Gets implemented by platform-specific code
	private:
		static Input* s_Instance;
	};
}