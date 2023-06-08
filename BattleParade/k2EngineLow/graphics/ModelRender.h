#pragma once

//#include "geometry/"

namespace nsK2EngineLow {
	class RenderingEngine;

	class ModelRender :public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		//���f�������_�[�̏�����
		void Init(
			//�t�@�C���̃p�X
			const char* filePath
			////�A�j���[�V�����N���b�v
			//AnimationClip* animationClips = nullptr,
			////�A�j���[�V�����N���b�v�̐�
			//int numAnimationClips = 0,
			////���f���̏�����̐ݒ�
			//EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);

		//�X�V����
		void Update();

		//�`�揈��
		void Draw(RenderContext& rc);

		//�A�j���[�V�����̍Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			//m_animation.Play(animNo, interpolateTime);
		}

		//���W�̐ݒ�
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		//���W�̐ݒ�
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//��]�̐ݒ�
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		//�g�嗦�̐ݒ�
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//�g�嗦�̐ݒ�
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

	private:
		////�X�P���g���̏�����
		//void InitSkeleton(
		//	//�t�@�C���p�X
		//	const char* filepath
		//);

		////�A�j���[�V�����̏�����
		//void InitAnimation(
		//	//�A�j���[�V�����N���b�v
		//	//AnimationClip* animationClips = nullptr,
		//	//�A�j���[�V�����N���b�v�̐�
		//	int numAnimationClips = 0
		//	//���f���̏����
		//	//EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		//);

		//�e�탂�f���̃��[���h���W���X�V����
		void  UpdateWorldMatrixInModes();

		//�e�탂�f���̒��_�V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
		//void SetupVertexShaderEntryPointFunc(ModelInitData& modelInitData);

	private:
		//�A�j���[�V�����N���b�v
		//AnimationClip* m_animationClips = nullptr;
		//�A�j���[�V�����N���b�v�̐�
		//int m_numAnimationClips = 0;
		//���W
		Vector3 m_position = Vector3::Zero;
		//��]
		Quaternion m_rotation = Quaternion::Identity;
		//�g�嗦
		Vector3 m_scale = Vector3::One;
		//�A�j���[�V����
		//Animation m_animation;
		//���f��
		Model m_Model;
		//���f���̏������f�[�^
		ModelInitData m_modelInitData;
		//�t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
		//Model m_forwardRenderModel;
		//RenderToGBuffer�ŕ`�悳��郂�f��
		//Model m_renderToGBufferModel;
		//�X�P���g��
		Skeleton m_skeleton;
		//�A�j���[�V�����̍Đ����x
		//float m_animationSpeed = 1.0f;
		//�W�I���g�����
		//std::vector<Gemo>
		
	};
}
