/*
This is an object that handles all the GameObject operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_Input {
public:
	static void init(duk_context *ctx);
	static duk_ret_t isKeyDown(duk_context *ctx);
	static duk_ret_t isKeyDownCase(duk_context *ctx);
	static duk_ret_t isMouseButtonDown(duk_context *ctx);
	static duk_ret_t getMouseMoveX(duk_context *ctx);
	static duk_ret_t getMouseMoveY(duk_context *ctx);
};