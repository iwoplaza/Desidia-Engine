#pragma once

#include <rapidjson\document.h>
#include <map>

using namespace rapidjson;

class Collider;

typedef Collider*(*FUNCTION_COLLIDER_PARSE)(const rapidjson::Value &);

class Collider {
	public:
		virtual const char* getTypeName() = 0;
		virtual void drawGizmos() {};

		static std::map<std::string, FUNCTION_COLLIDER_PARSE> callbackMap;
		static void registerAll();
		static void registerComponent(std::string, FUNCTION_COLLIDER_PARSE);
		static Collider* parseJSON(std::string _type, const Value& _value);
};