#include "baseobjects.h"

void FADE::Init()
{
	Initialize();
	Depth = false;
	image = AddComponent<Sprite>();
	image->SetTexture("asset\\texture\\fade.png");
	image->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	fadeIn = true;
	fadeOut = true;
	alpha = 1.0f;
	speed = 0.05f;
	
	ignorePause = true;
}

void FADE::Start()
{
	Init();
}

void FADE::Update()
{
	if (fadeIn == true)
	{
		if (alpha > 0.0f) { alpha -= speed; }
		else { alpha = 0.0f; fadeIn = false; }
	}

	//if (fadeOut == true)
	//{
	//	if (alpha <= 1.0f) { alpha += 0.05f; }
	//	else { alpha = 1.0f; fadeOut = false; }
	//}

	image->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

bool FADE::FadeOut()
{
	fadeOut = true;
	if (alpha <= 1.0f) { alpha += speed; }
	else { alpha = 1.0f; fadeOut = false; }
	return fadeOut;
}