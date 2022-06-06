#include "Shapes.h"

#include "Engine.h"

bool Shapes::Initialize(Engine* engine) {

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
	engine->
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



}

void Shapes::Update() {

}

