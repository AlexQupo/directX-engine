#include "WindowContainer.h"

LRESULT WindowContainer::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	OutputDebugStringA("AAAA\n");
	return DefWindowProc(hwnd, umessage, wparam, lparam);
}
