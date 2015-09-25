#include "anitomy.h"
#include <locale>
#include <codecvt>
#include <cstring>
#include <stdio.h>

extern "C" 
{
    #include "anitomyc.h"
}

static char*
wide_to_narrow(const wchar_t* wide)
{
    char* narrow;
    size_t size;

    size = sizeof(wchar_t)*wcslen(wide);
    narrow = (char*) malloc(size);
    wcstombs(narrow, wide, size);

    return narrow;
}

Anitomy* 
anitomy_new() 
{
    return reinterpret_cast<Anitomy*>(new anitomy::Anitomy());
}

void
anitomy_free(Anitomy* self)
{
    delete reinterpret_cast<anitomy::Anitomy*>(self);
}

int 
anitomy_parse(Anitomy* self, const char* filename)
{
    return reinterpret_cast<anitomy::Anitomy*>(self)->Parse(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename)); //Really wish m$ would catch up with the times
}

AnitomyElements*
anitomy_elements(Anitomy* self)
{
    return reinterpret_cast<AnitomyElements*>(&reinterpret_cast<anitomy::Anitomy*>(self)->elements());
}

size_t
anitomy_elements_size(AnitomyElements* self)
{
    return reinterpret_cast<anitomy::Elements*>(self)->size();
}

AnitomyElementPair* 
anitomy_elements_at(AnitomyElements* self, size_t pos)
{
    AnitomyElementPair* ret;
    anitomy::element_pair_t& pair = reinterpret_cast<anitomy::Elements*>(self)->at(pos);

    ret = (AnitomyElementPair*) malloc(sizeof(AnitomyElementPair));

    ret->category = static_cast<AnitomyElementCategory>(pair.first);
    ret->value = wide_to_narrow(pair.second.c_str());

    return ret;
}

char*
anitomy_elements_get(AnitomyElements* self, AnitomyElementCategory category)
{
    char* ret;

    ret = wide_to_narrow(reinterpret_cast<anitomy::Elements*>(self)->get(static_cast<anitomy::ElementCategory>(category)).c_str());

    return ret;
}

char**
anitomy_elements_get_all(AnitomyElements* self, AnitomyElementCategory category)
{
    char** ret;
    std::vector<anitomy::string_t> all;
    int i;

    all = reinterpret_cast<anitomy::Elements*>(self)->get_all(static_cast<anitomy::ElementCategory>(category));

    ret = (char**) malloc(sizeof(char*)*(all.size() + 1));

    for (i = 0; i < all.size(); i++)
    {
        anitomy::string_t s = all.at(i);
        ret[i] = wide_to_narrow(s.c_str());
    }

    ret[i] = NULL;

    return ret;
}

void 
anitomy_element_pair_free(AnitomyElementPair* self)
{
    free(self->value);
    free(self);
}
