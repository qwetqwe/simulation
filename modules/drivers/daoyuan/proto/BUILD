package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "daoyuan_proto",
    deps = [
        ":daoyuan_proto_lib",
    ],
)

proto_library(
    name = "daoyuan_proto_lib",
    srcs = ["daoyuan_conf.proto",
            "daoyuan.proto"],
    deps = [
        "//modules/drivers/canbus/proto:canbus_proto_lib",
    ],
)
