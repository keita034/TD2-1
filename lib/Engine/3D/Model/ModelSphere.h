#pragma once
#include "Model.h"
#include"DirectX12Core.h"

class ModelSphere : public Model
{
private:
	//���̃C���f�b�N�X���ƒ��_��
	const UINT sphereMaxIndex = 3072;
	const UINT sphereMaxVert = 560;

public:

	ModelSphere();
	~ModelSphere();

	//������
	virtual void Initialize()override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	virtual void Draw(Transform* transform, Material* material)override;

private:

	virtual void Create(const char* filePath, bool smoothing = false);

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(bool smoothing = false)override;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelSphere& operator=(const ModelSphere&) = delete;
	ModelSphere(const ModelSphere&) = delete;
};

