#pragma once

extern NJS_TEXLIST_ HeroesWater_TexList;

ModelInfo* LoadMDL(const char* name, ModelFormat format);
void FreeMDL(ModelInfo* pointer);

void DrawChunkModel(NJS_MODEL* model);
bool ClipSetObject(ObjectMaster* a1);
float* njPushUnitMatrix();
void njTranslateV(float* matrix, NJS_VECTOR* pos);
void njScalef(Float f);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
void njTranslateX(Float f);
void njTranslateY(Float f);
void njTranslateZ(Float f);

int IsPlayerInsideSphere(Float x, Float y, Float z, Float radius);
int IsPlayerInsideSphere(NJS_VECTOR* center, Float radius);
bool IsPlayerIDInsideSphere(Float x, Float y, Float z, Float radius, Uint8 PlayerID);
NJS_VECTOR GetPathPosition(NJS_VECTOR* orig, NJS_VECTOR* dest, float state);
void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR* orig, NJS_VECTOR* dest, float state);
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point);
NJS_OBJECT* GetChildModelByIndex(NJS_OBJECT* object, int index);
NJS_OBJECT* GetSiblingModelByIndex(NJS_OBJECT* object, int index);

void CommonObjects_LoadModels();
void CommonObjects_FreeModels();

void DashHoop(ObjectMaster* a1);
void ObjFan(ObjectMaster* obj);
void RingGroup(ObjectMaster* obj);
void DashRampAdjust(ObjectMaster* obj);
void Boxes(ObjectMaster* a1);
void Robots(ObjectMaster* a1);
void Beetle_Stationary(ObjectMaster* a1);
void Beetle_Attack(ObjectMaster* a1);
void Beetle_Electric(ObjectMaster* a1);

void LoadBreaker(NJS_VECTOR* pos, Rotation* rot, NJS_OBJECT* object, Float Yoff, Float time);