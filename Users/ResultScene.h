#pragma once
#include"Sprite2D.h"

class ResultScene
{
private:

	std::unique_ptr<Sprite2D> spriteSpace_[3];
	TextureData spaceTextureData_[3];
	Transform spaceTransform[3];

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

