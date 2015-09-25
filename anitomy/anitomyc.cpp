#include "anitomy.h"
#include <locale>
#include <codecvt>
#include <cstring>

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

void
anitomy_elements_free(AnitomyElements* self)
{
    delete reinterpret_cast<anitomy::Elements*>(self);
}

char*
anitomy_elements_get(AnitomyElements* self, AnitomyElementCategory category)
{
    char* ret;

    ret = wide_to_narrow(reinterpret_cast<anitomy::Elements*>(self)->get(static_cast<anitomy::ElementCategory>(category)).c_str());

    return ret;
}

