/****************************************************************************
Copyright (c) 2011      Laschweinski
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

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
#ifndef __AX_FILEUTILS_EMSCRIPTEN_H__
#define __AX_FILEUTILS_EMSCRIPTEN_H__

#include "platform/PlatformConfig.h"
#if AX_TARGET_PLATFORM == AX_PLATFORM_EMSCRIPTEN

#include "platform/FileUtils.h"
#include "platform/PlatformMacros.h"
#include "base/Types.h"
#include <string>
#include <vector>

NS_AX_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class AX_DLL FileUtilsEmscripten : public FileUtils
{
    friend class FileUtils;
protected:
    FileUtilsEmscripten();
public:
    /* override functions */
    bool init() override;
    virtual std::string getWritablePath() const override;
    std::string getNativeWritableAbsolutePath() const override;
private:
    virtual bool isFileExistInternal(std::string_view path) const override;
};

// end of platform group
/// @}

NS_AX_END

#endif // AX_TARGET_PLATFORM == AX_PLATFORM_EMSCRIPTEN

#endif    // __AX_FILEUTILS_EMSCRIPTEN_H__
