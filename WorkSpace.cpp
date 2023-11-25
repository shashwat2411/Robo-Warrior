#include "customScenes.h"

SPARK* spark1;
SPARK* spark2;

void WORKSPACE_SCENE::Init()
{
	//system = AddGameObject<PARTICLESYSTEM>(BILLBOARD_LAYER);
	spark1 = AddGameObject<SPARK>(BILLBOARD_LAYER);
	spark2 = AddGameObject<SPARK>(BILLBOARD_LAYER);
	skyDome = AddGameObject<SKYDOME>(GAMEOBJECT_LAYER);
	MainCamera->GetComponent<Camera>()->Target = spark1;

	//system->particleSystem->SetTexture("asset\\texture\\gear.png");
	//system->particleSystem->burst = true;
	//system->particleSystem->loop = true;
	//system->particleSystem->SetLife(10);
	//system->particleSystem->SetSpeed(1.0f);
	//system->particleSystem->rotateRandom = true;
	//system->particleSystem->rotationSpeed = 70.0f;
}

void WORKSPACE_SCENE::Update()
{
	if (Input::GetKeyPress('W')) { MainCamera->transform->Position.z += 0.2f; }
	if (Input::GetKeyPress('A')) { MainCamera->transform->Position.x -= 0.2f; }
	if (Input::GetKeyPress('S')) { MainCamera->transform->Position.z -= 0.2f; }
	if (Input::GetKeyPress('D')) { MainCamera->transform->Position.x += 0.2f; }
	if (Input::GetKeyPress('Q')) { MainCamera->transform->Position.y += 0.2f; }
	if (Input::GetKeyPress('E')) { MainCamera->transform->Position.y -= 0.2f; }

	if (Input::GetKeyTrigger('1'))
	{
		spark1->Burst(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		spark2->Burst(D3DXVECTOR3(-1.0f, 0.0f, 0.0f), true);
	}
	//if (Input::GetKeyPress('T')) { system->transform->Position.z += 0.5f; }
	//if (Input::GetKeyPress('G')) { system->transform->Position.z -= 0.5f; }

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], " | Particle Number : %d", system->particleSystem->GetNumberOfObjects());
#endif
}