load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libvelodyne_driver_component.so",
    linkopts = ["-shared"],
    linkstatic = False,
    deps = [":velodyne_driver_component_lib"],
)

cc_library(
    name = "velodyne_driver_component_lib",
    srcs = ["velodyne_driver_component.cc"],
    hdrs = ["velodyne_driver_component.h"],
    copts = ['-DMODULE_NAME=\\"velodyne\\"'],
    deps = [
        "//cyber",
        "//modules/common/util:message_util",
        "//modules/drivers/velodyne/driver",
    ],
)

cc_library(
    name = "driver",
    srcs = [
        "driver.cc",
        "driver64.cc",
        "input.cc",
	"rsinput.cc",
        "socket_input.cc",
        "driverRS.cc",
        "rslidar_decoder.cc",
    ],
    hdrs = [
        "driver.h",
        "input.h",
        "socket_input.h",
	"rslidar_packet.h",
	"rsinput.h",
	"rslidar_decoder.h",
    ],
    copts = ['-DMODULE_NAME=\\"velodyne\\"'],
    linkopts = [
        "-lpcap",
    ],
    deps = [
        "//cyber",
        "//modules/common/util",
        "//modules/drivers/velodyne/proto:velodyne_proto",
	"//modules/drivers/proto:sensor_proto",
        "@pcl",
    ],
)

cpplint()
