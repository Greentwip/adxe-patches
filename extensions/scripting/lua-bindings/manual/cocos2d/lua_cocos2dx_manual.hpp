/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

 https://adxeproject.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif


#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"
#include "base/CCEventListenerAcceleration.h"
#include "base/CCEventListenerCustom.h"
#include "2d/CCNode.h"

NS_CC_BEGIN
class LuaEventListenerCustom
{
public:
    static EventListenerCustom* create(std::string_view eventName);
};

class LuaEventListenerAcceleration
{
public:
    static EventListenerAcceleration* create();
};
NS_CC_END

USING_NS_CC;

TOLUA_API int register_all_cocos2dx_manual(lua_State* tolua_S);

TOLUA_API int register_all_cocos2dx_module_manual(lua_State* tolua_S);

TOLUA_API int register_all_cocos2dx_math_manual(lua_State* tolua_S);

TOLUA_API int register_all_cocos2dx_shaders_manual(lua_State *tolua_S);

TOLUA_API int register_all_cocos2dx_bytearray_manual(lua_State *tulua_S);

struct LuaEventAccelerationData
{
    void* acc;
    Event* event;

    LuaEventAccelerationData(void* inAcc,Event* inEvent)
    :acc(inAcc),event(inEvent)
    {
    }
};

struct LuaEventKeyboarData
{
    int keyCode;
    Event* event;

    LuaEventKeyboarData(int inKeyCode,Event* inEvent)
    :keyCode(inKeyCode),event(inEvent)
    {
    }
};

struct LuaEventTouchData
{
    Touch* touch;
    Event* event;

    LuaEventTouchData(Touch* inTouch, Event* inEvent)
    :touch(inTouch),
    event(inEvent)
    {
    }
};

struct LuaEventTouchesData
{
    std::vector<Touch*> touches;
    Event* event;

    LuaEventTouchesData(const std::vector<Touch*>& inTouches, Event* inEvent)
    :touches(inTouches),
    event(inEvent)
    {
    }
};

struct LuaEventMouseData
{
    Event* event;

    LuaEventMouseData(Event* inEvent)
    :event(inEvent)
    {
    }
};

class LuaNode :public cocos2d::Node
{
public:
    virtual ~LuaNode() {}

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
};

TOLUA_API int tolua_luanode_open(lua_State* tolua_S);
TOLUA_API int register_luanode_manual(lua_State* tolua_S);

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
