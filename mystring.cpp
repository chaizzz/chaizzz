#include <iostream>
#include "mystring"
using namespace std;

class mystring
{
private:
	char* buff;
public:
	mystring();
	mystring(const char* str);
	mystring(const mystring& str);//拷贝函数

	~mystring();

	int size() const;
	bool empty() const;

	void clear();
	void append(const char* str);
	void insert(int index, const char* str);
	void remove(const char* str);
	void replace(const char* oldstr, const char* newstr);
	const char* c_str() const;
	int to_int() const;
	float to_float() const;


	mystring operator+(const mystring& str) const;
	mystring& operator=(const mystring& str);
	char operator[](int index);
	bool operator==(const mystring& str);
	bool operator!=(const mystring& str);
	bool operator>(const mystring& str);
	
	friend istream& operator>>(istream& in, mystring& str);
	friend ostream& operator<<(ostream& out, const mystring& str);
};

mystring::mystring()
{
	buff = new char[2];
	buff[0] = '\0';
}

mystring::mystring(const char* str)
{
	buff = new char[strlen(str + 2)];
	strcpy(buff, str);
}

mystring::mystring(const mystring& str)
{
	buff = new char[strlen(str.buff) + 2];
	strcpy(buff, str.buff);
}

mystring::~mystring()
{
	delete []buff;
}

int mystring::size() const
{
	return strlen(buff);
}

bool mystring::empty() const
{
	return (buff[0] == '\0');
}

void mystring::clear()
{
	buff[0] = '\0';
}

mystring& mystring::operator=(const mystring& str)
{
	delete []buff;
	buff = new char[strlen(str.buff)+2];
	strcpy(buff, str.buff);

	return *this;
}

mystring mystring::operator+(const mystring& str) const
{
	mystring tmp;
	delete tmp.buff;
	tmp.buff = new char[strlen(this->buff) + strlen(str.buff) + 2];
	strcpy(tmp.buff, this->buff);
	strcat(tmp.buff, str.buff);

	return tmp;
}

ostream& operator<<(ostream& out, const mystring& str)
{
	out<<str.buff;
	return out;
}

istream& operator>>(istream& in, mystring& str)
{
	char* input_buff = NULL;
	int size = 1000;
	int cnt = 0;
	char chr;

	input_buff = new char[size+1];

	while(1)
	{
		chr = in.get();
		
		if('\n' == chr) break;
	
		input_buff[cnt++] = chr;
	
		if(size == cnt) 
		{
			size += 100;
			char* temp_buff = new char[size + 1];
			memcpy(temp_buff, input_buff, cnt);
			delete []input_buff;
			input_buff = temp_buff;
		}
	}
	input_buff[cnt] = '\0';

	delete []str.buff;

	str.buff = input_buff;

	return in;
}


int main()
{
	mystring str;
	
	cout<<str.size()<<endl;
	cout<<str.empty()<<endl;

	mystring str2("abc def");
	str2.clear();
	cout<<str2.size()<<endl;
        cout<<str2.empty()<<endl;

	str = "12345";
	str2 = str;
	str.clear();
	cout<<str2.size()<<endl;

	mystring str3;

	str3 = mystring("abc") + "def";
	
	const mystring str4("hello");

	str3 = str4 + ",world";
	
	cin>>str3;
	cout<<str3<<endl;	

	return 0;
}
