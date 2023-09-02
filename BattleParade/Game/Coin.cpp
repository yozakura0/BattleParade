#include "stdafx.h"
#include "Coin.h"
#include "CoinNumbers.h"
#include "CoinPlayer.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIplayerThird.h"
#include "CoinUI.h"
#include "CoinGameResult.h"

Coin::Coin()
{
	srand((unsigned int)time(NULL));

	gametime = maxGameTime;
	
	//�X�e�[�W�̏�����
	stageRender.Init("Assets/modelData/coin/stage3.tkm");
	stageRender.SetPosition(0.0f, 0.0f, 0.0f);
	stageRender.Update();
	stageObject.CreateFromModel(stageRender.GetModel(), stageRender.GetModel().GetWorldMatrix());

	m_coinPlayer = NewGO<CoinPlayer>(2, "coinPlayer");
	m_coinAI1 = NewGO<CoinAIplayerFirst>(2, "coinAI1");
	m_coinAI2 = NewGO<CoinAIplayerSecond>(2, "coinAI2");
	m_coinAI3 = NewGO<CoinAIplayerThird>(2, "coinAI3");
	m_coinUI = NewGO<CoinUI>(1, "coinUI");

	g_camera3D->SetPosition(CameraPos);
	g_camera3D->SetTarget(CameraTargetPos);
	g_camera3D->SetFar(CameraFar);

	//�R�C���̑S���W��o�^
	for (int i = 0; i < 6; i++)
	{ 
		for (int j = 0; j < 14; j++)
		{
			//�E�n��
			allCoinPos[coinListCount] = { -4000.0f + i * 500.0f, 0.0f, -3300.0f + j * 500.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			//���n��
			allCoinPos[coinListCount] = { 4000.0f - i * 500.0f, 0.0f, -3300.0f + j * 500.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//��n��
			allCoinPos[coinListCount] = { 1500.0f - i * 500.0f, 0.0f, -3700.0f + j * 300.0f };
			coinListCount++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//���n��
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

			//����c��
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

			//���䉡��
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

			//����̍��E�̒[
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

			//����̏㉺�̒[
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

	//�R�C���̉�]����
	rotation.AddRotationDegY(15.0f);
	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].SetRotation(rotation);
	}

	//�R�C���̍X�V����
	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].Update();
	}

	//���Ԃ̌v��
	timeFrameCount++;
	if (timeFrameCount == 60)
	{
		timeFrameCount = 0;
		gametime--;
	}

	//��莞�Ԃ��ƂɃR�C�����Ĕz�u����
	if ((/*gametime == 10 || gametime == 30 || gametime == 50*/gametime % 10 == 0) && gametime > 0 && timeFrameCount == 0)
	{
		ShowCoin();

		return;
	}

	//�R�C�����ՖʂɎc���Ă��邩�m�F
	for (int i = 0; i < coinCount; i++)
	{
		//�c���Ă���΂����ŕԂ�
		if (coinPos[i].y != -100000.0f)
		{
			return;
		}
	}

	//�c���Ă��Ȃ����
	//�R�C�����ĂюT��
	ShowCoin();
}

int Coin::CoinGet(Vector3 pos)
{
	for (int i = 0; i < coinCount; i++)
	{
		//�L�����ƃR�C���̋������v�Z
		direction = 0.0f;
		float x = pos.x - coinPos[i].x;
		float y = pos.y + 200.0f - coinPos[i].y;
		float z = pos.z - coinPos[i].z;
		direction = x * x + y * y + z * z;
		direction = sqrtf(direction);

		//���ȉ��Ȃ�R�C���̍��W��ύX
		if (direction <= 300.0f)
		{
			coinPos[i] = { 0.0f,-100000.0f,0.0f };
			coinRender[i].SetPosition(coinPos[i]);
			return coinGetPoint;
		}
	}
	return coinNotGet;
}

void Coin::ShowCoin()
{
	for (int i = 0; i < coinCount; i++)
	{
		do
		{
			noSameFrag = false;
			//��������R�C���̍��W������
			selectCount = rand() % 275;
			countSaveList[i] = selectCount;

			//���W������ĂȂ����m�F
			for (int j = 0; j < i; j++)
			{
				if (countSaveList[j] == selectCount)
				{
					noSameFrag = true;
				}
			}
			//����ĂȂ�������J��Ԃ��I���
		} while (noSameFrag);

		//�R�C���̏���ݒ�
		coinPos[i] = allCoinPos[selectCount];
		coinRender[i].Init("Assets/modelData/coin/coin2.tkm");
		coinRender[i].SetPosition(coinPos[i]);
		coinRender[i].Update();
	}
}

void Coin::gameClear()
{
	if (gameAfterTimer >= maxBlancCount)
	{
		m_coinGameRes = FindGO<CoinGameResult>("coinGameResult");

		if (m_coinGameRes == nullptr)
		{
			gameEndFlag = true;

			m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");

			if (m_coinPlayer == nullptr)
			{
				DeleteGO(this);
			}
		}
	}
	else
	{
		wchar_t finishText[256];
		swprintf_s(finishText, 256, L"finish!");
		finishRender.SetText(finishText);
		finishRender.SetColor(Vector4::Gray);
		finishRender.SetPosition({ -100.0f,0.0f });

		gameAfterTimer++;

		if (gameAfterTimer >= maxBlancCount)
		{
			m_coinGameRes = NewGO<CoinGameResult>(1, "coinGameResult");
		}
	}
}

void Coin::Render(RenderContext& rc)
{
	//�S�Ă�`��
	stageRender.Draw(rc);
	finishRender.Draw(rc);

	for (int i = 0; i < coinCount; i++)
	{
		coinRender[i].Draw(rc);
	}
}