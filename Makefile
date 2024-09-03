ASSETS_DIR=".\\build\\assets\\"
LIB_BUILD_DIR=".\\build\\lib\\"
BUILD_DIR=".\\build\\"
SRC_DIR=..
LINK_LIBS=User32.lib Gdi32.lib Opengl32.lib
INCLUDE_CMD=/I ..\common
COMMON_OBJ=.\lib\gl_init.obj .\lib\program.obj

all: 1_1 2_1 2_2 3_1

1_1: build_dir
	pushd $(BUILD_DIR) && \
	cl.exe $(SRC_DIR)\1_1_hello_window.cc /link $(LINK_LIBS) && \
	popd

2_1: build_dir
	pushd $(BUILD_DIR) && \
	cl.exe $(SRC_DIR)\2_1_hello_triangle.cc /link $(LINK_LIBS) && \
	popd

2_2: build_dir
	pushd $(BUILD_DIR) && \
	cl.exe $(SRC_DIR)\2_2_hello_triangle_indexed.cc /link $(LINK_LIBS) && \
	popd

3_1: build_dir
	pushd $(BUILD_DIR) && \
	cl.exe $(SRC_DIR)\3_1_shaders_uniform.cc /link $(LINK_LIBS) && \
	popd

3_2: build_dir
	pushd $(BUILD_DIR) && \
	cl.exe $(SRC_DIR)\3_2_shaders_interpolation.cc /link $(LINK_LIBS) && \
	popd

3_3: build_dir common
	pushd $(BUILD_DIR) && \
	cl.exe /Wall $(SRC_DIR)\3_3_shaders_class.cpp $(COMMON_OBJ) /link $(LINK_LIBS) && \
	popd

build_dir:
	-@ if NOT EXIST $(BUILD_DIR) mkdir $(BUILD_DIR)

lib_build_dir: build_dir
	-@ if NOT EXIST $(LIB_BUILD_DIR) mkdir $(LIB_BUILD_DIR)

assets_dir: build_dir
	-@ if NOT EXIST $(ASSETS_DIR) mkdir $(ASSETS_DIR)

assets: assets_dir
  pushd $(BUILD_DIR) && \
	xcopy /E /I ..\assets .\assets && \
	popd

common: common_gl_init common_program

common_program: lib_build_dir
	pushd $(LIB_BUILD_DIR) && \
	cl.exe /c /Fo .\lib\program.obj ..\..\common\program.cpp /link $(LINK_LIBS) && \
	popd

common_gl_init: lib_build_dir
	pushd $(LIB_BUILD_DIR) && \
	cl.exe /c /Fo .\lib\gl_init.obj ..\..\common\gl_init.cpp /link $(LINK_LIBS) && \
	popd

clean:
	rmdir /S /Q $(BUILD_DIR)