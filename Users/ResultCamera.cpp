#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(Transform* worldTransform)
{
	worldTransform_.parent = worldTransform;

	//ワールドトランスフォームの初期設定
	worldTransform_.translation = {2.0f,-2.0f,11.5f};
	worldTransform_.rotation = { 0.0,250.0f * EngineMathF::Deg2Rad,0.0f };

	viewProjection_ = std::make_unique<Camera>();
	viewProjection_->SetFar(12000.0f);
	//ビュープロジェクションの初期化
	viewProjection_->Initialize(UpdateProjMatrixFunc_Perspective);
}

void ResultCamera::Update()
{

	worldTransform_.MakeWorldMatrix();

	viewProjection_->eye = EngineMathF::GetWorldPosition(worldTransform_);
	//ワールド前方ベクトル
	EngineMathF::Vector3 forward(0, 0, 1);
	//レールカメラの回転を反映
	forward = EngineMathF::Vec3Mat4Mul(forward, worldTransform_.matWorld);
	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_->target = viewProjection_->eye + forward;
	//ワールド上方ベクトル
	EngineMathF::Vector3 up(0, 1, 0);
	//レールカメラの回転を反映(レールカメラの上方ベクトル)
	viewProjection_->up = EngineMathF::Vec3Mat4Mul(up, worldTransform_.matWorld);
}

void ResultCamera::Draw() {}

Camera* ResultCamera::GetViewProjection()
{
	return viewProjection_.get();
}

Transform* ResultCamera::GetWorldTransformPtr()
{
	return &worldTransform_;
}
void ResultCamera::addTranslation(EngineMathF::Vector3 translation)
{
	worldTransform_.translation += translation;
}
void ResultCamera::addRot(EngineMathF::Vector3 rot)
{
	worldTransform_.rotation += rot;
}
void ResultCamera::setTranslation(EngineMathF::Vector3 translation)
{
	worldTransform_.translation = translation;
}