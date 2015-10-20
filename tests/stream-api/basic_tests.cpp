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
#include "catch.hpp"
#include <astra/astra.hpp>

TEST_CASE("Can create a StreamSet with default ctor", "[c++-stream-api]") {
    astra::streamset streamset;
    REQUIRE(streamset.is_valid());
}

TEST_CASE("Can create a reader from a streamset", "[c++-stream-api]") {
    astra::streamset streamset;
    astra::stream_reader reader = streamset.create_reader();
    REQUIRE(reader.is_valid());
}


TEST_CASE("Can start depth stream", "[c++-stream-api]") {

    astra::streamset streamset;
    astra::stream_reader reader = streamset.create_reader();
    astra::depthstream depthStream = reader.stream<astra::depthstream>();
    depthStream.start();
    float hFOV = depthStream.horizontalFieldOfView();
    float vFOV = depthStream.verticalFieldOfView();

    REQUIRE(hFOV > 0);
    REQUIRE(vFOV > 0);
}

TEST_CASE("Can start color stream", "[c++-stream-api]") {

    astra::streamset streamset;
    astra::stream_reader reader = streamset.create_reader();

    reader.stream<astra::colorstream>().start();

    float hFOV = reader.stream<astra::colorstream>().horizontalFieldOfView();
    float vFOV = reader.stream<astra::colorstream>().verticalFieldOfView();

    REQUIRE(hFOV > 0);
    REQUIRE(vFOV > 0);
}