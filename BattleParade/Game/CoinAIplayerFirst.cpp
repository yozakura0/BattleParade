#include "stdafx.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIActs.h"
#include "Coin.h"
#include "CoinNumbers.h"
#include "CoinPlayer.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIplayerThird.h"

CoinAIplayerFirst::CoinAIplayerFirst()
{
	firstAIPos = startAI1Pos;

	//AIキャラクターの初期化
	firstCoinAIRender.Init("Assets/modelData/player/AIorichara1.tkm", animationClips);
	firstCoinAIRender.SetScale(scaleMultiply);
	firstCoinAIRender.SetPosition(firstAIPos);

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

	firstAIController.Init(
		controllerRadius,
		controllerHeight,
		firstAIPos
	);
	firstAIGhostObject.CreateCapsule(
		firstAIPos,
		noneRotation,
		capsuleRadius,
		capsuleHeight
	);
	firstAIStunTime = stunTime;
}

CoinAIplayerFirst::~CoinAIplayerFirst()
{

}

void CoinAIplayerFirst::Update()
{
	//coinAIActs->AIMove(firstAIPos, firstAIMoveSpeed, firstAIdifference/*, firstAIController, firstAIGhostObject*/);
	m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");
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

	if (m_coinPlayer && m_coinAI2 && m_coinAI3)
	{
		ReceiveTackle();
		Move();
		AI1Point += m_coin->CoinGet(firstAIPos);
		PointManager();

		firstCoinAIRender.Update();
	}
}

void CoinAIplayerFirst::Move()
{

	if (m_coin != nullptr)
	{
		//タックルされた処理
		if (receiveTacklePto1 == true || receiveTackle2to1 == true || receiveTackle3to1 == true)
		{
			if (receiveTacklePto1 && receiveTackleVecFlag)
			{
				m_coinPlayer->charaPoint += tackleResultPoint;
				AI1Point -= tackleResultPoint;

				receiveTackleMoveVec.x = firstAIPos.x - m_coinPlayer->charaPos.x;
				receiveTackleMoveVec.y = firstAIPos.y - m_coinPlayer->charaPos.y;
				receiveTackleMoveVec.z = firstAIPos.z - m_coinPlayer->charaPos.z;

				receiveTackleMoveVec.Normalize();

				firstAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				firstAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				firstAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle2to1 && receiveTackleVecFlag)
			{
				m_coinAI2->AI2Point += tackleResultPoint;
				AI1Point -= tackleResultPoint;

				receiveTackleMoveVec.x = firstAIPos.x - m_coinAI2->secondAIPos.x;
				receiveTackleMoveVec.y = firstAIPos.y - m_coinAI2->secondAIPos.y;
				receiveTackleMoveVec.z = firstAIPos.z - m_coinAI2->secondAIPos.z;

				receiveTackleMoveVec.Normalize();

				firstAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				firstAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				firstAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			else if (receiveTackle3to1 && receiveTackleVecFlag)
			{
				m_coinAI3->AI3Point += tackleResultPoint;
				AI1Point -= tackleResultPoint;

				receiveTackleMoveVec.x = firstAIPos.x - m_coinAI3->thirdAIPos.x;
				receiveTackleMoveVec.y = firstAIPos.y - m_coinAI3->thirdAIPos.y;
				receiveTackleMoveVec.z = firstAIPos.z - m_coinAI3->thirdAIPos.z;

				receiveTackleMoveVec.Normalize();

				firstAIMoveSpeed.x = receiveTackleMoveVec.x * receiveTackleMoveMultiply;
				firstAIMoveSpeed.y = receiveTackleMoveVec.y * receiveTackleMoveMultiply;
				firstAIMoveSpeed.z = receiveTackleMoveVec.z * receiveTackleMoveMultiply;
			}
			receiveTackleVecFlag = false;

			firstAIMoveSpeed.x /= tackleMoveWeaken;
			firstAIMoveSpeed.y /= tackleMoveWeaken;
			firstAIMoveSpeed.z /= tackleMoveWeaken;

			firstAIStunTime--;

			if (firstAIStunTime <= 0)
			{
				firstAIStunTime = stunTime;

				receiveTacklePto1 = false;
				receiveTackle2to1 = false;
				receiveTackle3to1 = false;
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
				float x = firstAIPos.x - m_coin->coinPos[i].x;
				float y = firstAIPos.y + 200.0f - m_coin->coinPos[i].y;
				float z = firstAIPos.z - m_coin->coinPos[i].z;
				direction = x * x + y * y + z * z;
				direction = sqrtf(direction);

				if (nearestDirection > direction)
				{
					nearestDirection = direction;
					nearestCoin = i;
				}
			}

			Vector3 coinVector;
			coinVector.x = m_coin->coinPos[nearestCoin].x - firstAIPos.x;
			/*coinVector.y = coinPos[nearestCoin].y - aiPos[i].y;*/
			coinVector.z = m_coin->coinPos[nearestCoin].z - firstAIPos.z;

			coinVector.Normalize();

			firstAIMoveSpeed.x = coinVector.x * moveMultiply;
			/*aiMoveSpeed[i].y = coinVector.y * 900.0f;*/
			firstAIMoveSpeed.z = coinVector.z * moveMultiply;

			//ジャンプ処理
			if (firstAIController.IsOnGround() == true && (firstAIdifference.x == firstAIPos.x || firstAIdifference.z == firstAIPos.z))
			{
				firstAIMoveSpeed.y = jumpPower;
			}

			firstAIdifference = firstAIPos;
		}
	}

	//飛んでいれば重力をかける
	if (firstAIController.IsOnGround() == false)
	{
		firstAIMoveSpeed.y -= gravity;
	}

	if (firstAIPos.y < -100.0f)
	{
		AI1Point -= fallPenalty;
		firstAIPos = startAI1Pos;
		firstAIController.SetPosition(firstAIPos);
	}
	else
	{
		//moveSpeedでプレイヤーの座標を変更
		firstAIPos = firstAIController.Execute(firstAIMoveSpeed, 1.0f / 60.0f);
	}

	//プレイヤーのゴーストオブジェクトの移動
	firstAIGhostObject.SetPosition(firstAIPos);

	//座標更新と情報の更新
	firstCoinAIRender.SetPosition(firstAIPos);
}

//タックルされたかの判定
void CoinAIplayerFirst::ReceiveTackle()
{
	//敵キャラ1との衝突判定
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinPlayer->playerController,
		[&](const btCollisionObject& contactObject)
		{
			if (firstAIGhostObject.IsSelf(contactObject) == true && m_coinPlayer->tackleFlag)
			{
				receiveTacklePto1 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
	//敵キャラ2との衝突判定
	PhysicsWorld::GetInstance()->ContactTest
	(
		m_coinAI2->secondAIController,
		[&](const btCollisionObject& contactObject)
		{
			if (firstAIGhostObject.IsSelf(contactObject) == true && m_coinAI2->secondAITackleFlag)
			{
				receiveTackle2to1 = true;
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
			if (firstAIGhostObject.IsSelf(contactObject) == true && m_coinAI3->thirdAITackleFlag)
			{
				receiveTackle3to1 = true;
				receiveTackleVecFlag = true;
			}
		}
	);
}

void CoinAIplayerFirst::PointManager()
{
	if (AI1Point < 0)
	{
		AI1Point = 0;
	}
}

void CoinAIplayerFirst::Render(RenderContext& rc)
{
	firstCoinAIRender.Draw(rc);
}

