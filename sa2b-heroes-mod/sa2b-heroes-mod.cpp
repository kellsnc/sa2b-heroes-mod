#include "stdafx.h"

HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
std::string modpath;

uint8_t CurrentChunk = 0;
LandTableInfo* lands2p[20];

bool restart;

TexPackInfo CommonTexPacks[2]{
	{ "efftex_common", texlist_efftex_common },
	{ "objtex_common", texlist_objtex_common }
};

enum HeroesLevelIDs {
	HeroesLevelID_OceanPalace = 10,
	HeroesLevelID_SeasideHill = 13
};

//Change the sadx col flags to similar sa2 ones
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

//Load every chunk, sort the geometry, set up the chunk system
void LoadLevelChunks(const char * level, CHUNK_LIST * chunklist, uint8_t size, char* fullname, NJS_TEXLIST* texlist) {
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
	CurrentLandTable = new LandTable();
	COL* col2p = new COL[finalcount];
	
	CurrentLandTable->COLCount = finalcount;
	finalcount = 0;

	//populate the data
	for (uint8_t chunk = 0; chunk < size; ++chunk) {
		LandTable* land = lands2p[chunk]->getlandtable();
			
		CurrentLandTable->ChunkModelCount += land->ChunkModelCount;
		CurrentLandTable->field_C = land->field_C;
		CurrentLandTable->TextureList = land->TextureList;
		CurrentLandTable->TextureName = land->TextureName;

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

	CurrentLandTable->COLList = col2p;
	CurrentLandTable->TextureList = texlist;
	CurrentLandTable->TextureName = fullname;

	FixColFlags(CurrentLandTable);

	LandTableSA2BModels = 0;
	LoadLandManager(CurrentLandTable);
}

//Show the visible pieces when in bounds
void ChunkHandler(const char * level, CHUNK_LIST * chunklist, uint8_t size) {
	if (!MainCharObj1[0] || !CurrentLandTable) return;

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

//Load the common texpacks, and fill the many common texlists
//Set some other common level stuff
void CommonLevelInit() {
	DropRingsFunc_ptr = DropRings;

	for (uint8_t i = 0; i < LengthOfArray(CommonTexPacks); ++i) {
		if (i == 0) {
			LoadTextureList((char*)"objtex_common", texlist_objtex_common);
			CommonTexPacks[i].TexList = texlist_objtex_common;
		}
		else {
			LoadTextureList((char*)"efftex_common", texlist_efftex_common);
			CommonTexPacks[i].TexList = texlist_efftex_common;
		}
		
		//Go through all the TexLists
		NJS_TEXLIST*** c1 = &CommonTexLists[26];
		while (1) {
			if (c1[0][0]) {
				
				NJS_TEXLIST** c2 = c1[0];
				while (1) {
					if (c2[0]) {
						
						NJS_TEXLIST* c3 = c2[0];
						while (1) {
							if (c3->nbTexture > 0 && c3->nbTexture < 3) {
								//put the texture pointer if the filename is identical

								for (uint8_t t = 0; t < CommonTexPacks[i].TexList->nbTexture; ++t) {
									void* orig = CommonTexPacks[i].TexList->textures[t].filename;
									
									for (uint8_t t2 = 0; t2 < c3->nbTexture; ++t2) {
										void* dest = c3->textures[t2].filename;

										if (orig == dest) {
											c3->textures[t2].texaddr = CommonTexPacks[i].TexList->textures[t].texaddr;
											c3->textures[t2].attr = CommonTexPacks[i].TexList->textures[t].attr;
										}
									}
								}
							}
							else {
								break;
							}

							c3 = &c3[1];
						}
					}
					else {
						break;
					}

					c2 = &c2[1];
				}

			}
			else {
				return;
			}

			c1 = &c1[1];
		}
	}
}

//Load the current level music
void LoadLevelMusic(char* name) {
	char character;
	int c = 0;
	do
	{
		character = name[c];
		CurrentSongName[c++] = character;
	} while (character);

	
	PlayMusic(name);
	ResetMusic();
}

//Set the start and end positions
void SetStartEndPoints(const HelperFunctions &helperFunctions, StartPosition* start, LevelEndPosition* start2pIntro, StartPosition* end, LevelEndPosition* missionend) {
	for (uint8_t i = 0; i < Characters_Amy; i++)
	{
		helperFunctions.RegisterStartPosition(i, *start);
		helperFunctions.Register2PIntroPosition(i, *start2pIntro);

		if (helperFunctions.Version >= 5)
		{
			helperFunctions.RegisterEndPosition(i, *end);
			helperFunctions.RegisterMission23EndPosition(i, *missionend);
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
		
		WriteData<2>((void*)0x47C2BC, 0x90u);

		SeasideHill_Init(path, helperFunctions);
		OceanPalace_Init(path, helperFunctions);
	}

	__declspec(dllexport) void OnFrame() {
		switch (CheckModelLoaded()) {
		case 2:
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_FreeModels();
				CommonObjects_FreeModels(); break;
			case HeroesLevelID_OceanPalace:
				OceanPalace_FreeModels();
				CommonObjects_FreeModels(); break;
			}
			return;
		default:
			break;
		}

		if (GameState == 9 || GameState == 13 || GameState == GameStates_RestartLevel_1) {
			restart = true;
			return;
		}
		
		if (GameState != GameStates_Pause) {
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_Main();
				break;
			case HeroesLevelID_OceanPalace:
				OceanPalace_OnFrame();
				break;
			}
		}

		if (GameState == 0) {
			if (CurrentLandTable) {
				delete[] CurrentLandTable;
				CurrentLandTable = nullptr;

				for (uint8_t i = 0; i < 20; ++i) {
					if (lands2p[i]) {
						delete lands2p[i];
						lands2p[i] = nullptr;
					}
				}
			}

			restart = false;
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}