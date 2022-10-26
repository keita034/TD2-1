#pragma once
#include"EngineMathUtility.h"
#include"DirectX12Core.h"

class ModelPipeLine
{
private:
	PipelineSet lambert{};
	PipelineSet phong{};
	PipelineSet dfault{};
	static ModelPipeLine* instance;
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	char pading[4]{};
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ModelPipeLine* GetInstance();

	/// <summary>
	/// ���
	/// </summary>
	void Destroy();

	/// <summary>
	/// �f�t�H���g���˃p�C�v���C���擾
	/// </summary>
	/// <returns>�p�C�v���C��</returns>
	PipelineSet* GetDefaultPipeline();

	/// <summary>
	/// �����o�[�g���˃p�C�v���C���擾
	/// </summary>
	/// <returns>�p�C�v���C��</returns>
	PipelineSet* GetLambertPipeline();

	/// <summary>
	/// �t�H���O���˃p�C�v���C���擾
	/// </summary>
	/// <returns>�p�C�v���C��</returns>
	PipelineSet* GetPhongPipeline();

private:
	ModelPipeLine() = default;
	~ModelPipeLine() = default;

	//�f�t�H���g
	void CreatDefaultPipeline();

	//�����o�[�g
	void CreatLambertPipeline();

	//�t�H���O
	void CreatPhongPipeline();
};

