#pragma once

//#include "geometry/"
#include "Light/SceneLight.h"

namespace nsK2EngineLow {

	class RenderingEngine;
	//class SceneLight;

	struct DirectionalLight
	{
		//���C�g�̕���
		Vector3 ligDirection;
		//�p�f�B���O
		float pad;
		//���C�g�̃J���[
		Vector4 ligColor;
	};

	struct PointLight
	{
		//���C�g�̈ʒu
		Vector3 ptPosition;
		float pad2;
		//���C�g�̃J���[
		Vector3 ptColor;
		//���C�g�̉e���͈�
		float ptRange;
	};

	struct Light
	{
		//�f�B���N�V�������C�g�̔z��(�ő�1�u����)
		DirectionalLight directionalLight;
		//�|�C���g���C�g�̔z��
		PointLight pointLight;

		//�J�����̈ʒu
		Vector3 eyePos;

		//����
		Vector3 ambientLight;
	};

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

		//���W�A��]�A�傫����S�Đݒ�
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
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

		//SceneLight sceneLight;
		
		//�V�[�����C�g�̃��C�g
		/*SLight slight;*/

		//�V�[�����C�g�̃f�B���N�V�������C�g
		SDirectionalLight sdirectionalLight;

		//�V�[�����C�g�̃|�C���g���C�g
		SPointLight spointLight;

		//�V�[�����C�g�̂��̂ق����C�g
		SOtherLight sotherLight;

		//���f�������_�[���̃f�B���N�V�������C�g
		//DirectionalLight directionalLight;

		//���C�g
		Light light;
	};
}

