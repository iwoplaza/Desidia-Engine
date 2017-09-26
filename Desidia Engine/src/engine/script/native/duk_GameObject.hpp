/*
This is an object that handles all the GameObject operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"

class duk_GameObject {
public:
	static void init(duk_context *ctx);
	static duk_ret_t getLocation(duk_context *ctx);
	static duk_ret_t getOrientation(duk_context *ctx);
	static duk_ret_t getForwardVector(duk_context *ctx);
	static duk_ret_t getRightVector(duk_context *ctx);
	static duk_ret_t setLocation(duk_context *ctx);
	static duk_ret_t setOrientation(duk_context *ctx);
	static duk_ret_t setOrientationEuler(duk_context *ctx);
	static duk_ret_t resetOrientation(duk_context *ctx);
	static duk_ret_t rotate(duk_context *ctx);
	static duk_ret_t rotateX(duk_context *ctx);
	static duk_ret_t rotateY(duk_context *ctx);
	static duk_ret_t rotateZ(duk_context *ctx);
	static duk_ret_t getComponents(duk_context *ctx);
	static duk_ret_t getComponent(duk_context *ctx);
};