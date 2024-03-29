#pragma once

//StartPosition sh_startpos = { LevelIDs_CityEscape, 0xBFFF, 0xBFFF, 0xBFFF, { 0.0f, 20.0f , 2960.0f }, { -50.0f, 140.0f, 850.0f }, { 50.0f, 140.0f, 850.0f } }; for the 2P version
StartPosition sh_startpos = { LevelIDs_CityEscape, 0xBFFF, 0xBFFF, 0xBFFF, { 0.0f, 20.0f , 2960.0f }, { -10.0f, 20.0f , 2960.0f }, { 10.0f, 20.0f, 2960.0f } };
StartPosition sh_endpos = { LevelIDs_CityEscape, 0x4000, 0, 0, { 1400.0f, 1075.0f, -42710.0f }, { -4530.0f, 100.0f, -12200.0f }, { -4530.0f, 100.0f, -12200.0f } };
LevelEndPosition sh_2pintro = { LevelIDs_CityEscape, 0, 0, 0, { 0.0f, 310.0f, -2000.0f }, { 0.0f, 310.0f, -2000.0f } };
LevelEndPosition sh_endpos23 = { LevelIDs_CityEscape, 0, 0x4000, 0, { -4530.0f, 100.0f, -12200.0f }, { -4530.0f, 100.0f, -12200.0f } };

CollisionData Col_Pole = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 10.0f, 80.0f, 10.0f, 0.0f, 0, 0, 0 };
CollisionData Col_Platform = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 25.0f, 15.0f, 25.0f, 0.0f, 0, 0, 0 };
CollisionData Col_BreakBlock = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 17.5f, 0.0f }, 25.0f, 35.0f, 25.0f, 0.0f, 0, 0, 0 };

CollisionData Col_MvPltfrm3 = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 24.0f, 200.0f, 24.0f, 0.0f, 0, 0, 0 };
CollisionData Col_MvPltfrm2 = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 75.0f, 200.0f, 75.0f, 0.0f, 0, 0, 0 };

CollisionData Col_MvPltfrm1[] = {
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 150.0f, 300.0f, 250.0f, 0.0f, 0, 0, 0 },
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 133.0f, 300.0f, 0.0f }, 15.0f, 80.0f, 250.0f, 0.0f, 0, 0, 0 },
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { -133.0f, 300.0f, 0.0f }, 15.0f, 80.0f, 250.0f, 0.0f, 0, 0, 0 }
};

NJS_TEXNAME_ seasidehill_texname[]{
	{ "k1_flo2", 0, 0 },
	{ "k1_kab01", 0, 0 },
	{ "k1_kab03", 0, 0 },
	{ "k1_kab11", 0, 0 },
	{ "k1_kab12", 0, 0 },
	{ "k1_kuj01", 0, 0 },
	{ "k1_kuj11", 0, 0 },
	{ "k1_kuj12", 0, 0 },
	{ "k1_m_k01", 0, 0 },
	{ "k1_mit01", 0, 0 },
	{ "k1_mit11", 0, 0 },
	{ "k1_rop01", 0, 0 },
	{ "k1_rop02", 0, 0 },
	{ "k1_sna01", 0, 0 },
	{ "k1_sna02", 0, 0 },
	{ "k1_sna03", 0, 0 },
	{ "k1_sra02", 0, 0 },
	{ "k1_sya01", 0, 0 },
	{ "k1_sya02", 0, 0 },
	{ "k1_sya03", 0, 0 },
	{ "k1_tika1", 0, 0 },
	{ "k1_tika1_", 0, 0 },
	{ "k1_tika2", 0, 0 },
	{ "k1_tika2_", 0, 0 },
	{ "k1_u1.1", 0, 0 },
	{ "k1_u1.2", 0, 0 },
	{ "k1_u1.3", 0, 0 },
	{ "k1_u1.4", 0, 0 },
	{ "k1_u1.5", 0, 0 },
	{ "k1_u1.6", 0, 0 },
	{ "k1_u1.7", 0, 0 },
	{ "k1_u1.8", 0, 0 },
	{ "k1_u1.9", 0, 0 },
	{ "k1_u1.10", 0, 0 },
	{ "k1_u1.11", 0, 0 },
	{ "k1_u1.12", 0, 0 },
	{ "k1_u1.13", 0, 0 },
	{ "k1_u1.14", 0, 0 },
	{ "k1_u1.15", 0, 0 },
	{ "k1_u1.16", 0, 0 },
	{ "k1_u1.17", 0, 0 },
	{ "k1_u1.18", 0, 0 },
	{ "k1_u1.19", 0, 0 },
	{ "k1_u1.20", 0, 0 },
	{ "k1_umi02", 0, 0 },
	{ "k1_umi03", 0, 0 },
	{ "k1_umi11", 0, 0 },
	{ "k1_umi13", 0, 0 },
	{ "k1_umi14", 0, 0 },
	{ "k1_yasi1", 0, 0 },
	{ "m1_1001", 0, 0 },
	{ "m1_1002", 0, 0 },
	{ "m1_1003", 0, 0 },
	{ "m1_1004", 0, 0 },
	{ "m1_1005", 0, 0 },
	{ "m1_1006", 0, 0 },
	{ "m1_1007", 0, 0 },
	{ "m1_1008", 0, 0 },
	{ "m1_1009", 0, 0 },
	{ "m1_1010", 0, 0 },
	{ "m1_1011", 0, 0 },
	{ "m1_1012", 0, 0 },
	{ "m1_2001", 0, 0 },
	{ "m1_2004", 0, 0 },
	{ "m1_2005", 0, 0 },
	{ "m1_2006", 0, 0 },
	{ "m1_2008", 0, 0 },
	{ "m1_2011", 0, 0 },
	{ "m1_2012", 0, 0 },
	{ "m1_2013", 0, 0 },
	{ "m1_5002", 0, 0 },
	{ "pk1_flo1", 0, 0 },
	{ "pk1_flo3", 0, 0 },
	{ "pk1_flo4", 0, 0 },
	{ "pk1_flo5", 0, 0 },
	{ "pk1_flo6", 0, 0 },
	{ "pk1_flo7", 0, 0 },
	{ "pk1_hika", 0, 0 },
	{ "pk1_par1", 0, 0 },
	{ "pk1_yas2", 0, 0 },
	{ "pk1_yas3", 0, 0 },
	{ "pkb1_hta", 0, 0 },
	{ "tk1_mizu", 0, 0 },
	{ "tk1_nam1", 0, 0 },
};