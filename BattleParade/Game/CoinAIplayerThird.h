#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerFirst;
class CoinAIplayerSecond;

class Coin;

class CoinAIplayerThird : public IGameObject
{
public:
	CoinAIplayerThird();
	~CoinAIplayerThird();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//��������
	CharacterController thirdAIController;
	//�����蔻��
	PhysicsGhostObject thirdAIGhostObject;

	//�G�L������\�����郂�f�������_�[
	ModelRender thirdCoinAIRender;

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
	bool thirdAITackleFlag = false;
	//AI3�̓��_
	int AI3Point;
	//�ꏊ
	Vector3 thirdAIPos;
private:
	//�ړ����x
	Vector3 thirdAIMoveSpeed;
	//1�t���[���O�̍��W
	Vector3 thirdAIdifference;
	//�L�������C�₵�Ă��邩
	bool thirdAIStunFlag = false;
	//�C�₵�Ă��鎞��
	int thirdAIStunTime;
	//�v���C���[�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTacklePto3 = false;
	//AI1�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle1to3 = false;
	//AI2�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle2to3 = false;
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
	CoinAIplayerSecond* m_coinAI2;

	Coin* m_coin;
};

