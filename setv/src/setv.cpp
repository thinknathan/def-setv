// Copyright (c) 2022 Indiesoft LLC
// Copyright (c) 2023 Justin Walsh (@thejustinwalsh)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define LIB_NAME "setv"
#define MODULE_NAME "setv"

#include <dmsdk/sdk.h>

//* GO Lookups
//* ----------------------------------------------------------------------------

static int setv_get_rotation(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Quat& rotation    = dmGameObject::GetRotation(instance);

	dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
	*out               = rotation;

	return 0;
}

static int setv_get_world_rotation(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Quat& rotation    = dmGameObject::GetWorldRotation(instance);

	dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
	*out               = rotation;

	return 0;
}

static int setv_get_position(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Point3& position  = dmGameObject::GetPosition(instance);

	dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
	out->setX(position.getX());
	out->setY(position.getY());
	out->setZ(position.getZ());

	return 0;
}

static int setv_get_world_position(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Point3& position  = dmGameObject::GetWorldPosition(instance);

	dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
	out->setX(position.getX());
	out->setY(position.getY());
	out->setZ(position.getZ());

	return 0;
}

static int setv_get_scale(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Vector3& scale    = dmGameObject::GetScale(instance);

	dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
	out->setX(scale.getX());
	out->setY(scale.getY());
	out->setZ(scale.getZ());

	return 0;
}

static int setv_get_world_scale(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	const dmVMath::Vector3& scale    = dmGameObject::GetWorldScale(instance);

	dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
	out->setX(scale.getX());
	out->setY(scale.getY());
	out->setZ(scale.getZ());

	return 0;
}

//* Arithmetic
//* ----------------------------------------------------------------------------

static int setv_add(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 3);
			*out = *lhs + *rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 2);
			Vectormath::Aos::Vector4 *rhs = dmScript::CheckVector4(L, 3);
			*out = *lhs + *rhs;
	}

	return 0;
}

static int setv_sub(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 3);
			*out = *lhs - *rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 2);
			Vectormath::Aos::Vector4 *rhs = dmScript::CheckVector4(L, 3);
			*out = *lhs - *rhs;
	}

	return 0;
}

static int setv_mul(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs * rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs * rhs;
	}

	return 0;
}

static int setv_div(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs / rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs / rhs;
	}

	return 0;
}

//* Vector
//* ----------------------------------------------------------------------------

static int setv_cross(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 3);
			*out = Vectormath::Aos::cross(*lhs, *rhs);
	}
	
	return 0;
}

static int setv_mul_per_elem(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 3);
			*out = Vectormath::Aos::mulPerElem(*lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 2);
			Vectormath::Aos::Vector4 *rhs = dmScript::CheckVector4(L, 3);
			*out = Vectormath::Aos::mulPerElem(*lhs, *rhs);
	}
	
	return 0;
}

static int setv_normalize(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Vector3 *a = dmScript::CheckVector3(L, 2);
			*out = Vectormath::Aos::normalize(*a);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			Vectormath::Aos::Vector4 *a = dmScript::CheckVector4(L, 2);
			*out = Vectormath::Aos::normalize(*a);
	}

	return 0;
}

static int setv_rotate(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			Vectormath::Aos::Quat *lhs = dmScript::CheckQuat(L, 2);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 3);
			*out = Vectormath::Aos::rotate(*lhs, *rhs);
	}

	return 0;
}

static int setv_vector(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			*out = Vectormath::Aos::Vector3(0, 0, 0);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			*out = Vectormath::Aos::Vector4(0, 0, 0, 1);
	}

	return 0;
}

//* Quat
//* ----------------------------------------------------------------------------

static int setv_quat_conj(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			Vectormath::Aos::Quat *a = dmScript::CheckQuat(L, 2);
			*out = Vectormath::Aos::conj(*a);
	}

	return 0;
}

static int setv_quat_axis_angle(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			Vectormath::Aos::Vector3 *axis = dmScript::CheckVector3(L, 2);
			float angle = (float) luaL_checknumber(L, 3);
			*out = Vectormath::Aos::Quat(*axis, angle);
	}

	return 0;
}

static int setv_quat_basis(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			Vectormath::Aos::Vector3 *x = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *y = dmScript::CheckVector3(L, 3);
			Vectormath::Aos::Vector3 *z = dmScript::CheckVector3(L, 4);
			Vectormath::Aos::Matrix3 m;
			m.setCol0(*x);
			m.setCol1(*y);
			m.setCol2(*z);
			*out = Vectormath::Aos::Quat(m);
	}

	return 0;
}

static int setv_quat_from_to(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			Vectormath::Aos::Vector3 *from = dmScript::CheckVector3(L, 2);
			Vectormath::Aos::Vector3 *to = dmScript::CheckVector3(L, 3);
			*out = Vectormath::Aos::Quat::rotation(*from, *to);
	}
	
	return 0;
}

static int setv_quat_rotation_x(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Quat::rotationX(angle);
	}

	return 0;
}

static int setv_quat_rotation_y(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Quat::rotationY(angle);
	}

	return 0;
}

static int setv_quat_rotation_z(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Quat::rotationZ(angle);
	}

	return 0;
}

static int setv_quat(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			*out = Vectormath::Aos::Quat::identity();
	}

	return 0;
}

//* Vector + Quat
//* ----------------------------------------------------------------------------

static int setv_lerp(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 3);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 4);
			*out = Vectormath::Aos::lerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 3);
			Vectormath::Aos::Vector4 *rhs = dmScript::CheckVector4(L, 4);
			*out = Vectormath::Aos::lerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Quat *lhs = dmScript::CheckQuat(L, 3);
			Vectormath::Aos::Quat *rhs = dmScript::CheckQuat(L, 4);
			*out = Vectormath::Aos::slerp(t, *lhs, *rhs);
	}
	
	return 0;
}

static int setv_slerp(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Vector3 *lhs = dmScript::CheckVector3(L, 3);
			Vectormath::Aos::Vector3 *rhs = dmScript::CheckVector3(L, 4);
			*out = Vectormath::Aos::slerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Vector4 *lhs = dmScript::CheckVector4(L, 3);
			Vectormath::Aos::Vector4 *rhs = dmScript::CheckVector4(L, 4);
			*out = Vectormath::Aos::slerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsQuat(L, 1))
	{
			Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			Vectormath::Aos::Quat *lhs = dmScript::CheckQuat(L, 3);
			Vectormath::Aos::Quat *rhs = dmScript::CheckQuat(L, 4);
			*out = Vectormath::Aos::slerp(t, *lhs, *rhs);
	}
	
	return 0;
}

//* Matrix
//* ----------------------------------------------------------------------------

static int setv_matrix(lua_State* L)
{
	if (lua_gettop(L) == 0 && dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			*out = Vectormath::Aos::Matrix4::identity();
	}
	else if (lua_gettop(L) == 1 && dmScript::IsMatrix4(L, 1) && dmScript::IsMatrix4(L, 2))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Matrix4 *in = dmScript::CheckMatrix4(L, 1);
			*out = *in;
	}
	
	return 0;
}

static int setv_matrix_axis_angle(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Vector3 *axis = dmScript::CheckVector3(L, 2);
			float angle = (float) luaL_checknumber(L, 3);
			*out = Vectormath::Aos::Matrix4::rotation(angle, *axis);
	}

	return 0;
}

static int setv_matrix_from_quat(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Quat *quat = dmScript::CheckQuat(L, 2);
			*out = Vectormath::Aos::Matrix4::rotation(*quat);
	}

	return 0;
}

static int setv_matrix_frustum(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float left = (float) luaL_checknumber(L, 2);
			float right = (float) luaL_checknumber(L, 3);
			float bottom = (float) luaL_checknumber(L, 4);
			float top = (float) luaL_checknumber(L, 5);
			float near_z = (float) luaL_checknumber(L, 6);
			if(near_z == 0.0f) near_z = 0.00001f;
			float far_z = (float) luaL_checknumber(L, 7);
			*out = Vectormath::Aos::Matrix4::frustum(left, right, bottom, top, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_inv(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Matrix4 *in = dmScript::CheckMatrix4(L, 2);
			*out = Vectormath::Aos::inverse(*in);
	}
	return 0;
}

static int setv_matrix_look_at(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Point3 eye = Vectormath::Aos::Point3(*dmScript::CheckVector3(L, 2));
			Vectormath::Aos::Point3 target = Vectormath::Aos::Point3(*dmScript::CheckVector3(L, 3));
			Vectormath::Aos::Vector3 up = *dmScript::CheckVector3(L, 4);
			*out = Vectormath::Aos::Matrix4::lookAt(eye, target, up);
	}

	return 0;
}

static int setv_matrix_orthographic(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float left = (float) luaL_checknumber(L, 2);
			float right = (float) luaL_checknumber(L, 3);
			float bottom = (float) luaL_checknumber(L, 4);
			float top = (float) luaL_checknumber(L, 5);
			float near_z = (float) luaL_checknumber(L, 6);
			float far_z = (float) luaL_checknumber(L, 7);
			*out = Vectormath::Aos::Matrix4::orthographic(left, right, bottom, top, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_ortho_inv(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			Vectormath::Aos::Matrix4 *in = dmScript::CheckMatrix4(L, 2);
			*out = Vectormath::Aos::orthoInverse(*in);
	}

	return 0;
}

static int setv_matrix_perspective(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float fov = (float) luaL_checknumber(L, 2);
			float aspect = (float) luaL_checknumber(L, 3);
			float near_z = (float) luaL_checknumber(L, 4);
			float far_z = (float) luaL_checknumber(L, 5);
			if (near_z == 0.0f) near_z = 0.00001f;
			*out = Vectormath::Aos::Matrix4::perspective(fov, aspect, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_rotation_x(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Matrix4::rotationX(angle);
	}

	return 0;
}

static int setv_matrix_rotation_y(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Matrix4::rotationY(angle);
	}

	return 0;
}

static int setv_matrix_rotation_z(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = Vectormath::Aos::Matrix4::rotationZ(angle);
	}

	return 0;
}

static int setv_matrix_translation(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
			if (dmScript::IsVector3(L, 2))
			{
					Vectormath::Aos::Vector3 *v = dmScript::CheckVector3(L, 2);
					*out = Vectormath::Aos::Matrix4::translation(*v);
			}
			else if (dmScript::IsVector4(L, 2))
			{
					Vectormath::Aos::Vector4 *v = dmScript::CheckVector4(L, 2);
					*out = Vectormath::Aos::Matrix4::translation(v->getXYZ());
			}
	}
	return 0;
}

//* Native Extension Bindings
//* ----------------------------------------------------------------------------

static const luaL_reg setvModule_methods[] =
{
	//* GO Lookups
	{"get_position", setv_get_position},
	{"get_world_position", setv_get_world_position},
	{"get_rotation", setv_get_rotation},
	{"get_world_rotation", setv_get_world_rotation},
	{"get_scale", setv_get_scale},
	{"get_world_scale", setv_get_world_scale},
	//* Arithmetic
	{"add", setv_add},
	{"sub", setv_sub},
	{"mul", setv_mul},
	{"div", setv_div},
	//* Vector
	{"cross", setv_cross},
	{"mul_per_elem", setv_mul_per_elem},
	{"normalize", setv_normalize},
	{"rotate", setv_rotate},
	{"vector", setv_vector},
	//* Quat
	{"quat_conj", setv_quat_conj},
	{"quat_axis_angle", setv_quat_axis_angle},
	{"quat_basis", setv_quat_basis},
	{"quat_from_to", setv_quat_from_to},
	{"quat_rotation_x", setv_quat_rotation_x},
	{"quat_rotation_y", setv_quat_rotation_x},
	{"quat_rotation_z", setv_quat_rotation_x},
	{"quat", setv_quat},
	//* Vector + Quat
	{"lerp", setv_lerp},
	{"slerp", setv_slerp},
	//* Matrix
	{"matrix_axis_angle", setv_matrix_axis_angle},
	{"matrix_from_quat", setv_matrix_from_quat},
	{"matrix_frustum", setv_matrix_frustum},
	{"matrix_inv", setv_matrix_inv},
	{"matrix_look_at", setv_matrix_look_at},
	{"matrix_orthographic", setv_matrix_orthographic},
	{"matrix_ortho_inv", setv_matrix_ortho_inv},
	{"matrix_perspective", setv_matrix_perspective},
	{"matrix_rotation_x", setv_matrix_rotation_x},
	{"matrix_rotation_y", setv_matrix_rotation_y},
	{"matrix_rotation_z", setv_matrix_rotation_z},
	{"matrix_translation", setv_matrix_translation},
	{"matrix", setv_matrix},
	{0, 0}
};

static void setvLuaInit(lua_State* L)
{
	int top = lua_gettop(L);

	luaL_register(L, MODULE_NAME, setvModule_methods);

	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}

dmExtension::Result setvAppInitialize(dmExtension::AppParams* params)
{
	return dmExtension::RESULT_OK;
}

dmExtension::Result setvInitialize(dmExtension::Params* params)
{
	setvLuaInit(params->m_L);
	dmLogInfo("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

dmExtension::Result setvAppFinalize(dmExtension::AppParams* params)
{
	return dmExtension::RESULT_OK;
}

dmExtension::Result setvFinalize(dmExtension::Params* params)
{
	return dmExtension::RESULT_OK;
}

// Defold SDK uses a macro for setting up extension entry points:
// It must match the name field in the `ext.manifest`
DM_DECLARE_EXTENSION(setv, LIB_NAME, setvAppInitialize, setvAppFinalize, setvInitialize, 0, 0, setvFinalize)
