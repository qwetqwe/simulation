load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "daoyuan_message_manager",
    srcs = ["daoyuan_message_manager.cc"],
    hdrs = ["daoyuan_message_manager.h"],
    deps = [
        "//modules/common/util:message_util",
        "//modules/drivers/canbus/can_client:can_client_factory",
        "//modules/drivers/canbus/can_comm:message_manager_base",
        "//modules/drivers/daoyuan/protocol:daoyuan_protocol",
        "//modules/drivers/daoyuan/proto:daoyuan_proto"
    ],
)

cc_library(
    name = "daoyuan_canbus_lib",
    srcs = ["daoyuan_canbus_component.cc"],
    hdrs = ["daoyuan_canbus_component.h"],
    copts = ['-DMODULE_NAME=\\"daoyuan\\"'],
    deps = [
        ":daoyuan_message_manager",
        "//cyber",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/monitor_log",
        "//modules/drivers/canbus/can_client:can_client_factory",
        "//modules/drivers/canbus/can_comm:can_receiver",
        "//modules/drivers/canbus/can_comm:message_manager_base",
        "//modules/drivers/daoyuan/protocol:daoyuan_protocol",
        "//modules/localization/proto:localization_proto",
        "//modules/localization/proto:pose_proto",
        "//modules/drivers/daoyuan/proto:daoyuan_proto",
        "//modules/common/math:math",
        "//modules/transform:transform_broadcaster_lib",
        "@eigen",
        "@proj4",
    ],
)

cc_binary(
    name = "libdaoyuan.so",
    linkopts = ["-shared"],
    linkstatic = False,
    deps = [":daoyuan_canbus_lib"],
)

cpplint()
