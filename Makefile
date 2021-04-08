BUILD_DIR=".\\build\\"
SRC_DIR=..
LINK_LIBS=User32.lib Gdi32.lib Opengl32.lib

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

build_dir:
	-@ if NOT EXIST $(BUILD_DIR) mkdir $(BUILD_DIR)

clean:
	rmdir /S /Q $(BUILD_DIR)