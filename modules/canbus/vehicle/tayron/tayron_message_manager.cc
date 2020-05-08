/* Copyright 2018 The Apollo Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "modules/canbus/vehicle/tayron/tayron_message_manager.h"

#include "modules/canbus/vehicle/tayron/protocol/brake_cmd_214.h"
#include "modules/canbus/vehicle/tayron/protocol/gas_cmd_216.h"
#include "modules/canbus/vehicle/tayron/protocol/shift_cmd_217.h"
#include "modules/canbus/vehicle/tayron/protocol/steering_cmd_215.h"

#include "modules/canbus/vehicle/tayron/protocol/brake_report_321.h"
#include "modules/canbus/vehicle/tayron/protocol/gas_report_323.h"
#include "modules/canbus/vehicle/tayron/protocol/mmotor_1_280.h"
#include "modules/canbus/vehicle/tayron/protocol/shift_report_324.h"
#include "modules/canbus/vehicle/tayron/protocol/steering_report_322.h"
#include "modules/canbus/vehicle/tayron/protocol/wheel_speed_4a0.h"
#include "modules/canbus/vehicle/tayron/protocol/brake_pressure_6AB.h"
namespace apollo {
namespace canbus {
namespace tayron {

TayronMessageManager::TayronMessageManager() {
  // Control Messages
  AddSendProtocolData<Brakecmd214, true>();
  AddSendProtocolData<Gascmd216, true>();
  AddSendProtocolData<Shiftcmd217, true>();
  AddSendProtocolData<Steeringcmd215, true>();

  // Report Messages
  AddRecvProtocolData<Brakereport321, true>();
  AddRecvProtocolData<Gasreport323, true>();
  AddRecvProtocolData<Mmotor1280, true>();
  AddRecvProtocolData<Shiftreport324, true>();
  AddRecvProtocolData<Steeringreport322, true>();
  AddRecvProtocolData<Wheelspeed4a0, true>();
  AddRecvProtocolData<Brakepressure6AB, true>();
}

TayronMessageManager::~TayronMessageManager() {}

}  // namespace tayron
}  // namespace canbus
}  // namespace apollo
