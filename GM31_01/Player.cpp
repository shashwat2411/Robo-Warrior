#include "prefab.h"
#include "manager.h"
#include "scene.h"
#include "soundReader.h"

void PLAYER::Start()
{
	Init();

	GetComponent<Transform>()->Scale = D3DXVECTOR3(1.0f, 1.0f,1.0f);
	GetComponent<Transform>()->Position = D3DXVECTOR3(1.0f, 1.01f, 1.0f);

	this->AddComponent<PlayerMovement>();
	hp = AddComponent<HitPoints>();
	posture = AddComponent<Posture>();

	shadow = AddComponent<Shadow>();
	//shadow->shadowHeight = 0.01f;

	hp->SetHP(100);
	hp->SetDisable(true);

	deadCounter = 0;
	afterDeathCounter = 0;
	deathAnimation = false;
	dead = false;
	
#ifdef DEBUG
	//hp->Invincible();
#endif
}

void PLAYER::Update()
{
	if (hp->GetHP() <= 0.0f && hp->GetNoDamage() == false)
	{
		SCENE* scene = Manager::GetScene();
		CHARACTER* character = scene->FindGameObject<CHARACTER>();
		if (dead == false) { SoundReader::GetReadSound(SoundReader::GAME_OVER)->Play(false, 0.2f); }

		if (character != nullptr)
		{
			character->disable = true;
			dead = true;
		}

		if (deadCounter < 45) { deadCounter++; }
		else if (deathAnimation == false)
		{
			deathAnimation = true;

			scene->GetCamera()->camera->Target = this;
			character->RemoveComponent<Shadow>();
			RemoveComponent<Shadow>();
			//character->animator->PlayAnimation(CHARACTER::DEATH);
			D3DXVECTOR3 position1 = character->GetRightDirection()*1.5f - character->GetForwardDirection()*0.3f;
			D3DXVECTOR3 position2 = -character->GetForwardDirection()*0.3f;
			D3DXVECTOR3 position3 = -character->GetRightDirection()*1.5f - character->GetForwardDirection()*0.3f;

			scene->AddGameObject<DEATHEFFECT>(BILLBOARD_LAYER)->Burst(transform->Position + position3);
			scene->AddGameObject<DEATHEFFECT>(BILLBOARD_LAYER)->Burst(transform->Position + position2);
			scene->AddGameObject<DEATHEFFECT>(BILLBOARD_LAYER)->Burst(transform->Position + position1);

			//character->Destroy();
			character->animator->PlayAnimation(CHARACTER::DEATH);

			SoundReader::GetReadSound(SoundReader::DEATH)->Play(false, 0.4f);
		}

		if (deathAnimation == true && afterDeathCounter < 160) { afterDeathCounter++; }
		//if (character->animator->GetAnimationState(CHARACTER::DEATH) == Animation::END)
		if(afterDeathCounter >= 160) { scene->SetEnd(); }
	}

	//Collision
	/*
	{
		{
			for (auto cylinder : Manager::GetScene()->FindGameObjects<CYLINDER>())
			{
				if (DistanceFromWithY0(cylinder) < cylinder->transform->Scale.x + transform->Scale.x)
				{
					if (transform->Position.y < cylinder->transform->Position.y + cylinder->transform->Scale.y - 0.5f)
					{
						transform->Position.x = transform->Position.x - rigidbody->Speed.x;
						transform->Position.z = transform->Position.z - rigidbody->Speed.z;
					}
					else
					{
						rigidbody->groundLevel = cylinder->transform->Position.y + cylinder->transform->Scale.y + 1.0f;
					}
					break;
				}
				else
				{
					rigidbody->groundLevel = 0.0f;
				}
			}
		}

		{
			for (auto box : Manager::GetScene()->FindGameObjects<CUBE>())
			{
				D3DXVECTOR3 playerPosition = transform->Position;
				D3DXVECTOR3 playerScale = transform->Scale;
				D3DXVECTOR3 boxPosition = box->transform->Position;
				D3DXVECTOR3 boxScale = box->transform->Scale;

				if (playerPosition.x < boxPosition.x + boxScale.x + 0.5f && playerPosition.x > boxPosition.x - boxScale.x - 0.5f)
				{
					if (playerPosition.z< boxPosition.z + boxScale.z + 0.5f && playerPosition.z > boxPosition.z - boxScale.z - 0.5f)
					{
						if (playerPosition.y < boxPosition.y + boxScale.y * 2.0f - 0.5f)
						{
							transform->Position.x = transform->Position.x - rigidbody->Speed.x;
							transform->Position.z = transform->Position.z - rigidbody->Speed.z;
						}
						else
						{
							rigidbody->groundLevel = box->transform->Position.y + box->transform->Scale.y * 2.0f + 1.0f;
						}
						break;
					}
				}
			}
		}
	}
	*/

#ifdef DEBUG
	if (Input::GetKeyTrigger('Q')) { hp->Damage(50.0f); Manager::GetScene()->GetCamera()->camera->CameraShake(100.0f); }
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " | Player HP : %d | Posture : %.2f", hp->GetHP(), posture->GetPosture());
#endif
}
