#ifndef PLANE_H
#define PLANE_H

#include <stdbool.h>

typedef struct plane_struct {
    char model[20];         // Model and brand
    float max_speed;        // Maximum speed
    float max_alt;          // Maximum altitude
    int passanger_cap;      // Passanger capacity
    bool is_military;       // Military or commercial?
} Plane ;

#endif // PLANE_H