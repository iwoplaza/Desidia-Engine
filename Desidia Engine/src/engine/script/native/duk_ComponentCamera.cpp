#include "duk_ComponentCamera.hpp"
#include "duk_Component.hpp"
#include "../../gameobject/GameObject.hpp"
#include "../../scene/Scene.hpp"
#include "../../gameobject/component/ComponentCamera.hpp"
#include "../../debug/DebugConsole.hpp"
#include <iostream>
#include <string>

using namespace std;

void duk_ComponentCamera::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_ComponentCamera::getFOV, 1);
	duk_put_prop_string(ctx, -2, "getFOV");
	duk_push_c_function(ctx, duk_ComponentCamera::setFOV, 2);
	duk_put_prop_string(ctx, -2, "setFOV");
	duk_push_c_function(ctx, duk_ComponentCamera::getActiveCamera, 1);
	duk_put_prop_string(ctx, -2, "getActiveCamera");

	duk_put_global_string(ctx, "ComponentCamera");
}

duk_ret_t duk_ComponentCamera::getFOV(duk_context *ctx) {
	ComponentCamera* component = (ComponentCamera*) duk_Component::parseComponent(ctx, 0);
	duk_push_number(ctx, component->getFOV());
	return 1;
}

duk_ret_t duk_ComponentCamera::setFOV(duk_context *ctx) {
	ComponentCamera* component = (ComponentCamera*)duk_Component::parseComponent(ctx, 0);
	float fov = duk_get_number(ctx, 1);
	component->setFOV(fov);
	return 0;
}

duk_ret_t duk_ComponentCamera::getActiveCamera(duk_context *ctx) {
	ComponentCamera* activeCamera = ComponentCamera::activeCamera;
	if (activeCamera == nullptr) {
		DebugConsole::instance.logError("Couldn't get the active camera. It's most likely not yet established.");
		return 0;
	}
	GameObject* gameObject = activeCamera->getGameObject();
	if (gameObject == nullptr) {
		DebugConsole::instance.logError("The active camera isn't attached to any GameObject.");
		return 0;
	}
	//duk_Component::pushComponent(ctx, gameObject->getName(); activeCamera->get);

	return 1;
}