#pragma once
#include "gameobject.h"
#include "component.h"

class EMPTYOBJECT : public GAMEOBJECT
{
private:

public:

	void Start() override
	{
		Init();
	}

	void Update() override
	{

	}
};
class SOUND : public GAMEOBJECT
{
public:
	Audio* audio;

public:

	void Start() override 
	{ 
		Init(); 
		audio = AddComponent<Audio>();
		ignorePause = true;
	}
	void Update() override 
	{
		if (audio != nullptr)
		{
			if (audio->IsPlaying() == false)
			{
				Destroy(true);
			}
		}
	}
};
class CYLINDER : public GAMEOBJECT
{
private:

public:
	
	void Start() override
	{
		Init();
		AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\cylinder.obj");
	}

	void Update() override
	{

	}
};
class CUBE : public GAMEOBJECT
{
private:

public:

	void Start() override
	{
		Init();
		AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\box.obj");
	}

	void Update() override
	{

	}
};
class CAMERA : public GAMEOBJECT
{
public:
	Camera* camera;

public:

	void Init() override 
	{ 
		Initialize(); 

		camera = AddComponent<ThirdPersonCamera>();
	}
	void Start() override { Init(); }
	void Update() override {}
};
class BILLBOARD : public GAMEOBJECT
{
protected:

public:
	void Init() override
	{
		Initialize();
		Depth = true;

		transform->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		transform->Position.y = 1.0f;

		this->AddComponent<Billboard>()->SetTextureName("asset\\texture\\Box.png");

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&PixelShader, "shader\\unlitTexturePS.cso");
	}


	void Start() override { Init(); }
	void Update() override {}


};
class PLANE :public GAMEOBJECT
{
public:

	void Init() override
	{
		Initialize();
		Depth = true;

		transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		AddComponent<Plane>()->SetTextureName("asset\\texture\\home2.png");
	}

	void Start() override { Init(); }
	void Update() override
	{

	}

};
class IMAGE :public GAMEOBJECT
{
public:
	Sprite* sprite;

public:
	void Init() override
	{
		Initialize();

		sprite = AddComponent<Sprite>();
		sprite->SetTexture("asset\\texture\\home2.png");

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout,
			"shader\\unlitTextureVS.cso");

		Renderer::CreatePixelShader(&PixelShader,
			"shader\\unlitTexturePS.cso");

		ignorePause = true;
	}

	void Start() override { Init(); }
	void Update() override
	{
		//GetComponent<Transform>()->Position.x += 0.5f;
		//GetComponent<Transform>()->Rotation.z += 0.5f;
	}

};
class DIGIT : public GAMEOBJECT
{
public:

	void Init() override
	{
		Initialize();

		this->AddComponent<Sprite>()->SetTexture("asset\\texture\\number.png");

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout,
			"shader\\unlitTextureVS.cso");

		Renderer::CreatePixelShader(&PixelShader,
			"shader\\unlitTexturePS.cso");

	}
	void Start() override { Init(); }
	void Update() override {}
};
class NUMBER : public GAMEOBJECT
{
private:
	int number;

public:

	void Init() override
	{
		Initialize();

		this->AddComponent<Number>();

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout,
			"shader\\unlitTextureVS.cso");

		Renderer::CreatePixelShader(&PixelShader,
			"shader\\unlitTexturePS.cso");

		number = 0;
	}
	void Start() override { Init(); }
	void Update() override
	{
		GetComponent<Number>()->SetNumber(number);
		GetComponent<Number>()->SetNumberColor(GetColor());
	}

	void Increment() { number++; }
	void Increment(int value) { number += value; }
	void SetNumber(int value) { number = value; }
	void SetDigits(int value) { GetComponent<Number>()->SetDigits(value); }

	int GetNumber(){return number;}
};
class PARTICLESYSTEM :public GAMEOBJECT
{
public:
	ParticleSystem* particleSystem;

public:
	void Init() override
	{
		Initialize();

		particleSystem = AddComponent<ParticleSystem>();
	}

	void Start() override { Init(); }
	void Update() override {}

};
class PARTICLE : public BILLBOARD
{
public:
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 rotationDirection;
	int life;
	int setLife;
	int counter;
	float speed;
	Billboard* image;

	void Init() override
	{
		Initialize();
		Depth = true;

		velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotationDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		life = setLife = 0;
		transform->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		transform->Position.y = 0.0f;
		speed = 0.1f;

		image = AddComponent<Billboard>();
		image->SetTextureName("asset\\texture\\Box.png");

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&PixelShader, "shader\\unlitTexturePS.cso");
	}


	void Start() override { Init(); }
	void Update() override {}

	void ReInitialize()
	{
		D3DXVECTOR3 direction;
		transform->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		direction.x = (float)(rand() % 10);
		direction.y = (float)(rand() % 10);
		direction.z = (float)(rand() % 10);
		int dirx = rand() % 2;
		int diry = rand() % 2;
		int dirz = rand() % 2;
		if (dirx == 1) { direction.x *= -1.0f; }
		if (diry == 1) { direction.y *= -1.0f; }
		if (dirz == 1) { direction.z *= -1.0f; }
		D3DXVec3Normalize(&direction, &direction);
		velocity = direction * speed;
		life = rand() % 61;
	}
};
class FADE : public GAMEOBJECT
{
private:
	Sprite* image;
	float alpha;
	bool fadeIn;
	bool fadeOut;
	float speed;

public:

	void Init() override;
	void Start() override;
	void Update() override;

	bool FadeOut();
	bool GetFadeIn() { return fadeIn; }

	void SetFadeIn(bool value = true) { fadeIn = value; }
};
class SKYDOME : public GAMEOBJECT
{
public:

	void Init() override
	{
		Initialize();
	}
	void Start() override;
	void Update() override;
};
class SHADOW :public GAMEOBJECT
{
public:
	Plane* polygon;

	void Init() override
	{
		Initialize();
		Depth = true;

		transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		
		polygon = AddComponent<Plane>();
		polygon->SetTextureName("asset\\texture\\shadow.png");
		polygon->Size = D3DXVECTOR2(1.0f, 1.0f);

		use = false;
	}

	void Start() override { Init(); }
	void Update() override
	{

	}

};
class BAR :public GAMEOBJECT
{
public:
	enum BAR_TYPE
	{
		RIGHT,
		LEFT,
		MIDDLE
	};

public:
	Sprite* sprite;
	float amount;
	float maxAmount;
	BAR_TYPE type;

public:
	void Init() override
	{
		Initialize();

		amount = 0.0f;
		maxAmount = 100.0f;

		transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
		transform->Scale = D3DXVECTOR3(1.5f, 0.15f, 0.5f);

		sprite = AddComponent<Sprite>();
		sprite->SetTexture("asset\\texture\\Box.png");

		SetBarType();

		Renderer::CreateVertexShader(&VertexShader, &VertexLayout,
			"shader\\unlitTextureVS.cso");

		Renderer::CreatePixelShader(&PixelShader,
			"shader\\unlitTexturePS.cso");

	}

	void Start() override { Init(); }
	void Update() override
	{
		if (Input::GetKeyPress('Q')) 
		{ 
			Amount(0.5f); 
		}
		if (Input::GetKeyPress('E')) { Amount(-0.5f); }

		if (type == RIGHT)
		{
			sprite->barOffsetRight = ((maxAmount - amount) / maxAmount) * -(sprite->GetSize().x * transform->Scale.x * 2.0f);
		}
		else if (type == LEFT)
		{
			sprite->barOffsetLeft = ((maxAmount - amount) / maxAmount) * (sprite->GetSize().x * transform->Scale.x * 2.0f);
		}
		else if (type == MIDDLE)
		{
			sprite->barOffsetRight = ((maxAmount - amount) / maxAmount) * -(sprite->GetSize().x * transform->Scale.x);
			sprite->barOffsetLeft = ((maxAmount - amount) / maxAmount) * (sprite->GetSize().x * transform->Scale.x);
		}

#ifdef DEBUG	// デバッグ情報を表示する
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], " | Amount : %.2f", amount);
		//sprintf(&str[strlen(str)], " | barOffsetRight : %.2f", sprite->barOffsetRight);
		//sprintf(&str[strlen(str)], " | barOffsetLeft : %.2f", sprite->barOffsetLeft);
#endif
	}

	void SetBarType(BAR_TYPE value = RIGHT)
	{
		type = value;

		if (type == RIGHT) 
		{
			sprite->barOffsetRight = -(sprite->GetSize().x * transform->Scale.x) * 2.0f;
		}
		else if (type == LEFT)
		{
			sprite->barOffsetLeft = (sprite->GetSize().x * transform->Scale.x) * 2.0f;
		}
		else if (type == MIDDLE)
		{
			sprite->barOffsetRight = -(sprite->GetSize().x * transform->Scale.x);
			sprite->barOffsetLeft = (sprite->GetSize().x * transform->Scale.x);
		}
	}

	void Amount(float value)
	{
		if (value >= 0.0f)
		{
			if ((amount + value) <= maxAmount) { amount += value; }
			else { amount = maxAmount; }
		}
		else if (value < 0.0f)
		{
			if ((amount + value) >= 0.0f) { amount += value; }
			else { amount = 0.0f; }
		}
	}
};