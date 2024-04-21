#include <cstdio>
#include <cstring>
#include <unordered_set>
using namespace std;


char *strpbrk(const char *str1, const char *str2)
{
    unordered_set<char>str;
    for (size_t i = 0; str2[i]!='\0'; i++)
    {
        str.insert(str2[i]);
    }
    for (size_t i = 0; str1[i]!='\0'; i++)
    {
        if(str.find(str1[i])!=str.end())return (char*)str1+i;
    }
    return NULL;
    

}