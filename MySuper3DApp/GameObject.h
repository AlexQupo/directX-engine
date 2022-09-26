#pragma once
//Объявление класса Game
class Engine;

//Объявление гейм компонента
class GameObject {
public:

	//Поинтер на класс Game
	Engine* engine;

	//Конструктор
	GameObject(Engine* inEngine) {
		engine = inEngine;
	}

	//Деструктор
	virtual ~GameObject() = default;

	//Функция инициализации
	virtual void Initialize() = 0;

	//Очистка ресурсов
	virtual void DestroyResources() = 0;

	//dx отрисовка
	virtual void Draw(float deltaTime) = 0;

	//Функция перезагрузки, потом оверрайдится на компоненте
	virtual void Reload() = 0;

	//Функция обновления
	virtual void Update(float deltaTime) = 0;
};