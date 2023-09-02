#pragma once
#include "CoinNumbers.h"

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class CoinGameResult : public IGameObject
{
public:
	CoinGameResult();
	~CoinGameResult();
	void Update();
	void ResultSlide(int number);
	void ResultSlideManage();
	void Render(RenderContext& rc);

	//結果画面の背景の表示
	SpriteRender resultBackRender;
	//キャラの順位の背景の表示
	SpriteRender pointBackRender[charaCount];
	//得点の表示
	FontRender pointRender[charaCount];

private:
	int charaPoints[2][charaCount];		//各キャラの得点とキャラ
	Vector2 resultRankPos[charaCount];	//ランキングの表示場所
	Vector3 pointBackPos[charaCount];	//得点の背景の表示場所
	bool slideFinishFlag[charaCount];	//横移動をしきったかどうかのフラグ

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;
};

