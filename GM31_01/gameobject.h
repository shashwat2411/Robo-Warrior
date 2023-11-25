#pragma once
#include "main.h"
#include "renderer.h"
#include "model.h"
#include <list>
#include <vector>
#include <array>

#define MAX_AFTERIMAGES 1

class Component;
class Transform;
class Rigidbody;
class Shadow;

class GAMEOBJECT
{
protected:
	D3DXMATRIX WorldMatrix[MAX_AFTERIMAGES];
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX RotationMatrix; 
	D3DXMATRIX TransformMatrix;

	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	MATERIAL Material;

	float defaultY = 1.01f;

	bool collide = false;

	bool destroy = false;
	bool use = true;

	bool Depth = true;
	int RingCounter = 0;
	bool faceInDirection = false;
	bool billboard = false;
	bool ignorePause = false;

	bool freezeX = false;
	bool freezeY = false;
	bool freezeZ = false;

	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;
	ID3D11InputLayout* VertexLayout = nullptr;

	std::list<Component*> ComponentList;

	char tag[64];

public:
	Transform*	transform;
	Rigidbody*	rigidbody;
	Shadow*		shadow;
	GAMEOBJECT* Parent;
	std::vector<GAMEOBJECT*>Children;

public:
	//Only Getter Functions
	ID3D11VertexShader* GetVertexShader() { return VertexShader; }
	ID3D11PixelShader* GetPixelShader() { return PixelShader; }
	ID3D11InputLayout* GetVertexLayout() { return VertexLayout; }
	D3DXMATRIX GetWorldMatrix() { return WorldMatrix[RingCounter]; }
	D3DXMATRIX GetWorldMatrix(int index) { return WorldMatrix[index]; }
	D3DXMATRIX GetScaleMatrix() { return ScaleMatrix; }
	D3DXMATRIX GetRotationMatrix() { return RotationMatrix; }
	D3DXMATRIX GetTransformMatrix() { return TransformMatrix; }
	MATERIAL GetMaterial() { return Material; }

	void Destroy(bool value = true);
	void SetWorldMatrix(D3DXMATRIX value, int index) { WorldMatrix[index] = value; }
	void SetScaleMatrix(D3DXMATRIX value) { ScaleMatrix = value; }
	void SetRotationMatrix(D3DXMATRIX value) { RotationMatrix = value; }
	void SetTransformMatrix(D3DXMATRIX value) { TransformMatrix = value; }
	void SetMaterial(const MATERIAL* material) { Material = *material; }
	GAMEOBJECT* SetParent(GAMEOBJECT* parent)
	{
		Parent = parent;
		Parent->Children.push_back(this);
		return this;
	}

	//Getter
	D3DXCOLOR	GetColor() { return Color; }
	float GetDefaultY() { return defaultY; }
	int GetRingCounter() { return RingCounter; }
	bool GetFaceInDirection() { return faceInDirection; }
	bool GetBillboard() { return billboard; }
	bool GetUse() { return use; }
	char* GetTag() { return tag; }
	bool GetIgnorePause() { return ignorePause; }
	bool GetFreezeY() { return freezeY; }

	//Setter
	void SetColor(D3DXCOLOR color) { Color = color; }
	void SetDepth(bool value) { Depth = value; }
	void SetFaceInDirection(bool value) { faceInDirection = value; }
	void SetBillboard(bool value) { billboard = value; }
	void SetRingCounter(int value) { RingCounter = value; }
	void SetUse(bool value) { use = value; }


	//Functions
	void Initialize();
	void UnInitialize();
	void Draw();
	bool Remove();

	//Pure Virtual Functions
	virtual void Init() { Initialize(); }
	virtual void Start() = 0;
	virtual void Update() = 0;

	//Utility Functions
	float Magnitude(D3DXVECTOR3 value)
	{
		float x = value.x;
		float y = value.y;
		float z = value.z;

		float mag = sqrtf(x * x + y * y + z * z);
		return mag;
	}
	void FaceTowards(GAMEOBJECT* object);
	void FaceTowards(D3DXVECTOR3 value);
	void FaceTowardsXYZ(GAMEOBJECT* object);
	float FaceInDirection();
	D3DXMATRIX FaceInDirectionXYZ();
	D3DXVECTOR3 GetForwardDirection();
	D3DXVECTOR3 GetRightDirection();
	float DistanceFrom(GAMEOBJECT* from);
	float DistanceFromWithY0(GAMEOBJECT* from);

	//Component Functions
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
			{
				return buff;
			}
		}
		return nullptr;
	}

	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->gameObject = this;
		T* temp = nullptr;
		temp = GetComponent<T>();
		buff->Start();
		if (temp == nullptr)
		{
			ComponentList.push_back(buff);
		}
		else
		{
			if (temp->GetMultipleSet() == true)
			{
				ComponentList.push_back(buff);
			}
		}
		return buff;
	}

	template<class T>
	void RemoveComponent()
	{
		T* buff = GetComponent<T>();
		if (buff != nullptr)
		{
			buff->End();
			ComponentList.remove(buff);
			delete buff;
		}
	}

	template<class T>
	T* GetComponentInChildren()
	{
		for (auto child : Children)
		{
			for (auto com : child->ComponentList)
			{
				T* buff = dynamic_cast<T*>(com);
				if (buff != nullptr)
				{
					return buff;
				}
			}
		}
	}

	template<typename T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> objects;
		for (auto obj : ComponentList)
		{
			T* buff = dynamic_cast<T*>(obj);
			if (buff != nullptr)
			{
				objects.push_back((T*)buff);
			}
		}
		return objects;
	}
};