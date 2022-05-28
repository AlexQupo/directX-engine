// MySuper3DApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <WinUser.h>
#include <wrl.h>
#include <iostream>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <chrono>

#include "Engine.h"


#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "d3d11.lib")

//#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib, "d3dcompiler.lib")
//#pragma comment(lib, "dxguid.lib")

//LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
//
//	switch (umessage) {
//
//	case WM_KEYDOWN: {
//
//		std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;
//
//		if (static_cast<unsigned int>(wparam) == 27) PostQuitMessage(0);
//		return 0;
//	}
//
//	default: {
//			return DefWindowProc(hwnd, umessage, wparam, lparam);
//		}
//	}
//}

//--InProcess
//bool MessageHandler(MSG msg) {
//
//	//MSG msg = {};
//	//ZeroMemory(&msg, sizeof(MSG)); // what is it?
//
//	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	if (msg.message == WM_QUIT) {
//		return false;
//	}
//	return true;
//}

int main()
{

#pragma region Window init

	//WNDCLASSEX wc;
	LPCWSTR applicationName = L"My3DApp";
	int screenWidth = 800;
	int screenHeight = 600;
	//HINSTANCE hInstance = GetModuleHandle(nullptr);
	//HWND hWnd;

	Engine engine;
	if(engine.Initialize(applicationName, screenWidth, screenHeight)) {
		while (engine.ProcessMessages() == true) {
			engine.Update();
			engine.RenderFrame();
		}
	}
	

	//INPUT ASSEBLER - completed
	//VERTEX SHADER - completed
	//RASTERIZER - completed
	//PIXEL SHADER - completed
	//OUTPUT MERGER - completed

	//Create our Vertex Buffer - completed
	//Draw - completed





	/*Display display;
	display.Initialize(L"My3DApp", screenHeight, screenWidth);
	while (display.ProcessMessages() == true) {
		
	}*/
	//DisplayWin32(L"My3DApp", screenHeight, screenWidth, hInstance, WndProc, hWnd);

#pragma endregion Window init

/////////////////////////////////////////////////////////////////////////////
///Done
/////////////////////////////////////////////////////////////////////////////
//	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
//
//	DXGI_SWAP_CHAIN_DESC swapDesc = {};
//	swapDesc.BufferCount = 2;
//	swapDesc.BufferDesc.Width = screenWidth;
//	swapDesc.BufferDesc.Height = screenHeight;
//	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
//	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
//	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	swapDesc.OutputWindow = hWnd;
//	swapDesc.Windowed = true;
//	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//	swapDesc.SampleDesc.Count = 1;
//	swapDesc.SampleDesc.Quality = 0;
//
//	Microsoft::WRL::ComPtr<ID3D11Device> device;
//	ID3D11DeviceContext* context;
//	IDXGISwapChain* swapChain;
//
//	auto res = D3D11CreateDeviceAndSwapChain(
//		nullptr,
//		D3D_DRIVER_TYPE_HARDWARE,
//		nullptr,
//		D3D11_CREATE_DEVICE_DEBUG,
//		featureLevel,
//		1,
//		D3D11_SDK_VERSION,
//		&swapDesc,
//		&swapChain,
//		&device,
//		nullptr,
//		&context);
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	if(FAILED(res)) {
//		
//	}
//
//
//	ID3D11Texture2D* backTex;
//	ID3D11RenderTargetView* rtv;
//	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex); //__uuidof(ID3D11Texture2D) IID_ID3D11Texture2D
//	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);
//
//	ID3DBlob* vertexBC = nullptr;
//	ID3DBlob* errorVertexCode = nullptr;
//
//	//3:06:53
//	res = D3DCompileFromFile(L"../Shaders/MyVeryFirstShader.hlsl",
//		nullptr /*macros*/,
//		nullptr /*include*/,
//		"VSMain",
//		"vs_5_0",
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
//		0,
//		&vertexBC,
//		&errorVertexCode);
//
//	if(FAILED(res)) {
//		if(errorVertexCode) {
//			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
//
//			std::cout << compileErrors << std::endl;
//		}
//		else {
//			MessageBox(hWnd, L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
//		}
//
//		return 0;
//	}
//
//	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
//
//	ID3DBlob* pixelBC;
//	ID3DBlob* errorPixelCode;
//
//	res = D3DCompileFromFile(L"../Shaders/MyVeryFirstShader.hlsl", Shader_Macros /*macros*/, nullptr /*include*/, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelBC, &errorPixelCode);
//
//	ID3D11VertexShader* vertexShader;
//	ID3D11PixelShader* pixelShader;
//	device->CreateVertexShader(
//		vertexBC->GetBufferPointer(),
//		vertexBC->GetBufferSize(),
//		nullptr, &vertexShader);
//
//	device->CreatePixelShader(
//		pixelBC->GetBufferPointer(),
//		pixelBC->GetBufferSize(),
//		nullptr, &pixelShader);
//
//	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
//		D3D11_INPUT_ELEMENT_DESC{
//			"POSITION",
//			0,
//			DXGI_FORMAT_R32G32B32A32_FLOAT,
//			0,
//			0,
//			D3D11_INPUT_PER_VERTEX_DATA,
//			0},
//		D3D11_INPUT_ELEMENT_DESC{
//			"COLOR",
//			0,
//			DXGI_FORMAT_R32G32B32A32_FLOAT,
//			0,
//			D3D11_APPEND_ALIGNED_ELEMENT,
//			D3D11_INPUT_PER_VERTEX_DATA,
//			0}
//	};
//
//	ID3D11InputLayout* layout;
//	device->CreateInputLayout(
//		inputElements,
//		2,
//		vertexBC->GetBufferPointer(),
//		vertexBC->GetBufferSize(),
//		&layout);
//
//	DirectX::XMFLOAT4 points[8] = {
//		DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
//		DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
//		DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
//		DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
//	};
//
//	D3D11_BUFFER_DESC vertexBufDesc = {};
//	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
//	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vertexBufDesc.CPUAccessFlags = 0;
//	vertexBufDesc.MiscFlags = 0;
//	vertexBufDesc.StructureByteStride = 0;
//	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);
//
//	D3D11_SUBRESOURCE_DATA vertexData = {};
//	vertexData.pSysMem = points;
//	vertexData.SysMemPitch = 0;
//	vertexData.SysMemSlicePitch = 0;
//
//	ID3D11Buffer* vb;
//	device->CreateBuffer(&vertexBufDesc, &vertexData, &vb);
//
//	int indeces[] = { 0,1,2, 1,0,3 };
//	D3D11_BUFFER_DESC indexBufDesc = {};
//	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
//	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	indexBufDesc.CPUAccessFlags = 0;
//	indexBufDesc.MiscFlags = 0;
//	indexBufDesc.StructureByteStride = 0;
//	indexBufDesc.ByteWidth = sizeof(int) * std::size(indeces);
//
//	D3D11_SUBRESOURCE_DATA indexData = {};
//	indexData.pSysMem = indeces;
//	indexData.SysMemPitch = 0;
//	indexData.SysMemSlicePitch = 0;
//
//	ID3D11Buffer* ib;
//	device->CreateBuffer(&indexBufDesc, &indexData, &ib);
//
//	UINT strides[] = { 32 };
//	UINT offsets[] = { 0 };
//
//	
//
//	CD3D11_RASTERIZER_DESC rastDesc = {};
//	rastDesc.CullMode = D3D11_CULL_NONE;
//	rastDesc.FillMode = D3D11_FILL_SOLID;
//
//	ID3D11RasterizerState* rastState;
//	res = device->CreateRasterizerState(&rastDesc, &rastState);
//
//	context->RSSetState(rastState);
//
//	
//
//	std::chrono::time_point<std::chrono::steady_clock> PrevTime = std::chrono::steady_clock::now();
//	float totalTime = 0;
//	unsigned int frameCount = 0;
//
//
//	MSG msg = {};
//	bool isExitRequested = false;
//	while(!isExitRequested) {
//
//		isExitRequested = !MessageHandler(msg);
//		/*while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//
//		if(msg.message == WM_QUIT) {
//			isExitRequested = true;
//		}*/
//
//		//��� ���������� ����
//
//		context->ClearState();
//		context->RSSetState(rastState);
//
//		context->IASetInputLayout(layout);
//		context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//		context->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
//		context->IASetVertexBuffers(0, 1, &vb, strides, offsets);
//
//		context->VSSetShader(vertexShader, nullptr, 0);
//		context->PSSetShader(pixelShader, nullptr, 0);
//
//
//		D3D11_VIEWPORT viewport = {};
//		viewport.Width = static_cast<float>(screenWidth);
//		viewport.Height = static_cast<float>(screenHeight);
//		viewport.TopLeftX = 0;
//		viewport.TopLeftY = 0;
//		viewport.MinDepth = 0;
//		viewport.MaxDepth = 1.0f;
//
//		context->RSSetViewports(1, &viewport);
//
//		//4.00.59
//
//		//����� fps
//		auto curTime = std::chrono::steady_clock::now();
//		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 1000000.0f;
//		PrevTime = curTime;
//
//		totalTime += deltaTime;
//		frameCount++;
//
//		if(totalTime>1.0f) {
//			float fps = frameCount / totalTime;
//
//			totalTime -= 1.0f;
//
//			WCHAR text[256];
//			swprintf_s(text, TEXT("FPS:%f"), fps);
//			SetWindowText(hWnd, text);
//
//			frameCount = 0;
//		}
//		//����� ������ fps
//
//		context->OMSetRenderTargets(1, &rtv, nullptr);
//
//		float color[] = { totalTime , 0.1f, 0.1f, 1.0f };
//		context->ClearRenderTargetView(rtv, color);
//
//		context->DrawIndexed(6, 0, 0);
//		swapChain->Present(1, 0);
//
//	}
//
//
//    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
