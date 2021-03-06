#include "stdafx.h"
#include "Scene.h"
#include <typeinfo>
#include <iostream>
#include <algorithm>

std::weak_ptr<GameObject> Scene::createGameObject()
{
	auto go = GameObjectPtr(new GameObject());
	mGameObjects.push_back(go);
	go->addComponent<Transform>();
	return std::weak_ptr<GameObject>(go);
}

void Scene::destoryGameObject(const std::weak_ptr<GameObject>& go)
{
	if (auto ptr = go.lock()) {
		auto result = std::find(mGameObjects.begin(), mGameObjects.end(), ptr);
		if (result != mGameObjects.end()) {
			ptr->onDestory();
			mGameObjects.erase(result);
		}
	}
}

std::vector<std::weak_ptr<GameObject>> Scene::getAllGameObjects()
{
	std::vector<std::weak_ptr<GameObject>> temp;
	for (auto go:mGameObjects)
	{
		temp.push_back(go);
	}
	return temp;
}

void Scene::enter()
{
	for (auto go:mGameObjects)
	{
		go->onAwake();
	}
}

void Scene::leave()
{

}
