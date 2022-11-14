/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/*
 * @addtogroup Filesystem
 * @{
 *
 * @brief 提供文件操作基本能力
 */

/*
 * @file fs.h
 *
 * @brief 文件系统对外接口和数据结构
 */

#ifndef FS_H
#define FS_H

#include "fcntl.h"
#include "stdint.h"
#include "sys/mount.h"
#include "sys/stat.h"
#include "sys/statfs.h"
#include "unistd.h"
#include "dirent.h"
#include "errno.h"
#include "stdio.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/*
 * @brief 获取分区剩余空间大小.

 * @param path 分区路径.
 * @param totalSize 分区总空间.
 * @param freeSize 分区剩余可用空间.
 * @return 返回FR_OK表示成功，否则返回失败错误码.
*/
int32_t FS_GetPartitionSize(const char *path, uint32_t *totalSize, uint32_t *freeSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif /* End of #ifndef FS_H */
/** @} */