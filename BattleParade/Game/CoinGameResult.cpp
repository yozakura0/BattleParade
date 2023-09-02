#include "stdafx.h"
#include "CoinGameResult.h"
#include "CoinTitle.h"
#include "CoinPlayer.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIplayerThird.h"
#include "CoinNumbers.h"

CoinGameResult::CoinGameResult()
{
	resultBackRender.Init("Assets/sprite/CC_resultBack.DDS", gameWidth, gameHeight);

	for (int i = 0; i < charaCount; i++)
	{
		pointBackRender[i].Init("Assets/sprite/CC_charaResult.DDS",1300,135);
		pointRender[i].SetColor(Vector4::White);
	}

	m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");
	m_coinAI1 = FindGO<CoinAIplayerFirst>("coinAI1");
	m_coinAI2 = FindGO<CoinAIplayerSecond>("coinAI2");
	m_coinAI3 = FindGO<CoinAIplayerThird>("coinAI3");

	for (int i = 0; i < charaCount; i++)
	{
		charaPoints[0][i] = i;
	}
	charaPoints[1][0] = m_coinPlayer->charaPoint;
	charaPoints[1][1] = m_coinAI1->AI1Point;
	charaPoints[1][2] = m_coinAI2->AI2Point;
	charaPoints[1][3] = m_coinAI3->AI3Point;

	for (int i = 0; i < charaCount; i++)
	{
		for (int j = i + 1; j < charaCount; j++)
		{
			if (charaPoints[1][j] > charaPoints[1][i])
			{
				int storage;
				storage = charaPoints[1][i];
				charaPoints[1][i] = charaPoints[1][j];
				charaPoints[1][j] = storage;

				storage = charaPoints[0][i];
				charaPoints[0][i] = charaPoints[0][j];
				charaPoints[0][j] = storage;
			}
		}
	}

	for (int i = 0; i < charaCount; i++)
	{
		resultRankPos[i] = resultRankStartPos[i];
		pointBackPos[i] = pointBackStartPos[i];
	}

	wchar_t point1stText[256];
	swprintf_s(point1stText, 256, L"1: Player%d  %d", charaPoints[0][0] + 1, charaPoints[1][0]);
	pointRender[0].SetText(point1stText);

	wchar_t point2ndText[256];
	swprintf_s(point2ndText, 256, L"2: Player%d  %d", charaPoints[0][1] + 1, charaPoints[1][1]);
	pointRender[1].SetText(point2ndText);

	wchar_t point3rdText[256];
	swprintf_s(point3rdText, 256, L"3: Player%d  %d", charaPoints[0][2] + 1, charaPoints[1][2]);
	pointRender[2].SetText(point3rdText);

	wchar_t point4thText[256];
	swprintf_s(point4thText, 256, L"4: Player%d  %d", charaPoints[0][3] + 1, charaPoints[1][3]);
	pointRender[3].SetText(point4thText);
}

CoinGameResult::~CoinGameResult()
{
	NewGO<CoinTitle>(0, "coinTitle");
}

void CoinGameResult::Update()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		DeleteGO(this);
	}

	ResultSlideManage();

	for (int i = 0; i < charaCount; i++)
	{
		pointBackRender[i].SetPosition(pointBackPos[i]);
		pointRender[i].SetPosition(resultRankPos[i]);
		pointBackRender[i].Update();
	}
}

void CoinGameResult::ResultSlideManage()
{
	if (slideFinishFlag[0] != true)
	{
		ResultSlide(0);
	}
	else if (slideFinishFlag[1] != true)
	{
		ResultSlide(1);
	}
	else if (slideFinishFlag[2] != true)
	{
		ResultSlide(2);
	}
	else if (slideFinishFlag[3] != true)
	{
		ResultSlide(3);
	}
}

void CoinGameResult::ResultSlide(int number)
{
	resultRankPos[number].x -= 100.0f;
	pointBackPos[number].x -= 100.0f;

	if (pointBackPos[number].x <= 0)
	{
		slideFinishFlag[number] = true;
	}
}

void CoinGameResult::Render(RenderContext& rc)
{
	resultBackRender.Draw(rc);

	for (int i = 0; i < charaCount; i++)
	{
		pointBackRender[i].Draw(rc);
		pointRender[i].Draw(rc);
	}
}