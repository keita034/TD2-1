#pragma once
#include "Sprite2D.h"
#include "Input.h"
#include "TextureManager.h"
#include "Transform.h"

struct Hexagon
{
	Transform transform;
	float timer = 120;
	char PADING[4]{};
};

class SceneParticle
{
public:

	SceneParticle() = default;
	~SceneParticle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	///<summary>
	///パーティクルスタート
	///<summary>
	void state();

	/// <summary>
	/// アイキャッチ
	/// </summary>
	void EyeCatch();

	/// <summary>
	/// アイキャッチの初期化
	/// </summary>
	void EyeCatchInitialize();

	/// <summary>
	/// アイキャッチの描画
	/// </summary>
	void EyeCatchDraw();

	/// <summary>
	/// 値の初期化
	/// </summary>
	void Reset();

	float GetNumTimer();

	EngineMathF::Vector2 pos;
	EngineMathF::Vector2 pos2;
	EngineMathF::Vector2 bottom;

	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
	char PADING[5]{};

private:
	// テクスチャハンドル
	TextureData textureHandle_;
	TextureData textureBox_;
	// スプライト
	std::list<Hexagon> hexagon_;
	std::list<Hexagon> hexagon2_;
	Transform spriteBoxTransform;
	std::unique_ptr<Sprite2D> sprite_;
	std::unique_ptr<Sprite2D> spriteBox_;
	Input* input_ = nullptr;

	//コピーコンストラクタ・代入演算子削除
	SceneParticle& operator=(const SceneParticle&) = delete;
	SceneParticle(const SceneParticle&) = delete;
};

