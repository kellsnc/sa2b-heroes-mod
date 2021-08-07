#pragma once

#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target()) //SF94
#define TARGET_STATIC(name) ((decltype(name##_r)*)name##_t.Target()) //SF94
#define NonStaticVoidFunc(NAME, ADDRESS) NonStaticFunctionPointer(void,NAME,(void),ADDRESS)
#define MaxPlayers 2

extern std::string modpath;
extern HelperFunctions HelperFunctionsGlobal;

Uint32 GetTimer();

enum IndexObj : Sint8 {
	ObjIndex_NoDisplay = 0,
	ObjIndex_1 = 0x1,
	ObjIndex_Common = 0x2,
	ObjIndex_Stage = 0x3,
	ObjIndex_4 = 0x4,
	ObjIndex_5 = 0x5,
	ObjIndex_6 = 0x6,
	ObjIndex_RunFirst = 0x7
};

enum DistObj : Sint16 {
	DistObj_Default = 0,
	DistObj_UseDist = 0x1,
	DistObj_NoDistCheck = 0x2,
	DistObj_Unknown3 = 0x3,
	DistObj_Unknown4 = 0x4,
	DistObj_Unknown5 = 0x5
};

#pragma pack(push, 1)

typedef struct {
	const char* filename;	/* texture filename strings     */
	Uint32			attr;		/* texture attribute            */
	void* texaddr;	/* texture memory list address  */
} NJS_TEXNAME_;

typedef struct {
	NJS_TEXNAME_* textures;	/* texture array                */
	Uint32          nbTexture;	/* texture count                */
} NJS_TEXLIST_;

struct camera_struct {
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



#pragma pack(pop)
//void __usercall LoadCrash3DEffect(NJS_VECTOR *pos@<eax>, Rotation *rot, float unkfloat, Rotation *another_rot, NJS_VECTOR *some_vector, ModelPointers model, NJS_TEXLIST *texlist, int flags)
static const void* const LoadCrash3DEffectPtr = (void*)0x6E1810;
static inline void LoadCrash3DEffect(NJS_VECTOR* pos, Rotation* rot, Float idk, NJS_VECTOR* dir, NJS_VECTOR* some_vector, NJS_MODEL* gc_or_cnk_mdl, NJS_TEXLIST* texlist, int flags)
{
	__asm
	{
		push[flags]
		push[texlist]
		push[gc_or_cnk_mdl]
		push[some_vector]
		push[dir]
		push[idk]
		push[rot]
		mov eax, [pos]
		call LoadCrash3DEffectPtr
		add esp, 28
	}
}

//char __usercall Play3DSound_Vector@<al>(int id@<edi>, NJS_VECTOR *pos@<esi>, int unk, char bank, char volume)
static const void* const Play3DSound_VectorPtr = (void*)0x4372E0;
static inline char Play3DSound_Vector(int id, NJS_VECTOR* pos, int unk, char bank, char volume)
{
	char result;
	__asm
	{
		push[volume]
		push[bank]
		push[unk]
		mov esi, [pos]
		mov edi, [id]
		call Play3DSound_VectorPtr
		mov result, al
		add esp, 12
	}
	return result;
}

static char Play3DSound_EntityPosBank(EntityData1* entity, int id, NJS_VECTOR* pos, char volume, char bank) {
	WriteData<1>((void*)0x43746F, bank);
	char index = Play3DSound_EntityAndPos(entity, id, pos, volume);
	WriteData<1>((void*)0x43746F, 0x01);
	return index;
}

DataPointer(NJS_TEXLIST*, CurrentLevelTexList, 0x109E824);
FunctionPointer(unsigned int, LoadLevelCam, (), 0x453A90);
DataPointer(void*, dword_1DE4680, 0x1DE4680); //Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);
DataPointer(Uint8, ScreenRenderingMode, 0x25EFFCC);
VoidFunc(ToggleScreenRenderingThing, 0x42A870);
ObjectFunc(ClipObjectObjFunc, 0x5B4250);
ObjectFunc(DeleteFunc_ResetVars, 0x5BCCF0);
ObjectFunc(ObjectFunc_DynColDelete, 0x5F12B0);