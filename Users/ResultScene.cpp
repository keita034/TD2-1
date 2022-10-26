#include "ResultScene.h"

void ResultScene::Initialize()
{
	spaceTextureData_[0] = TextureManager::GetInstance()->LoadTexture(L"Resources/PushSpace.png");
	spaceTransform[0].Initialize();
	spaceTransform[0].translation = { 640,640,0 };
	spriteSpace_[0] = std::make_unique<Sprite2D>();
	spriteSpace_[0]->Initialize();

	spaceTextureData_[1] = TextureManager::GetInstance()->LoadTexture(L"Resources/Result.png");
	spaceTransform[1].Initialize();
	spaceTransform[1].translation = { 900,200,0 };
	spriteSpace_[1] = std::make_unique<Sprite2D>();
	spriteSpace_[1]->Initialize();

	spaceTextureData_[2] = TextureManager::GetInstance()->LoadTexture(L"Resources/timerResult.png");
	spaceTransform[2].Initialize();
	spaceTransform[2].translation = { 900,400,0 };
	spriteSpace_[2] = std::make_unique<Sprite2D>();
	spriteSpace_[2]->Initialize();
}

void ResultScene::Update()
{
}

void ResultScene::SpriteDraw()
{
	spriteSpace_[0]->Draw(spaceTextureData_[0], spaceTransform[0]);
	spriteSpace_[1]->Draw(spaceTextureData_[1], spaceTransform[1]);
	spriteSpace_[2]->Draw(spaceTextureData_[2], spaceTransform[2]);
}
