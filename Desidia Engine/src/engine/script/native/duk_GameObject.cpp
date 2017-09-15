#include "duk_GameObject.hpp"
#include "../../util/Vector3.hpp"
#include "../../scene/Scene.hpp"
#include "../../gameobject/GameObject.hpp"
#include <iostream>
#include <string>

using namespace std;

void duk_GameObject::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_GameObject::setLocation, 2);
	duk_put_prop_string(ctx, -2, "setLocation");
	duk_push_c_function(ctx, duk_GameObject::getLocation, 1);
	duk_put_prop_string(ctx, -2, "getLocation");
	duk_push_c_function(ctx, duk_GameObject::test, 0);
	duk_put_prop_string(ctx, -2, "test");
	duk_put_global_string(ctx, "GameObject");
}

duk_ret_t duk_GameObject::setLocation(duk_context *ctx) {
	string gameObjectName = duk_safe_to_string(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	Vector3 vec = Vector3(x, y, z);
	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	gameObject->setLocation(vec);

	return 0;
}

duk_ret_t duk_GameObject::getLocation(duk_context *ctx) {
	string gameObjectName = duk_safe_to_string(ctx, 0);
	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	Vector3 vec = gameObject->getLocation();

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, vec.x);
	duk_push_number(ctx, vec.y);
	duk_push_number(ctx, vec.z);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_GameObject::test(duk_context *ctx) {
	cout << "GAMEOBJECT TEST" << endl;
	return 0;
}