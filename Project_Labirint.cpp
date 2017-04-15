// Project_Labirint.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "string.h"
#include "conio.h"
#include "fstream"
#include "windows.h"
#include "stack.cpp"


using namespace std;

struct cds
{
	int _i, _j;
	char _dir;
};
class labirint
{
private:
	cds _exit, _start, _turtle;
	int _size, _size2, _sizest;
	char **_str;
	stack <cds> _stack;
public:
	labirint()
	{
		_size2 = 0;
		_size = 0;
		_str = new char*[_size];
		_exit._i = 0;
		_exit._j = 0;
		_start._i = 0;
		_start._j = 0;
		_turtle._i = 0;
		_turtle._j = 0;
		_sizest = 0;
	}
	void input()
	{
		if (_size2 != 0) { return; }
		char *ifstr = new char[255];
		ifstream ifs("labirint.txt");
		if (!ifs) { return; }
		while (ifs.getline(ifstr, 254))
		{
			if (_size == 0)
			{
				_str = new char *[_size + 1];
			}
			else
			{
				char **tmp = new char *[_size + 1];
				for (int i = 0; i<_size; i++)
				{
					tmp[i] = _str[i];
				}
				delete[] _str;
				_str = tmp;
			}
			_str[_size] = new char[strlen(ifstr) + 1];
			strcpy(_str[_size], ifstr);
			_size++;
		}
		ifs.close();
		while (_str[0][_size2] != NULL)
		{
			_size2++;
		}
		while (_start._i<_size)
		{
			_start._j = 0;
			while (_str[_start._i][_start._j] != '\0')
			{
				if (_str[_start._i][_start._j] == '2')
				{
					break;
				}
				_start._j++;
			}
			if (_str[_start._i][_start._j] == '2')break;
			_start._i++;
		}
		while (_exit._i<_size)
		{
			_exit._j = 0;
			while (_str[_exit._i][_exit._j] != '\0')
			{
				if (_str[_exit._i][_exit._j] == '1') { break; }
				_exit._j++;
			}
			if (_str[_exit._i][_exit._j] == '1') { break; }
			_exit._i++;
		}
	}
	void pushst() { _stack.push(_turtle); _sizest++; }
	void popst() { _stack.pop(); _sizest--; }
	bool srhend()
	{
		if ((_turtle._i - 1 == _exit._i)&(_turtle._j == _exit._j))
		{
			pushst();
			_turtle._i -= 1;
			pushst();
			specialprint();
			return true;
		}
		else
		{
			if ((_turtle._i + 1 == _exit._i)&(_turtle._j == _exit._j))
			{
				pushst();
				_turtle._i += 1;
				pushst();
				specialprint();
				return true;
			}
			else
			{
				if ((_turtle._i == _exit._i)&(_turtle._j + 1 == _exit._j))
				{
					pushst();
					_turtle._j += 1;
					pushst();
					specialprint();
					return true;
				}
				else
				{
					if ((_turtle._i == _exit._i)&(_turtle._j - 1 == _exit._j))
					{
						pushst();
						_turtle._j -= 1;
						pushst();
						specialprint();
						return true;
					}
				}
			}
		}
		return false;
	}
	void start()
	{
		system("cls");
		_turtle._i = _start._i;
		_turtle._j = _start._j;
		specialprint();
		Sleep(500);
		if (srhend() == true) { return; }
		if (_str[_turtle._i][_turtle._j - 1] == '0')
		{
			if (_str[_turtle._i - 1][_turtle._j] == '3')
			{
				_turtle._dir = 'u';
				pushst();
				_turtle._i--;
				moveup();
				return;
			}
			else
			{
				if (_str[_turtle._i][_turtle._j + 1] == '3')
				{
					_turtle._dir = 'r';
					pushst();
					_turtle._j++;
					moveright();
					return;
				}
			}
		}
		else
		{
			_turtle._dir = 'l';
			pushst();
			_turtle._j--;
			moveleft();
			return;
		}
		_turtle._dir = 'd';
		pushst();
		_turtle._i += 1;
		movedown();
		return;
	}
	void moveup()
	{
		specialprint();
		Sleep(500);
		if (srhend() == true) { return; }
		if (_str[_turtle._i][_turtle._j - 1] == '0')
		{
			if (_str[_turtle._i - 1][_turtle._j] >= '3')
			{
				if (_stack.get_el(1)._dir == 'd') { popst(); }
				else { pushst(); }
				_turtle._i -= 1;
				moveup();
				return;
			}
			else
			{
				if (_str[_turtle._i][_turtle._j + 1] >= '3')
				{
					if (_stack.get_el(1)._dir == 'l') { popst(); }
					else
					{
						_turtle._dir = 'r';
						pushst();
					}
					_turtle._j += 1;
					moveright();
					return;
				}
			}
		}
		else
		{
			if (_stack.get_el(1)._dir == 'r') { popst(); }
			else
			{
				_turtle._dir = 'l';
				pushst();
			}
			_turtle._j -= 1;
			moveleft();
			return;
		}
		if (_stack.get_el(1)._dir == 'u') { popst(); }
		else
		{
			_turtle._dir = 'd';
			pushst();
		}
		_turtle._i += 1;
		movedown();
		return;
	}
	void moveright()
	{
		specialprint();
		Sleep(500);
		if (srhend() == true) { return; }
		if (_str[_turtle._i - 1][_turtle._j] == '0')
		{
			if (_str[_turtle._i][_turtle._j + 1] >= '3')
			{
				if (_stack.get_el(1)._dir == 'l') { popst(); }
				else { pushst(); }
				_turtle._j += 1;
				moveright();
				return;
			}
			else
			{
				if (_str[_turtle._i + 1][_turtle._j] >= '3')
				{
					if (_stack.get_el(1)._dir == 'u') { popst(); }
					else
					{
						_turtle._dir = 'd';
						pushst();
					}
					_turtle._i += 1;
					movedown();
					return;
				}
			}
		}
		else
		{
			if (_stack.get_el(1)._dir == 'd') { popst(); }
			else
			{
				_turtle._dir = 'u';
				pushst();
			}
			_turtle._i -= 1;
			moveup();
			return;
		}
		if (_stack.get_el(1)._dir == 'r') { popst(); }
		else
		{
			_turtle._dir = 'l';
			pushst();
		}
		_turtle._j -= 1;
		moveleft();
		return;
	}
	void moveleft()
	{
		specialprint();
		Sleep(500);
		if (srhend() == true) { return; }
		if (_str[_turtle._i + 1][_turtle._j] == '0')
		{
			if (_str[_turtle._i][_turtle._j - 1] >= '3')
			{
				if (_stack.get_el(1)._dir == 'r') { popst(); }
				else { pushst(); }
				_turtle._j -= 1;
				moveleft();
				return;
			}
			else
			{
				if (_str[_turtle._i - 1][_turtle._j] >= '3')
				{
					if (_stack.get_el(1)._dir == 'd') { popst(); }
					else
					{
						_turtle._dir = 'u';
						pushst();
					}
					_turtle._i -= 1;
					moveup();
					return;
				}
			}
		}
		else
		{
			if (_stack.get_el(1)._dir == 'u') { popst(); }
			else
			{
				_turtle._dir = 'd';
				pushst();
			}
			_turtle._i += 1;
			movedown();
			return;
		}
		if (_stack.get_el(1)._dir == 'l') { popst(); }
		else
		{
			_turtle._dir = 'r';
			pushst();
		}
		_turtle._j += 1;
		moveright();
		return;
	}
	void movedown()
	{
		specialprint();
		Sleep(500);
		if (srhend() == true) { return; }
		if (_str[_turtle._i][_turtle._j + 1] == '0')
		{
			if (_str[_turtle._i + 1][_turtle._j] >= '3')
			{
				if (_stack.get_el(1)._dir == 'u') { popst(); }
				else { pushst(); }
				_turtle._i += 1;
				movedown();
				return;
			}
			else
			{
				if (_str[_turtle._i][_turtle._j - 1] >= '3')
				{
					if (_stack.get_el(1)._dir == 'r') { popst(); }
					else
					{
						_turtle._dir = 'l';
						pushst();
					}
					_turtle._j -= 1;
					moveleft();
					return;
				}
			}
		}
		else
		{
			if (_stack.get_el(1)._dir == 'l') { popst(); }
			else
			{
				_turtle._dir = 'r';
				pushst();
			}
			_turtle._j += 1;
			moveright();
			return;
		}
		if (_stack.get_el(1)._dir == 'd') { popst(); }
		else
		{
			_turtle._dir = 'u';
			pushst();
		}
		_turtle._i -= 1;
		moveup();
		return;
	}
	void specialprint()
	{
		int a, b;
		system("cls");
		for (a = 0; a<_turtle._i; a++)
		{
			for (b = 0; b<_size2; b++)
			{
				if (_str[a][b] == '0')
				{
					cout << char(219);
				}
				if (_str[a][b] != '0')
				{
					cout << " ";
				}
			}
			cout << endl;
		}
		for (b = 0; b<_turtle._j; b++)
		{
			if (_str[a][b] != '0')
			{
				cout << " ";
			}
			if (_str[a][b] == '0')
			{
				cout << char(219);
			}
		}
		cout << char(1);
		for (b = _turtle._j + 1; b<_size2; b++)
		{
			if (_str[a][b] != '0')
			{
				cout << " ";
			}
			if (_str[a][b] == '0')
			{
				cout << char(219);
			}
		}
		cout << endl;
		for (a++; a<_size; a++)
		{
			for (int b = 0; b<_size2; b++)
			{
				if (_str[a][b] != '0')
				{
					cout << " ";
				}
				if (_str[a][b] == '0')
				{
					cout << char(219);
				}
			}
			cout << endl;
		}
	}
	void printst()
	{
		for (int i = _sizest, j = 1; i>0; i--, j++)
		{
			cout << j << ". (" << _stack.get_el(i)._i + 1 << ";" << _stack.get_el(i)._j + 1 << ")" << endl;
		}
	}
	void printlab()
	{
		for (int i = 0; i<_size; i++)
		{
			for (int j = 0; j<_size2; j++)
			{
				if (_str[i][j] == '0')
				{
					cout << char(219);
				}
				if (_str[i][j] != '0')
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	~labirint()
	{
		delete[]_str;
	}
};
int cinel()
{
	int a = 0;
	cin >> a;
	return a;
}
int main()
{
	labirint lab;
	bool b = true;
	while (b)
	{
		cout << "1 - Take the labyrinth; \n2 - Start;  \n3 - Print the labyrinth; \n4 - Print the distance. \nPress 0 to exit. ";
		switch (cinel())
		{
		case 1:
			system("cls");
			lab.input();
			break;
		case 2:
			system("cls");
			lab.input();
			lab.start();
			_getch();
			system("cls");
			break;
		case 3:
			system("cls");
			lab.printlab();
			_getch();
			system("cls");
			break;
		case 4:
			system("cls");
			lab.printst();
			_getch();
			system("cls");
			break;
		case 0:
			system("cls");
			b = false;
			break;
		default:
			system("cls");
			cout << "Invalid number. Try again.\n";
		}
	}
}

