//本文件为该Dll2模块的头文件

#ifndef DLL_API
#define DLL_API extern "C" _declspec(dllimport)
#endif

DLL_API int Add(int a,int b);

DLL_API int SubTract(int a,int b);
