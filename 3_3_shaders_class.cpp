#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glcorearb.h>
#include <gl/wglext.h>
#include <math.h>
#include <stdio.h>

#include "common/gl_init.hpp"
#include "common/program.hpp"

constexpr unsigned int kScreenWidth = 800;
constexpr unsigned int kScreenHeight = 600;

unsigned int vao;
unsigned int program;
HDC hdc;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
                   LPSTR /*lpCmdLine*/, int nShowCmd) {
  // Register window class
  static TCHAR wndclass_name[] = TEXT("LEARNOPENGL_CLASS");
  WNDCLASS wndclass;
  memset(&wndclass, 0, sizeof(wndclass));
  wndclass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WindowProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(/*hInstance=*/NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(/*hInstance=*/NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = wndclass_name;

  if (!RegisterClass(&wndclass)) {
    MessageBox(/*hWnd=*/NULL,
               TEXT("This program requires a newer version of Windows"),
               TEXT("learnopengl_win32"), MB_ICONERROR);
    return 1;
  }

  // Create window
  HWND hwnd = CreateWindow(wndclass_name, TEXT("LearnOpenGL Win32"),
                           /*dwStyle=*/WS_OVERLAPPEDWINDOW, /*x=*/CW_USEDEFAULT,
                           /*y=*/CW_USEDEFAULT, /*nWidth=*/kScreenWidth,
                           /*nHeight=*/kScreenHeight, /*hWndParent=*/NULL,
                           /*hMenu=*/NULL, hInstance, /*lpParam=*/NULL);

  // Create context
  hdc = GetDC(hwnd);
  PIXELFORMATDESCRIPTOR descriptor;
  memset(&descriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
  descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  descriptor.nVersion = 1;
  descriptor.dwFlags =
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  descriptor.iPixelType = PFD_TYPE_RGBA;
  descriptor.cColorBits = 32;
  descriptor.cAlphaBits = 8;
  descriptor.cDepthBits = 24;

  int pixel_format = ChoosePixelFormat(hdc, &descriptor);
  if (!pixel_format) {
    MessageBox(/*hWnd=*/NULL, TEXT("Can not create render context"),
               TEXT("learnopengl_win32"), MB_ICONERROR);
    return 1;
  }

  if (!SetPixelFormat(hdc, pixel_format, &descriptor)) {
    MessageBox(/*hWnd=*/NULL, TEXT("Can not set pixel format"),
               TEXT("learnopengl_win32"), MB_ICONERROR);
    return 1;
  }
  HGLRC temp_context = wglCreateContext(hdc);
  wglMakeCurrent(hdc, temp_context);

  // Initialize OpenGL extension procs.
  InitGlFunctions();

  // Init OpenGL 4.5 core context.
  int gl_attribs[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB,
      4,
      WGL_CONTEXT_MINOR_VERSION_ARB,
      5,
      WGL_CONTEXT_PROFILE_MASK_ARB,
      WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0,
  };
  const HGLRC new_context = wglCreateContextAttribsArb(hdc, NULL, gl_attribs);
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(temp_context);
  wglMakeCurrent(hdc, new_context);

  // Program
  program = InitPipeline("assets/shaders/3_3_shaders_class.vs",
                         "assets/shaders/3_3_shaders_class.fs");
  if (!program) {
    MessageBox(/*hWnd=*/NULL, TEXT("Could not init program"),
               TEXT("learnopengl_win32"), MB_ICONERROR);
    return 1;
  }

  // Set up vertex data (and buffers) and configure vertex attributes.
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  float vertices[] = {
      // positions        // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top

  };
  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  ShowWindow(hwnd, nShowCmd);
  UpdateWindow(hwnd);

  MSG msg;
  while (GetMessage(&msg, /*hWnd=*/NULL, /*wMsgFilterMin=*/0,
                    /*wMsgFilterMax=*/0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  PAINTSTRUCT ps;

  switch (uMsg) {
    case WM_SIZE:
      // Make sure the viewport matches the new window dimensions.
      glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
      PostMessage(hwnd, WM_PAINT, 0, 0);
    case WM_PAINT: {
      // Render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw our first triangle
      glUseProgram(program);
      glBindVertexArray(vao);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      SwapBuffers(hdc);

      BeginPaint(hwnd, &ps);
      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_KEYDOWN:
      // Process Input
      switch (wParam) {
        case VK_ESCAPE:
          PostQuitMessage(0);
          return 0;
      }
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}