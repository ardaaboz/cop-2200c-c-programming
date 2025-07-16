#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h> // For snprintf

// Define screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Physics constants
#define GRAVITY_ACCELERATION 9.81f * 100.0f // Pixels per second squared
#define BOUNCE_DAMPING 0.8f // How much velocity is retained after bounce (0.0 to 1.0)
#define MIN_ROTATION_SPEED 0.01f // Radians per frame (initial speed, increased for visibility)
#define MAX_ROTATION_SPEED 0.5f // Max radians per frame to prevent excessive speed
#define HEXAGON_LINE_THICKNESS 3.0f // Thickness of the hexagon lines

// Structure for the Circle
typedef struct Circle {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} Circle;

// Structure for the Hexagon
typedef struct Hexagon {
    Vector2 center;
    float radius;
    float rotationAngle; // Current rotation angle in radians
    float rotationSpeed; // Radians per second
    Vector2 vertices[6]; // Store calculated vertices
    Color color;
} Hexagon;

// Function to calculate the vertices of a regular hexagon
void CalculateHexagonVertices(Hexagon *hexagon) {
    for (int i = 0; i < 6; i++) {
        // Angle for each vertex, adjusted by the current rotation angle
        float angle = (float)i * (PI / 3.0f) + hexagon->rotationAngle;
        hexagon->vertices[i].x = hexagon->center.x + hexagon->radius * cosf(angle); // Corrected to use ->
        hexagon->vertices[i].y = hexagon->center.y + hexagon->radius * sinf(angle); // Corrected to use ->
    }
}

// Function to find the closest point on a line segment to a given point
// Returns the closest point on the segment
Vector2 GetClosestPointOnLineSegment(Vector2 p, Vector2 a, Vector2 b) {
    // Note: If you are getting "implicit declaration" errors for Vector2Subtract, Vector2LengthSqr,
    // Vector2DotProduct, Vector2Add, or Vector2Scale, ensure raymath.h is correctly included
    // and your raylib library is properly linked in your build environment.
    Vector2 ap = Vector2Subtract(p, a);
    Vector2 ab = Vector2Subtract(b, a);
    float magnitudeSq = Vector2LengthSqr(ab); // Corrected function name

    float t = 0.0f;
    if (magnitudeSq > 0) { // Avoid division by zero if segment is a point
        t = Vector2DotProduct(ap, ab) / magnitudeSq;
        t = fmaxf(0.0f, fminf(1.0f, t)); // Clamp t to [0, 1]
    }

    return Vector2Add(a, Vector2Scale(ab, t));
}

int main() {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravity Hexagon Simulation");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Initialize Hexagon
    Hexagon hexagon = {0};
    hexagon.center = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    hexagon.radius = 200.0f;
    hexagon.rotationAngle = 0.0f;
    hexagon.rotationSpeed = MIN_ROTATION_SPEED; // Initial low rotation speed
    hexagon.color = LIGHTGRAY;

    // Initialize Circle
    Circle circle = {0};
    circle.position = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - hexagon.radius / 2.0f};
    circle.velocity = (Vector2){0.0f, 0.0f};
    circle.radius = 15.0f;
    circle.color = RED;

    // Game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        // Apply gravity to circle's velocity
        circle.velocity.y += GRAVITY_ACCELERATION * deltaTime;

        // Update circle's position
        circle.position = Vector2Add(circle.position, Vector2Scale(circle.velocity, deltaTime));

        // Update hexagon rotation
        hexagon.rotationAngle += hexagon.rotationSpeed * deltaTime; // Rotate based on speed and time
        if (hexagon.rotationAngle >= 2 * PI) hexagon.rotationAngle -= 2 * PI; // Keep angle within 0-2PI

        // Recalculate hexagon vertices based on new rotation
        CalculateHexagonVertices(&hexagon);

        // Collision detection and response for circle with hexagon walls
        bool collidedThisFrame = false; // Flag to prevent multiple speed increases per frame
        for (int i = 0; i < 6; i++) {
            Vector2 p1 = hexagon.vertices[i];
            Vector2 p2 = hexagon.vertices[(i + 1) % 6];

            Vector2 closestPoint = GetClosestPointOnLineSegment(circle.position, p1, p2);
            Vector2 distVec = Vector2Subtract(circle.position, closestPoint);
            float distance = Vector2Length(distVec); // Note: Vector2Length also needs raymath.h

            if (distance < circle.radius) {
                // Collision detected!
                Vector2 normal;
                if (distance == 0) { // If circle center is exactly on the line
                    // Calculate a perpendicular vector to the line segment
                    Vector2 segmentDir = Vector2Normalize(Vector2Subtract(p2, p1)); // Note: Vector2Normalize also needs raymath.h
                    normal = (Vector2){-segmentDir.y, segmentDir.x}; // Perpendicular
                    // Ensure normal points outwards from the hexagon
                    if (Vector2DotProduct(normal, Vector2Subtract(circle.position, hexagon.center)) < 0) {
                        normal = Vector2Scale(normal, -1.0f);
                    }
                } else {
                    normal = Vector2Normalize(distVec); // Normal points from closest point to circle center
                }

                // Resolve overlap (push circle out of the wall)
                float overlap = circle.radius - distance;
                circle.position = Vector2Add(circle.position, Vector2Scale(normal, overlap + 0.01f)); // Add small epsilon

                // Reflect velocity
                float dotProduct = Vector2DotProduct(circle.velocity, normal);
                circle.velocity = Vector2Subtract(circle.velocity, Vector2Scale(normal, 2.0f * dotProduct));

                // Apply damping
                circle.velocity = Vector2Scale(circle.velocity, BOUNCE_DAMPING);

                // Double hexagon rotation speed, but only once per collision event
                if (!collidedThisFrame) {
                    hexagon.rotationSpeed *= 2.0f;
                    if (hexagon.rotationSpeed > MAX_ROTATION_SPEED) {
                        hexagon.rotationSpeed = MAX_ROTATION_SPEED; // Cap max speed
                    }
                    collidedThisFrame = true;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw Hexagon with thicker lines
        for (int i = 0; i < 6; i++) {
            DrawLineEx(hexagon.vertices[i], hexagon.vertices[(i + 1) % 6], HEXAGON_LINE_THICKNESS, hexagon.color);
        }

        // Draw Circle
        DrawCircleV(circle.position, circle.radius, circle.color);

        // Display info
        char speedText[50];
        snprintf(speedText, sizeof(speedText), "Rotation Speed: %.3f rad/s", hexagon.rotationSpeed);
        DrawText(speedText, 10, 10, 20, DARKGRAY);
        DrawText("Press ESC to exit", 10, 30, 20, DARKGRAY);


        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and unload OpenGL context

    return 0;
}
