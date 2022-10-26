#include "Door.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize(EngineMathF::Vector3 trans, EngineMathF::Vector3 Rot)
{
	door1worldTransform_.Initialize();
	door2worldTransform_.Initialize();
	door3worldTransform_.Initialize();

	door1model_ = std::make_unique<objModel>();
	door2model_ = std::make_unique<objModel>();
	door3model_ = std::make_unique<objModel>();

	door1model_->Initialize();
	door2model_->Initialize();
	door3model_->Initialize();

	door1model_->Create("Resources/door", true);
	door2model_->Create("Resources/door2", true);
	door3model_->Create("Resources/door3", true);

	input_ = Input::GetInstance();

	door1worldTransform_.translation = EngineMathF::Vector3(trans.x, trans.y, trans.z + 0.3f);
	door2worldTransform_.translation = trans;
	door3worldTransform_.translation = trans;

	door1worldTransform_.scale = { 10.0f,10.0f,1.0f };
	door2worldTransform_.scale = { 10.0f,10.0f,1.0f };
	door3worldTransform_.scale = { 10.0f,10.0f,1.0f };

	door1worldTransform_.rotation = Rot;
	door2worldTransform_.rotation = Rot;
	door3worldTransform_.rotation = Rot;
}

void door::Mash(EngineMathF::Vector3 vector)
{
	if (input_->TriggerPush(DIK_SPACE))
	{
		mashNum_++;
		door2worldTransform_.translation -= vector;
		door3worldTransform_.translation += vector;
	}
	if (mashNum_ > 10)
	{
		mashNum_ = 0;
		mashFlag_ = true;
	}
}

void door::Update(EngineMathF::Vector3 vector)
{
	Mash(vector);
}

void door::Draw(Camera* camera)
{
	door1worldTransform_.TransUpdate(camera);
	door2worldTransform_.TransUpdate(camera);
	door3worldTransform_.TransUpdate(camera);

	door1model_->Draw(&door1worldTransform_);
	door2model_->Draw(&door2worldTransform_);
	door3model_->Draw(&door3worldTransform_);
}

bool door::GetMashFlag()
{
	return mashFlag_;
}

UINT door::GetMashNum()
{
	return mashNum_;
}

void door::Reset(EngineMathF::Vector3 trans)
{
	mashFlag_ = false;
	door1worldTransform_.translation = EngineMathF::Vector3(trans.x, trans.y, trans.z + 0.3f);
	door2worldTransform_.translation = trans;
	door3worldTransform_.translation = trans;
}