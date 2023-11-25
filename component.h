#pragma once
#include "gameobject.h"
#include "input.h"
#include <xaudio2.h>

//前方宣言
class PARTICLE;
class DIGIT;
class SHADOW;
class SCENE;

#define COLLIDERS

#define VIEW_NEAR_Z 0.5f
#define VIEW_FAR_Z 140.0f

#define SPEED_VALUE 0.01f
#define ACCELERATION_VALUE 1.1f

#define GRAVITY_CONSTANT 1.0f
#define GRAVITY_ACCELERATION 1.1f

#define DEFAULT_VOLUME 1.0f

//Data Class
class Data
{
public:
	Data() {}
	Data(float m, float* p) { move = m; pointer = p; }
	float move;
	float* pointer;
};
class AnimationData
{
public:
	AnimationData() {}
	AnimationData(int f, Data a) { frame = f; angle.push_back(a); }
	int frame;
	std::vector<Data> angle;

	AnimationData operator=(AnimationData const& obj)
	{
		AnimationData result;
		result.frame = obj.frame;
		result.angle = obj.angle;
		return result;
	}
};

//Base Component Virtual Class
class Component
{
protected:
	bool multiple = false;
	bool ignorePause = false;

public:
	GAMEOBJECT* gameObject;

	bool GetMultipleSet() { return multiple; }

	virtual ~Component() {}
	virtual void Start() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void OnCollisionEnter(GAMEOBJECT* obj) {}

	bool GetIgnorePause() { return ignorePause; }
};

//Components
class Transform : public Component
{
public:

public:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR3 Scale;

	D3DXVECTOR3 GlobalPosition;

	void Start() override 
	{
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		GlobalPosition = Position;
	}
	void End() override {}
	void Update() override {}
	void Draw() override {}
};
class Rigidbody : public Component
{
public:
	D3DXVECTOR3 Speed;
	float Acceleration;
	GAMEOBJECT* FollowTarget;
	bool useGravity;
	float mass;
	float distance;
	float groundLevel;

public:

	void SetFollowTarget(GAMEOBJECT* target, float dist) { FollowTarget = target; distance = dist; }
	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;
};
class Afterimage : public Component
{
public:
	int imageNum;

public:

	void SetAfterimageNumber(int value) { imageNum = value; }
	void Start() override
	{
		//if (gameObject->GetComponent<Rigidbody>() == nullptr && gameObject->Parent->GetComponent<Rigidbody>() == nullptr)
		{
			//gameObject->RemoveComponent<Afterimage>();
			//return;
		}
		for (int i = 0; i < MAX_AFTERIMAGES; i++) { D3DXMatrixIdentity(&gameObject->GetWorldMatrix(i)); }
		D3DXMatrixIdentity(&gameObject->GetRotationMatrix());
		D3DXMatrixIdentity(&gameObject->GetTransformMatrix());
		D3DXMatrixIdentity(&gameObject->GetScaleMatrix());

		D3DXVECTOR3 Position = gameObject->transform->Position;
		D3DXVECTOR3 Rotation = gameObject->transform->Rotation;
		D3DXVECTOR3 Scale = gameObject->transform->Scale;
		//スケーリング行列作成
		D3DXMatrixScaling(&gameObject->GetScaleMatrix(), Scale.x, Scale.y, Scale.z);
		//回転行列作成
		D3DXMatrixRotationYawPitchRoll(&gameObject->GetRotationMatrix(), Rotation.y, Rotation.x, Rotation.z);
		//平行移動行列
		D3DXMatrixTranslation(&gameObject->GetTransformMatrix(), Position.x, Position.y, Position.z);
		//ワールド行列
		D3DXMatrixMultiply(&gameObject->GetWorldMatrix(), &gameObject->GetScaleMatrix(), &gameObject->GetRotationMatrix());  //World = Scaling * Rotation
		D3DXMatrixMultiply(&gameObject->GetWorldMatrix(), &gameObject->GetWorldMatrix(), &gameObject->GetTransformMatrix());  //World = World * Translation

		for (int i = 1; i < MAX_AFTERIMAGES; i++) { gameObject->SetWorldMatrix(gameObject->GetWorldMatrix(),i); }	//リングバッファの初期化
		gameObject->SetRingCounter(0);
	}
	void End() override {}
	void Update() override 
	{
		//Rigidbody* updater = (gameObject->rigidbody == nullptr ? gameObject->Parent->rigidbody : gameObject->rigidbody);
		//sif (fabs(updater->Speed.x) > 0.02f || fabs(updater->Speed.y) > 0.02f || fabs(updater->Speed.z) > 0.02f)
		{
			gameObject->SetRingCounter(gameObject->GetRingCounter() + 1);
			gameObject->SetRingCounter(gameObject->GetRingCounter() % MAX_AFTERIMAGES);
		}
	}
	void Draw() override {}
};
class Sprite : public Component
{
private:
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11ShaderResourceView* Texture = nullptr;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 TexCoord;
	D3DXCOLOR Color;
	
public:
	int Count;
	bool animate;
	int elementsX;
	int elementsY;

	float barOffsetRight;
	float barOffsetLeft;

public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	D3DXCOLOR GetColor() { return Color; }
	void SetColor(D3DXCOLOR value) { Color = value; }

	D3DXVECTOR2 GetSize() { return Size; }
	void SetSize(D3DXVECTOR2 value) { Size = value; }

	D3DXVECTOR2 GetTexCoord() { return TexCoord; }
	void SetTexCoord(D3DXVECTOR2 value) { TexCoord = value; }
	
	void SetTexture(const char* name) 
	{ 
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
			name,
			NULL,
			NULL,
			&Texture,
			NULL);
		assert(Texture);
	}
};
class ModelComponent :public Component
{
private:
	bool collider = false;

public:

	Model* m_Model;

	bool GetCollider() { return collider; }
	void SetCollider(bool value) { collider = value; }

	void Start() override
	{
		multiple = true;
		m_Model = nullptr;
		m_Model = new Model();
	}
	void End() override
	{
		if (m_Model != nullptr)
		{
			m_Model = nullptr;
			//m_Model->Unload();
			delete m_Model;
		}
	}
	void Update() override {}
	void Draw() override
	{
		//if (collider == false)
		{
			Renderer::SetMaterial(gameObject->GetMaterial());
			m_Model->Draw();
		}
	}
};
class SphereCollider : public Component
{
private:
	ModelComponent* m = nullptr;
	float CollisionSize;
	D3DXVECTOR3 CollisionScale;
	D3DXVECTOR3 CollisionPosition;

	GAMEOBJECT* collider = nullptr;
	bool dynamic;
public:

	float GetCollisionSize() { return CollisionSize; }
	bool GetDynamic() { return dynamic; }

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	//void DrawCollider();
	void SetCollisionSize(float s) { CollisionSize = s; collider->transform->Scale = CollisionScale * CollisionSize; }
	void SetDynamic(bool value) { dynamic = value; }

};
class Camera : public Component
{
protected:
	D3DXVECTOR3 Up;
	float fov;

	float len;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 at;

	D3DXMATRIX  mtxView;
	D3DXMATRIX  mtxProjection;

	float rad;

	int shakeCounter;
	float shakeValue;
	bool shake;

public:
	GAMEOBJECT* Target;

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void CameraShake(float value);

	D3DXMATRIX GetViewMatrix() { return mtxView; }
};
class Plane : public Component
{
protected:
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11ShaderResourceView* Texture = nullptr;
	D3DXVECTOR3 Normal;

public:
	GAMEOBJECT* collisionObject;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 TexCoord;

public:
	~Plane() {}

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void SetTextureName(const char* name)
	{
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
			name,
			NULL,
			NULL,
			&Texture,
			NULL);
		assert(Texture);
	}
	void SetNormal(D3DXVECTOR3 value) { Normal = value; }
	D3DXVECTOR3 GetNormal() { return Normal; }
};
class Billboard : public Component
{
private:
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11ShaderResourceView* Texture = nullptr;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 TexCoord;
	D3DXVECTOR3 Normal;


	bool animate;
	int elementsX;
	int elementsY;
public:
	GAMEOBJECT* collisionObject;
	int Count;
	bool flip;

public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void SetTextureName(const char* name)
	{
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
			name,
			NULL,
			NULL,
			&Texture,
			NULL);
		assert(Texture);
	}
	void SetNormal(D3DXVECTOR3 value) { Normal = value; }
	D3DXVECTOR3 GetNormal() { return Normal; }

	void SetAnimate(bool value) { animate = value; }
	bool GetAnimate() { return animate; }

	enum COOD { X = 0, Y };
	void SetElements(int x, int y) { elementsX = x; elementsY = y; }
	int GetElements(COOD value) { if (value == X) { return elementsX; } else { return elementsY; } }
};
class Script :public Component
{
public:
	void Start() override {}
	void End() override {}
	void Update() override {}
	void Draw() override {}
};
class ParticleSystem : public Component
{
private:
	int numberOfObjects;
	int numberOfObjectsToAdd;
	float speed;
	D3DXVECTOR3 direction;
	std::vector<PARTICLE*> objects;
	const char* texture;
	SCENE* scene;

public:
	bool burst;
	bool loop;
	bool rotateRandom;
	float rotationSpeed;

public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void SetTexture(const char* name);
	void SetLife(const int value);
	void SetSpeed(const float value);
	void SetParticleCount(int value);

	int GetNumberOfObjects() { return numberOfObjects; }

	void Burst();
};
class Number : public Component
{
private:
	std::vector<DIGIT*> numbers;
	int digits;
	int number;
public:

	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void SetNumber(int num) { number = num; }
	void SetDigits(int num);

	void SetNumberColor(D3DXCOLOR value);
};
class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};



public:

	int						m_Length{};
	int						m_PlayLength{};

	static void InitMaster();
	static void UninitMaster();
	static void PlayMaster(const char *FileName, float volume = DEFAULT_VOLUME);

	using Component::Component;

	void Load(const char *FileName);
	void Play(bool Loop = false, float volume = DEFAULT_VOLUME);
	void Stop();
	void SetVolume(float volume);

	void Start() override {}
	void End() override {}
	void Update() override {}
	void Draw() override {}

	void Unload();

	bool IsPlaying();
};
class Animation: public Component
{
public:
	enum ANIMATION_STATUS
	{
		STANDBY = 0,
		PLAYBACK,
		END,
		LOOP
	};

public:
	std::vector<AnimationData> data;
	int index;
	int timer;
	int animationSize;
	int keyframes;
	ANIMATION_STATUS status;

	void Start() override
	{
		data.push_back(AnimationData(0, Data(0.0f, &gameObject->transform->Rotation.x)));
		data.push_back(AnimationData(20, Data(50.0f, &gameObject->transform->Rotation.x)));
		data.push_back(AnimationData(40, Data(-120.0f, &gameObject->transform->Rotation.x)));
		data.push_back(AnimationData(60, Data(30.0f, &gameObject->transform->Rotation.x)));
		data.push_back(AnimationData(80, Data(-70.0f, &gameObject->transform->Rotation.x)));

		data[0].angle.push_back(Data(0.0f, &gameObject->transform->Rotation.y));
		data[1].angle.push_back(Data(50.0f, &gameObject->transform->Rotation.y));
		data[2].angle.push_back(Data(-120.0f, &gameObject->transform->Rotation.y));
		data[3].angle.push_back(Data(60.0f, &gameObject->transform->Rotation.y));
		data[4].angle.push_back(Data(-20.0f, &gameObject->transform->Rotation.y));

		index = 0;
		timer = 0;
		status = Animation::STANDBY;
	}


	void End() override {}
	void Update() override {}
	void Draw() override {}
};
class Animator : public Component
{
private:
	int animIndex;
	std::vector<Animation*> animation;

public:
	void Start() override;
	void End() override;
	void Update() override;
	void Draw() override;

	void InitAnimation(Animation::ANIMATION_STATUS stat = Animation::STANDBY)
	{
		animation[animIndex]->index = 0;
		animation[animIndex]->timer = 0;
		animation[animIndex]->status = stat;
	}
	void AddAnimation(Animation* anim, int index, Animation::ANIMATION_STATUS stat = Animation::STANDBY)
	{
		animation.push_back(anim);
		animIndex = index;
		InitAnimation(stat);
	}

	void PlayAnimation(int index, Animation::ANIMATION_STATUS stat = Animation::PLAYBACK)
	{
		if (animation[animIndex]->status != Animation::LOOP)
		{
			animIndex = index;
			animation[animIndex]->status = stat;
		}
	}

	void PauseAnimation(int index)
	{
		animation[index]->status = Animation::STANDBY;
	}

	void StopAnimation(int index)
	{
		animation[index]->index = 0;
		animation[index]->timer = 0;
		PauseAnimation(index);
	}

	void AnimationTransition(int index, int anotherIndex)
	{
		PauseAnimation(anotherIndex);
		animation[index]->timer = animation[anotherIndex]->animationSize - animation[anotherIndex]->timer;
		animation[index]->index = animation[anotherIndex]->keyframes - 2 - animation[anotherIndex]->index;
		StopAnimation(anotherIndex);

		PlayAnimation(index);
	}//(次のアニメーション, 止めるアニメーション)

	Animation::ANIMATION_STATUS GetAnimationState(int index)
	{
		Animation::ANIMATION_STATUS stat = animation[index]->status;
		if (animation[index]->status == Animation::PLAYBACK || animation[index]->status == Animation::LOOP)
		{
			stat = Animation::PLAYBACK;
		}
		return stat;
	}

	int GetCurrentIndex() { return animIndex; }
};
class Shadow : public Component
{
public:
	SHADOW* shadow;
	float shadowHeight;

public:
	~Shadow() {}

	void Start() override;
	void End() override {}
	void Update() override;
	void Draw() override {}
};
class FollowObject : public Component
{
public:
	GAMEOBJECT* target;
	float followSpeed;
	bool follow;

public:
	~FollowObject() {}

	void Start() override
	{
		target = nullptr;
		followSpeed = 0.04f;
		follow = true;
	}
	void End() override 
	{
		target = nullptr;
		delete target;
	}
	void Update() override
	{
		if (follow == true)
		{
			if (target == nullptr) { return; }

			gameObject->FaceTowards(target);

			D3DXVECTOR3 direction = target->transform->Position - gameObject->transform->Position;
			D3DXVec3Normalize(&direction, &direction);
			direction *= followSpeed;

			gameObject->transform->Position.x += direction.x;
			gameObject->transform->Position.y += direction.y;
			gameObject->transform->Position.z += direction.z;

			//if ((gameObject->transform->Position.y + direction.y) > gameObject->GetDefaultY()) { gameObject->transform->Position.y += direction.y; }
			//else { gameObject->transform->Position.y = gameObject->GetDefaultY(); }
		}
	}
	void Draw() override {}

	void SetTarget(GAMEOBJECT* value) { target = value; }
	void SetFollowBool(bool value) { follow = value; }

	GAMEOBJECT* GetTarget() { return target; }
	bool GetFollowBool() { return follow; }
};

//Camera Types
class TopDownCamera : public Camera
{
private:

public:

	void Update() override
	{
		gameObject->transform->Position = Target->transform->Position + D3DXVECTOR3(0.0f, 5.0, -10.0f);
	}
};
class ThirdPersonCamera : public Camera
{
private:

public:
	void Update() override
	{
		if (Target != nullptr)
		{
			if (shake == true)
			{
				shakeCounter++;
				if (shakeCounter % 3 == 0) { shakeValue *= -1; }
				at.x += shakeValue;

				if (shakeCounter % 15 == 0) { shake = false; }
			}
			//D3DXVECTOR3 Focus = Target->transform->Position + gameObject->GetRightDirection() * 0.5f;
			D3DXVECTOR3 toBeAt = at - Target->GetForwardDirection() * 8.0f + D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			
			
			D3DXVECTOR3 AtVec;
			D3DXVECTOR3 PosVec;

			//今回のカメラの座標
			PosVec.x = at.x - sinf(rot.y) *len;
			PosVec.y = gameObject->transform->Position.y;
			PosVec.z = at.z - cosf(rot.y) * len;

			AtVec = toBeAt - at;	//注視点の変化ベクトル
			PosVec = PosVec - gameObject->transform->Position;	//一座標の変化

			PosVec *= 0.01f;	//ベクトルスケーリング
			AtVec *= 0.03f;	//ベクトルスケーリング

			// カメラの注視点をプレイヤーの座標にしてみる
			at += AtVec;
			gameObject->transform->Position += PosVec;
		}
	}
};
class FirstPersonCamera : public Camera
{
private:

public:

	void Update() override
	{
		gameObject->transform->Position = Target->transform->Position + Target->GetForwardDirection();
		//Disable Look At
	}
};
class OpenWorldCamera : public Camera
{
private:

public:

	void Update() override
	{
		gameObject->transform->Position = Target->transform->Position + D3DXVECTOR3(0.0f, 5.0, 0.0f);
		gameObject->transform->Position += D3DXVECTOR3(cosf(gameObject->transform->Rotation.y), 0.0f, sinf(gameObject->transform->Rotation.y)) * 5.0f;

		if (Input::GetKeyPress('O'))
		{
			gameObject->transform->Rotation.y += 0.1f;
		}
		else if (Input::GetKeyPress('L'))
		{
			gameObject->transform->Rotation.y -= 0.1f;
		}
		//Disable Look At
	}
};