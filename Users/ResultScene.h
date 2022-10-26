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
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void SpriteDraw();
};

