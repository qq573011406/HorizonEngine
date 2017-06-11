#include "GameObject.h"
using namespace HorizonEngine;



std::vector<Component*>& HorizonEngine::GameObject::GetComponents()
{
	// TODO: �ڴ˴����� return ���
	return mComponents;
}

void HorizonEngine::GameObject::Start()
{
	mIsStatred = true;
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Start();
	}
}

void HorizonEngine::GameObject::Destory()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->OnDestory();
	}
}


GameObject::GameObject():
	mIsStatred(false)
{
	mComponents.push_back(&mTransform);
}


GameObject::~GameObject()
{
}
