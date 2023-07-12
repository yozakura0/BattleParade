#include "stdafx.h"
#include "Coin.h"

Coin::Coin()
{
	srand((unsigned int)time(NULL));
	
	//ステージの初期化
	stageRender.Init("Assets/modelData/coin/stage.tkm");
	stageRender.SetPosition(0.0f, 0.0f, 0.0f);
	stageRender.Update();
	stageObject.CreateFromModel(stageRender.GetModel(), stageRender.GetModel().GetWorldMatrix());

	//プレイヤーキャラクターの初期化
	charaRender.Init("Assets/modelData/player/orichara.tkm");
	charaRender.SetScale({ 5.0f,5.0f,5.0f });
	charaRender.SetPosition(charaPos);
	playerController.Init(120.0f, 240.0f, charaPos);

	//AIキャラクターの初期化
	AIRender[0].Init("Assets/modelData/player/AIorichara1.tkm");
	AIRender[1].Init("Assets/modelData/player/AIorichara2.tkm");
	AIRender[2].Init("Assets/modelData/player/AIorichara3.tkm");
	aiPos[0] = { 5200.0f,3000.0f,0.0f };
	aiPos[1] = { -5200.0f,3000.0f,0.0f };
	aiPos[2] = { 0.0f,3000.0f,5000.0f };
	for (int i = 0; i < AICount; i++)
	{
		AIRender[i].SetScale({ 5.0f,5.0f,5.0f });
		AIRender[i].SetPosition(aiPos[i]);
		AIController[i].Init(120.0f, 240.0f, aiPos[i]);
		aiMoveSpeed[i] = { 0.0f,0.0f,0.0f };
	}

	for (int i = 0; i < 4; i++)
	{
		playerPoint[i] = 0;
	}

	AnimationClips[enAnimationClip_Idle].Load("Assets/modelData/player/oriidle.tka");
	AnimationClips[enAnimationClip_Idle].SetLoopFlag(true);
	AnimationClips[enAnimationClip_Walk].Load("Assets/modelData/player/oriwalk.tka");
	AnimationClips[enAnimationClip_Walk].SetLoopFlag(true);
	AnimationClips[enAnimationClip_Walk].Load("Assets/modelData/player/orifall.tka");
	AnimationClips[enAnimationClip_Walk].SetLoopFlag(true);
	AnimationClips[enAnimationClip_Walk].Load("Assets/modelData/player/orijump.tka");
	AnimationClips[enAnimationClip_Walk].SetLoopFlag(false);

	g_camera3D->SetPosition(cameraPos);
	g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D->SetFar(15000.0f);

	//コインの全座標を登録
	for (int i = 0; i < 6; i++)
	{ 
		for (int j = 0; j < 14; j++)
		{
			//右地面
			allCoinPos[coinListCount] = { -4000.0f + i * 500.0f, 0.0f, -3300.0f + j * 500.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			//左地面
			allCoinPos[coinListCount] = { 4000.0f - i * 500.0f, 0.0f, -3300.0f + j * 500.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//上地面
			allCoinPos[coinListCount] = { 1500.0f - i * 500.0f, 0.0f, -3700.0f + j * 300.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//下地面
			allCoinPos[coinListCount] = { 1500.0f - i * 500.0f, 0.0f, 3700.0f - j * 300.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			float posX;
			switch (i)
			{
			case 0:
				posX = 4500.0f;
				break;
			case 1:
				posX = 1000.0f;
				break;
			case 2:
				posX = -1000.0f;
				break;
			case 3:
				posX = -4500.0f;
				break;
			default:
				break;
			}

			//高台縦列
			allCoinPos[coinListCount] = { posX, 1600.0f, 1020.0f - j * 340.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float posZ;
			switch (i)
			{
			case 0:
				posZ = 4300.0f;
				break;
			case 1:
				posZ = 1020.0f;
				break;
			case 2:
				posZ = -1020.0f;
				break;
			case 3:
				posZ = -4300.0f;
				break;
			default:
				break;
			}

			//高台横列
			allCoinPos[coinListCount] = { 500.0f - j * 500.0f, 1600.0f, posZ };
			coinListCount++;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float posX;
			float posZ;
			switch (i)
			{
			case 0:
				posX = -1000.0f;
				break;
			case 1:
				posX = 1000.0f;
				break;
			default:
				break;
			}
			switch (j)
			{
			case 0:
				posZ = 4800.0f;
				break;
			case 1:
				posZ = 4300.0f;
				break;
			case 2:
				posZ = -4030.0f;
				break;
			case 3:
				posZ = -4800.0f;
				break;
			default:
				break;
			}

			//高台の左右の端
			allCoinPos[coinListCount] = { posX, 1600.0f, posZ };
			coinListCount++;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float posX;
			float posZ;
			switch (i)
			{
			case 0:
				posX = 5000.0f;
				break;
			case 1:
				posX = -5000.0f;
				break;
			default:
				break;
			}
			switch (j)
			{
			case 0:
				posZ = 1000.0f;
				break;
			case 1:
				posZ = -1000.0f;
				break;
			default:
				break;
			}

			//高台の上下の端
			allCoinPos[coinListCount] = { posX, 1600.0f, posZ };
			coinListCount++;
		}
	}

	ShowCoin();

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

Coin::~Coin()
{

}

void Coin::Update()
{
	if (gametime <= 0)
	{
		gameClear();
		return;
	}

	//コインの回転処理
	rotation.AddRotationDegY(15.0f);
	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].SetRotation(rotation);
	}
	
	//プレイヤーの移動
	PlayerMove();
	//AIキャラクターの移動
	AIMove();
	
	bool getFlag = false;

	//コイン獲得処理
	getFlag = CoinGet(charaPos);
	if (getFlag)
	{
		playerPoint[0] += 1;
	}
	getFlag = CoinGet(aiPos[0]);
	if (getFlag)
	{
		playerPoint[1] += 1;
	}
	getFlag = CoinGet(aiPos[1]);
	if (getFlag)
	{
		playerPoint[2] += 1;
	}
	getFlag = CoinGet(aiPos[2]);
	if (getFlag)
	{
		playerPoint[3] += 1;
	}

	//時間の表示
	wchar_t timeText[256];
	swprintf_s(timeText, 256, L"%d", gametime);
	timeRender.SetText(timeText);
	timeRender.SetPosition({ 400.0f,500.0f });

	//コインの更新処理
	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].Update();
	}

	//時間の計測
	timeFrameCount++;
	if (timeFrameCount == 60)
	{
		timeFrameCount = 0;
		gametime--;
	}

	//デバッグ用
	//プレイヤーの座標を表示
	wchar_t showPosText[256];
	swprintf_s(showPosText, 256, L"x:%d,\ny:%d,\nz:%d", (int)charaPos.x, (int)charaPos.y, (int)charaPos.z);
	showPos.SetText(showPosText);
	showPos.SetPosition({ -400.0f,500.0f });

	//コインが盤面に残っているか確認
	for (int i = 0; i < coinCount; i++)
	{
		//残っていればここで返す
		if (coinPos[i].y != -100000.0f)
		{
			return;
		}
	}

	//残っていなければ
	//コインを再び撒く
	ShowCoin();
	
	//ゲームクリア処理
	/*gameClear();*/
}

void Coin::PlayerMove()
{
	//xzの移動速度を0.0fにする。
	charaMoveSpeed.x = 0.0f;
	charaMoveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	StickL.x = g_pad[0]->GetLStickXF() * -1200.0f;
	StickL.z = g_pad[0]->GetLStickYF() * -1200.0f;

	//スティックの入力をmoveSpeedに入れ込む
	charaMoveSpeed.x = StickL.x;
	charaMoveSpeed.z = StickL.z;

	//moveSpeedでプレイヤーの座標を変更
	charaPos = playerController.Execute(charaMoveSpeed, 1.0f / 60.0f);

	//ジャンプ処理
	if (g_pad[0]->IsTrigger(enButtonA) && playerController.IsOnGround() == true)
	{
		charaMoveSpeed.y = 3550.0f;
	}

	//飛んでいれば重力をかける
	if (playerController.IsOnGround() == false)
	{
		charaMoveSpeed.y -= 75.0f;
	}

	//座標変更と更新
	charaRender.SetPosition(charaPos);
	charaRender.Update(); 
}

void Coin::AIMove()
{
	for (int i = 0; i < AICount; i++)
	{
		
		float nearestDirection = 50000.0f;
		int nearestCoin = 0;

		for (int j = 0; j < coinCount; j++)
		{
			//キャラとコインの距離を計算
			direction = 0.0f;
			float x = aiPos[i].x - coinPos[j].x;
			float y = aiPos[i].y + 200.0f - coinPos[j].y;
			float z = aiPos[i].z - coinPos[j].z;
			direction = x * x + y * y + z * z;
			direction = sqrtf(direction);

			if (nearestDirection > direction)
			{
				nearestDirection = direction;
				nearestCoin = j;
			}
		}

		Vector3 coinVector;
		coinVector.x = coinPos[nearestCoin].x - aiPos[i].x;
		/*coinVector.y = coinPos[nearestCoin].y - aiPos[i].y;*/
		coinVector.z = coinPos[nearestCoin].z - aiPos[i].z;

		coinVector.Normalize();

		aiMoveSpeed[i].x = coinVector.x * 900.0f;
		/*aiMoveSpeed[i].y = coinVector.y * 900.0f;*/
		aiMoveSpeed[i].z = coinVector.z * 900.0f;
		
		//ジャンプ処理
		
		if (AIController[i].IsOnGround() == true && (difference[i].x == aiPos[i].x || difference[i].z == aiPos[i].z))
		{
			aiMoveSpeed[i].y = 3550.0f;
		}

		//飛んでいれば重力をかける
		if (AIController[i].IsOnGround() == false)
		{
			aiMoveSpeed[i].y -= 75.0f;
		}

		difference[i] = aiPos[i];

		//moveSpeedでプレイヤーの座標を変更
		aiPos[i] = AIController[i].Execute(aiMoveSpeed[i], 1.0f / 60.0f);
		

		//座標更新と更新
		AIRender[i].SetPosition(aiPos[i]);
		AIRender[i].Update();
	}
}

bool Coin::CoinGet(Vector3 pos)
{
	for (int i = 0; i < coinCount; i++)
	{
		//キャラとコインの距離を計算
		direction = 0.0f;
		float x = pos.x - coinPos[i].x;
		float y = pos.y + 200.0f - coinPos[i].y;
		float z = pos.z - coinPos[i].z;
		direction = x * x + y * y + z * z;
		direction = sqrtf(direction);

		//一定以下ならコインの座標を変更
		if (direction <= 300.0f)
		{
			coinPos[i] = { 0.0f,-100000.0f,0.0f };
			coinRender[i].SetPosition(coinPos[i]);
			return true;
		}
	}
	return false;
}

void Coin::ShowCoin()
{
	for (int i = 0; i < coinCount; i++)
	{
		do
		{
			noSameFrag = false;
			//乱数からコインの座標を決定
			selectCount = rand() % 275;
			countSaveList[i] = selectCount;

			//座標が被ってないか確認
			for (int j = 0; j < i; j++)
			{
				if (countSaveList[j] == selectCount)
				{
					noSameFrag = true;
				}
			}
			//被ってなかったら繰り返し終わり
		} while (noSameFrag);

		//コインの情報を設定
		coinPos[i] = allCoinPos[selectCount];
		coinRender[i].Init("Assets/modelData/coin/coin.tkm");
		coinRender[i].SetPosition(coinPos[i]);
		coinRender[i].Update();
	}
}

void Coin::gameClear()
{
	wchar_t finishText[256];
	swprintf_s(finishText, 256, L"1P:%d  2P:%d  3P:%d  4P:%d", playerPoint[0], playerPoint[1], playerPoint[2], playerPoint[3]);
	timeRender.SetText(finishText);
	timeRender.SetColor(Vector4::Gray);
	timeRender.SetPosition({ -100.0f,0.0f });
}

void Coin::Render(RenderContext& rc)
{
	//全てを描画
	stageRender.Draw(rc);
	charaRender.Draw(rc);
	showPos.Draw(rc);
	timeRender.Draw(rc);

	for (int i = 0; i < AICount; i++)
	{
		AIRender[i].Draw(rc);
	}

	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].Draw(rc);
	}
}