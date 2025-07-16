#include <stdio.h>
#include <string.h>
#include "games.h"

int main(void) {
    // Creating instances
    Game GTASanAndreas;
    Game Rimworld;
    Game Kenshi;
    Game Minecraft;
    Game PrisonArchitect;

    // Setting properties

    // GTA San Andreas
    strcpy(GTASanAndreas.title, "GTA: San Andreas");
    strcpy(GTASanAndreas.genre, "Action");
    GTASanAndreas.releaseYear = 2004;
    GTASanAndreas.rating = 9.6;
    strcpy(GTASanAndreas.platform, "PC, PS2, Xbox, Mobile");
    strcpy(GTASanAndreas.developer, "Rockstar North");

    // Rimworld
    strcpy(Rimworld.title, "RimWorld");
    strcpy(Rimworld.genre, "Colony Simulation");
    Rimworld.releaseYear = 2018;
    Rimworld.rating = 9.3;
    strcpy(Rimworld.platform, "PC, Mac, Linux, PS4, Xbox One");
    strcpy(Rimworld.developer, "Ludeon Studios");

    // Kenshi
    strcpy(Kenshi.title, "Kenshi");
    strcpy(Kenshi.genre, "RPG/Survival");
    Kenshi.releaseYear = 2018;
    Kenshi.rating = 8.7;
    strcpy(Kenshi.platform, "PC");
    strcpy(Kenshi.developer, "Lo-Fi Games");

    // Minecraft
    strcpy(Minecraft.title, "Minecraft");
    strcpy(Minecraft.genre, "Sandbox");
    Minecraft.releaseYear = 2011;
    Minecraft.rating = 9.0;
    strcpy(Minecraft.platform, "PC, Mobile, Console, VR");
    strcpy(Minecraft.developer, "Mojang Studios");

    // Prison Architect
    strcpy(PrisonArchitect.title, "Prison Architect");
    strcpy(PrisonArchitect.genre, "Construction/Management");
    PrisonArchitect.releaseYear = 2015;
    PrisonArchitect.rating = 8.1;
    strcpy(PrisonArchitect.platform, "PC, Mac, Linux, Mobile, Console");
    strcpy(PrisonArchitect.developer, "Introversion Software");

    // Putting games into an array
    Game gamesArray[] = {GTASanAndreas, Rimworld, Kenshi, Minecraft, PrisonArchitect};

    // Opening file
    FILE *file = fopen("games.dat", "wb");
    // Writing array to the file
    fwrite(gamesArray, sizeof(Game), 5, file);
    // Closing file
    fclose(file);

    return 0;
}