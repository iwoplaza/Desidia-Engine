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
	duk_push_c_function(ctx, duk_GameObject::getTransform, 1);
	duk_put_prop_string(ctx, -2, "getTransform");
	duk_push_c_function(ctx, duk_GameObject::getComponents, 2);
	duk_put_prop_string(ctx, -2, "getComponents");
	duk_push_c_function(ctx, duk_GameObject::getComponent, 2);
	duk_put_prop_string(ctx, -2, "getComponent");
	duk_put_global_string(ctx, "GameObject");
}

duk_ret_t duk_GameObject::getTransform(duk_context *ctx) {
	duk_Transform::pushTransform(ctx, duk_safe_to_string(ctx, 0));
	return 1;
}

duk_ret_t duk_GameObject::getComponents(duk_context *ctx) {
	duk_Component::pushComponents(ctx, duk_safe_to_string(ctx, 0), duk_safe_to_string(ctx, 1));
	return 1;
}

duk_ret_t duk_GameObject::getComponent(duk_context *ctx) {
	duk_Component::pushComponent(ctx, duk_safe_to_string(ctx, 0), duk_safe_to_string(ctx, 1), 0);
	return 1;
}