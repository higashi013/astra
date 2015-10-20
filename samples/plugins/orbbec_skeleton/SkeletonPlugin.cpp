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
#include "SkeletonPlugin.h"
#include <astra_core/Astra.h>

EXPORT_PLUGIN(astra::plugins::skeleton::SkeletonPlugin);

namespace astra { namespace plugins { namespace skeleton {

    void SkeletonPlugin::on_stream_added(astra_streamset_t setHandle,
                                         astra_stream_t streamHandle,
                                         astra_stream_desc_t desc)
    {
        if (desc.type != ASTRA_STREAM_DEPTH)
            return; // if new stream is not depth, we don't care.

        m_skeletonTrackers.push_back(std::make_unique<SkeletonTracker>(get_pluginService(),
                                                                     setHandle,
                                                                     streamHandle));
    }

    void SkeletonPlugin::on_stream_removed(astra_streamset_t setHandle,
                                           astra_stream_t streamHandle,
                                           astra_stream_desc_t desc)
    {
        auto it = std::find_if(m_skeletonTrackers.cbegin(),
                               m_skeletonTrackers.cend(),
                               [&streamHandle] (const SkeletonTrackerPtr& trackerPtr)
                               {
                                   return trackerPtr->sourceStream() == streamHandle;
                               });

        if (it != m_skeletonTrackers.cend())
        {
            m_skeletonTrackers.erase(it);
        }
    }

}}}
