/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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

#include "../Macros.h"
#include "../Types.h"
#include "../PixelBufferDescriptor.h"
#import <Metal/Metal.h>
#include <functional>

CC_BACKEND_BEGIN

class TextureBackend;

/**
 * @addtogroup _metal
 * @{
 */

/**
 * create and manager default depth and stencil attachment.
 * generate mipmaps.
 * read pixles from texture.
 */
struct UtilsMTL
{
    /*
     * init GPU texture supported formats
     */
    static void initGPUTextureFormats();

    /**
     * Update default color attachment texture.
     * @param texture Specifies the texture to be setted to the color attachemnt.
     */
    static void updateDefaultColorAttachmentTexture(id<MTLTexture> texture);
    static void resizeDefaultAttachmentTexture(std::size_t width, std::size_t height);

    /**
     * Get the default combined depth and stencil texture.
     * @return The default combined depth and stencil texture.
     */
    static id<MTLTexture> getDefaultDepthStencilTexture();

    /**
     * Convert backend::PixelFormat to MTLPixelFormat.
     * @param textureFormat Specifies a pixel format to be converted.
     * @return A MTLPixelFormat.
     */
    static MTLPixelFormat toMTLPixelFormat(PixelFormat textureFormat);

    /**
     * Generate a complete set of mipmaps in given texture.
     * @param texture Specifies a texture to generate mipmap.
     */
    static void generateMipmaps(id<MTLTexture> texture);

    /**
     * Swizzle the iamge form the given format to MTLPixelFormatRGBA8Unorm.
     * @param image Specifies the image to be swizzled.
     * @param width Specifies the width of the image.
     * @param heigth Specifies the height of the image.
     * @param format Specifies the format of the image.
     */
    static void swizzleImage(unsigned char* image, std::size_t width, std::size_t height, MTLPixelFormat format);

private:
    static id<MTLTexture> createDepthStencilAttachmentTexture();

    static id<MTLTexture> _defaultColorAttachmentTexture;
    static id<MTLTexture> _defaultDepthStencilAttachmentTexture;
};

// end of _metal group
/// @}
CC_BACKEND_END
