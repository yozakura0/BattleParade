#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;

class Coin;

class CoinAIplayerThird : public IGameObject
{
public:
	CoinAIplayerThird();
	~CoinAIplayerThird();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//物理判定
	CharacterController thirdAIController;
	//当たり判定
	PhysicsGhostObject thirdAIGhostObject;

	//敵キャラを表示するモデルレンダー
	ModelRender thirdCoinAIRender;

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
	bool thirdAITackleFlag = false;
	//AI3の得点
	int AI3Point;
	//場所
	Vector3 thirdAIPos;
private:
	//移動速度
	Vector3 thirdAIMoveSpeed;
	//1フレーム前の座標
	Vector3 thirdAIdifference;
	//キャラが気絶しているか
	bool thirdAIStunFlag = false;
	//気絶している時間
	int thirdAIStunTime;
	//プレイヤーにタックルされたフラグ
	bool receiveTacklePto3 = false;
	//AI1にタックルされたフラグ
	bool receiveTackle1to3 = false;
	//AI2にタックルされたフラグ
	bool receiveTackle2to3 = false;
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
	CoinAIplayerSecond* m_coinAI2;

	Coin* m_coin;
};

