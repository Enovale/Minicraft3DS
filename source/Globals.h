#pragma once

#include <3ds.h>
#include "Entity.h"
#include "Player.h"
#include "Input.h"
#include "MapGen.h"
#include "Quests.h"

#include "icons2_png.h"
#include "player_png.h"
#include "Font_png.h"
#include "bottombg_png.h"

#define CIRCLEPAD 0xF0000000
#define CSTICK 0x0F000000

#define MENU_NONE 0
#define MENU_TITLE 1
#define MENU_TUTORIAL 2
#define MENU_ABOUT 3
#define MENU_SETTINGS 4
#define MENU_LOADGAME 5
#define MENU_SETTINGS_REBIND 6
#define MENU_SETTINGS_TP 7
#define MENU_MULTIPLAYER_HOST 8
#define MENU_MULTIPLAYER_JOIN 9
#define MENU_MULTIPLAYER_WAIT 10
#define MENU_LOADING 11

#define MENU_PAUSED 100
#define MENU_INVENTORY 101
#define MENU_CRAFTING 102
#define MENU_CONTAINER 103
#define MENU_WIN 104
#define MENU_LOSE 105
#define MENU_DUNGEON 106
#define MENU_NPC 107
#define MENU_CHARACTER_CUSTOMIZE 108

#define NPC_GIRL 0
#define NPC_PRIEST 1
#define NPC_FARMER 2
#define NPC_LIBRARIAN 3
#define NPC_DWARF 4

#define TILE_NULL 255
#define TILE_GRASS 0
#define TILE_TREE 1
#define TILE_ROCK 2
#define TILE_DIRT 3
#define TILE_SAND 4
#define TILE_WATER 5
#define TILE_LAVA 6
#define TILE_CACTUS 7
#define TILE_FLOWER 8
#define TILE_IRONORE 9
#define TILE_GOLDORE 10
#define TILE_GEMORE 11
#define TILE_FARM 12
#define TILE_WHEAT 13
#define TILE_SAPLING_TREE 14
#define TILE_SAPLING_CACTUS 15
#define TILE_STAIRS_DOWN 16
#define TILE_STAIRS_UP 17
#define TILE_CLOUD 18
#define TILE_HARDROCK 19
#define TILE_CLOUDCACTUS 20
#define TILE_HOLE 21

#define TILE_WOOD_WALL 22
#define TILE_STONE_WALL 23
#define TILE_IRON_WALL 24
#define TILE_GOLD_WALL 25
#define TILE_GEM_WALL 26
#define TILE_DUNGEON_WALL 27
#define TILE_DUNGEON_FLOOR 28
#define TILE_DUNGEON_ENTRANCE 29
#define TILE_MAGIC_BARRIER 30
#define TILE_BOOKSHELVES 31
#define TILE_WOOD_FLOOR 32
#define TILE_MYCELIUM 33
#define TILE_MUSHROOM_BROWN 34
#define TILE_MUSHROOM_RED 35
#define TILE_ICE 36

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

//WARNING: Having this set to different values in different clients will break multiplayer!
#define TESTGODMODE false

bool paused;

u32 localUID;

int loadedtp;

u8 MODEL_3DS;

extern char versionText[34];

bool shouldRenderDebug;
bool shouldSpeedup;
bool shouldRenderMap;
bool UnderStrengthEffect;
bool UnderSpeedEffect;
bool regening;
bool UnderSwimBreathEffect;

sf2d_texture *icons;
sf2d_texture *playerSprites;
sf2d_texture *font;
sf2d_texture *bottombg;
sf2d_texture *minimap[6];

u32 dirtColor[5];
u32 grassColor;
u32 sandColor;
u32 waterColor[2];
u32 lavaColor[2];
u32 rockColor[4];
u32 woodColor;
u32 ironColor;
u32 goldColor;
u32 gemColor;
u32 dungeonColor[2];
u32 myceliumColor;
u32 mushroomColor;
u32 snowColor;
u32 iceColor;

char currentFileName[256];
extern u8 currentMenu;
extern char fpsstr[];
u8 initGame;
u8 initMPGame;
u8 initBGMap;
Item noItem;
int airWizardHealthDisplay;
s16 awX, awY;
bool quitGame;
s8 currentSelection;

typedef struct _worldData {
    u8 map[6][128*128];
    u8 data[6][128*128];
    
    u16 daytime;
    int day;
    u8 season;
    bool rain;
    
    u8 compassData[6][3];
} WorldData;

WorldData worldData;

//TODO: cleanup the order
int getEntities(Entity** result, s8 level, int x0, int y0, int x1, int y1);

bool moveMob(Entity* e, int xa, int ya);
void hurtEntity(Entity *e, int damage, int dir, u32 hurtColor, Entity *damager);

void tickTile(s8 level, int x, int y);
bool tileIsSolid(int tile, Entity * e);

s8 itemTileInteract(int tile, PlayerData *pd, Item *item, s8 level, int x, int y, int px, int py, int dir);

void tickEntity(Entity* e);

void trySpawn(int count, int level);

int getTile(s8 level, int x, int y);
void setTile(int id, s8 level, int x, int y);
int getData(s8 level, int x, int y);
void setData(int id, s8 level, int x, int y);
u32 getTileColor(int tile);

bool intersectsEntity(int x, int y, int r, Entity* e);

bool EntityBlocksEntity(Entity* e1, Entity* e2);
void EntityVsEntity(Entity* e1, Entity* e2);
bool ItemVsEntity(PlayerData *pd, Item *item, Entity *e, int dir);
void entityTileInteract(Entity* e, int tile, s8 level, int x, int y);

void openCraftingMenu(PlayerData *pd, RecipeManager *rm, char *title);
bool useEntity(PlayerData *pd, Entity* e);

bool isWater(s8 level, int xt, int yt);

void playerHurtTile(PlayerData *pd, int tile, s8 level, int xt, int yt, int damage, int dir);
void playerEntityInteract(PlayerData *pd, Entity* e);

bool dungeonActive();
void enterDungeon(PlayerData *pd);
void leaveDungeon(PlayerData *pd);

void setMinimapVisible(PlayerData *pd, int level, int x, int y, bool visible);
bool getMinimapVisible(PlayerData *pd, int level, int x, int y);
u32 getMinimapColor(PlayerData *pd, int level, int x, int y);
void initMinimapLevel(PlayerData *pd, int level);
void updateLevel1Map();

void reloadColors();