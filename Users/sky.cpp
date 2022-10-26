#include "sky.h"

sky::sky()
{
}

sky::~sky()
{
}

void sky::Initialize()
{
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// スケールを設定
	worldTransform_.scale = { 10000.0f,10000.0f,10000.0f };

	model_ = std::make_unique<objModel>();
	model_->Initialize();
	model_->Create("Resources/skydome", true);

}

void sky::Draw(Camera* camera)
{
	worldTransform_.TransUpdate(camera);
	model_->Draw(&worldTransform_);
}
