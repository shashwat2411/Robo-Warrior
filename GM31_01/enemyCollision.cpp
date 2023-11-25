#include "script.h"
#include "manager.h"
#include "scene.h"
#include "customScenes.h"

void EnemyCollision::Start()
{

}

void EnemyCollision::End()
{

}

void EnemyCollision::OnCollisionEnter(GAMEOBJECT* obj)
{
	ENEMY* enemy = (ENEMY*)gameObject;
	PLAYER* player = Manager::GetScene()->GetPlayer();
	if (strcmp(/*this is returning a pointer so change that*/obj->GetTag(),"character") == 0 && player->dead == false)
	{
		if (gameObject->GetComponent<EnemyScript>() == nullptr)
		{
			if (gameObject->Parent != nullptr)
			{
				if (gameObject->Parent->GetComponent<EnemyScript>() != nullptr)
				{
					enemy = (ENEMY*)gameObject->Parent;
				}
			}
		}

		PLAYER* player = (PLAYER*)obj->Parent;

		if (enemy->GetAttack() == false)
		{
			//player->hp->Damage();
			//enemy->hp->Damage();

			D3DXVECTOR3 dir = -gameObject->GetForwardDirection();
			D3DXVec3Normalize(&dir, &dir);
			enemy->rigidbody->Speed = dir * 0.2f;
		}
		else
		{
			GAME_SCENE* game = (GAME_SCENE*)Manager::GetScene();

			D3DXVECTOR3 dir = gameObject->GetForwardDirection();
			D3DXVec3Normalize(&dir, &dir);

			player->rigidbody->Speed = dir * 0.3f;
			enemy->SetAttack(false);

			D3DXVECTOR3 spawnLocation = gameObject->transform->GlobalPosition - obj->transform->GlobalPosition;
			D3DXVec3Normalize(&spawnLocation, &spawnLocation);
			float overlap = obj->GetComponent<SphereCollider>()->GetCollisionSize();
			D3DXVECTOR3 destination = obj->transform->GlobalPosition + spawnLocation * overlap;

			if (player->hp->Damage(8) == true)
			{
				game->GetDamageEffect()->Burst(destination);
				SoundReader::GetReadSound(SoundReader::HIT)->Play(false, 0.2f);
			}
			game->GetCamera()->camera->CameraShake(100.0f);
		}
	}
}