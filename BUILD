package(default_visibility = ["//visibility:public"])

load("@avr_tools//tools/avr:hex.bzl", "hex", "eeprom", "listing")
load("@utils//:unity_runner_generator.bzl", "cmock_generate")
load("@utils//:custom_macro.bzl", "custom_cc_library")
load("@utils//:custom_macro.bzl", "custom_cc_library_mock")
load("@utils//:unity_runner_generator.bzl", "unity_runner")
load("@utils//:unity_runner_generator.bzl", "UNITY_COPTS")
load("@utils//:unity_runner_generator.bzl", "UNITY_DEPS")

config_setting(
    name = "avr",
    values = {
        "cpu": "avr",
    },
)

################################################################################
## 
## Library: ds1620
## 
################################################################################

LIBRARY_NAME = "ds1620"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    "ds1620_read",
    "ds1620_receive_data",
    "ds1620_reset",
    "ds1620_send_command",
    "ds1620_send_data",
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_ds1620_read",
    "mock_ds1620_receive_data",
    "mock_ds1620_reset",
    "mock_ds1620_send_command",
    "mock_ds1620_send_data",
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = [],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: ds1620_read
## 
################################################################################

LIBRARY_NAME = "ds1620_read"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    "ds1620_receive_data",
    "ds1620_reset",
    "ds1620_send_command",
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_ds1620_receive_data",
    "mock_ds1620_reset",
    "mock_ds1620_send_command",
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = ["ds1620_header"],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: ds1620_receive_data
## 
################################################################################

LIBRARY_NAME = "ds1620_receive_data"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = ["ds1620_header"],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: ds1620_reset
## 
################################################################################

LIBRARY_NAME = "ds1620_reset"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = ["ds1620_header"],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: ds1620_send_command
## 
################################################################################

LIBRARY_NAME = "ds1620_send_command"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = [
    "mock_example_ds1620",
    ]

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = ["ds1620_header"],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: ds1620_send_data
## 
################################################################################

LIBRARY_NAME = "ds1620_send_data"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = [
    "mock_example_ds1620",
    ]
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

custom_cc_library(
    name = LIBRARY_NAME,
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_DEPS,
    visibility = LIBRARY_VISIBILITY,
)

custom_cc_library(
    name = LIBRARY_NAME+"_for_mocking",
    srcs = ["src/"+LIBRARY_NAME+".c","inc/"+LIBRARY_NAME+".h","ds1620_header"],
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_TEST_UNITY_DEPS,
    testonly = True,
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = ["ds1620_header"],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)

LIBRARY_TEST_UNITY_MAIN_SOURCE = "test_"+LIBRARY_NAME+".c"

unity_runner(
    name = "runner_"+LIBRARY_NAME+"_test",
    src = "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
)

cc_test(
    name = LIBRARY_NAME+"_unity_test",
    srcs = [
        "test/"+LIBRARY_TEST_UNITY_MAIN_SOURCE,
        "runner_"+LIBRARY_NAME+"_test.c",
    ],
    copts = UNITY_COPTS,
    size = LIBRARY_TEST_UNITY_SIZE,
    deps = [
        ":"+LIBRARY_NAME+"_for_mocking",
    ] + UNITY_DEPS + LIBRARY_TEST_UNITY_DEPS,
)

################################################################################
## 
## Library: example_ds1620
## 
################################################################################

LIBRARY_NAME = "example_ds1620"
LIBRARY_VISIBILITY = ["//visibility:public"]
LIBRARY_DEPS = [
    ]

LIBRARY_TEST_UNITY_SIZE = "small"
LIBRARY_TEST_UNITY_DEPS = []
LIBRARY_CMOCK_DEPS = []

filegroup(
    name = LIBRARY_NAME+"_header",
    srcs = ["inc/"+LIBRARY_NAME+".h"],
)

cmock_generate(
    prefix = LIBRARY_NAME,
    src = ":"+LIBRARY_NAME+"_header",
)

custom_cc_library_mock(
    srcs = [],
    name = LIBRARY_NAME,
    hdr = LIBRARY_NAME+"_header",
    deps = LIBRARY_CMOCK_DEPS,
    visibility = LIBRARY_VISIBILITY,
    testonly = True,
)
