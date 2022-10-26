#pragma once
#include"ErrorException.h"
#include"EngineMathUtility.h"
#include"Camera.h"

class Transform
{
private:
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	worldViewpojCamera* constBuffMap = nullptr;

public:
	// ���[�J�����W
	EngineMathF::Vector3 translation = { 0, 0, 0 };
	// X,Y,Z�����̃��[�J����]�p
	EngineMathF::Vector3 rotation = { 0, 0, 0 };
	// ���[�J���X�P�[��
	EngineMathF::Vector3 scale = { 1, 1, 1 };

	EngineMathF::Matrix4 matWorld;
private:
	char PADDING[4]{};
public:
	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
	const Transform* parent = nullptr;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �s���]������
	/// </summary>
	void TransUpdate(Camera* camera);

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();


};

namespace EngineMathF
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ���[���h���W�擾
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}