#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

#include "SA2ModLoader.h"
#include "LandTableInfo.h"
#include "ModelInfo.h"
#include "AnimationFile.h"
#include "Trampoline.h"

#include "mod.h"
#include "level.h"
#include "paths.h"
#include "objects.h"
#include "byteswap.h"
#include "landmanager.h"
#include "chunkmanager.h"
#include "animtexmanager.h"