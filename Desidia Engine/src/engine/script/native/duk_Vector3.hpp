/*
This is the duk representation of a Vector3
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_Vector3 {
	public:
		static void init(duk_context *ctx);
		static duk_ret_t constructor(duk_context *ctx);
		static duk_ret_t addVec(duk_context *ctx);
		static duk_ret_t multiplyVec(duk_context *ctx);
		static duk_ret_t multiply(duk_context *ctx);
		static duk_ret_t length(duk_context *ctx);
		static duk_ret_t normalize(duk_context *ctx);
		static duk_ret_t toString(duk_context *ctx);
};