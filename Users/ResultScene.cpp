#include "ResultScene.h"

void ResultScene::Initialize()
{
	spaceTextureData_ = TextureManager::GetInstance()->LoadTexture(L"Resources/PushSpace.png");
	spaceTransform.Initialize();
	spaceTransform.translation = { 303,67,0 };
	spriteSpace_ = std::make_unique<Sprite2D>();
	spriteSpace_->Initialize();
}

void ResultScene::Update()
{
}

void ResultScene::SpriteDraw()
{
	spriteSpace_->Draw(spaceTextureData_, spaceTransform);
}
