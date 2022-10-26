#include "Object.h"

void Object::Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, float radius, objModel* model)
{
	worldTransform_ = std::make_unique<Transform>();

	worldTransform_->translation = pos;
	worldTransform_->scale = { 1.0f,1.0f,1.0f };
	worldTransform_->rotation = rot;

	worldTransform_->Initialize();

	model_ = model;

	collider_.center = worldTransform_->translation;
	collider_.radius = radius;
}

void Object::Update()
{

}

void Object::Draw(Camera* camera)
{
	worldTransform_->TransUpdate(camera);
	model_->Draw(worldTransform_.get());
}

SPHERE& Object::GetCollider()
{
	return collider_;
}

bool Object::GetIsDeath()
{
	return IsDeath;
}

void Object::OnCollision()
{
	IsDeath = true;
}