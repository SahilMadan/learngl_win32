[LearnOpenGL](https://learnopengl.com/) implemented using win32 API.

## Headers:

The headers `GL/glcorearb.h` and `GL/wglext.h` are not included in the default Windows SDK. In turn, you will also need `KHR/khrplatform.h`.

You must get the GL files from https://github.com/KhronosGroup/OpenGL-Registry/tree/master/api/GL and the KHR file from https://www.khronos.org/registry/EGL/api/KHR place those files in the directory (for instance): `C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\um\`. 

Note that you can also place these files in another predefined directory such as `C:\Lib\include` but make sure to specify this directory in the build command using `/I $(INCLUDE_DIR)` during build.

## Make Tool:
nmake.exe is the default make tool on Windows made available through the developer command prompt.
