### 新式for循环:

```c++
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
 
int StrToInt3(string str)
    {
        int value = 0;
        for (auto ch : str)//ch依次取的是str里面的字符,直到取完为止
        {
            value *= 10;
            value += (ch - '0');
        }
        return value;
    }
 
int main()
{
    cout << StrToInt3("1234") << endl;
    system("pause");
    return 0;
}
```

