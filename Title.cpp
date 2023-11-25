#include "customScenes.h"

IMAGE* options[3];
IMAGE* options2[3];
int selected = 0;
D3DXVECTOR3 originalSize;
D3DXVECTOR3 selectedSize;
D3DXCOLOR originalColor;
D3DXCOLOR selectedColor;
bool press;
int pressCounter;

void TITLE_SCENE::Init()
{
	//GAMEOBJECT

	//UI
	IMAGE* background = AddGameObject<IMAGE>(SPRITE_LAYER);
	IMAGE* logo = AddGameObject<IMAGE>(SPRITE_LAYER);
	options[0] = AddGameObject<IMAGE>(SPRITE_LAYER);
	options[1] = AddGameObject<IMAGE>(SPRITE_LAYER);
	options[2] = AddGameObject<IMAGE>(SPRITE_LAYER);

	options2[0] = AddGameObject<IMAGE>(SPRITE_LAYER);
	options2[1] = AddGameObject<IMAGE>(SPRITE_LAYER);
	options2[2] = AddGameObject<IMAGE>(SPRITE_LAYER);

	//eŽqŠÖŒWÝ’è

	//Ý’è
	background->sprite->SetTexture("asset\\texture\\title.jpg");
	background->sprite->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	background->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	logo->GetComponent<Sprite>()->SetTexture("asset\\texture\\titleLogo2.png");
	logo->GetComponent<Sprite>()->SetSize(D3DXVECTOR2(20.0f, 10.0f));
	logo->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
	logo->transform->Scale = D3DXVECTOR3(15.0f, 15.0f, 15.0f);

	float offset = 40.0f;
	originalSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	selectedSize = D3DXVECTOR3(1.3f, 1.3f, 1.3f);

	originalColor = D3DXCOLOR(0.7f, 1.0f, 1.0f, 1.0f);
	selectedColor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	options[0]->sprite->SetSize(D3DXVECTOR2(80.0f, 20.0f));
	options[0]->sprite->SetTexture("asset\\texture\\play.png");
	options[0]->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	options[0]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50.0f + offset, 0.0f);

	options[1]->sprite->SetSize(D3DXVECTOR2(170.0f, 20.0f));
	options[1]->sprite->SetTexture("asset\\texture\\tutorial.png");
	options[1]->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	options[1]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 110.0f + offset, 0.0f);

	options[2]->sprite->SetSize(D3DXVECTOR2(80.0f, 20.0f));
	options[2]->sprite->SetTexture("asset\\texture\\quit.png");
	options[2]->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	options[2]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 170.0f + offset, 0.0f);

	options2[0]->sprite->SetSize(D3DXVECTOR2(80.0f, 20.0f));
	options2[0]->sprite->SetTexture("asset\\texture\\play2.png");
	options2[0]->transform->Scale = selectedSize;
	options2[0]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50.0f + offset, 0.0f);
	options2[0]->SetColor(selectedColor);
	options2[0]->SetUse(false);

	options2[1]->sprite->SetSize(D3DXVECTOR2(170.0f, 20.0f));
	options2[1]->sprite->SetTexture("asset\\texture\\tutorial2.png");
	options2[1]->transform->Scale = selectedSize;
	options2[1]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 110.0f + offset, 0.0f);
	options2[1]->SetColor(selectedColor);
	options2[1]->SetUse(false);
	
	options2[2]->sprite->SetSize(D3DXVECTOR2(80.0f, 20.0f));
	options2[2]->sprite->SetTexture("asset\\texture\\quit2.png");
	options2[2]->transform->Scale = selectedSize;
	options2[2]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 170.0f + offset, 0.0f);
	options2[2]->SetColor(selectedColor);
	options2[2]->SetUse(false);

	//variables
	selected = 0;
	press = false;
	pressCounter = 0;

	SoundReader::GetReadSound(SoundReader::TITLE)->Play(true, 0.4f);
}

void TITLE_SCENE::Update()
{
	//Input
	if (press == false && pressCounter <= 0)
	{
		if (Input::GetKeyTrigger('W'))
		{
			if (selected > 0) { selected--; }
			else { selected = 2; }
			SoundReader::GetReadSound(SoundReader::OPTION_CHANGE)->Play(false, 0.2f);
		}
		else if (Input::GetKeyTrigger('S'))
		{
			if (selected < 2) { selected++; }
			else { selected = 0; }
			SoundReader::GetReadSound(SoundReader::OPTION_CHANGE)->Play(false, 0.2f);
		}
	}

	//Size & Color
	for (int i = 0; i < 3; i++)
	{
		options[i]->SetUse(true);
		options2[i]->SetUse(false);
	}
	options[selected]->SetUse(false);
	options2[selected]->SetUse(true);

	//Key Press
	if (Input::GetKeyTrigger('K') && pressCounter <= 0) { press = true; SoundReader::GetReadSound(SoundReader::BUTTON)->Play(false, 0.2f);}
	if (press == true)
	{
		options2[selected]->transform->Scale = originalSize;
		if (pressCounter < 4) { pressCounter++; }
		else { press = false; options2[selected]->transform->Scale = selectedSize; End = true; }
	}

	//Fade Out
	if (End == true && Fade->GetFadeIn() == false) 
	{ 
		if (Fade->FadeOut() == false) 
		{
			if (selected == 0) { Manager::SetScene<GAME_SCENE>(); }
			else if (selected == 1) { Manager::SetScene<TUTORIAL_SCENE>(); }
			else if (selected == 2) { exit(999); }
		} 
	}
}