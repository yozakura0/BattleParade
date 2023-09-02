#pragma once

class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class Coin;

class CoinPlayer : public IGameObject
{
public:
	CoinPlayer();
	~CoinPlayer();
	void Update();
	void Move();
	void StateManagement();
	void Animation();
	void ReceiveTackle();
	void PointManager();
	void Render(RenderContext& rc);

	//キャラのモデルレンダー
	ModelRender charaRender;
	//キャラの物理判定
	CharacterController playerController;
	//キャラの当たり判定
	PhysicsGhostObject playerGhostObject;

	//キャラの場所
	Vector3 charaPos;
	//キャラの得点
	int charaPoint;
	//タックルしているか
	bool tackleFlag = false;
private:

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	//アニメーションのステート
	int animationState;

	//キャラの移動速度
	Vector3 charaMoveSpeed = { 0.0f, 0.0f, 0.0f };
	//左スティックの入力の取得
	Vector3 StickL;
	//回転
	Quaternion rotation;
	//無回転
	Quaternion noneRotation;
	//距離
	float direction;
	//キャラがジャンプしているか
	bool playerJumpingFlag;
	//キャラが気絶しているか
	bool playerStunFlag = false;
	//気絶している時間
	int playerStunTime;
	//キャラのタックルの力を溜めた量
	int playerCharge;
	//キャラのタックルの力が溜まり切ったかどうか
	bool playerFullChargeFlag = false;
	//キャラのタックルの残り時間
	int playerTackleTime;
	//タックル中の向き
	Vector3 tackleMove;
	//キャラの向きの回転
	Quaternion charaRotation;
	//タックルを受けて飛んでいく向き
	Vector3 receiveTackleMoveVec;
	//タックル受けて飛んでいく向きを決定するかのフラグ
	bool receiveTackleVecFlag;

	//AI1にタックルされたフラグ
	bool receiveTackleAI1 = false;
	//AI2にタックルされたフラグ
	bool receiveTackleAI2 = false;
	//AI3にタックルされたフラグ
	bool receiveTackleAI3 = false;

	CoinAIplayerFirst* m_coinAI1 = nullptr;
	CoinAIplayerSecond* m_coinAI2 = nullptr;
	CoinAIplayerThird* m_coinAI3 = nullptr;

	Coin* m_coin;
};

