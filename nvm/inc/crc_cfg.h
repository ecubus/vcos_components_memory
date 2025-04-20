/*
 * Copyright (c) 2025 Li Auto Inc. and its affiliates
 * Licensed under the Apache License, Version 2.0(the "License");
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

#ifndef CRC_CFG_H
#define CRC_CFG_H

#ifdef __cplusplus
extern "C"
{
#endif

 #define CRC_8_Mode        (CRC_8_TABLE)       ///< CRC8 模式配置

 #define CRC_8_8H2FMode    (CRC_8H2F_TABLE)    ///< CRC8H2F 模式配置

 #define CRC_16_Mode       (CRC_16_TABLE)      ///< CRC16 模式配置

 #define CRC_16ARC_Mode    (CRC_16_ARC_TABLE)   ///< CRC16 ARC 模式配置

 #define CRC_32_Mode       (CRC_32_TABLE)      ///< CRC32 模式配置

 #define CRC_32P4_Mode     (CRC_32P4_TABLE)    ///< CRC32P4 模式配置

 #define CRC_64_Mode       (CRC_64_TABLE)      ///< CRC64 模式配置

#ifdef __cplusplus
}
#endif

#endif /* CRC_CFG_H */
