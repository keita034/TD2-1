#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"
#include"DirectX12Core.h"

/// <summary>
/// ���C�g
/// </summary>

struct LightConstBuffData
{
	EngineMathF::Vector3 lightv;//���C�g�ւ̕����x�N�g��
	EngineMathF::Vector4 lightcolor;//���C�g�̐F
};

class Light
{
private:
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//�萔�o�b�t�@�̃}�b�v
	LightConstBuffData* constMap;
	//���C�g��������(�P�ʃx�N�g��)
	EngineMathF::Vector3 lightdir = {1,0,0};
	//���C�g�̐F
	EngineMathF::Vector4 lightcolor = { 1,1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;
	char PADDING[3]{};
public:

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Light* Create();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�փf�[�^�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ���C�g�����̃Z�b�g
	/// </summary>
	/// <param name="lightdir_">���C�g����</param>
	void SetLightDir(EngineMathF::Vector3& lightdir_);

	/// <summary>
	/// ���C�g�F�̃Z�b�g
	/// </summary>
	/// <param name="lightdir_">���C�g����</param>
	void SetLightColor(const EngineMathF::Vector4& lightcolor_);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �萔�o�b�t�@�r���[�̃Z�b�g
	/// </summary>
	/// <param name="cmdlist">�R�}���h���X�g</param>
	/// <param name="rootParameterIndex">�p�����[�^�[�ԍ�</param>
	void SetConstBufferView(ID3D12GraphicsCommandList* cmdList,UINT rootParameterIndex);
private:
};