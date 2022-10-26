#pragma once
#include"ModelCreate.h"
#include"Transform.h"
#include"Camera.h"
#include"Input.h"
#include"EngineMathUtility.h"
#include"CollisionPrimitive.h"

class Player
{
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Transform* worldTransform);

	/// <summary>
	/// ゲーム中の毎フレーム処理
	/// </summary>
	void Update();
	/// <summary>
	/// ゲーム以外の毎フレーム処理
	/// </summary>
	void titleUpdate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	Transform& GetWorldTransform();

	AABB& GetCollider();

	void OnCollision();

	bool GetCrashFlag();

	void SetTransform(EngineMathF::Vector3 translation);

	void EndGameReset();

	void jumpReset();

private:

	void Move();

	void Rotate();

	void Complement(float& x1, float x2, float flame);

	void Jump();

	void Squat();

	uint8_t jumpFlag = 0u;
	char PADING[3]{};

	float gravitySpeed = 0.5;
	float defGravitySpeed = gravitySpeed;

	bool crashFlag = false;
	char PADING1[7]{};

	uint32_t crashTime = 70;
	AABB collider_;

	//回転運動を止める
	bool rollStopFlag = false;

	//しゃがみフラグ
	bool squatFlag = false;
	char PADING2[2]{};

	EngineMathF::Vector3 oldRot;
	uint32_t squatTime = 60 * 2;
	float oldRotY = 0.0f;
	char PADING3[8]{};

	//モデル
	std::unique_ptr<objModel> model_;
	//ワールド変換データ
	Transform worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	Player& operator=(const Player&) = delete;
	Player(const Player&) = delete;
};

