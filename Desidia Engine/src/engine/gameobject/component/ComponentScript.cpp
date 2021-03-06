#include "ComponentScript.hpp"
#include "../GameObject.hpp"
#include "../../script/Scripts.hpp"
#include "../../script/ScriptContext.hpp"
#include <iostream>

ComponentScript::ComponentScript(std::string _script)
	: Component(), script(_script), metadata("{}") {
	holderObject = "Engine.Scripts['" + script + "']";
	Scripts::loadResource(script);
}

void ComponentScript::init() {
	Scripts::realiseScript(Scripts::database[script]);
	std::string eventObject = string("{") +
		"\"metadata\": " + metadata + ", " +
		"\"gameObject\": \"" + m_gameObject->getName() + "\"" +
		"}";
	metadata = ScriptContext::handleEventCallback(script, "init", eventObject);
}

void ComponentScript::postInit() {
	std::string eventObject = string("{") +
		"\"metadata\": " + metadata + ", " +
		"\"gameObject\": \"" + m_gameObject->getName() + "\"" +
		"}";
	metadata = ScriptContext::handleEventCallback(script, "postInit", eventObject);
}

void ComponentScript::update() {
	std::string eventObject = string("{") +
		"\"metadata\": " + metadata + ", " +
		"\"gameObject\": \"" + m_gameObject->getName() + "\"" +
		"}";
	metadata = ScriptContext::handleEventCallback(script, "update", eventObject);
}

void ComponentScript::reload() {
	Scripts::loadResource(script);
	Scripts::realiseScript(Scripts::database[script]);
}

void ComponentScript::onMouseMove() {
	std::string eventObject = string("{") +
		"\"metadata\": " + metadata + ", " +
		"\"gameObject\": \"" + m_gameObject->getName() + "\"" +
		"}";
	metadata = ScriptContext::handleEventCallback(script, "mouseMove", eventObject);
}

const char* ComponentScript::getType() {
	return "ComponentScript";
}

Component* ComponentScript::parseJSON(const Value& value) {
	if (!value.HasMember("script")) {
		cerr << "[SceneLoader] Necessary parameters (script) weren't specified for a ComponentScript." << endl;
		return nullptr;
	}

	std::string script = value["script"].GetString();
	Component* component = new ComponentScript(script);
	return component;
}