#include "stdafx.h"

HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
NJS_TEXLIST * LevelTexList;

uint8_t CurrentChunk = 0;
std::string modpath;

LandTableInfo* lands2p[20];
LandTable* land2p = nullptr;
uint8_t land2ploaded = 0;

NJS_TEXNAME seasidehill_texname[91];
NJS_TEXNAME oceanpalace_texname[114];
NJS_TEXLIST seasidehill_texlist{ arrayptrandlength(seasidehill_texname) };
NJS_TEXLIST oceanpalace_texlist{ arrayptrandlength(oceanpalace_texname) };

bool restart;

enum HeroesLevelIDs {
	HeroesLevelID_OceanPalace = 10,
	HeroesLevelID_SeasideHill = 13
};

void LandManagerHook(int a1, LandTable *a2)
{
	LandTableSA2BModels = 0;
	LoadLandManager(a2);
}

void FixColFlags(LandTable *land) {
	for (int i = 0; i < land->COLCount; ++i) {		
		switch (land->COLList[i].Flags) {
		case 0x80000000:
			break;
		case 0x2:
			land->COLList[i].Flags = 0x40000002;
			break;
		default:
			land->COLList[i].Flags = 0x1;
			break;
		}
	}
}

void LoadLevelChunks(const char * level, CHUNK_LIST * chunklist, uint8_t size) {
	int16_t visiblecount = 0;
	int16_t finalcount = 0;

	//load every geometry
	for (uint8_t chunk = 0; chunk < size; ++chunk) {
		std::string numtos = std::to_string(chunklist[chunk].Chunk);
		std::string fullPath = modpath + "\\gd_PC\\";
		fullPath += level;
		if (chunklist[chunk].Chunk < 10) fullPath += "0";
		fullPath += numtos + ".sa2lvl";
		const char *foo = fullPath.c_str();
		lands2p[chunk] = new LandTableInfo(foo);
		finalcount += lands2p[chunk]->getlandtable()->COLCount;
		visiblecount += lands2p[chunk]->getlandtable()->ChunkModelCount;
	}

	//load the landtable
	land2p = new LandTable();
	COL* col2p = new COL[finalcount];
	
	land2p->COLCount = finalcount;
	finalcount = 0;

	//populate the data
	for (uint8_t chunk = 0; chunk < size; ++chunk) {
		LandTable* land = lands2p[chunk]->getlandtable();
			
		land2p->ChunkModelCount += land->ChunkModelCount;
		land2p->field_C = land->field_C;
		land2p->TextureList = land->TextureList;
		land2p->TextureName = land->TextureName;

		for (int16_t col = 0; col < land->COLCount; ++col) {
			col2p[col + finalcount].Center = land->COLList[col].Center;
			col2p[col + finalcount].field_14 = land->COLList[col].field_14;
			col2p[col + finalcount].field_18 = land->COLList[col].field_18;
			col2p[col + finalcount].Flags = land->COLList[col].Flags;
			col2p[col + finalcount].Model = land->COLList[col].Model;
			col2p[col + finalcount].Radius = land->COLList[col].Radius;

			if (col2p[col + finalcount].Flags & 0x80000000) {
				col2p[col + finalcount].field_14 = chunklist[chunk].Chunk;
			}
			else {
				col2p[col + finalcount].field_14 = 0;
			}
		}

		finalcount += land->COLCount;
	}

	//sort visible and invisible models
	COL* geocol = new COL[visiblecount];
	COL* colcol = new COL[finalcount - visiblecount];
	int16_t geocount = 0;
	int16_t colcount = 0;

	for (int16_t col = 0; col < finalcount; ++col) {
		if (col2p[col].field_14 > 0) {
			geocol[geocount] = col2p[col];
			++geocount;
		}
		else {
			colcol[colcount] = col2p[col];
			++colcount;
		}
	}

	//add them back in
	for (int16_t col = 0; col < geocount; ++col) {
		col2p[col] = geocol[col];
	}
	for (int16_t col = 0; col < colcount; ++col) {
		col2p[col + geocount] = colcol[col];
	}

	delete[] geocol;
	delete[] colcol;

	land2p->COLList = col2p;

	LandTable *cland = nullptr;
	
	switch (CurrentLevel) {
	case HeroesLevelID_SeasideHill:
		cland = (LandTable *)GetProcAddress(hmodule, "objLandTable0013");
		cland->TextureList = &seasidehill_texlist;
		land2p->TextureName = (char*)"seasidehill";
		break;
	case HeroesLevelID_OceanPalace:
		cland = (LandTable *)GetProcAddress(hmodule, "objLandTable0010");
		cland->TextureList = &oceanpalace_texlist;
		land2p->TextureName = (char*)"oceanpalace";
		break;
	}

	land2p->TextureList = cland->TextureList;
	*cland = *land2p;
	CurrentLandTable = land2p;
	FixColFlags(CurrentLandTable);
	LoadLandManager(land2p);

	land2ploaded = 120;
}

void ChunkHandler(const char * level, CHUNK_LIST * chunklist, uint8_t size) {
	if (!MainCharObj1[0] || !CurrentLandTable) return;
	
	if (land2ploaded == 0) 
		LoadLevelChunks(level, chunklist, size);

	for (Int i = 0; i < size; ++i) {
		if (chunklist[i].Chunk != CurrentChunk) {
			EntityData1 *entity = MainCharObj1[0];
			if (entity != nullptr) {
				NJS_VECTOR pos = MainCharObj1[0]->Position;

				if (((chunklist[i].Position1.x == 0 || pos.x < chunklist[i].Position1.x)) &&
					((chunklist[i].Position1.y == 0 || pos.y < chunklist[i].Position1.y)) &&
					((chunklist[i].Position1.z == 0 || pos.z < chunklist[i].Position1.z)) &&
					((chunklist[i].Position2.x == 0 || pos.x > chunklist[i].Position2.x)) &&
					((chunklist[i].Position2.y == 0 || pos.y > chunklist[i].Position2.y)) &&
					((chunklist[i].Position2.z == 0 || pos.z > chunklist[i].Position2.z))) {
					
					CurrentChunk = chunklist[i].Chunk;
				
					CurrentLandTable->COLList[CurrentLandTable->COLCount - 1];

					for (int j = 0; j < CurrentLandTable->COLCount; ++j) {
						COL* col = &CurrentLandTable->COLList[j];

						if (col->field_14 == 0) return;

						if (col->field_14 == CurrentChunk) {
							col->Flags |= 0x80000000;
						}
						else {
							col->Flags &= ~0x80000000;
						}
					}

					break;
				}
			}
		}
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5) {
			MessageBoxA(MainWindowHandle,
				"Your copy of the Mod Loader is outdated, please update it to the latest version.",
				"SA2B Heroes Conversion",
				MB_ICONWARNING);
		}
		
		modpath = std::string(path);
		
		WriteCall((void*)0x5DCDF7, LandManagerHook);
		WriteData((char*)0x5DD4F0, (char)0xC3);
		WriteData<2>((void*)0x47C2BC, 0x90u);

		SeasideHill_Init(path, helperFunctions);
		OceanPalace_Init(path, helperFunctions);
	}

	__declspec(dllexport) void OnFrame() {
		switch (CheckModelLoaded()) {
		case 1:
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_LoadModels();
				CommonObjects_LoadModels(); break;
			case HeroesLevelID_OceanPalace:
				OceanPalace_LoadModels();
				CommonObjects_LoadModels(); break;
			}
			break;
		case 2:
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_FreeModels();
				CommonObjects_FreeModels(); break;
			case HeroesLevelID_OceanPalace:
				OceanPalace_FreeModels();
				CommonObjects_FreeModels(); break;
			}
			break;
		default:
			break;
		}

		if (GameState == 9 || GameState == 13 || GameState == GameStates_RestartLevel_1)
			restart = true;

		if (GameState != GameStates_Pause) {
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_OnFrame();
				break;
			case HeroesLevelID_OceanPalace:
				OceanPalace_OnFrame();
				break;
			}
		}

		if (land2ploaded > 1) --land2ploaded;

		if (GameState == 0) {
			if (land2ploaded == 1) {
				CurrentChunk = 0;
				land2ploaded = 0;

				//unload previous level
				if (land2p) {
					delete[] land2p;
					land2p = nullptr;

					for (uint8_t i = 0; i < 20; ++i) {
						if (lands2p[i]) {
							delete lands2p[i];
							lands2p[i] = nullptr;
						}
					}
				}
			}

			restart = false;
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}