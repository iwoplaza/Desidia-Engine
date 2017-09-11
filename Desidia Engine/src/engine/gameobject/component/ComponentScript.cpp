#include "ComponentScript.hpp"
#include "../../script/Scripts.hpp"
#include <iostream>

ComponentScript::ComponentScript(std::string _script)
	: Component(), script(_script) {
	holderObject = "Engine.Scripts['" + script + "']";
	Scripts::loadResource(script);
}

void ComponentScript::init() {
	Scripts::execute("Engine.Handler = {}");
	Scripts::executeScript(script);
	Scripts::execute((holderObject + " = {};" + holderObject + ".update = Engine.Handler.update;").c_str());
}

void ComponentScript::update() {
	Scripts::execute(("if("+ holderObject +" != undefined && "+ holderObject +".update != undefined) "+ holderObject +".update()").c_str());
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