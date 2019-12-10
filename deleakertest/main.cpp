#include "..\deleaker\mem2.h"

#include "..\include\Lib_Clara.h"
#include "..\include\Dir.h"

#include "..\classlib\cl.h"
#include "mybook.h"

void elf_exit(void)
{
	trace_done();
	SUBPROC( mfree_adr(), &ELF_BEGIN );
}

class NestedAllocs
{
	char* x;
public:
	NestedAllocs()
	{
		x=new char[10];
	}
	~NestedAllocs()
	{
		delete x;
	}
};

int main (void)
{
	trace_init(L"deleakertest.txt");

	NestedAllocs* nested=new NestedAllocs; //���� ��������� �������. ��� ���� ��� � mem2.cpp ����
	delete nested;                         //���������� ��������, �� �� ��� ���

	char* x=new char[3]; //���������
	new ((char*)1) char; //placement new. �� ������ �����������.

	delete[] x;
	new char[5];  //�� ���������
	List_Create();   //�� ���������
	malloc(3);    //�� ���������


	new CMyBook();  //���������. ��� ����� ������� - �������� ����. ���� ���� ���� � ���� ����

	u16 t=TIMER_SET(10000,CMyBook::onTimer,NULL); //���������
	Timer_Kill(&t);

	return 0;
}
