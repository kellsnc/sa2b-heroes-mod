#pragma once

typedef struct {
	uint8_t			Chunk;
	NJS_VECTOR		Position1;
	NJS_VECTOR		Position2;
} CHUNK_LIST;

typedef struct {
	int			texid;
	int			count;
	int			duration[40];
} SH_ANIMTEXS;

typedef struct {
	NJS_VECTOR		Position;
	Angle			Rotation[3];
	uint8_t			Chunk;
	Float			DrawDistance;
} SOI_LIST;

typedef struct {
	uint8_t			Model;
	NJS_VECTOR		Position;
	Angle			Rotation[3];
	NJS_VECTOR		Scale;
	Float			Bias;
	uint8_t			Chunk;
	Float			DrawDistance;
} SOI_LIST2;

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

void ChunkHandler(const char * level, CHUNK_LIST * chunklist, uint8_t size);

ModelInfo* LoadMDL(const char *name);
void FreeMDL(ModelInfo * pointer);
int CheckModelLoaded();
bool CheckModelDisplay(SOI_LIST item);
bool CheckModelDisplay2(SOI_LIST2 item);
int ClipSetObject(ObjectMaster *a1);

void SeasideHill_LoadModels();
void SeasideHill_FreeModels();
void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions);
void SeasideHill_OnFrame();

ObjectFunc(AutoLoop, 0x497B50);
ObjectFunc(RailPath, 0x4980C0);
ObjectFunc(CamPath, nullptr);

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

DataPointer(RenderInfoThing *, RenderInfo, 0x2670544);
FunctionPointer(void, DrawModel, (NJS_OBJECT*), 0x42E730);
FunctionPointer(signed int, ClipObject, (ObjectMaster *a1, float dist), 0x488C80);

extern uint8_t CurrentChunk;
extern std::string modpath;
extern bool ModelLoaded;