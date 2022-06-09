#pragma once
#include "Graphics/Vertex.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/Shaders.h"
#include <WICTextureLoader.h>

class Engine;

class Shapes {
private:
	ConstantBuffer<CB_VS_vertexshader> constantBuffer;
	IndexBuffer indicesBuffer;
	VertexBuffer<Vertex> vertexBuffer;
	//VertexShader vertexShader;
	PixelShader pixelShader;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	/*Vertex vertices[] = {Vertex(2.0f,0.0f,0.0f,0.0f,0.0f),Vertex(2.0f,0.0f,0.0f,0.0f,0.0f)};
	DWORD indices[] =  nullptr;*/


public:
	bool Initialize(Engine* engine);
	void Update();
	void Destroy();

};