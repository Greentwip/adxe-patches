/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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
#pragma once
/// @cond DO_NOT_SHOW

#include <stdint.h>
#include <iosfwd>
#include <string>
#include <string_view>

@class UIWebViewWrapper;

namespace cocos2d
{

class Data;
class Renderer;
class Mat4;

namespace ui
{

class WebView;

class WebViewImpl
{
public:
    WebViewImpl(WebView* webView);

    virtual ~WebViewImpl();

    void setJavascriptInterfaceScheme(std::string_view scheme);

    void loadData(const cocos2d::Data& data,
                  std::string_view MIMEType,
                  std::string_view encoding,
                  std::string_view baseURL);

    void loadHTMLString(std::string_view string, std::string_view baseURL);

    void loadURL(std::string_view url);
    void loadURL(std::string_view url, bool cleanCachedData);

    void loadFile(std::string_view fileName);

    void stopLoading();

    void reload();

    bool canGoBack();

    bool canGoForward();

    void goBack();

    void goForward();

    void evaluateJS(std::string_view js);

    void setScalesPageToFit(const bool scalesPageToFit);

    virtual void draw(cocos2d::Renderer* renderer, cocos2d::Mat4 const& transform, uint32_t flags);

    virtual void setVisible(bool visible);

    void setBounces(bool bounces);

    virtual void setOpacityWebView(float opacity);

    virtual float getOpacityWebView() const;

    virtual void setBackgroundTransparent();

private:
    UIWebViewWrapper* _uiWebViewWrapper;
    WebView* _webView;
};

}  // namespace ui
}  // namespace cocos2d

/// @endcond
