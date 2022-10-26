#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"EngineMathUtility.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include "Camera.h"
#include"Particle.h"
//pragma comment



//using namespace


class BasicParticle : public Particle
{
private:

	EngineMathF::Matrix4 mTrans, mRot, mScale;

public:

	BasicParticle() = default;
	~BasicParticle() = default;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	///<summary>
	///�ǂݍ���
	///</summary>
	///<param name="filePath">�t�@�C���p�X</param>
	virtual void Load(const wchar_t* filePath)override;

	///<summary>
	///�X�V
	///</summary>
	virtual void Update()override;

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="life">��������</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	/// <param name="accel">�����x</param>
	/// <param name="scale">{�J�n���X�P�[��,�I�����X�P�[��}</param>
	/// <param name="rotation">{�J�n����]�p,�I������]�p}</param>
	/// <param name="sColor">�J�n�J���[</param>
	/// <param name="eColor">�I���J���[</param>
	virtual void Add(
		UINT life, EngineMathF::Vector3& position, EngineMathF::Vector3& velocity,
		EngineMathF::Vector3& accel, EngineMathF::Vector2& scale, EngineMathF::Vector2& rotation
		, EngineMathF::Vector4& sColor, EngineMathF::Vector4& eColor)override;


	///<summary>
	///�r���{�[�h�`��
	///</summary>
	virtual void Draw(Camera* camera)override;

private:

	//�V�F�[�_�|���\�[�X�r���[��
	virtual void CreateShaderResourceView();
	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	virtual void CreatConstBuff();
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer();
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	BasicParticle& operator=(const BasicParticle&) = delete;
	BasicParticle(const BasicParticle&) = delete;
};

