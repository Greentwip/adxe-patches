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

#include "TextureCacheTest.h"

USING_NS_CC;

TextureCacheTests::TextureCacheTests()
{
    ADD_TEST_CASE(TextureCacheTest);
    ADD_TEST_CASE(TextureCacheUnbindTest);
}

TextureCacheTest::TextureCacheTest() : _numberOfSprites(20), _numberOfLoadedSprites(0)
{
    auto size = Director::getInstance()->getWinSize();

    _labelLoading = Label::createWithTTF("loading...", "fonts/arial.ttf", 15);
    _labelPercent = Label::createWithTTF("%0", "fonts/arial.ttf", 15);

    _labelLoading->setPosition(Vec2(size.width / 2, size.height / 2 - 20));
    _labelPercent->setPosition(Vec2(size.width / 2, size.height / 2 + 20));

    this->addChild(_labelLoading);
    this->addChild(_labelPercent);

    // load textures
    Director::getInstance()->getTextureCache()->addImageAsync("Images/HelloWorld.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_01.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_02.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_03.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_04.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_05.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_06.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_07.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_08.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_09.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_10.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_11.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_12.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_13.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_14.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/background1.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/background2.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/background3.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/blocks.png",
                                                              CC_CALLBACK_1(TextureCacheTest::loadingCallBack, this));
}

void TextureCacheTest::loadingCallBack(cocos2d::Texture2D* texture)
{
    ++_numberOfLoadedSprites;
    char tmp[10];
    sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
    _labelPercent->setString(tmp);

    if (_numberOfLoadedSprites == _numberOfSprites)
    {
        this->removeChild(_labelLoading, true);
        this->removeChild(_labelPercent, true);
        addSprite();
    }
}

void TextureCacheTest::addSprite()
{
    auto size = Director::getInstance()->getWinSize();

    // create sprites

    auto bg = Sprite::create("Images/HelloWorld.png");
    bg->setPosition(Vec2(size.width / 2, size.height / 2));

    auto s1  = Sprite::create("Images/grossini.png");
    auto s2  = Sprite::create("Images/grossini_dance_01.png");
    auto s3  = Sprite::create("Images/grossini_dance_02.png");
    auto s4  = Sprite::create("Images/grossini_dance_03.png");
    auto s5  = Sprite::create("Images/grossini_dance_04.png");
    auto s6  = Sprite::create("Images/grossini_dance_05.png");
    auto s7  = Sprite::create("Images/grossini_dance_06.png");
    auto s8  = Sprite::create("Images/grossini_dance_07.png");
    auto s9  = Sprite::create("Images/grossini_dance_08.png");
    auto s10 = Sprite::create("Images/grossini_dance_09.png");
    auto s11 = Sprite::create("Images/grossini_dance_10.png");
    auto s12 = Sprite::create("Images/grossini_dance_11.png");
    auto s13 = Sprite::create("Images/grossini_dance_12.png");
    auto s14 = Sprite::create("Images/grossini_dance_13.png");
    auto s15 = Sprite::create("Images/grossini_dance_14.png");

    // just loading textures to slow down
    Sprite::create("Images/background1.png");
    Sprite::create("Images/background2.png");
    Sprite::create("Images/background3.png");
    Sprite::create("Images/blocks.png");

    s1->setPosition(Vec2(50, 50));
    s2->setPosition(Vec2(60, 50));
    s3->setPosition(Vec2(70, 50));
    s4->setPosition(Vec2(80, 50));
    s5->setPosition(Vec2(90, 50));
    s6->setPosition(Vec2(100, 50));

    s7->setPosition(Vec2(50, 180));
    s8->setPosition(Vec2(60, 180));
    s9->setPosition(Vec2(70, 180));
    s10->setPosition(Vec2(80, 180));
    s11->setPosition(Vec2(90, 180));
    s12->setPosition(Vec2(100, 180));

    s13->setPosition(Vec2(50, 270));
    s14->setPosition(Vec2(60, 270));
    s15->setPosition(Vec2(70, 270));

    this->addChild(bg);

    this->addChild(s1);
    this->addChild(s2);
    this->addChild(s3);
    this->addChild(s4);
    this->addChild(s5);
    this->addChild(s6);
    this->addChild(s7);
    this->addChild(s8);
    this->addChild(s9);
    this->addChild(s10);
    this->addChild(s11);
    this->addChild(s12);
    this->addChild(s13);
    this->addChild(s14);
    this->addChild(s15);
}

TextureCacheUnbindTest::TextureCacheUnbindTest()
{
    auto size = Director::getInstance()->getWinSize();

    Label* nothing = Label::createWithTTF("There should be\nnothing below", "fonts/arial.ttf", 15);
    nothing->setPosition(Vec2(size.width / 4, 5 * size.height / 6));
    this->addChild(nothing);

    Label* something = Label::createWithTTF("There should be\na white square below", "fonts/arial.ttf", 15);
    something->setPosition(Vec2(3 * size.width / 4, 5 * size.height / 6));
    this->addChild(something);

    auto cache = Director::getInstance()->getTextureCache();

    cache->removeTextureForKey("Images/texture2048x2048.png");

    cache->addImageAsync("Images/texture2048x2048.png", CC_CALLBACK_1(TextureCacheUnbindTest::textureLoadedA, this),
                         "A");
    cache->addImageAsync("Images/texture2048x2048.png", CC_CALLBACK_1(TextureCacheUnbindTest::textureLoadedB, this),
                         "B");
    cache->unbindImageAsync("A");
}

void TextureCacheUnbindTest::textureLoadedA(Texture2D* texture)
{
    auto size = Director::getInstance()->getWinSize();
    auto s    = Sprite::create("Images/texture2048x2048.png");
    s->setScale(0.15);
    s->setPosition(size.width / 4, size.height / 2);
    this->addChild(s);
}

void TextureCacheUnbindTest::textureLoadedB(Texture2D* texture)
{
    auto size = Director::getInstance()->getWinSize();
    auto s    = Sprite::create("Images/texture2048x2048.png");
    s->setScale(0.15);
    s->setPosition(3 * size.width / 4, size.height / 2);
    this->addChild(s);
}
