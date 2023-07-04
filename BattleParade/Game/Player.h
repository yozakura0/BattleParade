#pragma once

class Nib;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void State();
	void Animation();

	ModelRender Character;
	Vector3 CharaPos;
	Quaternion CharaRot;
	CharacterController playerController;
	Vector3 moveSpeed;

	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Fall,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};

	Nib* nib;
	AnimationClip AnimationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B

	//�X�e�B�b�N�̓��͗ʂ�ۑ�����ϐ�
	Vector3 StickL;

	//�v���C���[�̏��
	int P_state = 0;

	//�t���O��
	bool fall = false;
	bool walk = false;
	bool attack = false;
};

