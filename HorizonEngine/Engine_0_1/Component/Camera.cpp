#include "stdafx.h"
#include "Camera.h"

Camera::Camera() :
	mDepth(0)
	, mFOV(45.0f)
	, mAspect(1.7f)
	, mNearClipPlane(0.001f)
	, mFarClipPanle(1000.0f)
	, mViewport(0,0,1,1)
	, mProjectionType(Projection::Perspective)
	, mClearColor(Color4f(0,0,0,1))
	, mClearFlag(ClearFlags::SolidColor)
{
	auto renderSystem = Application::getSingleton().getRenderSystem();
	auto win = renderSystem->getRenderWindow();
	auto width = win->getWidth();
	auto height = win->getHeight();
	mAspect = (float)width / (float)height;
}

const float Camera::getDepth() const
{
	return mDepth;
}

void Camera::setDepth(float depth)
{
	mDepth = depth;
}

const Vector4 Camera::getViewport() const
{
	return mViewport;
}

void Camera::setViewport(const Vector4 & rect)
{
	mViewport = rect;
}

void Camera::setFOV(float fov)
{
	mFOV = fov;
}

const float Camera::getFOV() const
{
	return mFOV;
}

void Camera::setAspect(float aspect)
{
	mAspect = aspect;
}

const float Camera::getAspect() const
{
	return mAspect;
}

void Camera::setNearClipPanle(float near)
{
	mNearClipPlane = near;
}

const float Camera::getNearClipPanle() const
{
	return mNearClipPlane;
}

void Camera::setFarClipPanle(float far)
{
	mFarClipPanle = far;
}

const float Camera::getFarClipPanle() const
{
	return mFarClipPanle;
}

void Camera::setProjection(Projection projection)
{
	mProjectionType = projection;
}

const Camera::Projection Camera::getProjection() const
{
	return mProjectionType;
}

void Camera::setClearColor(const Color4f& color)
{
	mClearColor = color;
}

const Color4f Camera::getClearColor() const
{
	return mClearColor;
}

const Matrix4x4 Camera::getViewMatrix() const
{
	auto go = getOnwer().lock();
	Matrix4x4 temp;
	if (go) {
		auto transform = go->getComponent<Transform>().lock();
		if (transform) {
			auto local2world = transform->getWorldMatrix() * transform->getLocalMatrix();
			auto world2camera = glm::inverse(local2world);
			temp = world2camera;
		}
	}
	return temp;
}

const Matrix4x4 Camera::getProjectionMatrix() const
{
	Matrix4x4 temp;
	if (mProjectionType == Projection::Perspective) {
		temp = glm::perspective(mFOV, mAspect, mNearClipPlane, mFarClipPanle);
	}
	else if (mProjectionType == Projection::Orthographic) {
		temp = glm::ortho(mOrthoRect.x, mOrthoRect.y, mOrthoRect.z, mOrthoRect.w,
			mNearClipPlane, mFarClipPanle);
	}
	return temp;
}

void Camera::setOrthoRect(Vector4 rect)
{
	mOrthoRect = rect;
}

const Vector4 Camera::getOrthoRect() const
{
	return mOrthoRect;
}

void Camera::setClearFlag(ClearFlags flag)
{
	mClearFlag = flag;
}

const Camera::ClearFlags Camera::getClearFlag() const
{
	return mClearFlag;
}
