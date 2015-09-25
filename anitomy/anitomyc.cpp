#include "anitomy.h"
#include <locale>
#include <codecvt>
#include <cstring>

extern "C" 
{
    #include "anitomyc.h"
}

Anitomy* 
anitomy_new() 
{
    return reinterpret_cast<Anitomy*>(new anitomy::Anitomy());
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

char*
anitomy_elements_get(AnitomyElements* self, AnitomyElementCategory category)
{
    char* ret;
    const wchar_t* fuck;
    size_t size;

    fuck = reinterpret_cast<anitomy::Elements*>(self)->get(static_cast<anitomy::ElementCategory>(category)).c_str();
    size = sizeof(wchar_t)*wcslen(fuck);
    ret = (char*) malloc(size);
    wcstombs(ret, fuck, size);

    return ret;
}
