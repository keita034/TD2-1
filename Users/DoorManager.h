#pragma once
#include "door.h"
#include"Sprite2D.h"

class DoorManager
{
public:

	DoorManager() = default;
	~DoorManager() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(EngineMathF::Vector3 vector);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int frequencyInvocationDoor);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	/// <summary>
/// スプライト用描画
/// </summary>
	void SpriteDraw();

	void  Reset();

	bool GetMashFlag(int frequencyInvocationDoor);

private:
	std::unique_ptr<door> door_[4]={};
	
	EngineMathF::Vector3 vector_;

	EngineMathF::Vector3 moveVector_;

	TextureData textureHandle_;
	Transform transform_;
	std::unique_ptr<Sprite2D> sprite_;

	//コピーコンストラクタ・代入演算子削除
	DoorManager& operator=(const DoorManager&) = delete;
	DoorManager(const DoorManager&) = delete;

};

