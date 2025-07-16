// games.h
// Struct definition for storing information about video or board games

#ifndef GAMES_H
#define GAMES_H

typedef struct game_structure
{
    char title[50];             // Name of the game (e.g., "The Legend of Zelda")
    char genre[30];             // Type of game (e.g., "Adventure", "Puzzle", "FPS")
    int releaseYear;           // Year the game was released
    double rating;             // Rating from critics or players (0.0 to 10.0 scale)
    char platform[40];         // Platform(s) the game is available on (e.g., "PC, PS5")
    char developer[40];        // Name of the game developer or studio
} Game;

#endif