#pragma once
#include"Sprite2D.h"

class ResultScene
{
private:

	std::unique_ptr<Sprite2D> spriteSpace_;
	TextureData spaceTextureData_;
	Transform spaceTransform;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void SpriteDraw();
};

