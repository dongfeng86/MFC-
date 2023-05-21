


int add(int a,int b);
int subtract(int a ,int b);

class Point
{
public:
	//这里面有个神奇的事情，如果在def文件中导出构造函数或者析构函数，会出错，不知道为什么
	Point();
	~Point();
	void OutPut(int x,int y);
private:
	double m_dXPoint;
	double m_dYPoint;
};


