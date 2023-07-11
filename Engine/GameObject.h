#pragma once

#include <list>
#include <string>
#include "Fbx.h"
#include "Direct3D.h"

using std::string;
using std::list;
class GameObject
{
private:
	bool IsDead_;

protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject* 		pParent_;
	string				objectName_;

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
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};
