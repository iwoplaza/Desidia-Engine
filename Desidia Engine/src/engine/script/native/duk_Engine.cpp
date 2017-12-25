#include "duk_Engine.hpp"
#include "../ScriptContext.hpp"
#include "../Script.hpp"
#include <iostream>

using namespace std;

void duk_Engine::init(duk_context *ctx) {
	duk_push_object(ctx);
	duk_push_c_function(ctx, duk_Engine::print, 1);
	duk_put_prop_string(ctx, -2, "print");
	duk_push_c_function(ctx, duk_Engine::registerEventHandler, 2);
	duk_put_prop_string(ctx, -2, "registerEventHandler");
	duk_put_global_string(ctx, "Engine");
}

duk_ret_t duk_Engine::print(duk_context *ctx) {
	cout << "[JS]: " << duk_to_string(ctx, 0) << endl;
	return 0;
}

duk_ret_t duk_Engine::registerEventHandler(duk_context *ctx) {
	const char* eventName = duk_safe_to_string(ctx, 0);

	duk_get_global_string(ctx, "Engine");
	duk_get_prop_string(ctx, -1, "Scripts");
	duk_get_prop_string(ctx, -1, ScriptContext::workScript->getPath().c_str());
	duk_get_prop_string(ctx, -1, "eventListeners");
	duk_dup(ctx, 1);
	duk_put_prop_string(ctx, -2, eventName);

	return 0;
}