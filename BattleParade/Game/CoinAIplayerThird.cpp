#include "stdafx.h"
#include "CoinAIplayerThird.h"
#include "CoinAIActs.h"
#include "Coin.h"
#include "CoinNumbers.h"
#include "CoinPlayer.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerSecond.h"

CoinAIplayerThird::CoinAIplayerThird()
{
	thirdAIPos = startAI3Pos;

	//AI�L�����N�^�[�̏�����
	thirdCoinAIRender.Init("Assets/modelData/player/AIorichara3.tkm", animationClips);
	thirdCoinAIRender.SetScale(scaleMultiply);
	thirdCoinAIRender.SetPosition(thirdAIPos);

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

	thirdAIController.Init(
		controllerRadius,
		controllerHeight,
		thirdAIPos
	);
	thirdAIGhostObject.CreateCapsule(
		thirdAIPos,
		noneRotation,
		capsuleRadius,
		capsuleHeight
	);
	thirdAIStunTime = stunTime;
}

CoinAIplayerThird::~CoinAIplayerThird()
{

}

void CoinAIplayerThird::Update()
{
	//coinAIActs->AIMove(thirdAIPos, thirdAIMoveSpeed, thirdAIdifference/*, firstAIController, firstAIGhostObject*/);
	m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");
	m_coinAI1 = FindGO<CoinAIplayerFirst>("coinAI1");
	m_coinAI2 = FindGO<CoinAIplayerSecond>("coinAI2");
	m_coin = FindGO<Coin>("coin");

	if (m_coin->gametime <= 0)
	{
		if (m_coin->gameEndFlag)
		{
			DeleteGO(this);
		}

		return;
	}

	if (m_coinPlayer && m_coinAI1 && m_coinAI2)
	{
		ReceiveTackle();
		Move();
		AI3Point += m_coin->CoinGet(thirdAIPos);
		PointManager();

		thirdCoinAIRender.Update();
	}
}

void CoinAIplayerThird::Render(RenderContext& rc)
{
	thirdCoinAIRender.Draw(rc);
}

void CoinAIplayerThird::Move()
{
	if (m_coin != nullptr)
	{
		//�^�b�N�����ꂽ����
		if (receiveTacklePto3 == true || receiveTackle1to3 == true || receiveTackle2to3 == true)
		{
			if (receiveTacklePto3 && receiveTackleVecFlag)
			{
				m_coinPlayer->charaPoint += tackleResultPoint;
				AI3Point -= tackleResultPoint;

				receiveTackleMoveVec.x = thirdAIPos.x - m_coinPlayer->charaPos.x;
				receiveTackleMoveVec.y = thirdAIPos.y - m_coinPlayer->charaPos.y;
				receiveTackleMoveVec.z = thirdAIPos.z - m_coinPlayer->charaPos.z;

				receiveTackleMoveVec.Normalize();

				thirdAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle1to3 && receiveTackleVecFlag)
			{
				m_coinAI1->AI1Point += tackleResultPoint;
				AI3Point -= tackleResultPoint;

				receiveTackleMoveVec.x = thirdAIPos.x - m_coinAI1->firstAIPos.x;
				receiveTackleMoveVec.y = thirdAIPos.y - m_coinAI1->firstAIPos.y;
				receiveTackleMoveVec.z = thirdAIPos.z - m_coinAI1->firstAIPos.z;

				receiveTackleMoveVec.Normalize();

				thirdAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle2to3 && receiveTackleVecFlag)
			{
				m_coinAI2->AI2Point += tackleResultPoint;
				AI3Point -= tackleResultPoint;

				receiveTackleMoveVec.x = thirdAIPos.x - m_coinAI2->secondAIPos.x;
				receiveTackleMoveVec.y = thirdAIPos.y - m_coinAI2->secondAIPos.y;
				receiveTackleMoveVec.z = thirdAIPos.z - m_coinAI2->secondAIPos.z;

				receiveTackleMoveVec.Normalize();

				thirdAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				thirdAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			receiveTackleVecFlag = false;

			thirdAIMoveSpeed.x /= tackleMoveWeaken;
			thirdAIMoveSpeed.y /= tackleMoveWeaken;
			thirdAIMoveSpeed.z /= tackleMoveWeaken;

			thirdAIStunTime--;

			if (thirdAIStunTime <= 0)
			{
				thirdAIStunTime = stunTime;

				receiveTacklePto3 = false;
				receiveTackle1to3 = false;
				receiveTackle2to3 = false;
			}
		}
		else
		{
			float nearestDirection = 50000.0f;
			int nearestCoin = 0;

			for (int i = 0; i < coinCount; i++)
			{
				//�L�����ƃR�C���̋������v�Z
				direction = 0.0f;
				float x = thirdAIPos.x - m_coin->coinPos[i].x;
				float y = thirdAIPos.y + 200.0f - m_coin->coinPos[i].y;
				float z = thirdAIPos.z - m_coin->coinPos[i].z;
				direction = x * x + y * y + z * z;
				direction = sqrtf(direction);

				if (nearestDirection > direction)
				{
					nearestDirection = direction;
					nearestCoin = i;
				}
			}

			Vector3 coinVector;
			coinVector.x = m_coin->coinPos[nearestCoin].x - thirdAIPos.x;
			/*coinVector.y = coinPos[nearestCoin].y - aiPos[i].y;*/
			coinVector.z = m_coin->coinPos[nearestCoin].z - thirdAIPos.z;

			coinVector.Normalize();

			thirdAIMoveSpeed.x = coinVector.x * moveMultiply;
			/*aiMoveSpeed[i].y = coinVector.y * 900.0f;*/
			thirdAIMoveSpeed.z = coinVector.z * moveMultiply;

			//�W�����v����
			if (thirdAIController.IsOnGround() == true && (thirdAIdifference.x == thirdAIPos.x || thirdAIdifference.z == thirdAIPos.z))
			{
				thirdAIMoveSpeed.y = jumpPower;
			}

			thirdAIdifference = thirdAIPos;
		}

		//���ł���Ώd�͂�������
		if (thirdAIController.IsOnGround() == false)
		{
			thirdAIMoveSpeed.y -= gravity;
		}

		if (thirdAIPos.y < -100.0f)
		{
			AI3Point -= fallPenalty;
			thirdAIPos = startAI3Pos;
			thirdAIController.SetPosition(thirdAIPos);
		}
		else
		{
			//moveSpeed�Ńv���C���[�̍��W��ύX
			thirdAIPos = thirdAIController.Execute(thirdAIMoveSpeed, 1.0f / 60.0f);
		}

		//�v���C���[�̃S�[�X�g�I�u�W�F�N�g�̈ړ�
		thirdAIGhostObject.SetPosition(thirdAIPos);

		//���W�X�V�Ə��̍X�V
		thirdCoinAIRender.SetPosition(thirdAIPos);
	}
}

//�^�b�N�����ꂽ���̔���
void CoinAIplayerThird::ReceiveTackle()
{
	//�G�L����1�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinPlayer->playerController,
		[&](const btCollisionObject& contactObject)
		{
			if (thirdAIGhostObject.IsSelf(contactObject) == true && m_coinPlayer->tackleFlag)
			{
				receiveTacklePto3 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//�G�L����2�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI1->firstAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (thirdAIGhostObject.IsSelf(contactObject) == true && m_coinAI1->firstAITackleFlag)
			{
				receiveTackle1to3 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//�G�L����3�Ƃ̏Փ˔���
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI2->secondAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (thirdAIGhostObject.IsSelf(contactObject) == true && m_coinAI2->secondAITackleFlag)
			{
				receiveTackle2to3 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
}

void CoinAIplayerThird::PointManager()
{
	if (AI3Point < 0)
	{
		AI3Point = 0;
	}
}