#include "Player.h"

#include <limits.h>
#include "Globals.h"

void potionEffect(int type) {
	if(type == 1) {
		UnderStrengthEffect = true;
	}
	if(type == 2) {
		UnderSpeedEffect = true;
	}
	if (type == 3) {
		regening = true;
	}
	if (type == 4) {
		UnderSwimBreathEffect = true;
	}
}

void initPlayers() {
    for(int i=0; i<MAX_PLAYERS; i++) {
        initPlayer(players+i);
    }
}

void freePlayers() {
    for(int i=0; i<MAX_PLAYERS; i++) {
        freePlayer(players+i);
    }
}

void playerInitMiniMapData(u8 *minimapData) {
	int i;
	for(i = 0; i < 128 * 128; ++i) {
		minimapData[i] = 0;
	}
}

void playerInitEntity(PlayerData *pd) {
    pd->entity.type = ENTITY_PLAYER;
    pd->entity.level = 1;
    pd->entity.xr = 4;
    pd->entity.yr = 3;
    pd->entity.canSwim = true;
    pd->entity.p.ax = 0;
    pd->entity.p.ay = 0;
    pd->entity.p.health = 10;
    pd->entity.p.stamina = 10;
    pd->entity.p.walkDist = 0;
    pd->entity.p.attackTimer = 0;
    pd->entity.p.dir = 0;
    pd->entity.p.isDead = false;
    pd->entity.p.hasWon = false;
    
    pd->entity.p.data = pd;
}

void playerInitInventory(PlayerData *pd) {
    //reset inventory
    pd->inventory.lastSlot = 0;
    pd->activeItem = &noItem;
    
    addItemToInventory(newItem(ITEM_WORKBENCH,0), &(pd->inventory));
    addItemToInventory(newItem(ITEM_POWGLOVE,0), &(pd->inventory));   
    
    if(TESTGODMODE) {
		addItemToInventory(newItem(ITEM_GOLD_APPLE,1), &(pd->inventory));
		addItemToInventory(newItem(ITEM_STRENGTH_POTION,1), &(pd->inventory));
        addItemToInventory(newItem(TOOL_SHOVEL,1), &(pd->inventory));
        addItemToInventory(newItem(TOOL_HOE,4), &(pd->inventory));
        addItemToInventory(newItem(TOOL_SWORD,4), &(pd->inventory));
        addItemToInventory(newItem(TOOL_PICKAXE,4), &(pd->inventory));
        addItemToInventory(newItem(TOOL_AXE,4), &(pd->inventory));
        
        addItemToInventory(newItem(ITEM_ANVIL,0), &(pd->inventory));
        addItemToInventory(newItem(ITEM_CHEST,0), &(pd->inventory));
        addItemToInventory(newItem(ITEM_OVEN,0), &(pd->inventory));
        addItemToInventory(newItem(ITEM_FURNACE,0), &(pd->inventory));
        addItemToInventory(newItem(ITEM_LANTERN,0), &(pd->inventory)); 
        
        addItemToInventory(newItem(TOOL_MAGIC_COMPASS,1), &(pd->inventory));  
        
        int i;
        for (i = 7;i < 28;++i) addItemToInventory(newItem(i,50), &(pd->inventory));
    }
}

void playerInitSprite(PlayerData *pd) {
    pd->sprite.choosen = false;
    
    pd->sprite.legs = 0;
    pd->sprite.body = 0;
    pd->sprite.arms = 0;
    pd->sprite.head = 0;
    pd->sprite.eyes = 0;
}

void playerInitMenus(PlayerData *pd) {
    pd->ingameMenu = MENU_NONE;
    pd->ingameMenuSelection = 0;
    pd->ingameMenuInvSel = 0;
    pd->ingameMenuInvSelOther = 0;
    pd->ingameMenuAreYouSure = false;
    pd->ingameMenuAreYouSureSave = false;
    pd->ingameMenuTimer = 0;
    
    resetNPCMenuData(&(pd->npcMenuData));
    
    pd->mapShouldRender = false;
	pd->mapScrollX = 0;
	pd->mapScrollY = 0;
	pd->mapZoomLevel = 2;
    sprintf(pd->mapText,"x%d", pd->mapZoomLevel);
    
    pd->touchLastX = -1;
    pd->touchLastY = -1;
    pd->touchIsDraggingMap = false;
    pd->touchIsChangingSize = false;
}

void initPlayer(PlayerData *pd) {
    pd->isSpawned = false;
    
    playerInitMiniMapData(pd->minimapData);
    playerInitEntity(pd);
    playerInitInventory(pd);
    
    playerInitSprite(pd);
    
    initQuests(&(pd->questManager));
    resetQuests(&(pd->questManager));
    
    playerInitMenus(pd);
    
    pd->score = 0;
}

void freePlayer(PlayerData *pd) {
    freeQuests(&(pd->questManager));
}

PlayerData* getNearestPlayer(s8 level, s16 x, s16 y) {
    int nearest = -1;
    unsigned int nearestDist = UINT_MAX;
    
    for(int i=0; i<playerCount; i++) {
        if(players[i].entity.level!=level) continue;
        
        int xdif = players[i].entity.x - x;
        int ydif = players[i].entity.y - y;
        
        unsigned int dist = xdif*xdif + ydif*ydif;
        if(dist<nearestDist) {
            nearest = i;
            nearestDist = dist;
        }
    }
    
    if(nearest==-1) return NULL;
    
    return players+nearest;
}

PlayerData* getLocalPlayer() {
    return players+playerLocalID;
}

//player update functions
bool playerUseItem(PlayerData *pd) {
    int aitemID = 0;
    Item * aitem;
    Item * item ;
    
    switch(pd->activeItem->id){
        //shooting arrows
        case TOOL_BOW:
            item = getItemFromInventory(ITEM_ARROW_WOOD, &(pd->inventory));
            if(item!=NULL) {
                aitemID = ITEM_ARROW_WOOD;
                aitem = item;
            }
            item = getItemFromInventory(ITEM_ARROW_STONE, &(pd->inventory));
            if(item!=NULL) {
                aitemID = ITEM_ARROW_STONE;
                aitem = item;
            }
            item = getItemFromInventory(ITEM_ARROW_IRON, &(pd->inventory));
            if(item!=NULL) {
                aitemID = ITEM_ARROW_IRON;
                aitem = item;
            }
            item = getItemFromInventory(ITEM_ARROW_GOLD, &(pd->inventory));
            if(item!=NULL) {
                aitemID = ITEM_ARROW_GOLD;
                aitem = item;
            }
            item = getItemFromInventory(ITEM_ARROW_GEM, &(pd->inventory));
            if(item!=NULL) {
                aitemID = ITEM_ARROW_GEM;
                aitem = item;
            }
            
            if(aitemID!=0) {
                --aitem->countLevel;
                if (isItemEmpty(aitem)) {
                    removeItemFromInventory(aitem->slotNum, &(pd->inventory));
                }
                
                switch(pd->entity.p.dir) {
                case 0:
                    addEntityToList(newArrowEntity(&(pd->entity), aitemID, 0, 2, pd->entity.level), &eManager);
                    break;
                case 1:
                    addEntityToList(newArrowEntity(&(pd->entity), aitemID, 0, -2, pd->entity.level), &eManager);
                    break;
                case 2:
                    addEntityToList(newArrowEntity(&(pd->entity), aitemID, -2, 0, pd->entity.level), &eManager);
                    break;
                case 3:
                    addEntityToList(newArrowEntity(&(pd->entity), aitemID, 2, 0, pd->entity.level), &eManager);
                    break;
                }
                return true;
            }
            break;
            
        // Health items
        case ITEM_APPLE:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 2)){
                playerHeal(pd, 1); 
                --(pd->activeItem->countLevel);
            }
            break;
		case ITEM_STRENGTH_POTION:
			if(pd->entity.p.health < 20 && playerUseEnergy(pd, 2) && pd->entity.p.strengthTimer == 0){
				potionEffect(1);
				--item->countLevel;
			}
            return 0;
		case ITEM_SPEED_POTION:
			if(pd->entity.p.health < 20 && playerUseEnergy(pd, 2) && pd->entity.p.speedTimer == 0){
				potionEffect(2);
				--item->countLevel;
			}
            return 0;
		case ITEM_REGEN_POTION:
			if(pd->entity.p.health < 20 && playerUseEnergy(pd, 2) && pd->entity.p.regenTimer == 0){
				potionEffect(3);
				--item->countLevel;
			}
            return 0;
		case ITEM_SWIM_BREATH_POTION:
			if(pd->entity.p.health < 20 && playerUseEnergy(pd, 2) && pd->entity.p.swimBreathTimer == 0){
				potionEffect(4);
				--item->countLevel;
			}
            return 0;
		case ITEM_GOLD_APPLE:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 1)){
                playerHeal(pd, 8); 
				playerUseEnergy(pd, -10);
                --item->countLevel;
            }
            return 0;
        case ITEM_FLESH:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 4+(rand()%4))){
                playerHeal(pd, 1); 
                --(pd->activeItem->countLevel);
            }
            break;
        case ITEM_BREAD:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 3)){
                playerHeal(pd, 2); 
                --(pd->activeItem->countLevel);
            }
            break;
		case ITEM_PORK_RAW:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 4+(rand()%4))){
                playerHeal(pd, 1); 
                --(pd->activeItem->countLevel);
            }
            break;
		case ITEM_PORK_COOKED:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 3)){
                playerHeal(pd, 3); 
                --(pd->activeItem->countLevel);
            }
            break;
		case ITEM_BEEF_RAW:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 4+(rand()%4))){
                playerHeal(pd, 1); 
                --(pd->activeItem->countLevel);
            }
            break;
		case ITEM_BEEF_COOKED:
            if(pd->entity.p.health < 10 && playerUseEnergy(pd, 3)){
                playerHeal(pd, 4); 
                --(pd->activeItem->countLevel);
            }
            break;
		//special item
		case ITEM_WIZARD_SUMMON:
			if(pd->entity.level==0) {
                --(pd->activeItem->countLevel);
				
				airWizardHealthDisplay = 2000;
				addEntityToList(newAirWizardEntity(630, 820, 0), &eManager);
			}
            break;
    }
    
    if (isItemEmpty(pd->activeItem)) {
        removeItemFromInventory(pd->activeItem->slotNum, &(pd->inventory));
        pd->activeItem = &noItem;
    }
    
	return false;
}

bool playerInteract(PlayerData *pd, int x0, int y0, int x1, int y1) {
	Entity * es[eManager.lastSlot[pd->entity.level]];
	int eSize = getEntities(es, pd->entity.level, x0, y0, x1, y1);
	int i;
	for (i = 0; i < eSize; ++i) {
		Entity * ent = es[i];
		if (ent != &(pd->entity)){
             if (ItemVsEntity(pd, pd->activeItem, ent, pd->entity.p.dir)) return true;
        }
	}
	return false;
}

void playerAttack(PlayerData *pd) {
    bool done = false;
	pd->entity.p.attackTimer = 5;
	int yo = -2;
    int range = 12;
	
    //directly using an item
	if(playerUseItem(pd)) return;
    
    //interacting with entities
    switch(pd->entity.p.dir){
        case 0: if(playerInteract(pd, pd->entity.x - 8, pd->entity.y + 4 + yo, pd->entity.x + 8, pd->entity.y + range + yo)) return; break;
        case 1: if(playerInteract(pd, pd->entity.x - 8, pd->entity.y - range + yo, pd->entity.x + 8, pd->entity.y - 4 + yo)) return; break;
        case 2: if(playerInteract(pd, pd->entity.x - range, pd->entity.y - 8 + yo, pd->entity.x - 4, pd->entity.y + 8 + yo)) return; break;
        case 3: if(playerInteract(pd, pd->entity.x + 4, pd->entity.y - 8 + yo, pd->entity.x + range, pd->entity.y + 8 + yo)) return; break;
    }

	int xt = pd->entity.x >> 4;
	int yt = (pd->entity.y + yo) >> 4;
	int r = 12;
	if (pd->entity.p.dir == 0) yt = (pd->entity.y + r + yo) >> 4;
	if (pd->entity.p.dir == 1) yt = (pd->entity.y - r + yo) >> 4;
	if (pd->entity.p.dir == 2) xt = (pd->entity.x - r) >> 4;
	if (pd->entity.p.dir == 3) xt = (pd->entity.x + r) >> 4;

    //interacting with tiles
	if (xt >= 0 && yt >= 0 && xt < 128 && yt < 128) {
        s8 itract = itemTileInteract(getTile(pd->entity.level, xt, yt), pd, pd->activeItem, pd->entity.level, xt, yt, pd->entity.x, pd->entity.y, pd->entity.p.dir);
        if(itract > 0){
		    if(itract==2) pd->entity.p.isCarrying = false;
		    done = true;
        }
		
		if (pd->activeItem != &noItem && isItemEmpty(pd->activeItem)) {
			removeItemFromInventory(pd->activeItem->slotNum, &(pd->inventory));
			pd->activeItem = &noItem;
		}
	}
	
	if(done) return;
    
    //breaking tiles
    if (pd->activeItem == &noItem || pd->activeItem->id == TOOL_SWORD || pd->activeItem->id == TOOL_AXE) {
        if (xt >= 0 && yt >= 0 && xt < 128 && 128) {
            playerHurtTile(pd, getTile(pd->entity.level, xt, yt), pd->entity.level, xt, yt, (rand()%3) + 1, pd->entity.p.dir);
        }
    }
}

bool playerUseArea(PlayerData *pd, int x0, int y0, int x1, int y1) {
	Entity * entities[eManager.lastSlot[pd->entity.level]];
	int i;
    int ae = getEntities(entities, pd->entity.level, x0, y0, x1, y1);
	for(i = 0; i < ae; ++i){ 
        if(useEntity(pd, entities[i])) return true;
    }
	return false;
}

bool playerUse(PlayerData *pd) {
	int yo = -2;
	if (pd->entity.p.dir == 0 && playerUseArea(pd, pd->entity.x - 8, pd->entity.y + 4 + yo, pd->entity.x + 8, pd->entity.y + 12 + yo)) return true;
	if (pd->entity.p.dir == 1 && playerUseArea(pd, pd->entity.x - 8, pd->entity.y - 12 + yo, pd->entity.x + 8, pd->entity.y - 4 + yo)) return true;
	if (pd->entity.p.dir == 3 && playerUseArea(pd, pd->entity.x + 4, pd->entity.y - 8 + yo, pd->entity.x + 12, pd->entity.y + 8 + yo)) return true;
	if (pd->entity.p.dir == 2 && playerUseArea(pd, pd->entity.x - 12, pd->entity.y - 8 + yo, pd->entity.x - 4, pd->entity.y + 8 + yo)) return true;
	return false;
}

void tickPlayer(PlayerData *pd, bool inmenu) {
    if (pd->entity.p.isDead) return;
    
    //invincibility time
    if (pd->entity.hurtTime > 0) pd->entity.hurtTime--;
    
    //stamina recharging
    bool swimming = isWater(pd->entity.level, pd->entity.x>>4, pd->entity.y>>4);
    if (pd->entity.p.stamina <= 0 && pd->entity.p.staminaRechargeDelay == 0 && pd->entity.p.staminaRecharge == 0) {
		pd->entity.p.staminaRechargeDelay = 40;
	}

	if (pd->entity.p.staminaRechargeDelay > 0) {
		--pd->entity.p.staminaRechargeDelay;
	}

	if (pd->entity.p.staminaRechargeDelay == 0) {
		++pd->entity.p.staminaRecharge;
		if (swimming) pd->entity.p.staminaRecharge = 0;
		
		while (pd->entity.p.staminaRecharge > 10) {
			pd->entity.p.staminaRecharge -= 10;
			if (pd->entity.p.stamina < 10) ++pd->entity.p.stamina;
		}
	}
    
    if(!inmenu) {
        if(!pd->sprite.choosen) {
            pd->ingameMenu = MENU_CHARACTER_CUSTOMIZE;
            pd->ingameMenuSelection = 0;
            return;
        }
        
        //movement
        pd->entity.p.ax = 0;
        pd->entity.p.ay = 0;
        
        if (pd->inputs.k_left.down){
            pd->entity.p.ax -= 1;
            pd->entity.p.dir = 2;
            ++pd->entity.p.walkDist;
        }
        if (pd->inputs.k_right.down){
            pd->entity.p.ax += 1;
            pd->entity.p.dir = 3;
            ++pd->entity.p.walkDist;
        }
        if (pd->inputs.k_up.down){
            pd->entity.p.ay -= 1;
            pd->entity.p.dir = 1;
            ++pd->entity.p.walkDist;
        }
        if (pd->inputs.k_down.down){
            pd->entity.p.ay += 1;
            pd->entity.p.dir = 0;
            ++pd->entity.p.walkDist;
        }
        if (pd->entity.p.staminaRechargeDelay % 2 == 0) moveMob(&(pd->entity), pd->entity.p.ax, pd->entity.p.ay);
        
        //"pausing", TODO: since multiplayer this will no longer pause
        if (pd->inputs.k_pause.clicked){
            pd->ingameMenuSelection = 0;
            pd->ingameMenu = MENU_PAUSED; 
        }
        
        //attacking
        if(pd->inputs.k_attack.clicked){
            if (pd->entity.p.stamina != 0) {
                if(!TESTGODMODE) pd->entity.p.stamina--;
                pd->entity.p.staminaRecharge = 0;
                
                playerAttack(pd);
            }
        }
        
        if (pd->inputs.k_menu.clicked){ 
            pd->ingameMenuInvSel = 0;
            if(!playerUse(pd)) pd->ingameMenu = MENU_INVENTORY; 
        }
    }
    
    //swimming stamina and drowning
	if (swimming && pd->entity.p.swimTimer % 60 == 0) {
		if (pd->entity.p.stamina > 0) {
			if(!TESTGODMODE) --pd->entity.p.stamina;
		} else {
		    hurtEntity(&(pd->entity), 1, -1, 0xFFAF00FF, NULL);
		}
	}
    
    if(isWater(pd->entity.level, pd->entity.x>>4, pd->entity.y>>4)) ++pd->entity.p.swimTimer;
    if(pd->entity.p.attackTimer > 0) --pd->entity.p.attackTimer;
	
	//TODO - maybe move to own function
	//Update Minimap
	int xp;
	int yp;
	for(xp = (pd->entity.x>>4)-5; xp<(pd->entity.x>>4)+5; ++xp) {
		for(yp = (pd->entity.y>>4)-5; yp<(pd->entity.y>>4)+5; ++yp) {
			if(xp>=0 && xp<128 && yp>=0 && yp<128) {
				if(!getMinimapVisible(pd, pd->entity.level, xp, yp)) {
					setMinimapVisible(pd, pd->entity.level, xp, yp, true);
				}
			}
		}
	}
}

void playerSetActiveItem(PlayerData *pd, Item *item) {
	pd->activeItem = item; 
    if(pd->activeItem->id > 27 && pd->activeItem->id < 51) pd->entity.p.isCarrying = true;
    else pd->entity.p.isCarrying = false;
}

bool playerUseEnergy(PlayerData *pd, int amount) {
    if(TESTGODMODE) return true;
    if(amount > pd->entity.p.stamina) return false;
    pd->entity.p.stamina -= amount;
    return true;
}

void playerHeal(PlayerData *pd, int amount) {
    pd->entity.p.health += amount;
    if(pd->entity.p.health > 10) pd->entity.p.health = 10;
    char healText[11];
    sprintf(healText, "%d", amount);
    addEntityToList(newTextParticleEntity(healText,0xFF00FF00, pd->entity.x, pd->entity.y, pd->entity.level), &eManager);
}

void playerSpawn(PlayerData *pd) {
    while(true){
        int rx = rand()%128;
        int ry = rand()%128;
        if(getTile(pd->entity.level, rx, ry) == TILE_GRASS){
            pd->entity.x = (rx << 4) + 8;
            pd->entity.y = (ry << 4) + 8;
            pd->isSpawned = true;
            break;    
        }
    }
}
