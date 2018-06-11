// opa-md-x64.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "opa-md-x64.h"


// 这是导出变量的一个示例
OPAMDX64_API int nopamdx64=0;

// 这是导出函数的一个示例。
OPAMDX64_API int fnopamdx64(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 opa-md-x64.h
Copamdx64::Copamdx64()
{
    return;
}
