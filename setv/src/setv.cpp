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

static int setv_world_to_local_position(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 3);
	dmVMath::Vector3* world_position = dmScript::CheckVector3(L, 2);

	dmVMath::Matrix4 go_transform = dmGameObject::GetWorldMatrix(instance);
	dmVMath::Matrix4 world_transform = dmVMath::Matrix4::identity();
	world_transform.setTranslation(*world_position);
	dmVMath::Matrix4 result_transform = world_transform * go_transform;

	dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
	const dmVMath::Vector3& result_translation = result_transform.getTranslation();

	out->setX(result_translation.getX());
	out->setY(result_translation.getY());
	out->setZ(result_translation.getZ());

	return 0;
}

static int setv_world_to_local_transform(lua_State* L)
{
	dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 2);
	dmVMath::Matrix4* world_transform = dmScript::CheckMatrix4(L, 3);

	const dmVMath::Matrix4& go_transform = dmGameObject::GetWorldMatrix(instance);

	dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
	*out                  = *world_transform * go_transform;

	return 0;
}

//* Arithmetic
//* ----------------------------------------------------------------------------

static int setv_add(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 3);
			*out = *lhs + *rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 2);
			dmVMath::Vector4* rhs = dmScript::CheckVector4(L, 3);
			*out = *lhs + *rhs;
	}

	return 0;
}

static int setv_sub(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 3);
			*out = *lhs - *rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 2);
			dmVMath::Vector4* rhs = dmScript::CheckVector4(L, 3);
			*out = *lhs - *rhs;
	}

	return 0;
}

static int setv_mul(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs * rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs * rhs;
	}

	return 0;
}

static int setv_div(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			float rhs = (float) luaL_checknumber(L, 3);
			*out = *lhs / rhs;
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 2);
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
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 3);
			*out = dmVMath::Cross(*lhs, *rhs);
	}
	
	return 0;
}

static int setv_mul_per_elem(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 3);
			*out = dmVMath::MulPerElem(*lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 2);
			dmVMath::Vector4* rhs = dmScript::CheckVector4(L, 3);
			*out = dmVMath::MulPerElem(*lhs, *rhs);
	}
	
	return 0;
}

static int setv_normalize(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Vector3* a = dmScript::CheckVector3(L, 2);
			*out = dmVMath::Normalize(*a);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			dmVMath::Vector4* a = dmScript::CheckVector4(L, 2);
			*out = dmVMath::Normalize(*a);
	}

	return 0;
}

static int setv_rotate(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			dmVMath::Quat* lhs = dmScript::CheckQuat(L, 2);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 3);
			*out = dmVMath::Rotate(*lhs, *rhs);
	}

	return 0;
}

static int setv_vector(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			*out = dmVMath::Vector3(0, 0, 0);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			*out = dmVMath::Vector4(0, 0, 0, 1);
	}

	return 0;
}

//* Quat
//* ----------------------------------------------------------------------------

static int setv_quat_conj(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			dmVMath::Quat* a = dmScript::CheckQuat(L, 2);
			*out = Vectormath::Aos::conj(*a);
	}

	return 0;
}

static int setv_quat_axis_angle(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			dmVMath::Vector3* axis = dmScript::CheckVector3(L, 2);
			float angle = (float) luaL_checknumber(L, 3);
			*out = dmVMath::Quat(*axis, angle);
	}

	return 0;
}

static int setv_quat_basis(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			dmVMath::Vector3* x = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* y = dmScript::CheckVector3(L, 3);
			dmVMath::Vector3* z = dmScript::CheckVector3(L, 4);
			dmVMath::Matrix3 m;
			m.setCol0(*x);
			m.setCol1(*y);
			m.setCol2(*z);
			*out = dmVMath::Quat(m);
	}

	return 0;
}

static int setv_quat_from_to(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			dmVMath::Vector3* from = dmScript::CheckVector3(L, 2);
			dmVMath::Vector3* to = dmScript::CheckVector3(L, 3);
			*out = dmVMath::Quat::rotation(*from, *to);
	}
	
	return 0;
}

static int setv_quat_rotation_x(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Quat::rotationX(angle);
	}

	return 0;
}

static int setv_quat_rotation_y(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Quat::rotationY(angle);
	}

	return 0;
}

static int setv_quat_rotation_z(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Quat::rotationZ(angle);
	}

	return 0;
}

static int setv_quat(lua_State* L)
{
	if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			*out = dmVMath::Quat::identity();
	}

	return 0;
}

//* Vector + Quat
//* ----------------------------------------------------------------------------

static int setv_lerp(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 3);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 4);
			*out = dmVMath::Lerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 3);
			dmVMath::Vector4* rhs = dmScript::CheckVector4(L, 4);
			*out = dmVMath::Lerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Quat* lhs = dmScript::CheckQuat(L, 3);
			dmVMath::Quat* rhs = dmScript::CheckQuat(L, 4);
			*out = dmVMath::Slerp(t, *lhs, *rhs);
	}
	
	return 0;
}

static int setv_slerp(lua_State* L)
{
	if (dmScript::IsVector3(L, 1))
	{
			dmVMath::Vector3* out = dmScript::CheckVector3(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Vector3* lhs = dmScript::CheckVector3(L, 3);
			dmVMath::Vector3* rhs = dmScript::CheckVector3(L, 4);
			*out = dmVMath::Slerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsVector4(L, 1))
	{
			dmVMath::Vector4* out = dmScript::CheckVector4(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Vector4* lhs = dmScript::CheckVector4(L, 3);
			dmVMath::Vector4* rhs = dmScript::CheckVector4(L, 4);
			*out = dmVMath::Slerp(t, *lhs, *rhs);
	}
	else if (dmScript::IsQuat(L, 1))
	{
			dmVMath::Quat* out = dmScript::CheckQuat(L, 1);
			float t = (float) luaL_checknumber(L, 2);
			dmVMath::Quat* lhs = dmScript::CheckQuat(L, 3);
			dmVMath::Quat* rhs = dmScript::CheckQuat(L, 4);
			*out = dmVMath::Slerp(t, *lhs, *rhs);
	}
	
	return 0;
}

//* Matrix
//* ----------------------------------------------------------------------------

static int setv_matrix(lua_State* L)
{
	if (lua_gettop(L) == 0 && dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			*out = dmVMath::Matrix4::identity();
	}
	else if (lua_gettop(L) == 1 && dmScript::IsMatrix4(L, 1) && dmScript::IsMatrix4(L, 2))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Matrix4* in = dmScript::CheckMatrix4(L, 1);
			*out = *in;
	}
	
	return 0;
}

static int setv_matrix_axis_angle(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Vector3* axis = dmScript::CheckVector3(L, 2);
			float angle = (float) luaL_checknumber(L, 3);
			*out = dmVMath::Matrix4::rotation(angle, *axis);
	}

	return 0;
}

static int setv_matrix_from_quat(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Quat* quat = dmScript::CheckQuat(L, 2);
			*out = dmVMath::Matrix4::rotation(*quat);
	}

	return 0;
}

static int setv_matrix_frustum(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float left = (float) luaL_checknumber(L, 2);
			float right = (float) luaL_checknumber(L, 3);
			float bottom = (float) luaL_checknumber(L, 4);
			float top = (float) luaL_checknumber(L, 5);
			float near_z = (float) luaL_checknumber(L, 6);
			if(near_z == 0.0f) near_z = 0.00001f;
			float far_z = (float) luaL_checknumber(L, 7);
			*out = dmVMath::Matrix4::frustum(left, right, bottom, top, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_inv(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Matrix4* in = dmScript::CheckMatrix4(L, 2);
			*out = dmVMath::Inverse(*in);
	}
	return 0;
}

static int setv_matrix_look_at(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Point3 eye = dmVMath::Point3(*dmScript::CheckVector3(L, 2));
			dmVMath::Point3 target = dmVMath::Point3(*dmScript::CheckVector3(L, 3));
			dmVMath::Vector3 up = *dmScript::CheckVector3(L, 4);
			*out = dmVMath::Matrix4::lookAt(eye, target, up);
	}

	return 0;
}

static int setv_matrix_orthographic(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float left = (float) luaL_checknumber(L, 2);
			float right = (float) luaL_checknumber(L, 3);
			float bottom = (float) luaL_checknumber(L, 4);
			float top = (float) luaL_checknumber(L, 5);
			float near_z = (float) luaL_checknumber(L, 6);
			float far_z = (float) luaL_checknumber(L, 7);
			*out = dmVMath::Matrix4::orthographic(left, right, bottom, top, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_ortho_inv(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			dmVMath::Matrix4* in = dmScript::CheckMatrix4(L, 2);
			*out = dmVMath::OrthoInverse(*in);
	}

	return 0;
}

static int setv_matrix_perspective(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float fov = (float) luaL_checknumber(L, 2);
			float aspect = (float) luaL_checknumber(L, 3);
			float near_z = (float) luaL_checknumber(L, 4);
			float far_z = (float) luaL_checknumber(L, 5);
			if (near_z == 0.0f) near_z = 0.00001f;
			*out = dmVMath::Matrix4::perspective(fov, aspect, near_z, far_z);
	}

	return 0;
}

static int setv_matrix_rotation_x(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Matrix4::rotationX(angle);
	}

	return 0;
}

static int setv_matrix_rotation_y(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Matrix4::rotationY(angle);
	}

	return 0;
}

static int setv_matrix_rotation_z(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			float angle = (float) luaL_checknumber(L, 2);
			*out = dmVMath::Matrix4::rotationZ(angle);
	}

	return 0;
}

static int setv_matrix_translation(lua_State* L)
{
	if (dmScript::IsMatrix4(L, 1))
	{
			dmVMath::Matrix4* out = dmScript::CheckMatrix4(L, 1);
			if (dmScript::IsVector3(L, 2))
			{
					dmVMath::Vector3* v = dmScript::CheckVector3(L, 2);
					*out = dmVMath::Matrix4::translation(*v);
			}
			else if (dmScript::IsVector4(L, 2))
			{
					dmVMath::Vector4* v = dmScript::CheckVector4(L, 2);
					*out = dmVMath::Matrix4::translation(v->getXYZ());
			}
	}
	return 0;
}

static int setv_quat_matrix(lua_State* L)
{
    if (dmScript::IsQuat(L, 1))
    {
        Vectormath::Aos::Quat *out = dmScript::CheckQuat(L, 1);
        Vectormath::Aos::Matrix4 *m = dmScript::CheckMatrix4(L, 2);
        Vectormath::Aos::Matrix3 m3(m->getCol0().getXYZ(), m->getCol1().getXYZ(), m->getCol2().getXYZ());
        *out = Vectormath::Aos::Quat(m3);
    }

    return 0;
}

static int setv_matrix_compose(lua_State* L)
{
    if (dmScript::IsMatrix4(L, 1))
    {
        Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
        Vectormath::Aos::Vector3 translation(0, 0, 0);
        if (dmScript::IsVector3(L, 2))
        {
            translation = *dmScript::CheckVector3(L, 2);
        }
        else if (dmScript::IsVector4(L, 2))
        {
            translation = dmScript::CheckVector4(L, 2)->getXYZ();
        }
        Vectormath::Aos::Quat *rotation = dmScript::CheckQuat(L, 3);
        Vectormath::Aos::Vector3 *scale = dmScript::CheckVector3(L, 4);

        Vectormath::Aos::Matrix3 rotationMatrix = Vectormath::Aos::Matrix3(*rotation);
        Vectormath::Aos::Matrix3 scaleMatrix = Vectormath::Aos::Matrix3::scale(*scale);
        Vectormath::Aos::Matrix3 rs = rotationMatrix * scaleMatrix;
        
        *out = Vectormath::Aos::Matrix4(rs, translation);
    }

    return 0;
}

static int setv_matrix_scale(lua_State* L)
{
    if (dmScript::IsMatrix4(L, 1))
    {
        Vectormath::Aos::Matrix4 *out = dmScript::CheckMatrix4(L, 1);
        int nargs = lua_gettop(L);
        
        if (nargs == 2)
        {
            if (dmScript::IsVector3(L, 2))
            {
                Vectormath::Aos::Vector3 *scale = dmScript::CheckVector3(L, 2);
                *out = Vectormath::Aos::Matrix4::scale(*scale);
            }
            else if (lua_isnumber(L, 2))
            {
                float s = (float) luaL_checknumber(L, 2);
                *out = Vectormath::Aos::Matrix4::scale(Vectormath::Aos::Vector3(s, s, s));
            }
        }
        else if (nargs == 4)
        {
            float x = (float) luaL_checknumber(L, 2);
            float y = (float) luaL_checknumber(L, 3);
            float z = (float) luaL_checknumber(L, 4);
            *out = Vectormath::Aos::Matrix4::scale(Vectormath::Aos::Vector3(x, y, z));
        }
    }

    return 0;
}

static inline float clamp_value(float value, float min_val, float max_val)
{
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

static int setv_clamp(lua_State* L)
{
    int nargs = lua_gettop(L);
    
    if (dmScript::IsVector3(L, 1))
    {
        // clamp(out, value, min, max) for vectors - modifies out in place
        Vectormath::Aos::Vector3 *out = dmScript::CheckVector3(L, 1);
        Vectormath::Aos::Vector3 *value = dmScript::CheckVector3(L, 2);
        
        float min_x, min_y, min_z;
        float max_x, max_y, max_z;
        
        if (dmScript::IsVector3(L, 3))
        {
            Vectormath::Aos::Vector3 *min_v = dmScript::CheckVector3(L, 3);
            min_x = min_v->getX();
            min_y = min_v->getY();
            min_z = min_v->getZ();
        }
        else
        {
            float min_val = (float) luaL_checknumber(L, 3);
            min_x = min_y = min_z = min_val;
        }
        
        if (dmScript::IsVector3(L, 4))
        {
            Vectormath::Aos::Vector3 *max_v = dmScript::CheckVector3(L, 4);
            max_x = max_v->getX();
            max_y = max_v->getY();
            max_z = max_v->getZ();
        }
        else
        {
            float max_val = (float) luaL_checknumber(L, 4);
            max_x = max_y = max_z = max_val;
        }
        
        out->setX(clamp_value(value->getX(), min_x, max_x));
        out->setY(clamp_value(value->getY(), min_y, max_y));
        out->setZ(clamp_value(value->getZ(), min_z, max_z));
    }
    else if (dmScript::IsVector4(L, 1))
    {
        Vectormath::Aos::Vector4 *out = dmScript::CheckVector4(L, 1);
        Vectormath::Aos::Vector4 *value = dmScript::CheckVector4(L, 2);
        
        float min_x, min_y, min_z, min_w;
        float max_x, max_y, max_z, max_w;
        
        if (dmScript::IsVector4(L, 3))
        {
            Vectormath::Aos::Vector4 *min_v = dmScript::CheckVector4(L, 3);
            min_x = min_v->getX();
            min_y = min_v->getY();
            min_z = min_v->getZ();
            min_w = min_v->getW();
        }
        else
        {
            float min_val = (float) luaL_checknumber(L, 3);
            min_x = min_y = min_z = min_w = min_val;
        }
        
        if (dmScript::IsVector4(L, 4))
        {
            Vectormath::Aos::Vector4 *max_v = dmScript::CheckVector4(L, 4);
            max_x = max_v->getX();
            max_y = max_v->getY();
            max_z = max_v->getZ();
            max_w = max_v->getW();
        }
        else
        {
            float max_val = (float) luaL_checknumber(L, 4);
            max_x = max_y = max_z = max_w = max_val;
        }
        
        out->setX(clamp_value(value->getX(), min_x, max_x));
        out->setY(clamp_value(value->getY(), min_y, max_y));
        out->setZ(clamp_value(value->getZ(), min_z, max_z));
        out->setW(clamp_value(value->getW(), min_w, max_w));
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
	{"world_to_local_position", setv_world_to_local_position},
	{"world_to_local_transform", setv_world_to_local_transform},
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
	{"quat_rotation_y", setv_quat_rotation_y},
	{"quat_rotation_z", setv_quat_rotation_z},
	{"quat", setv_quat},
	{"quat_matrix", setv_quat_matrix},
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
	{"matrix_compose", setv_matrix_compose},
  {"matrix_scale", setv_matrix_scale},
  //* Utility
  {"clamp", setv_clamp},
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
