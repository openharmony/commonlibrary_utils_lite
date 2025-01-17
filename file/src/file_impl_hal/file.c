/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utils_file.h"
#include <securec.h>
#include "hal_file.h"
#include "ohos_errno.h"
#include "ohos_types.h"

#include <stdbool.h>

#define BUFFER_SIZE 128

int UtilsFileOpen(const char* path, int oflag, int mode)
{
    return HalFileOpen(path, oflag, mode);
}

int UtilsFileClose(int fd)
{
    return HalFileClose(fd);
}

int UtilsFileRead(int fd, char* buf, unsigned int len)
{
    return HalFileRead(fd, buf, len);
}

int UtilsFileWrite(int fd, const char* buf, unsigned int len)
{
    return HalFileWrite(fd, buf, len);
}

int UtilsFileDelete(const char* path)
{
    return HalFileDelete(path);
}

int UtilsFileStat(const char* path, unsigned int* fileSize)
{
    return HalFileStat(path, fileSize);
}

int UtilsFileSeek(int fd, int offset, unsigned int whence)
{
    return HalFileSeek(fd, offset, whence);
}

int UtilsFileCopy(const char* src, const char* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return EC_FAILURE;
    }
    int fpSrc = UtilsFileOpen(src, O_RDONLY_FS, 0);
    if (fpSrc < 0) {
        return fpSrc;
    }
    int fpDest = UtilsFileOpen(dest, O_RDWR_FS | O_CREAT_FS | O_TRUNC_FS, 0);
    if (fpDest < 0) {
        UtilsFileClose(fpSrc);
        return fpDest;
    }
    bool copyFailed = true;
    int nLen;
    char* dataBuf = (char *)malloc(BUFFER_SIZE);
    if (dataBuf == NULL) {
        goto MALLOC_ERROR;
    }
    nLen = UtilsFileRead(fpSrc, dataBuf, BUFFER_SIZE);
    while (nLen > 0) {
        if (UtilsFileWrite(fpDest, dataBuf, nLen) != nLen) {
            goto EXIT;
        }
        nLen = UtilsFileRead(fpSrc, dataBuf, BUFFER_SIZE);
    }
    copyFailed = (nLen < 0);

EXIT:
    free(dataBuf);
MALLOC_ERROR:
    UtilsFileClose(fpSrc);
    UtilsFileClose(fpDest);
    if (copyFailed) {
        UtilsFileDelete(dest);
        return EC_FAILURE;
    }
    return EC_SUCCESS;
}

int UtilsFileMove(const char* src, const char* dest)
{
    int ret = UtilsFileCopy(src, dest);
    if (ret == EC_SUCCESS) {
        ret = UtilsFileDelete(src);
    }
    return ret;
}
