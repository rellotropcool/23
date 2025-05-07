
//{{BLOCK(map)

//======================================================================
//
//	map, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 5 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 320 + 8192 = 9024
//
//	Time-stamp: 2025-05-07, 22:37:26
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.7
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP_H
#define GRIT_MAP_H

#define mapTilesLen 320
extern const unsigned int mapTiles[80];

#define mapMapLen 8192
extern const unsigned short mapMap[4096];

#define mapPalLen 512
extern const unsigned short mapPal[256];

#endif // GRIT_MAP_H

//}}BLOCK(map)
