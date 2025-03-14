/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2022 Bytedance Inc.

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

#include "ui/UIVideoPlayer/UIVideoPlayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#    include <unordered_map>
#    include <stdlib.h>
#    include <jni.h>
#    include <string>
#    include "platform/android/jni/JniHelper.h"
#    include "base/CCDirector.h"
#    include "base/CCEventListenerKeyboard.h"
#    include "platform/CCFileUtils.h"
#    include "ui/UIHelper.h"

//-----------------------------------------------------------------------------------------------------------

static const char* videoHelperClassName = "org.cocos2dx.lib.Cocos2dxVideoHelper";

USING_NS_CC;

static void executeVideoCallback(int index, int event);

#    define QUIT_FULLSCREEN 1000

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxVideoHelper_nativeExecuteVideoCallback(JNIEnv*,
                                                                                            jclass,
                                                                                            jint index,
                                                                                            jint event)
{
    executeVideoCallback(index, event);
}
}

int createVideoWidgetJNI()
{
    JniMethodInfo t;
    int ret = -1;
    if (JniHelper::getStaticMethodInfo(t, videoHelperClassName, "createVideoWidget", "()I"))
    {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);

        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

void setLoopingJNI(int index, bool looping)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, videoHelperClassName, "setLooping", "(IZ)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, looping);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setUserInputEnabledJNI(int index, bool enableInput)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, videoHelperClassName, "setUserInputEnabled", "(IZ)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, enableInput);

        t.env->DeleteLocalRef(t.classID);
    }
}

//-----------------------------------------------------------------------------------------------------------

using namespace cocos2d::ui;

static std::unordered_map<int, VideoPlayer*> s_allVideoPlayers;

VideoPlayer::VideoPlayer()
    : _fullScreenDirty(false)
    , _fullScreenEnabled(false)
    , _keepAspectRatioEnabled(false)
    , _videoPlayerIndex(-1)
    , _eventCallback(nullptr)
    , _isPlaying(false)
    , _isLooping(false)
    , _isUserInputEnabled(true)
    , _styleType(StyleType::DEFAULT)
{
    _videoPlayerIndex                    = createVideoWidgetJNI();
    s_allVideoPlayers[_videoPlayerIndex] = this;

#    if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#    endif
}

VideoPlayer::~VideoPlayer()
{
    s_allVideoPlayers.erase(_videoPlayerIndex);
    JniHelper::callStaticVoidMethod(videoHelperClassName, "removeVideoWidget", _videoPlayerIndex);
}

void VideoPlayer::setFileName(std::string_view fileName)
{
    _videoURL    = FileUtils::getInstance()->fullPathForFilename(fileName);
    _videoSource = VideoPlayer::Source::FILENAME;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoUrl", _videoPlayerIndex, (int)Source::FILENAME,
                                    _videoURL);
}

void VideoPlayer::setURL(std::string_view videoUrl)
{
    _videoURL    = videoUrl;
    _videoSource = VideoPlayer::Source::URL;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoUrl", _videoPlayerIndex, (int)Source::URL,
                                    _videoURL);
}

void VideoPlayer::setLooping(bool looping)
{
    _isLooping = looping;
    setLoopingJNI(_videoPlayerIndex, _isLooping);
}

void VideoPlayer::setUserInputEnabled(bool enableInput)
{
    _isUserInputEnabled = enableInput;
    setUserInputEnabledJNI(_videoPlayerIndex, enableInput);
}

void VideoPlayer::setStyle(StyleType style)
{
    _styleType = style;
}

void VideoPlayer::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    cocos2d::ui::Widget::draw(renderer, transform, flags);

    if (flags & FLAGS_TRANSFORM_DIRTY)
    {
        auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(this);
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoRect", _videoPlayerIndex, (int)uiRect.origin.x,
                                        (int)uiRect.origin.y, (int)uiRect.size.width, (int)uiRect.size.height);
    }

#    if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode->clear();
    auto size         = getContentSize();
    Point vertices[4] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#    endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    if (_fullScreenEnabled != enabled)
    {
        _fullScreenEnabled = enabled;

        auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setFullScreenEnabled", _videoPlayerIndex, enabled,
                                        (int)frameSize.width, (int)frameSize.height);
    }
}

bool VideoPlayer::isFullScreenEnabled() const
{
    return _fullScreenEnabled;
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable)
    {
        _keepAspectRatioEnabled = enable;
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoKeepRatioEnabled", _videoPlayerIndex, enable);
    }
}

void VideoPlayer::play()
{
    if (!_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "startVideo", _videoPlayerIndex);
    }
}

void VideoPlayer::pause()
{
    if (!_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "pauseVideo", _videoPlayerIndex);
    }
}

void VideoPlayer::resume()
{
    if (!_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "resumeVideo", _videoPlayerIndex);
    }
}

void VideoPlayer::stop()
{
    if (!_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "stopVideo", _videoPlayerIndex);
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (!_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "seekVideoTo", _videoPlayerIndex, int(sec * 1000));
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}

bool VideoPlayer::isLooping() const
{
    return _isLooping;
}

bool VideoPlayer::isUserInputEnabled() const
{
    return _isUserInputEnabled;
}

void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);

    if (!visible || isRunning())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoVisible", _videoPlayerIndex, visible);
    }
}

void VideoPlayer::onEnter()
{
    Widget::onEnter();
    if (isVisible() && !_videoURL.empty())
    {
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoVisible", _videoPlayerIndex, true);
    }
}

void VideoPlayer::onExit()
{
    Widget::onExit();
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoVisible", _videoPlayerIndex, false);
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback)
{
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(int event)
{
    if (event == QUIT_FULLSCREEN)
    {
        _fullScreenEnabled = false;
    }
    else
    {
        VideoPlayer::EventType videoEvent = (VideoPlayer::EventType)event;
        if (videoEvent == VideoPlayer::EventType::PLAYING)
        {
            _isPlaying = true;
        }
        else
        {
            _isPlaying = false;
        }

        if (_eventCallback)
        {
            _eventCallback(this, videoEvent);
        }
    }
}

cocos2d::ui::Widget* VideoPlayer::createCloneInstance()
{
    return VideoPlayer::create();
}

void VideoPlayer::copySpecialProperties(Widget* widget)
{
    VideoPlayer* videoPlayer = dynamic_cast<VideoPlayer*>(widget);
    if (videoPlayer)
    {
        _isPlaying              = videoPlayer->_isPlaying;
        _isLooping              = videoPlayer->_isLooping;
        _isUserInputEnabled     = videoPlayer->_isUserInputEnabled;
        _styleType              = videoPlayer->_styleType;
        _fullScreenEnabled      = videoPlayer->_fullScreenEnabled;
        _fullScreenDirty        = videoPlayer->_fullScreenDirty;
        _videoURL               = videoPlayer->_videoURL;
        _keepAspectRatioEnabled = videoPlayer->_keepAspectRatioEnabled;
        _videoSource            = videoPlayer->_videoSource;
        _videoPlayerIndex       = videoPlayer->_videoPlayerIndex;
        _eventCallback          = videoPlayer->_eventCallback;
    }
}

void executeVideoCallback(int index, int event)
{
    auto it = s_allVideoPlayers.find(index);
    if (it != s_allVideoPlayers.end())
    {
        s_allVideoPlayers[index]->onPlayEvent(event);
    }
}

#endif
