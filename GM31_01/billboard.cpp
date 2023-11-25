#include "component.h"

void Billboard::Start()
{
	animate = false;
	elementsX = 1;
	elementsY = 1;

	Count = 0;
	float x = Count % elementsX * (1.0f / (float)elementsX);
	float y = Count / elementsY * (1.0f / (float)elementsX);
	D3DXVECTOR2 offset = D3DXVECTOR2((1.0f / (float)elementsX), (1.0f / (float)elementsY));

	VERTEX_3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
	vertex[0].Normal = Normal;
	vertex[0].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(Size.x, Size.y, 0.0f);
	vertex[1].Normal = Normal;
	vertex[1].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[1].TexCoord = D3DXVECTOR2(x + offset.x, y);

	vertex[2].Position = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
	vertex[2].Normal = Normal;
	vertex[2].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[2].TexCoord = D3DXVECTOR2(x, y + offset.y);

	vertex[3].Position = D3DXVECTOR3(Size.x, -Size.y, 0.0f);
	vertex[3].Normal = Normal;
	vertex[3].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[3].TexCoord = D3DXVECTOR2(x + offset.x, y + offset.y);


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
	

	gameObject->SetBillboard(true);
	Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	Size = D3DXVECTOR2(10.0f, 10.0f);
	TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	collisionObject = nullptr;


}

void Billboard::End()
{
	if (VertexBuffer != nullptr) { VertexBuffer->Release(); }
	if (Texture != nullptr) { Texture->Release(); }
}

void Billboard::Update()
{
	//Count++;
	//if (Count >= 16)
	//{
	//	Count = 0;
	//	gameObject->Destroy(true);
	//	return;
	//}
}

void Billboard::Draw()
{
	Normal.x = gameObject->GetWorldMatrix()._21;
	Normal.y = gameObject->GetWorldMatrix()._22;
	Normal.z = gameObject->GetWorldMatrix()._23;

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
	vertex[0].Position = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
	vertex[0].Normal = Normal;
	vertex[0].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(Size.x, Size.y, 0.0f);
	vertex[1].Normal = Normal;
	vertex[1].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[1].TexCoord = D3DXVECTOR2(x + offset.x, y);

	vertex[2].Position = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
	vertex[2].Normal = Normal;
	vertex[2].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[2].TexCoord = D3DXVECTOR2(x, y + offset.y);

	vertex[3].Position = D3DXVECTOR3(Size.x, -Size.y, 0.0f);
	vertex[3].Normal = Normal;
	vertex[3].Diffuse = (D3DXVECTOR4)gameObject->GetColor();
	vertex[3].TexCoord = D3DXVECTOR2(x + offset.x, y + offset.y);

	if (flip == true)
	{
		vertex[0].TexCoord = D3DXVECTOR2(x + offset.x, y);
		vertex[1].TexCoord = D3DXVECTOR2(x, y);
		vertex[2].TexCoord = D3DXVECTOR2(x + offset.x, y + offset.y);
		vertex[3].TexCoord = D3DXVECTOR2(x, y + offset.y);
	}

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	//���_�o�b�t�@�[����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(gameObject->GetVertexLayout());

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(gameObject->GetVertexShader(), NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(gameObject->GetPixelShader(), NULL, 0);

	//Animation


	//���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT Offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &Offset);

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
