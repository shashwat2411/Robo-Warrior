#include "script.h"
#include "manager.h"
#include "scene.h"
#include "customScenes.h"

void PlayerAttack::Start()
{

}

void PlayerAttack::End()
{

}

void PlayerAttack::Update()
{
	
}

void PlayerAttack::Draw()
{

}

void PlayerAttack::OnCollisionEnter(GAMEOBJECT* obj)
{
	bool exists = false;
	if (obj->GetComponent<EnemyScript>() != nullptr) { exists = true; }
	if (obj->Parent != nullptr) { if (obj->Parent->GetComponent<EnemyScript>() != nullptr) { obj = obj->Parent; exists = true; } }

	PLAYER* player = Manager::GetScene()->FindGameObject<PLAYER>();

	if (exists == true && player->dead == false)
	{
		GAME_SCENE* game = (GAME_SCENE*)Manager::GetScene();
		GAMEOBJECT* object = player->GetComponentInChildren<Animator>()->gameObject;
		CHARACTER* character = (CHARACTER*)object;
		ENEMY* enemy = (ENEMY*)obj;
		Animation::ANIMATION_STATUS punchR = character->rightHand->GetAnimationState(CHARACTER::PUNCH_LAUNCH_R);
		Animation::ANIMATION_STATUS punchL = character->leftHand->GetAnimationState(CHARACTER::PUNCH_LAUNCH_L);

		//Collision Coordinates
		D3DXVECTOR3 spawnLocation = obj->transform->GlobalPosition - gameObject->transform->GlobalPosition;
		D3DXVec3Normalize(&spawnLocation, &spawnLocation);
		float overlap = gameObject->GetComponent<SphereCollider>()->GetCollisionSize();
		D3DXVECTOR3 destination = gameObject->transform->GlobalPosition + spawnLocation * overlap;

		if (punchR == Animation::PLAYBACK || punchL == Animation::PLAYBACK)//player attack
		{
			D3DXVECTOR3 dir = character->GetForwardDirection();
			D3DXVec3Normalize(&dir, &dir);
			obj->rigidbody->Speed = dir * 0.3f;

			if (enemy->hp->Damage() == true)
			{
				game->GetAttackEffect()->Burst(destination);
				SoundReader::GetReadSound(SoundReader::ATTACK_LAND)->Play(false, 0.15f);
			}
		}
		else if (enemy->animator->GetAnimationState(DASH_ENEMY::ATTACK) == Animation::PLAYBACK)//enemy attack
		{
			if (character->animator->GetAnimationState(CHARACTER::PARRY) != Animation::PLAYBACK)
			{
				float damage = 5.0f;
				if (character->guard == true) { damage = 5.0f; }
				else { damage = 10.0f; game->GetCamera()->camera->CameraShake(20.0f); }

				bool condition = player->posture->Damage(damage);
				if(condition == true){ SoundReader::GetReadSound(SoundReader::HIT_WHILE_GUARD)->Play(false, 0.35f); }

				D3DXVECTOR3 dir = enemy->rigidbody->Speed;
				D3DXVec3Normalize(&dir, &dir);
				player->rigidbody->Speed = dir * 0.4f;
				enemy->SetAttack(false);

				if (player->hp->GetInvincible() == false && condition == true) { game->GetDamageEffect()->Burst(destination); }
			}
			else
			{
				D3DXVECTOR3 dir = character->GetForwardDirection();
				D3DXVec3Normalize(&dir, &dir);

				obj->rigidbody->Speed = dir * 0.6f;
				if (enemy->hp->Damage(5) == true)
				{
					SoundReader::GetReadSound(SoundReader::PARRY)->Play(false, 0.4f);

					game->GetParryEffect()->Burst(D3DXVECTOR3(destination.x + 1.0f, destination.y, destination.z));
					game->GetParryEffect()->Burst(D3DXVECTOR3(destination.x - 1.0f, destination.y, destination.z), true);
				}

			}
		}
		else//Enemy collides with the fists
		{
			D3DXVECTOR3 dir = gameObject->transform->Position - enemy->transform->Position;
			D3DXVec3Normalize(&dir, &dir);
			dir.y = 0.0f;

			obj->rigidbody->Speed = dir * 0.2f;
		}
	}
}