#pragma once
#include"objModel.h"
#include"Transform.h"
#include"Camera.h"
#include"CollisionPrimitive.h"

class Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, float radius, objModel* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	//�R���C�_�[����
	SPHERE& GetCollider();

	//�����������̊֐�
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	SPHERE collider_;
	objModel* model_;
	std::unique_ptr<Transform> worldTransform_;
};