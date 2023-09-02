#pragma once
#include "CoinNumbers.h"

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;
class CoinGameResult;
class CoinUI;
class CoinGameResult;

class Coin : public IGameObject
{
public:
	Coin();
	~Coin();

	void Update();
	void Render(RenderContext& rc);
	int CoinGet(Vector3 pos);
	void ShowCoin();
	void gameClear();

	//�X�e�[�W��\�����郂�f�������_�[
	ModelRender stageRender;
	//�R�C����\�����郂�f�������_�[
	ModelRender coinRender[coinCount];
	//�X�e�[�W�̕�������
	PhysicsStaticObject stageObject;
	//���Ԃ̕\��
	FontRender finishRender;

	//���݂��Ă���R�C���̍��W
	Vector3 coinPos[coinCount];
	//�Q�[���̎���
	int gametime;
	//�Q�[�������t���O
	bool gameEndFlag = false;
private:
	//Vector3 cameraPos = { 0.0f, 12000.0f, 1.0f };
	//�R�C���̏o������S���W
	Vector3 allCoinPos[276];
	//��]
	Quaternion rotation;
	//�R�C���̑S���W��o�^���鎞�ɔz���i�߂邽�߂̕ϐ�
	int coinListCount = 0;
	//����
	float direction;
	//�t���[���̐i�݋��ۑ�����ϐ�
	int timeFrameCount;
	//����������Ă��Ȃ����̃t���O
	bool noSameFrag;
	//�����őI�΂ꂽ�l���󂯎��ϐ�
	int selectCount;
	//�o�Ă���R�C���̔ԍ����o����z��
	int countSaveList[coinCount];
	//�R�C����\������t���O
	bool showCoinFlag;
	//�Q�[���I����̑҂�����
	int gameAfterTimer;

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;
	CoinUI* m_coinUI;
	CoinGameResult* m_coinGameRes;
};

