#include "component.h"
#include "manager.h"
#include "scene.h"

void Sprite::Start()
{
	ignorePause = true;

	animate = false;
	elementsX = 1;
	elementsY = 1;

	barOffsetRight = 0.0f;
	barOffsetLeft = 0.0f;

	Count = 0;

	VERTEX_3D vertex[4];
	//���_�o�b�t�@�[����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\kizuna.jpg",
		NULL,
		NULL,
		&Texture,
		NULL);
	assert(Texture);

	gameObject->SetDepth(false);
	Size = D3DXVECTOR2(100.0f, 100.0f);
	TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
void Sprite::End()
{
	VertexBuffer->Release();
	Texture->Release();
}
void Sprite::Update() 
{
	if (Count >= elementsX * elementsY)
	{
		Count = 0;
	}
}
void Sprite::Draw()
{
	float x = 0.0f;
	float y = 0.0f;
	D3DXVECTOR2 offset = D3DXVECTOR2(1.0f, 1.0f);
	if (animate == true)
	{
		offset = D3DXVECTOR2((1.0f / (float)elementsX), (1.0f / (float)elementsY));
		x = (Count % elementsX) * offset.x;
		y = (Count / elementsX) * offset.y;
	}

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-Size.x * gameObject->transform->Scale.x + barOffsetLeft, -Size.y * gameObject->transform->Scale.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(Size.x * gameObject->transform->Scale.x + barOffsetRight, -Size.y * gameObject->transform->Scale.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[1].TexCoord = D3DXVECTOR2(x + offset.x, y);

	vertex[2].Position = D3DXVECTOR3(-Size.x * gameObject->transform->Scale.x + barOffsetLeft, Size.y * gameObject->transform->Scale.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[2].TexCoord = D3DXVECTOR2(x, y + offset.y);

	vertex[3].Position = D3DXVECTOR3(Size.x * gameObject->transform->Scale.x + barOffsetRight, Size.y * gameObject->transform->Scale.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[3].TexCoord = D3DXVECTOR2(x + offset.x, y + offset.y);

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	float rad = D3DXToRadian(gameObject->transform->Rotation.z);

	for (int i = 0; i < 4; i++)
	{
		float X = ((vertex[i].Position.x * cosf(rad)) - (vertex[i].Position.y * sinf(rad)));
		float Y = ((vertex[i].Position.x * sinf(rad)) + (vertex[i].Position.y * cosf(rad)));
		vertex[i].Position.x = gameObject->transform->Position.x + X;
		vertex[i].Position.y = gameObject->transform->Position.y + Y;
		vertex[i].Position.z = 0.0f;
	}

	//���_�o�b�t�@�[����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);


	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(gameObject->GetVertexLayout());

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(gameObject->GetVertexShader(), NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(gameObject->GetPixelShader(), NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT Offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &Offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color;
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���ݒ�
	Renderer::GetDeviceContext()->Draw(4, 0);

	//Manager::GetScene(GAME)->FindGameObject<CAMERA>(CAMERA_LAYER)->GetComponent<Camera>()->Draw();
}