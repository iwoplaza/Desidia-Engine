#include "duk_GameObject.hpp"
#include "duk_Transform.hpp"
#include "duk_Component.hpp"
#include "../../util/Vector3.hpp"
#include "../../scene/Scene.hpp"
#include "../../gameobject/GameObject.hpp"
#include <iostream>
#include <string>

using namespace std;

void duk_GameObject::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_GameObject::getParent, 1);
	duk_put_prop_string(ctx, -2, "getParent");
	duk_push_c_function(ctx, duk_GameObject::getTransform, 1);
	duk_put_prop_string(ctx, -2, "getTransform");
	duk_push_c_function(ctx, duk_GameObject::getComponents, 2);
	duk_put_prop_string(ctx, -2, "getComponents");
	duk_push_c_function(ctx, duk_GameObject::getComponent, 2);
	duk_put_prop_string(ctx, -2, "getComponent");
	duk_push_c_function(ctx, duk_GameObject::setParent, 2);
	duk_put_prop_string(ctx, -2, "setParent");
	duk_put_global_string(ctx, "GameObject");
}

duk_ret_t duk_GameObject::getParent(duk_context *ctx) {
	GameObject* gameObject = Scene::current->getGameObject(duk_safe_to_string(ctx, 0));
	Transform* parent = gameObject->getTransform()->getParent();
	if (parent == nullptr)
		return 0;

	duk_Transform::pushTransform(ctx, parent->getGameObject()->getName().c_str());
	return 1;
}

duk_ret_t duk_GameObject::getTransform(duk_context *ctx) {
	if (duk_Transform::pushTransform(ctx, duk_safe_to_string(ctx, 0)))
		return 1;
	else
		return 0;
}

duk_ret_t duk_GameObject::getComponents(duk_context *ctx) {
	duk_Component::pushComponents(ctx, duk_safe_to_string(ctx, 0), duk_safe_to_string(ctx, 1));
	return 1;
}

duk_ret_t duk_GameObject::getComponent(duk_context *ctx) {
	duk_Component::pushComponent(ctx, duk_safe_to_string(ctx, 0), duk_safe_to_string(ctx, 1), 0);
	return 1;
}

duk_ret_t duk_GameObject::setParent(duk_context *ctx) {
	const char* gameObjectName = duk_safe_to_string(ctx, 1);
	const char* parentName = duk_safe_to_string(ctx, 1);
	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	GameObject* parent = Scene::current->getGameObject(parentName);
	gameObject->getTransform()->setParent(parent->getTransform());

	return 0;
}