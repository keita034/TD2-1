#include"GameScene.h"
#include "TextureManager.h"
#include <cassert>

int GetHundredDigit(int nowTime)
{
	if (nowTime > 1000)
	{
		int a = nowTime % 1000;
		return a / 100;
	}
	return nowTime / 100;
}
int GetTenDigit(int nowTime)
{
	if (nowTime > 100)
	{
		int a = nowTime % 100;
		return a / 10;
	}
	return nowTime / 10;
}

int GetOneDigit(int nowTime)
{
	if (nowTime > 10)
	{
		int a = nowTime % 10;
		return a;
	}
	return nowTime;
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	sprite_ = std::make_unique<Sprite2D>();
	textureHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/gamescene.png");
	transform_.Initialize();
	transform_.translation = { 640,360,0 };
	sprite_->Initialize();

	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();
	resultCamera_ = std::make_unique<ResultCamera>();
	stage_ = std::make_unique<stage>();
	modelSkydome_ = std::make_unique<sky>();
	particle_ = std::make_unique<SceneParticle>();
	objectManager_ = std::make_unique<ObjectManager>();
	titleScene_ = std::make_unique<TitleScene>();
	resultScene_ = std::make_unique<ResultScene>();
	speedUpChance_ = std::make_unique<SpeedUpChance>();
	doorManager_ = std::make_unique<DoorManager>();
	goalModel_ = std::make_unique<Goal>();

	input_ = Input::GetInstance();
	player_->Initialize(railCamera_->GetWorldTransformPtr());
	railCamera_->Initialize(EngineMathF::Vector3{ 0.0,0.0f,-10.0f }, { 0,0,0 });
	resultCamera_->Initialize(railCamera_->GetWorldTransformPtr());
	stage_->Initialize();
	modelSkydome_->Initialize();
	particle_->Initialize();
	objectManager_->Initialize(player_.get());
	doorManager_->Initialize(railCamera_->GetVector());
	titleScene_->Initialize();
	resultScene_->Initialize();
	speedUpChance_->Initialize(railCamera_.get());
	goalModel_->Initialize();

	viewProjection = resultCamera_->GetViewProjection();
}

void GameScene::Update()
{
	switch (scene)
	{
	case Scene::title:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		resultCamera_->Update();
		player_->titleUpdate();
		if (input_->TriggerPush(DIK_SPACE))
		{
			titleParticleFrg = true;
			particle_->state();
		}
		if (particle_->GetNumTimer() >= 225 && titleParticleFrg == true)
		{
			titleParticleFrg = false;
			scene = Scene::game;
			viewProjection = railCamera_->GetViewProjection();
			railCamera_->reset();
			player_->Update();
			objectManager_->Reset();
			startTime = time(NULL);
		}
		break;
	case Scene::game:
		if (startGameFrg && endGameFrg == false)
		{
			if (isActivationDoor == false)
			{
				if (railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor))
				{
					player_->SetTransform({ 0.0f, -2.0f, 10.0f });
					isActivationDoor = true;
					frequencyInvocationDoor++;
					player_->jumpReset();
				}
				player_->Update();
				objectManager_->Update();
				speedUpChance_->Update(player_.get());
				if (railCamera_->GetLap() >= 1)
				{
					endGameFrg = true;
					endTime = nowTime;
				}
				if (railCamera_->GetIsRapReset())
				{
					railCamera_->lapReset();
					doorManager_->Reset();
					frequencyInvocationDoor = 0;
				}
			}
			else
			{
				doorManager_->Update(frequencyInvocationDoor);
				if (doorManager_->GetMashFlag(frequencyInvocationDoor))
				{
					isActivationDoor = false;
				}
			}
			nowTime = time(NULL) - startTime;
		}
		else if (startGameFrg == false)
		{
			if (3 <= time(NULL) - startTime)
			{
				startGameFrg = true;
				startTime = time(NULL);
			}
		}
		if (endGameFrg)
		{
			if (3 <= time(NULL) - endTime)
			{
				ParticleFrg = true;
				particle_->state();
			}
			if (particle_->GetNumTimer() >= 225)
			{
				viewProjection = resultCamera_->GetViewProjection();

				scene = Scene::result;
				endGameFrg = false;
				startGameFrg = false;
				railCamera_->setSpeed(1.0f);
				player_->EndGameReset();
			}
		}
		break;
	case Scene::result:
		railCamera_->Update(player_->GetCrashFlag(), frequencyInvocationDoor);
		player_->titleUpdate();
		resultCamera_->Update();
		resultScene_->Update();
		if (input_->TriggerPush(DIK_SPACE))
		{
			resultParticleFrg = true;
			particle_->state();
		}
		if (particle_->GetNumTimer() >= 225 && resultParticleFrg == true)
		{
			scene = Scene::title;
			resultParticleFrg = false;
		}
		break;
	default:
		break;
	}
}

void GameScene::Draw()
{

	switch (scene)
	{
	case GameScene::Scene::title:
		break;
	case GameScene::Scene::game:
		objectManager_->Draw(viewProjection);
		goalModel_->Draw(viewProjection);
		doorManager_->Draw(viewProjection);
		speedUpChance_->Draw(viewProjection);
		break;
	case GameScene::Scene::result:
		break;
	default:
		break;
	}
	player_->Draw(viewProjection);
	stage_->Draw(viewProjection);
	modelSkydome_->Draw(viewProjection);


	switch (scene)
	{
	case GameScene::Scene::title:
		titleScene_->SpriteDraw();
		break;
	case GameScene::Scene::game:

		if (isActivationDoor)
		{
			doorManager_->SpriteDraw();
		}
		transform_.TransUpdate(viewProjection);
		sprite_->Draw(textureHandle_, transform_);
		break;
	case GameScene::Scene::result:
		resultScene_->SpriteDraw();
		break;
	default:
		break;
	}
	particle_->Draw();

}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}