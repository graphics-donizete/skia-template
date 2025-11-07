#include <iostream>

#include <skia/include/core/SkPaint.h>

int main(int, char **)
{
    std::cout << "Hello, from skia_template!\n";

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setColor(SK_ColorRED);
}
