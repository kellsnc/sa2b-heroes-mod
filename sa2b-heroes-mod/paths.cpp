#include "stdafx.h"
#include "paths.h"

// 64 bytes are allocated for paths, in Data2
struct PathControl {
	Uint32 padding[14];
	LoopHead* loophead;
};

void __cdecl PropellerPath(ObjectMaster* obj) {
	PathControl* head = (PathControl*)obj->Data2.Undefined;

	
}