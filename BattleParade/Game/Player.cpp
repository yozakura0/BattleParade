#include "stdafx.h"
#include "Player.h"

#include "Nib.h"

Player::Player()
{
	nib = FindGO<Nib>("nib");

	/*AnimationClips[enAnimationClip_Idle].Load("Assets/character/oriidle.tka");
	AnimationClips[enAnimationClip_Idle].SetLoopFlag(true);
	AnimationClips[enAnimationClip_Walk].Load("Assets/character/oriwalk.tka");
	AnimationClips[enAnimationClip_Walk].SetLoopFlag(true);*/

	Character.SetScale({ 2.0f,2.0f,2.0f, });
	Character.Init("Assets/modelData/player/player1.tkm");
	Character.Update();
	
	playerController.Init(120.0f, 240.0f, CharaPos);
}

Player::~Player()
{

}

void Player::Update()
{
	if (nib != nullptr) {
		if (nib->isStop != true) {
	Move();
	Rotation();
		}
		else if (playerController.IsOnGround() == false)
		{
			//重力を発生させる。
			moveSpeed.y -= 9.8f;
			CharaPos = playerController.Execute(moveSpeed, 1.0f / 60.0f);
			Character.SetPosition(CharaPos);
		}
	}
	//Animation();
	Character.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と50.0fを乗算。
	right *= stickL.x * 900.0f;
	forward *= stickL.y * 900.0f;

	//移動速度にスティックの入力量を加算する。
	moveSpeed += right + forward;

	//地面に付いていたら。
	if (playerController.IsOnGround())
	{
		//重力を無くす。
		moveSpeed.y = 0.0f;
		//Aボタンが押されたら。
	}
	//地面に付いていなかったら。
	else if (playerController.IsOnGround() == false)
	{
		//重力を発生させる。
		moveSpeed.y -= 98.0f;
	}

	//キャラクターコントローラーを使って座標を移動させる。
	CharaPos = playerController.Execute(moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	Character.SetPosition(CharaPos);
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		CharaRot.SetRotationYFromDirectionXZ(moveSpeed);
		//絵描きさんに回転を教える。
		Character.SetRotation(CharaRot);
	}
}

void Player::Render(RenderContext& rc)
{
	Character.Draw(rc);
}