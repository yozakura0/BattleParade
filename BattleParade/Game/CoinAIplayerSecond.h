#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerThird;

class Coin;

class CoinAIplayerSecond : public IGameObject
{
public:
	CoinAIplayerSecond();
	~CoinAIplayerSecond();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//物理判定
	CharacterController secondAIController;
	//当たり判定
	PhysicsGhostObject secondAIGhostObject;

	//敵キャラを表示するモデルレンダー
	ModelRender secondCoinAIRender;

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。

	//タックルしているかの判定
	bool secondAITackleFlag = false;
	//AI2の得点
	int AI2Point;
	//場所
	Vector3 secondAIPos;
private:
	//移動速度
	Vector3 secondAIMoveSpeed;
	//1フレーム前の座標
	Vector3 secondAIdifference;
	//キャラが気絶しているか
	bool secondAIStunFlag = false;
	//気絶している時間
	int secondAIStunTime;
	//プレイヤーにタックルされたフラグ
	bool receiveTacklePto2 = false;
	//AI1にタックルされたフラグ
	bool receiveTackle1to2 = false;
	//AI3にタックルされたフラグ
	bool receiveTackle3to2 = false;
	//距離
	float direction;
	//無回転
	Quaternion noneRotation;
	//タックルを受けて飛んでいく向き
	Vector3 receiveTackleMoveVec;
	//タックルを受けて飛んでいく向きを決定するかのフラグ
	bool receiveTackleVecFlag;

	CoinAIActs* coinAIActs;

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerThird* m_coinAI3;

	Coin* m_coin;
};

