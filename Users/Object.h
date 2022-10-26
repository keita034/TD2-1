#pragma once
#include"objModel.h"
#include"Transform.h"
#include"Camera.h"
#include"CollisionPrimitive.h"

class Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, float radius, objModel* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	//コライダー所得
	SPHERE& GetCollider();

	//当たった時の関数
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	SPHERE collider_;
	objModel* model_;
	std::unique_ptr<Transform> worldTransform_;
};