#include "script.h"
#include "prefab.h"
#include "manager.h"
#include "scene.h"
#include "input.h"

void EnemyBrain::Start()
{
	initiateAttack = false;
	startCounter = false;
	counter = 0;
}

void EnemyBrain::Update()
{
	PLAYER* player = Manager::GetScene()->FindGameObject<PLAYER>();
	std::vector<DASH_ENEMY*> allEnemies = Manager::GetScene()->FindGameObjects<DASH_ENEMY>();

	//for (auto enemy : allEnemies)
	//{
	//	if (enemy->DistanceFrom(player) < 16.0f)
	//	{
	//		int i = 0;
	//		for (auto en : enemies) { if (en == enemy) { i++; } }
	//		if (i == 0) { enemies.push_back(enemy); }
	//	}
	//}

	//for (int i = 0; i < enemies.size(); i++)
	//{
	//	enemies.remove_if([](DASH_ENEMY* object) {return object->Remove(); });
	//}

	//if (Input::GetKeyTrigger('E'))
	//{
	//	initiateAttack = true;
	//}

	//if (initiateAttack == true)
	//{
	//	if (enemies.size() > 0)
	//	{
	//		int random = rand() % (enemies.size());

	//		enemies[random]->Attack();
	//		startCounter = true;
	//		initiateAttack = false;
	//	}
	//}
	//
	//if (startCounter == true)
	//{
	//	if (counter < 120) { counter++; }
	//	else { counter = 0; startCounter = false; initiateAttack = true; }
	//}


#ifdef DEBUG
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " | Enemies near me : %d", enemies.size());
#endif
}