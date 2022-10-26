#pragma once

#include "objModel.h"
#include "Transform.h"

class sky
{
public:
	sky();
	~sky();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

private:
	// ���[���h�ϊ��f�[�^
	Transform worldTransform_;
	// ���f��
	std::unique_ptr<objModel> model_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	sky& operator=(const sky&) = delete;
	sky(const sky&) = delete;
};

