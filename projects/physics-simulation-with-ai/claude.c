#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define HEXAGON_RADIUS 200
#define CIRCLE_RADIUS 15
#define GRAVITY 500.0f
#define DAMPING 0.8f
#define INITIAL_ROTATION_SPEED 10.0f

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Circle;

typedef struct {
    Vector2 center;
    float radius;
    float rotation;
    float rotationSpeed;
    Vector2 vertices[6];
} Hexagon;

// Function to rotate a point around another point
Vector2 RotatePoint(Vector2 point, Vector2 center, float angle) {
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);

    float dx = point.x - center.x;
    float dy = point.y - center.y;

    Vector2 result;
    result.x = center.x + dx * cos_a - dy * sin_a;
    result.y = center.y + dx * sin_a + dy * cos_a;

    return result;
}

// Calculate hexagon vertices
void UpdateHexagonVertices(Hexagon* hex) {
    for (int i = 0; i < 6; i++) {
        float angle = (PI / 3.0f) * i + hex->rotation;
        hex->vertices[i].x = hex->center.x + hex->radius * cosf(angle);
        hex->vertices[i].y = hex->center.y + hex->radius * sinf(angle);
    }
}

// Get the normal vector of a line segment
Vector2 GetLineNormal(Vector2 p1, Vector2 p2) {
    Vector2 dir = {p2.x - p1.x, p2.y - p1.y};
    Vector2 normal = {-dir.y, dir.x};

    // Normalize
    float length = sqrtf(normal.x * normal.x + normal.y * normal.y);
    if (length > 0) {
        normal.x /= length;
        normal.y /= length;
    }

    return normal;
}

// Check if point is inside hexagon (for normal direction)
bool IsPointInsideHexagon(Vector2 point, Hexagon* hex) {
    int crossings = 0;

    for (int i = 0; i < 6; i++) {
        Vector2 v1 = hex->vertices[i];
        Vector2 v2 = hex->vertices[(i + 1) % 6];

        if (((v1.y <= point.y) && (point.y < v2.y)) ||
            ((v2.y <= point.y) && (point.y < v1.y))) {
            float intersectX = v1.x + (point.y - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
            if (point.x < intersectX) {
                crossings++;
            }
        }
    }

    return (crossings % 2) == 1;
}

// Distance from point to line segment
float DistanceToLineSegment(Vector2 point, Vector2 p1, Vector2 p2, Vector2* closest) {
    Vector2 line = {p2.x - p1.x, p2.y - p1.y};
    Vector2 toPoint = {point.x - p1.x, point.y - p1.y};

    float lineLength = sqrtf(line.x * line.x + line.y * line.y);
    if (lineLength == 0) {
        *closest = p1;
        return sqrtf(toPoint.x * toPoint.x + toPoint.y * toPoint.y);
    }

    float t = (toPoint.x * line.x + toPoint.y * line.y) / (lineLength * lineLength);
    t = fmaxf(0.0f, fminf(1.0f, t));

    closest->x = p1.x + t * line.x;
    closest->y = p1.y + t * line.y;

    float dx = point.x - closest->x;
    float dy = point.y - closest->y;
    return sqrtf(dx * dx + dy * dy);
}

// Check collision with hexagon and respond
bool CheckHexagonCollision(Circle* circle, Hexagon* hex) {
    bool collided = false;

    for (int i = 0; i < 6; i++) {
        Vector2 p1 = hex->vertices[i];
        Vector2 p2 = hex->vertices[(i + 1) % 6];
        Vector2 closest;

        float distance = DistanceToLineSegment(circle->position, p1, p2, &closest);

        if (distance < circle->radius) {
            // Calculate collision normal
            Vector2 normal = GetLineNormal(p1, p2);

            // Make sure normal points inward
            Vector2 midpoint = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
            Vector2 toCenter = {hex->center.x - midpoint.x, hex->center.y - midpoint.y};

            if (normal.x * toCenter.x + normal.y * toCenter.y < 0) {
                normal.x = -normal.x;
                normal.y = -normal.y;
            }

            // Move circle out of wall
            float penetration = circle->radius - distance;
            circle->position.x += normal.x * penetration;
            circle->position.y += normal.y * penetration;

            // Reflect velocity
            float dotProduct = circle->velocity.x * normal.x + circle->velocity.y * normal.y;
            circle->velocity.x -= 2 * dotProduct * normal.x;
            circle->velocity.y -= 2 * dotProduct * normal.y;

            // Apply damping
            circle->velocity.x *= DAMPING;
            circle->velocity.y *= DAMPING;

            collided = true;
            break;
        }
    }

    return collided;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hexagon Bounce Simulation");
    SetTargetFPS(60);

    // Initialize circle
    Circle circle = {0};
    circle.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50};
    circle.velocity = (Vector2){100, 0};
    circle.radius = CIRCLE_RADIUS;

    // Initialize hexagon
    Hexagon hexagon = {0};
    hexagon.center = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    hexagon.radius = HEXAGON_RADIUS;
    hexagon.rotation = 0;
    hexagon.rotationSpeed = INITIAL_ROTATION_SPEED;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update hexagon rotation
        hexagon.rotation += hexagon.rotationSpeed * deltaTime * PI / 180.0f;
        UpdateHexagonVertices(&hexagon);

        // Apply gravity to circle
        circle.velocity.y += GRAVITY * deltaTime;

        // Update circle position
        circle.position.x += circle.velocity.x * deltaTime;
        circle.position.y += circle.velocity.y * deltaTime;

        // Check collision with hexagon
        if (CheckHexagonCollision(&circle, &hexagon)) {
            // Double rotation speed on collision
            hexagon.rotationSpeed *= 2.0f;

            // Cap rotation speed to prevent it from becoming too crazy
            if (hexagon.rotationSpeed > 1000.0f) {
                hexagon.rotationSpeed = 1000.0f;
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw hexagon
        for (int i = 0; i < 6; i++) {
            Vector2 p1 = hexagon.vertices[i];
            Vector2 p2 = hexagon.vertices[(i + 1) % 6];
            DrawLineV(p1, p2, WHITE);
        }

        // Draw circle
        DrawCircleV(circle.position, circle.radius, RED);

        // Draw info
        DrawText(TextFormat("Rotation Speed: %.1f°/s", hexagon.rotationSpeed), 10, 10, 20, WHITE);
        DrawText("Press ESC to exit", 10, 40, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}