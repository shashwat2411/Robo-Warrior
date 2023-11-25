#pragma once
#include "collision.h"
#include "prefab.h"
#include "animations.h"

#define GAME_OBJECT_MAX 64 

enum LAYER
{
	CAMERA_LAYER = 0,
	GAMEOBJECT_LAYER,
	BILLBOARD_LAYER,
	SHADOW_LAYER,
	COLLIDER_LAYER,
	SPRITE_LAYER,
	FADE_LAYER,
	MAX_LAYER
};

class SCENE
{
protected :
	std::array<std::list<GAMEOBJECT*>,MAX_LAYER> GameObjects;
	COLLISION Collision;
	bool End;
	bool paused;

	CAMERA* MainCamera;
	FADE* Fade;
	SKYDOME* skyDome;

public:
	PLAYER* player;
	
	void SetEnd() { End = true; }

	std::list<GAMEOBJECT*> GetGameObjectList(LAYER layer) { return GameObjects[layer]; }
	CAMERA* GetCamera() { return (CAMERA*)MainCamera; }
	PLAYER* GetPlayer() { return player; }
	bool GetPaused() { return paused; }

	void InitBefore();
	virtual void Init() {}
	void Uninit();
	void UpdateBefore();
	virtual void Update() {}
	void Draw();

	//ADD
	template <typename T>
	T* AddGameObject(LAYER layer = GAMEOBJECT_LAYER)
	{
		T* gameObject = new T();
		GameObjects[layer].push_back(gameObject);
		gameObject->Start();

		return gameObject;
	}


	//REMOVE
	template<typename T>
	void RemoveGameObject(LAYER layer)
	{
		T* buff = FindGameObject<T>();
		if (buff != nullptr)
		{
			buff->UnInitialize();
			GameObjects[layer].remove(buff);
			delete buff;
		}
	}

	//FIND
	template<typename T>
	T* FindGameObject()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (auto com : GameObjects[i])
			{
				T* buff = dynamic_cast<T*>(com);
				if (buff != nullptr)
				{
					return buff;
				}
			}
		}
		return nullptr;
	}

	//FIND MULTIPLE
	template<typename T>
	std::vector<T*> FindGameObjects()
	{
		std::vector<T*> objects;
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (auto obj : GameObjects[i])
			{
				T* buff = dynamic_cast<T*>(obj);
				if (buff != nullptr)
				{
					objects.push_back((T*)buff);
				}
			}
		}
		return objects;
	}
};