#include "../SDK/Vector.h"
#include "../SDK/Color.h"
#include "../Interfaces.h"

bool ScreenTransform(const Vector& point, Vector& screen);
void Line(int x, int y, int x2, int y2, Color color);
bool WorldToScreen(const Vector& origin, Vector& screen);
void text2(int x, int y, const char* _Input, int font, Color color);