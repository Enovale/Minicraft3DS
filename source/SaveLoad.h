#pragma once
#include <stdio.h>
#include <string.h>
#include "Entity.h"
#include "Player.h"
#include "Globals.h"

#define SAVE_VERSION 1

#define SAVE_COMMENT "Minicraft3DSSave"
#define SAVE_COPYBUFFER_SIZE 4096

//void saveCurrentWorld(char * filename, EntityManager * eManager, Entity * player, u8 * map, u8 * mapData, WorldData *worldData);
//int loadWorld(char * filename, EntityManager * eManager, Entity * player, u8 * map, u8 * mapData, WorldData *worldData);

bool saveWorld(char *filename,  EntityManager *eManager, WorldData *worldData, PlayerData *players, int playerCount);
bool loadWorld(char *filename, EntityManager *eManager, WorldData *worldData, PlayerData *players, int playerCount);
