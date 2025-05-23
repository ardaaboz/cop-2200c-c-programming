#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Draw a circle in SVG format
void circle ( int cx, int cy, int r, char* color )
{
    printf ( "\t<circle cx='%d' cy='%d' r='%d' fill='%s' />\n", cx, cy, r, color) ;
}

// Draw a rectangle in SVG format
void rect ( int x, int y, int width, int height, char* color )
{
    printf ( "\t<rect x='%d' y='%d' width='%d' height='%d' style='fill:%s;stroke-width:3;stroke:rgb(0,0,0)'/>\n",
        x, y, width, height, color ) ;
}

// Start HTML document with SVG canvas
void beginHtmlSVG ( int wide, int high, char* backColor)
{
    printf ( "<!DOCTYPE html>\n" ) ;
    printf ( "<html>\n" ) ;
    printf ( "<body>\n" ) ;

    printf( "<svg height='%d' width='%d' style='stroke-width: 0px; background-color: %s;'>\n",
        high, wide, backColor ) ;
}

// End HTML document with SVG
void endHtmlSVG ( )
{
    printf( "</svg>\n") ;
    printf ( "</body>\n" ) ;
    printf ( "</html>\n" ) ;
}

// Generate RGB color string
char* getRGBColor ( int red, int green, int blue )
{
    static char* svgFillString = "rgb(%d, %d, %d)" ;
    static char result[100] = { 0 } ;
    sprintf( result, svgFillString, red, green, blue ) ;
    return result ;
}

int main ( )
{
    // Initialize random seed
    srand( time ( 0 ) ) ;

    // Create 1000x1000 canvas with black background
    beginHtmlSVG ( 1000, 1000, getRGBColor( 0, 0, 0 ) ) ;

    // Generate random number of shapes
    int shapeCount = rand() % 250;
    int shapeCountIncreaseValue = rand() % 10;
    int maxShapes = 1000;

    // Draw shapes until reaching maximum
    while (shapeCount < maxShapes) {
        // Generate random RGB color
        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;
        char* color = getRGBColor(red, green, blue);

        // Draw circles for first half, rectangles for second half
        if (shapeCount < 500) {
            int cx = (rand() % 900) + 50;
            int cy = (rand() % 900) + 50;
            int r = (rand() % 50) + 10;
            circle(cx, cy, r, color);
        } else {
            int x = (rand() % 800) + 50;
            int y = (rand() % 800) + 50;
            int size = (rand() % 50) + 10;
            rect(x, y, size, size, color);
        }

        shapeCount += shapeCountIncreaseValue;
    }

    // Close HTML document
    endHtmlSVG ( ) ;

    return 0 ;
}