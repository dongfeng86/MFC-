#include <stdio.h>
#include <windows.h>
int main(int argc, char* argv[])
{
	printf("\n别害怕15妙后你的鼠标就可以使用了^_^\n");
	RECT rect;
	rect.bottom = 300;
	rect.right = 300;
	//-----------add------
	rect.left = 0;
	rect.top = 0;
	//-----------end-----
	ClipCursor(&rect);
	::Sleep(5000);
	ClipCursor(NULL);//释放
	return 0;
}