#include "component.h"
#include "manager.h"
#include "scene.h"

void SphereCollider::Start()
{
	//if (gameObject->GetComponent<Rigidbody>() == nullptr)
	//{
	//	gameObject->RemoveComponent<SphereCollider>();
	//	return;
	//}

	collider = Manager::GetScene()->AddGameObject<EMPTYOBJECT>(COLLIDER_LAYER);
	collider->SetParent(gameObject);
	collider->AddComponent<ModelComponent>()->m_Model->Load("asset\\model\\ColliderModel.obj");
	collider->GetComponent<ModelComponent>()->SetCollider(true);
	CollisionSize = 1.0f;
	CollisionScale = D3DXVECTOR3(1.0f / gameObject->transform->Scale.x, 1.0f / gameObject->transform->Scale.y, 1.0f / gameObject->transform->Scale.z);
	CollisionPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	multiple = true;
	
	collider->transform->Scale = CollisionScale * CollisionSize;
	collider->transform->Position = CollisionPosition;

	collider->SetUse(false);
	dynamic = false;

#ifdef DEBUG
	m = gameObject->AddComponent<ModelComponent>();
	m->m_Model->Load("asset\\model\\ColliderModel.obj");
	m->SetCollider(true);
#endif
}

void SphereCollider::End()
{
	//collider->UnInitialize();
}

void SphereCollider::Update()
{
	collider->transform->Scale = CollisionScale * CollisionSize;
	collider->Update();
}

void SphereCollider::Draw()
{
	//collider->Draw();
}

//void SphereCollider::DrawCollider()
//{
//#ifdef COLLIDERS
//	//入力レイアウト設定
//	Renderer::GetDeviceContext()->IASetInputLayout(gameObject->GetVertexLayout());
//
//	//シェーダー設定
//	Renderer::GetDeviceContext()->VSSetShader(gameObject->GetVertexShader(), NULL, 0);
//	Renderer::GetDeviceContext()->PSSetShader(gameObject->GetPixelShader(), NULL, 0);
//
//	D3DXMATRIX ScaleMatrix;
//	D3DXMATRIX RotationMatrix;
//	D3DXMATRIX TransformMatrix;
//	D3DXMATRIX WorldMatrix;
//
//	D3DXMatrixScaling(&ScaleMatrix, CollisionScale.x * CollisionSize, CollisionScale.y * CollisionSize, CollisionScale.z * CollisionSize);
//	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f));
//	D3DXMatrixTranslation(&TransformMatrix, CollisionPosition.x, CollisionPosition.y, CollisionPosition.z);
//	D3DXMatrixMultiply(&WorldMatrix, &ScaleMatrix, &RotationMatrix);  //World = Scaling * Rotation
//	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransformMatrix); //World = World * Translation
//	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &gameObject->GetWorldMatrix()); //World = World * Translation
//
//	Renderer::SetWorldMatrix(&WorldMatrix);
//	m->m_Model->Draw();
//#endif
//}
