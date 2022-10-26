#include "Goal.h"

void Goal::Initialize()
{
	worldTransform_ = std::make_unique<Transform>();
	worldTransform_->Initialize();

	worldTransform_->translation = { 18.0f,-3.0f,-30.0f };
	worldTransform_->scale = { 4.0f,4.0f,4.0f };
	worldTransform_->rotation = { 0.0f,150.0f * EngineMathF::Deg2Rad, 0.0f };

	model_ = std::make_unique<objModel>();
	model_->Initialize();
	model_->Create("Resources/goal");
}

void Goal::Draw(Camera* camera)
{
	worldTransform_->TransUpdate(camera);
	model_->Draw(worldTransform_.get());
}