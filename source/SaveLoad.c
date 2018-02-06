#include "SaveLoad.h"

#include "ZipHelper.h"

bool entityIsImportant(Entity * e){
    switch(e->type){
        case ENTITY_AIRWIZARD:
        case ENTITY_SLIME:
        case ENTITY_ZOMBIE:
		case ENTITY_SKELETON:
		case ENTITY_KNIGHT:
        case ENTITY_ITEM:
        case ENTITY_FURNITURE:
		case ENTITY_PASSIVE:
		case ENTITY_GLOWWORM:
		case ENTITY_DRAGON:
        case ENTITY_NPC:
            return true;
        default:
            return false;
    }
}

s16 calculateImportantEntites(EntityManager * eManager, int level){
    int i;
    s16 count = 0;
    for(i = 0; i < eManager->lastSlot[level]; ++i){
        if(entityIsImportant(&eManager->entities[level][i])){
            count++;
        }
    }
    return count;
}

//helper methods
char **files;
int fileCount;

void saveTrackFileReset() {
    if(files!=NULL) {
        for(int i=0; i<fileCount; i++) {
            free(files[i]);
        }
        free(files);
    }
    
    files = NULL;
    fileCount = 0;
}

int saveTrackFile(char *filename) {
    //test if entry allready present
    for(int i=0; i<fileCount; i++) {
        if(strcmp(filename, files[i])==0) {
            return 0;
        }
    }
    
    //add new entry
    fileCount++;
    char **newFiles = realloc(files, fileCount*sizeof(char*));
    if(!newFiles) {
        for(int i=0; i<fileCount-1; i++) {
            free(files[i]);
        }
        free(files);
        files = NULL;
        return 1;
    }
    
    files = newFiles;
    files[fileCount-1] = malloc(strlen(filename)+1);
    strcpy(files[fileCount-1], filename);
    return 0;
}

void saveDeleteTrackedFiles() {
    for(int i=0; i<fileCount; i++) {
        remove(files[i]);
    }
}

bool saveFileCopy(char *target, char*source) {
    char buffer[SAVE_COPYBUFFER_SIZE];
    
    FILE *in = fopen(source, "rb");
    if(in==NULL) {
        return false;
    }
    FILE *out = fopen(target, "wb");
    if(out==NULL) {
        fclose(out);
        return false;
    }
    
    size_t size;
    do {
        size = fread(buffer, 1, SAVE_COPYBUFFER_SIZE, in);
        
        if(size>0) {
            fwrite(buffer, 1, size, out);
        }
    } while(size>0);
    
    fclose(in);
    fclose(out);
    
    return true;
}

//internal save methods
void saveInventory(Inventory *inv, EntityManager *eManager, FILE *file) {
    fwrite(&inv->lastSlot, sizeof(s16), 1, file); // write amount of items in inventory;
    for(int j = 0; j < inv->lastSlot; ++j) {
        fwrite(&(inv->items[j].id), sizeof(s16), 1, file); // write ID of item
        fwrite(&(inv->items[j].countLevel), sizeof(s16), 1, file); // write count/level of item
        fwrite(&(inv->items[j].onlyOne), sizeof(bool), 1, file);
        if(inv->items[j].id == ITEM_CHEST){
            int invIndex = inv->items[j].chestPtr - eManager->invs;
            fwrite(&invIndex, sizeof(int), 1, file);
        }
    }
}

void saveWorldInternal(char *filename, EntityManager *eManager, WorldData *worldData) {
    FILE * file = fopen(filename, "wb"); //TODO: should be checked
    
    int i, j;
    
    //write savefile version
    int version = SAVE_VERSION;
    fwrite(&version, sizeof(int), 1, file);
    
    // Inventory Data
    fwrite(&eManager->nextInv, sizeof(s16), 1, file); // write amount of inventories.
    for(i = 0; i < eManager->nextInv; ++i) {
        saveInventory(&(eManager->invs[i]), eManager, file);
    }
    
    // Entity Data
    for(i = 0; i < 5; ++i) { //for every level (except dungeon of course)
        int amount = calculateImportantEntites(eManager,i);
        fwrite(&amount, sizeof(s16), 1, file); // read amount of entities in level.
        for(j = 0; j < eManager->lastSlot[i]; ++j){
            if(!entityIsImportant(&eManager->entities[i][j])) continue;
            
            fwrite(&eManager->entities[i][j].type, sizeof(s16), 1, file); // write entity's type ID
            fwrite(&eManager->entities[i][j].x, sizeof(s16), 1, file); // write entity's x coordinate
            fwrite(&eManager->entities[i][j].y, sizeof(s16), 1, file); // write entity's y coordinate
            switch(eManager->entities[i][j].type){
                case ENTITY_AIRWIZARD:
                    fwrite(&eManager->entities[i][j].wizard.health, sizeof(s16), 1, file);
                    break;
                case ENTITY_SLIME:
                    fwrite(&eManager->entities[i][j].slime.health, sizeof(s16), 1, file);
                    fwrite(&eManager->entities[i][j].slime.lvl, sizeof(s8), 1, file);
                    break;
                case ENTITY_ZOMBIE:
				case ENTITY_SKELETON:
				case ENTITY_KNIGHT:
                    fwrite(&eManager->entities[i][j].hostile.health, sizeof(s16), 1, file);
                    fwrite(&eManager->entities[i][j].hostile.lvl, sizeof(s8), 1, file);
                    break;
                case ENTITY_ITEM:
                    fwrite(&eManager->entities[i][j].entityItem.item.id, sizeof(s16), 1, file);
                    fwrite(&eManager->entities[i][j].entityItem.item.countLevel, sizeof(s16), 1, file);
                    fwrite(&eManager->entities[i][j].entityItem.age, sizeof(s16), 1, file);
                    break;
                case ENTITY_FURNITURE:
                    fwrite(&eManager->entities[i][j].entityFurniture.itemID, sizeof(s16), 1, file);
                    int invIndex = eManager->entities[i][j].entityFurniture.inv - eManager->invs;
                    fwrite(&invIndex, sizeof(int), 1, file);
                    break;
				case ENTITY_PASSIVE:
					fwrite(&eManager->entities[i][j].passive.health, sizeof(s16), 1, file);
                    fwrite(&eManager->entities[i][j].passive.mtype, sizeof(u8), 1, file);
                    break;
				case ENTITY_DRAGON:
                    fwrite(&eManager->entities[i][j].dragon.health, sizeof(s16), 1, file);
                    break;
                case ENTITY_NPC:
                    fwrite(&eManager->entities[i][j].npc.type, sizeof(u8), 1, file);
                    break;
            }
        }
    }
    
    // Day/season Data
    fwrite(&worldData->daytime, sizeof(u16), 1, file);
	fwrite(&worldData->day, sizeof(int), 1, file);
	fwrite(&worldData->season, sizeof(u8), 1, file);
    fwrite(&worldData->rain, sizeof(bool), 1, file);
    
    // Compass Data
    fwrite(worldData->compassData, sizeof(u8), 6*3, file); //x,y of choosen stair and count per level
    
    // Map Data
	//Don't write or load dungeon, so only first 5 levels not 6
    fwrite(worldData->map, sizeof(u8), 128*128*5, file); // Map Tile IDs, 128*128*5 bytes = 80KB
    fwrite(worldData->data, sizeof(u8), 128*128*5, file); // Map Tile Data (Damage done to trees/rocks, age of wheat & saplings, etc). 80KB
    
    fclose(file);
}

void savePlayerInternal(char *filename, PlayerData *player, EntityManager *eManager) {
    FILE * file = fopen(filename, "wb"); //TODO: should be checked
    
    int i;
    
    //write savefile version
    int version = SAVE_VERSION;
    fwrite(&version, sizeof(int), 1, file);
    
    // basic player info
    fwrite(&player->score, sizeof(int), 1, file);
    fwrite(&player->isSpawned, sizeof(bool), 1, file);
    fwrite(&player->entity.p.hasWonSaved, sizeof(bool), 1, file);
    fwrite(&player->entity.p.health, sizeof(s16), 1, file);
    fwrite(&player->entity.x, sizeof(s16), 1, file);
    fwrite(&player->entity.y, sizeof(s16), 1, file);
    fwrite(&player->entity.level, sizeof(s8), 1, file);
    
    saveInventory(&(player->inventory), eManager, file);
    
    // Sprite info
    fwrite(&(player->sprite.choosen), sizeof(bool), 1, file);
    fwrite(&(player->sprite.legs), sizeof(u8), 1, file);
    fwrite(&(player->sprite.body), sizeof(u8), 1, file);
    fwrite(&(player->sprite.arms), sizeof(u8), 1, file);
    fwrite(&(player->sprite.head), sizeof(u8), 1, file);
    fwrite(&(player->sprite.eyes), sizeof(u8), 1, file);
    
    // Minimap Data
    fwrite(player->minimapData, sizeof(u8), 128*128, file); // Minimap, visibility data 16KB
    
    // Quest Data
    fwrite(&(player->questManager.size), sizeof(int), 1, file);
    for(i = 0; i < player->questManager.size; ++i) {
        fwrite(&(player->questManager.questlines[i].currentQuest), sizeof(int), 1, file);
        fwrite(&(player->questManager.questlines[i].currentQuestDone), sizeof(bool), 1, file);
    }
    
    //Potion Data
    fwrite(&UnderStrengthEffect, sizeof(bool), 1, file);
    fwrite(&UnderSpeedEffect, sizeof(bool), 1, file);
    fwrite(&regening, sizeof(bool), 1, file);
    fwrite(&UnderSwimBreathEffect, sizeof(bool), 1, file);
    fwrite(&player->entity.p.strengthTimer, sizeof(int), 1, file);
    fwrite(&player->entity.p.speedTimer, sizeof(int), 1, file);
    fwrite(&player->entity.p.swimBreathTimer, sizeof(int), 1, file);
    fwrite(&player->entity.p.regenTimer, sizeof(int), 1, file);

    fclose(file);
}

//internal load methods
void loadInventory(Inventory *inv, EntityManager *eManager, FILE *file) {
    fread(&(inv->lastSlot), sizeof(s16), 1, file); // read amount of items in inventory;
    for(int j = 0; j < inv->lastSlot; ++j) {
        fread(&(inv->items[j].id), sizeof(s16), 1, file); // write ID of item
        fread(&(inv->items[j].countLevel), sizeof(s16), 1, file); // write count/level of item
        fread(&(inv->items[j].onlyOne), sizeof(bool), 1, file);
        inv->items[j].invPtr = (int*)inv; // setup Inventory pointer
        inv->items[j].slotNum = j; // setup slot number
        if(inv->items[j].id == ITEM_CHEST){ // for chest item specifically.
            int invIndex; 
            fread(&invIndex, sizeof(int), 1, file);
            inv->items[j].chestPtr = (Inventory*)&eManager->invs[invIndex]; // setup chest inventory pointer.
        }
    }
}

void loadWorldInternal(char *filename, EntityManager *eManager, WorldData *worldData) {
    FILE * file = fopen(filename, "rb"); //TODO: should be checked
    
    int i, j;
    
    //read savefile version
    int version;
    fread(&version, sizeof(int), 1, file);
    
    // Inventory Data
    fread(&eManager->nextInv, sizeof(s16), 1, file);
    for(i = 0; i < eManager->nextInv; ++i) {
        loadInventory(&(eManager->invs[i]), eManager, file);
    }
    
    // Entity Data
    for(i = 0; i < 5; ++i){
        fread(&eManager->lastSlot[i], sizeof(s16), 1, file); // read amount of entities in level.
        for(j = 0; j < eManager->lastSlot[i]; ++j){
            fread(&eManager->entities[i][j].type, sizeof(s16), 1, file); // read entity's type ID
            fread(&eManager->entities[i][j].x, sizeof(s16), 1, file); // read entity's x coordinate
            fread(&eManager->entities[i][j].y, sizeof(s16), 1, file); // read entity's y coordinate
            eManager->entities[i][j].slotNum = j;
            switch(eManager->entities[i][j].type){
                case ENTITY_SMASHPARTICLE:
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].smashParticle.age = 300;
                    eManager->entities[i][j].canPass = true;
                    break;
                case ENTITY_TEXTPARTICLE:
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].canPass = true;
                    eManager->entities[i][j].textParticle.age = 59;
                    eManager->entities[i][j].textParticle.text = NULL;
                    eManager->entities[i][j].textParticle.xx = eManager->entities[i][j].x;
                    eManager->entities[i][j].textParticle.yy = eManager->entities[i][j].y;
                    eManager->entities[i][j].textParticle.zz = 2;
                    eManager->entities[i][j].textParticle.xa = 0;
                    eManager->entities[i][j].textParticle.ya = 0;
                    eManager->entities[i][j].textParticle.za = 0;
                    break;
                case ENTITY_SPARK:
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].spark.age = 300;
                    break;
                case ENTITY_AIRWIZARD:
                    fread(&eManager->entities[i][j].wizard.health, sizeof(s16), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].wizard.dir = 0;
                    eManager->entities[i][j].wizard.attackDelay = 0;
                    eManager->entities[i][j].wizard.attackTime = 0;
                    eManager->entities[i][j].wizard.attackType = 0;
                    eManager->entities[i][j].wizard.xa = 0;
                    eManager->entities[i][j].wizard.ya = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = true;
                    break;
                case ENTITY_SLIME:
                    fread(&eManager->entities[i][j].slime.health, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].slime.lvl, sizeof(s8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].slime.xa = 0;
                    eManager->entities[i][j].slime.ya = 0;
                    eManager->entities[i][j].slime.dir = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    switch(eManager->entities[i][j].slime.lvl){
                        case 2: eManager->entities[i][j].slime.color = 0xFF8282CC; break;
                        case 3: eManager->entities[i][j].slime.color = 0xFFEFEFEF; break;
                        case 4: eManager->entities[i][j].slime.color = 0xFFAA6262; break;
                        default: eManager->entities[i][j].slime.color = 0xFF95DB95; break;
                    }
                    break;
                case ENTITY_ZOMBIE:
                    fread(&eManager->entities[i][j].hostile.health, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].hostile.lvl, sizeof(s8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].hostile.dir = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    switch(eManager->entities[i][j].hostile.lvl){
                        case 2: eManager->entities[i][j].hostile.color = 0xFF8282CC; break;
                        case 3: eManager->entities[i][j].hostile.color = 0xFFEFEFEF; break;
                        case 4: eManager->entities[i][j].hostile.color = 0xFFAA6262; break;
                        default: eManager->entities[i][j].hostile.color = 0xFF95DB95; break;
                    }
                    break;
                case ENTITY_SKELETON:
                    fread(&eManager->entities[i][j].hostile.health, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].hostile.lvl, sizeof(s8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].hostile.dir = 0;
                    eManager->entities[i][j].hostile.randAttackTime = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    switch(eManager->entities[i][j].hostile.lvl){
                        case 2: eManager->entities[i][j].hostile.color = 0xFFC4C4C4; break;
                        case 3: eManager->entities[i][j].hostile.color = 0xFFA0A0A0; break;
                        case 4: eManager->entities[i][j].hostile.color = 0xFF7A7A7A; break;
                        default: eManager->entities[i][j].hostile.color = 0xFFFFFFFF; break;
                    }
                    break;
                case ENTITY_KNIGHT:
                    fread(&eManager->entities[i][j].hostile.health, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].hostile.lvl, sizeof(s8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].hostile.dir = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    switch(eManager->entities[i][j].hostile.lvl){
                        case 2: eManager->entities[i][j].hostile.color = 0xFF0000C6; break;
                        case 3: eManager->entities[i][j].hostile.color = 0xFF00A3C6; break;
                        case 4: eManager->entities[i][j].hostile.color = 0xFF707070; break;
                        default: eManager->entities[i][j].hostile.color = 0xFFFFFFFF; break;
                    }
                    break;
                case ENTITY_ITEM:
                    //eManager->entities[i][j].entityItem.item = newItem(0,0);
                    fread(&eManager->entities[i][j].entityItem.item.id, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].entityItem.item.countLevel, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].entityItem.age, sizeof(s16), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].entityItem.age = 0;
                    eManager->entities[i][j].xr = 3;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    eManager->entities[i][j].entityItem.xx = eManager->entities[i][j].x;
                    eManager->entities[i][j].entityItem.yy = eManager->entities[i][j].y;
                    eManager->entities[i][j].entityItem.zz = 2;
                    eManager->entities[i][j].entityItem.xa = 0;
                    eManager->entities[i][j].entityItem.ya = 0;
                    eManager->entities[i][j].entityItem.za = 0;
                    break;
                case ENTITY_FURNITURE:
                    fread(&eManager->entities[i][j].entityFurniture.itemID, sizeof(s16), 1, file);
                    int invIndex;
                    fread(&invIndex, sizeof(int), 1, file);
                    eManager->entities[i][j].entityFurniture.inv = &eManager->invs[invIndex];
                    eManager->entities[i][j].xr = 3;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    if(eManager->entities[i][j].entityFurniture.itemID == ITEM_LANTERN) eManager->entities[i][j].entityFurniture.r = 8;
                    break;
                case ENTITY_PASSIVE:
                    fread(&eManager->entities[i][j].passive.health, sizeof(s16), 1, file);
                    fread(&eManager->entities[i][j].passive.mtype, sizeof(u8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].passive.dir = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    break;
                case ENTITY_GLOWWORM:
                    eManager->entities[i][j].glowworm.xa = 0;
                    eManager->entities[i][j].glowworm.ya = 0;
                    eManager->entities[i][j].glowworm.randWalkTime = 0;
                    eManager->entities[i][j].glowworm.waitTime = 0;
                    break;
                case ENTITY_DRAGON:
                    fread(&eManager->entities[i][j].dragon.health, sizeof(s16), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].dragon.dir = 0;
                    eManager->entities[i][j].dragon.attackDelay = 0;
                    eManager->entities[i][j].dragon.attackTime = 0;
                    eManager->entities[i][j].dragon.attackType = 0;
                    eManager->entities[i][j].dragon.animTimer = 0;
                    eManager->entities[i][j].dragon.xa = 0;
                    eManager->entities[i][j].dragon.ya = 0;
                    eManager->entities[i][j].xr = 8;
                    eManager->entities[i][j].yr = 8;
                    eManager->entities[i][j].canPass = true;
                    break;
                case ENTITY_NPC:
                    fread(&eManager->entities[i][j].npc.type, sizeof(u8), 1, file);
                    eManager->entities[i][j].level = i;
                    eManager->entities[i][j].hurtTime = 0;
                    eManager->entities[i][j].xKnockback = 0;
                    eManager->entities[i][j].yKnockback = 0;
                    eManager->entities[i][j].xr = 4;
                    eManager->entities[i][j].yr = 3;
                    eManager->entities[i][j].canPass = false;
                    break;
            }
        }
    }
    
    // Day/season Data
    fread(&worldData->daytime, sizeof(u16), 1, file);
	fread(&worldData->day, sizeof(int), 1, file);
	fread(&worldData->season, sizeof(u8), 1, file);
    fread(&worldData->rain, sizeof(bool), 1, file);
    
    // Compass Data
    fread(worldData->compassData, sizeof(u8), 6*3, file); //x,y of choosen stair and count per level
    
    // Map Data
	//Don't write or load dungeon, so only first 5 levels not 6
    fread(worldData->map, sizeof(u8), 128*128*5, file); // Map Tile IDs, 128*128*5 bytes = 80KB
    fread(worldData->data, sizeof(u8), 128*128*5, file); // Map Tile Data (Damage done to trees/rocks, age of wheat & saplings, etc). 80KB
    
    fclose(file);
}

void loadPlayerInternal(char *filename, PlayerData *player, EntityManager *eManager) {
    FILE * file = fopen(filename, "rb"); //TODO: should be checked
    
    int i;
    
    //read savefile version
    int version;
    fread(&version, sizeof(int), 1, file);
    
    // basic player info
    fread(&player->score, sizeof(int), 1, file);
    fread(&player->isSpawned, sizeof(bool), 1, file);
    fread(&player->entity.p.hasWonSaved, sizeof(bool), 1, file);
    fread(&player->entity.p.health, sizeof(s16), 1, file);
    fread(&player->entity.x, sizeof(s16), 1, file);
    fread(&player->entity.y, sizeof(s16), 1, file);
    fread(&player->entity.level, sizeof(s8), 1, file);
    
    loadInventory(&(player->inventory), eManager, file);
    
    // Sprite info
    fread(&(player->sprite.choosen), sizeof(bool), 1, file);
    fread(&(player->sprite.legs), sizeof(u8), 1, file);
    fread(&(player->sprite.body), sizeof(u8), 1, file);
    fread(&(player->sprite.arms), sizeof(u8), 1, file);
    fread(&(player->sprite.head), sizeof(u8), 1, file);
    fread(&(player->sprite.eyes), sizeof(u8), 1, file);
    
    // Minimap Data
    fread(player->minimapData, sizeof(u8), 128*128, file); // Minimap, visibility data 16KB
    
    // Quest Data
    fread(&(player->questManager.size), sizeof(int), 1, file);
    for(i = 0; i < player->questManager.size; ++i) {
        fread(&(player->questManager.questlines[i].currentQuest), sizeof(int), 1, file);
        fread(&(player->questManager.questlines[i].currentQuestDone), sizeof(bool), 1, file);
    }
	
    //Potion Data
    fread(&UnderStrengthEffect, sizeof(bool), 1, file);
    fread(&UnderSpeedEffect, sizeof(bool), 1, file);
    fread(&regening, sizeof(bool), 1, file);
    fread(&UnderSwimBreathEffect, sizeof(bool), 1, file);
    fread(&player->entity.p.strengthTimer, sizeof(int), 1, file);
    fread(&player->entity.p.speedTimer, sizeof(int), 1, file);
    fread(&player->entity.p.swimBreathTimer, sizeof(int), 1, file);
    fread(&player->entity.p.regenTimer, sizeof(int), 1, file);
    
    fclose(file);
}


bool saveWorld(char *filename, EntityManager *eManager, WorldData *worldData, PlayerData *players, int playerCount) {
    //check if old save file exists
    bool exists = false;
    FILE *testFile = fopen(filename, "rb");
    if(testFile) {
        fclose(testFile);
        exists = true;
    }
    
    saveTrackFileReset();
    
    if(exists) {
        //create backup copy
        char *filenameBackup = malloc(sizeof(filename)+4+1);
        if(filenameBackup==NULL) {
            return false;
        }
        strcpy(filenameBackup, filename);
        strcat(filenameBackup, ".bak");
        if(!saveFileCopy(filenameBackup, filename)) {
            return false;
        }
    
        //extract files and keep track of references
        if(unzipAndLoad(filename, &saveTrackFile, SAVE_COMMENT, ZIPHELPER_KEEP_FILES)!=0) {
            saveDeleteTrackedFiles();
            return false;
        }
        
        remove(filename);
    }
    
    //save world data
    saveWorldInternal("main.wld", eManager, worldData);
    saveTrackFile("main.wld");
    
    //save player data of active players
    for(int i=0; i<playerCount; i++) {
        char playerFilename[50];
        playerFilename[0] = '\0';
        sprintf(playerFilename, "%lu.plr", players[i].id);
        
        savePlayerInternal(playerFilename, players+i, eManager);
        saveTrackFile(playerFilename);
    }
    
    //zip all tracked files
    if(zipFiles(filename, files, fileCount, ZIPHELPER_REPLACE, SAVE_COMMENT)!=0) {
        remove(filename);
    }
    
    saveDeleteTrackedFiles();
    
    return true;
}

bool loadHadWorld;
EntityManager *loadEManager;
WorldData *loadWorldData;
PlayerData *loadPlayers;
int loadPlayerCount;

int loadFile(char *filename) {
    //load world
    if(strcmp(filename, "main.wld")==0) {
        loadWorldInternal(filename, loadEManager, loadWorldData);
        loadHadWorld = true;
    }
  
    //load player data of active players
    for(int i=0; i<playerCount; i++) {
        char playerFilename[50];
        playerFilename[0] = '\0';
        sprintf(playerFilename, "%lu.plr", players[i].id);
        
        if(strcmp(filename, playerFilename)==0) {
            loadPlayerInternal(filename, loadPlayers+i, loadEManager);
        }
    }
  
    return 0;
}

bool loadWorld(char *filename, EntityManager *eManager, WorldData *worldData, PlayerData *players, int playerCount) {
    //check if save file exists
    bool exists = false;
    FILE *testFile = fopen(filename, "rb");
    if(testFile) {
        fclose(testFile);
        exists = true;
    }
    if(!exists) return false;
    
    loadHadWorld = false;
    loadEManager = eManager;
    loadWorldData = worldData;
    loadPlayers = players;
    loadPlayerCount = playerCount;
    
    //extract files
    if(unzipAndLoad(filename, &loadFile, SAVE_COMMENT, ZIPHELPER_CLEANUP_FILES)!=0) {
        return false;
    }
    
    if(!loadHadWorld) {
        return false;
    }
    
    return true;
}
