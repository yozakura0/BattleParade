#pragma once
class CoinOperationExpranation : public IGameObject
{
public:
	CoinOperationExpranation();
	~CoinOperationExpranation();
	void Update();
	void Render(RenderContext& rc);

	//‰æ‘œ‚Ì•\Ž¦
	SpriteRender operationRender;
};

