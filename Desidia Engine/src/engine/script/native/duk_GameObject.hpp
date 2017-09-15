/*
This is the duk representation of a GameObject
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_GameObject {
public:
	static void init(duk_context *ctx);
	static duk_ret_t setLocation(duk_context *ctx);
	static duk_ret_t getLocation(duk_context *ctx);
	static duk_ret_t test(duk_context *ctx);
};