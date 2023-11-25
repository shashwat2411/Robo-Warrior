#include "baseobjects.h"
#include "manager.h"
#include "scene.h"

void SKYDOME::Start()
{
	Init();

	AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\skyDome.obj");
	transform->Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "shader\\unlitTexturePS.cso");

	transform->Position.y = -3.0f;
}

void SKYDOME::Update()
{
	SCENE* scene = Manager::GetScene();
	if (scene->GetPlayer() != nullptr)
	{
		D3DXVECTOR3 pos = scene->GetPlayer()->transform->Position;
		transform->Position.x = pos.x;
		transform->Position.z = pos.z;

		transform->Rotation.y += 0.04f;
	}
}