#pragma once

typedef struct {
	uint8_t			Chunk;
	NJS_VECTOR		Position1;
	NJS_VECTOR		Position2;
} CHUNK_LIST;

void ChunkHandler(const char * level, CHUNK_LIST * chunklist, uint8_t size);

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions);
void SeasideHill_OnFrame();