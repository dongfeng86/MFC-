//本文件为该Dll2模块的头文件

#ifndef DLL_API
#define DLL_API extern "C" _declspec(dllimport)
#endif

DLL_API int add(int a,int b);

DLL_API int subtract(int a,int b);

class _declspec(dllexport) Point
{
public:
	Point();
	~Point();
	void OutPut(int x, int y);
private:
	double m_dXPoint;
	double m_dYPoint;
};

