/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef __CCTEXTURE_CACHE_H__
#define __CCTEXTURE_CACHE_H__

#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <unordered_map>
#include <functional>

#include "base/CCRef.h"
#include "renderer/CCTexture2D.h"
#include "platform/CCImage.h"

#if CC_ENABLE_CACHE_TEXTURE_DATA
#    include <list>
#endif

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */
/*
 * From version 3.0, TextureCache will never be treated as a singleton, it will be owned by director.
 * All call by TextureCache::getInstance() should be replaced by Director::getInstance()->getTextureCache().
 */

/** @brief Singleton that handles the loading of textures.
 * Once the texture is loaded, the next time it will return.
 * A reference of the previously loaded texture reducing GPU & CPU memory.
 */
class CC_DLL TextureCache : public Ref
{
public:
    // ETC1 ALPHA supports.
    static void setETC1AlphaFileSuffix(std::string_view suffix);
    static std::string getETC1AlphaFileSuffix();

public:
    /**
     * @js ctor
     */
    TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    // Dictionary* snapshotTextures();

    /** Returns a Texture2D object given an filename.
    * If the filename was not previously loaded, it will create a new Texture2D.
    * Object and it will return it. It will use the filename as a key.
    * Otherwise it will return a reference of a previously loaded image.
    * Supported image extensions: .png, .bmp, .jpeg, .pvr.
     @param filepath The file path.
    */
    Texture2D* addImage(std::string_view filepath);

    /** Returns a Texture2D object given a file image.
    * If the file image was not previously loaded, it will create a new Texture2D object and it will return it.
    * Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with
    the Texture2D as a parameter.
    * The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
    * Supported image extensions: .png, .jpg
     @param filepath The file path.
     @param callback A callback function would be invoked after the image is loaded.
     @since v0.8
    */
    virtual void addImageAsync(std::string_view filepath, const std::function<void(Texture2D*)>& callback);

    void addImageAsync(std::string_view path,
                       const std::function<void(Texture2D*)>& callback,
                       std::string_view callbackKey);

    /** Unbind a specified bound image asynchronous callback.
     * In the case an object who was bound to an image asynchronous callback was destroyed before the callback is
     * invoked, the object always need to unbind this callback manually.
     * @param filename It's the related/absolute path of the file image.
     * @since v3.1
     */
    virtual void unbindImageAsync(std::string_view filename);

    /** Unbind all bound image asynchronous load callbacks.
     * @since v3.1
     */
    virtual void unbindAllImageAsync();

    /** Returns a Texture2D object given an Image.
     * If the image was not previously loaded, it will create a new Texture2D object and it will return it.
     * Otherwise it will return a reference of a previously loaded image.
     * @param key The "key" parameter will be used as the "key" for the cache.
     * If "key" is nil, then a new texture will be created each time.
     */
    Texture2D* addImage(Image* image, std::string_view key);

    /** Returns an already created texture. Returns nil if the texture doesn't exist.
    @param key It's the related/absolute path of the file image.
    @since v0.99.5
    */
    Texture2D* getTextureForKey(std::string_view key) const;

    /** Reload texture from the image file.
     * If the file image hasn't loaded before, load it.
     * Otherwise the texture will be reloaded from the file image.
     * @param fileName It's the related/absolute path of the file image.
     * @return True if the reloading is succeed, otherwise return false.
     */
    bool reloadTexture(std::string_view fileName);

    /** Purges the dictionary of loaded textures.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeAllTextures();

    /** Removes unused textures.
     * Textures that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     * @since v0.8
     */
    void removeUnusedTextures();

    /** Deletes a texture from the cache given a texture.
     */
    void removeTexture(Texture2D* texture);

    /** Deletes a texture from the cache given a its key name.
    @param key It's the related/absolute path of the file image.
    @since v0.99.4
    */
    void removeTextureForKey(std::string_view key);

    /** Output to CCLOG the current contents of this TextureCache.
     * This will attempt to calculate the size of each texture, and the total texture memory in use.
     *
     * @since v1.0
     */
    std::string getCachedTextureInfo() const;

    // Wait for texture cache to quit before destroy instance.
    /**Called by director, please do not called outside.*/
    void waitForQuit();

    /**
     * Get the file path of the texture
     *
     * @param texture A Texture2D object pointer.
     *
     * @return The full path of the file.
     */
    std::string getTextureFilePath(Texture2D* texture) const;

    /** Reload texture from a new file.
     * This function is mainly for editor, won't suggest use it in game for performance reason.
     *
     * @param srcName Original texture file name.
     * @param dstName New texture file name.
     *
     * @since v3.10
     */
    void renameTextureWithKey(std::string_view srcName, std::string_view dstName);

private:
    void addImageAsyncCallBack(float dt);
    void loadImage();
    void parseNinePatchImage(Image* image, Texture2D* texture, std::string_view path);

public:
protected:
    struct AsyncStruct;

    std::thread* _loadingThread;

    std::deque<AsyncStruct*> _asyncStructQueue;
    std::deque<AsyncStruct*> _requestQueue;
    std::deque<AsyncStruct*> _responseQueue;

    std::mutex _requestMutex;
    std::mutex _responseMutex;

    std::condition_variable _sleepCondition;

    bool _needQuit;

    int _asyncRefCount;

    hlookup::string_map<Texture2D*> _textures;

    static std::string s_etc1AlphaFileSuffix;
};

#if CC_ENABLE_CACHE_TEXTURE_DATA

class VolatileTexture
{
    typedef enum
    {
        kInvalid = 0,
        kImageFile,
        kImageData,
        kString,
        kImage,
    } ccCachedImageType;

private:
    VolatileTexture(Texture2D* t);
    /**
     * @js NA
     * @lua NA
     */
    ~VolatileTexture();

protected:
    friend class VolatileTextureMgr;
    Texture2D* _texture;

    Image* _uiImage;

    ccCachedImageType _cashedImageType;

    void* _textureData;
    int _dataLen;
    Vec2 _textureSize;
    backend::PixelFormat _pixelFormat;

    std::string _fileName;

    std::string _text;
    FontDefinition _fontDefinition;
};

class CC_DLL VolatileTextureMgr
{
public:
    static void addImageTexture(Texture2D* tt, std::string_view imageFileName);
    static void addStringTexture(Texture2D* tt, const char* text, const FontDefinition& fontDefinition);
    static void addDataTexture(Texture2D* tt,
                               void* data,
                               int dataLen,
                               backend::PixelFormat pixelFormat,
                               const Vec2& contentSize);
    static void addImage(Texture2D* tt, Image* image);
    static void removeTexture(Texture2D* t);
    static void reloadAllTextures();

public:
    static std::list<VolatileTexture*> _textures;
    static bool _isReloading;

    // find VolatileTexture by Texture2D*
    // if not found, create a new one
    static VolatileTexture* findVolotileTexture(Texture2D* tt);

private:
    static void reloadTexture(Texture2D* texture, std::string_view filename, backend::PixelFormat pixelFormat);
};

#endif

// end of textures group
/// @}

NS_CC_END

#endif  //__CCTEXTURE_CACHE_H__
