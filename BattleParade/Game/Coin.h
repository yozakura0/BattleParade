#pragma once

#define coinCount 10
#define AICount 3

class Coin : public IGameObject
{
public:
	Coin();
	~Coin();

	void Update();
	void Render(RenderContext& rc);
	void PlayerMove();
	void AIMove();
	bool CoinGet(Vector3 pos);
	void ShowCoin();
	void gameClear();

	ModelRender stageRender;
	ModelRender charaRender;
	ModelRender coinRender[50];
	ModelRender AIRender[3];
	PhysicsStaticObject stageObject;
	CharacterController playerController;
	CharacterController AIController[AICount];
	FontRender showPos;
	FontRender timeRender;
	int mode = 0;

private:
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Num
	};
	AnimationClip AnimationClips[enAnimationClip_Num];		//アニメーションクリップ。

	Vector3 cameraPos = { 0.0f, 12000.0f, 1.0f };
	Vector3 charaPos = { 0.0f, 3000.0f, -5000.0f };
	Vector3 aiPos[AICount];
	Vector3 charaMoveSpeed = { 0.0f, 0.0f, 0.0f };
	Vector3 aiMoveSpeed[AICount];
	Vector3 StickL;
	Vector3 allCoinPos[276];
	Quaternion rotation;
	int coinListCount = 0;
	float direction;
	int gametime = 30;
	int timeFrameCount;
	bool noSameFrag;
	int selectCount;
	int countSaveList[coinCount];
	Vector3 coinPos[coinCount];
	int playerPoint[4];
	Vector3 difference[AICount];
};

