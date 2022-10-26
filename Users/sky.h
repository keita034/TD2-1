#pragma once

#include "objModel.h"
#include "Transform.h"

class sky
{
public:
	sky();
	~sky();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

private:
	// ワールド変換データ
	Transform worldTransform_;
	// モデル
	std::unique_ptr<objModel> model_;

	//コピーコンストラクタ・代入演算子削除
	sky& operator=(const sky&) = delete;
	sky(const sky&) = delete;
};

