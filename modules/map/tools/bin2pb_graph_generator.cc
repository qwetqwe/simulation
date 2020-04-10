/* Copyright 2017 The Apollo Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
=========================================================================*/

#include "gflags/gflags.h"

#include "cyber/common/file.h"
#include "cyber/common/log.h"
#include "modules/map/hdmap/adapter/opendrive_adapter.h"
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/map/proto/map.pb.h"
#include "modules/routing/proto/topo_graph.pb.h"
/**
 * A map tool to transform .txt map to .bin map
 */

DEFINE_string(output_dir, "/tmp", "output map directory");
DEFINE_string(map_file, "routing_map", "input or output map name");
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  google::ParseCommandLineFlags(&argc, &argv, true);

  const auto map_filename = FLAGS_map_file;
  apollo::routing::Graph pb_map;
  CHECK(apollo::cyber::common::GetProtoFromBinaryFile(map_filename,&pb_map));
  const std::string output_pb_file = FLAGS_output_dir + "/routing_map.txt";
  CHECK(apollo::cyber::common::SetProtoToASCIIFile(pb_map,output_pb_file));
 
  pb_map.Clear();
  CHECK(apollo::cyber::common::GetProtoFromASCIIFile(output_pb_file, &pb_map));

  AINFO << "transform map into .bin map success";

  return 0;
}
