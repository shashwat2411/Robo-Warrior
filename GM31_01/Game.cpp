#include "customScenes.h"

void GAME_SCENE::Init()
{
	//Trash
	/*
	|-----------------TRASH---------------------------------
	|
	|cylinder = AddGameObject<CYLINDER>();
	|AddGameObject<CUBE>()->transform->Position.y = -1.0f;
	|
	|character = AddGameObject<CHARACTER>();
	|
	|AddGameObject<PARTICLESYSTEM>()->GetComponent<ParticleSystem>()->SetTexture("asset\\texture\\home2.png");
	|
	|playerModel->AddComponent<Afterimage>()->SetAfterimageNumber(2);
	|
	|cylinder->transform->Scale = D3DXVECTOR3(3.0f, 2.0f, 3.0f);
	|cylinder->transform->Position = D3DXVECTOR3(2.0f, -1.0f, 10.0f);
	|
	|FindGameObjects<DASH_ENEMY>()[0]->GetComponent<Rigidbody>()->SetFollowTarget(player, 2.1f);
	|FindGameObjects<DASH_ENEMY>()[1]->GetComponent<Rigidbody>()->SetFollowTarget(FindGameObjects<DASH_ENEMY>()[0], 2.1f);
	|FindGameObjects<DASH_ENEMY>()[2]->GetComponent<Rigidbody>()->SetFollowTarget(FindGameObjects<DASH_ENEMY>()[1], 2.1f);
	|FindGameObjects<DASH_ENEMY>()[3]->GetComponent<Rigidbody>()->SetFollowTarget(FindGameObjects<DASH_ENEMY>()[2], 2.1f);
	|
	|playerModel->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\Player1.obj");
	|-------------------------------------------------------
	*/


	//変数定義
	GAMEOBJECT* field;
	GAMEOBJECT* cylinder;
	GAMEOBJECT* enemy;
	IMAGE* heart;


	//オブジェクト追加
	skyDome = AddGameObject<SKYDOME>();
	field = AddGameObject<PLANE>();
	player = AddGameObject<PLAYER>();
	playerModel = AddGameObject<CHARACTER>();

	//UI
	score = Manager::GetDontDestroyOnLoadScene()->FindGameObject<NUMBER>();
	if (score == nullptr) { score = Manager::GetDontDestroyOnLoadScene()->AddGameObject<NUMBER>(SPRITE_LAYER); }

	postureBarBackground2 = AddGameObject<IMAGE>(SPRITE_LAYER);
	postureBarBackground = AddGameObject<IMAGE>(SPRITE_LAYER);
	hpBarBackground = AddGameObject<IMAGE>(SPRITE_LAYER);
	postureBar = AddGameObject<BAR>(SPRITE_LAYER);
	hpBar = AddGameObject<BAR>(SPRITE_LAYER);
	pauseText[1] = AddGameObject<IMAGE>(SPRITE_LAYER);
	pauseText[0] = AddGameObject<IMAGE>(SPRITE_LAYER);
	pauseText[2] = AddGameObject<IMAGE>(SPRITE_LAYER);
	pauseText[3] = AddGameObject<IMAGE>(SPRITE_LAYER);
	heart = AddGameObject<IMAGE>(SPRITE_LAYER);


	//親子関係設定
	playerModel->SetParent(player);


	//編集
	//skyDome->SetUse(false);

	player->hp->Vulnerable();

	playerModel->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	playerModel->transform->Rotation.y = 90.0f;

	//skyDome->GetComponent<ModelComponent>()->m_Model->Load("asset\\model\\domeTest.obj");
	
	field->GetComponent<Plane>()->SetTextureName("asset\\texture\\ground4.jpg");
	field->GetComponent<Plane>()->TexCoord = D3DXVECTOR2(100.0f, 100.0f);;
	field->GetComponent<Plane>()->Size = D3DXVECTOR2(1000.0f, 1000.0f);
	field->transform->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MainCamera->GetComponent<Camera>()->Target = playerModel;
	MainCamera->AddComponent<EnemySpawn>();

	
	//UI
	score->SetUse(true);
	score->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 15.0f, 45.0f, 0.0f);
	score->transform->Scale = D3DXVECTOR3(0.3f, 0.35f, 0.3f);
	score->SetDigits(4);
	score->SetNumber(0);
	score->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	postureBar->sprite->SetTexture("asset\\texture\\postureBar.png");
	postureBar->sprite->SetSize(D3DXVECTOR2(100.0f, 10.0f));
	postureBar->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	postureBar->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	postureBar->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f));
	sprintf(postureBar->GetTag(), "PostureBar");
	postureBar->SetBarType(BAR::MIDDLE);
	player->posture->SetBarController(&postureBar->amount);

	hpBar->sprite->SetSize(D3DXVECTOR2(150.0f, 15.0f));
	hpBar->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT - 50.0f, 0.0f);
	hpBar->transform->Scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
	hpBar->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	sprintf(hpBar->GetTag(), "HP Bar");
	hpBar->SetBarType(BAR::RIGHT);
	player->hp->SetBarController(&hpBar->amount);

	postureBarBackground->sprite->SetSize(D3DXVECTOR2(110.0f, 18.0f));
	postureBarBackground->sprite->SetTexture("asset\\texture\\postureBar.png");
	postureBarBackground->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	postureBarBackground->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	postureBarBackground->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	postureBarBackground2->sprite->SetSize(D3DXVECTOR2(110.0f, 18.0f));
	postureBarBackground2->sprite->SetTexture("asset\\texture\\postureBar.png");
	postureBarBackground2->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	postureBarBackground2->transform->Scale = D3DXVECTOR3(1.05f, 1.2f, 1.2f);
	postureBarBackground2->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	hpBarBackground->sprite->SetSize(D3DXVECTOR2(160.0f, 20.0f));
	hpBarBackground->sprite->SetTexture("asset\\texture\\Box.png");
	hpBarBackground->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT - 50.0f, 0.0f);
	hpBarBackground->transform->Scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
	hpBarBackground->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	heart->sprite->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	heart->sprite->SetTexture("asset\\texture\\heart.png");
	heart->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 420.0f, SCREEN_HEIGHT - 50.0f, 0.0f);
	heart->transform->Scale = D3DXVECTOR3(0.4f, 0.4f, 0.4f);

	for (int i = 0; i < 2; i++)
	{
		pauseText[i]->sprite->SetSize(D3DXVECTOR2(140.0f, 20.0f));
		pauseText[i]->sprite->SetTexture("asset\\texture\\paused.png");
		pauseText[i]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
		pauseText[i]->transform->Scale = D3DXVECTOR3(1.0f + 0.05f*i, 1.0f + 0.15f*i, 1.0f);
		pauseText[i]->SetColor(D3DXCOLOR(1 - i, 1 - i, 1 - i, 1.0f));
		pauseText[i]->SetUse(false);
	}

	pauseText[2]->sprite->SetSize(D3DXVECTOR2(25.0f, 25.0f));
	pauseText[2]->sprite->SetTexture("asset\\texture\\L_key.png");
	pauseText[2]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH - 175.0f, 30.0f, 0.0f);
	pauseText[2]->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pauseText[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pauseText[2]->SetUse(false);

	pauseText[3]->sprite->SetSize(D3DXVECTOR2(64.0f, 16.0f));
	pauseText[3]->sprite->SetTexture("asset\\texture\\back.png");
	pauseText[3]->transform->Position = D3DXVECTOR3(SCREEN_WIDTH - 70.0f, 30.0f, 0.0f);
	pauseText[3]->transform->Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pauseText[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pauseText[3]->SetUse(false);

	Collision.Init();

	Starter();

	int ps = 5, bl = ENEMY_MAX;
	if (tutorial == true) { ps = 1; bl = ENEMY_MAX / 6; }

	for (int i = 0; i < ps; i++) { enemyDestroyEffect.push_back(AddGameObject<ENEMYDESTROY_EFFECT>(BILLBOARD_LAYER)); }
	for (int i = 0; i < bl; i++) { parryEffect.push_back(AddGameObject<SPARK>(BILLBOARD_LAYER)); }
	for (int i = 0; i < bl; i++) { attackEffect.push_back(AddGameObject<ATTACKEFFECT>(BILLBOARD_LAYER)); }
	for (int i = 0; i < bl; i++) { damageEffect.push_back(AddGameObject<DAMAGEEFFECT>(BILLBOARD_LAYER)); }

	//Audio
	SoundReader::GetReadSound(SoundReader::GAME)->Play(true, 0.2f);
	//SoundReader::GetReadSound(SoundReader::GAME_START)->Play(false, 0.2f);
}

void GAME_SCENE::Update()
{	
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		if (paused == false) { paused = true; SoundReader::GetReadSound(SoundReader::PAUSE_IN)->Play(false, 0.15f);}
		else { paused = false; SoundReader::GetReadSound(SoundReader::PAUSE_OUT)->Play(false, 0.15f);}
	}

	if (paused == true)
	{
		SoundReader::GetReadSound(SoundReader::GAME)->SetVolume(0.1f);
		for (int i = 0; i < 4; i++) { pauseText[i]->SetUse(true); }
		if (Input::GetKeyTrigger('L')) { Manager::GetScene()->SetEnd();  SoundReader::GetReadSound(SoundReader::BUTTON)->Play(false, 0.2f);}
	}
	else
	{
		SoundReader::GetReadSound(SoundReader::GAME)->SetVolume(0.2f);
		for (int i = 0; i < 4; i++) { pauseText[i]->SetUse(false); }
	}

	if (End == true && Fade->GetFadeIn() == false)
	{
		if (Fade->FadeOut() == false)
		{
			if (tutorial == false)
			{
				if (player->hp->GetHP() > 0) { score->SetUse(false); Manager::SetScene<TITLE_SCENE>(); }
				else { Manager::SetScene<RESULT_SCENE>(); }
			}
			else { Manager::SetScene<TITLE_SCENE>(); }
		}
	}

#ifdef DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], " | playerModel Rotation.y : %.2f", &playerModel->transform->Rotation.y);
#endif
}