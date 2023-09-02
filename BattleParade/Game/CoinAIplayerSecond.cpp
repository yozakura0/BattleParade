#include "stdafx.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIActs.h"
#include "Coin.h"
#include "CoinNumbers.h"
#include "CoinPlayer.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerThird.h"

CoinAIplayerSecond::CoinAIplayerSecond()
{
	secondAIPos = startAI2Pos;

	//AIキャラクターの初期化
	secondCoinAIRender.Init("Assets/modelData/player/AIorichara2.tkm", animationClips);
	secondCoinAIRender.SetScale(scaleMultiply);
	secondCoinAIRender.SetPosition(secondAIPos);

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

	secondAIController.Init(
		controllerRadius,
		controllerHeight,
		secondAIPos
	);
	secondAIGhostObject.CreateCapsule(
		secondAIPos,
		noneRotation,
		capsuleRadius,
		capsuleHeight
	);
	secondAIStunTime = stunTime;
}

CoinAIplayerSecond::~CoinAIplayerSecond()
{

}

void CoinAIplayerSecond::Update()
{
	//coinAIActs->AIMove(secondAIPos, secondAIMoveSpeed, secondAIdifference/*, firstAIController, firstAIGhostObject*/);
	m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");
	m_coinAI1 = FindGO<CoinAIplayerFirst>("coinAI1");
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

	if (m_coinPlayer && m_coinAI1 && m_coinAI3)
	{
		ReceiveTackle();
		Move();
		AI2Point += m_coin->CoinGet(secondAIPos); 
		PointManager();

		secondCoinAIRender.Update();
	}
}

void CoinAIplayerSecond::Render(RenderContext& rc)
{
	secondCoinAIRender.Draw(rc);
}

void CoinAIplayerSecond::Move()
{

	if (m_coin != nullptr)
	{
		//タックルされた処理
		if (receiveTacklePto2 == true || receiveTackle1to2 == true || receiveTackle3to2 == true)
		{
			if (receiveTacklePto2 && receiveTackleVecFlag)
			{
				m_coinPlayer->charaPoint += tackleResultPoint;
				AI2Point -= tackleResultPoint;

				receiveTackleMoveVec.x = secondAIPos.x - m_coinPlayer->charaPos.x;
				receiveTackleMoveVec.y = secondAIPos.y - m_coinPlayer->charaPos.y;
				receiveTackleMoveVec.z = secondAIPos.z - m_coinPlayer->charaPos.z;

				receiveTackleMoveVec.Normalize();

				secondAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				secondAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				secondAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle1to2 && receiveTackleVecFlag)
			{
				m_coinAI1->AI1Point += tackleResultPoint;
				AI2Point -= tackleResultPoint;

				receiveTackleMoveVec.x = secondAIPos.x - m_coinAI1->firstAIPos.x;
				receiveTackleMoveVec.y = secondAIPos.y - m_coinAI1->firstAIPos.y;
				receiveTackleMoveVec.z = secondAIPos.z - m_coinAI1->firstAIPos.z;

				receiveTackleMoveVec.Normalize();

				secondAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				secondAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				secondAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle3to2 && receiveTackleVecFlag)
			{
				m_coinAI3->AI3Point += tackleResultPoint;
				AI2Point -= tackleResultPoint;

				receiveTackleMoveVec.x = secondAIPos.x - m_coinAI3->thirdAIPos.x;
				receiveTackleMoveVec.y = secondAIPos.y - m_coinAI3->thirdAIPos.y;
				receiveTackleMoveVec.z = secondAIPos.z - m_coinAI3->thirdAIPos.z;

				receiveTackleMoveVec.Normalize();

				secondAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				secondAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				secondAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			receiveTackleVecFlag = false;

			secondAIMoveSpeed.x /= tackleMoveWeaken;
			secondAIMoveSpeed.y /= tackleMoveWeaken;
			secondAIMoveSpeed.z /= tackleMoveWeaken;

			secondAIStunTime--;

			if (secondAIStunTime <= 0)
			{
				secondAIStunTime = stunTime;

				receiveTacklePto2 = false;
				receiveTackle1to2 = false;
				receiveTackle3to2 = false;
			}
		}
		else
		{
			float nearestDirection = 50000.0f;
			int nearestCoin = 0;

			for (int i = 0; i < coinCount; i++)
			{
				//キャラとコインの距離を計算
				direction = 0.0f;
				float x = secondAIPos.x - m_coin->coinPos[i].x;
				float y = secondAIPos.y + 200.0f - m_coin->coinPos[i].y;
				float z = secondAIPos.z - m_coin->coinPos[i].z;
				direction = x * x + y * y + z * z;
				direction = sqrtf(direction);

				if (nearestDirection > direction)
				{
					nearestDirection = direction;
					nearestCoin = i;
				}
			}

			Vector3 coinVector;
			coinVector.x = m_coin->coinPos[nearestCoin].x - secondAIPos.x;
			/*coinVector.y = coinPos[nearestCoin].y - aiPos[i].y;*/
			coinVector.z = m_coin->coinPos[nearestCoin].z - secondAIPos.z;

			coinVector.Normalize();

			secondAIMoveSpeed.x = coinVector.x * moveMultiply;
			/*aiMoveSpeed[i].y = coinVector.y * 900.0f;*/
			secondAIMoveSpeed.z = coinVector.z * moveMultiply;

			//ジャンプ処理
			if (secondAIController.IsOnGround() == true && (secondAIdifference.x == secondAIPos.x || secondAIdifference.z == secondAIPos.z))
			{
				secondAIMoveSpeed.y = jumpPower;
			}

			secondAIdifference = secondAIPos;
		}

		//飛んでいれば重力をかける
		if (secondAIController.IsOnGround() == false)
		{
			secondAIMoveSpeed.y -= gravity;
		}

		if (secondAIPos.y < -100.0f)
		{
			AI2Point -= fallPenalty;
			secondAIPos = startAI2Pos;
			secondAIController.SetPosition(secondAIPos);
		}
		else
		{
			//moveSpeedでプレイヤーの座標を変更
			secondAIPos = secondAIController.Execute(secondAIMoveSpeed, 1.0f / 60.0f);
		}

		//プレイヤーのゴーストオブジェクトの移動
		secondAIGhostObject.SetPosition(secondAIPos);

		//座標更新と情報の更新
		secondCoinAIRender.SetPosition(secondAIPos);
	}
}

//タックルされたかの判定
void CoinAIplayerSecond::ReceiveTackle()
{
	//敵キャラ1との衝突判定
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinPlayer->playerController,
		[&](const btCollisionObject& contactObject)
		{
			if (secondAIGhostObject.IsSelf(contactObject) == true && m_coinPlayer->tackleFlag)
			{
				receiveTacklePto2 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//敵キャラ2との衝突判定
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI1->firstAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (secondAIGhostObject.IsSelf(contactObject) == true && m_coinAI1->firstAITackleFlag)
			{
				receiveTackle1to2 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//敵キャラ3との衝突判定
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI3->thirdAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (secondAIGhostObject.IsSelf(contactObject) == true && m_coinAI3->thirdAITackleFlag)
			{
				receiveTackle3to2 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
}

void CoinAIplayerSecond::PointManager()
{
	if (AI2Point < 0)
	{
		AI2Point = 0;
	}
}