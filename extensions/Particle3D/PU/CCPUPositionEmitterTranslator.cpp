/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "CCPUPositionEmitterTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUPositionEmitterTranslator::PUPositionEmitterTranslator() {}
//-------------------------------------------------------------------------
bool PUPositionEmitterTranslator::translateChildProperty(PUScriptCompiler* compiler, PUAbstractNode* node)
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEmitter* em                = static_cast<PUEmitter*>(prop->parent->context);
    PUPositionEmitter* emitter   = static_cast<PUPositionEmitter*>(em);

    if (prop->name == token[TOKEN_POS_ADD_POSITION])
    {
        // Property: add_position
        if (passValidateProperty(compiler, prop, token[TOKEN_POS_ADD_POSITION], VAL_VECTOR3))
        {
            Vec3 val;
            if (getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->addPosition(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_POS_RANDOMIZE])
    {
        // Property: random_position
        if (passValidateProperty(compiler, prop, token[TOKEN_POS_RANDOMIZE], VAL_BOOL))
        {
            bool val;
            if (getBoolean(*prop->values.front(), &val))
            {
                emitter->setRandomized(val);
                return true;
            }
        }
    }

    return false;
}

bool PUPositionEmitterTranslator::translateChildObject(PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/)
{
    // No objects
    return false;
}

NS_CC_END
