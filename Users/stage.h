#pragma once
#include "Input.h"
#include "objModel.h"
#include "Camera.h"
#include "Transform.h"

class stage
{
public:
	stage() = default;
	~stage() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);


private:
	//ワールド変換データ
	Transform stageWorldTransform_;
	//モデル
	std::unique_ptr<objModel> stage_;
	char PADING[4]{};

	EngineMathF::Vector3 vector = {};

	//コピーコンストラクタ・代入演算子削除
	stage& operator=(const stage&) = delete;
	stage(const stage&) = delete;
};

