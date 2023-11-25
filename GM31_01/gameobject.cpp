#include "gameobject.h"
#include "component.h"
#include "manager.h"
#include "scene.h"
#include "prefab.h"

void GAMEOBJECT::Initialize()
{
	use = true;

	transform = this->AddComponent<Transform>();
	shadow = nullptr;
	Parent = nullptr;

	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "shader\\vertexLightingPS.cso");

	if (Parent != nullptr) { D3DXVec3TransformCoord(&transform->GlobalPosition, &transform->Position, &Parent->GetWorldMatrix()); }
	else { transform->GlobalPosition = transform->Position; }

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = Color;
}

void GAMEOBJECT::UnInitialize()
{
	for (auto com : ComponentList)
	{
		com->End();
		delete com;
	}

	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
}

void GAMEOBJECT::Draw()
{
	if (use == true)
	{
		auto buff = ComponentList;
		for (auto com : buff)
		{
			if (Manager::GetScene()->GetPaused() == false || com->GetIgnorePause() == true)
			{
				com->Update();
			}
		}

		if (Depth == true)
		{
			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

			//シェーダー設定
			Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

			D3DXVECTOR3 Position = GetComponent<Transform>()->Position;
			D3DXVECTOR3 Rotation = GetComponent<Transform>()->Rotation;
			D3DXVECTOR3 Scale = GetComponent<Transform>()->Scale;

			//マトリクス設定
			D3DXMatrixScaling(&ScaleMatrix, Scale.x, Scale.y, Scale.z);

			if (GetComponent<Rigidbody>() != nullptr)
			{
				if (GetComponent<Rigidbody>()->FollowTarget != nullptr) {}
				else { D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z)); }
			}
			else if (faceInDirection == true) {}
			else { D3DXMatrixRotationYawPitchRoll(&RotationMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z)); }

			D3DXMATRIX view = Manager::GetScene()->GetCamera()->GetComponent<Camera>()->GetViewMatrix();
			D3DXMATRIX invView;
			D3DXMatrixInverse(&invView, NULL, &view);
			invView._41 = 0.0f;
			invView._42 = 0.0f;
			invView._43 = 0.0f;

			D3DXMatrixTranslation(&TransformMatrix, Position.x, Position.y, Position.z);
			if (billboard == true) { D3DXMatrixMultiply(&WorldMatrix[RingCounter], &ScaleMatrix, /*&RotationMatrix*/&invView); }  //World = Scaling * Rotation
			else { D3DXMatrixMultiply(&WorldMatrix[RingCounter], &ScaleMatrix, &RotationMatrix); }
			D3DXMatrixMultiply(&WorldMatrix[RingCounter], &WorldMatrix[RingCounter], &TransformMatrix); //World = World * Translation

			if (Parent != nullptr)
			{
				D3DXVec3TransformCoord(&transform->GlobalPosition, &transform->Position, &Parent->GetWorldMatrix()); //Global Position
				D3DXMatrixMultiply(&WorldMatrix[RingCounter], &WorldMatrix[RingCounter], &Parent->GetWorldMatrix()); //World = World * Parent->World
			}
			else { transform->GlobalPosition = transform->Position; }

			if (GetComponent<Afterimage>() != nullptr)
			{
				for (int i = RingCounter, n = 0; i < RingCounter + GetComponent<Afterimage>()->imageNum; i++, n++)
				{
					int index = RingCounter - (n * 16);
					if (index < 0) { index += MAX_AFTERIMAGES; }

					Renderer::SetWorldMatrix(&WorldMatrix[index]);
					if (GetComponent<ModelComponent>() != nullptr)
					{
						GetComponent<ModelComponent>()->Draw();
					}
					//for (auto child : Children)
					//{
					//	if (child->GetComponent<ModelComponent>() != nullptr)
					//	{
					//		if (child->GetComponent<ModelComponent>()->GetCollider() == false)
					//		{
					//			//child->GetComponent<ModelComponent>()->Draw();
					//		}
					//	}
					//}
				}
			}
			else
			{
				Renderer::SetWorldMatrix(&WorldMatrix[0]);
			}

		}

		//SetMaterial(&Material);

		for (auto com : ComponentList)
		{
			com->Draw();
		}
	}
}

void GAMEOBJECT::Destroy(bool value)
{
	destroy = value;
	for (auto child : Children) { child->Destroy(value); }
	if (shadow != nullptr) { shadow->shadow->Destroy(); }
}

bool GAMEOBJECT::Remove()
{
	if (destroy == true)
	{
		if (rigidbody != nullptr)
		{
			this->RemoveComponent<Rigidbody>();
		}
		UnInitialize();
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}

void GAMEOBJECT::FaceTowards(GAMEOBJECT* object)
{
	//Y-Axis
	float X = object->transform->Position.x;
	float Z = object->transform->Position.z;
	float corrector = 180;
	float height = (Z - transform->Position.z);
	float base = (X - transform->Position.x);

	if (object->transform->Position.z < transform->Position.z) { corrector = 180; }
	else { corrector = 0; }

	transform->Rotation.y = (D3DXToDegree(atanf(base / height))) + corrector;
}

void GAMEOBJECT::FaceTowards(D3DXVECTOR3 value)
{
	float X = value.x;
	float Z = value.z;
	float corrector = 180;
	float height = (Z - transform->Position.z);
	float base = (X - transform->Position.x);

	if (value.z < 0) { corrector = 180; }
	else { corrector = 0; }

	transform->Rotation.y = (D3DXToDegree(atanf(base / height))) + corrector;
}
void GAMEOBJECT::FaceTowardsXYZ(GAMEOBJECT* object)
{
	D3DXVECTOR3 X;
	D3DXVECTOR3 Y(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 Z = object->transform->Position;

	Z -= transform->Position;
	D3DXVec3Normalize(&Z, &Z);

	D3DXVec3Cross(&X, &Y, &Z);
	D3DXVec3Normalize(&X, &X);

	D3DXVec3Cross(&Y, &Z, &X);
	D3DXVec3Normalize(&Y, &Y);

	D3DXMatrixIdentity(&RotationMatrix);
	RotationMatrix._11 = X.x;
	RotationMatrix._12 = X.y;
	RotationMatrix._13 = X.z;

	RotationMatrix._21 = Y.x;
	RotationMatrix._22 = Y.y;
	RotationMatrix._23 = Y.z;

	RotationMatrix._31 = Z.x;
	RotationMatrix._32 = Z.y;
	RotationMatrix._33 = Z.z;
}

float GAMEOBJECT::FaceInDirection()
{
	if (rigidbody == nullptr)
	{
		return 0.0f;
	}
	float corrector = 180;
	float height;
	float base;

	//Y-Axis
	corrector = 180;
	height = rigidbody->Speed.z;//(Z + rigidbody->Speed.z);
	base =	rigidbody->Speed.x;//(X + rigidbody->Speed.x);

	//height = Direction.z;
	//base = Direction.x;
	if (height < 0.0f) { corrector = 180; }
	else { corrector = 0; }

	return (D3DXToDegree(atanf(base / height))) + corrector;

	////X-Axis
	//corrector = 180;
	//height = rigidbody->Speed.y;//(Z + rigidbody->Speed.z);
	//base = rigidbody->Speed.z;//(X + rigidbody->Speed.x);

	//if (height < 0.0f) { corrector = 180; }
	//else { corrector = 0; }

	//transform->Rotation.x = (D3DXToDegree(atanf(base / height))) + corrector;

	////Z-Axis
	//corrector = 180;
	//height = rigidbody->Speed.y;//(Z + rigidbody->Speed.z);
	//base = rigidbody->Speed.x;//(X + rigidbody->Speed.x);

	//if (height < 0.0f) { corrector = 180; }
	//else { corrector = 0; }

	//transform->Rotation.z = (D3DXToDegree(atanf(base / height))) + corrector;
}
D3DXMATRIX GAMEOBJECT::FaceInDirectionXYZ()
{
	if (rigidbody == nullptr)
	{
		return RotationMatrix;
	}

	faceInDirection = true;

	D3DXVECTOR3 X;
	D3DXVECTOR3 Y(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 Z = rigidbody->Speed;

	Z -= transform->Position;
	D3DXVec3Normalize(&Z, &Z);

	D3DXVec3Cross(&X, &Y, &Z);
	D3DXVec3Normalize(&X, &X);

	D3DXVec3Cross(&Y, &Z, &X);
	D3DXVec3Normalize(&Y, &Y);

	D3DXMATRIX rot;

	rot._11 = X.x;
	rot._12 = X.y;
	rot._13 = X.z;
	
	rot._21 = Y.x;
	rot._22 = Y.y;
	rot._23 = Y.z;
	
	rot._31 = Z.x;
	rot._32 = Z.y;
	rot._33 = Z.z;

	return rot;
}

D3DXVECTOR3 GAMEOBJECT::GetForwardDirection()
{
	D3DXMATRIX rot;
	D3DXMatrixRotationYawPitchRoll(&rot, D3DXToRadian(transform->Rotation.y), D3DXToRadian(transform->Rotation.x), D3DXToRadian(transform->Rotation.z));

	D3DXVECTOR3 returner;
	returner.x = rot._31;
	returner.y = rot._32;
	returner.z = rot._33;

	return returner;
}

D3DXVECTOR3 GAMEOBJECT::GetRightDirection()
{
	D3DXMATRIX rot;
	D3DXMatrixRotationYawPitchRoll(&rot, D3DXToRadian(transform->Rotation.y), D3DXToRadian(transform->Rotation.x), D3DXToRadian(transform->Rotation.z));

	D3DXVECTOR3 returner;
	returner.x = rot._11;
	returner.y = rot._12;
	returner.z = rot._13;

	return returner;
}

float GAMEOBJECT::DistanceFrom(GAMEOBJECT* from)
{
	D3DXVECTOR3 distance;
	distance = this->transform->Position - from->transform->Position;
	float finalDistance = D3DXVec3Length(&distance);
	return  finalDistance;
}
float GAMEOBJECT::DistanceFromWithY0(GAMEOBJECT* from)
{
	D3DXVECTOR3 distance;
	distance = this->transform->Position - from->transform->Position;
	distance.y = 0.0f;
	float finalDistance = D3DXVec3Length(&distance);
	return  finalDistance;
}