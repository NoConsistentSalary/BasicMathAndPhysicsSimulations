#include <stdio.h>
#include <mikroplot/window.h>

int main() {
	mikroplot::Window window(800, 800, "Hello window!");
	while (false == window.shouldClose()) {
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
		window.drawCircle({ 0,0 }, 3.0f);
		window.update();
	}
	return 0;
}