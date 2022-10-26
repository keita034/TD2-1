#pragma once

#include"Vector3.h"
#include"Matrix4.h"
namespace EngineMathF
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		//�N�I�[�^�j�I�����쐬
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 9.0f, float w = 1.0f);
		Quaternion(const Vector3& v, float angle);
		Quaternion(const Matrix4& m);

		//���ς����߂�
		float dot(const Quaternion& q1, const Quaternion& q2);

		//�m���������߂�
		float length(const Quaternion& q);
		//���K������
		Quaternion normalize(const Quaternion& q);
		//�P�����Z�q�I�[�o�[���[�h
		Quaternion operator + ()const;
		Quaternion operator - ()const;
		//������Z�q�I�[�o�[���[�h
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (float s);
		Quaternion& operator /= (float s);
		Quaternion& operator *= (const Quaternion& q);

		Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
		Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);
		Matrix4 rotate(const Quaternion& q);

		Vector3 getAxis(const Quaternion& q);
	};

	//2�����Z�q�I�[�o�[���[�h
	const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q, float s);
	const Quaternion operator * (float s, const Quaternion& q);
	const Quaternion operator / (const Quaternion& q, float s);

}