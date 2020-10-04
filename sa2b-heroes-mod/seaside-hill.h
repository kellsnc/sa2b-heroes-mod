#pragma once

//StartPosition sh_startpos = { LevelIDs_CityEscape, 0xBFFF, 0xBFFF, 0xBFFF, { 0.0f, 20.0f , 2960.0f }, { -50.0f, 140.0f, 850.0f }, { 50.0f, 140.0f, 850.0f } }; for the 2P version
StartPosition sh_startpos = { LevelIDs_CityEscape, 0xBFFF, 0xBFFF, 0xBFFF, { 0.0f, 20.0f , 2960.0f }, { -10.0f, 20.0f , 2960.0f }, { 10.0f, 20.0f, 2960.0f } };
StartPosition sh_endpos = { LevelIDs_CityEscape, 0x4000, 0, 0, { 1400.0f, 1075.0f, -42710.0f }, { -4530.0f, 100.0f, -12200 }, { -4530.0f, 100.0f, -12200 } };
LevelEndPosition sh_2pintro = { LevelIDs_CityEscape, 0, 0, 0, { 0.0f, 310.0f, -2000.0f }, { 0.0f, 310.0f, -2000.0f } };
LevelEndPosition sh_endpos23 = { LevelIDs_CityEscape, 0, 0x4000, 0, { -4530.0f, 100.0f, -12200 }, { -4530.0f, 100.0f, -12200 } };

CollisionData Col_Pole = { 0x100, 0xE077, 0, { 0, 0, 0 }, 10, 80, 10, 0, 0, 0, 0 };
CollisionData Col_Platform = { 0x300, 0xE077, 0, { 0, 0, 0 }, 25, 15, 25, 0, 0, 0, 0 };
CollisionData Col_MvPltfrm3 = { 0x300, 0xE077, 0, { 0, 0, 0 }, 24, 200, 24, 0, 0, 0, 0 };
CollisionData Col_MvPltfrm2[] = { 0x300, 0xE077, 0, { 0, 0, 0 }, 75, 200, 75, 0, 0, 0, 0 };
CollisionData Col_MvPltfrm1[] = {
	{ 0x300, 0xE077, 0, { 0, 0, 0 }, 150, 300, 250, 0, 0, 0, 0 },
	{ 0x300, 0xE077, 0, { 133, 300, 0 }, 15, 80, 250, 0, 0, 0, 0 },
	{ 0x300, 0xE077, 0, { -133, 300, 0 }, 15, 80, 250, 0, 0, 0, 0 }
};