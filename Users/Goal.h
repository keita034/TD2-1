#pragma once
#include "Transform.h"
#include "Camera.h"
#include "objModel.h"
#include "EngineMathUtility.h"
#include <memory>

class Goal
{
public:

	Goal() = default;
	~Goal() = default;

	// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

private:
	std::unique_ptr<objModel> model_;
	std::unique_ptr<Transform> worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	Goal& operator=(const Goal&) = delete;
	Goal(const Goal&) = delete;
};