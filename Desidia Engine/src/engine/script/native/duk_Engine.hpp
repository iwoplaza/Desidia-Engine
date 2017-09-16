/*
This is the duk representation of the Engine
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_Engine {
	public:
		static void init(duk_context *ctx);
		static duk_ret_t print(duk_context *ctx);
		//Used to append a callback to the current script object being worked on.
		static duk_ret_t registerEventHandler(duk_context *ctx);
		static duk_ret_t handleEventCallback(duk_context *ctx);
};