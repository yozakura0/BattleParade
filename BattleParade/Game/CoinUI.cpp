#include "stdafx.h"
#include "CoinUI.h"
#include "Coin.h"
#include "CoinPlayer.h"
#include "CoinAIplayerFirst.h"
#include "CoinAIplayerSecond.h"
#include "CoinAIplayerThird.h"
#include "CoinNumbers.h"

CoinUI::CoinUI()
{
	UIbackRender.Init("Assets/sprite/coin/CC_gameUI.DDS", gameWidth, gameHeight);

	for (int i = 0; i < charaCount; i++)
	{
		pointRender[i].SetColor(Vector4::Black);
	}
}

CoinUI::~CoinUI()
{

}

void CoinUI::Update()
{
	m_coin = FindGO<Coin>("coin");
	m_coinPlayer = FindGO<CoinPlayer>("coinPlayer");
	m_coinAI1 = FindGO<CoinAIplayerFirst>("coinAI1");
	m_coinAI2 = FindGO<CoinAIplayerSecond>("coinAI2");
	m_coinAI3 = FindGO<CoinAIplayerThird>("coinAI3");

	if (m_coin->gameEndFlag)
	{
		DeleteGO(this);
	}

	if (m_coin != nullptr && m_coinPlayer != nullptr && m_coinAI1 != nullptr && m_coinAI2 != nullptr && m_coinAI3 != nullptr)
	{
		wchar_t timeText[256];
		swprintf_s(timeText, 256, L"%d", m_coin->gametime);
		timeRender.SetText(timeText);
		timeRender.SetScale(2.0f);
		timeRender.SetPosition(timePos);

		wchar_t charaPointText[256];
		swprintf_s(charaPointText, 256, L"%d", m_coinPlayer->charaPoint);
		pointRender[0].SetText(charaPointText);
		pointRender[0].SetScale(2.0f);
		pointRender[0].SetPosition(charaPointPos);

		wchar_t AI1PointText[256];
		swprintf_s(AI1PointText, 256, L"%d", m_coinAI1->AI1Point);
		pointRender[1].SetText(AI1PointText);
		pointRender[1].SetScale(2.0f);
		pointRender[1].SetPosition(AI1PointPos);

		wchar_t AI2PointText[256];
		swprintf_s(AI2PointText, 256, L"%d", m_coinAI2->AI2Point);
		pointRender[2].SetText(AI2PointText);
		pointRender[2].SetScale(2.0f);
		pointRender[2].SetPosition(AI2PointPos);

		wchar_t AI3PointText[256];
		swprintf_s(AI3PointText, 256, L"%d", m_coinAI3->AI3Point);
		pointRender[3].SetText(AI3PointText);
		pointRender[3].SetScale(2.0f);
		pointRender[3].SetPosition(AI3PointPos);

		UIbackRender.Update();
	}
}

void CoinUI::Render(RenderContext& rc)
{
	UIbackRender.Draw(rc);
	timeRender.Draw(rc);
	for (int i = 0; i < charaCount; i++)
	{
		pointRender[i].Draw(rc);
	}
}