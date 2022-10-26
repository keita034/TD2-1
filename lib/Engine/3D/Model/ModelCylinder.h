#pragma once
#include "Model.h"

class ModelCylinder : public Model
{
private:
	//�~���̃C���f�b�N�X���ƒ��_��
	const UINT cylinderMaxIndex = 384;
	const UINT cylinderMaxVert = 132;

public:

	ModelCylinder();
	~ModelCylinder();

	//������
	virtual void Initialize()override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	void Draw(Transform* transform, Material* material);

private:

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(bool smoothing = false)override;

	virtual void Create(const char* filePath, bool smoothing = false);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelCylinder& operator=(const ModelCylinder&) = delete;
	ModelCylinder(const ModelCylinder&) = delete;
};

