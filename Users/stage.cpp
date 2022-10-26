#include "stage.h"

void stage::Initialize()
{
	stage_ = std::make_unique<objModel>();
	stage_->Initialize();
	stage_->Create("Resources/stage", true);

	stageWorldTransform_.Initialize();
	stageWorldTransform_.translation = { 375.25f,-3.0f,375.25f };
	stageWorldTransform_.scale = { 12.0f,1.0f,12.0f };
}

void stage::Draw(Camera* camera)
{
	stageWorldTransform_.TransUpdate(camera);
	stage_->Draw(&stageWorldTransform_);

}
