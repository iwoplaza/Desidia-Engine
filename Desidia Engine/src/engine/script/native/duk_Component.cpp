#include "duk_Component.hpp"
#include "../../gameobject/component/Component.hpp"
#include "../../gameobject/GameObject.hpp"
#include "../../scene/Scene.hpp"

Component* duk_Component::parseComponent(duk_context *ctx, duk_idx_t obj_idx) {
	duk_get_prop_string(ctx, obj_idx, "gameObject");
	string gameObjectName = duk_get_string(ctx, -1);
	duk_get_prop_string(ctx, obj_idx, "group");
	string group = duk_get_string(ctx, -1);
	duk_get_prop_string(ctx, obj_idx, "index");
	int index = duk_get_int(ctx, -1);

	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	return gameObject->getComponent(group, index);
}

void duk_Component::pushComponent(duk_context *ctx, const char* gameObjectName, const char* componentGroupName, int index) {
	duk_push_object(ctx);
	duk_push_string(ctx, gameObjectName);
	duk_put_prop_string(ctx, -2, "gameObject");
	duk_push_string(ctx, componentGroupName);
	duk_put_prop_string(ctx, -2, "group");
	duk_push_int(ctx, 0);
	duk_put_prop_string(ctx, -2, "index");
}

void duk_Component::pushComponents(duk_context *ctx, const char* gameObjectName, const char* componentGroupName) {
	GameObject* gameObject = Scene::current->getGameObject(gameObjectName);
	vector<Component*> components = gameObject->getComponents(componentGroupName);

	duk_idx_t arr_idx = duk_push_array(ctx);
	for (int i = 0; i < components.size(); i++) {
		duk_push_object(ctx);
		duk_push_string(ctx, gameObjectName);
		duk_put_prop_string(ctx, -2, "gameObject");
		duk_push_string(ctx, componentGroupName);
		duk_put_prop_string(ctx, -2, "group");
		duk_push_int(ctx, i);
		duk_put_prop_string(ctx, -2, "index");
		duk_put_prop_index(ctx, arr_idx, i);
	}
}