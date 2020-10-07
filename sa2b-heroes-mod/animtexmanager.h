#pragma once

void AnimateTexlist(NJS_TEXLIST_* list, Uint32 frame, Uint32* CurrentFrame, void** texaddr);
void UnloadTXCFile();
void LoadTXCFile(const char* path);