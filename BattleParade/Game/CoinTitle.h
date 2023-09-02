#pragma once
class CoinTitle : public IGameObject
{
public:
	CoinTitle();
	~CoinTitle();
	void Update();
	void CursorManager();
	void CursorPosSet();
	void Render(RenderContext& rc);

	//タイトル画像表示
	SpriteRender titleRender;
	//カーソル画像表示
	SpriteRender cursorRender;

private:
	Vector3 cursorPos;
	int cursorPosSwitch;

};

