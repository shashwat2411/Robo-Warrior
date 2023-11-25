#include "prefab.h"
#include "scene.h"
#include "manager.h"
#include "customScenes.h"

void ATTACKEFFECT::Start()
{
	Init();
	bill = GetComponent<Billboard>();
	bill->SetTextureName("asset\\texture\\attackEffect6.png");
	bill->SetAnimate(true);
	bill->SetElements(4, 3);
	counter = 0.0f;
	transform->Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	use = false;
}

void ATTACKEFFECT::Update()
{
	if (use == true)
	{
		counter += 0.8f;
		bill->Count = (int)counter;
		if (bill->Count >= 12)
		{
			bill->Count = 0;
			use = false;
		}
	}
}

void ATTACKEFFECT::Burst(D3DXVECTOR3 pos, bool flipper) 
{
	if (this != nullptr)
	{
		use = true;
		transform->Position = pos;
		bill->flip = flipper;
		bill->Count = 0;
		counter = 0.0f;
		
		GAME_SCENE* game = (GAME_SCENE*)Manager::GetScene();
		if (game->tutorial == true)
		{
			SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}