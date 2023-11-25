#include "scene.h"
#include "manager.h"
#include "soundReader.h"

void SCENE::InitBefore()
{
	//GAMEOBJECT
	MainCamera = AddGameObject<CAMERA>(CAMERA_LAYER);

	//UI
	Fade = Manager::GetDontDestroyOnLoadScene()->FindGameObject<FADE>();
	if (Fade == nullptr) { Fade = Manager::GetDontDestroyOnLoadScene()->AddGameObject<FADE>(FADE_LAYER); }

	//eŽqŠÖŒWÝ’è

	Fade->SetFadeIn();

	Collision.Init();
	End = false;
	paused = false;
}

void SCENE::Uninit()
{
	for (int i = 0; i < MAX_LAYER; i++)
	{
		for (auto var : GameObjects[i])
		{
			var->UnInitialize();
			delete var;
		}

		GameObjects[i].clear();
	}
	SoundReader::StopAllSound();
}

void SCENE::UpdateBefore()
{
	for (int i = 0; i < MAX_LAYER; i++)
	{
		for (auto var : GameObjects[i])
		{
			if (paused == false || var->GetIgnorePause() == true)
			{
				if (var->GetUse() == true)
				{
					var->Update();
				}
			}
		}
		GameObjects[i].remove_if([](GAMEOBJECT* object) {return object->Remove(); });
	}
	if (paused == false) { Collision.Update(); }

}

void SCENE::Draw()
{
	for (int i = 0; i < MAX_LAYER; i++)
	{
		for (auto var : GameObjects[i])
		{
			var->Draw();
		}
		//for (auto var : GameObjects[i])
		//{
		//	if (var->GetComponent<SphereCollider>() != nullptr)
		//	{
		//		var->GetComponent<SphereCollider>()->DrawCollider();
		//	}
		//}
	}
}