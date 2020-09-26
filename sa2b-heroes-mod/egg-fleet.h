#pragma once

StartPosition ef_startpos = { LevelIDs_FinalRush, 0xBFFF, 0xBFFF, 0xBFFF, { 500.0f, 4200.0f, 5250.0f }, { 480.0f, 4200.0f, 5250.0f }, { 520.0f, 4200.0f, 5250.0f } };
StartPosition ef_endpos = { LevelIDs_FinalRush, 0x4000, 0x4000, 0x4000, { -9500.0f, -3293.0f, -42570.0f }, { -9500.0f, -3293.0f, -42570.0f }, { -9500.0f, -3293.0f, -42570.0f } };
LevelEndPosition ef_2pintro = { LevelIDs_FinalRush, 0xBFFF, 0xBFFF, 0, { 500.0f, 4200.0f, 5250.0f }, { 500.0f, 4200.0f, 5250.0f } };
LevelEndPosition ef_endpos23 = { LevelIDs_FinalRush, 0x4000, 0x4000, 0, { -6000.0f, 3390.0f, -12254.0f }, { -6000.0f, 3390.0f, -12254.0f } };

LoopHead* EggFleetPathList[] = {
	0
};

DeathZone EggFleetDeathZones[] = {
	{ 0 }
};