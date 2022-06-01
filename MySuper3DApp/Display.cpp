#include "WindowContainer.h"

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {

	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		return 0;
	}
	default:
	{
		//retrieve ptr to window class
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		//forward message to window class handler
		return pWindow->WndProc(hwnd, umessage, wparam, lparam);
	}
	}

}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {

	switch (umessage) {

	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) {
			//ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));

		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WndProc(hwnd, umessage, wparam, lparam);
	}
	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}


bool Display::Initialize(WindowContainer* pWindowContainer, LPCWSTR appName, int width, int height) {

	applicationName = appName;
	clientHeight = height;
	clientWidth = width;
	//WndProc = MessageHandler;
	RegisterWindowClass();

	auto dwStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	//WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->clientWidth / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->clientHeight / 2;

	RECT wr; //Widow Rectangle
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + this->clientWidth;
	wr.bottom = wr.top + this->clientHeight;
	AdjustWindowRect(&wr, dwStyle, FALSE);

	this->hWnd = CreateWindowEx(0, //Extended Windows style - we are using the default. For other options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
		this->applicationName, //Window class name
		this->applicationName, //Window Title
		dwStyle, //Windows style
		wr.left, //Window X Position
		wr.top, //Window Y Position
		wr.right - wr.left, //Window Width
		wr.bottom - wr.top, //Window Height
		nullptr, //Handle to parent of this window. Since this is the first window, it has no parent window.
		nullptr, //Handle to menu or child window identifier. Can be set to NULL and use menu in WindowClassEx if a menu is desired to be used.
		this->hInstance, //Handle to the instance of module to be used with this window
		pWindowContainer); //Param to create window

	//RECT windowRect = { 0,0,static_cast<LONG>(clientWidth), static_cast<LONG>(clientHeight) };
	//AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);


	////Стиль окна
	//auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
	////Положение окна на экране. В даннос случае окно будет отображено посередине.
	//auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	//auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;
	////Обработчик окна
	//hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
	//	dwStyle,
	//	posX, posY,
	//	windowRect.right - windowRect.left,
	//	windowRect.bottom - windowRect.top,
	//	nullptr, 
	//	nullptr, 
	//	hInstance, 
	//	pWindowContainer); //Param to create window

	if(hWnd == nullptr) {
		//ErrorLogger::Log(GetLastError(),"CreateWindowEX Failed for window: " + applicationName);
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);//Показ окна
	SetForegroundWindow(hWnd);//Поверх других окон
	SetFocus(hWnd);//Установка фокуса (курсора) на это окно

	ShowCursor(true);//Показ курсора

	return true;
}

void Display::RegisterWindowClass() {
	//Блок регистрации окна
	hInstance = GetModuleHandle(nullptr);
	//WNDCLASSEX wc - рассширенный класс окна. необходимо заполнить его до создания (регистрации)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //устанавливает стиль окна, когда оно перерисовывается
	wc.lpfnWndProc = HandleMessageSetup; //указатель на функцию для обработки сообщений из окна                  !!!!!!!!!!!WndProc!!!!!!!!!!!!!
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance; //дескриптор (обработчик) экземплера, содержащего оконную процедуру
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc); //регистрация класса для возможности его использовать
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

HWND Display::GetHWND() const
{
	return this->hWnd;
}

Display::~Display() {
	if(this->hWnd != nullptr)
	{
		UnregisterClass(applicationName, hInstance);
		DestroyWindow(hWnd);
	}
}
