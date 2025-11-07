#include <iostream>

#include <GLFW/glfw3.h>

#include "skia/include/gpu/ganesh/GrBackendSurface.h"
#include "skia/include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "skia/include/gpu/ganesh/gl/GrGLBackendSurface.h"

#include "skia/include/core/SkPaint.h"
#include "skia/include/core/SkCanvas.h"
#include "skia/include/core/SkColorSpace.h"

#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"

#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkStream.h"
#include "include/core/SkSurface.h"

const int kWidth = 500;
const int kHeight = 500;

struct skia_data
{
	sk_sp<GrDirectContext> context;
	sk_sp<SkSurface> surface;
};

static struct skia_data make_surface(int width, int height)
{
	sk_sp<const GrGLInterface> interface = nullptr;
	sk_sp<GrDirectContext> context = GrDirectContexts::MakeGL(interface);

	GrGLFramebufferInfo framebufferInfo{
		.fFBOID = 0,
		.fFormat = GL_RGBA8,
	};

	SkColorType colorType = SkColorType::kRGBA_8888_SkColorType;
	GrBackendRenderTarget backendRenderTarget = GrBackendRenderTargets::MakeGL(width, height,
																			   0, // sample count
																			   0, // stencil bits
																			   framebufferInfo);

	sk_sp<SkSurface> surface = SkSurfaces::WrapBackendRenderTarget(
		context.get(),
		backendRenderTarget,
		GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
		colorType, nullptr, nullptr);

	return {context, surface};
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int, char **)
{
	if (!glfwInit())
	{
		std::cerr << "Something wrong happened" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(kWidth, kHeight, "LearnOpenGL", NULL, NULL);

	if (!window)
	{
		std::cerr << "Something wrong happened" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	struct skia_data skia_data = make_surface(kWidth, kHeight);
	SkCanvas *canvas = skia_data.surface->getCanvas();

	while (!glfwWindowShouldClose(window))
	{
		glfwWaitEvents();

		SkPaint paint;
		paint.setColor(SK_ColorWHITE);
		canvas->drawPaint(paint);
		paint.setColor(SK_ColorBLUE);
		canvas->drawRect({0, 0, 250, 250}, paint);
		skia_data.context->flush();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
