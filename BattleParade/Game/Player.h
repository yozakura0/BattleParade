#pragma once

class Nib;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void State();
	void Animation();

	ModelRender Character;
	Vector3 CharaPos;
	Quaternion CharaRot;
	CharacterController playerController;
	Vector3 moveSpeed;

	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};

	Nib* nib;
	AnimationClip AnimationClips[enAnimationClip_Num];		//アニメーションクリップ。

	//スティックの入力量を保存する変数
	Vector3 StickL;

	//プレイヤーの状態
	int P_state = 0;

	//フラグ類
	bool fall = false;
	bool walk = false;
	bool attack = false;
};

