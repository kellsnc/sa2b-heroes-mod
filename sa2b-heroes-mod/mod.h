#pragma once

#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target()) //SF94
#define NonStaticVoidFunc(NAME, ADDRESS) NonStaticFunctionPointer(void,NAME,(void),ADDRESS)
#define MaxPlayers 4

extern std::string modpath;
extern HelperFunctions HelperFunctionsGlobal;

typedef struct {
	const char* filename;	/* texture filename strings     */
	Uint32			attr;		/* texture attribute            */
	void* texaddr;	/* texture memory list address  */
} NJS_TEXNAME_;

typedef struct {
	NJS_TEXNAME_* textures;	/* texture array                */
	Uint32          nbTexture;	/* texture count                */
} NJS_TEXLIST_;

struct RenderInfoThing
{
	char gap0[8];
	int texparplus4;
	int Thing;
	int unknown2;
	int texparbuf;
	int MinDrawDist;
	int MaxDrawDist;
	NJS_TEXLIST* CurrentTexlist;
	int unknown;
	int CurrentTexid;
};

struct camera_struct
{
	int field_0;
	int field_4;
	int field_8;
	char gapC[328];
	float field_154;
	float field_158;
	float field_15C;
	int field_160;
	char gap164[48];
	NJS_VECTOR Position;
	Rotation field_1A0;
	char gap1AC[9000];
	int field_24D4;
};

enum IndexObj : Sint8
{
	ObjIndex_NoDisplay = 0,
	ObjIndex_1 = 0x1,
	ObjIndex_Common = 0x2,
	ObjIndex_Stage = 0x3,
	ObjIndex_4 = 0x4,
	ObjIndex_5 = 0x5,
	ObjIndex_6 = 0x6,
	ObjIndex_RunFirst = 0x7
};

enum DistObj : Sint16
{
	DistObj_Default = 0,
	DistObj_UseDist = 0x1,
	DistObj_NoDistCheck = 0x2,
	DistObj_Unknown3 = 0x3,
	DistObj_Unknown4 = 0x4,
	DistObj_Unknown5 = 0x5
};

static const void* const AddToCollisionListPtr = (void*)0x47E750;
static inline void AddToCollisionList(ObjectMaster* a1)
{
	__asm
	{
		mov esi, [a1]
		call AddToCollisionListPtr
	}
}

// void __usercall(TexPackInfo* a1@<eax>, NJS_TEXLIST*** a2)
static const void* const LoadTexPacksPtr = (void*)0x44C7B0;
static inline void LoadTexPacks(TexPackInfo* TexPackList, NJS_TEXLIST*** Texlists)
{
	__asm
	{
		push[Texlists]
		mov eax, [TexPackList]
		call LoadTexPacksPtr
		add esp, 4
	}
}

// void __usercall(NJS_TEXLIST*** a1@<eax>, TexPackInfo* a2@<ecx>)
static const void* const FreeTexPacksPtr = (void*)0x44C810;
static inline void FreeTexPacks(NJS_TEXLIST*** Texlists, TexPackInfo* TexPackList)
{
	__asm
	{
		mov ecx, [TexPackList]
		mov eax, [Texlists]
		call FreeTexPacksPtr
	}
}

ObjectFunc(AutoLoop, 0x497B50);
ObjectFunc(RailPath, 0x4980C0);
ObjectFunc(CamPath, nullptr);
DataPointer(NJS_TEXLIST*, CurrentLevelTexList, 0x109E824);
DataPointer(RenderInfoThing*, RenderInfo, 0x2670544);
FunctionPointer(signed int, ClipObject, (ObjectMaster* a1, float dist), 0x488C80);
FunctionPointer(void, Collision_InitThings, (ObjectMaster* a1), 0x47E6C0);
FunctionPointer(signed int, FreeTexList, (NJS_TEXLIST* a1), 0x77F9F0);
FunctionPointer(unsigned int, LoadLevelCam, (), 0x453A90);
DataPointer(void*, dword_1DE4680, 0x1DE4680); //Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);
VoidFunc(ResetRenderSpace, 0x42D340);
DataPointer(camera_struct, CameraInfo, 0x1DCFF40);
DataPointer(COL**, LandTable_VisibleEntries, 0x1A5A2E4);
DataPointer(Uint16, LandTable_VisibleEntriesCount, 0x1945A00);
DataPointer(NJS_VECTOR*, CameraPosArray, 0x1DD92B0); // Actual position and rotation, two times
DataPointer(int, CurrentScreen, 0x1DD92A0);
DataPointer(Uint8, ScreenRenderingMode, 0x25EFFCC);
VoidFunc(ToggleScreenRenderingThing, 0x42A870);