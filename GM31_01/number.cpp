#include "component.h"
#include "baseobjects.h"

void Number::Start()
{
	digits = 3;
	number = 0;
	for (int i = 0; i < digits; i++)
	{
		auto b = new DIGIT();
		b->Start();
		b->GetComponent<Sprite>()->elementsX = 5;
		b->GetComponent<Sprite>()->elementsY = 5;
		b->GetComponent<Sprite>()->animate = true;
		numbers.push_back(b);
	}

}

void Number::End()
{
	for (auto num : numbers)
	{
		num->UnInitialize();
		delete num;
	}
}

void Number::Update()
{
	int i = digits / 2;
	int c = 0;
	int d = digits;

	for (auto num : numbers)
	{
		num->transform->Scale = gameObject->transform->Scale;

		d--;
		int dig = number % (int)pow(10, digits - d) / (int)pow(10, digits - (d + 1));
		num->GetComponent<Sprite>()->Count = dig;

		num->transform->Position.x = gameObject->transform->Position.x + i * num->GetComponent<Sprite>()->GetSize().x * 1.3f * gameObject->transform->Scale.x;
		num->transform->Position.y = gameObject->transform->Position.y;
		if (num->GetComponent<Sprite>()->Count >= 10) { num->GetComponent<Sprite>()->Count = 0; }
		i--;
		c++;
	}
}

void Number::Draw()
{
	for (auto num : numbers)
	{
		num->Draw();
	}
}

void Number::SetDigits(int num)
{
	int diff = num - digits;
	while (diff > 0)
	{
		auto b = new DIGIT();
		b->Start();
		b->GetComponent<Sprite>()->elementsX = 5;
		b->GetComponent<Sprite>()->elementsY = 5;
		b->GetComponent<Sprite>()->animate = true;
		numbers.push_back(b);
		diff--;
		digits++;
	}
	while (diff < 0)
	{
		numbers.back()->UnInitialize();
		delete numbers.back();
		numbers.pop_back();
		diff++;
		digits--;
	}
}

void Number::SetNumberColor(D3DXCOLOR value)
{
	for (auto num : numbers)
	{
		num->SetColor(value);
	}
}
