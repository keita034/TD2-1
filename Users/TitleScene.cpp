#include "TitleScene.h"

void TitleScene::Initialize()
{
	textureHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/Rin.png");
	transform_.Initialize();
	transform_.translation = { 619,675,0 };
	sprite_ = std::make_unique<Sprite2D>();
	sprite_->Initialize();

	spaceTextureHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/PushSpace.png");
	spaceTransform_.Initialize();
	spaceTransform_.translation = { 454,100,0 };
	spriteSpace_ = std::make_unique<Sprite2D>();
	spriteSpace_->Initialize();
}

void TitleScene::SpriteDraw()
{
	sprite_->Draw(textureHandle_, transform_);
	spriteSpace_->Draw(spaceTextureHandle_, spaceTransform_);
}
