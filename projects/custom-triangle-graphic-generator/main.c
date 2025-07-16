#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// My function: Draw a triangle using three vertices
// (x1, y1) - First vertex (e.g. top-left corner)
// (x2, y2) - Second vertex (e.g. bottom-right corner)
// (x3, y3) - Third vertex (e.g. bottom-left corner)
// Coordinates are based on an SVG canvas with origin (0,0) at the top-left.
// x increases to the right, y increases downward.
void triangle(float x1, float y1, float x2, float y2, float x3, float y3, const char* color, bool mirror) {
    // Original triangle
    printf("<polygon points=\"%f,%f %f,%f %f,%f\" style=\"fill:%s;\" />\n",
           x1, y1, x2, y2, x3, y3, color);

    if (mirror) {
        // Mirrored triangle across vertical axis (x = 50 for 100x100 canvas)
        printf("<polygon points=\"%f,%f %f,%f %f,%f\" style=\"fill:%s;\" />\n",
               100 - x1, y1, 100 - x2, y2, 100 - x3, y3, color);
    }
}

// Other student's function: WordArt
void WordArt(int height, int width, int x, int y, char* color, char* transform, char* stroke) {
    char* ourShape =
    "<text x='%d' y='%d' font-size='35' %s fill='%s' stroke='%s'>"
    "<tspan fill='%s'> COP </tspan>"
    "<tspan fill='%s' stroke='%s'>Hello</tspan>"
    "<tspan fill='%s'> World!</tspan>"
    "</text>";
    printf(ourShape, x, y, transform, color, stroke, "black", "blue", "red", "green");
}

void beginHtmlSVG(int wide, int high, char* backColor) {
    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<svg height='%d' width='%d' style='stroke-width: 0px; background-color: %s;'>\n",
           high, wide, backColor);
}

void endHtmlSVG() {
    printf("</svg>\n");
    printf("</body>\n");
    printf("</html>\n");
}

char* getRGBColor(int red, int green, int blue) {
    static char result[100] = {0};
    sprintf(result, "rgb(%d, %d, %d)", red, green, blue);
    return result;
}

int main() {
    srand(time(NULL));

    // Create a larger canvas to accommodate both functions
    beginHtmlSVG(800, 600, getRGBColor(255, 255, 255));

    // Loop to demonstrate my triangle function with different parameters
    printf("<!-- Demonstrating triangle function with different parameters -->\n");
    for (int i = 0; i < 5; i++) {
        float x1 = 50 + i * 30;
        float y1 = 50 + i * 10;
        float x2 = x1 + 30;
        float y2 = y1 + 40;
        float x3 = x1;
        float y3 = y1 + 40;

        // Create different colors for each triangle
        int red = (i * 50) % 256;
        int green = (i * 80) % 256;
        int blue = (i * 120) % 256;

        bool shouldMirror = (i % 2 == 0); // Mirror every other triangle

        triangle(x1, y1, x2, y2, x3, y3, getRGBColor(red, green, blue), shouldMirror);
    }

    // Loop to demonstrate WordArt function with different parameters
    printf("<!-- Demonstrating WordArt function with different parameters -->\n");
    for (int j = 0; j < 3; j++) {
        int x = 100 + j * 200;
        int y = 300 + j * 50;
        char* colors[] = {"purple", "orange", "teal"};
        char* transforms[] = {
            "transform='rotate(-10 100 300)'",
            "transform='rotate(0 300 350)'",
            "transform='rotate(10 500 400)'"
        };
        char* strokes[] = {"black", "gray", "darkblue"};

        WordArt(100, 500, x, y, colors[j], transforms[j], strokes[j]);
    }

    endHtmlSVG();

    return 0;
}