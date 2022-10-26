#pragma once
#include"EngineMathUtility.h"
#include"Model.h"
#include"RailCamera.h"
#include"Player.h"
#include"Camera.h"
class BranchPoint
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, const EngineMathF::Vector3& size, objModel* bodyModel, std::function<void(void)>left, std::function<void(void)>right);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(Camera* camera);

private:
	//–{‘Ì
	objModel* bodyModel_ = nullptr;
	Transform bodyWorldTransform_;

	AABB collider_;

	std::function<void()>left_;
	std::function<void()>right_;

	bool passingFlag_ = false;

	char PADING[7]{};
};

