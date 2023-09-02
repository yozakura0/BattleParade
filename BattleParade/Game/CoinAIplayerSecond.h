#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerThird;

class Coin;

class CoinAIplayerSecond : public IGameObject
{
public:
	CoinAIplayerSecond();
	~CoinAIplayerSecond();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//��������
	CharacterController secondAIController;
	//�����蔻��
	PhysicsGhostObject secondAIGhostObject;

	//�G�L������\�����郂�f�������_�[
	ModelRender secondCoinAIRender;

	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};
	AnimationClip animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B

	//�^�b�N�����Ă��邩�̔���
	bool secondAITackleFlag = false;
	//AI2�̓��_
	int AI2Point;
	//�ꏊ
	Vector3 secondAIPos;
private:
	//�ړ����x
	Vector3 secondAIMoveSpeed;
	//1�t���[���O�̍��W
	Vector3 secondAIdifference;
	//�L�������C�₵�Ă��邩
	bool secondAIStunFlag = false;
	//�C�₵�Ă��鎞��
	int secondAIStunTime;
	//�v���C���[�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTacklePto2 = false;
	//AI1�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle1to2 = false;
	//AI3�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle3to2 = false;
	//����
	float direction;
	//����]
	Quaternion noneRotation;
	//�^�b�N�����󂯂Ĕ��ł�������
	Vector3 receiveTackleMoveVec;
	//�^�b�N�����󂯂Ĕ��ł������������肷�邩�̃t���O
	bool receiveTackleVecFlag;

	CoinAIActs* coinAIActs;

	CoinPlayer* m_coinPlayer;
	CoinAIplayerFirst* m_coinAI1;
	CoinAIplayerThird* m_coinAI3;

	Coin* m_coin;
};

