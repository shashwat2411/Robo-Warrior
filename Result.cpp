#include "customScenes.h"

void RESULT_SCENE::Init()
{
	//GAMEOBJECT

	//UI
	GAMEOBJECT* result = AddGameObject<IMAGE>(SPRITE_LAYER);
	score = Manager::GetDontDestroyOnLoadScene()->FindGameObject<NUMBER>();

	//eŽqŠÖŒWÝ’è

	//Ý’è
	result->GetComponent<Sprite>()->SetTexture("asset\\texture\\resultBG.png");
	result->GetComponent<Sprite>()->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	result->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	finalScore = score->GetNumber();
	score->SetNumber(0);
	score->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 30.0f, SCREEN_HEIGHT / 2, 0.0f);
	score->transform->Scale = D3DXVECTOR3(0.7f, 0.6f, 0.6f);

	SoundReader::GetReadSound(SoundReader::RESULT)->Play(true, 0.2f);
}

void RESULT_SCENE::Update()
{
	if (wait <= 60) { wait++; }
	else
	{
		if ((score->GetNumber() + 5) < finalScore) { score->Increment(5); SoundReader::GetReadSound(SoundReader::COUNTDOWN)->Play(false, 0.2f);}
		else { score->SetNumber(finalScore); }
	}

	if (Input::GetKeyTrigger('K')) { End = true; SoundReader::GetReadSound(SoundReader::BUTTON)->Play(false, 0.2f);}
	if (End == true && Fade->GetFadeIn() == false) { if (Fade->FadeOut() == false) { score->SetUse(false); Manager::SetScene<TITLE_SCENE>(); } }
}