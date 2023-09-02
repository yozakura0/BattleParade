#pragma once
#include "CoinNumbers.h"

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;
class CoinGameResult;
class CoinUI;
class CoinGameResult;

class Coin : public IGameObject
{
public:
	Coin();
	~Coin();

	void Update();
	void Render(RenderContext& rc);
	int CoinGet(Vector3 pos);
	void ShowCoin();
	void gameClear();

	//ステージを表示するモデルレンダー
	ModelRender stageRender;
	//コインを表示するモデルレンダー
	ModelRender coinRender[coinCount];
	//ステージの物理判定
	PhysicsStaticObject stageObject;
	//時間の表示
	FontRender finishRender;

	//存在しているコインの座標
	Vector3 coinPos[coinCount];
	//ゲームの時間
	int gametime;
	//ゲームを閉じるフラグ
	bool gameEndFlag = false;
private:
	//Vector3 cameraPos = { 0.0f, 12000.0f, 1.0f };
	//コインの出現する全座標
	Vector3 allCoinPos[276];
	//回転
	Quaternion rotation;
	//コインの全座標を登録する時に配列を進めるための変数
	int coinListCount = 0;
	//距離
	float direction;
	//フレームの進み具合を保存する変数
	int timeFrameCount;
	//乱数が被っていないかのフラグ
	bool noSameFrag;
	//乱数で選ばれた値を受け取る変数
	int selectCount;
	//出てくるコインの番号を覚える配列
	int countSaveList[coinCount];
	//コインを表示するフラグ
	bool showCoinFlag;
	//ゲーム終了後の待ち時間
	int gameAfterTimer;

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;
	CoinUI* m_coinUI;
	CoinGameResult* m_coinGameRes;
};

