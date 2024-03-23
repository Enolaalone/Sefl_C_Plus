#include <corecrt_internal.h>
#include <ctype.h>
// #include <locale.h>
#include <string.h>
#include <errno.h>

extern "C" int __cdecl_memcmp(
    void const*const lhs,
    void const*const rhs,
    size_t count
    )   
{
    _VALIDATE_RETURN(lhs!=nullptr || count==0,EINVAL,_NLSCMPERROR);
    _VALIDATE_RETURN(rhs!=nullptr || count==0,EINVAL,_NLSCMPERROR);

    if(count==0) return 0;

    unsigned char const* lhs_ptr=static_cast<unsigned char const*>(lhs);
    unsigned char const* lhs_ptr=static_cast<unsigned char const*>(rhs);

    int result,remaining=count;
    do
    {
        result=__ascii_tolower(*++lhs_ptr)-__ascii_tolower(*++lhs_ptr);
    } while (result==0 && --remaining!=0);

    return result;
    


}