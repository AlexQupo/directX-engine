//#include "GameObject.h"
//
//bool GameObject::Initialize() {
//
//	//—юда вертекс
//
//	//Load Vertex Data
//	HRESULT hres = this->vertexBuffer.Initialize(this->device.Get(), v, ARRAYSIZE(v));
//
//	if (FAILED(hres))
//	{
//		ErrorLogger::Log(hres, "Failed to create vertex buffer.");
//		return false;
//	}
//
//	//—юда индекс
//
//	//Load Index Data
//	hres = this->indicesBuffer.Initialize(this->device.Get(), indices, 3/*ARRAYSIZE(indices)*/);
//
//	if (FAILED(hres))
//	{
//		ErrorLogger::Log(hres, "Failed to create indices buffer.");
//		return false;
//	}
//
//	//LOAD TEXTURE
//	hres = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\chest.png", nullptr, myTexture.GetAddressOf());
//	if (FAILED(hres))
//	{
//		ErrorLogger::Log(hres, "Failed to create wic texture from file.");
//		return false;
//	}
//
//	//Initialize Constant Buffer(s)
//
//
//	hres = this->constantBuffer.Initialize(this->device.Get(), this->deviceContext.Get());
//	if (FAILED(hres))
//	{
//		ErrorLogger::Log(hres, "Failed to initialize constant buffer.");
//		return false;
//	}
//
//	return true;
//}
//
//bool GameObject::AddComponent(Vertex v[], DWORD indices[]) {
//	for (auto vert : v) {
//		
//	}
//}
//
