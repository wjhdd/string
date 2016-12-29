#include<iostream>
#include<cstring>
using namespace std;

class String
{
	friend ostream& operator<<(ostream& os, const String& s);
	
public:
	String (char* str="")
		:_str(new char[strlen(str)+1+4]),_sz(strlen(str)),_capacity(strlen(str)+1)
	{
		strcpy(_str, str);
	}
	~String()      //析构
    {  
        if (_str != NULL)  
        {  
            delete[] _str;  
            _sz= 0;  
            _capacity= 0;  
        }  
    }
	String(const String &s)  //拷贝构造
        :_str(new char[strlen(s._str) + 1])  
    {  
        _sz = s._sz;  
        _capacity = s._capacity;  
        strcpy(_str, s._str);  
    }
	const char *c_str() const  //获取c风格的字符指针
    {  
        return _str;  
    }
	String& operator=(String s)     //赋值运算符重载  
    {  
        _sz = s._sz;  
        _capacity = s._capacity;  
        std::swap(s._str, _str);  
        return *this;  
    }
	char operator[](int sz)  //[]的重载
    {  
        return _str[sz];  
    }  
    String& operator+=(const String& s)  //+=重载
    {  
        CheckCapacity(strlen(s._str));  
        strcat(_str, s._str);  
        return *this;  
    }
	size_t	size()const 
	{
		return strlen(_str);
	}

	void  PushBack(char c)  //尾插
	{
		CheckCapacity(1);
		_str[_sz++]=c;
		_str[_sz]='\0';
	}

	 String& Insert(size_t pos,const char *str)//指定位置插入
	 {
		 char*tmp = new char[strlen(_str+pos)];
		 strcpy(tmp,_str+pos);
		 CheckCapacity(strlen(str));
		 while (*str)
		 {
			 _str[pos++]= *str;
			 str++;
		 }
		 strcpy(_str+pos,tmp);
		 return *this;
	 }
	 
	

	void CheckCapacity(int sz)   //检测容量是否够用，不够则重新开辟  
    {  
        int tmp = 0;
        if (_capacity<(sz + _sz + 1))  
        {  
            tmp = (2 * _capacity > _capacity + sz) ? 2 * _capacity : _capacity + sz;  
            char *str = new char[_capacity];  
            strcpy(str, _str);  
            delete[] _str;  
            _str = new char[tmp];  
            strcpy(_str, str);  
            _capacity = tmp;  
        }  
    }

private:
	char* _str;
	int _sz;
	int _capacity;
};
ostream& operator<<(ostream& os, const String& s)  //输出运算符重载
{  
    os << s._str;  
    return os;  
} 

void test()
{
	String s1("abc");  
    String s2(s1);
	cout<<s2<<endl;
    String s3;
	s3=s1;
	cout<<s3<<endl;
	String s4("def");
	s1+=s4;
	cout<<s1<<endl;
	cout<<s1[2]<<endl;
	cout<<s1.size()<<endl;
	s1.PushBack('p');
	s1.PushBack('p');
	cout<<s1<<endl;
	s1.Insert(3," ooooo ");
	cout<<s1<<endl;

}

int main()
{
	test();
	getchar();
	return 0;
}