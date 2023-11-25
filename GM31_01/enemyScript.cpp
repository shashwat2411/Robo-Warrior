#include "script.h"
#include "manager.h"
#include "scene.h"
#include "prefab.h"
#include "customScenes.h"

void EnemyScript::Start()
{
	ENEMY* enemy = (ENEMY*)gameObject;

	enemy->scene = Manager::GetScene();
	enemy->player = enemy->scene->GetPlayer();

	enemy->AddComponent<Rigidbody>();
	enemy->hp = enemy->AddComponent<HitPoints>();
	enemy->shadow = enemy->AddComponent<Shadow>();
	enemy->follower = enemy->AddComponent<FollowObject>();

	enemy->follower->SetTarget(enemy->player);
}

void EnemyScript::End()
{

}

void EnemyScript::Update()
{
	ENEMY* enemy = (ENEMY*)gameObject;
	PLAYER* player = Manager::GetScene()->GetPlayer();

	gameObject->transform->Position += gameObject->rigidbody->Speed;
	gameObject->rigidbody->Speed *= 0.9f;

	//if (player->dead == false)
	{
		if (gameObject->DistanceFrom(enemy->follower->GetTarget()) < 16.0f) { enemy->follower->SetFollowBool(false); }
		else { enemy->follower->SetFollowBool(true); }
	}

	if (enemy->hp->GetHP() <= 0.0f && enemy->hp->GetNoDamage() == false)
	{
		enemy->Destroy();
		//enemy->shadow->shadow->SetUse(false);
		//system->particleSystem->Burst();
		GAME_SCENE* game = (GAME_SCENE*)enemy->scene;
		PARTICLESYSTEM* effect = game->GetEnemyDestroyEffect();
		effect->particleSystem->Burst();
		effect->transform->Position = enemy->transform->Position;

		game->GetScore()->Increment(50);

		SoundReader::GetReadSound(SoundReader::ENEMY_KILL)->Play(false, 0.5f);
	}
	//if (enemy->hp->GetHP() > 0.0f) { system->transform->Position = enemy->transform->Position; }
}


void EnemyScript::Draw()
{
}
