#include "DisplayWin32.h"

bool DisplayWin32::Initialize(LPCWSTR appName, int Height, int Width, HINSTANCE hInst, WNDPROC MessageHandler, HWND &handlerWindow)
	: applicationName(appName), clientHeight(Height), clientWidth(Width), hInstance(hInst), WndProc(MessageHandler), hWnd(handlerWindow) {

	//Блок регистрации окна

	//WNDCLASSEX wc - рассширенный класс окна. необходимо заполнить его до создания (регистрации)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //устанавливает стиль окна, когда оно перерисовывается
	wc.lpfnWndProc = WndProc; //указатель на функцию для обработки сообщений из окна
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

	//Конец блока

	RECT windowRect = { 0,0,static_cast<LONG>(clientWidth), static_cast<LONG>(clientHeight) };
	AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);

	//Стиль окна
	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	//Положение окна на экране. В даннос случае окно будет отображено посередине.
	auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;

	//Обработчик окна
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);//Показ окна
	SetForegroundWindow(hWnd);//Поверх других окон
	SetFocus(hWnd);//Установка фокуса (курсора) на это окно

	ShowCursor(true);//Показ курсора

	return true;
}

DisplayWin32::~DisplayWin32() {
	if(this->hWnd !=NULL)
	{
		UnregisterClass(this->applicationName, this->hInstance);
		DestroyWindow(hWnd);
	}
}
