#pragma once
#include"Model.h"


class ModelCube :public Model
{
private:
	//�L���[�u�̃C���f�b�N�X���ƒ��_��
	const UINT cubeMaxIndex = 36;
	const UINT cubeMaxVert = 24;

public:
	ModelCube();
	~ModelCube();


	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	void Draw(Transform* transform, Material* material)override;

	//������
	void Initialize()override;

private:

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(bool smoothing = false)override;

	virtual void Create(const char* filePath, bool smoothing = false);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelCube& operator=(const ModelCube&) = delete;
	ModelCube(const ModelCube&) = delete;
};

