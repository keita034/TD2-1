#pragma once
#include"Sprite2D.h"
#include "TextureManager.h"

class TitleScene
{
public:
	TitleScene() = default;
	~TitleScene() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void SpriteDraw();
private:
	std::unique_ptr<Sprite2D> sprite_;
	Transform transform_;
	TextureData textureHandle_;

	TextureData spaceTextureHandle_;
	std::unique_ptr<Sprite2D> spriteSpace_;
	Transform spaceTransform_;

	//コピーコンストラクタ・代入演算子削除
	TitleScene& operator=(const TitleScene&) = delete;
	TitleScene(const TitleScene&) = delete;
};

