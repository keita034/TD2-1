#pragma once
#pragma once
/// <summary>
///�����蔻��v���~�e�B�u
/// </summary>

#include"EngineMathUtility.h"
#include"Transform.h"

class BaseCollsion
{
protected:

	uint32_t collisionAttribute = 0xffffffff;
	//�Փ˃}�X�N(����)
	uint32_t CollisionMask = 0xffffffff;

	//���O(����)
	std::string collsionName;
	//���O(����)
	char opponentCollsionName[256];

	virtual ~BaseCollsion() = default;

public:
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision() = 0;
	//�Փˑ���(����)���擾
	const uint32_t GetCollisionAttribute();
	//�Փˑ���(����)���擾
	void SetCollisionAttribute(uint32_t collisionAttribute_);
	//�Փˑ���(����)���擾
	const uint32_t GetCollisionMask();
	//�Փˑ���(����)��ݒ�
	void SetCollisionMask(uint32_t CollisionMask_);

	void SetCollsionName(std::string name);
	std::string GetCollsionName();

	void SetOpponentCollsionName(std::string name);
	std::string GetOpponentCollsionName();
};

/// <summary>
/// ��
/// </summary>
class Sphere : public BaseCollsion
{
protected:

	//���S���W
	EngineMathF::Vector4 center = { 0.0f,0.0f,0.0f,1.0f };
	//���a
	float radius = 1.0f;
private:
	char PADING[4]{};

public:

	//���a���擾
	const float GetRadius();
	//���a����ݒ�
	void SetRadius(float radius_);
	//���S���W���擾
	const EngineMathF::Vector4& GetCenter();
	//���S���W����ݒ�
	void SetCenter(EngineMathF::Vector4& center_);
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision()
	{
	};
};

/// <summary>
/// ����
/// </summary>
class Plane : public BaseCollsion
{
protected:
	//�@���x�N�g��
	EngineMathF::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
	//���_�_(0,0,0)����̋���
	float distance = 0.0f;
private:
	char PADING[4]{};
public:
	//���_�_(0,0,0)����̋������擾
	const float GetDistance();
	//���_�_(0,0,0)����̋�����ݒ�
	void SetDistance(float distance_);
	//�@���x�N�g�����擾
	const EngineMathF::Vector4& GetNormal();
	//�@���x�N�g����ݒ�
	void SetNormal(EngineMathF::Vector4& normal_);
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision()
	{
	};
};

/// <summary>
/// �@���t���O�p�`(���v��肪�\��)
/// </summary>
class Triangle : public BaseCollsion
{
protected:

	//���_���W3��
	EngineMathF::Vector4 p0;
	EngineMathF::Vector4 p1;
	EngineMathF::Vector4 p2;
	//�@���x�N�g��
	EngineMathF::Vector4 normal;

public:
	/// <summary>
	/// �@���̌v�Z
	/// </summary>
	void ComputeNormal();

	//���_���W1�ڎ擾
	const EngineMathF::Vector4& GetP0();
	//���_���W1�ڂ�ݒ�
	void SetP0(EngineMathF::Vector4& p0_);

	//���_���W2�ڂ��擾
	const EngineMathF::Vector4& GetP1();
	//���_���W2�ڂ�ݒ�
	void SetP1(EngineMathF::Vector4& p1_);

	//���_���W3�ڂ��擾
	const EngineMathF::Vector4& GetP2();
	//���_���W3�ڂ�ݒ�
	void SetP2(EngineMathF::Vector4& p2_);

	//�@���x�N�g�����擾
	const EngineMathF::Vector4& GetNormal();
	//�@���x�N�g����ݒ�
	void SetNormal(EngineMathF::Vector4& normal_);
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision()
	{
	};
};

/// <summary>
/// ���C(������)
/// </summary>
class Ray : public BaseCollsion
{
protected:

	//�n�_���W
	EngineMathF::Vector4 start = { 0,0,0,1 };
	//����
	EngineMathF::Vector4 dir = { 1,0,0,0 };

public:

	//�n�_���W���擾
	const EngineMathF::Vector4& GetStart();
	//�n�_���W��ݒ�
	void SetStart(EngineMathF::Vector4& start_);

	//�������擾
	const EngineMathF::Vector4& GetDir();
	//������ݒ�
	void SetDir(EngineMathF::Vector4& dir_);
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision()
	{
	};
};

class RayCast : public Ray
{
protected:
	//����
	float range = 0.0f;
private:
	char PADING[4]{};
public:
	//���a���擾
	const float GetRange();
	//���a����ݒ�
	void SetRange(float range_);
};

class OBB : public BaseCollsion
{
protected:
	EngineMathF::Vector3 center = {};//�ʒu
	EngineMathF::Vector3 normaDirect[3];//�����x�N�g��
	float Length[3]{};// �e�������̒���
private:
	char PADING[4]{};
public:
	const EngineMathF::Vector3 GetDirect(uint16_t elem);//�w�莲�ԍ��̕����x�N�g�����擾
	const float GetLen(uint16_t elem);// �w�莲�����̒������擾
	const EngineMathF::Vector3 GetCenter();// �ʒu���擾
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision()
	{
	};

	void CreateOBB(std::vector<PosNormalUv> vertex_,Transform& transform);

	void UpdateOBB(Transform& transform);
};

struct AABB
{

	//���S���W
	EngineMathF::Vector3 center;

	//�T�C�Y
	EngineMathF::Vector3 size;

};

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2);

struct SPHERE
{
	//���S���W
	EngineMathF::Vector3 center;

	//���a
	float radius;
};

bool CheckAABB2SPHERE(AABB& aabb1, SPHERE& sphere);