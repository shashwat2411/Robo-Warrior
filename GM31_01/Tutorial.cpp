#include "customScenes.h"

void TUTORIAL_SCENE::Starter()
{
	tutorial = true;
	score->SetUse(false);	
	player->hp->Invincible();
	skyDome->SetUse(false);

	IMAGE* controls = AddGameObject<IMAGE>(SPRITE_LAYER);

	PLANE* field = FindGameObject<PLANE>();

	field->GetComponent<Plane>()->SetTextureName("asset\\texture\\Square4.png");
	field->GetComponent<Plane>()->TexCoord = D3DXVECTOR2(200.0f, 200.0f);;
	field->GetComponent<Plane>()->Size = D3DXVECTOR2(1000.0f, 1000.0f);
	field->transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	controls->sprite->SetTexture("asset\\texture\\explanation.png");
	controls->sprite->SetSize(D3DXVECTOR2(300.0f, 400.0f));
	controls->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350.0f, 175.0f, 0.0f);
	controls->transform->Scale = D3DXVECTOR3(0.4f, 0.4f, 0.4f);

	//controls->SetUse(false);
}