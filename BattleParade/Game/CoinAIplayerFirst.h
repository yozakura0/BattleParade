#pragma once

class CoinAIActs;

class CoinPlayer;
class CoinAIplayerSecond;
class CoinAIplayerThird;

class Coin;

class CoinAIplayerFirst : public IGameObject
{
public:
	CoinAIplayerFirst();
	~CoinAIplayerFirst();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ReceiveTackle();
	void PointManager();

	//��������
	CharacterController firstAIController;
	//�����蔻��
	PhysicsGhostObject firstAIGhostObject;

	//�G�L������\�����郂�f�������_�[
	ModelRender firstCoinAIRender;

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
	bool firstAITackleFlag = false;
	//AI1�̓��_
	int AI1Point;
	//�ꏊ
	Vector3 firstAIPos;
private:
	//�ړ����x
	Vector3 firstAIMoveSpeed;
	//1�t���[���O�̍��W
	Vector3 firstAIdifference;
	//�^�b�N�����̌���
	Vector3 tackleMove;
	//�L�������C�₵�Ă��邩
	bool firstAIStunFlag = false;
	//�C�₵�Ă��鎞��
	int firstAIStunTime;
	//�v���C���[�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTacklePto1 = false;
	//AI2�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle2to1 = false;
	//AI3�Ƀ^�b�N�����ꂽ�t���O
	bool receiveTackle3to1 = false;
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
	CoinAIplayerSecond* m_coinAI2;
	CoinAIplayerThird* m_coinAI3;

	Coin* m_coin;
};

