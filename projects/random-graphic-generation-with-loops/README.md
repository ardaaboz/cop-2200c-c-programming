# SVG Shape Generator

This project generates SVG (Scalable Vector Graphics) images containing a random assortment of circles and rectangles. The C program `main.c` outputs an HTML file that can be opened in any web browser to view the generated artwork.

## Features

* **Randomized Shapes:** Generates a random number of either circles or rectangles.
* **Dynamic Positioning and Sizing:** Each shape has a random position and size.
* **Vibrant Colors:** Shapes are drawn with randomly generated RGB colors.
* **SVG Output:** Creates an `svg.html` file that contains the SVG drawing.

## How it Works

The C program `main.c`:

1.  Initializes the random number generator using the current time to ensure different outputs each time it's run.
2.  Starts an HTML document with an SVG canvas of 1000x1000 pixels and a black background.
3.  Determines a random starting `shapeCount` and `shapeCountIncreaseValue`, and sets a `maxShapes` limit of 1000.
4.  Enters a loop that continues until `shapeCount` reaches `maxShapes`.
5.  Inside the loop:
    * Generates a random RGB color for each shape.
    * If `shapeCount` is less than 500, it draws a circle with random `cx`, `cy`, and `r` values.
    * Otherwise (if `shapeCount` is 500 or more), it draws a rectangle with random `x`, `y`, and `size` (for both width and height) values.
    * Increases `shapeCount` by `shapeCountIncreaseValue` for the next iteration.
6.  Closes the SVG and HTML tags, completing the `svg.html` file.

## How to Compile and Run

1.  **Save the code:** Save the provided C code as `main.c`.
2.  **Compile:** Open a terminal or command prompt and use a C compiler (like GCC) to compile the program:
    ```bash
    gcc main.c -o shape_generator
    ```
3.  **Run:** Execute the compiled program:
    ```bash
    ./shape_generator > svg.html
    ```
    This redirects the standard output (which contains the SVG and HTML tags) to a file named `svg.html` in the same directory.
4.  **View the output:** Open the `svg.html` file in your web browser to see the generated shapes.

## Examples

*(Since no specific output images for this version of `main.c` were provided, you would add them here. For instance, if you generate `circles_and_rects.png`)*

| ![Example Output](circles_and_rects.png) |
| :--------------------------------------: |
|         A mix of random circles and rectangles          |