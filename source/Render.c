#include "Render.h"

void render(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 8;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 8;
	}
	sf2d_draw_texture_part_scale(icons, xp << 1, yp << 1, xTile, yTile, 8, 8,
			scaleX, scaleY);
}
void renderb(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits, u32 color) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 8;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 8;
	}
	sf2d_draw_texture_part_scale_blend(icons, xp << 1, yp << 1, xTile, yTile, 8,
			8, scaleX, scaleY, color);
}
void renderr(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits, float rotate) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 8;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 8;
	}
	sf2d_draw_texture_part_rotate_scale(icons, xp << 1, yp << 1, rotate, xTile,
			yTile, 8, 8, scaleX, scaleY);
}
void renderc(s32 xp, s32 yp, u32 xTile, u32 yTile, int sizeX, int sizeY,
		u8 bits) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += sizeX;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += sizeY;
	}
	sf2d_draw_texture_part_scale(icons, xp << 1, yp << 1, xTile, yTile, sizeX,
			sizeY, scaleX, scaleY);
}
void renderbc(s32 xp, s32 yp, u32 xTile, u32 yTile, int sizeX, int sizeY,
		u8 bits, u32 color) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += sizeX;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += sizeY;
	}
	sf2d_draw_texture_part_scale_blend(icons, xp << 1, yp << 1, xTile, yTile,
			sizeX, sizeY, scaleX, scaleY, color);
}
void render16(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 16;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 16;
	}
	sf2d_draw_texture_part_scale(icons, xp << 1, yp << 1, xTile, yTile, 16, 16,
			scaleX, scaleY);
}

void render16c(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits, float scaleX,float scaleY) {
	xp -= offsetX;
	yp -= offsetY;
	xp *= scaleX;
	yp *= scaleY;
	if ((bits & 1) > 0) {
		xp += 16 * scaleX;
		scaleX = -scaleX;
	}
	if ((bits & 2) > 0) {
		yp += 16 * scaleY;
		scaleY = -scaleY;
	}
	sf2d_draw_texture_part_scale(icons, xp, yp, xTile, yTile,16, 16, scaleX, scaleY);
}

void render16b(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits, u32 color) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 16;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 16;
	}
	sf2d_draw_texture_part_scale_blend(icons, xp << 1, yp << 1, xTile, yTile,
			16, 16, scaleX, scaleY, color);
}
void render16s(s32 xp, s32 yp, u32 tile, u8 bits, u32 color) {
	xp -= offsetX;
	yp -= offsetY;
	int xTile = tile & 255;
	int yTile = tile >> 8;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 16;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 16;
	}
	sf2d_draw_texture_part_scale_blend(icons, xp << 1, yp << 1, xTile, yTile,
			16, 16, scaleX, scaleY, color);
}

void render32(s32 xp, s32 yp, u32 xTile, u32 yTile, u8 bits) {
	xp -= offsetX;
	yp -= offsetY;
	int scaleX = 2, scaleY = 2;
	if ((bits & 1) > 0) {
		scaleX = -2;
		xp += 32;
	}
	if ((bits & 2) > 0) {
		scaleY = -2;
		yp += 32;
	}
	sf2d_draw_texture_part_scale(icons, xp << 1, yp << 1, xTile, yTile, 32, 32,
			scaleX, scaleY);
}

void renderTitle(int x, int y) {
	sf2d_draw_texture_part_scale(icons, (x - 26) << 1, y << 1, 0, 240, 104, 16,
			2.0, 2.0); // MINICRAFT
	sf2d_draw_texture_part(icons, x + 48, y + 52, 104, 240, 152, 16); // 3DS HOMEBREW EDITION
}

void renderButtonIcon(u32 keyIcon, int x, int y, float scale) {
	switch (keyIcon) {
	case CIRCLEPAD:
		render16c(x, y, 96, 208, 0, scale, scale);
		break;
	case KEY_CPAD_UP:
		render16c(x, y, 112, 208, 0, scale, scale);
		break;
	case KEY_CPAD_LEFT:
		render16c(x, y, 128, 208, 0, scale, scale);
		break;
	case KEY_CPAD_DOWN:
		render16c(x, y, 144, 208, 0, scale, scale);
		break;
	case KEY_CPAD_RIGHT:
		render16c(x, y, 160, 208, 0, scale, scale);
		break;

		/* New 3DS only */
	case CSTICK:
		render16c(x, y, 176, 208, 0, scale, scale);
		break;
	case KEY_CSTICK_UP:
		render16c(x, y, 192, 208, 0, scale, scale);
		break;
	case KEY_CSTICK_LEFT:
		render16c(x, y, 208, 208, 0, scale, scale);
		break;
	case KEY_CSTICK_DOWN:
		render16c(x, y, 224, 208, 0, scale, scale);
		break;
	case KEY_CSTICK_RIGHT:
		render16c(x, y, 240, 208, 0, scale, scale);
		break;

	case KEY_A:
		render16c(x, y, 0, 224, 0, scale, scale);
		break;
	case KEY_B:
		render16c(x, y, 16, 224, 0, scale, scale);
		break;
	case KEY_X:
		render16c(x, y, 32, 224, 0, scale, scale);
		break;
	case KEY_Y:
		render16c(x, y, 48, 224, 0, scale, scale);
		break;
	case KEY_DUP:
		render16c(x, y, 64, 224, 0, scale, scale);
		break;
	case KEY_DLEFT:
		render16c(x, y, 80, 224, 0, scale, scale);
		break;
	case KEY_DDOWN:
		render16c(x, y, 96, 224, 0, scale, scale);
		break;
	case KEY_DRIGHT:
		render16c(x, y, 112, 224, 0, scale, scale);
		break;
	case KEY_START:
		render16c(x - 8, y, 128, 224, 0, scale, scale);
		render16c(x + 8, y, 144, 224, 0, scale, scale);
		break;
	case KEY_SELECT:
		render16c(x - 8, y, 160, 224, 0, scale, scale);
		render16c(x + 8, y, 176, 224, 0, scale, scale);
		break;
	case KEY_L:
		render16c(x, y, 192, 224, 0, scale, scale);
		break;
	case KEY_R:
		render16c(x, y, 208, 224, 0, scale, scale);
		break;

		/* New 3DS only */
	case KEY_ZL:
		render16c(x, y, 224, 224, 0, scale, scale);
		break;
	case KEY_ZR:
		render16c(x, y, 240, 224, 0, scale, scale);
		break;
	}
}

int getFrame(int a, int b, int s) {
	return (a == s) ? 0 : ((a < b - 1) ? 8 : 16);
}

void renderFrame(int x1, int y1, int x2, int y2, u32 bgColor) {
	int startX = x1;
	int startY = y1;
	sf2d_draw_rectangle((x1 << 4) + 4 - (offsetX << 1),
			(y1 << 4) + 4 - (offsetY << 1), ((x2 - x1) << 4) - 8,
			((y2 - y1) << 4) - 8, bgColor);
	while (x1 < x2) {
		y1 = startY;
		while (y1 < y2) {
			int xp = (x1 << 4) - (offsetX << 1);
			int yp = (y1 << 4) - (offsetY << 1);
			sf2d_draw_texture_part_scale(icons, xp, yp,
					getFrame(x1, x2, startX), 200 + getFrame(y1, y2, startY), 8,
					8, 2.0, 2.0);
			++y1;
		}
		++x1;
	}
}

void bakeLights() {
	playerLightBake = sf2d_create_texture(64, 64, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	lanternLightBake = sf2d_create_texture(128, 128, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	glowwormLightBake = sf2d_create_texture(16, 16, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	glowwormBigLightBake = sf2d_create_texture(32, 32, TEXFMT_RGBA8, SF2D_PLACE_RAM);

	bakeLight(playerLightBake, 32, 32, 32);
	bakeLight(lanternLightBake, 64, 64, 64);
	
	bakeLight(glowwormLightBake, 8, 8, 8);
	bakeLight(glowwormBigLightBake, 12, 12, 12);
}

void freeLightBakes() {
	sf2d_free_texture(playerLightBake);
	sf2d_free_texture(lanternLightBake);
	
	sf2d_free_texture(glowwormLightBake);
	sf2d_free_texture(glowwormBigLightBake);
}

void renderLightsToStencil(bool force, bool invert, bool rplayer) {
	if (force || (currentLevel > 1 && currentLevel != 5)) {
		GPU_SetDepthTestAndWriteMask(true, GPU_NEVER, 0);
		GPU_SetStencilTest(true, GPU_NEVER, 1, 0xFF, 0xFF);
		GPU_SetStencilOp(GPU_STENCIL_REPLACE, GPU_STENCIL_KEEP,
				GPU_STENCIL_KEEP);
		GPU_SetAlphaTest(true, GPU_GREATER, 0);

        if(player.p.activeItem->id == ITEM_LANTERN) renderLight(player.x, player.y, lanternLightBake);
        else if(rplayer) renderLight(player.x, player.y, playerLightBake);
        
		int i;
		for (i = 0; i < eManager.lastSlot[currentLevel]; ++i) {
			Entity e = eManager.entities[currentLevel][i];
			if (e.type == ENTITY_FURNITURE) {
				if (e.entityFurniture.itemID == ITEM_LANTERN && e.x > player.x - 160 && e.y > player.y - 125 && e.x < player.x + 160 && e.y < player.y + 125)
					renderLight(e.x, e.y, lanternLightBake);
			} else if(e.type == ENTITY_GLOWWORM && e.x > player.x - 160 && e.y > player.y - 125 && e.x < player.x + 160 && e.y < player.y + 125) { //TODO could be made smaller becuase of smaller light radius
				if(rand()%10==0) continue;
				else if(rand()%100==0) renderLight(e.x+4, e.y-4, glowwormBigLightBake);
				else renderLight(e.x, e.y, glowwormLightBake);
			}
		}
		
		int xo = offsetX >> 4;
		int yo = offsetY >> 4;
		int x, y;
		//added offset to render lights from lava which is offscreen
		//TODO: Even this is not performant enough for old 3DS, when there is a lot of lava on screen
		for (x = xo-2; x <= 13 + xo+2; ++x) {
			for (y = yo-2; y <= 8 + yo+2; ++y) {
			    if(getTile(x, y) == TILE_LAVA) {
					//experimental "speedhack"
					if(getTile(x+1,y)==TILE_LAVA && getTile(x-1,y)==TILE_LAVA && getTile(x,y+1)==TILE_LAVA && getTile(x,y-1)==TILE_LAVA) {
						if((x+y)%2 == 0) continue;
					}
					renderLight((x << 4) + 8, (y << 4) + 8, playerLightBake);
				}
			}
		}
		
		
		GPU_SetDepthTestAndWriteMask(true, GPU_GEQUAL, GPU_WRITE_ALL);
		if(invert) {
			GPU_SetStencilTest(true, GPU_EQUAL, 0, 0xFF, 0x0);
		} else {
			GPU_SetStencilTest(true, GPU_EQUAL, 1, 0xFF, 0x0);
		}
		GPU_SetAlphaTest(false, GPU_ALWAYS, 0x00);
		GPU_SetStencilOp(GPU_STENCIL_KEEP, GPU_STENCIL_KEEP, GPU_STENCIL_REPLACE);
	}
}

void resetStencilStuff() {
	//if (currentLevel > 1) {
		GPU_SetStencilTest(false, GPU_ALWAYS, 0x00, 0xFF, 0x00);
		GPU_SetStencilOp(GPU_STENCIL_KEEP, GPU_STENCIL_KEEP, GPU_STENCIL_KEEP);
	//}
}

void renderLight(int x, int y, sf2d_texture* texture) {
	sf2d_draw_texture_scale(texture, (x - (texture->width / 2) - offsetX) * 2,
			(y - (texture->height / 2) - offsetY) * 2, 2.f, 2.f);
}

/* The original software rendered version, it's bad for the framerate :( */
void bakeLight(sf2d_texture* texture, int x, int y, int r) {
	int x0 = x - r;
	int x1 = x + r;
	int y0 = y - r;
	int y1 = y + r;

	// The game's resolution is actually 200x120, the textures are all scaled up by 2.
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x1 > texture->width)
		x1 = texture->width;
	if (y1 > texture->height)
		y1 = texture->height;

	int xx, yy;
	for (yy = y0; yy < y1; yy++) {
		int yd = yy - y;
		yd = yd * yd;
		for (xx = x0; xx < x1; xx++) {
			int xd = xx - x;
			int dist = xd * xd + yd;
			if (dist <= r * r) {
				if (dist >= (r - (r / 5)) * (r - (r / 5))) {
					if ((xd % 2 == 0 && yd % 2 != 0) || (xd % 2 != 0 && yd % 2 == 0)) { // rand() % 4 != 0
						sf2d_set_pixel(texture, xx, yy, 0xFF000000); //RGBA8(0, 0, 0, 255)); // set transparent pixel
					}
				} else {
					sf2d_set_pixel(texture, xx, yy, 0xFF000000); //RGBA8(0, 0, 0, 255)); // set transparent pixel
				}
			}
		}
	}

	sf2d_texture_tile32(texture);
}

bool tu = false;
bool td = false;
bool tl = false;
bool tr = false;

bool tul = false;
bool tur = false;
bool tdl = false;
bool tdr = false;

void renderDots(int x, int y, u8 bits1, u8 bits2, u8 bits3, u8 bits4, u32 xTile, u32 yTile) {
	//another speedhack for o3DS
	if(tu && tl && tr && td) {
		render16(x, y, xTile, yTile, bits1);
		return;
	}
	
	if(tu && tl) render(x, y, xTile, yTile, bits1);
	if(tu && tr) render(x + 8, y, xTile+8, yTile, bits2);
	if(td && tl) render(x, y + 8, xTile, yTile+8, bits3);
	if(td && tr) render(x + 8, y + 8, xTile+8, yTile+8, bits4);
}

void resetSurrTiles() {
	tu = false;
	td = false;
	tl = false;
	tr = false;

	tul = false;
	tur = false;
	tdl = false;
	tdr = false;
}

void checkSurrTiles8(int xt, int yt, int id) {
	if (getTile(xt, yt - 1) == id)
		tu = true;
	if (getTile(xt - 1, yt) == id)
		tl = true;
	if (getTile(xt + 1, yt) == id)
		tr = true;
	if (getTile(xt, yt + 1) == id)
		td = true;
	if (getTile(xt - 1, yt - 1) == id)
		tul = true;
	if (getTile(xt + 1, yt - 1) == id)
		tur = true;
	if (getTile(xt - 1, yt + 1) == id)
		tdl = true;
	if (getTile(xt + 1, yt + 1) == id)
		tdr = true;
}
void checkSurrTiles4(int xt, int yt, int id) {
	if (getTile(xt, yt - 1) == id)
		tu = true;
	if (getTile(xt - 1, yt) == id)
		tl = true;
	if (getTile(xt + 1, yt) == id)
		tr = true;
	if (getTile(xt, yt + 1) == id)
		td = true;
}

u8 tData = 0;
void renderTile(int i, int d, int x, int y) {
	int age = 0;
	switch (i) {
	case TILE_GRASS:
		checkSurrTiles4(x >> 4, y >> 4, TILE_GRASS);
		checkSurrTiles4(x >> 4, y >> 4, TILE_TREE);
		checkSurrTiles4(x >> 4, y >> 4, TILE_FLOWER);
		checkSurrTiles4(x >> 4, y >> 4, TILE_SAPLING_TREE);
		
		renderConnectedTile4(x, y, 256, 0);
		break;
	case TILE_TREE:
		renderTile(TILE_GRASS, 0, x, y);
		
		checkSurrTiles8(x >> 4, y >> 4, TILE_TREE);
		
		render(x,   y,   256+((tu && tl && tul) ? 16 : 0), 48, 0);
		render(x+8, y,   264+((tu && tr && tur) ? 16 : 0), 48, 0);
		render(x,   y+8, 256+((td && tl && tdl) ? 16 : 0), 56, 0);
		render(x+8, y+8, 264+((td && tr && tdr) ? 16 : 0), 56, 0);
		
		break;
	case TILE_ROCK:
		checkSurrTiles8(x >> 4, y >> 4, TILE_ROCK);
		renderConnectedTile8(x, y, 336, 64);
		break;
	case TILE_HARDROCK:
		checkSurrTiles8(x >> 4, y >> 4, TILE_HARDROCK);
		renderConnectedTile8(x, y, 416, 64);
		break;
	case TILE_DIRT: // render dots.
		if (currentLevel > 1)
			render16(x, y, 320, 80, 0);
		else
			render16(x, y, 336, 80, 0);
		break;
	case TILE_SAND:
		checkSurrTiles4(x >> 4, y >> 4, TILE_SAND);
		checkSurrTiles4(x >> 4, y >> 4, TILE_CACTUS);
		checkSurrTiles4(x >> 4, y >> 4, TILE_SAPLING_CACTUS);
		
		renderConnectedTile4(x, y, 320, 0);
		
		if (d > 0) {
			render16(x, y, 336, 48, 0);
		}
		break;
	case TILE_WATER:
		checkSurrTiles4(x >> 4, y >> 4, TILE_WATER);
		checkSurrTiles4(x >> 4, y >> 4, TILE_HOLE);
		
		renderConnectedTile4(x, y, 384, 0);
		
		srand((tickCount + (x / 2 - y) * 4311) / 10);
		renderDots(x, y, rand() & 3, rand() & 3, rand() & 3, rand() & 3, 288, 64);
		break;
	case TILE_LAVA:
		checkSurrTiles4(x >> 4, y >> 4, TILE_LAVA);
		checkSurrTiles4(x >> 4, y >> 4, TILE_HOLE);
		
		renderConnectedTile4(x, y, 448, 0);
		
		srand((tickCount + (x / 2 - y) * 4311) / 10);
		renderDots(x, y, rand() & 3, rand() & 3, rand() & 3, rand() & 3, 304, 64);
		break;
	case TILE_HOLE:
		checkSurrTiles4(x >> 4, y >> 4, TILE_HOLE);
		checkSurrTiles4(x >> 4, y >> 4, TILE_WATER);
		checkSurrTiles4(x >> 4, y >> 4, TILE_LAVA);
		
		renderConnectedTile4(x, y, 256, 16);
		break;
	case TILE_CACTUS:
		renderTile(TILE_SAND, 0, x, y);
		render16(x, y, 304, 48, 0);
		break;
	case TILE_FLOWER:
		renderTile(TILE_GRASS, 0, x, y);
		render16(x, y, 320, 48, getData(x >> 4, y >> 4));
		break;
	case TILE_STAIRS_DOWN:
		if (currentLevel == 0)
			renderTile(TILE_CLOUD, 0, x, y);
		render16(x, y, 256, 64, 0);
		break;
	case TILE_STAIRS_UP:
		render16(x, y, 272, 64, 0);
		break;
	case TILE_IRONORE:
		render16(x, y, 464, 48, 0);
		break;
	case TILE_GOLDORE:
		render16(x, y, 480, 48, 0);
		break;
	case TILE_GEMORE:
		render16(x, y, 496, 48, 0);
		break;
	case TILE_CLOUD:
		checkSurrTiles4(x >> 4, y >> 4, TILE_CLOUD);
		checkSurrTiles4(x >> 4, y >> 4, TILE_STAIRS_DOWN);
		checkSurrTiles4(x >> 4, y >> 4, TILE_CLOUDCACTUS);
		
		renderConnectedTile4(x, y, 320, 16);
		break;
	case TILE_CLOUDCACTUS:
		renderTile(TILE_CLOUD, 0, x, y);
		render16(x, y, 496, 64, 0);
		break;
	case TILE_SAPLING_TREE:
		renderTile(TILE_GRASS, 0, x, y);
		render16(x, y, 288, 48, 0);
		break;
	case TILE_SAPLING_CACTUS:
		renderTile(TILE_SAND, 0, x, y);
		render16(x, y, 288, 48, 0);
		break;
	case TILE_FARM:
		render16(x, y, 352, 48, 0);
		break;
	case TILE_WHEAT:
		age = getData(x >> 4, y >> 4) / 20;
		if (age > 5)
			age = 5;
		render16(x, y, 368 + (age << 4), 48, 0);
		break;
	case TILE_WOOD_WALL:
		checkSurrTiles4(x >> 4, y >> 4, TILE_WOOD_WALL);
		
		renderConnectedTile4(x, y, 384, 16);
		break;
	case TILE_STONE_WALL:
		checkSurrTiles4(x >> 4, y >> 4, TILE_STONE_WALL);
		
		renderConnectedTile4(x, y, 256, 80);
		break;
	case TILE_IRON_WALL:
		checkSurrTiles4(x >> 4, y >> 4, TILE_IRON_WALL);
		
		renderConnectedTile4(x, y, 448, 16);
		break;
	case TILE_GOLD_WALL:
		checkSurrTiles4(x >> 4, y >> 4, TILE_GOLD_WALL);
		
		renderConnectedTile4(x, y, 256, 32);
		break;
	case TILE_GEM_WALL:
		checkSurrTiles4(x >> 4, y >> 4, TILE_GEM_WALL);
		
		renderConnectedTile4(x, y, 320, 32);
		break;
	case TILE_DUNGEON_WALL:
		checkSurrTiles8(x >> 4, y >> 4, TILE_DUNGEON_WALL);
		
		renderConnectedTile8(x, y, 384, 32);
		break;
	case TILE_DUNGEON_FLOOR:
		render16(x, y, 464, 32, 0);
		break;
	case TILE_DUNGEON_ENTRANCE:
		render16(x, y, 480 + (currentLevel==5 ? 16 : 0), 32, 0);
		break;
	case TILE_MAGIC_BARRIER:
		renderTile(TILE_DUNGEON_FLOOR, 0, x, y);
		render16(x, y, 320, 64, 0);
		
		//draw remaining pillar count
		if((player.x - (x+8))*(player.x - (x+8)) + (player.y - (y+8))*(player.y - (y+8)) <= 24*24) {
			x -= offsetX;
			y -= offsetY;
		
			int data = 0;
			int i = 0;
			for (i = 0; i < eManager.lastSlot[currentLevel]; ++i) {
				Entity * e = &eManager.entities[currentLevel][i];
			
				if(e->type == ENTITY_MAGIC_PILLAR) {
					++data;
				}
			}
			
			char currentCount[3];
			sprintf(currentCount,"%d", data);
			
			drawSizedTextColor(currentCount, x+4 + 1, y+4 + 1, 2, dungeonColor[1]);
			drawSizedTextColor(currentCount, x+4, y+4, 2, dungeonColor[0]);
		}
		
		break;
	}

	resetSurrTiles();
}

void renderConnectedTile4(int x, int y, u32 xTile, u32 yTile) {
	//render complete tile in one piece to reduce strain(added for o3DS)
	if (tl && tr && tu && td) {
		render16(x, y, xTile+48, yTile, 0);
		return;
	}
	
	int l = (tl ? 16 : 0);
	int r = (tr ? 16 : 0);
	int u = (tu ? 32 : 0);
	int d = (td ? 32 : 0);
	
	render(x,   y,   xTile  +l+u, yTile, 0);
	render(x+8, y,   xTile+8+r+u, yTile, 0);
	render(x,   y+8, xTile  +l+d, yTile+8, 0);
	render(x+8, y+8, xTile+8+r+d, yTile+8, 0);
}

void renderConnectedTile8(int x, int y, u32 xTile, u32 yTile) {
	//render complete tile in one piece to reduce strain(added for o3DS)
	if (tl && tr && tu && td && tul && tur && tdl && tdr) {
		render16(x, y, xTile+64, yTile, 0);
		return;
	}
	
	int l = (tl ? 16 : 0);
	int r = (tr ? 16 : 0);
	int u = (tu ? 32 : 0);
	int d = (td ? 32 : 0);
	
	render(x,   y,   xTile  +l+u+((tl && tu && tul) ? 16 : 0), yTile, 0);
	render(x+8, y,   xTile+8+r+u+((tr && tu && tur) ? 16 : 0), yTile, 0);
	render(x,   y+8, xTile  +l+d+((tl && td && tdl) ? 16 : 0), yTile+8, 0);
	render(x+8, y+8, xTile+8+r+d+((tr && td && tdr) ? 16 : 0), yTile+8, 0);
}

void renderZoomedMap() {
	sf2d_draw_rectangle(0, 0, 320, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
	
    int mx = mScrollX;
    int my = mScrollY;
    if(zoomLevel == 2) mx = 32;
	sf2d_draw_texture_scale(minimap[currentLevel], mx, my, zoomLevel, zoomLevel); // zoomed map
	// Airwizard on zoomed map
	if(currentLevel == 0){
		if(awX != 0 && awY != 0){
			render16c(
			(mx+((awX/16)*zoomLevel)-16)/2, 
			(my+((awY/16)*zoomLevel)-16)/2, 
			160, 112, 
			((player.p.walkDist >> 6) & 1) == 0 ? 0 : 1, 
			2, 2
			);
		}
    }
	// Player on zoomed map
    render16c(
    (mx+((player.x/16)*zoomLevel)-16)/2, 
    (my+((player.y/16)*zoomLevel)-16)/2, 
    0, 112, 
    ((player.p.walkDist >> 6) & 1) == 0 ? 0 : 1, 
    2, 2
    );
	
    drawText(mapText,224, 214); // "x2"/"x4"/"x6"
    render16(142, 2, 72, 208, 0); // Exit button
    renderc(126, 102, 40, 208, 32, 16, 0); // Plus/Minus zoom buttons
    if(zoomLevel < 3) sf2d_draw_rectangle(258, 210, 26, 20, 0x7F4F4F4F); // gray out minus button
    else if(zoomLevel > 5) sf2d_draw_rectangle(284, 210, 26, 20, 0x7F4F4F4F); // gray out minus button
}

char scoreT[32];
void renderGui() {
	int i;
	for (i = 0; i < 10; ++i) {
		if (i < player.p.health)
			render(i * 8 + 6, 5, 168, 152, 0);
		else
			render(i * 8 + 6, 5, 176, 152, 0);
		if (i < player.p.stamina)
			render(i * 8 + 6, 14, 184, 152, 0);
		else
			render(i * 8 + 6, 14, 191, 152, 0);
	}
	sf2d_draw_texture(minimap[currentLevel], 10, 102);
	renderItemWithTextCentered(player.p.activeItem, 320, 66);
	itoa(player.p.score, scoreT, 10); // integer to base10 string
	drawText("Score:",214,12);
	drawText(scoreT,(140-(strlen(scoreT)*12))/2 + 180,29);
	if(currentLevel == 0){
		if(awX != 0 && awY != 0){
			renderc(1 + (awX/32), 47 + (awY/32), 88, 216, 8, 8, 0); // Mini-AWizard head.
		}
    }
	renderc(1 + (player.x/32), 47 + (player.y/32), 88, 208, 8, 8, 0); // Mini-Player head.
	
	//quick select
	drawText("Quickselect:",164,118);

	Inventory * inv = player.p.inv;
	Item * item;
	for (i = 0; i < 8; ++i) {
		if((inv->lastSlot) > i) {
			int xip = i % 4;
			int yip = i / 4;
		
			item = &inv->items[i];
			renderItemIcon(item->id, item->countLevel, 81+xip*21, 77+yip*21);
		}
	}
}

void renderPlayer() {
	if (player.p.isDead)
		return;
	int xo = player.x - 8;
	int yo = player.y - 8;

	if (player.p.attackTimer > 0 && player.p.dir == 1) {
		renderc(xo, yo - 4, 16, 160, 16, 8, 0);
		renderItemIcon(player.p.activeItem->id, player.p.activeItem->countLevel,
				xo + 4, yo - 4);
	}
	u8 walk = (player.p.walkDist >> 4) & 1;
	bool swimming = isSwimming();
	switch (player.p.dir) {
	case 0: // down
		if (swimming)
			renderc(xo, yo + 4, 48,
					160 + (((player.p.swimTimer >> 4) & 1) << 3), 16, 8, 0);
		else
			renderc(xo, yo + 8, 0, 120 + (player.p.isCarrying ? 16 : 0), 16, 8,
					walk == 0 ? 0 : 1);
		renderc(xo, yo, 0, 112 + (player.p.isCarrying ? 16 : 0), 16, 8,
				walk == 0 ? 0 : 1);
		break;
	case 1: // up
		if (swimming)
			renderc(xo, yo + 4, 48,
					160 + (((player.p.swimTimer >> 4) & 1) << 3), 16, 8, 0);
		else
			renderc(xo, yo + 8, 16, 120 + (player.p.isCarrying ? 16 : 0), 16, 8,
					walk == 0 ? 0 : 1);
		renderc(xo, yo, 16, 112 + (player.p.isCarrying ? 16 : 0), 16, 8,
				walk == 0 ? 0 : 1);
		break;
	case 2: // left
		if (swimming)
			renderc(xo, yo + 4, 48,
					160 + (((player.p.swimTimer >> 4) & 1) << 3), 16, 8, 0);
		else
			renderc(xo, yo + 8, 32 + (walk << 4),
					120 + (player.p.isCarrying ? 16 : 0), 16, 8, 1);
		renderc(xo, yo, 32 + (walk << 4), 112 + (player.p.isCarrying ? 16 : 0),
				16, 8, 1);
		break;
	case 3: // right
		if (swimming)
			renderc(xo, yo + 4, 48,
					160 + (((player.p.swimTimer >> 4) & 1) << 3), 16, 8, 0);
		else
			renderc(xo, yo + 8, 32 + (walk << 4),
					120 + (player.p.isCarrying ? 16 : 0), 16, 8, 0);
		renderc(xo, yo, 32 + (walk << 4), 112 + (player.p.isCarrying ? 16 : 0),
				16, 8, 0);
		break;
	}

	if (player.p.isCarrying) {
		renderFurniture(player.p.activeItem->id, xo, yo - 12);
	}

	if (player.p.attackTimer > 0) {
		switch (player.p.dir) {
		case 0:
			renderc(xo - player.p.ax, yo - player.p.ay + 12, 16, 168, 16, 8, 0);
			renderItemIcon(player.p.activeItem->id,
					player.p.activeItem->countLevel, xo + 4, yo + 12);
			break;
		case 2:
			renderc(xo - player.p.ax - 4, yo - player.p.ay, 32, 160, 8, 16, 0);
			renderItemIcon(player.p.activeItem->id,
					player.p.activeItem->countLevel, xo - 4, yo + 4);
			break;
		case 3:
			renderc(xo - player.p.ax + 12, yo - player.p.ay, 40, 160, 8, 16, 0);
			renderItemIcon(player.p.activeItem->id,
					player.p.activeItem->countLevel, xo + 12, yo + 4);
			break;
		}
	}
}

void renderMenuBackground(int xScroll, int yScroll) {
	sf2d_draw_rectangle(0, 0, 400, 240, 0xFF0C0C0C); //You might think "real" black would be better, but it actually looks better that way
	renderLightsToStencil(false, false, true);
	renderBackground(xScroll, yScroll);
	resetStencilStuff();
	
	renderDayNight();
}

void renderDayNight() {
	if(currentLevel==1 && (daytime<6000 || daytime>18000)) {
		int color1 = 0x000C0C0C;
		int color2 = 0x00100C0C;
		int alpha1 = 0x88;
		int alpha2 = 0xDD;
		
		if(daytime>5000 && daytime<6000) {
			alpha1 = (alpha1 * (1000-(daytime-5000)))/1000;
			alpha2 = (alpha2 * (1000-(daytime-5000)))/1000;
		} else if(daytime>18000 && daytime<19000) {
			alpha1 = (alpha1 * (daytime-18000))/1000;
			alpha2 = (alpha2 * (daytime-18000))/1000;
		}
		
		color1 = color1 | (alpha1 << 24);
		color2 = color2 | (alpha2 << 24);
		
		sf2d_draw_rectangle(0, 0, 400, 240, color1); //You might think "real" black would be better, but it actually looks better that way
		renderLightsToStencil(true, true, false);
		sf2d_draw_rectangle(0, 0, 400, 240, color2); //You might think "real" black would be better, but it actually looks better that way
		resetStencilStuff();
	}
}

void renderBackground(int xScroll, int yScroll) {
    if(currentLevel == 0) {
		sf2d_draw_texture_part_scale(minimap[1], (-xScroll / 3) - 256, (-yScroll / 3) - 32, 0, 0, 128, 128, 12.5, 7.5);
		sf2d_draw_rectangle(0, 0, 400, 240, 0xAFDFDFDF);
	} else if(currentLevel == 5) {
		sf2d_draw_rectangle(0, 0, 400, 240, dungeonColor[1]);
	} else {
		sf2d_draw_rectangle(0, 0, 400, 240, dirtColor[currentLevel]); // dirt color
	}
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int x, y;
	for (x = xo; x <= 13 + xo; ++x) {
		for (y = yo; y <= 8 + yo; ++y)
			renderTile(getTile(x, y), getData(x, y), x << 4, y << 4);
	}
}

char * fontChars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ      0123456789.,!?'\"-+=/\\%()<>:;     ";

void drawText(char * msg, u32 x, u32 y) {
	int i = 0;
	x -= offsetX << 1;
	y -= offsetY << 1;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part(font, x + i * 12, y, (ix & 31) * 12,
					16 + (iy * 12), 12, 12);
		}
	}
}

void drawSizedText(char * msg, u32 x, u32 y, float size) {
	int i = 0;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part_scale(font, (x + i * 8) * size, y,
					(ix & 31) << 3, iy << 3, 8, 8, size, size);
		}
	}
}

void drawTextColor(char * msg, u32 x, u32 y, u32 color) {
	int i = 0;
	x -= offsetX << 1;
	y -= offsetY << 1;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0) {
			sf2d_draw_texture_part_blend(font, x + i * 12, y, (ix & 31) * 12,
					16 + (iy * 12), 12, 12, color);
		}
	}
}

// Changes text color after the first space.
void drawTextColorSpecial(char * msg, u32 x, u32 y, u32 color, u32 color2) {
	int i = 0;
	x -= offsetX << 1;
	y -= offsetY << 1;
	bool sOver = false;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		if (msg[i] == 32)
			sOver = true;
		int iy = ix >> 5;
		if (ix >= 0) {
			if (sOver)
				sf2d_draw_texture_part_blend(font, x + i * 12, y,
						(ix & 31) * 12, 16 + (iy * 12), 12, 12, color2);
			else
				sf2d_draw_texture_part_blend(font, x + i * 12, y,
						(ix & 31) * 12, 16 + (iy * 12), 12, 12, color);
		}
	}
}

void drawSizedTextColor(char * msg, int x, int y, float size, u32 color) {
	int i;
	for (i = 0; i < strlen(msg); ++i) {
		int ix = strchr(fontChars, toupper((unsigned char) msg[i])) - fontChars;
		int iy = ix >> 5;
		if (ix >= 0)
			sf2d_draw_texture_part_scale_blend(font, (x + i * 8) * size,
					y * size, (ix & 31) << 3, iy << 3, 8, 8, size, size, color);
	}
}

void renderFurniture(int itemID, int x, int y) {
	switch (itemID) {
	case ITEM_ANVIL:
		render16(x, y, 64, 128, 0);
		break;
	case ITEM_CHEST:
		render16(x, y, 80, 128, 0);
		break;
	case ITEM_OVEN:
		render16(x, y, 96, 128, 0);
		break;
	case ITEM_FURNACE:
		render16(x, y, 112, 128, 0);
		break;
	case ITEM_WORKBENCH:
		render16(x, y, 128, 128, 0);
		break;
	case ITEM_LANTERN:
		render16(x, y, 144, 128, 0);
		break;
	case ITEM_LOOM:
		render16(x, y, 224, 128, 0);
		break;
	case ITEM_ENCHANTER:
		render16(x, y, 240, 128, 0);
		break;
	}
}

char ertxt[20];
void renderEntity(Entity* e, int x, int y) {
	switch (e->type) {
	case ENTITY_ITEM:
		if (e->entityItem.age >= 520)
			if (e->entityItem.age / 6 % 2 == 0)
				return;
		renderItemIcon(e->entityItem.item.id, e->entityItem.item.countLevel,
				x - 4, y - 4 - (int) e->entityItem.zz);
		break;
	case ENTITY_FURNITURE:
		renderFurniture(e->entityFurniture.itemID, x - 8, y - 8);
		break;
	case ENTITY_ZOMBIE:
		switch (e->hostile.dir) {
		case 0: // down
			render16b(x - 8, y - 8, 64, 112, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 1: // up
			render16b(x - 8, y - 8, 80, 112, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 2: // left
			render16b(x - 8, y - 8, 96 + (((e->hostile.walkDist >> 4) & 1) << 4), 112, 1, e->hostile.color);
			break;
		case 3: // right
			render16b(x - 8, y - 8, 96 + (((e->hostile.walkDist >> 4) & 1) << 4), 112, 0, e->hostile.color);
			break;
		}
		break;
	case ENTITY_SKELETON:
		switch (e->hostile.dir) {
		case 0: // down
			render16b(x - 8, y - 8, 0, 80, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 1: // up
			render16b(x - 8, y - 8, 16, 80, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 2: // left
			render16b(x - 8, y - 8, 32 + (((e->hostile.walkDist >> 4) & 1) << 4), 80, 1, e->hostile.color);
			break;
		case 3: // right
			render16b(x - 8, y - 8, 32 + (((e->hostile.walkDist >> 4) & 1) << 4), 80, 0, e->hostile.color);
			break;
		}
		break;
	case ENTITY_KNIGHT:
		switch (e->hostile.dir) {
		case 0: // down
			render16b(x - 8, y - 8, 64, 80, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 1: // up
			render16b(x - 8, y - 8, 80, 80, ((e->hostile.walkDist >> 4) & 1) == 0 ? 0 : 1, e->hostile.color);
			break;
		case 2: // left
			render16b(x - 8, y - 8, 96 + (((e->hostile.walkDist >> 4) & 1) << 4), 80, 1, e->hostile.color);
			break;
		case 3: // right
			render16b(x - 8, y - 8, 96 + (((e->hostile.walkDist >> 4) & 1) << 4), 80, 0, e->hostile.color);
			break;
		}
		break;
	case ENTITY_SLIME:
		render16b(x - 8, y - 8 - (e->slime.jumpTime > 0 ? 4 : 0),
				128 + (e->slime.jumpTime > 0 ? 16 : 0), 112, 0, e->slime.color);
		break;
	case ENTITY_AIRWIZARD:
		e->wizard.spriteAdjust = 0;
		if (e->wizard.health < 200) {
			if (tickCount / 4 % 3 < 2)
				e->wizard.spriteAdjust = 16;
		} else if (e->wizard.health < 1000) {
			if (tickCount / 5 % 4 < 2)
				e->wizard.spriteAdjust = 16;
		}
		switch (e->wizard.dir) {
		case 0: // down
			render16(x - 8, y - 8, 160, 112 + e->wizard.spriteAdjust,
					((e->wizard.walkDist >> 4) & 1) == 0 ? 0 : 1);
			break;
		case 1: // up
			render16(x - 8, y - 8, 176, 112 + e->wizard.spriteAdjust,
					((e->wizard.walkDist >> 4) & 1) == 0 ? 0 : 1);
			break;
		case 2: // left
			render16(x - 8, y - 8, 192 + (((e->wizard.walkDist >> 4) & 1) << 4),
					112 + e->wizard.spriteAdjust, 1);
			break;
		case 3: // right
			render16(x - 8, y - 8, 192 + (((e->wizard.walkDist >> 4) & 1) << 4),
					112 + e->wizard.spriteAdjust, 0);
			break;
		}
		break;
	case ENTITY_PASSIVE:
		switch (e->passive.dir) {
		case 0: // down
			render16(x - 8, y - 8, (e->passive.mtype*64) + 0, 96, ((e->passive.walkDist >> 4) & 1) == 0 ? 0 : 1);
			break;
		case 1: // up
			render16(x - 8, y - 8, (e->passive.mtype*64) + 16, 96, ((e->passive.walkDist >> 4) & 1) == 0 ? 0 : 1);
			break;
		case 2: // left
			render16(x - 8, y - 8, (e->passive.mtype*64) + 32 + (((e->passive.walkDist >> 4) & 1) << 4), 96, 1);
			break;
		case 3: // right
			render16(x - 8, y - 8, (e->passive.mtype*64) + 32 + (((e->passive.walkDist >> 4) & 1) << 4), 96, 0);
			break;
		}
		break;
	case ENTITY_TEXTPARTICLE:
		x -= offsetX;
		y -= offsetY;
		drawSizedTextColor(e->textParticle.text, x + 1,
				y - (int) e->textParticle.zz + 1, 2, 0xFF);
		drawSizedTextColor(e->textParticle.text, x,
				y - (int) e->textParticle.zz, 2, e->textParticle.color);
		break;
	case ENTITY_SMASHPARTICLE:
		render16(x, y, 0, 160, 0);
		break;
	case ENTITY_SPARK:
		if (e->spark.age >= 200)
			if (e->spark.age / 6 % 2 == 0)
				return;
		renderr(x, y, 200, 152, 0, e->spark.age * 0.0349);
		break;
	case ENTITY_DRAGON:
		switch (e->dragon.dir) {
		case 0: // down
			render32(x - 16, y - 16, 0+(e->dragon.animTimer/4 * 32), 256, 2);
			break;
		case 1: // up
			render32(x - 16, y - 16, 0+(e->dragon.animTimer/4 * 32), 256, 0);
			break;
		case 2: // left
			render32(x - 16, y - 16, 0+(e->dragon.animTimer/4 * 32), 288, 1);
			break;
		case 3: // right
			render32(x - 16, y - 16, 0+(e->dragon.animTimer/4 * 32), 288, 0);
			break;
		}
		break;
	case ENTITY_DRAGONPROJECTILE: 
		if(e->dragonFire.type==0) {
			renderr(x, y, 0, 320, 0, e->dragonFire.age * 0.349);
		} else {
			render(x, y, 8, 320 + (e->dragonFire.age/10)*8, 0);
		}
		break;
	case ENTITY_MAGIC_PILLAR:
		render16(x - 8, y - 8, 16, 320, 0);
		break;
	case ENTITY_ARROW:
		if (e->arrow.age >= 200)
			if (e->arrow.age / 6 % 2 == 0)
				return;
		
		int abits = 0;
		int ayp = 168;
		if(e->arrow.xa<0) {
			abits += 1;
		}
		if(e->arrow.ya<0) {
			ayp += 8;
		}
		if(e->arrow.ya>0) {
			ayp += 8;
			abits += 2;
		}
		
		switch (e->arrow.itemID) {
		case ITEM_ARROW_WOOD:
			render(x-2, y-2, 72, ayp, abits);
			break;
		case ITEM_ARROW_STONE:
			render(x-2, y-2, 80, ayp, abits);
			break;
		case ITEM_ARROW_IRON:
			render(x-2, y-2, 88, ayp, abits);
			break;
		case ITEM_ARROW_GOLD:
			render(x-2, y-2, 96, ayp, abits);
			break;
		case ITEM_ARROW_GEM:
			render(x-2, y-2, 104, ayp, abits);
			break;
		}
		break;
	case ENTITY_GLOWWORM:
		render(x-4, y-4, 224, 112, 0);
		break;
	}
}

void renderEntities(int x, int y, EntityManager* em) {
	int i;
	for (i = 0; i < em->lastSlot[currentLevel]; ++i) {
		Entity e = em->entities[currentLevel][i];
		if (e.x > x - 200 && e.y > y - 125 && e.x < x + 200 && e.y < y + 125)
			renderEntity(&e, e.x, e.y);
	}
}

void renderItemList(Inventory * inv, int xo, int yo, int x1, int y1,
		int selected) {
	// If lastSlot is 0, then there are no items are in the inventory.
	bool drawCursor = true;
	if (selected < 0) {
		drawCursor = false;
		selected = 0;
	}
	int w = x1 - xo;
	int h = y1 - yo - 2;
	int i1 = inv->lastSlot;
	if (i1 > h)
		i1 = h;
	int io = selected - h / 2;
	if (io > inv->lastSlot - h)
		io = inv->lastSlot - h;
	if (io < 0)
		io = 0;

	int i;
	for (i = 0; i < i1; ++i)
		renderItemWithText(&inv->items[i + io], (1 + xo) << 4,
				(i + 1 + yo) << 4);

	if (drawCursor) {
		int yy = selected + 1 - io + yo;
		sf2d_draw_rectangle((xo << 4) - (offsetX << 1),
				(yy << 4) - (offsetY << 1), 12, 12, 0xFF);
		drawText(">", (xo << 4), yy << 4);
		sf2d_draw_rectangle(((xo + w) << 4) - 12 - (offsetX << 1),
				(yy << 4) - (offsetY << 1), 12, 12, 0xFF);
		drawText("<", ((xo + w) << 4) - 12, yy << 4);
	}
}

void renderRecipes(RecipeManager * r, int xo, int yo, int x1, int y1,
		int selected) {
	int size = r->size;
	if (size < 1)
		return;
	if (selected < 0)
		selected = 0;
	int w = x1 - xo;
	int h = y1 - yo - 2;
	int i1 = size;
	if (i1 > h)
		i1 = h;
	int io = selected - h / 2;
	if (io > size - h)
		io = size - h;
	if (io < 0)
		io = 0;

	int i, col;
	for (i = 0; i < i1; ++i) {
		int x = (1 + xo) << 4, y = (i + 1 + yo) << 4;
		renderItemIcon(r->recipes[i + io].itemResult,
				r->recipes[i + io].itemAmountLevel, x >> 1, y >> 1);
		if (r->recipes[i + io].canCraft)
			col = 0xFFFFFFFF;
		else
			col = 0xFF7F7F7F;
		drawTextColor(
				getBasicItemName(r->recipes[i + io].itemResult,
						r->recipes[i + io].itemAmountLevel), x + 18, y + 2,
				col);
	}

	int yy = selected + 1 - io + yo;
	sf2d_draw_rectangle(xo << 4, yy << 4, 12, 12, 0xFF);
	drawText(">", xo << 4, yy << 4);
	sf2d_draw_rectangle(((xo + w) << 4) - 12, yy << 4, 12, 12, 0xFF);
	drawText("<", ((xo + w) << 4) - 12, yy << 4);
}

void renderItemWithText(Item* item, int x, int y) {
	renderItemIcon(item->id, item->countLevel, x >> 1, y >> 1);
	if (item->onlyOne)
		drawText(getItemName(item->id, item->countLevel), x + 18, y + 2);
	else
		drawTextColorSpecial(getItemName(item->id, item->countLevel), x + 18,
				y + 2, 0xFFD2D2D2, 0xFFFFFFFF);
}

void renderItemStuffWithText(int itemID, int itemCL, bool onlyOne, int x, int y) {
	renderItemIcon(itemID, itemCL, x >> 1, y >> 1);
	if (onlyOne)
		drawText(getItemName(itemID, itemCL), x + 18, y + 2);
	else
		drawTextColorSpecial(getItemName(itemID, itemCL), x + 18,
				y + 2, 0xFFD2D2D2, 0xFFFFFFFF);
}

/* For bottom screen */ 
void renderItemWithTextCentered(Item* item, int width, int y) {
	char * tn = getItemName(item->id, item->countLevel);
    int x = (width - ((strlen(tn) + 2) * 12))/2;
    
	renderItemIcon(item->id, item->countLevel, x >> 1, y >> 1);
	
	if (item->onlyOne)
		drawText(getItemName(item->id, item->countLevel), x + 18, y + 2);
	else
		drawTextColorSpecial(getItemName(item->id, item->countLevel), x + 18,
				y + 2, 0xFFD2D2D2, 0xFFFFFFFF);
}

void renderItemIcon(int itemID, int countLevel, int x, int y) {
	switch (itemID) {
	case ITEM_NULL:
		return;
	case TOOL_SHOVEL:
		render(x, y, countLevel * 8, 144, 0);
		break;
	case TOOL_HOE:
		render(x, y, 40 + countLevel * 8, 144, 0);
		break;
	case TOOL_SWORD:
		render(x, y, 80 + countLevel * 8, 144, 0);
		break;
	case TOOL_PICKAXE:
		render(x, y, 120 + countLevel * 8, 144, 0);
		break;
	case TOOL_AXE:
		render(x, y, 160 + countLevel * 8, 144, 0);
		break;
	case ITEM_ANVIL:
		render(x, y, 120, 152, 0);
		break;
	case ITEM_CHEST:
		render(x, y, 128, 152, 0);
		break;
	case ITEM_OVEN:
		render(x, y, 136, 152, 0);
		break;
	case ITEM_FURNACE:
		render(x, y, 144, 152, 0);
		break;
	case ITEM_WORKBENCH:
		render(x, y, 152, 152, 0);
		break;
	case ITEM_LANTERN:
		render(x, y, 160, 152, 0);
		break;
	case ITEM_POWGLOVE:
		render(x, y, 56, 152, 0);
		break;
	case ITEM_FLOWER:
		render(x, y, 0, 152, 0);
		break;
	case ITEM_WOOD:
		render(x, y, 8, 152, 0);
		break;
	case ITEM_STONE:
		renderb(x, y, 16, 152, 0, rockColor[1]);
		break;
	case ITEM_SAND:
		renderb(x, y, 16, 152, 0, sandColor);
		break;
	case ITEM_DIRT:
		renderb(x, y, 16, 152, 0, 0xFF8197AF);
		break;
	case ITEM_CLOUD:
		renderb(x, y, 16, 152, 0, 0xFFFFFFFF);
		break;
	case ITEM_ACORN:
		render(x, y, 24, 152, 0);
		break;
	case ITEM_CACTUS:
		render(x, y, 32, 152, 0);
		break;
	case ITEM_SEEDS:
		render(x, y, 40, 152, 0);
		break;
	case ITEM_WHEAT:
		render(x, y, 48, 152, 0);
		break;
	case ITEM_FLESH:
		render(x, y, 64, 152, 0);
		break;
	case ITEM_BREAD:
		render(x, y, 72, 152, 0);
		break;
	case ITEM_APPLE:
		render(x, y, 80, 152, 0);
		break;
	case ITEM_SLIME:
		renderb(x, y, 88, 152, 0, 0xFF4DC04D);
		break;
	case ITEM_COAL:
		renderb(x, y, 88, 152, 0, 0xFF383838);
		break;
	case ITEM_IRONORE:
		renderb(x, y, 88, 152, 0, ironColor);
		break;
	case ITEM_GOLDORE:
		renderb(x, y, 88, 152, 0, goldColor);
		break;
	case ITEM_IRONINGOT:
		renderb(x, y, 96, 152, 0, ironColor);
		break;
	case ITEM_GOLDINGOT:
		renderb(x, y, 96, 152, 0, goldColor);
		break;
	case ITEM_GLASS:
		render(x, y, 104, 152, 0);
		break;
	case ITEM_GEM:
		render(x, y, 112, 152, 0);
		break;
	case ITEM_LOOM:
		render(x, y, 120, 160, 0);
		break;
	case ITEM_ENCHANTER:
		render(x, y, 144, 160, 0);
		break;
	case ITEM_WALL_WOOD:
		renderb(x, y, 224, 144, 0, woodColor);
		break;
	case ITEM_WALL_STONE:
		renderb(x, y, 224, 144, 0, rockColor[1]);
		break;
	case ITEM_WALL_IRON:
		renderb(x, y, 224, 144, 0, ironColor);
		break;
	case ITEM_WALL_GOLD:
		renderb(x, y, 224, 144, 0, goldColor);
		break;
	case ITEM_WALL_GEM:
		renderb(x, y, 224, 144, 0, gemColor);
		break;
	case ITEM_WOOL:
		render(x, y, 64, 160, 0);
		break;
	case ITEM_STRING:
		render(x, y, 72, 160, 0);
		break;
	case ITEM_PORK_RAW:
		render(x, y, 80, 160, 0);
		break;
	case ITEM_PORK_COOKED:
		render(x, y, 88, 160, 0);
		break;
	case ITEM_BEEF_RAW:
		render(x, y, 96, 160, 0);
		break;
	case ITEM_BEEF_COOKED:
		render(x, y, 104, 160, 0);
		break;
	case ITEM_LEATHER:
		render(x, y, 112, 160, 0);
		break;
	case ITEM_ARROW_WOOD:
		render(x, y, 72, 168, 0);
		break;
	case ITEM_ARROW_STONE:
		render(x, y, 80, 168, 0);
		break;
	case ITEM_ARROW_IRON:
		render(x, y, 88, 168, 0);
		break;
	case ITEM_ARROW_GOLD:
		render(x, y, 96, 168, 0);
		break;
	case ITEM_ARROW_GEM:
		render(x, y, 104, 168, 0);
		break;
	case ITEM_BONE:
		render(x, y, 128, 160, 0);
		break;
	case ITEM_DUNGEON_KEY:
		render(x, y, 136, 160, 0);
		break;
	case ITEM_WIZARD_SUMMON:
		render(x, y, 152, 160, 0);
		break;
	case ITEM_DRAGON_EGG:
		render(x, y, 160, 160, 0);
		break;
	case ITEM_DRAGON_SCALE:
		render(x, y, 168, 160, 0);
		break;
	case TOOL_BUCKET:
		render(x, y, 200 + countLevel * 8, 144, 0);
		break;
	case TOOL_BOW:
		render(x, y, 64, 168, 0);
		break;
	}
}
