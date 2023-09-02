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

	//時間の表示
	FontRender timeRender;
	//各キャラの得点の表示
	FontRender pointRender[charaCount];
	//UI画像の表示
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

