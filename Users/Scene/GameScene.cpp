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

	numTexHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/Number.png");
	for (int i = 0; i < 3; i++)
	{
		numSprite[i] = std::make_unique<Sprite2D>();
		numSprite[i]->Initialize();
	}

	numTransform[0].Initialize();
	numTransform[1].Initialize();
	numTransform[2].Initialize();

	numTransform[0].translation = { 570,55,0 };
	numTransform[1].translation = { 640,55,0 };
	numTransform[2].translation = { 710,55,0 };

	startCountDownSprite = std::make_unique<Sprite2D>();
	startCountDownSprite->Initialize();

	startCountDownTransform.Initialize();
	startCountDownTransform.translation = {640,360,0};

	goSprite = std::make_unique<Sprite2D>();
	goSprite->Initialize();
	goTexHandle_= TextureManager::GetInstance()->LoadTexture(L"Resources/Go.png");

	secondSprite = std::make_unique<Sprite2D>();
	secondSprite->Initialize();
	secondTexHandle_= TextureManager::GetInstance()->LoadTexture(L"Resources/seconds.png");
	secondTransform.Initialize();
	secondTransform.translation = {1018,430,0};

	titleHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/titleBGM.mp3");
	gameHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/gameBGM.mp3");
	clearHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/clearBGM1.mp3");
	engineHandle= AudioManager::GetInstance()->LoadAudio("Resources/musics/engine.mp3",0.5);
//	clearHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/clearBGM2.mp3");

	AudioManager::GetInstance()->PlayWave(titleHandle,true);
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
			AudioManager::GetInstance()->StopWave(titleHandle);
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
			AudioManager::GetInstance()->PlayWave(gameHandle, true);
			nowTime = 0;
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
					AudioManager::GetInstance()->StopWave(gameHandle);
					AudioManager::GetInstance()->StopWave(engineHandle);
					endTime = nowTime;
					ParticleFrg = true;
					particle_->state();
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
			if (4 <= time(NULL) - startTime)
			{
				startGameFrg = true;
				startTime = time(NULL);
				AudioManager::GetInstance()->PlayWave(engineHandle, true);
			}
		}
		if (endGameFrg)
		{
			if (particle_->GetNumTimer() >= 225)
			{
				viewProjection = resultCamera_->GetViewProjection();
				scene = Scene::result;
				AudioManager::GetInstance()->PlayWave(clearHandle, true);
				endGameFrg = false;
				startGameFrg = false;
				railCamera_->setSpeed(1.0f);
				player_->EndGameReset();

				numTransform[0].translation = { 830,400,0 };
				numTransform[1].translation = { 900,400,0 };
				numTransform[2].translation = { 970,400,0 };
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
			AudioManager::GetInstance()->StopWave(clearHandle);
			particle_->state();
		}
		if (particle_->GetNumTimer() >= 225 && resultParticleFrg == true)
		{
			scene = Scene::title;
			AudioManager::GetInstance()->PlayWave(titleHandle, true);
			resultParticleFrg = false;

			numTransform[0].translation = { 570,55,0 };
			numTransform[1].translation = { 640,55,0 };
			numTransform[2].translation = { 710,55,0 };
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

		{
			float Time[3] = {
			 GetHundredDigit(nowTime)
			,GetTenDigit(nowTime)
			,GetOneDigit(nowTime) };

			for (int i = 0; i < 3; i++)
			{
				numSprite[i]->AnimationDraw(numTexHandle_, numTransform[i], 32, 32, Time[i], 1);
			}
		}
		if (startGameFrg == false)
		{
			if (3 == time(NULL) - startTime)
			{
				float a = 1;
				startCountDownSprite->AnimationDraw(numTexHandle_,startCountDownTransform,32,32,a, 1);
			}
			if (2 == time(NULL) - startTime)
			{
				float a = 2;
				startCountDownSprite->AnimationDraw(numTexHandle_, startCountDownTransform, 32, 32, a, 1);
			}
			if (1 == time(NULL) - startTime)
			{
				float a = 3;
				startCountDownSprite->AnimationDraw(numTexHandle_, startCountDownTransform, 32, 32, a, 1);
			}
		}
		else
		{
			if (1 >= time(NULL) - startTime)
			{
				goSprite->Draw(goTexHandle_, startCountDownTransform);
			}
		}
		break;
	case GameScene::Scene::result:
		resultScene_->SpriteDraw();
		{
			float Time[3] = {
				 GetHundredDigit(endTime)
				,GetTenDigit(endTime)
				,GetOneDigit(endTime) };

			for (int i = 0; i < 3; i++)
			{
				numSprite[i]->AnimationDraw(numTexHandle_, numTransform[i], 32, 32, Time[i], 1);
			}
			secondSprite->Draw(secondTexHandle_,secondTransform);
		}
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