load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "tl_preprocess_proto",
    deps = [
        ":tl_preprocess_proto_lib",
    ],
)

proto_library(
    name = "tl_preprocess_proto_lib",
    srcs = ["tl_preprocess.proto"],
)

cc_library(
    name = "multi_camera_projection",
    srcs = ["multi_camera_projection.cc"],
    copts = [
        '-DMODULE_NAME=\\"perception\\"',
    ],
    hdrs = ["multi_camera_projection.h"],
    deps = [
        ":pose",
        "//cyber",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/common/io:io_util",
        "//modules/perception/common/sensor_manager",
    ],
)

cc_library(
    name = "pose",
    srcs = ["pose.cc"],
    copts = [
        '-DMODULE_NAME=\\"perception\\"',
    ],
    hdrs = ["pose.h"],
    deps = [
        "//cyber",
        "//modules/perception/base",
    ],
)

cc_library(
    name = "tl_preprocessor",
    srcs = ["tl_preprocessor.cc"],
    copts = [
        '-DMODULE_NAME=\\"perception\\"',
    ],
    hdrs = ["tl_preprocessor.h"],
    deps = [
        ":multi_camera_projection",
        "//cyber",
        "//external:gflags",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/camera/lib/interface",
        "//modules/perception/camera/lib/interface:base_init_options",
        "//modules/perception/lib/config_manager",
        "//modules/perception/lib/utils",
        "@boost",
        "@eigen",
    ],
)

cpplint()
