/****************************************************************************
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

#include "RotateWorldTest.h"
#include "../testResource.h"

USING_NS_CC;

RotateWorldTests::RotateWorldTests()
{
    ADD_TEST_CASE(RotateWorldTest);
}

//------------------------------------------------------------------
//
// TestLayer
//
//------------------------------------------------------------------
void TestLayer::onEnter()
{
    Layer::onEnter();

    float x, y;

    auto size = Director::getInstance()->getWinSize();
    x         = size.width;
    y         = size.height;

    // auto array = [UIFont familyNames];
    // for( String *s in array )
    //     NSLog( s );
    auto label = Label::createWithSystemFont("cocos2d", "Tahoma", 64);

    label->setPosition(Vec2(x / 2, y / 2));

    addChild(label);
}

//------------------------------------------------------------------
//
// SpriteLayer
//
//------------------------------------------------------------------
void SpriteLayer::onEnter()
{
    Layer::onEnter();

    float x, y;

    auto size = Director::getInstance()->getWinSize();
    x         = size.width;
    y         = size.height;

    auto sprite        = Sprite::create(s_pathGrossini);
    auto spriteSister1 = Sprite::create(s_pathSister1);
    auto spriteSister2 = Sprite::create(s_pathSister2);

    sprite->setScale(1.5f);
    spriteSister1->setScale(1.5f);
    spriteSister2->setScale(1.5f);

    sprite->setPosition(Vec2(x / 2, y / 2));
    spriteSister1->setPosition(Vec2(40.0f, y / 2));
    spriteSister2->setPosition(Vec2(x - 40, y / 2));

    auto rot = RotateBy::create(16, -3600);

    addChild(sprite);
    addChild(spriteSister1);
    addChild(spriteSister2);

    sprite->runAction(rot);

    auto jump1 = JumpBy::create(4, Vec2(-400, 0), 100, 4);
    auto jump2 = jump1->reverse();

    auto rot1 = RotateBy::create(4, 360 * 2);
    auto rot2 = rot1->reverse();

    spriteSister1->runAction(Repeat::create(Sequence::create(jump2, jump1, nullptr), 5));
    spriteSister2->runAction(Repeat::create(Sequence::create(jump1->clone(), jump2->clone(), nullptr), 5));

    spriteSister1->runAction(Repeat::create(Sequence::create(rot1, rot2, nullptr), 5));
    spriteSister2->runAction(Repeat::create(Sequence::create(rot2->clone(), rot1->clone(), nullptr), 5));
}

//------------------------------------------------------------------
//
// RotateWorldMainLayer
//
//------------------------------------------------------------------

void RotateWorldMainLayer::onEnter()
{
    Layer::onEnter();

    float x, y;

    auto size = Director::getInstance()->getWinSize();
    x         = size.width;
    y         = size.height;

    auto blue  = LayerColor::create(Color4B(0, 0, 255, 255));
    auto red   = LayerColor::create(Color4B(255, 0, 0, 255));
    auto green = LayerColor::create(Color4B(0, 255, 0, 255));
    auto white = LayerColor::create(Color4B(255, 255, 255, 255));

    blue->setScale(0.5f);
    blue->setPosition(Vec2(-x / 4, -y / 4));
    blue->addChild(SpriteLayer::create());

    red->setScale(0.5f);
    red->setPosition(Vec2(x / 4, -y / 4));

    green->setScale(0.5f);
    green->setPosition(Vec2(-x / 4, y / 4));
    green->addChild(TestLayer::create());

    white->setScale(0.5f);
    white->setPosition(Vec2(x / 4, y / 4));
    white->setIgnoreAnchorPointForPosition(false);
    white->setPosition(Vec2(x / 4 * 3, y / 4 * 3));

    addChild(blue, -1);
    addChild(white);
    addChild(green);
    addChild(red);

    auto rot = RotateBy::create(8, 720);

    blue->runAction(rot);
    red->runAction(rot->clone());
    green->runAction(rot->clone());
    white->runAction(rot->clone());
}

bool RotateWorldTest::init()
{
    if (TestCase::init())
    {
        auto layer = RotateWorldMainLayer::create();

        addChild(layer);
        runAction(RotateBy::create(4.0f, -360.0f));

        return true;
    }

    return false;
}
