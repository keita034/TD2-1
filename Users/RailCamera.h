#pragma once
#include"Camera.h"
#include"Transform.h"

class RailCamera
{
public:

	RailCamera();
	~RailCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const EngineMathF::Vector3& position, const EngineMathF::Vector3& rotaion);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	bool Update(bool GetCrashFlag, int frequencyInvocationDoor);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// タイトルからゲームに移行するときにリセットする
	/// </summary>
	void reset();

	/// <summary>
	/// 一周するごとにリセットするモノをまとめる
	/// </summary>
	void lapReset();

	void SpeedUp();

	void SpeedDown();

	Camera* GetViewProjection();

	Transform* GetWorldTransformPtr();

	float GetWorldTransformRot();

	int GetLap();

	void addRot(EngineMathF::Vector3 rot);
	void addTranslation(EngineMathF::Vector3 translation);

	void setTranslation(EngineMathF::Vector3 translation);

	void setSpeed(float speed);

	bool GetIsRapReset();

	EngineMathF::Vector3 GetVector();
private:

	std::unique_ptr<Camera> viewProjection_;
	Transform worldTransform_;

	EngineMathF::Vector3 vector = { 0,0,0 };

	float rotRange[6] = {};

	float speed = 1.0f;

	enum class side {
		First = 1,//一番
		Second,//二番
		Third,//三番
		Fourth,//四番
		Fifth,//五番
		Sixth//六番
	};

	side currentSide = side::First;

	int lap = 0;

	bool IsLapReset = false;

	void Move();

	float invocationTrnsDoor[4] = {};

	//コピーコンストラクタ・代入演算子削除
	RailCamera& operator=(const RailCamera&) = delete;
	RailCamera(const RailCamera&) = delete;
};

