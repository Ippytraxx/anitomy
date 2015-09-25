#ifndef _ANITOMYC_H
#define _ANITOMYC_H

#include <stddef.h>

typedef enum
{
  ANITOMY_ELEMENT_ITERATE_FIRST,
  ANITOMY_ELEMENT_ANIME_SEASON = ANITOMY_ELEMENT_ITERATE_FIRST,
  ANITOMY_ELEMENT_ANIME_SEASONPREFIX,
  ANITOMY_ELEMENT_ANIME_TITLE,
  ANITOMY_ELEMENT_ANIME_TYPE,
  ANITOMY_ELEMENT_ANIME_YEAR,
  ANITOMY_ELEMENT_AUDIO_TERM,
  ANITOMY_ELEMENT_DEVICE_COMPATIBILITY,
  ANITOMY_ELEMENT_EPISODE_NUMBER,
  ANITOMY_ELEMENT_EPISODE_PREFIX,
  ANITOMY_ELEMENT_EPISODE_TITLE,
  ANITOMY_ELEMENT_FILE_CHECKSUM,
  ANITOMY_ELEMENT_FILE_EXTENSION,
  ANITOMY_ELEMENT_FILE_NAME,
  ANITOMY_ELEMENT_LANGUAGE,
  ANITOMY_ELEMENT_OTHER,
  ANITOMY_ELEMENT_RELEASE_GROUP,
  ANITOMY_ELEMENT_RELEASE_INFORMATION,
  ANITOMY_ELEMENT_RELEASE_VERSION,
  ANITOMY_ELEMENT_SOURCE,
  ANITOMY_ELEMENT_SUBTITLES,
  ANITOMY_ELEMENT_VIDEO_RESOLUTION,
  ANITOMY_ELEMENT_VIDEO_TERM,
  ANITOMY_ELEMENT_ITERATE_LAST,
  ANITOMY_ELEMENT_UNKNOWN = ANITOMY_ELEMENT_ITERATE_LAST
} AnitomyElementCategory;

typedef struct Anitomy Anitomy;
typedef struct AnitomyElements AnitomyElements;

typedef struct
{
    AnitomyElementCategory category;
    char* value;
} AnitomyElementPair;

Anitomy* anitomy_new();
size_t anitomy_elements_size(AnitomyElements* self);
void anitomy_free(Anitomy* self);
int anitomy_parse(Anitomy* self, const char* filename); 
AnitomyElements* anitomy_elements(Anitomy* self);
AnitomyElementPair* anitomy_elements_at(AnitomyElements* self, size_t pos);
char* anitomy_elements_get(AnitomyElements* self, AnitomyElementCategory category);
char** anitomy_elements_get_all(AnitomyElements* self, AnitomyElementCategory category);
void anitomy_element_pair_free(AnitomyElementPair* self);

#endif
