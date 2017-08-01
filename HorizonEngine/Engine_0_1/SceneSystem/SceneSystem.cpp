#include "stdafx.h"
#include "SceneSystem.h"
#include "Component/Transform.h"
#include <memory>
SceneSystem::SceneSystem():
	mRunningScene(std::make_shared<Scene>())
{

}

void SceneSystem::startUp()
{
	auto go =  mRunningScene->createGameObject().lock();
	go->addComponent<Camera>();
}

void SceneSystem::shutDown()
{
	if (mRunningScene) {
		mRunningScene->leave();
	}
}

void SceneSystem::update(double dt)
{

}

void SceneSystem::render()
{
	assert(mRunningScene);
	auto objs = mRunningScene->getAllGameObjects();
	std::vector<std::shared_ptr<Camera>> cameras;
	for (auto weak_obj:objs)
	{
		auto obj = weak_obj.lock();
		if (!obj)continue;
		auto camera = obj->getComponent<Camera>().lock();
		if (camera) {
			cameras.push_back(camera);
		}
	}
}

void SceneSystem::enterScene(const ScenePtr & scene)
{
	if (scene && mRunningScene != scene) {
		if (mRunningScene) {
			mRunningScene->leave();
		}
		mRunningScene = scene;
		mRunningScene->enter();
	}
}

std::weak_ptr<Scene> SceneSystem::getRunningScene()
{
	return std::weak_ptr<Scene>(mRunningScene);
}