#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "QuestsData.h"
#include "Player.h"
#include "Crafting.h"

#define NPC_MENU_TALK 0

RecipeManager priestTrades;
RecipeManager farmerTrades;
RecipeManager dwarfTrades;

void initTrades();
void freeTrades();

void initQuests(QuestlineManager *questManager);
void resetQuests(QuestlineManager *questManager);
void freeQuests(QuestlineManager *questManager);

void resetNPCMenuData(NPC_MenuData *data);
void openNPCMenu(PlayerData *pd, int npc);
void tickNPCMenu(PlayerData *pd);
void renderNPCMenu(NPC_MenuData *data);
