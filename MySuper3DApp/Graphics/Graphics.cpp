#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!InitializeDirectX(hwnd, width, height))
		return false;

	if (!InitializeShaders())
		return false;
	if (!InitializeScene())
		return false;

	return true;
}

void Graphics::RenderFrame()
{
	float bgcolor[] = { 0.0f, 0.0f, 1.0f, 1.0f }; //цвет задника
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);

	this->deviceContext->IASetInputLayout(this->vertexShader.GetInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);


	this->deviceContext->Draw(3, 0);

	this->swapchain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height)
{
	std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

	if (adapters.size() < 1)
	{
		ErrorLogger::Log("No IDXGI Adapters found.");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

//	DXGI_SWAP_CHAIN_DESC swapDesc = {};
//	swapDesc.BufferCount = 2;
//	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60; //только если полный экран и вертикальная синхра.
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapDesc.SampleDesc.Count = 1; 
	swapDesc.SampleDesc.Quality = 0;

	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;//двойная буферизация. для тройной нужно поставить 2
	swapDesc.OutputWindow = hwnd;
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //переключение между оконным и полноэкранным режимом и изменение размера окна

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	HRESULT hres;
	hres = D3D11CreateDeviceAndSwapChain(
		adapters[0].pAdapter, //IDXGI Adapter
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr, //FOR SOFTWARE DRIVER TYPE
		D3D11_CREATE_DEVICE_DEBUG, //FLAGS FOR RUNTIME LAYERS
		featureLevel, //FEATURE LEVELS ARRAY
		1, //# OF FEATURE LEVELS IN ARRAY
		D3D11_SDK_VERSION,
		&swapDesc, //Swapchain description
		this->swapchain.GetAddressOf(), //Swapchain Address
		this->device.GetAddressOf(), //Device Address
		nullptr, //Supported feature level
		this->deviceContext.GetAddressOf()); //Device Context Address

//		auto res = D3D11CreateDeviceAndSwapChain(
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


	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create device and swapchain.");
		return false;
	}

//	ID3D11Texture2D* backTex;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
//	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex); //__uuidof(ID3D11Texture2D) IID_ID3D11Texture2D
	hres = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hres)) //If error occurred
	{
		ErrorLogger::Log(hres, "GetBuffer Failed.");
		return false;
	}

//	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);
	hres = this->device->CreateRenderTargetView(backBuffer.Get(), nullptr, this->renderTargetView.GetAddressOf());
	if (FAILED(hres)) //If error occurred
	{
		ErrorLogger::Log(hres, "Failed to create render target view.");
		return false;
	}

//	context->OMSetRenderTargets(1, &rtv, nullptr);
	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), nullptr);

	//RASTERIZER
	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;

	//Set the Viewport
	this->deviceContext->RSSetViewports(1, &viewport);
	//END RASTERIZER

	return true;
}

bool Graphics::InitializeShaders() //INPUT ASSEBLER
{
	//VERTEX SHADER
	std::wstring shaderfolder = L"";
#pragma region DetermineShaderPath
	if(IsDebuggerPresent() == TRUE) {
#ifdef _DEBUG
	#ifdef _WIN64
			shaderfolder = L"..\\x64\\Debug\\";
	#else
			shaderfolder = L"..\\Debug\\";
	#endif
	#else
	#ifdef _WIN64
			shaderfolder = L"..\\x64\\Release\\";
	#else
			shaderfolder = L"..\\Release\\";
	#endif
#endif
	}
#pragma endregion DetermineShaderPath

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0,
			0,
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexShader.Initialize(this->device, shaderfolder + L"vertexshader.cso", layout, numElements))
		return false;

	if (!pixelShader.Initialize(this->device, shaderfolder + L"pixelshader.cso"))
		return false;
	
	return true;
}

bool Graphics::InitializeScene()
{
	Vertex v[] =
	{
		Vertex(0.0f, -0.1f), //Center Point
		Vertex(-0.1f, 0.0f), //Left Point
		Vertex(0.1f, 0.0f), //Right Point
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;

	HRESULT hr = this->device->CreateBuffer(
		&vertexBufferDesc, 
		&vertexBufferData, 
		this->vertexBuffer.GetAddressOf()
	);

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create vertex buffer.");
		return false;
	}

	return true;
}
