/*
This is an object that handles all the GameObject operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_GameObject {
public:
	static void init(duk_context *ctx);
	static duk_ret_t getParent(duk_context *ctx);
	static duk_ret_t getTransform(duk_context *ctx);
	static duk_ret_t getComponents(duk_context *ctx);
	static duk_ret_t getComponent(duk_context *ctx);
	static duk_ret_t setParent(duk_context *ctx);
};