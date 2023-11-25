#include "prefab.h"
#include "animations.h"
#include "manager.h"
#include "scene.h"
#include "soundReader.h"

void ZIGZAG_ENEMY::Start()
{
	Init();

	AddComponent<EnemyScript>();

	body = scene->AddGameObject<EMPTYOBJECT>();
	after = scene->AddGameObject<FIRE>(BILLBOARD_LAYER);

	body->SetParent(this);
	body->transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	body->transform->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	body->AddComponent<ModelComponent>()->m_Model = ModelReader::GetReadModel(ModelReader::ZIGZAG_ENEMY_M);
	body->AddComponent<SphereCollider>()->SetDynamic(true);
	body->AddComponent<EnemyCollision>();

	after->transform->Position = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	//after->transform->Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	defaultY = 1.5f;
	GetComponent<Transform>()->Scale = D3DXVECTOR3(0.9f, 0.9f, 0.9f);
	GetComponent<Transform>()->Position = D3DXVECTOR3(-4.0f, 3.3f, 0.0f);

	animator = AddComponent<Animator>();
	animator->AddAnimation(AddComponent<EnemyLockOn>(), ZIGZAG_ENEMY::LOCKON);
	animator->AddAnimation(AddComponent<EnemyLockOnReverse>(), ZIGZAG_ENEMY::LOCKON_REVERSE);
	animator->AddAnimation(AddComponent<ZigzagEnemyAttack>(), ZIGZAG_ENEMY::ATTACK);
	animator->AddAnimation(AddComponent<ZigzagEnemyMove>(), ZIGZAG_ENEMY::MOVE);

	hp->SetHP(8.0f);
	//afterimage->SetAfterimageNumber(1);

	attack = false;
	calculate = false;
	attackCounter = 0;
	waitLimit = 60;
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void ZIGZAG_ENEMY::Update()
{
	if (use == true)
	{
		after->transform->Position = D3DXVECTOR3(transform->Position.x, transform->Position.y + body->transform->Position.y - 2.0f, transform->Position.z);
		if (hp->GetHP() <= 0.0f)
		{
			body->Destroy();
			after->Destroy();
		}

		if (transform->Position.y < 1.0f) { transform->Position.y = 1.0f; }

		std::vector<ENEMY*> enemies = scene->FindGameObjects<ENEMY>();

		if (enemies.size() >= 0 && enemies.size() < 10) { waitLimit = 60; }
		else if (enemies.size() >= 10 && enemies.size() < 25) { waitLimit = 90; }
		else if (enemies.size() >= 25 && enemies.size() <= 40) { waitLimit = 120; }

		if (follower->GetFollowBool() == true)
		{
			if (animator->GetAnimationState(ZIGZAG_ENEMY::MOVE) != Animation::PLAYBACK)
			{
				animator->PlayAnimation(ZIGZAG_ENEMY::MOVE);
			}
		}

		if (DistanceFrom(player) < 16.0f)
		{
			//afterimage->SetAfterimageNumber(2);
			if (attack == true && animator->GetAnimationState(ZIGZAG_ENEMY::MOVE) != Animation::PLAYBACK)
			{
				follower->follow = false;
				if (lockon == true)
				{
					animator->PlayAnimation(ZIGZAG_ENEMY::LOCKON);
					if (SoundReader::GetReadSound(SoundReader::ENEMY_LOCK_ON)->IsPlaying() == false) { SoundReader::GetReadSound(SoundReader::ENEMY_LOCK_ON)->Play(false, 0.2f); }
					lockon = false;

					direction = GetForwardDirection();
					direction.y = 0.0f;
					D3DXVec3Normalize(&direction, &direction);
					follower->follow = false;
				}

				if (animator->GetAnimationState(ZIGZAG_ENEMY::LOCKON) == Animation::END)
				{
					if (calculate == true)
					{
						animator->PlayAnimation(ZIGZAG_ENEMY::ATTACK);
						SoundReader::GetReadSound(SoundReader::ZIGZAG_ENEMY_ATTACK)->Play(false, 0.1f);
						calculate = false;
					}

					if (animator->GetAnimationState(ZIGZAG_ENEMY::ATTACK) == Animation::PLAYBACK)
					{
						transform->Position.x += direction.x * 0.3f;
						transform->Position.y += direction.y * 0.3f;
						transform->Position.z += direction.z * 0.3f;

						//if ((transform->Position.y + direction.y * 0.3f) > defaultY) { transform->Position.y += direction.y * 0.3f; }
						//else { transform->Position.y = defaultY; }
					}

					if (animator->GetAnimationState(ZIGZAG_ENEMY::ATTACK) == Animation::END)
					{
						attackCounter = 0;
						attack = false;

						animator->PlayAnimation(ZIGZAG_ENEMY::LOCKON_REVERSE);
					}
				}
			}
			else if (animator->GetAnimationState(ZIGZAG_ENEMY::LOCKON_REVERSE) != Animation::PLAYBACK)
			{
				follower->follow = true;
				if (waitCounter <= waitLimit) { waitCounter++; }
				else { waitCounter = 0; Attack(); }
			}
		}
		else
		{
			//afterimage->SetAfterimageNumber(1);
		}


#ifdef DEBUG	// デバッグ情報を表示する
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], " | hp : %d", hp->GetHP());
#endif
	}
}

void ZIGZAG_ENEMY::SetEnemy(D3DXVECTOR3 position)
{
	hp->SetHP(8.0f);
	attack = false;
	calculate = false;
	attackCounter = 0;
	waitLimit = 60;
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform->Position = position;

	body->SetUse(true);
	use = true;
}