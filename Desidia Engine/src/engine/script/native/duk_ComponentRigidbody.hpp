/*
This is an object that handles all the ComponentRigidbody operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_ComponentRigidbody {
	public:
		static void init(duk_context *ctx);
		static duk_ret_t addForce(duk_context *ctx);
		static duk_ret_t getVelocity(duk_context *ctx);
		static duk_ret_t setVelocity(duk_context *ctx);
};