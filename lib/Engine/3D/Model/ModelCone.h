#pragma once
#include "Model.h"

class ModelCone : public Model
{
private:
	//�~���̃C���f�b�N�X���ƒ��_��
	const UINT coneMaxIndex = 191;
	const UINT coneMaxVert = 66;

public:

	ModelCone();
	~ModelCone();

	//������
	virtual void Initialize()override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	virtual void Draw(Transform* transform, Material* material)override;

private:


	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(bool smoothing = false)override;

	virtual void Create(const char* filePath, bool smoothing = false);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelCone& operator=(const ModelCone&) = delete;
	ModelCone(const ModelCone&) = delete;
};

