
#include <dmsdk/sdk.h>

#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

static int GetRotationTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Quat& rotation    = dmGameObject::GetRotation(instance);

    dmVMath::Quat* out = dmScript::CheckQuat(L, 2);
    *out               = rotation;

    return 0;
}

static int GetWorldRotationTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Quat& rotation    = dmGameObject::GetWorldRotation(instance);

    dmVMath::Quat* out = dmScript::CheckQuat(L, 2);
    *out               = rotation;

    return 0;
}

static int GetPositionTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Point3& position  = dmGameObject::GetPosition(instance);

    dmVMath::Vector3* out = dmScript::CheckVector3(L, 2);
    out->setX(position.getX());
    out->setY(position.getY());
    out->setZ(position.getZ());

    return 0;
}

static int GetWorldPositionTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Point3& position  = dmGameObject::GetWorldPosition(instance);

    dmVMath::Vector3* out = dmScript::CheckVector3(L, 2);
    out->setX(position.getX());
    out->setY(position.getY());
    out->setZ(position.getZ());

    return 0;
}

static int GetScaleTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Vector3& scale    = dmGameObject::GetScale(instance);

    dmVMath::Vector3* out = dmScript::CheckVector3(L, 2);
    out->setX(scale.getX());
    out->setY(scale.getY());
    out->setZ(scale.getZ());

    return 0;
}

static int GetWorldScaleTo(lua_State* L)
{
    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L, 1);
    const dmVMath::Vector3& scale    = dmGameObject::GetWorldScale(instance);

    dmVMath::Vector3* out = dmScript::CheckVector3(L, 2);
    out->setX(scale.getX());
    out->setY(scale.getY());
    out->setZ(scale.getZ());

    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] = {
    { "get_position_to", GetPositionTo },
    { "get_world_position_to", GetWorldPositionTo },
    { "get_rotation_to", GetRotationTo },
    { "get_world_rotation_to", GetWorldRotationTo },
    { "get_scale_to", GetScaleTo },
    { "get_world_scale_to", GetWorldScaleTo },
    /* Sentinel: */
    { NULL, NULL }
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, "scene3d", Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result InitializeExt(dmExtension::Params* params)
{
    LuaInit(params->m_L);

    g_FrustumMeshes.reserve(1000);

    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnPreRender(dmExtension::Params* params)
{
    PreRender_InvokeCallbacks();

    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnPostRender(dmExtension::Params* params)
{
    // Nothing here yet.
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppInitializeExt(dmExtension::AppParams* params)
{
    dmExtension::RegisterCallback(dmExtension::CALLBACK_PRE_RENDER, OnPreRender);
    dmExtension::RegisterCallback(dmExtension::CALLBACK_POST_RENDER, OnPostRender);

    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExt(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExt(dmExtension::AppParams* params)
{
    PreRender_ClearCallbacks();

    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnUpdateExt(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(scene3d, "scene3d", AppInitializeExt, AppFinalizeExt, InitializeExt, OnUpdateExt, 0, FinalizeExt)
