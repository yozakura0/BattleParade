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
			//�d�͂𔭐�������B
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
	//xz�̈ړ����x��0.0f�ɂ���B
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�50.0f����Z�B
	right *= stickL.x * 900.0f;
	forward *= stickL.y * 900.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	moveSpeed += right + forward;

	//�n�ʂɕt���Ă�����B
	if (playerController.IsOnGround())
	{
		//�d�͂𖳂����B
		moveSpeed.y = 0.0f;
		//A�{�^���������ꂽ��B
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else if (playerController.IsOnGround() == false)
	{
		//�d�͂𔭐�������B
		moveSpeed.y -= 98.0f;
	}

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	CharaPos = playerController.Execute(moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	Character.SetPosition(CharaPos);
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		CharaRot.SetRotationYFromDirectionXZ(moveSpeed);
		//�G�`������ɉ�]��������B
		Character.SetRotation(CharaRot);
	}
}

void Player::Render(RenderContext& rc)
{
	Character.Draw(rc);
}