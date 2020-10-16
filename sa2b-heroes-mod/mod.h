#pragma once

#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target()) //SF94
#define NonStaticVoidFunc(NAME, ADDRESS) NonStaticFunctionPointer(void,NAME,(void),ADDRESS)
#define MaxPlayers 4

extern std::string modpath;
extern HelperFunctions HelperFunctionsGlobal;

Uint32 GetTimer();

typedef struct {
	const char* filename;	/* texture filename strings     */
	Uint32			attr;		/* texture attribute            */
	void* texaddr;	/* texture memory list address  */
} NJS_TEXNAME_;

typedef struct {
	NJS_TEXNAME_* textures;	/* texture array                */
	Uint32          nbTexture;	/* texture count                */
} NJS_TEXLIST_;

struct RenderInfoThing {
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

struct camera_screen {
	NJS_VECTOR pos;
	Rotation rot;
};

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

//void __usercall DynCol_Add(SurfaceFlags flags@<eax>, ObjectMaster *obj@<edx>, DynColData *dyncoldata@<esi>)
static const void* const DynCol_AddPtr = (void*)0x47D6B0;
static inline void DynCol_Add(int flags, ObjectMaster* obj, NJS_OBJECT* object)
{
	__asm
	{
		mov edx, [obj]
		mov esi, [object]
		mov eax, [flags]
		call DynCol_AddPtr
	}
}

//void __usercall DrawSA2BModel(SA2B_Model *model@<eax>)
static const void* const DrawSA2BModelPtr = (void*)0x4932C0;
static inline void DrawSA2BModel(SA2B_Model* model)
{
	__asm
	{
		mov eax, [model]
		call DrawSA2BModelPtr
	}
}

//ObjectMaster *__usercall GetCollidingPlayer@<eax>(ObjectMaster *obj@<eax>)
static const void* const GetCollidingPlayerPtr = (void*)0x486500;
static inline ObjectMaster* GetCollidingPlayer(ObjectMaster* obj)
{
	ObjectMaster* result;
	__asm
	{
		mov eax, [obj]
		call GetCollidingPlayerPtr
		mov result, eax
	}
	return result;
}

//void __usercall UpdateSetDateAndDelete(ObjectMaster *obj@<eax>)
static const void* const UpdateSetDateAndDeletePtr = (void*)0x488DA0;
static inline void UpdateSetDateAndDelete(ObjectMaster* obj)
{
	__asm
	{
		mov eax, [obj]
		call UpdateSetDateAndDeletePtr
	}
}

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

//void __usercall njCalcVector(NJS_VECTOR *transform@<eax>, NJS_VECTOR *out@<edx>, float *matrix@<ecx>)
static const void* const njCalcVectorPtr = (void*)0x4273B0;
static inline void njCalcVector(NJS_VECTOR* transform, NJS_VECTOR* out, float* matrix)
{
	__asm
	{
		mov ecx, [matrix]
		mov edx, [out]
		mov eax, [transform]
		call njCalcVectorPtr
	}
}

//void __usercall njCalcVector@<eax>(NJS_MATRIX* result@<eax>, NJS_VECTOR* out@<edx>, NJS_VECTOR* a3@<ecx>, char a4)
static const void* const njCalcPointPtr = (void*)0x426CC0;
static inline void njCalcPoint(float* matrix, NJS_VECTOR* out, NJS_VECTOR* transform, bool something)
{
	__asm
	{
		push[something]
		mov ecx, [transform]
		mov edx, [out]
		mov eax, [matrix]
		call njCalcPointPtr
		add esp, 4;
	}
}

// void __usercall njSetMotion(NJS_MOTION *motion@<ecx>, float frame);
static const void* const njSetMotionPtr = (void*)0x7819A0;
static inline void njSetMotion(NJS_MOTION* motion, float frame)
{
	__asm
	{
		push[frame]
		mov ecx, [motion]
		call njSetMotionPtr
		add esp, 4
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

// void __usercall LoadStageSounds(char *filename@<esi>, void *address)
static const void* const LoadStageSoundsPtr = (void*)0x4355A0;
static inline void LoadStageSounds(const char* filename, void* address)
{
	__asm
	{
		push[address]
		mov esi, [filename]
		call LoadStageSoundsPtr
		add esp, 4
	}
}

//char __usercall Play3DSound_EntityAndPos@<al>(EntityData1* entity@<ebx>, int id@<edi>, int pos@<esi>, char volume)
static const void* const Play3DSound_EntityAndPosPtr = (void*)0x437420;
static inline char Play3DSound_EntityAndPos(EntityData1* entity, int id, NJS_VECTOR* pos, char volume)
{
	char result;
	__asm
	{
		push[volume]
		mov esi, [pos]
		mov edi, [id]
		mov ebx, [entity]
		call Play3DSound_EntityAndPosPtr
		mov result, al
		add esp, 4
	}
	return result;
}

static char Play3DSound_EntityPosBank(EntityData1* entity, int id, NJS_VECTOR* pos, char volume, char bank) {
	WriteData<1>((void*)0x43746F, bank);
	char index = Play3DSound_EntityAndPos(entity, id, pos, volume);
	WriteData<1>((void*)0x43746F, 0x01);
	return index;
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
DataArray(camera_screen*, CameraScreenArray, 0x1DD92B0, 2);
DataPointer(int, CurrentScreen, 0x1DD92A0);
DataPointer(Uint8, ScreenRenderingMode, 0x25EFFCC);
VoidFunc(ToggleScreenRenderingThing, 0x42A870);
ObjectFunc(ClipObjectObjFunc, 0x5B4250);
ObjectFunc(DeleteFunc_ResetVars, 0x5BCCF0);
ObjectFunc(ObjectFunc_DynColDelete, 0x5F12B0);
FastcallFunctionPointer(float, njSin, (Angle angle), 0x42AAB0);
FunctionPointer(NJS_OBJECT*, GetFreeDynObject, (), 0x47D7F0);
FunctionPointer(void, DrawObjMotion, (NJS_OBJECT* a1), 0x782420);
DataPointer(void*, MotionDrawCallback, 0x1D19C0C);