#pragma once

DataArray(ObjectListEntry, MetalHarbor_ObjectArray, 0xAEC550, 93);

StartPosition op_startpos = { LevelIDs_MetalHarbor, 0xBFFF, 0xBFFF, 0xBFFF, { -8771, 1303, -2819.688f }, { -8768, 1303, -2819.688f }, { -8774, 1303, -2819.688f } };
StartPosition op_endpos = { LevelIDs_MetalHarbor, 4000, 4000, 3000, { 1404, 1075.34f, -45687 }, { 1404, 1075.34f, -45687 }, { 1432, 1063.55f, -45782 } };
LevelEndPosition op_2pintro = { LevelIDs_MetalHarbor, 0x64EC, 0x64EC, 0, { 220, 41.65f, 436 }, { 195, 6.8f, -706 } };
LevelEndPosition op_endpos23 = { LevelIDs_MetalHarbor, 0, 0x4000, 0, { 900.0848f, -298.2f, -33579.89f }, { -4569, 441.8f, -17016 } };

SH_ANIMTEXS OceanPalaceAnimTexs[]{
	{ 2, 19,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4 } },
	{ 90, 19,{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 } }
};

CHUNK_LIST OceanPalaceChunks[]{
	{ 1,{ 0, 0, 0 },{ 0, 0, -10637 } },
	{ 2,{ 0, 0, -10638 },{ 0, 0, -16182 } },
	{ 3,{ 0, 0, -16185 },{ 0, 0, -21276 } },
	{ 4,{ 0, 0, -21286 },{ 0, 0, -24604 } },
	{ 5,{ 0, 0, -25192 },{ 0, 0, -33666 } },
	{ 6,{ 0, 0, -33667 },{ 0, 0, -40250 } },
	{ 7,{ 0, 0, -40251 },{ -8443, 0, -48669 } },
	{ 8,{ -8442, 0, -45529 },{ 0, 0, 0 } }
};