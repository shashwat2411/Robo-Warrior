#pragma once
#include "baseobjects.h"
#include "script.h"

#define ENEMY_MAX 18

class SCENE;

//Prefab
class PLAYER : public GAMEOBJECT
{
private:
	int deadCounter;
	bool deathAnimation;
	int afterDeathCounter;

public:
	HitPoints* hp;
	Posture* posture;
	bool dead;

public:

	void Start() override;
	void Update() override;
};
class ENEMY : public GAMEOBJECT
{
public:
	HitPoints* hp;
	Animator* animator;
	Afterimage* afterimage;
	FollowObject* follower;
	SCENE* scene;
	PLAYER* player;

protected:
	bool attack;
	bool calculate;
	bool lockon;

	int attackCounter;
	int waitCounter;
	int lockonCounter;

	int waitLimit;
	D3DXVECTOR3 direction;

public:

	void Start() override {}
	void Update() override {}

	bool GetAttack() { return attack; }
	void SetAttack(bool value) { attack = value; }

	virtual void Attack()
	{
		attack = true;
		calculate = true;
		lockon = true;
	}

	virtual void SetEnemy(D3DXVECTOR3 position) = 0;
};
class DASH_ENEMY : public ENEMY
{
public:
	//Afterimage* afterimage;
	enum
	{
		LOCKON,
		LOCKON_REVERSE,
		ATTACK,
		MOVE,
		SPAWN
	};

public:

	void Start() override;
	void Update() override;

	void SetEnemy(D3DXVECTOR3 position) override;
};
class ZIGZAG_ENEMY : public ENEMY
{
public:
	GAMEOBJECT* body;
	GAMEOBJECT* after;
	enum
	{
		LOCKON,
		LOCKON_REVERSE,
		ATTACK,
		MOVE,
		SPAWN
	};

private:

public:

	void Start() override;
	void Update() override;

	void SetEnemy(D3DXVECTOR3 position) override;
};
class CHARACTER : public GAMEOBJECT
{
public:
	bool pressed;
	bool dash;
	bool dashCooler;
	bool rollstart;
	bool guard;
	bool stance;
	bool guardCooler;
	bool punch;
	bool disable;
	Animator* animator;
	Animator* animatorRoll;
	Animator* rightHand;
	Animator* leftHand;
	int dashCounter;
	int dashCooldown;
	int guardCooldown;

public:
	EMPTYOBJECT* body;
	EMPTYOBJECT* innerbody;

	//EMPTYOBJECT* L_arm1;
	//EMPTYOBJECT* L_arm2;
	//EMPTYOBJECT* L_arm3;
	EMPTYOBJECT* L_joint1;
	EMPTYOBJECT* L_joint2;
	EMPTYOBJECT* L_joint3;
	EMPTYOBJECT* L_hand;
	EMPTYOBJECT* L_fist;
	EMPTYOBJECT* L_arm1_cover;
	EMPTYOBJECT* L_arm2_cover;
	EMPTYOBJECT* L_arm3_cover;

	//EMPTYOBJECT* R_arm1;
	//EMPTYOBJECT* R_arm2;
	//EMPTYOBJECT* R_arm3;
	EMPTYOBJECT* R_joint1;
	EMPTYOBJECT* R_joint2;
	EMPTYOBJECT* R_joint3;
	EMPTYOBJECT* R_hand;
	EMPTYOBJECT* R_fist;
	EMPTYOBJECT* R_arm1_cover;
	EMPTYOBJECT* R_arm2_cover;
	EMPTYOBJECT* R_arm3_cover;

	std::vector<EMPTYOBJECT*> parts;

	enum
	{
		RETRACT = 0,
		EXTEND,
		JUMP,
		GUARD,
		PARRY,
		STUN,
		DEATH
	};

	enum
	{
		ROLL = 0,
		DASH
	};

	enum
	{
		PUNCH_LAUNCH_R,
	};

	enum
	{
		PUNCH_LAUNCH_L,
	};

public:

	void Start() override;
	void Update() override;

};

class EXPLOSION : public BILLBOARD
{
public:

	void Start() override
	{
		Init();
		Billboard* bill = GetComponent<Billboard>();
		bill->SetTextureName("asset\\texture\\explosion.png");
		bill->SetAnimate(true);
		bill->SetElements(4, 4);
	}

	void Update() override
	{

	}
};
class FIRE : public BILLBOARD
{
public:
	Billboard* bill;
	float counter;

public:

	void Start() override
	{
		Init();
		bill = GetComponent<Billboard>();
		bill->SetTextureName("asset\\texture\\fire.png");
		bill->SetAnimate(true);
		bill->SetElements(3, 2);
	}

	void Update() override
	{
		counter += 0.4f;
		bill->Count = (int)counter;
		if (bill->Count >= 6)
		{
			bill->Count = 0;
			counter = 0.0f;
		}
	}
};
class SPARK : public BILLBOARD
{
public:
	Billboard* bill;
	float counter;

public:

	void Start() override
	{
		Init();
		bill = GetComponent<Billboard>();
		bill->SetTextureName("asset\\texture\\sparks.png");
		bill->SetAnimate(true);
		bill->SetElements(3, 2);
		counter = 0.0f;

		transform->Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
		use = false;
	}

	void Update() override
	{
		if (use == true)
		{
			counter += 0.2f;
			bill->Count = (int)counter;
			if (bill->Count >= 6)
			{
				bill->Count = 0;
				use = false;
			}
		}
	}

	virtual void Burst(D3DXVECTOR3 pos, bool flipper = false)
	{
		if (this != nullptr)
		{
			use = true;
			transform->Position = pos;
			bill->flip = flipper;
			bill->Count = 0;
			counter = 0.0f;
		}
	}
};
class ATTACKEFFECT : public SPARK
{
public:

public:

	void Start() override;
	void Update() override;
	void Burst(D3DXVECTOR3 pos, bool flipper = false) override;

};
class DAMAGEEFFECT : public SPARK
{
public:

public:

	void Start() override
	{
		Init();
		bill = GetComponent<Billboard>();
		bill->SetTextureName("asset\\texture\\damage.png");
		bill->SetAnimate(true);
		bill->SetElements(3, 3);
		counter = 0.0f;
		transform->Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

		use = false;
	}

	void Update() override
	{
		if (use == true)
		{
			counter += 0.5f;
			bill->Count = (int)counter;
			if (bill->Count >= 9)
			{
				bill->Count = 0;
				use = false;
			}
		}
	}

};
class DEATHEFFECT : public SPARK
{
public:

public:

	void Start() override
	{
		Init();
		bill = GetComponent<Billboard>();
		bill->SetTextureName("asset\\texture\\explosion2.png");
		bill->SetAnimate(true);
		bill->SetElements(4, 2);
		counter = 0.0f;
		transform->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	}

	void Update() override
	{
		if (use == true)
		{
			counter += 0.2f;
			bill->Count = (int)counter;
			if (bill->Count >= 8)
			{
				bill->Count = 0;
				Destroy();
			}
		}
	}

};

class ENEMYDESTROY_EFFECT : public PARTICLESYSTEM
{
public:

	void Start() override
	{
		Init();

		particleSystem->SetTexture("asset\\texture\\gear3.png");
		particleSystem->burst = true;
		particleSystem->loop = false;
		particleSystem->SetLife(20);
		particleSystem->SetSpeed(0.5f);
		particleSystem->rotateRandom = true;
		particleSystem->rotationSpeed = 70.0f;
		//particleSystem->SetParticleCount(20);
		
		SetUse(false);
		transform->Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	}

	void Update() override {}
};