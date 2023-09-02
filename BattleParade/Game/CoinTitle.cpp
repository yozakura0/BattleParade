#include "stdafx.h"
#include "CoinTitle.h"
#include "CoinNumbers.h"
#include "Coin.h"
#include "CoinOperationExpranation.h"

CoinTitle::CoinTitle()
{
	titleRender.Init("Assets/sprite/coin/CC_title.DDS", gameWidth, gameHeight);
	cursorRender.Init("Assets/sprite/coin/CC_titleCursor.DDS", cursorWidth, cursorHeight);
	titleRender.Update();
}

CoinTitle::~CoinTitle()
{
	if (cursorPosSwitch == operationButtonNumber)
	{
		NewGO<CoinOperationExpranation>(0, "CoinOperationExpranation");
	}
	else
	{
		NewGO<Coin>(0, "coin");
	}
}

void CoinTitle::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
	}

	CursorManager();
	CursorPosSet();

	cursorRender.Update();
}

void CoinTitle::CursorManager()
{
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
	{
		cursorPosSwitch++;

		if (cursorPosSwitch > operationButtonNumber)
		{
			cursorPosSwitch = startButtonNumber;
		}
	}
}

void CoinTitle::CursorPosSet()
{
	switch (cursorPosSwitch)
	{
	case startButtonNumber:
		cursorPos = startButtonPos;
		break;
	case operationButtonNumber:
		cursorPos = operationButtonPos;
		break;
	default:
		break;
	}

	cursorRender.SetPosition(cursorPos);
}

void CoinTitle::Render(RenderContext& rc)
{
	titleRender.Draw(rc);
	cursorRender.Draw(rc);
}