#ifdef DLL1_API
#else
#define  DLL1_API _declspec(dllimport)
#endif

//注意，此时不再需要声明方法为_declspec(dllexport)标识符了
DLL1_API int add(int a,int b);
DLL1_API int subtract(int a ,int b);

class DLL1_API Point
{
public:
	void OutPut(int x,int y);
};


