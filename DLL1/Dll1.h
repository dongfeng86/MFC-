#ifdef DLL1_API
#else
#define  DLL1_API _declspec(dllimport)
#endif

//ע�⣬��ʱ������Ҫ��������Ϊ_declspec(dllexport)��ʶ����
DLL1_API int add(int a,int b);
DLL1_API int subtract(int a ,int b);

class DLL1_API Point
{
public:
	void OutPut(int x,int y);
};


