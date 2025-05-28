#include <stdio.h>
#include <stdbool.h>

// Draw a triangle using three vertices:
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


void beginHtmlSVG ( int wide, int high, char* backColor)
{
    printf ( "<!DOCTYPE html>\n" ) ;
    printf ( "<html>\n" ) ;
    printf ( "<body>\n" ) ;

    printf( "<svg height='%d' width='%d' style='stroke-width: 0px; background-color: %s;'>\n",
        high, wide, backColor ) ;
}

void endHtmlSVG ( )
{
    printf( "</svg>\n") ;
    printf ( "</body>\n" ) ;
    printf ( "</html>\n" ) ;
}

char* getRGBColor ( int red, int green, int blue )
{
    static char* svgFillString = "rgb(%d, %d, %d)" ;
    static char result[100] = { 0 } ;
    sprintf( result, svgFillString, red, green, blue ) ;
    return result ;
}

int main ( )
{
    beginHtmlSVG ( 100, 100, getRGBColor( 255, 255, 255 ) ) ;

    triangle(10,10,40,50,10,50,  getRGBColor(0,255,0), true);

    endHtmlSVG ( ) ;

    return 0 ;
}
