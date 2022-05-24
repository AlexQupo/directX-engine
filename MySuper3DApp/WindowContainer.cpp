#include "WindowContainer.h"

LRESULT WindowContainer::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
	case WM_KEYDOWN: 
	{
		unsigned char keycode = static_cast<unsigned char>(wparam);
		if (keyboard.IsKeysAutoRepeat()) {
			keyboard.OnKeyPressed(keycode);
		}
		else {
			const bool wasPressed = lparam & 0x40000000;
			if (!wasPressed) {
				keyboard.OnKeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_KEYUP: 
	{
		unsigned char keycode = static_cast<unsigned char>(wparam);
		keyboard.OnKeyReleased(keycode);
		return 0;
	}
	case WM_CHAR: 
	{
		unsigned char ch = static_cast<unsigned char>(wparam);
		if (keyboard.IsCharsAutoRepeat()) {
			keyboard.OnChar(ch);
		}
		else {
			const bool wasPressed = lparam & 0x40000000;
			if (!wasPressed) {
				keyboard.OnChar(ch);
			}
		}
		return 0;
	}

	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}
