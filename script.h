#pragma once
#include "component.h"
#include "modelReader.h"

#define COLLIDE_COUNTDOWN 5

class ENEMY;
class PARTICLESYSTEM;

//Script
class PlayerMovement : public Script
{
public:
	D3DXVECTOR3 rotationDirection;
	bool move;

public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

};
class PlayerAttack :public Script
{
public:
	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void OnCollisionEnter(GAMEOBJECT* obj) override;
};
class EnemyScript : public Script
{
private:
	D3DXVECTOR3 Position;
	PARTICLESYSTEM* system;

public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;
};
class EnemySpawn : public Script
{
private:
	int spawnCounter;
	int spawnSpeed;
	GAMEOBJECT* spawnObject;

public:

	void Start() override;
	void End() override {}
	void Update() override;
	void Draw() override {}
};
class EnemyCollision : public Script
{
public:

	void Start() override;
	void End() override;
	void Update() override {}
	void Draw() override {}

	void OnCollisionEnter(GAMEOBJECT* obj) override;
};
class HitPoints : public Script
{
private:
	float hp;
	bool invincible;
	int invincibilityCounter;
	GAMEOBJECT* object;
	bool disable;
	bool noDamage;
	float* barController;

public:

	void SetBarController(float* value) { barController = value; }
	void SetHP(int value) { hp = value; }
	void SetDisable(bool value) { disable = value; }
	void SetObject(GAMEOBJECT* value) { object = value; }

	int GetHP() { return hp; }
	bool GetNoDamage() { return noDamage; }
	bool GetInvincible() { return invincible; }

	void Start() override
	{
		hp = 5.0f;
		invincible = false;
		invincibilityCounter = 0;
		object = nullptr;
		disable = false;
		noDamage = false;
		barController = nullptr;
	}
	void End() override {}
	void Update() override
	{
		if (barController != nullptr) { *barController = hp; }
		//if (hp <= 0.0f && noDamage == false)
		//{
		//	if (object != nullptr)
		//	{
		//		if (disable == true) { object->SetUse(false); }
		//		else { object->Destroy(); }
		//	}
		//	else
		//	{
		//		if (disable == true) { gameObject->SetUse(false); }
		//		else { gameObject->Destroy(); }
		//	}
		//}

		if (invincible == true)
		{
			if (invincibilityCounter < COLLIDE_COUNTDOWN) { invincibilityCounter++; }
			else { invincibilityCounter = 0; invincible = false; }
		}

		if (noDamage == true) { Heal(2.0f); }
	}
	void Draw() override {}

	void Invincible() { noDamage = true; invincible = true; }
	void Vulnerable() { noDamage = false; invincible = false; }
	bool Damage(float damage = 1.0f) 
	{ 
		if (invincible == false) 
		{ 
			if ((hp - damage) > 0.0f) { hp -= damage; }
			else { hp = 0.0f; }
			invincible = true;
			return true;
		} 
		return false;
	}

	void Heal(float value = 1.0f) 
	{ 
		if ((hp + value) < 100.0f) { hp += value; } 
		else { hp = 100.0f; }
	}
};
class EnemyBrain : public Script
{
private:
	std::vector<ENEMY*> enemies;
	int counter;
	bool initiateAttack;
	bool startCounter;

public:

	void Start() override;
	void End() override {}
	void Update() override;
	void Draw() override{}
};
class Posture : public Script
{
private:
	float posture;
	float maxPosture;

	bool invincible;
	int invincibilityCounter;
	bool noDamage;
	float* barController;

public:

	void SetBarController(float* value) { barController = value; }
	void SetPosture(int value) { posture = value; }
	float GetPosture() { return posture; }

	void Start() override;
	void End() override {}
	void Update() override;
	void Draw() override {}

	bool Damage(float damage = 5.0f) 
	{ 
		if (invincible == false) 
		{ 
			posture += damage; 
			invincible = true; 
			return true;
		} 
		return false;
	}

	void Invincible()
	{
		noDamage = true; 
		invincible = true;
	}

	void Recover(float value = 1.0f)
	{
		if ((posture - value) > 0.0f) { posture -= value; }
		else { posture = 0.0f; }
	}

};