#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "../GameObject.h"

//using namespace DirectX::SimpleMath;

class Ball : public GameObject {

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

	int pointsCount;
	int* indeces;
	int indecesCount;

#pragma pack(push, 4)
	struct ConstData
	{
		float x;
		float y;
		float dummy0;
		float dummy1;
	};
#pragma pack(pop)

	ConstData constData = { 0,0 };

	float speedY = 0;

public:
	float velocityX = 0.01f;
	float velocityY = 0.0f;
	float ballSpeedMultiplyer = 1;

	Ball(Engine* engine);
	~Ball();


	virtual void Initialize() override;
	virtual void DestroyResources() override;
	virtual void Draw(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Reload() override;
	virtual void Reload(float x, float y);
	virtual ConstData GetConstData();
};