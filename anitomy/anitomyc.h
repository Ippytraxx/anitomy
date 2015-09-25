#ifndef _ANITOMYC_H
#define _ANITOMYC_H

typedef enum
{
  AnitomyElementIterateFirst,
  AnitomyElementAnimeSeason = AnitomyElementIterateFirst,
  AnitomyElementAnimeSeasonPrefix,
  AnitomyElementAnimeTitle,
  AnitomyElementAnimeType,
  AnitomyElementAnimeYear,
  AnitomyElementAudioTerm,
  AnitomyElementDeviceCompatibility,
  AnitomyElementEpisodeNumber,
  AnitomyElementEpisodePrefix,
  AnitomyElementEpisodeTitle,
  AnitomyElementFileChecksum,
  AnitomyElementFileExtension,
  AnitomyElementFileName,
  AnitomyElementLanguage,
  AnitomyElementOther,
  AnitomyElementReleaseGroup,
  AnitomyElementReleaseInformation,
  AnitomyElementReleaseVersion,
  AnitomyElementSource,
  AnitomyElementSubtitles,
  AnitomyElementVideoResolution,
  AnitomyElementVideoTerm,
  AnitomyElementIterateLast,
  AnitomyElementUnknown = AnitomyElementIterateLast
} AnitomyElementCategory;

typedef struct Anitomy Anitomy;
typedef struct AnitomyElements AnitomyElements;

Anitomy* anitomy_new();
void anitomy_free(Anitomy* self);
int anitomy_parse(Anitomy* self, const char* filename); 
AnitomyElements* anitomy_elements(Anitomy* self);
char* anitomy_elements_get(AnitomyElements* self, AnitomyElementCategory category);
char** anitomy_elements_get_all(AnitomyElements* self, AnitomyElementCategory category);

#endif
