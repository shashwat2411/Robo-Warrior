#include "component.h"

void Plane::Start()
{
	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\kizuna.jpg",
		NULL,
		NULL,
		&Texture,
		NULL);
	assert(Texture);

	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Size = D3DXVECTOR2(10.0f, 10.0f);
	TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	collisionObject = nullptr;

}

void Plane::End()
{
	if (VertexBuffer != nullptr) { VertexBuffer->Release(); }
	if (Texture != nullptr) { Texture->Release(); }
}

void Plane::Update()
{
	//Collision
	if (collisionObject != nullptr)
	{
		if (collisionObject->GetComponent<Rigidbody>() != nullptr)
		{
			D3DXVECTOR3 speed = collisionObject->rigidbody->Speed;
			D3DXVECTOR3 pos = collisionObject->transform->Position;
			D3DXVECTOR3 fieldPos = gameObject->transform->Position;

			pos -= fieldPos;
			float distance = D3DXVec3Dot(&Normal, &pos);

			if (distance < 1.0f)
			{
				collisionObject->transform->Position += (Normal * (1.0f - distance));

				D3DXVECTOR3 ref;
				ref = speed - 2 * D3DXVec3Dot(&speed, &Normal) * Normal;
				D3DXVec3Normalize(&ref, &ref);
				collisionObject->rigidbody->Speed = ref * 0.02f;
			}
		}
	}
}

void Plane::Draw()
{
	Normal.x = gameObject->GetWorldMatrix()._21;
	Normal.y = gameObject->GetWorldMatrix()._22;
	Normal.z = gameObject->GetWorldMatrix()._23;

	VERTEX_3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-Size.x, 0.0f, Size.y);
	vertex[0].Normal = Normal;
	vertex[0].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(Size.x, 0.0f, Size.y);
	vertex[1].Normal = Normal;
	vertex[1].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[1].TexCoord = D3DXVECTOR2(TexCoord.x, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-Size.x, 0.0f, -Size.y);
	vertex[2].Normal = Normal;
	vertex[2].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, TexCoord.y);

	vertex[3].Position = D3DXVECTOR3(Size.x, 0.0f, -Size.y);
	vertex[3].Normal = Normal;
	vertex[3].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[3].TexCoord = D3DXVECTOR2(TexCoord.x, TexCoord.y);

	//���_�o�b�t�@�[����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(gameObject->GetVertexLayout());

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(gameObject->GetVertexShader(), NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(gameObject->GetPixelShader(), NULL, 0);

	////�}�g���N�X�ݒ�
	D3DXVECTOR3 Position = gameObject->transform->Position;
	D3DXVECTOR3 Rotation = gameObject->transform->Rotation;
	D3DXVECTOR3 Scale = gameObject->transform->Scale;

	D3DXMATRIX world, scale, rotation, transform;

	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotation, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&transform, Position.x, Position.y, Position.z);
	world = scale * rotation * transform;
	Renderer::SetWorldMatrix(&world);

	//���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���ݒ�
	Renderer::GetDeviceContext()->Draw(4, 0);
}
