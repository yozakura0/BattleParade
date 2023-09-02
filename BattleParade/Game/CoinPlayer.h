#pragma once

class CoinAIplayerFirst;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class Coin;

class CoinPlayer : public IGameObject
{
public:
	CoinPlayer();
	~CoinPlayer();
	void Update();
	void Move();
	void StateManagement();
	void Animation();
	void ReceiveTackle();
	void PointManager();
	void Render(RenderContext& rc);

	//�L�����̃��f�������_�[
	ModelRender charaRender;
	//�L�����̕�������
	CharacterController playerController;
	//�L�����̓����蔻��
	PhysicsGhostObject playerGhostObject;

	//�L�����̏ꏊ
	Vector3 charaPos;
	//�L�����̓��_
	int charaPoint;
	//�^�b�N�����Ă��邩
	bool tackleFlag = false;
private:

	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};
	AnimationClip animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	//�A�j���[�V�����̃X�e�[�g
	int animationState;

	//�L�����̈ړ����x
	Vector3 charaMoveSpeed = { 0.0f, 0.0f, 0.0f };
	//���X�e�B�b�N�̓��͂̎擾
	Vector3 StickL;
	//��]
	Quaternion rotation;
	//����]
	Quaternion noneRotation;
	//����
	float direction;
	//�L�������W�����v���Ă��邩
	bool playerJumpingFlag;
	//�L�������C�₵�Ă��邩
	bool playerStunFlag = false;
	//�C�₵�Ă��鎞��
	int playerStunTime;
	//�L�����̃^�b�N���̗͂𗭂߂���
	int playerCharge;
	//�L�����̃^�b�N���̗͂����܂�؂������ǂ���
	bool playerFullChargeFlag = false;
	//�L�����̃^�b�N���̎c�莞��
	int playerTackleTime;
	//�^�b�N�����̌���
	Vector3 tackleMove;
	//�L�����̌����̉�]
	Quaternion charaRotation;
	//�^�b�N�����󂯂Ĕ��ł�������
	Vector3 receiveTackleMoveVec;
	//�^�b�N���󂯂Ĕ��ł������������肷�邩�̃t���O
	bool receiveTackleVecFlag;

	//AI1�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackleAI1 = false;
	//AI2�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackleAI2 = false;
	//AI3�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackleAI3 = false;

	CoinAIplayerFirst* m_coinAI1 = nullptr;
	CoinAIplayerSecond* m_coinAI2 = nullptr;
	CoinAIplayerThird* m_coinAI3 = nullptr;

	Coin* m_coin;
};

