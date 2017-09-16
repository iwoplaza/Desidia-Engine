#include "ScriptContext.hpp"
#include "../lib/duktape/duktape.h"
#include <iostream>

using namespace std;

GameObject* ScriptContext::gameObject;
Script* ScriptContext::workScript;

extern duk_context* context;

void ScriptContext::setWorkScript(Script* script) {
	workScript = script;
}

std::string ScriptContext::handleEventCallback(std::string scriptPath, std::string eventName, std::string eventObject) {
	duk_get_global_string(context, "Engine");
	duk_get_prop_string(context, -1, "Scripts");
	duk_get_prop_string(context, -1, scriptPath.c_str());
	duk_get_prop_string(context, -1, "eventListeners");
	duk_get_prop_string(context, -1, eventName.c_str());
	//cout << "OUTPUT: " << duk_safe_to_string(context, -1) << endl;
	duk_push_string(context, eventObject.c_str());
	duk_json_decode(context, -1);
	duk_call(context, 1);
	duk_get_prop_string(context, -1, "metadata");
	duk_json_encode(context, -1);
	std::string metadata = duk_get_string(context, -1);
	duk_pop(context);
	duk_pop(context);
	duk_pop(context);
	duk_pop(context);
	duk_pop(context);


	return metadata;
}