#pragma once

enum class HeroesLevelIDs {
	Invalid = -1,
	TestRoom = 0,
	SeasideHill = 1,
	OceanPalace,
	EggFleet = 13
};

extern HeroesLevelIDs CurrentHeroesLevel;
extern HelperFunctions HelperFunctionsGlobal;

NJS_TEXLIST* GetCurrentHeroesTexList();
void LoadLevelTex(NJS_TEXLIST* texlist, const char* name);
void CommonLevelInit();
void LoadLevelMusic(char* name);
void SetStartEndPoints(const HelperFunctions& helperFunctions, StartPosition* start, LevelEndPosition* start2pIntro, StartPosition* end, LevelEndPosition* missionend);
void CommonLevelDelete();

struct RenderInfoThing
{
	char gap0[8];
	int texparplus4;
	int Thing;
	int unknown2;
	int texparbuf;
	int unknown3;
	int unknown4;
	NJS_TEXLIST *CurrentTexlist;
	int unknown;
	int CurrentTexid;
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

ModelInfo* LoadMDL(const char *name);
void FreeMDL(ModelInfo * pointer);

void DrawModel(NJS_MODEL * model);
bool ClipSetObject(ObjectMaster *a1);
float* njPushUnitMatrix();
void njTranslateV(float* matrix, NJS_VECTOR* pos);
void njCalcPoint(NJS_VECTOR *transform, NJS_VECTOR *out, float *matrix, uint8_t somebool);

int IsPlayerInsideSphere(NJS_VECTOR *center, float radius);
void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR orig, NJS_VECTOR dest, float state);
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point);

void CommonObjects_LoadModels();
void CommonObjects_FreeModels();

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions);
void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions);
void EggFleet_Init(const char *path, const HelperFunctions &helperFunctions);

void DashHoop(ObjectMaster* a1);
void ObjFan(ObjectMaster *obj);
void RingGroup(ObjectMaster* obj);
void DashRampAdjust(ObjectMaster* obj);
void Boxes(ObjectMaster* a1);
void Robots(ObjectMaster* a1);
void Beetle_Stationary(ObjectMaster* a1);
void Beetle_Attack(ObjectMaster* a1);
void Beetle_Electric(ObjectMaster* a1);

extern NJS_MATERIAL matlist_col[1];

ObjectFunc(AutoLoop, 0x497B50);
ObjectFunc(RailPath, 0x4980C0);
ObjectFunc(CamPath, nullptr);
DataPointer(NJS_TEXLIST*, CurrentLevelTexList, 0x109E824);
DataPointer(RenderInfoThing *, RenderInfo, 0x2670544);
FunctionPointer(signed int, ClipObject, (ObjectMaster *a1, float dist), 0x488C80);
FunctionPointer(void, Collision_InitThings, (ObjectMaster *a1), 0x47E6C0);
FunctionPointer(signed int, FreeTexList, (NJS_TEXLIST *a1), 0x77F9F0);
FunctionPointer(unsigned int, LoadLevelCam, (), 0x453A90);
DataPointer(void*, dword_1DE4680, 0x1DE4680); //Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);
VoidFunc(ResetRenderSpace, 0x42D340);

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

DataPointer(camera_struct, CameraInfo, 0x1DCFF40);

static const void *const AddToCollisionListPtr = (void*)0x47E750;
static inline void AddToCollisionList(ObjectMaster *a1)
{
	__asm
	{
		mov esi, [a1]
		call AddToCollisionListPtr
	}
}