#include "Display.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {

	switch (umessage) {

	case WM_KEYDOWN: {
		if (static_cast<unsigned int>(wparam) == 27) PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}

bool Display::Initialize(LPCWSTR appName, int height, int width) {

	applicationName = appName;
	clientHeight = height;
	clientWidth = width;
	//WndProc = MessageHandler;
	RegisterWindowClass();

	RECT windowRect = { 0,0,static_cast<LONG>(clientWidth), static_cast<LONG>(clientHeight) };
	AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);


	//����� ����
	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
	//��������� ���� �� ������. � ������ ������ ���� ����� ���������� ����������.
	auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;
	//���������� ����
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	if(hWnd == nullptr) {
		//ErrorLogger::Log(GetLastError(),"CreateWindowEX Failed for window: " + applicationName);
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);//����� ����
	SetForegroundWindow(hWnd);//������ ������ ����
	SetFocus(hWnd);//��������� ������ (�������) �� ��� ����

	ShowCursor(true);//����� �������

	return true;
}

void Display::RegisterWindowClass() {
	//���� ����������� ����
	hInstance = GetModuleHandle(nullptr);
	//WNDCLASSEX wc - ������������ ����� ����. ���������� ��������� ��� �� �������� (�����������)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //������������� ����� ����, ����� ��� ����������������
	wc.lpfnWndProc = WndProc; //��������� �� ������� ��� ��������� ��������� �� ����                  !!!!!!!!!!!WndProc!!!!!!!!!!!!!
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance; //���������� (����������) ����������, ����������� ������� ���������
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc); //����������� ������ ��� ����������� ��� ������������
}

bool Display::ProcessMessages() {

	MSG msg = {};
	//ZeroMemory(&msg, sizeof(MSG)); // what is it?

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) {
		if (!IsWindow(hWnd)) {
			hWnd = nullptr;
			UnregisterClass(applicationName, hInstance);
			return false;
		}
	}
	return true;
}



Display::~Display() {
	if(this->hWnd != nullptr)
	{
		UnregisterClass(applicationName, hInstance);
		DestroyWindow(hWnd);
	}
}
