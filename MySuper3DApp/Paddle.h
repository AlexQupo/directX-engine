#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "../GameObject.h"

//using namespace DirectX::SimpleMath;

enum PaddleLocation {
	left = 0,
	right = 1
};

class Engine;

class Paddle : public GameObject {

#pragma pack(push, 4)
	struct ConstData
	{
		float x;
		float y;
		float dummy0;
		float dummy1;
	};
#pragma pack(pop)

	ID3D11InputLayout* layout = nullptr;

	ID3D11PixelShader* pixelShader = nullptr;
	ID3DBlob* pixelShaderByteCode = nullptr;

	ID3D11VertexShader* vertexShader = nullptr;
	ID3DBlob* vertexShaderByteCode = nullptr;

	//Vector4* points = nullptr;
	DirectX::XMFLOAT4 points;

	ID3D11RasterizerState* rastState = nullptr;
	ID3D11Buffer* indecesBuffer = nullptr;

	ID3D11Buffer* verticies = nullptr;
	ID3D11Buffer* constBuffer = nullptr;

	// оличество точек, индексы и количество индексов
	int pointsCount;
	int* indeces;
	int indecesCount;

	PaddleLocation compLocation;

	ConstData constData = { 0,0 };

public:
	Paddle(Engine* engine, PaddleLocation location);
	~Paddle();

	//void SetX(float X);

	virtual void Initialize() override;
	virtual void DestroyResources() override;
	virtual void Draw(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual ConstData GetConstData();
	virtual void Reload() override {};
};