#pragma once
class CoinOperationExpranation : public IGameObject
{
public:
	CoinOperationExpranation();
	~CoinOperationExpranation();
	void Update();
	void Render(RenderContext& rc);

	//�摜�̕\��
	SpriteRender operationRender;
};

