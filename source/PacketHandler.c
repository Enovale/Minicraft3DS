#include "PacketHandler.h"

#include "Globals.h"

void processPacket(networkPacket *packet, u8 type, u16 sender) {
    //TODO: Differenciate the packets and process them
    if(networkIsServer()) {
		if(type==PACKET_REQUEST_MAPDATA) {
			u8 level = packet->requestMapData.level;
			
			if(level>=0 && level<=5) {
				//send back tile data
				for(int y=0; y<128; y++) {
					networkPacket packet = {
						.mapData = {
							.type = PACKET_MAPDATA,
							.level = level,
							.offset = y
						}
					};
					for(int x=0; x<128; x++) {
						packet.mapData.map[x] = map[level][x+y*128];
						packet.mapData.data[x] = data[level][x+y*128];
					}
					networkSendTo(&packet, sizeof(packetMapData), sender);
				}
			}
		} else {
			//TODO: Unknown packet - how to handle?
		}
	} else {
		if(type==PACKET_MAPDATA) {
			u8 level = packet->mapData.level;
			
			if(level>=0 && level<=5) {
				//recieve tile data
				//TODO: This should really check whether the values are in valid range
				int y = packet->mapData.offset;
				for(int x=0; x<128; x++) {
					map[level][x+y*128] = packet->mapData.map[x];
					data[level][x+y*128] = packet->mapData.data[x];
				}
			}
		} else {
			//TODO: Unknown packet - how to handle?
		}
	}
}
