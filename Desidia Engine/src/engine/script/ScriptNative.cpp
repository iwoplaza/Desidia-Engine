#include "ScriptNative.hpp"
#include "Scripts.hpp"
#include "Script.hpp"
#include "../util/Vector3.hpp"
#include "ScriptContext.hpp"
#include <iostream>

using namespace std;

vector<ScriptNative::Function> ScriptNative::functions = {
	ScriptNative::Function("print", ScriptNative::print, 1)
};

ScriptNative::Function::Function(string _name, duk_c_function _function, int _nargs) 
	: name(_name), function(_function), nargs(_nargs) {}

duk_ret_t ScriptNative::print(duk_context* context) {
	cout << "[JS]: " << duk_to_string(context, 0) << endl;
	return 0;
}

duk_ret_t ScriptNative::registerEventListener(duk_context* ctx) {
	cout << "0: " << duk_safe_to_string(ctx, 0) << endl;
	cout << "1: " << duk_safe_to_string(ctx, 1) << endl;

	const char* eventName = duk_safe_to_string(ctx, 0);

	duk_get_global_string(ctx, "Engine");
	duk_get_prop_string(ctx, -1, "Scripts");
	duk_get_prop_string(ctx, -1, ScriptContext::workScript->getPath().c_str());
	duk_get_prop_string(ctx, -1, "eventListeners");
	duk_dup(ctx, 1);
	duk_put_prop_string(ctx, -2, eventName);

	return 0;
}