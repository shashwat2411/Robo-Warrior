#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "customScenes.h"
#include "component.h"
#include "soundReader.h"
#include "modelReader.h"

SCENE* Manager::Scene{};	//staticメンバ変数は再宣言が必要
SCENE* Manager::DontDestroyOnLoad{};	//staticメンバ変数は再宣言が必要
Model ModelReader::Models[ModelReader::READ_MODEL_MAX]{};
Audio SoundReader::Audios[SoundReader::READ_SOUND_MAX]{};

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();
	SoundReader::ReadSound();
	ModelReader::ReadModel();

	DontDestroyOnLoad = new EMPTY_SCENE();
	DontDestroyOnLoad->InitBefore();
	DontDestroyOnLoad->Init();

	SetScene<TITLE_SCENE>();
	//SetScene<WORKSPACE_SCENE>();
}

void Manager::Uninit()
{
	Scene->Uninit();
	DontDestroyOnLoad->Uninit();

	ModelReader::UnReadModel();
	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	Scene->UpdateBefore();
	Scene->Update();

	DontDestroyOnLoad->UpdateBefore();
	DontDestroyOnLoad->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	Scene->Draw();
	DontDestroyOnLoad->Draw();

	Renderer::End();
}
