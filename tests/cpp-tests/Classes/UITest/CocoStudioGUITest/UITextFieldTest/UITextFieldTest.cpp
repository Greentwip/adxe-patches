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

#include "UITextFieldTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextFieldTests::UITextFieldTests()
{
    ADD_TEST_CASE(UITextFieldTest);
    ADD_TEST_CASE(UITextFieldTest_MaxLength);
    ADD_TEST_CASE(UITextFieldTest_Password);
    ADD_TEST_CASE(UITextFieldTest_LineWrap);
    ADD_TEST_CASE(UITextFieldTest_TrueTypeFont);
    ADD_TEST_CASE(UITextFieldTest_BMFont);
    ADD_TEST_CASE(UITextFieldTest_PlaceHolderColor);
}

// UITextFieldTest
UITextFieldTest::UITextFieldTest() : _displayValueLabel(nullptr) {}

UITextFieldTest::~UITextFieldTest() {}

bool UITextFieldTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(
            Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input words here", "Arial", 30);

        textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
        _displayValueLabel->setString(StringUtils::format("insert words"));
        break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word"));
        break;

    default:
        break;
    }
}

// UITextFieldTest_MaxLength
UITextFieldTest_MaxLength::UITextFieldTest_MaxLength() : _displayValueLabel(nullptr) {}

UITextFieldTest_MaxLength::~UITextFieldTest_MaxLength() {}

bool UITextFieldTest_MaxLength::init()
{
    if (UIScene::init())
    {
        Size screenSize = Director::getInstance()->getWinSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField max length", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input words here", "Arial", 30);
        textField->setMaxLengthEnabled(true);
        textField->setMaxLength(3);
        textField->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_MaxLength::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest_MaxLength::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME max length %d", textField->getMaxLength()));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME max length %d", textField->getMaxLength()));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        _displayValueLabel->setString(StringUtils::format("insert words max length %d", textField->getMaxLength()));
    }
    break;

    case TextField::EventType::DELETE_BACKWARD:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        _displayValueLabel->setString(StringUtils::format("delete word max length %d", textField->getMaxLength()));
    }
    break;

    default:
        break;
    }
}

// UITextFieldTest_Password
UITextFieldTest_Password::UITextFieldTest_Password() : _displayValueLabel(nullptr) {}

UITextFieldTest_Password::~UITextFieldTest_Password() {}

bool UITextFieldTest_Password::init()
{
    if (UIScene::init())
    {
        Size screenSize = Director::getInstance()->getWinSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            screenSize.width / 2.0f, screenSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField password", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input password here", "Arial", 30);
        textField->setPasswordEnabled(true);
        textField->setPasswordStyleText("*");
        textField->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_Password::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest_Password::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME password"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME password"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
        _displayValueLabel->setString(StringUtils::format("insert words password"));
        break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word password"));
        break;

    default:
        break;
    }
}

// UITextFieldTest_LineWrap
UITextFieldTest_LineWrap::UITextFieldTest_LineWrap() : _displayValueLabel(nullptr) {}

UITextFieldTest_LineWrap::~UITextFieldTest_LineWrap() {}

bool UITextFieldTest_LineWrap::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 30);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField line wrap", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(
            Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input words here", "fonts/Marker Felt.ttf", 30);
        textField->ignoreContentAdaptWithSize(false);
        ((Label*)(textField->getVirtualRenderer()))->setLineBreakWithoutSpace(true);
        textField->setContentSize(Size(240.0f, 170.0f));
        textField->setString("input words here");
        textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
        textField->setTextVerticalAlignment(TextVAlignment::CENTER);
        textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_LineWrap::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest_LineWrap::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size widgetSize      = _widget->getContentSize();
        textField->runAction(MoveTo::create(0.225f, Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 30)));
        _displayValueLabel->setString(StringUtils::format("attach with IME"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
        textField->setTextVerticalAlignment(TextVAlignment::CENTER);

        _displayValueLabel->setString(StringUtils::format("detach with IME"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
        _displayValueLabel->setString(StringUtils::format("insert words"));
        break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word"));
        break;

    default:
        break;
    }
}

// UITextFieldTest_TrueTypeFont
UITextFieldTest_TrueTypeFont::UITextFieldTest_TrueTypeFont() : _displayValueLabel(nullptr) {}

UITextFieldTest_TrueTypeFont::~UITextFieldTest_TrueTypeFont() {}

bool UITextFieldTest_TrueTypeFont::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("True Type Font Test - No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField", "fonts/Marker Felt.ttf", 30);
        alert->setPosition(
            Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input words here", "fonts/A Damn Mess.ttf", 30);

        textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_TrueTypeFont::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest_TrueTypeFont::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
        _displayValueLabel->setString(StringUtils::format("insert words"));
        break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word"));
        break;

    default:
        break;
    }
}

// UITextFieldTest_BMFont
UITextFieldTest_BMFont::UITextFieldTest_BMFont() : _displayValueLabel(nullptr) {}

UITextFieldTest_BMFont::~UITextFieldTest_BMFont() {}

bool UITextFieldTest_BMFont::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel = Text::create("BMFont Test - No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField", "fonts/Marker Felt.ttf", 30);
        alert->setPosition(
            Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("BMFont Text", "fonts/bitmapFontTest3.fnt", 30);
        textField->setCursorEnabled(true);
        textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_BMFont::textFieldEvent, this));
        _uiLayer->addChild(textField);

        return true;
    }
    return false;
}

void UITextFieldTest_BMFont::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
        _displayValueLabel->setString(StringUtils::format("insert words"));
        break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word"));
        break;

    default:
        break;
    }
}

// UITextFieldTest_PlaceHolderColor
UITextFieldTest_PlaceHolderColor::UITextFieldTest_PlaceHolderColor() : _displayValueLabel(nullptr) {}

UITextFieldTest_PlaceHolderColor::~UITextFieldTest_PlaceHolderColor() {}

bool UITextFieldTest_PlaceHolderColor::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the textfield events will be displayed
        _displayValueLabel =
            Text::create("You should see 16.50000, 34.0000 in the output window the first time you type",
                         "fonts/Marker Felt.ttf", 12);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(
            widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("TextField", "fonts/Marker Felt.ttf", 30);
        alert->setPosition(
            Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        // Create the textfield
        TextField* textField = TextField::create("input words here", "Arial", 30);
        textField->setPlaceHolder("input text here");
        textField->setPlaceHolderColor(Color4B::GREEN);
        textField->setTextColor(Color4B::RED);
        textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_PlaceHolderColor::textFieldEvent, this));
        _uiLayer->addChild(textField);
        return true;
    }
    return false;
}

void UITextFieldTest_PlaceHolderColor::textFieldEvent(Ref* pSender, TextField::EventType type)
{
    switch (type)
    {
    case TextField::EventType::ATTACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(
            0.225f,
            Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("attach with IME"));
    }
    break;

    case TextField::EventType::DETACH_WITH_IME:
    {
        TextField* textField = dynamic_cast<TextField*>(pSender);
        Size screenSize      = Director::getInstance()->getWinSize();
        textField->runAction(MoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
        _displayValueLabel->setString(StringUtils::format("detach with IME"));
    }
    break;

    case TextField::EventType::INSERT_TEXT:
    {
        _displayValueLabel->setString(StringUtils::format("insert words"));
        CCLOG("%f, %f", dynamic_cast<TextField*>(pSender)->getContentSize().width,
              dynamic_cast<TextField*>(pSender)->getContentSize().height);
    }
    break;

    case TextField::EventType::DELETE_BACKWARD:
        _displayValueLabel->setString(StringUtils::format("delete word"));
        break;

    default:
        break;
    }
}
