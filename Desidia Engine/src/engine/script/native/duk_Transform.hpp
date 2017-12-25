/*
This is an object that handles all the Transform operations through JS code.
*/

#pragma once
#include "../../lib/duktape/duktape.h"
#include "../../gameobject/Transform.hpp"

class duk_Transform {
public:
	static void init(duk_context *ctx);
	static Transform* parseTransform(duk_context *ctx, duk_idx_t obj_idx);
	static void pushTransform(duk_context *ctx, const char* gameObjectName);
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
};