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
#ifndef ASTRA_STREAMSET_HPP
#define ASTRA_STREAMSET_HPP

#include <string>
#include "capi/astra_core.h"
#include "astra_stream_reader.hpp"
#include <stdexcept>

namespace astra {

    class streamset
    {
    public:
        streamset(std::string uri)
        {
            astra_streamsetconnection_t streamSetConnection;
            astra_streamset_open(uri.c_str(), &streamSetConnection);
            sensorRef_ = std::make_shared<streamset_ref>(streamSetConnection);
        }

        streamset(const astra_streamsetconnection_t& streamSetHandle)
        {
            if (streamSetHandle == nullptr)
            {
                throw std::invalid_argument("streamSetHandle must not be null");
            }
            sensorRef_ = std::make_shared<streamset_ref>(streamSetHandle);
        }

        streamset()
            : streamset("device/default")
        {}

        bool is_valid() { return sensorRef_ != nullptr; }

        inline stream_reader create_reader();
        astra_streamsetconnection_t get_handle() const { return sensorRef_->get_connection(); }

    private:
        std::string uri_;

        class streamset_ref;
        using streamset_ref_ptr = std::shared_ptr<streamset_ref>;

        class streamset_ref :
            public std::enable_shared_from_this<streamset_ref>
        {
        public:
            streamset_ref(astra_streamsetconnection_t connection)
                :  connection_(connection)
            { }

            ~streamset_ref()
            {
                astra_streamset_close(&connection_);
            }

            astra_streamsetconnection_t get_connection() const { return connection_; }

        private:
            astra_streamsetconnection_t connection_;
        };

        streamset_ref_ptr sensorRef_;

        friend bool operator==(const streamset& lhs, const streamset& rhs);
        friend bool operator!=(const streamset& lhs, const streamset& rhs);
    };

    inline bool operator==(const streamset& lhs, const streamset& rhs)
    {
        return lhs.sensorRef_ == rhs.sensorRef_;
    }

    inline bool operator!=(const streamset& lhs, const streamset& rhs)
    {
        return !(lhs == rhs);
    }

    stream_reader streamset::create_reader()
    {
        astra_reader_t reader;
        astra_reader_create(get_handle(), &reader);

        return stream_reader(reader);
    }
}

#endif // ASTRA_STREAMSET_HPP
