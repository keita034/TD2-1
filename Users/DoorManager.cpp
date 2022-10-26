#include "DoorManager.h"

void DoorManager::Initialize(EngineMathF::Vector3 vector)
{
	vector_ = vector;

	door_[0] = std::make_unique<door>();
	door_[1] = std::make_unique<door>();
	door_[2] = std::make_unique<door>();
	door_[3] = std::make_unique<door>();

	door_[0]->Initialize(EngineMathF::Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z), EngineMathF::Vector3(0.0f, 30.0f * EngineMathF::Deg2Rad, 0.0f));
	door_[1]->Initialize(EngineMathF::Vector3(600 * vector_.x, 4.0f, 600 * -vector_.z), EngineMathF::Vector3(0.0f, 330.0f * EngineMathF::Deg2Rad, 0.0f));
	door_[2]->Initialize(EngineMathF::Vector3(450 * vector_.x, 4.0f, 450 * -vector_.z), EngineMathF::Vector3(0.0f, 330.0f * EngineMathF::Deg2Rad, 0.0f));
	door_[3]->Initialize(EngineMathF::Vector3(300 * vector_.x, 4.0f, 300 * -vector_.z), EngineMathF::Vector3(0.0f, 330.0f * EngineMathF::Deg2Rad, 0.0f));


	textureHandle_ = TextureManager::GetInstance()->LoadTexture(L"Resources/PushSpace.png");
	transform_.Initialize();
	transform_.translation = { 640,640,0 };
	sprite_= std::make_unique<Sprite2D>();
	sprite_->Initialize();

	//sprite_.reset(Sprite::Create(textureHandle_, { }));
}

void DoorManager::Update(int frequencyInvocationDoor)
{
	if (frequencyInvocationDoor == 1)
	{
		door_[frequencyInvocationDoor-1]->Update(EngineMathF::Vector3(vector_.z,0.0f,-vector_.x));
	}
	if (frequencyInvocationDoor == 2)
	{
		door_[frequencyInvocationDoor-1]->Update(EngineMathF::Vector3(vector_.z, 0.0f, vector_.x));
	}
	if (frequencyInvocationDoor == 3)
	{
		door_[frequencyInvocationDoor-1]->Update(EngineMathF::Vector3(vector_.z, 0.0f, vector_.x));
	}
	if (frequencyInvocationDoor == 4)
	{
		door_[frequencyInvocationDoor-1]->Update(EngineMathF::Vector3(vector_.z, 0.0f, vector_.x));
	}
}

void DoorManager::Draw(Camera* camera)
{
	transform_.TransUpdate(camera);
	for (int i = 0; i < 4; i++)
	{
		door_[i]->Draw(camera);
	}
}
void DoorManager::SpriteDraw()
{
	sprite_->Draw(textureHandle_,transform_);
}

void DoorManager::Reset()
{
	door_[0]->Reset(EngineMathF::Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z));
	door_[1]->Reset(EngineMathF::Vector3(600 * vector_.x, 4.0f, 600 * -vector_.z));
	door_[2]->Reset(EngineMathF::Vector3(450 * vector_.x, 4.0f, 450 * -vector_.z));
	door_[3]->Reset(EngineMathF::Vector3(300 * vector_.x, 4.0f, 300 * -vector_.z));
}

bool DoorManager::GetMashFlag(int frequencyInvocationDoor)
{
	return door_[frequencyInvocationDoor-1]->GetMashFlag();
}
