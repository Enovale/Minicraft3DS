#include "Menu.h"

#include "PacketHandler.h"
#include "SaveLoad.h"

char options[][12] = {"Start Game", "Host Game", "Join Game", "How To Play", "Settings", "About", "Exit"};
char keybOptions[][24] = {"Exit and Save", "Exit and Don't save","Reset to default"};
char setOptions[][24] = {"Rebind Buttons", "Texture packs", "Test Features:   ", "N3DS Speedup:   ", "Return to title"};

// Rebind buttons menu (Settings)
int keys[] = {
    KEY_A,KEY_B,KEY_X,KEY_Y,
    KEY_CPAD_UP,KEY_CPAD_DOWN,KEY_CPAD_LEFT,KEY_CPAD_RIGHT,
    KEY_DUP, KEY_DDOWN, KEY_DLEFT, KEY_DRIGHT, 
    KEY_CSTICK_UP,KEY_CSTICK_DOWN,KEY_CSTICK_LEFT,KEY_CSTICK_RIGHT,
    KEY_L,KEY_R,KEY_ZL,KEY_ZR,
    KEY_START,KEY_SELECT
};
int keyProp[12] = {[0 ... 11] = 0};
bool areYouSure = false;
bool areYouSureSave = false;
bool bindOpt = false;
bool left = false;
bool selBut = false;
s8 errorBut = -1;
s8 curSaveSel = 0;
int menuScanTimer = 0;

// Load Game Menu (Start Game)
char fileNames[1000][256];
int fileScore[1000];
bool fileWin[1000];
s16 worldFileCount = 0;
bool enteringName = false;
s8 touchDelay = 0;
bool isTouching = false;
int touchX = 0, touchY = 0, touchW = 0, touchH = 0;
s8 errorFileName = 0;
bool toMultiplayer;

// Load Texturepacks Menu
char tpFileNames[1000][256];
char tpFileComment[1000][60];
s16 tpFileCount = 0;
s8 isLoadingTP = 0;

void readFiles(){
    memset(&fileNames, 0, sizeof(fileNames)); // reset fileNames
    worldFileCount = 0;
    DIR * d;
    struct dirent * dir;
    d = opendir(".");
    if (d){
        while ((dir = readdir(d)) != NULL) {
            if (strncmp(dir->d_name+strlen(dir->d_name)-4, ".msv", 4) == 0) { // Check if filename contains ".msv"
                strncpy(fileNames[worldFileCount], dir->d_name, strlen(dir->d_name)-4);
                //TODO: This no longer works, update for new format:
                //FILE * file = fopen(dir->d_name, "rb");
                //fread(&fileScore[worldFileCount],sizeof(int), 1, file);
                //fread(&fileWin[worldFileCount],sizeof(bool), 1, file);
                //fclose(file);
                fileScore[worldFileCount] = 0;
                fileWin[worldFileCount] = false;
                
                ++worldFileCount;
            }
        }
        closedir(d);
    }
}

void readTPFiles(){
    memset(&tpFileNames, 0, sizeof(tpFileNames)); // reset tp fileNames
    memset(&tpFileComment, 0, sizeof(tpFileComment)); // reset zip comments
    tpFileCount = 1; // 0 = default.
    DIR * d;
    struct dirent * dir;
    d = opendir("./texturepacks/");
    if (d){
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".zip") != NULL) { // Check if filename contains ".zip"
                strncpy(tpFileNames[tpFileCount], dir->d_name, strlen(dir->d_name)-4);
                
                char fullDirName[256];
                sprintf(fullDirName,"./texturepacks/%s",dir->d_name);
                //int err = 
                getTexturePackComment(fullDirName, tpFileComment[tpFileCount]);
                /*
                if(err > 0){
                    char errorText[10];    
                    sprintf(errorText,"err:%d",err);
                    strncpy(tpFileComment[tpFileCount], errorText, strlen(errorText));
                }*/
                ++tpFileCount;
            }
        }
        closedir(d);
    }
}

s8 checkFileNameForErrors(){
    int length = strlen(fileNames[worldFileCount]);
    if(length < 1)return 1; // Error: Length cannot be 0.
    int i;
    bool isGood = false;
    for(i=0; i < length; ++i){ if(isalnum((int)fileNames[worldFileCount][i])) isGood = true; }
    if(!isGood) return 2; // Error: Filename must contain atleast one letter or number.
    
    DIR * d;
    struct dirent * dir;
    d = opendir(".");
    if (d){
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".msv") != NULL) { // Check if filename contains ".msv"
                char cmprFile[256];
                strncpy(cmprFile, dir->d_name, strlen(dir->d_name)-4);
                if(strncmp(fileNames[worldFileCount],cmprFile,strlen(fileNames[worldFileCount])) == 0) return 3; // Error: Filename cannot already exist.
            }
        }
        closedir(d);
    }
    
    return 0; // No errors found!
}

void addToFileName(char * c){
    strncat(fileNames[worldFileCount], c, 1);
}

/* Keypad */
void doTouchButton(){
    int xVal = localInputs.k_touch.px, yVal = localInputs.k_touch.py;
    int strLength = strlen(fileNames[worldFileCount]);
    if(yVal >= 60 && yVal < 80){ // 0 to 9
        if(xVal >= 4 && xVal < 4+16){ touchX = 4; if(strLength < 24)addToFileName("1");}
        else if(xVal >= 36 && xVal < 4+32+16){ touchX = 36; if(strLength < 24)addToFileName("2");}
        else if(xVal >= 68 && xVal < 4+64+16){ touchX = 68; if(strLength < 24)addToFileName("3");}
        else if(xVal >= 100 && xVal < 4+96+16){ touchX = 100; if(strLength < 24)addToFileName("4");}
        else if(xVal >= 132 && xVal < 4+128+16){ touchX = 132; if(strLength < 24)addToFileName("5");}
        else if(xVal >= 164 && xVal < 4+160+16){ touchX = 164; if(strLength < 24)addToFileName("6");}
        else if(xVal >= 196 && xVal < 4+192+16){ touchX = 196; if(strLength < 24)addToFileName("7");}
        else if(xVal >= 228 && xVal < 4+224+16){ touchX = 228; if(strLength < 24)addToFileName("8");}
        else if(xVal >= 260 && xVal < 4+256+16){ touchX = 260; if(strLength < 24)addToFileName("9");}
        else if(xVal >= 292 && xVal < 4+288+16){ touchX = 292; if(strLength < 24)addToFileName("0");}
        else return;
        touchY = 56;
        touchW = 22;
        touchH = 22;
        touchDelay = 6;
        isTouching = true;
    } else if(yVal >= 80 && yVal < 100){ // Q to P
        if(xVal >= 4 && xVal < 4+16){ touchX = 4; if(strLength < 24)addToFileName("Q");}
        else if(xVal >= 36 && xVal < 4+32+16){ touchX = 36; if(strLength < 24)addToFileName("W");}
        else if(xVal >= 68 && xVal < 4+64+16){ touchX = 68; if(strLength < 24)addToFileName("E");}
        else if(xVal >= 100 && xVal < 4+96+16){ touchX = 100; if(strLength < 24)addToFileName("R");}
        else if(xVal >= 132 && xVal < 4+128+16){ touchX = 132; if(strLength < 24)addToFileName("T");}
        else if(xVal >= 164 && xVal < 4+160+16){ touchX = 164; if(strLength < 24)addToFileName("Y");}
        else if(xVal >= 196 && xVal < 4+192+16){ touchX = 196; if(strLength < 24)addToFileName("U");}
        else if(xVal >= 228 && xVal < 4+224+16){ touchX = 228; if(strLength < 24)addToFileName("I");}
        else if(xVal >= 260 && xVal < 4+256+16){ touchX = 260; if(strLength < 24)addToFileName("O");}
        else if(xVal >= 292 && xVal < 4+288+16){ touchX = 292; if(strLength < 24)addToFileName("P");}
        else return;
        touchY = 76;
        touchW = 22;
        touchH = 22;
        touchDelay = 6;
        isTouching = true;
    } else if(yVal >= 100 && yVal < 120){ // A to L
        if(xVal >= 20 && xVal < 36){ touchX = 20; if(strLength < 24)addToFileName("A");}
        else if(xVal >= 52 && xVal < 68){ touchX = 52; if(strLength < 24)addToFileName("S");}
        else if(xVal >= 84 && xVal < 100){ touchX = 84; if(strLength < 24)addToFileName("D");}
        else if(xVal >= 116 && xVal < 132){ touchX = 116; if(strLength < 24)addToFileName("F");}
        else if(xVal >= 148 && xVal < 164){ touchX = 148; if(strLength < 24)addToFileName("G");}
        else if(xVal >= 180 && xVal < 196){ touchX = 180; if(strLength < 24)addToFileName("H");}
        else if(xVal >= 212 && xVal < 230){ touchX = 212; if(strLength < 24)addToFileName("J");}
        else if(xVal >= 244 && xVal < 262){ touchX = 244; if(strLength < 24)addToFileName("K");}
        else if(xVal >= 276 && xVal < 294){ touchX = 276; if(strLength < 24)addToFileName("L");}
        else return;
        touchY = 96;
        touchW = 22;
        touchH = 22;
        touchDelay = 6;
        isTouching = true;
    } else if(yVal >= 120 && yVal < 140){ // Z to M
        if(xVal >= 52 && xVal < 68){ touchX = 52; if(strLength < 24)addToFileName("Z");}
        else if(xVal >= 84 && xVal < 100){ touchX = 84; if(strLength < 24)addToFileName("X");}
        else if(xVal >= 116 && xVal < 132){ touchX = 116; if(strLength < 24)addToFileName("C");}
        else if(xVal >= 148 && xVal < 164){ touchX = 148; if(strLength < 24)addToFileName("V");}
        else if(xVal >= 180 && xVal < 196){ touchX = 180; if(strLength < 24)addToFileName("B");}
        else if(xVal >= 212 && xVal < 230){ touchX = 212; if(strLength < 24)addToFileName("N");}
        else if(xVal >= 244 && xVal < 262){ touchX = 244; if(strLength < 24)addToFileName("M");}
        else return;
        touchY = 116;
        touchW = 22;
        touchH = 22;
        touchDelay = 6;
        isTouching = true;
    } else if(yVal >= 140 && yVal < 160){ // SPACE and BACKSPACE
        if(xVal >= 32 && xVal < 112){ 
            touchX = 32; 
            touchW = 16*5+14;
            if(strLength < 24)addToFileName("_"); // Underscores don't appear in the game.
        }
        else if(xVal >= 148 && xVal < 262){ 
            if(strLength <= 0) return;
            touchX = 148; 
            touchW = 16*9+8;
            fileNames[worldFileCount][strLength-1] = '\0';
        }
        else return;
        touchY = 136;
        touchH = 22;
        touchDelay = 6;
        isTouching = true;
    }
    errorFileName = 0;
}

void switchGameBut(bool left, int buttonID){
    int id;
    for(id = 0; id < 7; ++id){
        if(keyProp[id] & buttonID){
            keyProp[id] ^= buttonID; // Toggle buttonID bit
            if(left){
                int id2 = id -1;
                if (id2 < 0) return;
                keyProp[id2] ^= buttonID;
            } else { 
                int id2 = id+1;
                if (id2 > 6) return;
                keyProp[id2] ^= buttonID;
            }
            return;
        }
    }
    if(left) keyProp[6] ^= buttonID;
    else keyProp[0] ^= buttonID;
    
}
void switchMenuBut(bool left, int buttonID){
    int id;
    for(id = 0; id < 12; ++id){
        if(id > 3 && id < 7) continue;
        if(keyProp[id] & buttonID){
            keyProp[id] ^= buttonID; // Toggle buttonID bit
            if(left){
                int id2 = id - 1;
                if (id2 == 6) id2 = 3;
                if (id2 < 0) return;
                keyProp[id2] ^= buttonID;
            } else { 
                int id2 = id+1;
                if (id2 == 4) id2 = 7;
                if (id2 > 11) return;
                keyProp[id2] ^= buttonID;
            }
            return;
        }
    }
    if(left) keyProp[11] ^= buttonID;
    else keyProp[0] ^= buttonID;
}

s8 checkPropButtons(){
    if(keyProp[0] == 0) return 0;
    if(keyProp[1] == 0) return 1;
    if(keyProp[2] == 0) return 2;
    if(keyProp[3] == 0) return 3;
    if(keyProp[4] == 0) return 4;
    if(keyProp[5] == 0) return 5;
    if(keyProp[6] == 0) return 6;
    if(keyProp[7] == 0) return 7;
    if(keyProp[8] == 0) return 8;
    if(keyProp[9] == 0) return 9;
    if(keyProp[10] == 0) return 10;
    if(keyProp[11] == 0) return 11;
    return -1;
}

bool menuHasMapLoaded = false;
float mxscr = 400;
float myscr = 400;
float menuxa = 0;
float menuya = 0;
void initMenus() {
	readFiles();
	
	if(worldFileCount>0) {
		memset(&currentFileName, 0, 255); // reset currentFileName
        sprintf(currentFileName,"%s.msv",fileNames[currentSelection]);
		
		initBGMap = 1;
	} else {
		initBGMap = 2;
	}
	
	menuHasMapLoaded = true;
    while(menuxa==0) menuxa = (rand()%3 - 1) * 0.25;
	while(menuya==0) menuya = (rand()%3 - 1) * 0.25;
}

Item median;
void tickMenu(int menu){
    switch(menu){
        case MENU_SETTINGS_REBIND:
        if(!bindOpt){
            if(!selBut){
		        if (localInputs.k_up.clicked){ --currentSelection; if(currentSelection < 0)currentSelection=21;}
		        if (localInputs.k_down.clicked){ ++currentSelection; if(currentSelection > 21)currentSelection=0;}
		        if (localInputs.k_left.clicked){ left = true;}
		        if (localInputs.k_right.clicked){ left = false;}
            } else {
                if (localInputs.k_left.clicked){ 
                    if(left)switchGameBut(true,keys[currentSelection]);
                    else switchMenuBut(true,keys[currentSelection]);
                } else if (localInputs.k_right.clicked) { 
                    if(left)switchGameBut(false,keys[currentSelection]);
                    else switchMenuBut(false,keys[currentSelection]);
                }
            }
		    
            if (localInputs.k_accept.clicked) selBut = !selBut;
            if (localInputs.k_decline.clicked){ 
                bindOpt = true;
                curSaveSel = 0;
            }
        } else {
		    if (localInputs.k_up.clicked){ --curSaveSel; if(curSaveSel < 0)curSaveSel=2;}
		    if (localInputs.k_down.clicked){ ++curSaveSel; if(curSaveSel > 2)curSaveSel=0;}
            if (localInputs.k_decline.clicked){ 
                bindOpt = false;
                errorBut = -1;
            }
            if (localInputs.k_accept.clicked){
                switch(curSaveSel){
                    case 0: // Exit and save  
                        if(checkPropButtons() == -1){
                            localInputs.k_up.input = keyProp[0];
                            localInputs.k_down.input = keyProp[1];
                            localInputs.k_left.input = keyProp[2];
                            localInputs.k_right.input = keyProp[3];
                            localInputs.k_attack.input = keyProp[4];
                            localInputs.k_menu.input = keyProp[5];
                            localInputs.k_pause.input = keyProp[6];
                            localInputs.k_accept.input = keyProp[7];
                            localInputs.k_decline.input = keyProp[8];
                            localInputs.k_delete.input = keyProp[9];
                            localInputs.k_menuNext.input = keyProp[10];
                            localInputs.k_menuPrev.input = keyProp[11];
                            
                            FILE *fs=fopen("btnSave.bin","wb");
                            fwrite(keyProp,sizeof(int),12,fs);
                            fclose(fs);
                            
                            currentSelection = 0;
                            currentMenu = MENU_SETTINGS;
                            errorBut = -1;
                        } else errorBut = checkPropButtons();
                        break;
                    case 1: // Exit and DON'T save  
                        currentSelection = 0;
                        currentMenu = MENU_SETTINGS;
                        errorBut = -1;
                        break;
                    case 2: // reset defaults
	                    keyProp[0] = KEY_DUP | KEY_CPAD_UP | KEY_CSTICK_UP;
	                    keyProp[1] = KEY_DDOWN | KEY_CPAD_DOWN | KEY_CSTICK_DOWN;
	                    keyProp[2] = KEY_DLEFT | KEY_CPAD_LEFT | KEY_CSTICK_LEFT;
	                    keyProp[3] = KEY_DRIGHT | KEY_CPAD_RIGHT | KEY_CSTICK_RIGHT;
	                    keyProp[4] = KEY_A | KEY_B | KEY_L | KEY_ZR;
	                    keyProp[5] = KEY_X | KEY_Y | KEY_R | KEY_ZL;
	                    keyProp[6] = KEY_START;
                        keyProp[7] = KEY_A;
                        keyProp[8] = KEY_B;
                        keyProp[9] = KEY_X;
                        keyProp[10] = KEY_R;
                        keyProp[11] = KEY_L;
	                    bindOpt = false;
                        errorBut = -1;
                        break;
                    }
                }
            }
        break;
        
        case MENU_ABOUT:
            if (localInputs.k_decline.clicked) currentMenu = MENU_TITLE;
        break;
		/*
		case MENU_ARMOR:
            if (k_delete.clicked || k_decline.clicked){
                 currentMenu = MENU_NONE;
                 player.p.activeItem = &noItem;
                 player.p.isCarrying = false;
            }
            if (k_accept.clicked){ // Select item from inventory
                if(player.p.inv->lastSlot!=0){
                    median = player.p.inv->items[curInvSel]; // create copy of item.
                    removeItemFromInventory(curInvSel, player.p.inv); // remove original
                    pushItemToInventoryFront(median, player.p.inv); // add copy to front
					playerSetActiveItem(&player.p.inv->items[0]); // active item = copy.
                }
                currentMenu = MENU_NONE;
            }
		    if (k_up.clicked){ --curInvSel; if(curInvSel < 0)curInvSel=player.p.inv->lastSlot-1;}
		    if (k_down.clicked){ ++curInvSel; if(curInvSel > player.p.inv->lastSlot-1)curInvSel=0;}
        break;
		*/
        
        case MENU_LOADGAME:
            if(!enteringName && !areYouSure){ // World select
                if (localInputs.k_decline.clicked){
                    if(toMultiplayer) {
                        currentMenu = MENU_MULTIPLAYER_HOST;
                    } else {
                        currentMenu = MENU_TITLE;
                        currentSelection = 0;
                    }
                }
                if (localInputs.k_up.clicked){ --currentSelection; if(currentSelection < 0)currentSelection = worldFileCount;}
                if (localInputs.k_down.clicked){ ++currentSelection; if(currentSelection > worldFileCount)currentSelection=0;}
            
                if(localInputs.k_delete.clicked){
                    if(currentSelection < worldFileCount) areYouSure = true;
                }
            
                if(localInputs.k_accept.clicked){
                    if(currentSelection == worldFileCount){
                        
                        enteringName = true;
                    } else {
                        memset(&currentFileName, 0, 255); // reset currentFileName
                        sprintf(currentFileName, "%s.msv", fileNames[currentSelection]);
                        playSound(snd_test);
                        if(toMultiplayer) {
                            initMPGame = 2;
                        } else {
                            initGame = 1;
                        }
                        currentMenu = MENU_LOADING;
                    }
                }
            } else if (areYouSure){
                if (localInputs.k_decline.clicked || localInputs.k_delete.clicked) areYouSure = false;
                if (localInputs.k_accept.clicked){
                    sprintf(currentFileName,"%s.msv",fileNames[currentSelection]);
                    remove(currentFileName);
                    readFiles();
                    enteringName = false;
                    areYouSure = false;
                    memset(&currentFileName, 0, 255); // reset currentFileName
                }
            } else { // Enter new world name.
                if(localInputs.k_decline.clicked) enteringName = false;
                if(localInputs.k_accept.clicked && errorFileName == 0){
                    errorFileName = checkFileNameForErrors();
                    if(errorFileName == 0){ // If no errors are found with the filename, then start a new game!
                        memset(&currentFileName, 0, 255); // reset currentFileName
                        sprintf(currentFileName, "%s.msv", fileNames[worldFileCount]);
                        currentMenu = MENU_LOADING;
                        playSound(snd_test);
                        if(toMultiplayer) {
                            initMPGame = 2;
                        } else {
                            initGame = 1;
                        }
                        ++worldFileCount;
                        currentMenu = MENU_LOADING;
                    }
                }
                if((localInputs.k_touch.px != 0 || localInputs.k_touch.py != 0) && touchDelay == 0){ 
                    if(!isTouching)doTouchButton(); 
                }
                else if(localInputs.k_touch.px == 0 || localInputs.k_touch.py == 0) isTouching = false;
                if(touchDelay > 0) --touchDelay;
            }
        break;
        case MENU_SETTINGS_TP:
            
            if (localInputs.k_up.clicked){ --currentSelection; if(currentSelection < 0)currentSelection = tpFileCount-1;}
            if (localInputs.k_down.clicked){ ++currentSelection; if(currentSelection > tpFileCount-1)currentSelection=0;}
            if (localInputs.k_decline.clicked){
                if(isLoadingTP < 1){
                    currentMenu = MENU_SETTINGS;
                    currentSelection = 1;
                }
            }
            if (localInputs.k_accept.clicked){
                
                if(currentSelection > 0){
                    isLoadingTP = 4;
                } else {
	                icons = sfil_load_PNG_buffer(icons2_png, SF2D_PLACE_RAM);
	                reloadColors();
	                font = sfil_load_PNG_buffer(Font_png, SF2D_PLACE_RAM);
	                bottombg = sfil_load_PNG_buffer(bottombg_png, SF2D_PLACE_RAM);
                    currentMenu = MENU_SETTINGS;
                    currentSelection = 1;
                    remove("lastTP.bin");
                }
            }
        break;
        
        case MENU_SETTINGS:
		    if (localInputs.k_up.clicked){ 
                --currentSelection; 
                if(currentSelection == 3 && !((MODEL_3DS & 6) != 0)) --currentSelection; 
                if(currentSelection < 0)currentSelection=4;
            }
		    if (localInputs.k_down.clicked){ 
                ++currentSelection; 
                if(currentSelection == 3 && !((MODEL_3DS & 6) != 0)) ++currentSelection; 
                if(currentSelection > 4)currentSelection=0;
            }
            if(localInputs.k_decline.clicked){
                currentMenu = MENU_TITLE;
                currentSelection = 4;
            }
		    if(localInputs.k_accept.clicked){
                switch(currentSelection){
                    case 0:
                        keyProp[0] = localInputs.k_up.input;
                        keyProp[1] = localInputs.k_down.input;
                        keyProp[2] = localInputs.k_left.input;
                        keyProp[3] = localInputs.k_right.input;
                        keyProp[4] = localInputs.k_attack.input;
                        keyProp[5] = localInputs.k_menu.input;
                        keyProp[6] = localInputs.k_pause.input;
                        keyProp[7] = localInputs.k_accept.input;
                        keyProp[8] = localInputs.k_decline.input;
                        keyProp[9] = localInputs.k_delete.input;
                        keyProp[10] = localInputs.k_menuNext.input;
                        keyProp[11] = localInputs.k_menuPrev.input;
                        left = true;
                        selBut = false;
                        bindOpt = false;
                        currentSelection = 0;
                        currentMenu = MENU_SETTINGS_REBIND;
                        break;
                    case 1:
                        readTPFiles();
                        currentMenu = MENU_SETTINGS_TP;
                        currentSelection = 0;
                        break;
                    case 2:
                        shouldRenderDebug = !shouldRenderDebug; // toggle option
                        break;
                    case 3:
                        if((MODEL_3DS & 6) != 0){ // detect if user is using a New 3DS
                            shouldSpeedup = !shouldSpeedup; // toggle option
                            osSetSpeedupEnable(shouldSpeedup);
                        }
                        break;
                    case 4:
                        if(true){
                            FILE * fset = fopen("settings.bin","wb");
                            fwrite(&shouldRenderDebug,sizeof(bool),1,fset);
                            fwrite(&shouldSpeedup,sizeof(bool),1,fset);
                            fclose(fset);
                        }
                        currentMenu = MENU_TITLE;
                        currentSelection = 2;
                        break;
                }
            }
        break;
        case MENU_TITLE:
			//Map BG
			if(menuHasMapLoaded) {
				mxscr += menuxa;
				myscr += menuya;
				
				if (mxscr < 16) {
					mxscr = 16;
					menuxa = -menuxa;
				} else if (mxscr > 1832) {
					mxscr = 1832;
					menuxa = -menuxa;
				}
				if (myscr < 16) {
					myscr = 16;
					menuya = -menuya;
				} else if (myscr > 1792) {
					myscr = 1792;
					menuya = -menuya;
				}
			}
		
		    if (localInputs.k_up.clicked){ --currentSelection; if(currentSelection < 0)currentSelection=6;}
		    if (localInputs.k_down.clicked){ ++currentSelection; if(currentSelection > 6)currentSelection=0;}
		    
		    if(localInputs.k_accept.clicked){
                switch(currentSelection){
                    case 0:
                        toMultiplayer = false;
                        currentMenu = MENU_LOADGAME;
                        readFiles();
                        currentSelection = 0;
                        enteringName = false;
                        areYouSure = false;
                    break;
                    case 1:
                        if(networkHost()) {
                            toMultiplayer = true;
                            currentMenu = MENU_MULTIPLAYER_HOST;
                            currentSelection = 0;
                        }
                    break;
                    case 2:
                        networkScan();
                        currentMenu = MENU_MULTIPLAYER_JOIN;
                        currentSelection = 0;
                        menuScanTimer = 0;
                    break;
                    case 3:
                        sprintf(pageText,"Page: %d/%d",pageNum+1,maxPageNum+1);
                        currentMenu = MENU_TUTORIAL;
                    break;
                    case 4:
                        currentSelection = 0;
                        currentMenu = MENU_SETTINGS;
                    break;
                    case 5: 
                        currentMenu = MENU_ABOUT;
                    break;
                    case 6: 
                        quitGame = true;
                    break;
                }
                
            }
        break;
        case MENU_TUTORIAL:
            if(localInputs.k_decline.clicked){ 
                currentSelection = 3;
                currentMenu = MENU_TITLE;
            }
            if(localInputs.k_menuNext.clicked){
                if(pageNum < maxPageNum){ 
                    ++pageNum;
                    sprintf(pageText,"Page: %d/%d",pageNum+1,maxPageNum+1);
                }
            }
            if(localInputs.k_menuPrev.clicked){
                if(pageNum > 0){
                    --pageNum;
                    sprintf(pageText,"Page: %d/%d",pageNum+1,maxPageNum+1);
                }
            }
            
        break;
        case MENU_MULTIPLAYER_HOST:
            if (localInputs.k_decline.clicked){
                networkDisconnect();
                
                currentMenu = MENU_TITLE;
                currentSelection = 1;
            }
            
            if(localInputs.k_accept.clicked){
                if(networkGetNodeCount()>1) {
                    currentMenu = MENU_LOADGAME;
                    readFiles();
                    currentSelection = 0;
                    enteringName = false;
                    areYouSure = false;
                }
            }
        break;
        case MENU_MULTIPLAYER_JOIN:
            if(menuScanTimer>0) {
                menuScanTimer--;
            } else {
                networkScan();
                menuScanTimer = 30;
            }
            if(currentSelection >= networkGetScanCount()) currentSelection=networkGetScanCount()-1;
            if(currentSelection < 0) currentSelection = 0;
        
            if (localInputs.k_decline.clicked){
                currentMenu = MENU_TITLE;
                currentSelection = 2;
            }
            if (localInputs.k_up.clicked){ --currentSelection; if(currentSelection < 0) currentSelection = (networkGetScanCount()>0 ? networkGetScanCount()-1 : 0);}
            if (localInputs.k_down.clicked){ ++currentSelection; if(currentSelection >= networkGetScanCount()) currentSelection=0;}
        
            if(localInputs.k_accept.clicked){
                if(networkGetScanCount()!=0) {
                    for(int t=0; t<10; t++) { //try to connect multiple times, because it will not work the first try every time
                        if(networkConnect(currentSelection)) {
                            currentMenu = MENU_MULTIPLAYER_WAIT;
                            currentSelection = 0;
                            break;
                        }
                    }
                }
            }
        break;
        case MENU_MULTIPLAYER_WAIT:
            if (localInputs.k_decline.clicked){
                networkDisconnect();
                
                currentMenu = MENU_TITLE;
                currentSelection = 2;
            }
        break;
    }
    
}

char scoreText[15];

char * getButtonFunctionGame(int key){
    if(keyProp[0] & key) return "Move up";
    if(keyProp[1] & key) return "Move down";
    if(keyProp[2] & key) return "Move left";
    if(keyProp[3] & key) return "Move right";
    if(keyProp[4] & key) return "Attack";
    if(keyProp[5] & key) return "Toggle Menu";
    if(keyProp[6] & key) return "Pause";
    return "Nothing";
}
char * getButtonFunctionMenu(int key){
    if(keyProp[0] & key) return "Up";
    if(keyProp[1] & key) return "Down";
    if(keyProp[2] & key) return "Left";
    if(keyProp[3] & key) return "Right";
    if(keyProp[7] & key) return "Accept";
    if(keyProp[8] & key) return "Decline";
    if(keyProp[9] & key) return "Delete";
    if(keyProp[10] & key) return "Next";
    if(keyProp[11] & key) return "Previous";
    return "Nothing";
}


char guiText0[] = "1 2 3 4 5 6 7 8 9 0";
char guiText1[] = "Q W E R T Y U I O P";
char guiText2[] = "A S D F G H J K L";
char guiText3[] = "Z X C V B N M";
char guiText4[] = " SPACE  BACKSPACE";

void renderMenu(int menu,int xscr,int yscr){
    int i = 0;
    switch(menu){
        case MENU_TUTORIAL:
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				
		        renderTutorialPage(true);
		    sf2d_end_frame();
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);	
				sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
		        renderTutorialPage(false);
		    sf2d_end_frame();
            break;
        case MENU_SETTINGS_TP:
            offsetX = 0;offsetY = (currentSelection * 40) - 48;
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
		        drawText("Texture Packs",122,-16);
		        for(i = 0; i < tpFileCount; ++i){
                    int color = 0xFF923232;
                    char * text = tpFileNames[i];
                    char * cmtText = tpFileComment[i];
                    if(i == 0){
                        text = "Default";
                        cmtText = "Regular look of the game";
                        color = 0xFF921060;
                    }
                    if(i != currentSelection) color &= 0x7FFFFFFF; // Darken color.
                    else if(areYouSure)color = 0xFF1010DF;
                    
                    renderFrame(1,i*5,24,(i*5)+5,color);
                    drawText(text,(400-(strlen(text)*12))/2,i*80+16);
                    
                    if(strlen(cmtText) > 29){
                        char cmtTxt1[30],cmtTxt2[30];
                        strncpy(cmtTxt1, cmtText, 29);
                        strncpy(cmtTxt2, cmtText + 29, strlen(cmtText)-29);
                        drawTextColor(cmtTxt1,(400-(strlen(cmtTxt1)*12))/2,i*80+36,0xFFAFAFAF);
                        drawTextColor(cmtTxt2,(400-(strlen(cmtTxt2)*12))/2,i*80+50,0xFFAFAFAF);
                    } else {
                        drawTextColor(cmtText,(400-(strlen(cmtText)*12))/2,i*80+43,0xFFAFAFAF);
                    }
                }
            offsetX = 0;offsetY = 0;
                if(isLoadingTP > 0){
                    --isLoadingTP;
                    renderFrame(1,5,24,9,0xFF666666);
                    drawTextColor("Loading Texture pack...",(400-(23*12))/2,108,0xFF10FFFF);
                    if(isLoadingTP == 0){
                        char fullDirName[256];
                        sprintf(fullDirName,"texturepacks/%s.zip",tpFileNames[currentSelection]);
                        loadedtp = loadTexturePack(fullDirName);   
                        
                        FILE * fs=fopen("lastTP.bin","w");
                        fprintf(fs,"%s", fullDirName);
                        fclose(fs);
                        
                        currentMenu = MENU_SETTINGS;
                        currentSelection = 1; 
                    }
                }
		    sf2d_end_frame();
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);	
				sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
                drawText("Press   to select", 58, 100);
                renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 128, 98, 1);
                drawText("Press   to return", 58, 150);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
		    sf2d_end_frame();
        break;
        case MENU_LOADGAME:
            sf2d_start_frame(GFX_TOP, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                if(!enteringName){ // World select
                    offsetX = 0;offsetY = (currentSelection * 32) - 48;
                    drawText("Select a file",122,-16);
                    for(i = 0; i < worldFileCount + 1; ++i){
                        int color = 0xFF921020;
                        char * text = fileNames[i];
                        if(i == worldFileCount){
                            text = "Generate New World";
                            color = 0xFF209210;
                        }
                        if(i != currentSelection) color &= 0xFF7F7F7F; // Darken color.
                        else {
                            if(areYouSure)color = 0xFF1010DF;
                        }
                        
                        char scoreText[24];
                        sprintf(scoreText,"Score: %d",fileScore[i]);
                        
                        renderFrame(1,i*4,24,(i*4)+4,color);
                        if(i != worldFileCount){
                            drawText(text,(400-(strlen(text)*12))/2,i*64+12);
                            drawText(scoreText,(400-(strlen(scoreText)*12))/2,i*64+32);
                        } else {
                            drawText(text,(400-(strlen(text)*12))/2,i*64+24);
                        }
                        if(fileWin[i] && i != worldFileCount) render16(18,i*32+8,24,208,0); // Render crown
                    }
                    offsetX = 0;offsetY = 0;
                } else { // Enter new world name.
                    drawText("Enter a name",128,16);
                    drawText(fileNames[worldFileCount],(400-(strlen(fileNames[worldFileCount])*12))/2, 48);
                    
                    if(errorFileName > 0){
                        switch(errorFileName){// Error: Filename cannot already exist.
                            case 1: drawTextColor("ERROR: Length cannot be 0!",(400-26*12)/2,200,0xFF1010AF); break;    
                            case 2: drawTextColor("ERROR: You need Letters/Numbers!",(400-32*12)/2,200,0xFF1010AF); break;    
                            case 3: drawTextColor("ERROR: Filename already exists!",(400-31*12)/2,200,0xFF1010AF); break;    
                        }    
                    }
                }
            sf2d_end_frame();
            sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                if(!enteringName){ // World select
                    if(!areYouSure){
                        drawTextColor("Load World",100,12,0xFF3FFFFF);
                        drawText("Press   or   to scroll", 28, 50);
                        renderButtonIcon(localInputs.k_up.input & -localInputs.k_up.input, 98, 48, 1);
                        renderButtonIcon(localInputs.k_down.input & -localInputs.k_down.input, 160, 48, 1);
                        drawText("Press   to load world", (320-21*12)/2, 100);
                        renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 104, 98, 1);
                        drawText("Press   to return", 58, 150);
                        renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
                        if(currentSelection != worldFileCount){
                            drawText("Press   to delete",(320-17*12)/2, 200);
                            renderButtonIcon(localInputs.k_delete.input & -localInputs.k_delete.input, 128, 198, 1);
                        }
                    } else {
                        drawTextColor("Delete File?",88,12,0xFF3F3FFF);
                        drawText("Press   to confirm", (320-18*12)/2, 100);
                        renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 122, 98, 1);
                        drawText("Press   to return", 58, 150);
                        renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
                    }
                    
                } else { // Draw the "keyboard"
                    drawTextColor("Touch the keypad below",(320-22*12)/2,12,0xFF33FFFF);
                    
                    sf2d_draw_rectangle(0, 50, 320, 110, 0xFF7F7FBF);
                    
                    if(touchDelay > 0){
                        sf2d_draw_rectangle(touchX, touchY, touchW, touchH, 0xFF0000AF);
                    }
                    
                    drawSizedText(guiText0,4, 60, 2);
                    drawSizedText(guiText1,4, 80, 2);
                    drawSizedText(guiText2,12, 100, 2);
                    drawSizedText(guiText3,28, 120, 2);
                    drawSizedText(guiText4,12, 140, 2);
                    
                    drawText("Press   to confirm", (320-18*12)/2, 180);
                    renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 122, 178, 1);
                    drawText("Press   to return", 58, 210);
                    renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 208, 1);
                }
            sf2d_end_frame();
        break;
        case MENU_SETTINGS_REBIND:
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
		        drawTextColor("Rebind Buttons",116,12,0xFF00AFAF);
                drawText("Button",16,32);
                drawText("Game",140,32);
                drawText("Menus",280,32);
		    
                char gameButText[34];
                char menuButText[34];
                    
                for(i = 0; i < 5; ++i){
                    if((currentSelection-2) + i > 21 || (currentSelection-2) + i < 0) continue;
                    renderButtonIcon(keys[(currentSelection-2) + i], 16, (i * 18) + 30, 2);
                    int ccol = 0xFF7F7F7F;
                    
                    sprintf(gameButText,"%s",getButtonFunctionGame(keys[(currentSelection-2) + i]));
                    sprintf(menuButText,"%s",getButtonFunctionMenu(keys[(currentSelection-2) + i]));
                    
                    if(i == 2){ 
                        if(!selBut)ccol = 0xFFFFFFFF;
                        else{ 
                            ccol = 0xFF00FF00;
                            if(left)sprintf(gameButText,"<%s>",getButtonFunctionGame(keys[(currentSelection-2) + i]));
                            else sprintf(menuButText,"<%s>",getButtonFunctionMenu(keys[(currentSelection-2) + i]));
                        }
                    }
                    if(left){
                        drawTextColor(gameButText, 112, (i * 33) + 80, ccol);
                        drawTextColor(menuButText, 280, (i * 33) + 80, 0xFF7F7F7F);
                    } else {
                        drawTextColor(gameButText, 112, (i * 33) + 80, 0xFF7F7F7F);
                        drawTextColor(menuButText, 280, (i * 33) + 80, ccol);
                    }
                }
                if(bindOpt){
                    renderFrame(1,1,24,14,0xFFBF1010);
                    drawTextColor("Save changes?",122,32,0xFF00AFAF);
                    for(i = 2; i >= 0; --i){
                        char* msg = keybOptions[i];
                        u32 color = 0xFF4F4F4F;
                        if(i == curSaveSel) color = 0xFFFFFFFF;
                        drawTextColor(msg,(400 - (strlen(msg) * 12))/2, (i * 24) + 92, color);    
                    }
                    drawText("Press   to return", 98, 190);
                    renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 168, 188, 1);
                    
                    if(errorBut >= 0 && errorBut < 12){
                        char errorText[30];
                        switch(errorBut){
                            case 0: sprintf(errorText, "Error: Missing 'Move up'"); break;
                            case 1: sprintf(errorText, "Error: Missing 'Move down'"); break;
                            case 2: sprintf(errorText, "Error: Missing 'Move right'"); break;
                            case 3: sprintf(errorText, "Error: Missing 'Move left'"); break;
                            case 4: sprintf(errorText, "Error: Missing 'Attack'"); break;
                            case 5: sprintf(errorText, "Error: Missing 'Toggle Menu'"); break;
                            case 6: sprintf(errorText, "Error: Missing 'Pause'"); break;
                            case 7: sprintf(errorText, "Error: Missing 'Accept'"); break;
                            case 8: sprintf(errorText, "Error: Missing 'Decline'"); break;
                            case 9: sprintf(errorText, "Error: Missing 'Delete'"); break;
                            case 10: sprintf(errorText, "Error: Missing 'Next'"); break;
                            case 11: sprintf(errorText, "Error: Missing 'Previous'"); break;
                        }
                        drawTextColor(errorText,(400 - (strlen(errorText) * 12))/2,50,0xFF0000FF);
                    }
                    
                }
		    sf2d_end_frame();
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);	
				sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				
				if(!selBut){
					drawText("Press   to select", 58, 80);
					renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 128, 78, 1);
					drawText("Press   to return", 58, 130);
					renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 128, 1);
				} else {
					drawText("Press   or   to scroll", 28, 50);
					renderButtonIcon(localInputs.k_left.input & -localInputs.k_left.input, 98, 48, 1);
					renderButtonIcon(localInputs.k_right.input & -localInputs.k_right.input, 160, 48, 1);
					drawText("Press   to unselect", 46, 100);
					renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 118, 98, 1);
					drawText("Press   to return", 58, 150);
					renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
				}
		    sf2d_end_frame();
        break;
		
        case MENU_ABOUT:
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
		        drawText("About Minicraft",110,12);
		        drawSizedText("Minicraft was made by Markus Persson for the",24,36,1.0);
		        drawSizedText("22'nd ludum dare competition in december 2011.",16,48,1.0);
		        drawSizedText("it is dedicated to my father. <3",72,60,1.0);
		        drawSizedText("- Markus \"Notch\" Persson",104,76,1.0);
		        
		        drawTextColor("3DS Homebrew Edition",74,120,0xFF00FF00);
		        drawSizedTextColor("This port was made by David Benepe (Davideesk)",16,144,1.0,0xFF00FF00);
		        drawSizedTextColor("just for fun in September/October 2015.",44,156,1.0,0xFF00FF00);
				drawSizedTextColor("Modded by Andre Schweiger (andre111) and ",44,168,1.0,0xFF00FF00);
				drawSizedTextColor("***REMOVED*** ***REMOVED*** (Enova)",71,180,1.0,0xFF00FF00);
		        drawSizedTextColor("TY Notch for creating a fun game to remake!",28,192,1.0,0xFF00FF00);
		    sf2d_end_frame();
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		        sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
				drawTextColor("Special Thanks to:",52,12,0xFF7F7FFF);
		        drawTextColor("Smea",136,50,0xFF2020FF);
		        drawSizedTextColor("for ctrulib",116,70,1.0,0xFF2020FF);
		        drawTextColor("Xerpi",130,100,0xFFFF2020);
		        drawSizedTextColor("for sf2dlib",116,120,1.0,0xFFFF2020);
				drawTextColor("Music from",100,150,0xFF20FF20);
		        drawSizedTextColor("opengameart.org/content/",64,170,1.0,0xFF20FF20);
				drawSizedTextColor("generic-8-bit-jrpg-soundtrack",48,180,1.0,0xFF20FF20);
				
                drawText("Press   to return", 58, 220);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 218, 1);
		    sf2d_end_frame();
        break;
        case MENU_SETTINGS:
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
		        drawText("Settings",(400-(8*12))/2,30);
		        for(i = 4; i >= 0; --i){
                    char* msg = setOptions[i];
                    u32 color = 0xFF7F7F7F;
                    if(i == currentSelection) color = 0xFFFFFFFF;
                    if(i == 2){
                        if(shouldRenderDebug) drawSizedTextColor("On",142, ((8 + i) * 32 - 190) >> 1,2.0, 0xFF00DF00);    
                        else  drawSizedTextColor("Off",142, ((8 + i) * 32 - 190) >> 1,2.0, 0xFF0000DF);   
                    } else if(i == 3){
                        
                        if((MODEL_3DS & 6) != 0){ // detect if user is using a New 3DS
                            if(shouldSpeedup) drawSizedTextColor("On",142, ((8 + i) * 32 - 190) >> 1,2.0, 0xFF00DF00);    
                            else  drawSizedTextColor("Off",142, ((8 + i) * 32 - 190) >> 1,2.0, 0xFF0000DF); 
                        } else {
                            color = 0xFF3F3F3F;
                            drawSizedTextColor("Off",142, ((8 + i) * 32 - 190) >> 1,2.0, 0xFF3F3F3F); 
                        }
                    }
                    drawSizedTextColor(msg,(200 - (strlen(msg) * 8))/2, ((8 + i) * 32 - 190) >> 1,2.0, color);    
                }
		    sf2d_end_frame();
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);	
		        sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
			
				switch(currentSelection){
                    case 0:
                        drawTextColor("Change the controls",(320 - (19 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 1:
                        drawTextColor("Change the game's art",(320 - (21 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 2:
                        drawTextColor("Enable Testing Features.",(320 - (22 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 3:
                        drawTextColor("Use the N3DS 804mhz mode",(320 - (24 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 4:
                        drawTextColor("Back to the titlescreen",(320 - (23 * 12))/2,24,0xFF7FFFFF);
                        break;
                }
                drawText("Press   to select", 58, 100);
                renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 128, 98, 1);
                drawText("Press   to return", 58, 150);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
		    sf2d_end_frame();
        break;
        case MENU_TITLE:
            /* Top Screen */
		    sf2d_start_frame(GFX_TOP, GFX_LEFT);
				sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				//map BG
				if(menuHasMapLoaded) {
					offsetX = (int) mxscr; offsetY = (int) myscr;
						renderBackground(1, (int) mxscr, (int) myscr);
					offsetX = 0; offsetY = 0;
					
					sf2d_draw_rectangle(0, 0, 400, 240, 0xAA0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				}
			
		        renderTitle(76,8);
		    
		        for(i = 6; i >= 0; --i){
                    char* msg = options[i];
                    u32 color = 0xFF7F7F7F;
                    if(i == currentSelection) color = 0xFFFFFFFF;
					drawSizedTextColor(msg,((200 - (strlen(msg) * 8))/2) + 1, (((8 + i) * 20 - 74) >> 1) + 1,2.0, 0xFF000000);   
                    drawSizedTextColor(msg,(200 - (strlen(msg) * 8))/2, ((8 + i) * 20 - 74) >> 1,2.0, color);    
                }
                
		        drawText(versionText,2,225);
		    sf2d_end_frame();
		    
            /* Bottom Screen */
		    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);	
				sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				//map BG
				if(menuHasMapLoaded) {
					offsetX = (int) mxscr + 20; offsetY = (int) myscr + 120;
						renderBackground(1, (int) mxscr + 20, (int) myscr + 120);
					offsetX = 0; offsetY = 0;
					
					sf2d_draw_rectangle(0, 0, 320, 240, 0xAA0C0C0C); //You might think "real" black would be better, but it actually looks better that way
				}
			
			  int startX = 0, startY = 0;// relative coordinates ftw
		        switch(currentSelection){
                    case 0: // "Start Game"
                        break;
                    case 1: // "Host Game"
                        drawTextColor("Host local multiplayer",(320 - (22 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 2: // "Join Game"
                        drawTextColor("Join local multiplayer",(320 - (22 * 12))/2,24,0xFF7FFFFF);
                        break;
                    case 3: // "How To Play"
                        startX = 72;startY = 54;
                        render16(startX,startY,96,208,0);//C-PAD
                        startX = 72;startY = 37;
                        render16(startX,startY-16,16,112,0);//Player
                        render16(startX,startY,112,208,0);//C-PAD up
                        startX = 72;startY = 71;
                        render16(startX,startY+16,0,112,0);//Player
                        render16(startX,startY,144,208,0);//C-PAD down
                        startX = 39;startY = 54;
                        render16(startX,startY,48,112,1);//Player
                        render16(startX+16,startY,128,208,0);//C-PAD left
                        startX = 89;startY = 54;
                        render16(startX+16,startY,48,112,0);//Player
                        render16(startX,startY,160,208,0);//C-PAD right
                        drawTextColor("Learn the basics",64,24,0xFF7FFFFF);
                        break;
                    case 4: // "Settings"
                        drawTextColor("Modify the game's feel",(320 - (22 * 12))/2,24,0xFF7FFFFF);
                        renderc(48,48,0,112,64,32,0);
                        break;
                    case 5: // "About"
                        drawTextColor("Who made this game?",(320 - (19 * 12))/2,24,0xFF7FFFFF);
                        
                        // Secret code ;)
                        //drawSizedText("497420776173206e6f746368",(320 - (24 * 8))/2,80,1);
                        //drawSizedText("506f727465642062792044617669646565736b",(320 - (38 * 8))/2,88,1);
                        //drawSizedText("576879207265616420746869733f",(320 - (28 * 8))/2,96,1);
                        //drawSizedText("596f75207761737465642074696d65",(320 - (30 * 8))/2,104,1);
                        //drawSizedText("4861204861204861204861204861",(320 - (28 * 8))/2,112,1);
                        //drawSizedText("5468652063616b652069732061206c6965",(320 - (34 * 8))/2,120,1);
                        //drawSizedText("4044617669646565736b2074776974746572",(320 - (36 * 8))/2,128,1);
                        //drawSizedText("3533363536333732363537343231",(320 - (28 * 8))/2,136,1);
                        //drawSizedText("4c69617220746578742062656c6f77",(320 - (30 * 8))/2,144,1);
                        //drawSizedText("(Totally not a secret code or anything)",4,160,1);
                         
                        break;
                    case 6: // "Exit"
                        drawTextColor("Exit to the home menu",(320 - (21 * 12))/2,24,0xFF7FFFFF);
                        drawTextColor("(bye-bye)",(320 - (9 * 12))/2,100,0xFF7FFFFF);
                        break;
                }
		    sf2d_end_frame();
        break;
        case MENU_MULTIPLAYER_HOST:
            sf2d_start_frame(GFX_TOP, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                networkUpdateStatus();
                drawText("Connected Players",98,8);
                int j = 0;
                int lastj = 0;
                for(i = 0; i<networkGetNodeCount(); i++) {
                    
                    for(j = lastj+1; j <= UDS_MAXNODES; j++) {
                        if(networkIsNodeConnected(j)) {
                            char * text = malloc((50+8+1) * sizeof(char));
                            memset(text, 0, (50+8+1) * sizeof(char));
                            networkGetNodeName(j, text);
                            
                            drawText(text,(400-(strlen(text)*12))/2,i*26+32);
                            
                            free(text);
                            lastj = j;
                            break;
                        }
                    }
                }
            sf2d_end_frame();
            sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                drawText("Press   to start game", (320-21*12)/2, 100);
                renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 104, 98, 1);
                drawText("Press   to return", 58, 150);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
            sf2d_end_frame();
        break;
        case MENU_MULTIPLAYER_JOIN:
            sf2d_start_frame(GFX_TOP, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                offsetX = 0;offsetY = (currentSelection * 32) - 48;
                drawText("Select a world",122,-16);
                for(i = 0; i < networkGetScanCount(); ++i){
                    int color = 0xFF921020;
                    char * text = malloc((50+8+1) * sizeof(char));
                    memset(text, 0, (50+8+1) * sizeof(char));
                    networkGetScanName(text, i);
                    strcat(text, "'s World");
                    
                    if(i != currentSelection) color &= 0xFF7F7F7F; // Darken color.
                    
                    renderFrame(1,i*4,24,(i*4)+4,color);
                    drawText(text,(400-(strlen(text)*12))/2,i*64+24);
                    
                    free(text);
                }
                offsetX = 0;offsetY = 0;
            sf2d_end_frame();
            sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                drawTextColor("Searching for Worlds",40,12,0xFF3FFFFF);
                drawText("Press   or   to scroll", 28, 50);
                renderButtonIcon(localInputs.k_up.input & -localInputs.k_up.input, 98, 48, 1);
                renderButtonIcon(localInputs.k_down.input & -localInputs.k_down.input, 160, 48, 1);
                drawText("Press   to join world", (320-21*12)/2, 100);
                renderButtonIcon(localInputs.k_accept.input & -localInputs.k_accept.input, 104, 98, 1);
                drawText("Press   to return", 58, 150);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
            sf2d_end_frame();
        break;
        case MENU_MULTIPLAYER_WAIT:
            sf2d_start_frame(GFX_TOP, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                networkUpdateStatus();
                drawText("Connected to",(400-12*12)/2,1*26+32);
                if(networkIsNodeConnected(1)) {
                    char * text = malloc((50+8+1) * sizeof(char));
                    memset(text, 0, (50+8+1) * sizeof(char));
                    networkGetNodeName(1, text);
                    
                    drawText(text,(400-(strlen(text)*12))/2,2*26+32);
                    
                    free(text);
                }
                drawText("Waiting for host to start",(400-25*12)/2,3*26+32);
            sf2d_end_frame();
            sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                drawText("Awaiting game start..", (320-21*12)/2, 100);
                drawText("Press   to return", 58, 150);
                renderButtonIcon(localInputs.k_decline.input & -localInputs.k_decline.input, 128, 148, 1);
            sf2d_end_frame();
        break;
        case MENU_LOADING:
            sf2d_start_frame(GFX_TOP, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
            sf2d_end_frame();
            sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
                
                drawText("Loading game...", (320-15*12)/2, 100);
            sf2d_end_frame();
        break;
    }

}

void menuRenderTilePit(int x,int y,int xt,int yt) {
	render16(x+8,y+8,xt+48,yt,0);
	
	render(x,   y,   xt,   yt,  0);
	render(x+24,y,   xt+8, yt,  0);
	render(x,   y+24,xt,   yt+8,0);
	render(x+24,y+24,xt+8, yt+8,0);
	
	render(x+8, y,   xt+16,yt,  0);
	render(x+16,y,   xt+24,yt,  0);
	render(x+8, y+24,xt+16,yt+8,0);
	render(x+16,y+24,xt+24,yt+8,0);
	
	render(x,   y+8, xt+32,yt,  0);
	render(x,   y+16,xt+32,yt,  0);
	render(x+24,y+8, xt+40,yt,  0);
	render(x+24,y+16,xt+40,yt,  0);
}
