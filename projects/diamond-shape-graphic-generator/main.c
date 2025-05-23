#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void line ( float x1, float y1, float x2, float y2, char* stroke )
{
    printf ( "<line x1='%f' y1='%f' x2='%f' y2='%f' style='%s' />\n",
        x1, y1, x2, y2, stroke ) ;
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
    // Write output to file
    freopen("svg.html", "w", stdout);  // Or fopen("svg.html", "w")
    // Initialize random seed
    srand( time ( 0 ) ) ;

    // Create 1000x1000 canvas with black background
    beginHtmlSVG ( 1000, 1000, getRGBColor( 0, 0, 0 ) ) ;

    // Generate random number of shapes
    int shapeCount = 0;
    int maxShapes = (rand() % 50) + 5;

    // Draw shapes until reaching maximum
    while (shapeCount < maxShapes) {
        // Generate random RGB color
        int red = rand() % 256;
        int green = rand() % 256;
        int blue = rand() % 256;

        int positionX = (rand() % 500) + 250;
        int positionY = (rand() % 500) + 250;
        int lineLength = (rand() % 200) + 10;
        int lineCount = (rand() % 10) + 5;

        char* color = getRGBColor(red, green, blue);
        static char stroke[100];
        sprintf(stroke, "stroke:%s; stroke-width:2", color);

        // Horizontal Line
        line(positionX - lineLength, positionY, positionX + lineLength, positionY, stroke);

        // Vertical line
        line(positionX, positionY+lineLength, positionX, positionY-lineLength, stroke);

        int i = 0;
        int var1 = lineCount;
        int var2 = lineCount-(lineCount-1);
        while (i < lineCount) {
            line(positionX, positionY + var1 * (lineLength / lineCount), positionX + var2 * (lineLength / lineCount), positionY, stroke);
            line(positionX,positionY - var1 * (lineLength / lineCount),positionX + var2 * (lineLength / lineCount), positionY, stroke);
            line(positionX,positionY - var1 * (lineLength / lineCount),positionX - var2 * (lineLength / lineCount), positionY, stroke);
            line(positionX,positionY + var1 * (lineLength / lineCount),positionX - var2 * (lineLength / lineCount), positionY, stroke);
            var1--;
            var2++;
            i++;
        }

        /* MANUAL WAY
        // -3Y, X1
        line(position,position + 3 * (lineLength / lineCount),position + 1 * (lineLength / lineCount), position, stroke);
        // -2Y, X2
        line(position,position + 2 * (lineLength / lineCount),position + 2 * (lineLength / lineCount), position, stroke);
        // -1Y, X3
        line(position,position + 1 * (lineLength / lineCount),position + 3 * (lineLength / lineCount), position, stroke);

        // 3Y, X1
        line(position,position - 3 * (lineLength / lineCount),position + 1 * (lineLength / lineCount), position, stroke);
        // 2Y, X2
        line(position,position - 2 * (lineLength / lineCount),position + 2 * (lineLength / lineCount), position, stroke);
        // 1Y, X3
        line(position,position - 1 * (lineLength / lineCount),position + 3 * (lineLength / lineCount), position, stroke);

        // 3Y, -X1
        line(position,position - 3 * (lineLength / lineCount),position - 1 * (lineLength / lineCount), position, stroke);
        // 2Y, -X2
        line(position,position - 2 * (lineLength / lineCount),position - 2 * (lineLength / lineCount), position, stroke);
        // 1Y, -X13
        line(position,position - 1 * (lineLength / lineCount),position - 3 * (lineLength / lineCount), position, stroke);

        // -3Y, -X1
        line(position,position + 3 * (lineLength / lineCount),position - 1 * (lineLength / lineCount), position, stroke);
        // -2Y, -X2
        line(position,position + 2 * (lineLength / lineCount),position - 2 * (lineLength / lineCount), position, stroke);
        // -1Y, -X13
        line(position,position + 1 * (lineLength / lineCount),position - 3 * (lineLength / lineCount), position, stroke);
        */
        shapeCount++;
    }
    // Close HTML document
    endHtmlSVG ( ) ;
    return 0 ;
}