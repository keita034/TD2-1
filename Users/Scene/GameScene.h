#pragma once

#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "Camera.h"
#include "Transform.h"
#include "Particle.h"
#include "TextureManager.h"
#include"AudioManager.h"

#include"Users/stage.h"
#include"Users/RailCamera.h"
#include"Users/ResultCamera.h"
#include"Users/ObjectManager.h"
#include"Users/player.h"
#include"Users/sky.h"
#include"Users/door.h"
#include"Users/TitleScene.h"
#include"Users/ResultScene.h"
#include"Users/SpeedUpChance.h"
#include"Users/DoorManager.h"
#include"Users/Goal.h"
#include"Users/Particle.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	static GameScene* GetInstance();

private: // メンバ変数
	Camera* viewProjection = nullptr;

	Input* input_ = nullptr;
	TextureData textureHandle_;
	Transform transform_;

	TextureData numTexHandle_;
	std::array<Transform, 3> numTransform;
	std::unique_ptr<Sprite2D> numSprite[3];

	Transform startCountDownTransform;
	std::unique_ptr<Sprite2D> startCountDownSprite;

	std::unique_ptr<Sprite2D> goSprite;
	TextureData goTexHandle_;

	std::unique_ptr<Light> light;
	EngineMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<Sprite2D> sprite_;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<ResultCamera> resultCamera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<stage> stage_;
	std::unique_ptr<sky> modelSkydome_;
	std::unique_ptr<SceneParticle> particle_;
	std::unique_ptr<ObjectManager> objectManager_;
	std::unique_ptr<TitleScene> titleScene_;
	std::unique_ptr<ResultScene> resultScene_;
	std::unique_ptr<SpeedUpChance>speedUpChance_;
	std::unique_ptr<DoorManager> doorManager_;
	std::unique_ptr<Goal> goalModel_;

	enum class Scene
	{
		title,
		game,
		door,
		result
	};

	Scene scene = Scene::title;

	int startTime = 0;

	int nowTime = 0;

	int endTime = 0;

	int frequencyInvocationDoor = 0;

	//発動中？
	bool isActivationDoor = false;

	bool titleParticleFrg = false;
	bool ParticleFrg = false;
	bool resultParticleFrg = false;

	bool startGameFrg = false;

	bool endGameFrg = false;

	//サウンド
	uint32_t titleHandle = 0;
	uint32_t gameHandle = 0;
	uint32_t clearHandle = 0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
