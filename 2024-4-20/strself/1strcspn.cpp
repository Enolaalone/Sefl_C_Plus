#include <cstdio>
#include <cstring>
#include <unordered_set>
using namespace std;


size_t strcspn(const char *str1, const char *str2){
    unordered_set<char>str;

    for (int i;str2[i]!='\0';i++)
    {
        str.insert(str2[i]);
    }

    for (size_t i = 0; i < strlen(str1); i++)
    {
        if(str.find(str1[i])!=str.end())return i+1;
    }
    return -1;


}
