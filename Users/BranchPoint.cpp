#include "BranchPoint.h"

void BranchPoint::Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, const EngineMathF::Vector3& size, objModel* bodyModel, std::function<void(void)>left, std::function<void(void)>right)
{
	bodyModel_ = bodyModel;
	bodyWorldTransform_.translation = pos;
	bodyWorldTransform_.scale = { 12.0f,12.0f,12.0f };
	bodyWorldTransform_.rotation = rot;
	bodyWorldTransform_.Initialize();
	bodyWorldTransform_.MakeWorldMatrix();
	collider_.center = EngineMathF::GetWorldPosition(bodyWorldTransform_);
	collider_.size = {
		size.x* bodyWorldTransform_.scale.x,
		size.y* bodyWorldTransform_.scale.y,
		size.z* bodyWorldTransform_.scale.z };

	left_ = left;
	right_ = right;
}

void BranchPoint::Update(Player* player)
{
	if (!passingFlag_&&CheckAABB2AABB(player->GetCollider(), collider_))
	{
		passingFlag_ = true;

		if (player->GetWorldTransform().translation.x > 0)
		{
			left_();
		}
		else
		{
			right_();
		}
	}
}

void BranchPoint::Draw(Camera* camera)
{
	bodyWorldTransform_.TransUpdate(camera);
	bodyModel_->Draw(&bodyWorldTransform_);

}