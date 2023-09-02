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

	//�^�C�g���摜�\��
	SpriteRender titleRender;
	//�J�[�\���摜�\��
	SpriteRender cursorRender;

private:
	Vector3 cursorPos;
	int cursorPosSwitch;

};

