#pragma once
#include "CoinNumbers.h"

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class CoinGameResult : public IGameObject
{
public:
	CoinGameResult();
	~CoinGameResult();
	void Update();
	void ResultSlide(int number);
	void ResultSlideManage();
	void Render(RenderContext& rc);

	//���ʉ�ʂ̔w�i�̕\��
	SpriteRender resultBackRender;
	//�L�����̏��ʂ̔w�i�̕\��
	SpriteRender pointBackRender[charaCount];
	//���_�̕\��
	FontRender pointRender[charaCount];

private:
	int charaPoints[2][charaCount];		//�e�L�����̓��_�ƃL����
	Vector2 resultRankPos[charaCount];	//�����L���O�̕\���ꏊ
	Vector3 pointBackPos[charaCount];	//���_�̔w�i�̕\���ꏊ
	bool slideFinishFlag[charaCount];	//���ړ��������������ǂ����̃t���O

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;
};

