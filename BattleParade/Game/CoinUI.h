#pragma once
#include "CoinNumbers.h"

class Coin;
class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class CoinUI : public IGameObject
{
public:
	CoinUI();
	~CoinUI();
	void Update();
	void Render(RenderContext& rc);

	//���Ԃ̕\��
	FontRender timeRender;
	//�e�L�����̓��_�̕\��
	FontRender pointRender[charaCount];
	//UI�摜�̕\��
	SpriteRender UIbackRender;

private:
	int charaPoint;
	int AI1Point;
	int AI2Point;
	int AI3Point;
	int gametime;

	Coin* m_coin;
	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;
};

