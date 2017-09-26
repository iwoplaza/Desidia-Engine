/*
This is an object that handles all the ComponentCamera operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_ComponentCamera {
public:
	static void init(duk_context *ctx);
	static duk_ret_t getFOV(duk_context *ctx);
	static duk_ret_t setFOV(duk_context *ctx);
	static duk_ret_t getActiveCamera(duk_context *ctx);
};