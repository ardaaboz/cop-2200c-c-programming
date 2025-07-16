#include "raylib.h"
#include "raymath.h"
#include <math.h>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define NUM_SIDES 6
#define RADIUS 200
#define BALL_RADIUS 10
#define GRAVITY 300.0f

typedef struct {
    Vector2 position;
    Vector2 velocity;
} Ball;

typedef struct {
    Vector2 points[NUM_SIDES];
} Hexagon;

float DegreesToRadians(float deg) {
    return deg * (PI / 180.0f);
}

Vector2 RotatePoint(Vector2 point, Vector2 origin, float angle) {
    float s = sinf(angle);
    float c = cosf(angle);

    point.x -= origin.x;
    point.y -= origin.y;

    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    point.x = xnew + origin.x;
    point.y = ynew + origin.y;
    return point;
}

Hexagon GetRotatedHexagon(Vector2 center, float radius, float rotation) {
    Hexagon hex;
    for (int i = 0; i < NUM_SIDES; i++) {
        float angleDeg = 60 * i;
        float angleRad = DegreesToRadians(angleDeg) + rotation;
        hex.points[i] = (Vector2){
            center.x + radius * cosf(angleRad),
            center.y + radius * sinf(angleRad)
        };
    }
    return hex;
}

Vector2 Reflect(Vector2 velocity, Vector2 normal) {
    float dot = velocity.x * normal.x + velocity.y * normal.y;
    return (Vector2){
        velocity.x - 2 * dot * normal.x,
        velocity.y - 2 * dot * normal.y
    };
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rotating Hexagon Gravity Simulation");
    SetTargetFPS(60);

    Vector2 center = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    float rotation = 0.0f;
    float rotationSpeed = DegreesToRadians(10); // low initial speed

    Ball ball = {
        .position = { center.x, center.y - 100 },
        .velocity = { 50.0f, 0.0f }
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics
        ball.velocity.y += GRAVITY * dt;
        ball.position.x += ball.velocity.x * dt;
        ball.position.y += ball.velocity.y * dt;

        // Update rotation
        rotation += rotationSpeed * dt;

        // Get hexagon vertices
        Hexagon hex = GetRotatedHexagon(center, RADIUS, rotation);

        // Collision check
        for (int i = 0; i < NUM_SIDES; i++) {
            Vector2 a = hex.points[i];
            Vector2 b = hex.points[(i + 1) % NUM_SIDES];

            Vector2 edge = Vector2Subtract(b, a);
            Vector2 edgeNormal = { -edge.y, edge.x };
            edgeNormal = Vector2Normalize(edgeNormal);

            Vector2 ap = Vector2Subtract(ball.position, a);
            float dist = Vector2DotProduct(ap, edgeNormal);

            if (dist < BALL_RADIUS && Vector2DotProduct(ball.velocity, edgeNormal) < 0) {
                // Collision occurred
                ball.position = Vector2Add(ball.position, Vector2Scale(edgeNormal, BALL_RADIUS - dist));
                ball.velocity = Reflect(ball.velocity, edgeNormal);
                rotationSpeed *= 2.0f;
                break;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw hexagon
        for (int i = 0; i < NUM_SIDES; i++) {
            Vector2 p1 = hex.points[i];
            Vector2 p2 = hex.points[(i + 1) % NUM_SIDES];
            DrawLineEx(p1, p2, 2.0f, BLACK);
        }

        DrawCircleV(ball.position, BALL_RADIUS, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
