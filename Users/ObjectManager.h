#pragma once
#include"Object.h"
#include"EngineMathUtility.h"
#include"player.h"


class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Player* player);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);
	
	void  Reset();
private:

	std::list<std::unique_ptr<Object>>objects_;
	std::unique_ptr<objModel> objectModel_;
	Player* player_ = nullptr;

	//コピーコンストラクタ・代入演算子削除
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&) = delete;
};

