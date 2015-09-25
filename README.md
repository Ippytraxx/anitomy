# AnitomyC

A C wrapper with unit tests for Erengy's Anitomy anime filename parser.

Equivalent C code snippet:
```c
#include <stdio.h>
#include <anitomy/anitomyc.h>

int main()
{
    Anitomy* anitomy = anitomy_new();
    Elements* elements;

    anitomy_parse(anitomy, "[Ouroboros]_Fullmetal_Alchemist_Brotherhood_-_01.mkv");

    elements = anitomy_elements(anitomy); // Owned by anitomy, no free needed.

    for (int i = 0; i < anitomy_elements_size(elements); i++)
    {
        AnitomyElementPair* pair = anitomy_elements_at(elements, i);

        printf("Category %d, value %s\n", pair->category, pair->value);

        anitomy_element_pair_free(pair);
    }

    printf("Title %s, ep num %s, release group %s\n",
           anitomy_elements_get(elements, ANITOMY_ELEMENTS_ANIME_TITLE),
           anitomy_elements_get(elements, ANITOMY_ELEMENTS_EPISODE_NUMER),
           anitomy_elements_get(elements, ANITOMY_ELEMENTS_RELEASE_GROUP));

    anitomy_free(anitomy);
}
```

Please refer to [the original repo for additonal info](https://github.com/erengy/anitomy).
