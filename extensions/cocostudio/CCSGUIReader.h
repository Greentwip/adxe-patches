/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __CCSGUIREADER_H__
#define __CCSGUIREADER_H__

#include "ui/UILayout.h"
#include "DictionaryHelper.h"
#include "WidgetReader/WidgetReaderProtocol.h"
#include "base/ObjectFactory.h"
#include "base/CCValue.h"
#include "CocosStudioExport.h"

namespace protocolbuffers
{
class NodeTree;
}

namespace tinyxml2
{
class XMLElement;
}

namespace cocostudio
{

class CocoLoader;
struct stExpCocoNode;

#define kCCSVersion 1.0

typedef void (cocos2d::Ref::*SEL_ParseEvent)(std::string_view, cocos2d::Ref*, const rapidjson::Value&);
#define parseselector(_SELECTOR) (SEL_ParseEvent)(&_SELECTOR)

class CCS_DLL GUIReader : public cocos2d::Ref
{
public:
    CC_DEPRECATED_ATTRIBUTE static GUIReader* shareReader() { return GUIReader::getInstance(); };
    CC_DEPRECATED_ATTRIBUTE static void purgeGUIReader() { GUIReader::destroyInstance(); };

    static GUIReader* getInstance();
    static void destroyInstance();

    cocos2d::ui::Widget* widgetFromJsonFile(const char* fileName);

    cocos2d::ui::Widget* widgetFromBinaryFile(const char* fileName);

    int getVersionInteger(const char* str);
    /**
     *  @js NA
     */
    void storeFileDesignSize(const char* fileName, const cocos2d::Size& size);
    /**
     *  @js NA
     */
    cocos2d::Size getFileDesignSize(const char* fileName) const;

    void setFilePath(std::string_view strFilePath) { m_strFilePath = strFilePath; }
    std::string_view getFilePath() const { return m_strFilePath; }

    void registerTypeAndCallBack(std::string_view classType,
                                 cocos2d::ObjectFactory::Instance ins,
                                 Ref* object,
                                 SEL_ParseEvent callBack);

    void registerTypeAndCallBack(std::string_view classType,
                                 cocos2d::ObjectFactory::InstanceFunc ins,
                                 Ref* object,
                                 SEL_ParseEvent callBack);

protected:
    GUIReader();
    ~GUIReader();

    std::string m_strFilePath;
    cocos2d::ValueMap _fileDesignSizes;

    typedef hlookup::string_map<SEL_ParseEvent> ParseCallBackMap;
    ParseCallBackMap _mapParseSelector;
    typedef hlookup::string_map<Ref*> ParseObjectMap;
    ParseObjectMap _mapObject;

public:
    ParseCallBackMap* getParseCallBackMap() { return &_mapParseSelector; };
    ParseObjectMap* getParseObjectMap() { return &_mapObject; };
};

class CCS_DLL WidgetPropertiesReader : public cocos2d::Ref
{
public:
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic,
                                              const char* fullPath,
                                              const char* fileName) = 0;

    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& data)  = 0;
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader,
                                                        cocos2d::ui::Widget* widget,
                                                        const rapidjson::Value& options) = 0;

    virtual void setPropsForAllCustomWidgetFromJsonDictionary(std::string_view classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) = 0;

    // add binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader,
                                                        stExpCocoNode* pCocoNode,
                                                        const char* fileName)                       = 0;
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader, stExpCocoNode* pCocoNode) = 0;
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode* pCocoNode)                           = 0;

protected:
    void setAnchorPointForWidget(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    std::string getWidgetReaderClassName(std::string_view classname);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget* widget);

    std::string getGUIClassName(std::string_view name);
    cocos2d::ui::Widget* createGUI(std::string_view classname);
    WidgetReaderProtocol* createWidgetReaderProtocol(std::string_view classname);

protected:
    std::string m_strFilePath;
};

class CCS_DLL WidgetPropertiesReader0250 : public WidgetPropertiesReader
{

public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};

    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic,
                                              const char* fullPath,
                                              const char* fileName) override;

    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic) override;

    // added for binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader,
                                                        stExpCocoNode* pCocoNode,
                                                        const char* fileName) override;

    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader, stExpCocoNode* pCocoNode) override;

    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode* pCocoNode) override;

    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);

    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);

    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);

    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader,
                                                        cocos2d::ui::Widget* widget,
                                                        const rapidjson::Value& options) override;
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(std::string_view classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) override;
};

class CCS_DLL WidgetPropertiesReader0300 : public WidgetPropertiesReader
{

public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};

    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic,
                                              const char* fullPath,
                                              const char* fileName) override;

    // add bin parse support
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader,
                                                        stExpCocoNode* pCocoNode,
                                                        const char* fileName) override;

    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader, stExpCocoNode* pCocoNode) override;

    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode* pCocoNode) override;

    virtual void setPropsForAllCustomWidgetFromBinary(std::string_view classType,
                                                      cocos2d::ui::Widget* widget,
                                                      CocoLoader* cocoLoader,
                                                      stExpCocoNode* pCocoNode);

    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic) override;

    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader,
                                                        cocos2d::ui::Widget* widget,
                                                        const rapidjson::Value& options) override;

    virtual void setPropsForAllCustomWidgetFromJsonDictionary(std::string_view classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) override;
};

}  // namespace cocostudio

#endif /* defined(__CCSGUIReader__) */
