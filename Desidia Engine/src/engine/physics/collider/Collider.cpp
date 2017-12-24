#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "PolygonCollider.hpp"
#include "MeshCollider.hpp"
#include <iostream>

std::map<std::string, FUNCTION_COLLIDER_PARSE> Collider::callbackMap = std::map<std::string, FUNCTION_COLLIDER_PARSE>();

void Collider::registerAll() {
	registerComponent("SphereCollider", SphereCollider::parseJSON);
	registerComponent("PolygonCollider", PolygonCollider::parseJSON);
	registerComponent("MeshCollider", MeshCollider::parseJSON);
}

void Collider::registerComponent(std::string _type, FUNCTION_COLLIDER_PARSE _callback) {
	callbackMap[_type] = _callback;
}

Collider* Collider::parseJSON(std::string _type, const Value& _value) {
	if (callbackMap.find(_type) == callbackMap.end())
		return nullptr;

	return callbackMap[_type](_value);
}