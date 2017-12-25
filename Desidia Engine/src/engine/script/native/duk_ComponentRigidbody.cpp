#include "duk_ComponentRigidbody.hpp"
#include "duk_Component.hpp"
#include "../../gameobject/component/ComponentRigidbody.hpp"
#include "../../util/Vector3.hpp"

void duk_ComponentRigidbody::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_ComponentRigidbody::addForce, 2);
	duk_put_prop_string(ctx, -2, "addForce");
	duk_push_c_function(ctx, duk_ComponentRigidbody::getVelocity, 2);
	duk_put_prop_string(ctx, -2, "getVelocity");
	duk_push_c_function(ctx, duk_ComponentRigidbody::setVelocity, 2);
	duk_put_prop_string(ctx, -2, "setVelocity");

	duk_put_global_string(ctx, "ComponentRigidbody");
}

duk_ret_t duk_ComponentRigidbody::addForce(duk_context *ctx) {
	ComponentRigidbody* component = (ComponentRigidbody*)duk_Component::parseComponent(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	Vector3 vec = Vector3(x, y, z);
	component->addForce(vec);

	return 0;
}

duk_ret_t duk_ComponentRigidbody::getVelocity(duk_context *ctx) {
	ComponentRigidbody* component = (ComponentRigidbody*)duk_Component::parseComponent(ctx, 0);
	Vector3 vec = component->getVelocity();

	duk_get_global_string(ctx, "Vector3");
	duk_push_number(ctx, vec.x);
	duk_push_number(ctx, vec.y);
	duk_push_number(ctx, vec.z);
	duk_new(ctx, 3);

	return 1;
}

duk_ret_t duk_ComponentRigidbody::setVelocity(duk_context *ctx) {
	ComponentRigidbody* component = (ComponentRigidbody*)duk_Component::parseComponent(ctx, 0);

	duk_get_prop_string(ctx, 1, "x");
	float x = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "y");
	float y = duk_get_number(ctx, -1);
	duk_get_prop_string(ctx, 1, "z");
	float z = duk_get_number(ctx, -1);

	Vector3 vec = Vector3(x, y, z);
	component->setVelocity(vec);

	return 0;
}

/*duk_ret_t duk_ComponentCamera::setFOV(duk_context *ctx) {
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
}*/