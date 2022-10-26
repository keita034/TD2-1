#include "SpeedUpChance.h"

void SpeedUpChance::Initialize(RailCamera* railCamera)
{
	firstModel_ = std::make_unique<objModel>();
	firstModel_->Initialize();
	firstModel_->Create("Resources/branchPoint2");

	secondModel_ = std::make_unique<objModel>();
	secondModel_->Initialize();
	secondModel_->Create("Resources/branchPoint");

	std::unique_ptr<BranchPoint> branchPoint;
	//1‰ñ–Ú
	branchPoint = std::make_unique<BranchPoint>();
	branchPoint->Initialize({ 750.0f,-10.0f,520.3f }, { 0.0f,180 * EngineMathF::Deg2Rad,0.0f }, { 1.0f,1.5f,0.01f },
		firstModel_.get(),
		std::bind(&RailCamera::SpeedDown, railCamera), std::bind(&RailCamera::SpeedUp, railCamera));
	branchPoints.push_back(std::move(branchPoint));

	//2‰ñ–Ú
	branchPoint = std::make_unique<BranchPoint>();
	branchPoint->Initialize({ 750.0f,-10.0f,260.3f }, { 0.0f,180 * EngineMathF::Deg2Rad,0.0f }, { 1.0f,1.5f,0.01f },
		secondModel_.get(),
		std::bind(&RailCamera::SpeedUp, railCamera), std::bind(&RailCamera::SpeedDown, railCamera));
	branchPoints.push_back(std::move(branchPoint));
}

void SpeedUpChance::Update(Player* player)
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->Update(player);
	}
}

void SpeedUpChance::Draw(Camera* camera)
{
	for (std::unique_ptr<BranchPoint>& branchPoint : branchPoints)
	{
		branchPoint->Draw(camera);
	}
}
