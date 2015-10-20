// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#include <astra_core/capi/astra_defines.h>
#include <astra_core/capi/astra_types.h>
#include <astra/capi/streams/skeleton_types.h>
#include "astra_generic_stream_api.hpp"
#include <memory.h>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/stream_types.h>
#include <string.h>


ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_reader_get_skeletonstream(astra_reader_t reader,
                                                                     astra_skeletonstream_t* skeletonStream)

{
    return astra_reader_get_stream(reader,
                                      ASTRA_STREAM_SKELETON,
                                      DEFAULT_SUBTYPE,
                                      skeletonStream);
}

ASTRA_API_EX astra_status_t astra_frame_get_skeletonframe(astra_reader_frame_t readerFrame,
                                                                   astra_skeletonframe_t* skeletonFrame)
{
    return astra_generic_frame_get<astra_skeletonframe_wrapper_t>(readerFrame,
                                                                        ASTRA_STREAM_SKELETON,
                                                                        DEFAULT_SUBTYPE,
                                                                        skeletonFrame);
}

ASTRA_API_EX astra_status_t astra_skeletonframe_get_frameindex(astra_skeletonframe_t skeletonFrame,
                                                                        astra_frame_index_t* index)
{
    return astra_generic_frame_get_frameindex(skeletonFrame, index);
}

ASTRA_API_EX astra_status_t astra_skeletonframe_get_skeleton_count(astra_skeletonframe_t skeletonFrame,
                                                                            size_t* skeletonCount)
{
    *skeletonCount = skeletonFrame->skeletonCount;

    return ASTRA_STATUS_SUCCESS;
}

ASTRA_API_EX astra_status_t astra_skeletonframe_copy_skeletons(astra_skeletonframe_t skeletonFrame,
                                                                        astra_skeleton_t* skeletonsDestination)
{
    size_t size = skeletonFrame->skeletonCount * sizeof(astra_skeleton_t);

    memcpy(skeletonsDestination, skeletonFrame->skeletons, size);

    return ASTRA_STATUS_SUCCESS;
}

ASTRA_API_EX astra_status_t astra_skeletonframe_get_skeletons_ptr(astra_skeletonframe_t skeletonFrame,
                                                                           astra_skeleton_t** skeletons,
                                                                           size_t* skeletonCount)
{
    *skeletons = skeletonFrame->skeletons;
    astra_skeletonframe_get_skeleton_count(skeletonFrame, skeletonCount);

    return ASTRA_STATUS_SUCCESS;
}
ASTRA_END_DECLS
