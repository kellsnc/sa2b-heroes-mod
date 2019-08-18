#include "stdafx.h"

NJS_TEXLIST * oldtexlist;
NJS_TEXNAME seasidehill_texname[99];
NJS_TEXLIST seasidehill_texlist = { arrayptrandlengthT(seasidehill_texname, Uint32) };
void LandManagerHook(int a1, LandTable *a2)
{
	LandTableSA2BModels = 0;
	LoadLandManager(a2);
}

StartPosition startpos = { LevelIDs_CityEscape, 0x6000, 0x6000, 0x6000, { -14, 233, -7462 }, { -14, 233, -7458 }, { -14, 233, -7466 } };

void __cdecl Background_Display(ObjectMaster *a1) {

}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5)
			MessageBoxA(MainWindowHandle, "Your copy of the mod loader does not support API version 5. Some functionality will not be available.\n\nPlease exit the game and update the mod loader for the best experience.", "SA2B Dreamcast Conversion", MB_ICONWARNING);

		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
		LandTable *land = (LandTable *)GetProcAddress(hmodule, "objLandTable0013");
		oldtexlist = land->TextureList;
		*land = *(new LandTableInfo(std::string(path) + "\\gd_PC\\SH01.sa2lvl"))->getlandtable();
		land->TextureName = (char*)"seasidehill";
		land->TextureList = oldtexlist;

		for (int i = 0; i < land->COLCount; ++i) {
			land->COLList[i].Flags = 0x80000001;
		}

		WriteData((ObjectFuncPtr*)0x5DD213, Background_Display);
		WriteCall((void*)0x5DCDF7, LandManagerHook);
		WriteData((char*)0x5DD4F0, (char)0xC3);
		WriteData<2>((void*)0x47C2BC, 0x90u);

		for (uint8_t i = 0; i < Characters_Amy; i++)
		{
			helperFunctions.RegisterStartPosition(i, startpos);
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}