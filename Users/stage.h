#pragma once
#include "Input.h"
#include "objModel.h"
#include "Camera.h"
#include "Transform.h"

class stage
{
public:
	stage() = default;
	~stage() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);


private:
	//���[���h�ϊ��f�[�^
	Transform stageWorldTransform_;
	//���f��
	std::unique_ptr<objModel> stage_;
	char PADING[4]{};

	EngineMathF::Vector3 vector = {};

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	stage& operator=(const stage&) = delete;
	stage(const stage&) = delete;
};

