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

void draw_line(SkCanvas *canvas)
{
	SkPaint p;

	p.setColor(SK_ColorRED);
	p.setAntiAlias(true);
	p.setStyle(SkPaint::kStroke_Style);
	p.setStrokeWidth(10);

	canvas->drawLine(20, 20, 100, 100, p);
}

void draw_square(SkCanvas *canvas)
{
	SkPaint paint;
	paint.setColor(SK_ColorBLUE);
	canvas->drawRect({0, 0, 250, 250}, paint);
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
	glfwWindowHint(GLFW_REFRESH_RATE, 60);

	GLFWwindow *window = glfwCreateWindow(kWidth, kHeight, "CMake GLFW Project", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Setup Skia OpenGL context
	sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
	sk_sp<GrDirectContext> context = GrDirectContexts::MakeGL(interface);

	// Create OpenGL framebuffer target
	auto target = GrBackendRenderTargets::MakeGL(
		kWidth, kHeight,
		0, // sample count
		0, // stencil bits
		(GrGLFramebufferInfo){
			.fFBOID = 0,
			.fFormat = GL_RGBA8,
		});

	sk_sp<SkSurface> surface = SkSurfaces::WrapBackendRenderTarget(
		context.get(),
		target,
		GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
		SkColorType::kRGBA_8888_SkColorType, nullptr, nullptr);

	SkCanvas *canvas = surface->getCanvas();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		canvas->clear(SK_ColorWHITE);

		draw_square(surface->getCanvas());
		draw_line(surface->getCanvas());

		context->flushAndSubmit();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
