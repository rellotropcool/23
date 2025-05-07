
//{{BLOCK(cheese)

//======================================================================
//
//	cheese, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 1015 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 64960 + 8192 = 73664
//
//	Time-stamp: 2025-05-07, 22:05:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.7
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CHEESE_H
#define GRIT_CHEESE_H

#define cheeseTilesLen 64960
extern const unsigned int cheeseTiles[16240];

#define cheeseMapLen 8192
extern const unsigned short cheeseMap[4096];

#define cheesePalLen 512
extern const unsigned short cheesePal[256];

#endif // GRIT_CHEESE_H

//}}BLOCK(cheese)
