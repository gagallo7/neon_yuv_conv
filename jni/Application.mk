APP_ABI := all # Define the target architecture to be ARM.
APP_STL := c++_static
#APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -fexceptions    # This is the place you enable exception.
APP_PLATFORM = android-22
APP_OPTIM = debug
