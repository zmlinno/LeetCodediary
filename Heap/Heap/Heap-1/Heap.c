#define _CRT_SECURE_NO_WARNINGS
#include"Heap.h"

void HeapInit(Heap* hp)
{
	//�ѵĳ�ʼ��
	hp->_capacity = 10;//��ʼ����
	hp->_size = 0;
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType));

	if (hp->_a == NULL)
	{
		perror("malloc");

		exit(EXIT_FAILURE);
	}
}
// �ѵ�����
void HeapDestory(Heap* hp)
{
	if (hp->_a)
	{
		free(hp->_a);
		hp->_a = NULL;
		hp->_size = 0;
		hp->_capacity = 0;
	}
}



// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x)
{
	if (hp->_size >= hp->_capacity)
	{
		hp->_capacity *=2;
		hp->_a = (HPDataType*)realloc(hp->_a,hp->_capacity* sizeof(HPDataType));
		if (hp->_a == NULL)
		{
			perror("malloc");

			exit(EXIT_FAILURE);
		}
	}

	hp->_a[hp->_size] = x;
	int child = hp->_size;
	int parent = (child - 1) / 2;

	while (child > 0 && hp->_a[child] > hp->_a[parent])
	{
		//swap(hp->_a[child], hp->_a[parent]);
		HPDataType temp = hp->_a[child];
		hp->_a[child] = hp->_a[parent];
		hp->_a[parent] = temp;
		child = parent;

		parent = (child - 1)/2;
	}
}


// �ѵ�ɾ��
void HeapPop(Heap* hp)
{
	if (hp->_size == 0)
	{
		return;
	}

	hp->_a[0] = hp->_a[hp->_size - 1];
	hp->_size--;

	int parent = 0;
	int child = 2 * parent + 1;

	while (child < hp->_size)
	{
		if (child + 1 < hp->_size && hp->_a[child] < hp->_a[child + 1])
		{
			child++;
		}

		if (hp->_a[parent] >= hp->_a[child])
		{
			break;
		}

		//swap(hp->_a[child], hp->_a[parent]);
		HPDataType temp = hp->_a[parent];
		hp->_a[parent] = hp->_a[child];
		hp->_a[child] = temp;

		parent = child;
		child = 2 * parent + 1;
	}
}



// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp)
{
	if (hp->_size > 0)
	{
		return hp->_a[0];
	}
	else
	{
		fprintf(stderr, "Heap is empty.\n");
		exit(EXIT_FAILURE);
	}
}


// �ѵ����ݸ���
int HeapSize(Heap* hp)
{
	return hp->_size;
}


// �ѵ��п�
int HeapEmpty(Heap* hp)
{
	return hp->_size == 0;
}