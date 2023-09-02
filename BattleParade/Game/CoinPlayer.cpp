#include "stdafx.h"
#include "CoinPlayer.h"
#include "CoinNumbers.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIplayerThird.h"
#include "Coin.h"

CoinPlayer::CoinPlayer()
{
	charaPos = startCharaPos;

	//�v���C���[�L�����N�^�[�̏�����
	charaRender.Init("Assets/modelData/player/orichara.tkm", animationClips);
	charaRender.SetScale(scaleMultiply);
	charaRender.SetPosition(charaPos);

	animationClips[enAnimationClip_Idle].Load("Assets/modelData/player/oriidle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/modelData/player/oriwalk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Fall].Load("Assets/modelData/player/orifall.tka");
	animationClips[enAnimationClip_Fall].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/modelData/player/orijump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/modelData/player/oriruntest.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);

	playerController.Init(
		controllerRadius, 
		controllerHeight, 
		charaPos
	);
	playerGhostObject.CreateCapsule(
		charaPos, 
		noneRotation, 
		capsuleRadius, 
		capsuleHeight
	);
	playerStunTime = stunTime;
}

CoinPlayer::~CoinPlayer()
{

}

void CoinPlayer::Update()
{
	m_coinAI1 = FindGO<CoinAIplayerFirst>("coinAI1");
	m_coinAI2 = FindGO<CoinAIplayerSecond>("coinAI2");
	m_coinAI3 = FindGO<CoinAIplayerThird>("coinAI3");
	m_coin = FindGO<Coin>("coin");

	if (m_coin->gametime <= 0)
	{
		if (m_coin->gameEndFlag)
		{
			DeleteGO(this);
		}

		return;
	}

	if (m_coinAI1 && m_coinAI2 && m_coinAI3)
	{
		Move();
		StateManagement();
		Animation();
		ReceiveTackle();
		charaPoint += m_coin->CoinGet(charaPos);
		PointManager();

		charaRender.Update();
	}
}

void CoinPlayer::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	charaMoveSpeed.x = 0.0f;
	charaMoveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	StickL.x = g_pad[0]->GetLStickXF() * stickMultiply;
	StickL.z = g_pad[0]->GetLStickYF() * stickMultiply;

	//�X�e�B�b�N�̓��͂�moveSpeed�ɓ��ꍞ��
	charaMoveSpeed.x = StickL.x;
	charaMoveSpeed.z = StickL.z;

	//�^�b�N�����ꂽ����
	if (receiveTackleAI1 == true || receiveTackleAI2 == true || receiveTackleAI3 == true)
	{
		playerFullChargeFlag = false;
		tackleFlag = false;
		playerCharge = 0.0f;

		if (receiveTackleAI1 && receiveTackleVecFlag)
		{
			m_coinAI1->AI1Point += tackleResultPoint;
			charaPoint -= tackleResultPoint;

			receiveTackleMoveVec.x = charaPos.x - m_coinAI1->firstAIPos.x;
			receiveTackleMoveVec.y = charaPos.y - m_coinAI1->firstAIPos.y;
			receiveTackleMoveVec.z = charaPos.z - m_coinAI1->firstAIPos.z;

			receiveTackleMoveVec.Normalize();

			charaMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
			charaMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
			charaMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
		}
		else if (receiveTackleAI2 && receiveTackleVecFlag)
		{
			m_coinAI2->AI2Point += tackleResultPoint;
			charaPoint -= tackleResultPoint;

			receiveTackleMoveVec.x = charaPos.x - m_coinAI2->secondAIPos.x;
			receiveTackleMoveVec.y = charaPos.y - m_coinAI2->secondAIPos.y;
			receiveTackleMoveVec.z = charaPos.z - m_coinAI2->secondAIPos.z;

			receiveTackleMoveVec.Normalize();

			charaMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
			charaMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
			charaMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
		}
		else if (receiveTackleAI3 && receiveTackleVecFlag)
		{
			m_coinAI3->AI3Point += tackleResultPoint;
			charaPoint -= tackleResultPoint;

			receiveTackleMoveVec.x = charaPos.x - m_coinAI3->thirdAIPos.x;
			receiveTackleMoveVec.y = charaPos.y - m_coinAI3->thirdAIPos.y;
			receiveTackleMoveVec.z = charaPos.z - m_coinAI3->thirdAIPos.z;

			receiveTackleMoveVec.Normalize();

			charaMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
			charaMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
			charaMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
		}
		receiveTackleVecFlag = false;

		charaMoveSpeed.x /= tackleMoveWeaken;
		charaMoveSpeed.y /= tackleMoveWeaken;
		charaMoveSpeed.z /= tackleMoveWeaken;

		playerStunTime--;

		if (playerStunTime <= 0)
		{
			playerStunTime = stunTime;

			receiveTackleAI1 = false;
			receiveTackleAI2 = false;
			receiveTackleAI3 = false;
		}
	}
	//�^�b�N���̗͂����߂鏈��
	else if (g_pad[0]->IsPress(enButtonRB2) && tackleFlag == false && playerController.IsOnGround() == true)
	{
		playerCharge++;

		if (fabsf(charaMoveSpeed.x) >= 0.001f || fabsf(charaMoveSpeed.z) >= 0.001f)
		{
			//�L�����N�^�[�̕�����ς���B
			charaRotation.SetRotationYFromDirectionXZ(charaMoveSpeed);
			//�G�`������ɉ�]��������B
			charaRender.SetRotation(charaRotation);
		}

		if (playerCharge >= fullChargeCount)
		{
			playerFullChargeFlag = true;
			playerTackleTime = tackleTimeCount;
			tackleMove.x = StickL.x * tackleMoveMultiply;
			tackleMove.z = StickL.z * tackleMoveMultiply;
		}
	}
	//�^�b�N�������鏈��
	else if (playerFullChargeFlag)
	{
		tackleFlag = true;
		playerCharge = 0;
		playerTackleTime--;

		//tackleMove�Ńv���C���[�̍��W��ύX
		charaPos = playerController.Execute(tackleMove, 1.0f / 60.0f);

		//�v���C���[�̃S�[�X�g�I�u�W�F�N�g�̈ړ�
		playerGhostObject.SetPosition(charaPos);

		if (playerTackleTime <= 0)
		{
			playerFullChargeFlag = false;
			tackleFlag = false;
		}
	}
	else
	{
		playerCharge = 0;
		playerTackleTime = 0;

		//�W�����v����
		if (g_pad[0]->IsTrigger(enButtonA) && playerController.IsOnGround() == true)
		{
			charaMoveSpeed.y = jumpPower;
			playerJumpingFlag = true;
		}


		if (charaPos.y < -100.0f)
		{
			charaPoint -= fallPenalty;
			charaPos = startCharaPos;
			playerController.SetPosition(charaPos);
		}
		else
		{
			//moveSpeed�Ńv���C���[�̍��W��ύX
			charaPos = playerController.Execute(charaMoveSpeed, 1.0f / 60.0f);
		}

		//�v���C���[�̃S�[�X�g�I�u�W�F�N�g�̈ړ�
		playerGhostObject.SetPosition(charaPos);

		if (fabsf(charaMoveSpeed.x) >= 0.001f || fabsf(charaMoveSpeed.z) >= 0.001f)
		{
			//�L�����N�^�[�̕�����ς���B
			charaRotation.SetRotationYFromDirectionXZ(charaMoveSpeed);
			//�G�`������ɉ�]��������B
			charaRender.SetRotation(charaRotation);
		}
	}

	//���ł���Ώd�͂�������
	if (playerController.IsOnGround() == false)
	{
		charaMoveSpeed.y -= gravity;
	}
	else
	{
		playerJumpingFlag = false;
	}

	//���W�ύX�ƍX�V
	charaRender.SetPosition(charaPos);
	charaRender.Update();
}

//�Đ�����A�j���[�V�����̐؂�ւ�
void CoinPlayer::StateManagement()
{
	if (playerJumpingFlag == true)
	{
		animationState = animation_jump;
	}
	else if (playerController.IsOnGround() == false)
	{
		animationState = animation_fall;
	}
	else if (tackleFlag == true)
	{
		animationState = animation_run;
	}
	else if (StickL.x != 0.0f || StickL.y != 0.0f)
	{
		animationState = animation_walk;
	}
	else
	{
		animationState = animation_idle;
	}
}

//�A�j���[�V�������Đ�����
void CoinPlayer::Animation()
{
	switch (animationState)
	{
	case animation_idle:
		charaRender.PlayAnimation(enAnimationClip_Idle, 0.2f);
		break;
	case animation_walk:
		charaRender.PlayAnimation(enAnimationClip_Walk, 0.2f);
		break;
	case animation_fall:
		charaRender.PlayAnimation(enAnimationClip_Fall, 0.2f);
		break;
	case animation_jump:
		charaRender.PlayAnimation(enAnimationClip_Jump, 0.2f);
		break;
	case animation_run:
		charaRender.PlayAnimation(enAnimationClip_Run, 0.2f);
		break;
	default:
		break;
	}
}

//�^�b�N�����ꂽ���̔���
void CoinPlayer::ReceiveTackle()
{
	//�G�L����1�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI1->firstAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (playerGhostObject.IsSelf(contactObject) == true && m_coinAI1->firstAITackleFlag)
			{
				receiveTackleAI1 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//�G�L����2�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI2->secondAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (playerGhostObject.IsSelf(contactObject) == true && m_coinAI2->secondAITackleFlag)
			{
				receiveTackleAI2 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//�G�L����3�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI3->thirdAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (playerGhostObject.IsSelf(contactObject) == true && m_coinAI3->thirdAITackleFlag)
			{
				receiveTackleAI3 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
}

void CoinPlayer::PointManager()
{
	if (charaPoint < 0)
	{
		charaPoint = 0;
	}
}

void CoinPlayer::Render(RenderContext& rc)
{
	charaRender.Draw(rc);
}