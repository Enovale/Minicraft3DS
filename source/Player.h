#pragma once

#include "Input.h"
#include "Entity.h"
#include "QuestsData.h"
#include "Crafting.h"

#define MAX_PLAYERS 8
#define MAX_INPUT_BUFFER 3

#define PLAYER_SPRITE_HEAD_COUNT 4
#define PLAYER_SPRITE_EYES_COUNT 5
#define PLAYER_SPRITE_BODY_COUNT 6
#define PLAYER_SPRITE_ARMS_COUNT 6
#define PLAYER_SPRITE_LEGS_COUNT 5


typedef struct _plrsp {
    bool choosen;
    
    u8 legs;
    u8 body;
    u8 arms;
    u8 head;
    u8 eyes;
} PlayerSprite;

typedef struct _plrd {
    //for identification in save data and sync game start
    u32 id;
    bool idSet;
    bool ready;
    
    //input/multiplayer/synchronization
    Inputs inputs;
    Inputs nextInputs[MAX_INPUT_BUFFER];
    bool nextTurnReady[MAX_INPUT_BUFFER];
    
    //
    bool isSpawned;
    u8 minimapData[128*128];
    
	int score;
    QuestlineManager questManager;
    
    Entity entity;
    Inventory inventory;
    Item *activeItem;
    
    PlayerSprite sprite;
    
    //menu data
    u8 ingameMenu;
    s8 ingameMenuSelection;
    s16 ingameMenuInvSel;
    s16 ingameMenuInvSelOther;
    bool ingameMenuAreYouSure;
    bool ingameMenuAreYouSureSave;
    s16 ingameMenuTimer;
    NPC_MenuData npcMenuData;
    
    RecipeManager currentRecipes;
    char *currentCraftTitle;
    Entity *curChestEntity;
    s8 curChestEntityR;
    
    bool mapShouldRender;
    u8 mapZoomLevel;
    s16 mapScrollX;
    s16 mapScrollY;
    char mapText[32];
    
    s16 touchLastX;
    s16 touchLastY;
    bool touchIsDraggingMap;
    bool touchIsChangingSize;
} PlayerData;

PlayerData players[MAX_PLAYERS];
int playerCount;
int playerLocalID;

void initPlayers();
void freePlayers();

void initPlayer(PlayerData *pd);
void freePlayer(PlayerData *pd);

PlayerData* getNearestPlayer(s8 level, s16 x, s16 y);
PlayerData* getLocalPlayer();

void tickPlayer(PlayerData *pd, bool inmenu);
void playerSetActiveItem(PlayerData *pd, Item * item);
bool playerUseEnergy(PlayerData * pd, int amount);
void playerHeal(PlayerData *pd, int amount);
void playerSpawn(PlayerData *pd);
