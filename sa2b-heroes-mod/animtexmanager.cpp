#include "stdafx.h"

#pragma pack(push, 1)

struct AnimTexFrameEntry {
    Uint16 FrameOffset;
    Uint16 TextureID;
};

struct AnimTexEntry {
    Uint32  FrameCount;
    Uint8   FrameEntryCount;
    void*   OriginalTex;
    Uint8   TextureOffset;
    Uint8   Zero[510];
    char    FirstFrameTextureName[32];
    char    TextureCommonName[32];
    AnimTexFrameEntry* Frames;
};

#pragma pack(pop)

static AnimTexEntry* AnimTexEntries = nullptr;
static int AnimTexCount = 0;

void AnimateTexlist(NJS_TEXLIST_* list, Uint32 frame, Uint32* CurrentFrame, void** texaddr)
{
    if (*texaddr == NULL)
    {
        *texaddr = list->textures[0].texaddr;
    }

    if (GetTimer() % frame == 0)
    {
        *CurrentFrame += 1;

        if (*CurrentFrame >= list->nbTexture)
        {
            *CurrentFrame = 0;
            list->textures[0].texaddr = *texaddr;
        }
        else
        {
            list->textures[0].texaddr = list->textures[*CurrentFrame].texaddr;
        }
    }
}

static void AnimTexManager(ObjectMaster* obj)
{
    for (int i = 0; i < AnimTexCount; ++i)
    {
        auto entry = &AnimTexEntries[i];
        auto texlist = reinterpret_cast<NJS_TEXLIST_*>(GetCurrentHeroesTexList());
        int CurrentFrame = GetTimer() % entry->FrameCount;

        for (int j = 0; j < entry->FrameEntryCount; ++j)
        {
            if (CurrentFrame < entry->Frames[j].FrameOffset)
            {
                int nexttexid = entry->TextureOffset + entry->Frames[j].TextureID - 1;

                // We replace the memory pointer of the first texture of the animation
                // If it's the first pointer, use the one stored
                if (nexttexid == entry->TextureOffset)
                {
                    texlist->textures[entry->TextureOffset].texaddr = entry->OriginalTex;
                }
                else
                {
                    texlist->textures[entry->TextureOffset].texaddr = texlist->textures[nexttexid].texaddr;
                }

                break;
            }
        }
    }
}

void LoadAnimTexManager() {
    if (AnimTexCount > 0)
    {
        for (int i = 0; i < AnimTexCount; ++i)
        {
            AnimTexEntry* entry = &AnimTexEntries[i];

            NJS_TEXLIST_* texlist = (NJS_TEXLIST_*)GetCurrentHeroesTexList();

            for (uint32_t tex = 0; tex < texlist->nbTexture; ++tex)
            {
                std::string temp1 = texlist->textures[tex].filename;

                // If the name in the file match a name in the texture file, save the offset
                if (temp1.compare(entry->FirstFrameTextureName) == 0)
                {
                    entry->OriginalTex = texlist->textures[tex].texaddr; // Store first texture pointer
                    entry->TextureOffset = static_cast<Uint8>(tex);
                }
            }
        }

        LoadObject((LoadObj)0, "ANIMTEXMNG", AnimTexManager, 1);
    }
}

void UnloadTXCFile()
{
    if (AnimTexCount > 0)
    {
        for (int i = 0; i < AnimTexCount; ++i)
        {
            delete[] AnimTexEntries[i].Frames;
        }

        delete[] AnimTexEntries;
        AnimTexEntries = nullptr;
        AnimTexCount = 0;
    }
}

void LoadTXCFile(const char* path)
{
    std::ifstream file(HelperFunctionsGlobal.GetReplaceablePath(path), std::ios::in | std::ios::binary);

    if (file.is_open())
    {
        std::vector<AnimTexEntry> AnimTexEntriesVector; // We don't know the number of entries
        AnimTexEntry animtexentry; // Current entry

        // The entries stop at 0xFF
        while (file.peek() != 0xFF)
        {
            std::vector<AnimTexFrameEntry> AnimTexFrameEntriesVector; // We don't know the number of frame entries
            AnimTexFrameEntry animtexframeentry; // Current frame entry

            file.read((char*)&animtexentry, sizeof(AnimTexEntry) - 0x4); // Add to struct

            // The frame entries stop at 0xFF
            while (file.peek() != 0xFF)
            {
                file.read((char*)&animtexframeentry, sizeof(AnimTexFrameEntry)); // Add every frame entries
                AnimTexFrameEntriesVector.push_back(animtexframeentry);
            }

            // Add frame entries to struct
            animtexentry.FrameEntryCount = static_cast<Uint8>(AnimTexFrameEntriesVector.size());
            animtexentry.Frames = new AnimTexFrameEntry[animtexentry.FrameEntryCount]();

            for (Uint8 i = 0; i < animtexentry.FrameEntryCount; ++i)
            {
                animtexentry.Frames[i] = AnimTexFrameEntriesVector[i];
            }

            AnimTexFrameEntriesVector.clear();
            AnimTexEntriesVector.push_back(animtexentry);
        }

        // Allocate AnimTexEntries
        AnimTexCount = AnimTexEntriesVector.size();
        AnimTexEntries = new AnimTexEntry[AnimTexCount];

        for (int j = 0; j < AnimTexCount; ++j)
        {
            AnimTexEntries[j] = AnimTexEntriesVector[j];
        }

        AnimTexEntriesVector.clear();

        file.close();

        LoadAnimTexManager();
    }
}