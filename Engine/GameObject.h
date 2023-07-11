#pragma once

#include <list>
#include <string>
#include "Fbx.h"
#include "Direct3D.h"

using std::string;
using std::list;
class GameObject
{
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject* 		pParent_;
	string				objectName_;
	bool IsDead_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void KillMe();

	template <class T>
	void Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
	}
};
