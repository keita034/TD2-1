#pragma once

#include"Camera.h"
#include"Transform.h"

class ResultCamera
{
public:

	ResultCamera();
	~ResultCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Transform* worldTransform);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Camera* GetViewProjection();

	Transform* GetWorldTransformPtr();

	void addRot(EngineMathF::Vector3 rot);
	void addTranslation(EngineMathF::Vector3 translation);

	void setTranslation(EngineMathF::Vector3 translation);

private:

	std::unique_ptr<Camera> viewProjection_;

	Transform worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	ResultCamera& operator=(const ResultCamera&) = delete;
	ResultCamera(const ResultCamera&) = delete;
};
