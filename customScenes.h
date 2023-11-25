#pragma once
#include "scene.h"
#include "manager.h"
#include "soundReader.h"

class EMPTY_SCENE : public SCENE
{
public:

	void Init() override {}
	void Update() override {}
};
class TITLE_SCENE : public SCENE
{
public:

	void Init() override;
	void Update() override;
};
class GAME_SCENE : public SCENE
{
public:
	//std::vector<DASH_ENEMY*> dashEnemies;
	//std::vector<ZIGZAG_ENEMY*> zigzagEnemies;
	std::vector<ENEMYDESTROY_EFFECT*> enemyDestroyEffect;
	std::vector<SPARK*> parryEffect;
	std::vector<ATTACKEFFECT*> attackEffect;
	std::vector<DAMAGEEFFECT*> damageEffect;
	NUMBER* score;

	bool tutorial;

	BAR* postureBar;
	IMAGE* postureBarBackground;
	IMAGE* postureBarBackground2;
	BAR* hpBar;
	IMAGE* hpBarBackground;
	CHARACTER* playerModel;

	//TEXT
	IMAGE* pauseText[4];

public:

	void Init() override;
	void Update() override;

	virtual void Starter() {}

	NUMBER* GetScore() { return score; }

	ENEMYDESTROY_EFFECT* GetEnemyDestroyEffect()
	{
		for (auto enemyDestroy : enemyDestroyEffect)
		{
			if (enemyDestroy->GetUse() == false)
			{
				return enemyDestroy;
			}
		}
		return nullptr;
	}

	SPARK* GetParryEffect()
	{
		for (auto parry : parryEffect)
		{
			if (parry->GetUse() == false)
			{
				return parry;
			}
		}
		return nullptr;
	}

	ATTACKEFFECT* GetAttackEffect()
	{
		for (auto attack : attackEffect)
		{
			if (attack->GetUse() == false)
			{
				return attack;
			}
		}
		return nullptr;
	}

	DAMAGEEFFECT* GetDamageEffect()
	{
		for (auto damage : damageEffect)
		{
			if (damage->GetUse() == false)
			{
				return damage;
			}
		}
		return nullptr;
	}

};
class TUTORIAL_SCENE : public GAME_SCENE
{
public:
	
	void Starter() override;

};
class RESULT_SCENE : public SCENE
{
private:
	NUMBER* score;
	int finalScore;
	int wait;

public:

	void Init() override;
	void Update() override;
};
class WORKSPACE_SCENE : public SCENE
{
private:
	PARTICLESYSTEM* system;

public:

	void Init() override;
	void Update() override;
};