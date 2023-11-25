#include "script.h"
#include "manager.h"
#include "scene.h"
#include "customScenes.h"

void EnemySpawn::Start()
{
	spawnCounter = 0;
	spawnSpeed = 180;
}

void EnemySpawn::Update()
{
	SCENE* scene = Manager::GetScene();
	std::vector<ENEMY*> enemies = scene->FindGameObjects<ENEMY>();
	//for (auto enemy : enemies) { if (enemy->GetUse() == true) { numOfEnemy++; } }

	spawnCounter++;
	if (spawnCounter % 1800 == 0) { spawnCounter = 0; spawnSpeed *= 0.75; }

	if (spawnCounter % spawnSpeed == 0)
	{
		int dirX = 1;
		int dirZ = 1;

		//Random Generation
		{
			dirX = rand() % 2;
			dirZ = rand() % 2;

			if (dirX % 2 == 0) { dirX = 1; }
			else if (dirX % 2 == 1) { dirX = -1; }

			if (dirZ % 2 == 0) { dirZ = 1; }
			else if (dirZ % 2 == 1) { dirZ = -1; }
		}

		int rX = 20 + (rand() % 100);
		int rZ = 20 + (rand() % 100);

		float x = scene->GetCamera()->transform->Position.x + rX * dirX;
		float z = scene->GetCamera()->transform->Position.z + rZ * dirZ;

		int type = 0;
		type = rand() % 2;

		GAME_SCENE* game = (GAME_SCENE*)scene;

		if (enemies.size() < (game->tutorial == false ? ENEMY_MAX : 1))
		{
			ENEMY* enemy = nullptr;

			if (type == 0) { enemy = scene->AddGameObject<DASH_ENEMY>(); }
			if (type == 1) { enemy = scene->AddGameObject<ZIGZAG_ENEMY>(); }

			if (enemy != nullptr)
			{
				//enemy->SetEnemy(D3DXVECTOR3(x, enemy->transform->Position.y, z));
				enemy->transform->Position.x = x;
				enemy->transform->Position.z = z;
			}
		}
	}

#ifdef DEBUG
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " | Enemy Num : %d", enemies.size());
#endif
}