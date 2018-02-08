#include <iostream>
#include <string>
#include <list>
#include <queue>

using namespace std;

void getLinkedList(short rings, short rows, short columns, int** arr, queue< int, list<int> >** arrQ) {
	for (size_t c = 0; c < rings; c++)
	{
		short cacheM = rows - 1 - c, cacheN = columns - 1 - c;
		arrQ[c] = new queue< int, list<int> >;
		for (size_t i = c; i < cacheN; i++) arrQ[c]->push(arr[c][i]);
		for (size_t i = c; i < cacheM; i++) arrQ[c]->push(arr[i][cacheN]);
		for (size_t i = cacheN; i > c; i--) arrQ[c]->push(arr[cacheM][i]);
		for (size_t i = cacheM; i > c; i--) arrQ[c]->push(arr[i][c]);
	}
}

void rotate(int rotations, queue< int, list<int> >** arrQ, short rings) {
	for (size_t c = 0; c < rings; c++)
	{
		int RR = rotations % arrQ[c]->size();
		for (size_t i = 0; i < RR; i++)
		{
			int temp = arrQ[c]->front();
			arrQ[c]->pop();
			arrQ[c]->push(temp);
		}
	}
}

void replaseElemInArr(short rings, short rows, short columns, int** arr, queue< int, list<int> >** arrQ) {
	for (size_t c = 0; c < rings; c++)
	{
		short cacheM = rows - 1 - c, cacheN = columns - 1 - c;
		for (size_t i = c; i < cacheN; i++)
		{
			arr[c][i] = arrQ[c]->front();
			arrQ[c]->pop();
		}
		for (size_t i = c; i < cacheM; i++)
		{
			arr[i][cacheN] = arrQ[c]->front();
			arrQ[c]->pop();
		}
		for (size_t i = cacheN; i > c; i--)
		{
			arr[cacheM][i] = arrQ[c]->front();
			arrQ[c]->pop();
		}
		for (size_t i = cacheM; i > c; i--)
		{
			arr[i][c] = arrQ[c]->front();
			arrQ[c]->pop();
		}
	}
}

void showArr(int** arr, short rows, short columns) {
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	short rows, columns, rings;
	int rotations;
	cin >> rows >> columns >> rotations;
	int** arr = new int*[rows];
	for (size_t i = 0; i < rows; i++)
	{
		arr[i] = new int[columns];
		for (size_t j = 0; j < columns; j++)
		{
			cin >> arr[i][j];
		}
	}
	rings = (rows <= columns ? rows : columns) / 2;
	queue< int, list<int> >** arrQ = new queue< int, list<int> >*[rings];
	getLinkedList(rings, rows, columns, arr, arrQ);
	rotate(rotations, arrQ, rings);
	replaseElemInArr(rings, rows, columns, arr, arrQ);
	showArr(arr, rows, columns);


	return 0;
}

