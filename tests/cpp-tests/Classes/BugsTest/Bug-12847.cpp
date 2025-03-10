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

//
//  Bug-12847.cpp
//  cocos2d_tests
//
//  Issue: https://github.com/cocos2d/cocos2d-x/issues/12847
//  Please test in iPhone5 +
//
//

#include "Bug-12847.h"

USING_NS_CC;

Bug12847Layer::Bug12847Layer()
{
    _projection = Director::getInstance()->getProjection();
}

Bug12847Layer::~Bug12847Layer()
{
    Director::getInstance()->setProjection(_projection);
}

bool Bug12847Layer::init()
{
    if (BugsTestBase::init())
    {
        Director::getInstance()->setProjection(Director::Projection::_2D);
        auto _visibleSize = Director::getInstance()->getVisibleSize();

        // Create with Sprite
        {
            sprite1 = Sprite::create("Images/bug12847_sprite.png");
            sprite1->getTexture()->setAliasTexParameters();
            sprite1->setPosition(Vec2(_visibleSize.width / 3, 50.0f));
            this->addChild(sprite1, 1);

            sprite2 = Sprite::create("Images/bug12847_sprite.png");
            sprite2->getTexture()->setAliasTexParameters();
            sprite2->setPosition(sprite1->getPosition() + Vec2(0.0f, sprite1->getContentSize().height));
            this->addChild(sprite2, 1);
        }
        // Create with SpriteFrame
        {
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/bug12847_spriteframe.plist");

            sprite3 = Sprite::createWithSpriteFrameName("bug12847_sprite2.png");
            sprite3->getTexture()->setAliasTexParameters();
            sprite3->setPosition(Vec2(_visibleSize.width * 2 / 3, 50.0f));
            this->addChild(sprite3, 1);

            sprite4 = Sprite::createWithSpriteFrameName("bug12847_sprite2.png");
            sprite4->getTexture()->setAliasTexParameters();
            sprite4->setPosition(sprite3->getPosition() + Vec2(0.0f, sprite3->getContentSize().height));
            this->addChild(sprite4, 1);
        }

        this->scheduleUpdate();
        return true;
    }

    return false;
}

void Bug12847Layer::update(float dt)
{
    sprite1->setPositionY(sprite1->getPositionY() + 0.01f);
    sprite2->setPositionY(sprite2->getPositionY() + 0.01f);
    sprite3->setPositionY(sprite3->getPositionY() + 0.01f);
    sprite4->setPositionY(sprite4->getPositionY() + 0.01f);
}

void Bug12847Layer::onEnter()
{
    BugsTestBase::onEnter();
    Director::getInstance()->setClearColor(Color4F::RED);
}

void Bug12847Layer::onExit()
{
    Director::getInstance()->setClearColor(Color4F::BLACK);
    BugsTestBase::onExit();
}