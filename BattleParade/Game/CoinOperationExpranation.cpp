#include "stdafx.h"
#include "CoinOperationExpranation.h"
#include "CoinNumbers.h"
#include "CoinTitle.h"

CoinOperationExpranation::CoinOperationExpranation()
{
	operationRender.Init("Assets/sprite/coin/CC_operation.DDS", gameWidth, gameHeight);
	operationRender.Update();
}

CoinOperationExpranation::~CoinOperationExpranation()
{
	NewGO<CoinTitle>(0, "coinTitle");
}

void CoinOperationExpranation::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
	}
}

void CoinOperationExpranation::Render(RenderContext& rc)
{
	operationRender.Draw(rc);
}