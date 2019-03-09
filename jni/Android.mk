LOCAL_PATH:= $(call my-dir) # Get the local path of the project.
include $(CLEAR_VARS) # Clear all the variables with a prefix "LOCAL_"

LOCAL_SRC_FILES:= yv12_nv21.cpp # Indicate the source code.
LOCAL_MODULE:= yv12_nv21 # The name of the binary.
LOCAL_ARM_MODE := arm
LOCAL_CFLAGS += -g

include $(BUILD_EXECUTABLE) # Tell ndk-build that we want to build a native executable.
