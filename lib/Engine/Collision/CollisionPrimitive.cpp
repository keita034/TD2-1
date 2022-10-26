#include"CollisionPrimitive.h"

void Triangle::ComputeNormal()
{
	EngineMathF::Vector4 p0_p1 = p1 - p0;
	EngineMathF::Vector4 p0_p2 = p2 - p0;

	//外積により、2辺に垂直なベクトルを算出する
	normal = p0_p1.cross(p0_p2);
	normal.normal();

}

const EngineMathF::Vector4& Triangle::GetP0()
{
	return p0;
}

void Triangle::SetP0(EngineMathF::Vector4& p0_)
{
	p0 = p0_;
}

const EngineMathF::Vector4& Triangle::GetP1()
{
	return p1;
}

void Triangle::SetP1(EngineMathF::Vector4& p1_)
{
	p1 = p1_;
}

const EngineMathF::Vector4& Triangle::GetP2()
{
	return p2;
}

void Triangle::SetP2(EngineMathF::Vector4& p2_)
{
	p2 = p2_;
}

const EngineMathF::Vector4& Triangle::GetNormal()
{
	return normal;
}

void Triangle::SetNormal(EngineMathF::Vector4& normal_)
{
	normal = normal_;
}

const EngineMathF::Vector3 OBB::GetDirect(uint16_t elem)
{
	return normaDirect[elem];
}

const float OBB::GetLen(uint16_t elem)
{
	return Length[elem];
}

const EngineMathF::Vector3 OBB::GetCenter()
{
	return center;
}

bool CheckAABB2AABB(AABB& aabb1, AABB& aabb2)
{
	std::array<EngineMathF::Vector3, 2> min_;
	min_[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	min_[1] = { aabb2.center.x - aabb2.size.x, aabb2.center.y - aabb2.size.y ,aabb2.center.z - aabb2.size.z };
	std::array<EngineMathF::Vector3, 2> max_;
	max_[0] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	max_[1] = { aabb2.center.x + aabb2.size.x, aabb2.center.y + aabb2.size.y ,aabb2.center.z + aabb2.size.z };

	if (min_[0].x > max_[1].x || max_[0].x < min_[1].x ||
		min_[0].y > max_[1].y || max_[0].y < min_[1].y ||
		min_[0].z > max_[1].z || max_[0].z < min_[1].z)
	{
		return false;
	}

	return true;
}

bool CheckAABB2SPHERE(AABB& aabb1, SPHERE& sphere)
{
	std::array<EngineMathF::Vector3, 8> vex;

	vex[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[1] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	vex[2] = { aabb1.center.x + aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[3] = { aabb1.center.x + aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z + aabb1.size.z };

	vex[4] = { aabb1.center.x - aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[5] = { aabb1.center.x - aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	vex[6] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	vex[7] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };

	for (EngineMathF::Vector3 v : vex)
	{
		float ren = (fabs(v.x - sphere.center.x)) * 2 + (fabs(v.y - sphere.center.y)) * 2 + (fabs(v.z - sphere.center.z)) * 2;

		if (fabs(ren) < sphere.radius * 2)
		{
			return true;
		}

	}

	return false;
}

void OBB::CreateOBB(std::vector<PosNormalUv> vertex_, Transform& transform)
{
	EngineMathF::Matrix4	matRot;

	//最大値、最小値の初期値設定
	EngineMathF::Vector3 max = EngineMathF::Vector3(-10000.0f, -10000.0f, -10000.0f);
	EngineMathF::Vector3 min = EngineMathF::Vector3(10000.0f, 10000.0f, 10000.0f);

	//メッシュの頂点データ取得
	std::vector<PosNormalUv> vertex = vertex_;
	//最大値、最小値取得ループ
	for (size_t i = 0; i < vertex.size(); i++)
	{
		EngineMathF::Vector3 pos = vertex[i].pos;
		if (pos.x < min.x)min.x = pos.x;
		if (pos.x > max.x)max.x = pos.x;
		if (pos.y < min.y)min.y = pos.y;
		if (pos.y > max.y)max.y = pos.y;
		if (pos.z < min.z)min.z = pos.z;
		if (pos.z > max.z)max.z = pos.z;
	}

	//中心点取得
	center = transform.translation;

	//方向ベクトル取得
	matRot.MakeRotation(transform.rotation);
	normaDirect[0] = { matRot.m[0][0], matRot.m[0][1], matRot.m[0][2] };
	normaDirect[1] = { matRot.m[1][0], matRot.m[1][1], matRot.m[1][2] };
	normaDirect[2] = { matRot.m[2][0], matRot.m[2][1], matRot.m[2][2] };

	//長さ取得
	Length[0] = EngineMathF::Abs(max.x - min.x) * 0.5f;
	Length[1] = EngineMathF::Abs(max.y - min.y) * 0.5f;
	Length[2] = EngineMathF::Abs(max.z - min.z) * 0.5f;

	Length[0] *= transform.scale.x;
	Length[1] *= transform.scale.y;
	Length[2] *= transform.scale.z;
}

void OBB::UpdateOBB(Transform& transform)
{
	EngineMathF::Matrix4	matRot;

	//中心点取得
	center = EngineMathF::GetWorldPosition(transform);

	//方向ベクトル取得
	matRot.MakeRotation(transform.rotation);
	normaDirect[0] = { matRot.m[0][0], matRot.m[0][1], matRot.m[0][2] };
	normaDirect[1] = { matRot.m[1][0], matRot.m[1][1], matRot.m[1][2] };
	normaDirect[2] = { matRot.m[2][0], matRot.m[2][1], matRot.m[2][2] };
}

const uint32_t BaseCollsion::GetCollisionAttribute()
{
	return collisionAttribute;
}

void BaseCollsion::SetCollisionAttribute(uint32_t collisionAttribute_)
{
	collisionAttribute = collisionAttribute_;
}

const uint32_t BaseCollsion::GetCollisionMask()
{
	return CollisionMask;
}

void BaseCollsion::SetCollisionMask(uint32_t CollisionMask_)
{
	CollisionMask = CollisionMask_;
}

void BaseCollsion::SetCollsionName(std::string name)
{
	collsionName = name;
}

std::string BaseCollsion::GetCollsionName()
{
	return collsionName;
}

std::string BaseCollsion::GetOpponentCollsionName()
{
	return opponentCollsionName;
}

void BaseCollsion::SetOpponentCollsionName(std::string name)
{
	for (size_t i = 0; i < name.size(); i++)
	{
		opponentCollsionName[i] = name[i];
	}
}

const float Sphere::GetRadius()
{
	return radius;
}

void Sphere::SetRadius(float radius_)
{
	radius = radius_;
}

const EngineMathF::Vector4& Sphere::GetCenter()
{
	return center;
}

void Sphere::SetCenter(EngineMathF::Vector4& center_)
{
	center = center_;
}

const float Plane::GetDistance()
{
	return distance;
}

void Plane::SetDistance(float distance_)
{
	distance = distance_;
}

const EngineMathF::Vector4& Plane::GetNormal()
{
	return normal;
}

void Plane::SetNormal(EngineMathF::Vector4& normal_)
{
	normal = normal_;
}

const EngineMathF::Vector4& Ray::GetStart()
{
	return start;
}

void Ray::SetStart(EngineMathF::Vector4& start_)
{
	start = start_;
}

const EngineMathF::Vector4& Ray::GetDir()
{
	return dir;
}

void Ray::SetDir(EngineMathF::Vector4& dir_)
{
	dir = dir_;
}

const float RayCast::GetRange()
{
	return range;
}

void RayCast::SetRange(float range_)
{
	range = range_;
}
