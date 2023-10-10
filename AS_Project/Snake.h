#pragma once
#pragma once
class Cell//declare class CELL
{
public:
	int x;//x coordinate
	int y;//y coordinate
	Cell(int X, int Y)//constructor
	{
		x = X;
		y = Y;
		prev = 0;
		next = 0;
	}
	Cell* prev;//prev Cell address
	Cell* next;//next Cell address
};

class Snake//declare class Snake
{
	
public:
	Cell* head;//set head pointer
	Cell* tail;//set tail pointer
	void initSnake()//make 3 cells with double linked list
	{
		Cell* nodeh = new Cell(0, 0);//the head is in center of map
		head = nodeh;
		Cell* nodem = new Cell(1, 0);//
		nodem->prev = head;
		head->next = nodem;
		Cell* nodet = new Cell(2, 0);
		nodem->next = nodet;
		nodet->prev = nodem;
		tail = nodet;
	}
};
