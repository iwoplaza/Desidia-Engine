#pragma once
#include <string>
#include <vector>
#include <map>
#include <rapidjson\document.h>

typedef unsigned long int COMPONENT_UID;

class GameObject;
class Component;

using namespace std;
using namespace rapidjson;

typedef Component*(*FUNCTION_COMPONENT_PARSE)(const rapidjson::Value &);

class Component {
	protected:
		GameObject* m_gameObject;
	public:
		Component();
		~Component();

		GameObject* getGameObject();
		Component* setGameObject(GameObject* _gameObject);

		virtual void init() {};
		virtual void postInit() {};
		virtual void update() {};
		virtual void reload() {};
		virtual void draw() {};
		virtual void onMouseMove() {};
		virtual const char* getType() = 0;

		static map<string, FUNCTION_COMPONENT_PARSE> callbackMap;
		static void registerAll();
		static void registerComponent(string, FUNCTION_COMPONENT_PARSE);
		static Component* parseJSON(string, const rapidjson::Value&);
};