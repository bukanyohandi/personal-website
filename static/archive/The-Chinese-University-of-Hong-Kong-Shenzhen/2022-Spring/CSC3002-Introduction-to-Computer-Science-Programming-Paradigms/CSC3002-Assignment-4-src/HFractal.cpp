/*
 * File: HFractal.cpp
 * ------------------
 * This program draws an H-fractal on the graphics window.int main() {
 */

#include "HFractal.h"

const int dx[] = {-1, -1, 1, 1};
const int dy[] = {-1, 1, -1, 1};

void drawHFractal(GWindow &gw, double x, double y, double size, int order){
    if(order < 0) return;

    int half_size = size / 2;

    gw.setColor("Black");
    gw.drawLine(x - half_size, y - half_size, x - half_size, y + half_size);
    gw.drawLine(x + half_size, y - half_size, x + half_size, y + half_size);
    gw.drawLine(x - half_size, y            , x + half_size, y            );

    for(int idx = 0; idx < 4; ++idx)
        drawHFractal(gw, x + dx[idx] * half_size, y + dy[idx] * half_size, half_size, order - 1);

    return;
}
