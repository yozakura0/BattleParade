#pragma once
//�Q�[���V�X�e��
const float gameWidth = 1920.0f;		//��ʂ̉���
const float gameHeight = 1080.0f;		//��ʂ̏c��
const int maxGameTime = 60;				//�Q�[���̎���
const int maxBlancCount = 180;			//�Q�[���O��̌��Ԃ̎���(�t���[���P��)
const int coinCount = 30;				//�R�C���̖���
const int AICount = 3;					//CPU�L�����̐�
const int charaCount = AICount + 1;		//�S�v���C���[�̐�
const int coinGetPoint = 1;				//�R�C������肵�����̓_
const int coinNotGet = 0;				//�R�C������肵�ĂȂ����̓_
const int fallPenalty = 3;				//���������̃y�i���e�B
const int tackleResultPoint = 3;		//�^�b�N���ɂ���đ������链�_

//�J�����̏��
const Vector3 CameraPos = { 0.0f, 12000.0f, 5000.0f };	//�J�����̍��W
const Vector3 CameraTargetPos = { 0.0f,0.0f,0.0f };		//�J�����̌������W
const float CameraFar = 15000.0f;						//�J�����̉�����

//�L�������ʔԍ�
const int mychara = 0;					//���L�����̔ԍ�
const int firstAI = 1;					//1�l�ڂ�AI�ԍ�
const int secondAI = 2;					//2�l�ڂ�AI�ԍ�
const int thirdAI = 3;					//3�l�ڂ�AI�ԍ�

//�L�����֌W�̏��
const Vector3 scaleMultiply = { 5.0f,5.0f,5.0f };			//�L�������f����傫������{��
const Vector3 startCharaPos = { 0.0f, 1000.0f, -5000.0f };	//�ŏ��̎��L�����̏ꏊ
const Vector3 startAI1Pos = { 5200.0f,1000.0f,0.0f };		//�ŏ���AI1�̏ꏊ
const Vector3 startAI2Pos = { -5200.0f,1000.0f,0.0f };		//�ŏ���AI2�̏ꏊ
const Vector3 startAI3Pos = { 0.0f,1000.0f,5000.0f };		//�ŏ���AI3�̏ꏊ
const float capsuleRadius = 200.0f;					//�����蔻��̔��a
const float capsuleHeight = 240.0f;					//�����蔻��̍���
const float controllerRadius = 120.0f;				//��������̔��a
const float controllerHeight = 240.0f;				//��������̍���
const float gravity = 75.0f;						//�d�͂̋���
const float jumpPower = 3550.0f;					//�W�����v�̋���
const float moveMultiply = 900.0f;					//�ړ����x�̔{��
const float stickMultiply = -1200.0f;				//�X�e�B�b�N���͗ʂւ̔{��

//�^�b�N���֌W�̏��
const int fullChargeCount = 120;					//�^�b�N�����\�ɂȂ�`���[�W��
const int tackleTimeCount = 30;						//�^�b�N�������鎞��
const int tackleMoveMultiply = 4;					//�^�b�N�����̈ړ����x�ւ̔{��
const int stunTime = 90;							//�X�^����Ԃ̎���
const float tackleMoveWeaken = 1.1;					//��^�b�N����̈ړ����x�̌�����
const float receiveTackleMoveMultiply = 10000.0f;	//��^�b�N�����̈ړ����x�ւ̔{��

//�A�j���[�V�����̔ԍ�
const int animation_idle = 0;		//�����A�j���[�V�����X�e�[�g
const int animation_walk = 1;		//�����A�j���[�V�����X�e�[�g
const int animation_fall = 2;		//�����A�j���[�V�����X�e�[�g
const int animation_jump = 3;		//�W�����v�A�j���[�V�����X�e�[�g
const int animation_run = 4;		//����A�j���[�V�����X�e�[�g

//UI�֌W�̏��
const Vector2 timePos = { -50.0f,500.0f };				//���Ԃ�\��������W
const Vector2 charaPointPos = { -900.0f,500.0f };		//�v���C���[�̓��_��\��������W
const Vector2 AI1PointPos = { 800.0f,500.0f };			//AI1�̓��_��\��������W
const Vector2 AI2PointPos = { -900.0f,-425.0f };		//AI2�̓��_��\��������W
const Vector2 AI3PointPos = { 800.0f,-425.0f };			//AI3�̓��_��\��������W

//�^�C�g����ʂ̏��
const Vector3 startButtonPos = { 0.0f,100.0f,0.0f };	//�Q�[���J�n�̃{�^���̍��W
const Vector3 operationButtonPos = { 0.0f,0.0f,0.0f };	//��������̃{�^���̍��W
const int startButtonNumber = 0;						//�Q�[���J�n�̃{�^����\���ԍ�
const int operationButtonNumber = 1;					//��������̃{�^����\���ԍ�
const float cursorWidth = 150.0f;						//�J�[�\���̉���
const float cursorHeight = 130.0f;						//�J�[�\���̏c��

//�t�F�[�h�̏��
const int fadeOutFrag = 0;		//�t�F�[�h�A�E�g������t���O
const int fadeInFrag = 1;		//�t�F�[�h�C��������t���O
const int fadeIdleFlag = 2;		//�t�F�[�h�ҋ@��Ԃ̃t���O
const int fadeTime = 60;		//�t�F�[�h�̎���

//���ʉ�ʂ̏��
const Vector2 resultRankStartPos[charaCount] = {
	{990.0f, 350.0f},		//�����L���O1�ʂ̐l��\��������W
	{990.0f, 100.0f},		//�����L���O2�ʂ̐l��\��������W
	{990.0f,-100.0f},		//�����L���O3�ʂ̐l��\��������W
	{990.0f,-350.0f}		//�����L���O4�ʂ̐l��\��������W
};
const Vector3 pointBackStartPos[charaCount] = {
	{1000.0f,  350.0f, 0.0f},
	{1000.0f,  100.0f, 0.0f},
	{1000.0f, -100.0f, 0.0f},
	{1000.0f, -350.0f, 0.0f}
};