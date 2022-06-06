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
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indicesBuffer;

	VertexShader vertexShader;
	PixelShader pixelShader;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

public:
	bool Initialize(Engine* engine);
	void Update();
	void Destroy();

};