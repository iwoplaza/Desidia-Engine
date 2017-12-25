#include "duk_Transform.hpp"
#include "../../gameobject/GameObject.hpp"
#include "../../scene/Scene.hpp"

void duk_Transform::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_Transform::getLocation, 1);
	duk_put_prop_string(ctx, -2, "getLocation");
	duk_push_c_function(ctx, duk_Transform::getOrientation, 1);
	duk_put_prop_string(ctx, -2, "getOrientation");
	duk_push_c_function(ctx, duk_Transform::getForwardVector, 1);
	duk_put_prop_string(ctx, -2, "getForwardVector");
	duk_push_c_function(ctx, duk_Transform::getRightVector, 1);
	duk_put_prop_string(ctx, -2, "getRightVector");
	duk_push_c_function(ctx, duk_Transform::setLocation, 2);
	duk_put_prop_string(ctx, -2, "setLocation");
	duk_push_c_function(ctx, duk_Transform::setOrientation, 2);
	duk_put_prop_string(ctx, -2, "setOrientation");
	duk_push_c_function(ctx, duk_Transform::setOrientationEuler, 2);
	duk_put_prop_string(ctx, -2, "setOrientationEuler");
	duk_push_c_function(ctx, duk_Transform::resetOrientation, 1);
	duk_put_prop_string(ctx, -2, "resetOrientation");
	duk_push_c_function(ctx, duk_Transform::rotate, 2);
	duk_put_prop_string(ctx, -2, "rotate");
	duk_push_c_function(ctx, duk_Transform::rotateX, 2);
	duk_put_prop_string(ctx, -2, "rotateX");
	duk_push_c_function(ctx, duk_Transform::rotateY, 2);
	duk_put_prop_string(ctx, -2, "rotateY");
	duk_push_c_function(ctx, duk_Transform::rotateZ, 2);
	duk_put_prop_string(ctx, -2, "rotateZ");
	duk_put_global_string(ctx, "Transform");
}

Transform* duk_Transform::parseTransform(duk_context *ctx, duk_idx_t obj_idx) {
	duk_get_prop_string(ctx, obj_idx, "gameObject");
	string gameObjectName = duk_get_string(ctx, -1);

	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	return gameObject->getTransform();
}

void duk_Transform::pushTransform(duk_context *ctx, const char* gameObjectName) {
	duk_push_object(ctx);
	duk_push_string(ctx, gameObjectName);
	duk_put_prop_string(ctx, -2, "gameObject");
}

duk_ret_t duk_Transform::getLocation(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	Vector3 vec = transform->getLocation();

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, vec.x);
	duk_push_number(ctx, vec.y);
	duk_push_number(ctx, vec.z);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Transform::getOrientation(duk_context *ctx) {
	//TODO implement this
	return 0;
}

duk_ret_t duk_Transform::getForwardVector(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	Vector3 vec = transform->getForwardVector();

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, vec.x);
	duk_push_number(ctx, vec.y);
	duk_push_number(ctx, vec.z);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Transform::getRightVector(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	Vector3 vec = transform->getRightVector();

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, vec.x);
	duk_push_number(ctx, vec.y);
	duk_push_number(ctx, vec.z);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_Transform::setLocation(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	transform->setLocation(Vector3(x, y, z));

	return 0;
}

duk_ret_t duk_Transform::setOrientation(duk_context *ctx) {
	return 0;
}

duk_ret_t duk_Transform::setOrientationEuler(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	transform->setOrientation(Vector3(x, y, z));

	return 0;
}

duk_ret_t duk_Transform::resetOrientation(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	transform->setOrientation(Quaternion());

	return 0;
}

duk_ret_t duk_Transform::rotate(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	transform->rotate(Vector3(x, y, z));

	return 0;
}

duk_ret_t duk_Transform::rotateX(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	float x = duk_get_number(ctx, 1);

	transform->rotateX(x);

	return 0;
}

duk_ret_t duk_Transform::rotateY(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	float y = duk_get_number(ctx, 1);

	transform->rotateY(y);

	return 0;
}

duk_ret_t duk_Transform::rotateZ(duk_context *ctx) {
	Transform* transform = parseTransform(ctx, 0);
	float z = duk_get_number(ctx, 1);

	transform->rotateZ(z);

	return 0;
}