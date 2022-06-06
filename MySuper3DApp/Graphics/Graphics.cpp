#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	this->windowWidth = width;
	this->windowHeight = height;
	this->fpsTimer.Start();

	if (!InitializeDirectX(hwnd))
		return false;

	if (!InitializeShaders())
		return false;
	if (!InitializeScene())
		return false;

	//Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(this->device.Get(), this->deviceContext.Get());
	ImGui::StyleColorsDark();

	return true;
}

void Graphics::RenderFrame()
{
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //цвет задника
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->deviceContext->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	this->deviceContext->IASetInputLayout(this->vertexShader.GetInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->deviceContext->RSSetState(this->rasterizerState.Get());
	this->deviceContext->OMSetDepthStencilState(this->depthStencilState.Get(), 0);
	this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
	this->deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

	UINT offset = 0;

	//Update Constant Buffer
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	constantBuffer.data.mat = world * camera.GetViewMatrix() * camera.GetProjectionMatrix();
	constantBuffer.data.mat = DirectX::XMMatrixTranspose(constantBuffer.data.mat);

	if (!constantBuffer.ApplyChanges())
		return;

	this->deviceContext->VSSetConstantBuffers(0, 1, this->constantBuffer.GetAddressOf());
	
	//SQUARE
	this->deviceContext->PSSetShaderResources(0, 1, this->myTexture.GetAddressOf());
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	this->deviceContext->IASetIndexBuffer(indicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->DrawIndexed(indicesBuffer.BufferSize(), 0, 0);

	//Draw Text
	static int fpsCounter = 0;
	static std::string fpsString = "FPS: 0";
	fpsCounter += 1;
	if(fpsTimer.GetMilisecondsElapsed() > 1000.0) {
		fpsString = "FPS: " + std::to_string(fpsCounter);
		fpsCounter = 0;
		fpsTimer.Restart();
	}
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), StringConverter::StringToWide(fpsString).c_str(), DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteBatch->End();

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//Create ImGui Test Window
	ImGui::Begin("Test");
	//YOUR GUI HERE
	//
	//
	ImGui::End();
	//Assemble Together Draw Data
	ImGui::Render();
	//Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	this->swapchain->Present(0, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd)
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

	swapDesc.BufferDesc.Width = this->windowWidth;
	swapDesc.BufferDesc.Height = this->windowHeight;
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

	//DEPTH BUFFER & STENCIL
	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = this->windowWidth;
	depthStencilDesc.Height = this->windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hres = this->device->CreateTexture2D(&depthStencilDesc, nullptr, this->depthStencilBuffer.GetAddressOf());
	if (FAILED(hres)) //If error occurred
	{
		ErrorLogger::Log(hres, "Failed to create depth stencil buffer.");
		return false;
	}

	hres = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), nullptr, this->depthStencilView.GetAddressOf());
	if (FAILED(hres)) //If error occurred
	{
		ErrorLogger::Log(hres, "Failed to create depth stencil view.");
		return false;
	}

/////////////////////////
//	context->OMSetRenderTargets(1, &rtv, nullptr);
	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthStencilView.Get());
/////////////////////////

	//Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hres = this->device->CreateDepthStencilState(&depthstencildesc, this->depthStencilState.GetAddressOf());
	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create depth stencil state.");
		return false;
	}
	//END DEPTH BUFFER & STENCIL

	//RASTERIZER
	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = this->windowWidth;
	viewport.Height = this->windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	this->deviceContext->RSSetViewports(1, &viewport);
	//END RASTERIZER

	//Create Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	hres = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create rasterizer state.");
		return false;
	}

	spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->deviceContext.Get());
	spriteFont = std::make_unique<DirectX::SpriteFont>(this->device.Get(), L"Data\\Fonts\\calibri_light_16.spritefont");

	//TEXTURING
	//Create sampler description for sampler state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hres = this->device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf()); //Create sampler state
	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create sampler state.");
		return false;
	}

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
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
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
	//Textured Square
	Vertex v[] =
	{
		Vertex(-0.5f,  -0.5f, 0.0f, 0.0f, 1.0f), //Bottom Left	[0] 
		Vertex(-0.5f,   0.5f, 0.0f, 0.0f, 0.0f), //Top Left		[1]
		Vertex(0.5f,   0.5f, 0.0f, 1.0f, 0.0f), //Top Right		[2]
		Vertex(0.5f,  -0.5f, 0.0f, 1.0f, 1.0f), //Bottom Right	[3]
	};

	//Load Vertex Data
	HRESULT hres = this->vertexBuffer.Initialize(this->device.Get(), v, ARRAYSIZE(v));

	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create vertex buffer.");
		return false;
	}

	DWORD indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
		
	//Load Index Data
	hres = this->indicesBuffer.Initialize(this->device.Get(), indices, ARRAYSIZE(indices));

	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create indices buffer.");
		return false;
	}

	//LOAD TEXTURE
	hres = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\chest.png", nullptr, myTexture.GetAddressOf());
	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to create wic texture from file.");
		return false;
	}

	//Initialize Constant Buffer(s)


	hres = this->constantBuffer.Initialize(this->device.Get(), this->deviceContext.Get());
	if (FAILED(hres))
	{
		ErrorLogger::Log(hres, "Failed to initialize constant buffer.");
		return false;
	}

	camera.SetPosition(0.0f, 0.0f, -2.0f);
	camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);

	return true;
}


ID3D11Device& Graphics::GetDevice() {
	return this->device.GetAddressOf();
}
