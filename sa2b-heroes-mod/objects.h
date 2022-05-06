#pragma once

extern NJS_TEXLIST_ HeroesWater_TexList;

void LoadMDL(ModelInfo** info, const char* name, ModelFormat format);
void LoadAnim(AnimationFile** info, const char* name);
void FreeMDL(ModelInfo** pointer);
void FreeAnim(AnimationFile** pointer);

void njScalef(Float f);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
void njTranslateXYZ(Float x, Float y, Float z);
void njTranslateX(Float f);
void njTranslateY(Float f);
void njTranslateZ(Float f);
void njRotateX_(Angle x);
void njRotateY_(Angle y);
void njRotateZ_(Angle z);
void njRotateZXY(Angle x, Angle y, Angle z);
void njRotateZXY(Rotation* rot);
void DrawChunkModel__(NJS_MODEL* model);
void njCnkAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void njSA2BAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void DrawObject_(NJS_OBJECT* obj, ModelFormat format);

int IsPlayerInsideSphere(Float x, Float y, Float z, Float radius);
int IsPlayerInsideSphere(NJS_VECTOR* center, Float radius);
bool IsPlayerIDInsideSphere(Float x, Float y, Float z, Float radius, Uint8 PlayerID);
NJS_VECTOR GetPathPosition(NJS_VECTOR* orig, NJS_VECTOR* dest, float state);
void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR* orig, NJS_VECTOR* dest, float state);
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point);
NJS_OBJECT* GetChildModelByIndex(NJS_OBJECT* object, int index);
NJS_OBJECT* GetSiblingModelByIndex(NJS_OBJECT* object, int index);
void MainSub_Collision(ObjectMaster* obj);

void CommonObjects_LoadModels();
void CommonObjects_FreeModels();

bool Fans_IsSpecificPlayerInCylinder(EntityData1* entity, NJS_VECTOR* center, float radius, float height);
void __cdecl DashHoop(ObjectMaster* a1);
void __cdecl ObjFan(ObjectMaster* obj);
void __cdecl RingGroup(ObjectMaster* obj);
void __cdecl DashRampAdjust(ObjectMaster* obj);
void __cdecl Boxes(ObjectMaster* obj);
void __cdecl Robots(ObjectMaster* obj);
void __cdecl Beetle_Stationary(ObjectMaster* obj);
void __cdecl Beetle_Attack(ObjectMaster* obj);
void __cdecl Beetle_Electric(ObjectMaster* obj);
void __cdecl ObjCannon(ObjectMaster* obj);
void __cdecl OBJCASE(ObjectMaster* obj);
void __cdecl e2000_Init(ObjectMaster* obj);
void __cdecl Flyer_Init(ObjectMaster* obj);
void __cdecl Flyer_Trigger(ObjectMaster* obj);
void __cdecl Laserdoor(ObjectMaster* obj);

void LoadBreaker(NJS_VECTOR* pos, Rotation* rot, NJS_OBJECT* object, Float Xoff, Float Yoff, Float Zoff, Float time);