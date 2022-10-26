#include "Collision.h"

void Collision::ClosestPtPoint2Triangle(EngineMathF::Vector4& point, Triangle& triangle, EngineMathF::Vector4* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	EngineMathF::Vector4 p0_p1 = triangle.GetP1() - triangle.GetP1();
	EngineMathF::Vector4 p0_p2 = triangle.GetP2() - triangle.GetP0();
	EngineMathF::Vector4 p0_pt = point - triangle.GetP0();

	float d1 = p0_pt.dot(p0_p1);
	float d2 = p0_pt.dot(p0_p2);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.GetP0();
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	EngineMathF::Vector4 p1_pt = point - triangle.GetP1();

	float d3 = p1_pt.dot(p0_p1);
	float d4 = p1_pt.dot(p0_p2);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.GetP1();
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.GetP0() + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	EngineMathF::Vector4 p2_pt = point - triangle.GetP2();

	float d5 = p2_pt.dot(p0_p1);
	float d6 = p2_pt.dot(p0_p2);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.GetP2();
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.GetP0() + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.GetP1() + w * (triangle.GetP2() - triangle.GetP1());
		return;
	}

	// point�͖ʗ̈�̒��ɂ���Bclosest���d�S���W��p���Čv�Z����
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.GetP0() + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Sphere(Sphere& sphereA, Sphere& sphereB, EngineMathF::Vector4* inter, EngineMathF::Vector4* reject)
{
	// ���S�_�̋����̂Q�� <= ���a�̘a�̂Q��@�Ȃ����
	EngineMathF::Vector4 tmp;
	tmp = sphereA.GetCenter() - sphereB.GetCenter();
	float dist = tmp.lengthSquared();
	float radius2 = sphereA.GetRadius() + sphereB.GetRadius();
	radius2 *= radius2;

	if (dist <= radius2)
	{
		if (inter)
		{
			// A�̔��a��0�̎����W��B�̒��S�@B�̔��a��0�̎����W��A�̒��S�@�ƂȂ�悤�⊮
			float t = sphereB.GetRadius() / (sphereA.GetRadius() + sphereB.GetRadius());
			*inter = EngineMathF::Vector4Lerp(sphereA.GetCenter(), sphereB.GetCenter(), t);
		}
		// �����o���x�N�g�����v�Z
		if (reject)
		{
			float rejectLen = sphereA.GetRadius() + sphereB.GetRadius() - std::sqrtf(dist);
			tmp = sphereA.GetCenter() - sphereB.GetCenter();
			*reject = tmp.normal();
			*reject *= rejectLen;
		}
		return true;
	}

	return false;
}

bool Collision::CheckSphere2Plane(Sphere& sphere, Plane& plane, EngineMathF::Vector4* inter)
{
	// ���W�n�̌��_���狅�̒��S���W�ւ̋�������
	// ���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = sphere.GetCenter().dot(plane.GetNormal()) - plane.GetDistance();
	// �����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabsf(dist) > sphere.GetRadius())	return false;

	// �[����_���v�Z
	if (inter)
	{
		// ���ʏ�̍Đڋߓ_���A�^����_�Ƃ���
		*inter = -dist * plane.GetNormal() + sphere.GetCenter() + sphere.GetCenter();
	}

	return true;
}

bool Collision::CheckSphere2Triangle(Sphere& sphere, Triangle& triangle, EngineMathF::Vector4* inter, EngineMathF::Vector4* reject)
{
	EngineMathF::Vector4 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	EngineMathF::Vector4 tmp = sphere.GetCenter();
	ClosestPtPoint2Triangle(tmp, triangle, &p);
	// �_p�Ƌ��̒��S�̍����x�N�g��
	EngineMathF::Vector4 v = p - sphere.GetCenter();
	// �����̓������߂�
	//�i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����j
	float distanceSquare = v.dot(v);
	// ���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (distanceSquare > sphere.GetRadius() * sphere.GetRadius())
	{
		return false;
	}

	// �[����_���v�Z
	if (inter)
	{
		// �O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	// �����o���x�N�g�����v�Z
	if (reject)
	{
		float ds = sphere.GetCenter().dot(triangle.GetNormal());
		float dt = triangle.GetP0().dot(triangle.GetNormal());
		float rejectLen = dt - ds + sphere.GetRadius();
		*reject = triangle.GetNormal() * rejectLen;
	}
	return true;
}

bool Collision::CheckRay2Plane(Ray& lay, Plane& plane, float* distance, EngineMathF::Vector4* inter)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

	float d1 = plane.GetNormal().dot(lay.GetDir());
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon)
	{
		return false;
	}

	float d2 = plane.GetNormal().dot(lay.GetStart());
	float t = (plane.GetDistance() - d2) / d1;

	if (t < 0) return false;

	// ��������������
	if (distance)
	{
		*distance = t;
	}

	// ��_���v�Z
	if (inter)
	{
		*inter = lay.GetStart() + t * lay.GetDir();
	}

	return true;
}

bool Collision::CheckRay2Triangle(Ray& lay, Triangle& triangle, float* distance, EngineMathF::Vector4* inter)
{
	// �O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	EngineMathF::Vector4 interPlane;
	EngineMathF::Vector4 tmp = triangle.GetNormal();
	plane.SetNormal(tmp);
	plane.SetDistance(triangle.GetNormal().dot(triangle.GetP0()));
	// ���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�	
	if (!CheckRay2Plane(lay, plane, distance, &interPlane))
	{
		return false;
	}
	// ���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ

	// ���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	EngineMathF::Vector4 m;
	// ��p0_p1�ɂ���
	EngineMathF::Vector4 pt_p0 = triangle.GetP0() - interPlane;
	EngineMathF::Vector4 p0_p1 = triangle.GetP1() - triangle.GetP0();
	m = pt_p0.cross(p0_p1);
	// �ӂ̊O��
	if (m.dot(triangle.GetNormal()) < -epsilon)
	{
		return false;
	}

	// ��p1_p2�ɂ���
	EngineMathF::Vector4 pt_p1 = triangle.GetP1() - interPlane;
	EngineMathF::Vector4 p1_p2 = triangle.GetP2() - triangle.GetP1();
	m = pt_p1.cross(p1_p2);
	// �ӂ̊O��
	if (m.dot(triangle.GetNormal()) < -epsilon)
	{
		return false;
	}

	// ��p2_p0�ɂ���
	EngineMathF::Vector4 pt_p2 = triangle.GetP2() - interPlane;
	EngineMathF::Vector4 p2_p0 = triangle.GetP0() - triangle.GetP2();
	m = pt_p2.cross(p2_p0);
	// �ӂ̊O��
	if (m.dot(triangle.GetNormal()) < -epsilon)
	{
		return false;
	}

	if (inter)
	{
		*inter = interPlane;
	}

	// �����Ȃ̂ŁA�������Ă���
	return true;
}

bool Collision::CheckRay2Sphere(Ray& lay, Sphere& sphere, float* distance, EngineMathF::Vector4* inter)
{
	EngineMathF::Vector4 m = lay.GetStart() - sphere.GetCenter();
	float b = m.dot(lay.GetDir());
	float c = m.dot(m) - sphere.GetRadius() * sphere.GetRadius();
	// lay�̎n�_��sphere�̊O���ɂ���(c > 0)�Alay��sphere���痣��Ă���������
	// �����Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// ���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	// ���C�͋��ƌ������Ă���B
	// ��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	// t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = lay.GetStart() + t * lay.GetDir();
	}

	return true;
}

bool Collision::CheckRayCast2Sphere(RayCast& lay, Sphere& sphere, float* distance, EngineMathF::Vector4* inter)
{
	float dis = 0.0f;

	if (!CheckRay2Sphere(lay, sphere, &dis, inter))
	{
		return false;
	}

	if (dis > lay.GetRange())
	{
		return false;
	}

	if (distance)
	{
		*distance = dis;
	}

	return true;
}

bool Collision::CheckOBB2OBB(OBB& obb1, OBB& obb2)
{
	//�e�����x�N�g���̊m��
	//(N***:�W���������x�N�g��)
	EngineMathF::Vector3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen(0);
	EngineMathF::Vector3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen(1);
	EngineMathF::Vector3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen(2);
	EngineMathF::Vector3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen(0);
	EngineMathF::Vector3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen(1);
	EngineMathF::Vector3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen(2);
	EngineMathF::Vector3 Interval = obb1.GetCenter() - obb2.GetCenter();

	//������:Ae1
	float rA = Ae1.length();
	float rB = EngineMathF::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = EngineMathF::Abs(Interval.dot(NAe1));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Ae2
	rA = Ae2.length();
	rB = EngineMathF::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(NAe2));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Ae3
	rA = Ae3.length();
	rB = EngineMathF::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(NAe3));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be1
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = EngineMathF::Abs(Interval.dot(NBe1));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be2
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = EngineMathF::Abs(Interval.dot(NBe2));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be3
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = EngineMathF::Abs(Interval.dot(NBe3));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C11
	EngineMathF::Vector3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C12
	Cross = NAe1.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C13
	Cross = NAe1.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C21
	Cross = NAe2.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C22
	Cross = NAe2.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C23
	Cross = NAe2.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C31
	Cross = NAe3.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C32
	Cross = NAe3.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C33
	Cross = NAe3.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//�������ʂ����݂��Ȃ��̂ŏՓ˂��Ă���
	return true;
}

bool Collision::CheckOBB2OBB(OBB* obb1, OBB* obb2)
{
	if (!obb1||!obb2)
	{
		return false;
	}

	//�e�����x�N�g���̊m��
	//(N***:�W���������x�N�g��)
	EngineMathF::Vector3 NAe1 = obb1->GetDirect(0), Ae1 = NAe1 * obb1->GetLen(0);
	EngineMathF::Vector3 NAe2 = obb1->GetDirect(1), Ae2 = NAe2 * obb1->GetLen(1);
	EngineMathF::Vector3 NAe3 = obb1->GetDirect(2), Ae3 = NAe3 * obb1->GetLen(2);
	EngineMathF::Vector3 NBe1 = obb2->GetDirect(0), Be1 = NBe1 * obb2->GetLen(0);
	EngineMathF::Vector3 NBe2 = obb2->GetDirect(1), Be2 = NBe2 * obb2->GetLen(1);
	EngineMathF::Vector3 NBe3 = obb2->GetDirect(2), Be3 = NBe3 * obb2->GetLen(2);
	EngineMathF::Vector3 Interval = obb1->GetCenter() - obb2->GetCenter();

	//������:Ae1
	float rA = Ae1.length();
	float rB = EngineMathF::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = EngineMathF::Abs(Interval.dot(NAe1));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Ae2
	rA = Ae2.length();
	rB = EngineMathF::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(NAe2));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Ae3
	rA = Ae3.length();
	rB = EngineMathF::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(NAe3));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be1
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Be1.length();
	L = EngineMathF::Abs(Interval.dot(NBe1));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be2
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Be2.length();
	L = EngineMathF::Abs(Interval.dot(NBe2));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:Be3
	rA = EngineMathF::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Be3.length();
	L = EngineMathF::Abs(Interval.dot(NBe3));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C11
	EngineMathF::Vector3 Cross;
	Cross = NAe1.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C12
	Cross = NAe1.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C13
	Cross = NAe1.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C21
	Cross = NAe2.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C22
	Cross = NAe2.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C23
	Cross = NAe2.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C31
	Cross = NAe3.cross(NBe1);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C32
	Cross = NAe3.cross(NBe2);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//������:C33
	Cross = NAe3.cross(NBe3);
	rA = EngineMathF::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = EngineMathF::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = EngineMathF::Abs(Interval.dot(Cross));
	if (L > rA + rB)
	{
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	//�������ʂ����݂��Ȃ��̂ŏՓ˂��Ă���
	return true;
}
