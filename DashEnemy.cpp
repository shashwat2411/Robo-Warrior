#include "prefab.h"
#include "manager.h"
#include "scene.h"
#include "animations.h"
#include "soundReader.h"

void DASH_ENEMY::Start()
{
	Init();

	AddComponent<EnemyScript>();

	AddComponent<ModelComponent>()->m_Model = ModelReader::GetReadModel(ModelReader::DASH_ENEMY_M);

	AddComponent<SphereCollider>()->SetDynamic(true);
	AddComponent<EnemyCollision>();

	GetComponent<Transform>()->Scale = D3DXVECTOR3(0.9f, 0.9f, 0.9f);
	GetComponent<Transform>()->Position = D3DXVECTOR3(-4.0f, 1.01f, 0.0f);

	animator = AddComponent<Animator>();
	animator->AddAnimation(AddComponent<EnemyLockOn>(), DASH_ENEMY::LOCKON);
	animator->AddAnimation(AddComponent<EnemyLockOnReverse>(), DASH_ENEMY::LOCKON_REVERSE);
	animator->AddAnimation(AddComponent<DashEnemyAttack>(), DASH_ENEMY::ATTACK);
	animator->AddAnimation(AddComponent<DashEnemyMove>(), DASH_ENEMY::MOVE);

	rigidbody->useGravity = true;
	
	hp->SetHP(8.0f);
	//shadow->shadowHeight = 0.6f;

	attack = false;
	calculate = false;
	attackCounter = 0;
	waitLimit = 60;
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	freezeY = true;

	//use = false;
}

void DASH_ENEMY::Update()
{
	if (use == true)
	{	
		if (transform->Position.y < 1.0f) { transform->Position.y = 1.0f; }

		std::vector<ENEMY*> enemies = scene->FindGameObjects<ENEMY>();

		if (enemies.size() >= 0 && enemies.size() < 10) { waitLimit = 60; }
		else if (enemies.size() >= 10 && enemies.size() < 25) { waitLimit = 90; }
		else if (enemies.size() >= 25 && enemies.size() <= 40) { waitLimit = 120; }

		if (follower->GetFollowBool() == true)
		{
			if (animator->GetAnimationState(DASH_ENEMY::MOVE) != Animation::PLAYBACK)
			{
				animator->PlayAnimation(DASH_ENEMY::MOVE);
			}
		}

		if (DistanceFrom(player) < 16.0f)
		{
			if (attack == true && animator->GetAnimationState(DASH_ENEMY::MOVE) != Animation::PLAYBACK)
			{
				follower->follow = false;
				if (lockon == true)
				{
					animator->PlayAnimation(DASH_ENEMY::LOCKON);
					if (SoundReader::GetReadSound(SoundReader::ENEMY_LOCK_ON)->IsPlaying() == false) { SoundReader::GetReadSound(SoundReader::ENEMY_LOCK_ON)->Play(false, 0.2f); }
					lockon = false;

					direction = GetForwardDirection();
					direction.y = 0.0f;
					D3DXVec3Normalize(&direction, &direction);
					follower->follow = false;
				}

				if (animator->GetAnimationState(DASH_ENEMY::LOCKON) == Animation::END)
				{
					if (calculate == true)
					{
						rigidbody->Speed = direction * 0.5f;
						animator->PlayAnimation(DASH_ENEMY::ATTACK);
						SoundReader::GetReadSound(SoundReader::DASH_ENEMY_ATTACK)->Play(false, 0.1f);
						calculate = false;
					}

					if (animator->GetAnimationState(DASH_ENEMY::ATTACK) == Animation::END)
					{
						attackCounter = 0;
						attack = false;

						animator->PlayAnimation(DASH_ENEMY::LOCKON_REVERSE);
					}
				}
			}
			else if (animator->GetAnimationState(DASH_ENEMY::LOCKON_REVERSE) != Animation::PLAYBACK)
			{
				follower->follow = true;
				if (waitCounter <= waitLimit) { waitCounter++; }
				else { waitCounter = 0; Attack(); }
			}
		}


#ifdef DEBUG	// デバッグ情報を表示する
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], " | hp : %d", hp->GetHP());
#endif
	}
}

void DASH_ENEMY::SetEnemy(D3DXVECTOR3 position)
{
	hp->SetHP(8.0f);
	attack = false;
	calculate = false;
	attackCounter = 0;
	waitLimit = 60;
	direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	freezeY = true;
	transform->Position = position;

	use = true;
}