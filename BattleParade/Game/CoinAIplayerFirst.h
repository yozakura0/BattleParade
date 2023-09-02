#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class Coin;

class CoinAIplayerFirst : public IGameObject
{
public:
	CoinAIplayerFirst();
	~CoinAIplayerFirst();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//物理判定
	CharacterController firstAIController;
	//当たり判定
	PhysicsGhostObject firstAIGhostObject;

	//敵キャラを表示するモデルレンダー
	ModelRender firstCoinAIRender;

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
	bool firstAITackleFlag = false;
	//AI1の得点
	int AI1Point;
	//場所
	Vector3 firstAIPos;
private:
	//移動速度
	Vector3 firstAIMoveSpeed;
	//1フレーム前の座標
	Vector3 firstAIdifference;
	//タックル中の向き
	Vector3 tackleMove;
	//キャラが気絶しているか
	bool firstAIStunFlag = false;
	//気絶している時間
	int firstAIStunTime;
	//プレイヤーにタックルされたフラグ
	bool receiveTacklePto1 = false;
	//AI2にタックルされたフラグ
	bool receiveTackle2to1 = false;
	//AI3にタックルされたフラグ
	bool receiveTackle3to1 = false;
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
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;

	Coin* m_coin;
};

