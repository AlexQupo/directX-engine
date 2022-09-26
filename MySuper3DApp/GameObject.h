#pragma once
//���������� ������ Game
class Engine;

//���������� ���� ����������
class GameObject {
public:

	//������� �� ����� Game
	Engine* engine;

	//�����������
	GameObject(Engine* inEngine) {
		engine = inEngine;
	}

	//����������
	virtual ~GameObject() = default;

	//������� �������������
	virtual void Initialize() = 0;

	//������� ��������
	virtual void DestroyResources() = 0;

	//dx ���������
	virtual void Draw(float deltaTime) = 0;

	//������� ������������, ����� ������������ �� ����������
	virtual void Reload() = 0;

	//������� ����������
	virtual void Update(float deltaTime) = 0;
};