#pragma once
#include <string>
#include <vector>
#include <map>
#include <rapidjson\document.h>

class GameObject;
class Component;

using namespace std;
using namespace rapidjson;

typedef Component*(*FUNCTION_COMPONENT_PARSE)(const rapidjson::Value &);

class Component {
	protected:
		GameObject* gameObject;
	public:
		Component();
		~Component();

		Component* setGameObject(GameObject* _gameObject);

		virtual void init();
		virtual void update();
		virtual void draw();
		virtual void onMouseMove();
		virtual const char* getType() = 0;

		static map<string, FUNCTION_COMPONENT_PARSE> callbackMap;
		static void registerAll();
		static void registerComponent(string, FUNCTION_COMPONENT_PARSE);
		static Component* parseJSON(string, const rapidjson::Value&);
};