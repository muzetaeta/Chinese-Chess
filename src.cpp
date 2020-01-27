#include<iostream>
#include<Windows.h>
using namespace std;
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}
class Chessboard; class Ju; class Ma; class Xiang; class Shi; class Jiang; class Bing; class Pao;
class Chess
{
protected:
	int x;
	int y;
	int owner;
public:
	Chess(int xx, int yy, int o)
	{
		x = xx;
		y = yy;
		owner = o;
	};
	virtual void print() = 0;
	virtual bool move(Chessboard& c, int newX = EOF, int newY = EOF) = 0;
	int Getowner()
	{
		if (this == NULL) return 2;
		return owner;
	}
	~Chess() { };
	friend class Chessboard;
};
class Chessboard
{
protected:
	Chess* CHESS[10][9];
	int hand = 1;
public:
	int Jiang_X1 = 9; int Jiang_X2 = 0;
	int Jiang_Y1 = 4; int Jiang_Y2 = 4;
	bool check(int x, int y)
	{
		if (CHESS[x][y])		return true;
		else return false;
	}
	Chess* output(int x, int y)
	{
		return CHESS[x][y];
	}
	Chessboard()
	{
		memset(CHESS, NULL, sizeof(CHESS));
	}
	void Chessboard_Initial();
	void Chessboard_Print()
	{
		cout << "    0  1  2  3  4  5  6  7  8" << endl << endl;
		for (int i = 0; i < 10; i++)
		{
			SetConsoleColor(7);
			cout << i << "   ";
			if (i == 4)
			{
				for (int j = 0; j < 9; j++)
				{
					if (j == 8)
					{
						if (!CHESS[i][j])
						{
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "+";
						}
						else CHESS[i][j]->print();
					}
					else
					{
						if (!CHESS[i][j])
						{
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "+--";
						}
						else {
							CHESS[i][j]->print();
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "--";
						}
					}
				}
				cout << endl;
				SetConsoleColor(FOREGROUND_BLUE);
				cout << "    |   CHUHE      HANJIE   |     ";
				SetConsoleColor(7);
				cout << "      Round:" << (hand + 1) / 2 << "    Turn:";
				if (hand % 2 == 1) cout << "red"; else cout << "green";
				SetConsoleColor(FOREGROUND_BLUE);
				cout << endl;
			}
			else
			{
				for (int j = 0; j < 9; j++)
				{
					if (j == 8)
					{
						if (!CHESS[i][j])
						{
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "+";
						}
						else CHESS[i][j]->print();
					}
					else
					{
						if (!CHESS[i][j]) {
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "+--";
						}
						else {
							CHESS[i][j]->print();
							SetConsoleColor(FOREGROUND_BLUE);
							cout << "--";
						}
					}
				}
				cout << endl;
			}
		}
		cout << endl;
	}
	~Chessboard()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 9; j++)
				if (CHESS[i][j] != NULL)
				{
					delete CHESS[i][j];
					CHESS[i][j] = NULL;
				}
	}
	void Start_The_Game()
	{
		while (!NULL)
		{
			SetConsoleColor(7);
			cout << "Please input the data of chess being moved next" << endl;
			cout << "(Format Standard : X Y NEW_X NEW_Y):";
			movechess();
		}
	}
	int Between_Calculate(int x1, int x2, int y1, int y2);
	void movechess()
	{
		int xorigin, yorigin;
		int xterm, yterm;
		int playerlasttime;
		cin >> xorigin >> yorigin;
		cin >> xterm >> yterm;
		if (hand % 4 == 1 || hand % 4 == 3) playerlasttime = 1; else playerlasttime = 0;
		if (CHESS[xorigin][yorigin])
		{
			if (CHESS[xorigin][yorigin]->owner == playerlasttime)
			{
				cout << "You can't move twice." << endl;
			}
			else {
				if (CHESS[xorigin][yorigin]->move(CB, xterm, yterm))
				{
					CHESS[xterm][yterm] = CHESS[xorigin][yorigin];
					CHESS[xorigin][yorigin] = NULL;
					hand++;
					Chessboard_Print();
				}
			}
		}
		else cout << "There's no chess." << endl;
	}
	int Jiang_Opposite_Check(int newX, int newY, int owner)
	{
		if (owner == 0 && newY == Jiang_Y2)
			return Between_Calculate(newX, Jiang_X2, newY, Jiang_Y2);
		if (owner == 1 && newY == Jiang_Y1)
			return Between_Calculate(newX, Jiang_X1, newY, Jiang_Y1);
		else return 1;
	}
	int Jiang_Opposite_Check(int yor,int ynew)
	{
		if (yor == Jiang_Y1 && yor== Jiang_Y2)
		{
			if (ynew == yor) return Between_Calculate(Jiang_X2, Jiang_X1, Jiang_Y2, Jiang_Y1);
			else return Between_Calculate(Jiang_X1, Jiang_X2, Jiang_Y1, Jiang_Y2) - 1;
		}
		if (Jiang_Y1 == Jiang_Y2)
			return Between_Calculate(Jiang_X2, Jiang_X1, Jiang_Y2, Jiang_Y1);
		else return 1;
	}
	friend class Chess;
} CB;
class Jiang :public Chess
{
public:
	Jiang(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "J";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "J";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (newY != 3 && newY != 4 && newY != 5)
		{
			cout << "You can't move like this.(Illegal)" << endl; return false;
		}
		if (((newX - x) * (newX - x) + (newY - y) * (newY - y)) != 1)
		{
			cout << "You can't move like this.(Not match the rule)" << endl; return false;
		}
		if (owner == 1)
		{
			if (newX != 0 && newX != 1 && newX != 2)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (owner == 0)
		{
			if (newX != 7 && newX != 8 && newX != 9)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (!CB.Jiang_Opposite_Check(newX, newY, owner))
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}		
		x = newX; y = newY;
		if (owner == 0) { CB.Jiang_Y1 = newY; CB.Jiang_X1 = newX; }
		else { CB.Jiang_Y2 = newY; CB.Jiang_X2 = newX; }
		return true;
	}
};
class Shi :public Chess
{
public:
	Shi(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "S";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "S";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (newY != 3 && newY != 4 && newY != 5)
		{
			cout << "You can't move like this.(Illegal)" << endl; return false;
		}
		if (((newX - x) * (newX - x) + (newY - y) * (newY - y)) != 2)
		{
			cout << "You can't move like this.(Not match the rule)" << endl; return false;
		}
		if (owner == 1)
		{
			if (newX != 0 && newX != 1 && newX != 2)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (owner == 0)
		{
			if (newX != 7 && newX != 8 && newX != 9)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (CB.Jiang_Opposite_Check(y,newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		x = newX; y = newY;
		return true;
	}
};
class Xiang :public Chess
{
public:
	friend class Chessboard;
	Xiang(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "X";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "X";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (((newX - x) * (newX - x) + (newY - y) * (newY - y)) != 8)
		{
			cout << "You can't move like this.(Not match the rule)" << endl; return false;
		}
		if (c.output((newX + x) / 2, (newY + y) / 2))
		{
			cout << "You can't move like this.(The Xiang gets blocked this way.)" << endl; return false;
		}
		if (owner == 0)
		{
			if (newX < 5)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (owner == 1)
		{
			if (newX > 4)
			{
				cout << "You can't move like this.(Illegal)" << endl; return false;
			}
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (CB.Jiang_Opposite_Check(y, newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		x = newX; y = newY;
		return true;
	}
};
class Ma :public Chess
{
public:
	Ma(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "M";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "M";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (((newX - x) * (newX - x) + (newY - y) * (newY - y)) != 5)
		{
			cout << "You can't move like this.(Not match the rule)" << endl; return false;
		}
		if (newY - y == 2)
		{
			if (c.output(x, (newY + y) / 2))
			{
				cout << "You can't move like this.(Ma gets blocked in this way.)" << endl; return false;
			}
		}
		if (newY - y == 1)
		{
			if (c.output((newX + x) / 2, y))
			{
				cout << "You can't move like this.(Ma gets blocked in this way.)" << endl; return false;
			}
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (CB.Jiang_Opposite_Check(y, newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		x = newX; y = newY;
		return true;
	}
};
class Pao :public Chess
{
public:
	Pao(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "P";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "P";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (!((newX == x && newY != y) || (newY == y && newX != x)))
		{
			cout << "You can't move like this.(Pao needs to stay at the same line.)" << endl; return false;
		}
		if ((c.Between_Calculate(x, newX, y, newY)) == 1 && CB.output(newX, newY) == NULL)
		{
			cout << "There are some chesses in the front of Pao." << endl; return false;
		}
		if ((c.Between_Calculate(x, newX, y, newY)) > 1)
		{
			cout << "There are some chesses in the front of Pao." << endl; return false;
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (CB.Jiang_Opposite_Check(y, newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		x = newX; y = newY;
		return true;
	}
};
class Ju :public Chess
{
public:
	Ju(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "C";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "C";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (!((newX == x && newY != y) || (newY == y && newX != x)))
		{
			cout << "You can't move like this.(Ju needs to stay at the same line.)" << endl; return false;
		}
		if ((c.Between_Calculate(x, newX, y, newY)) > 0)
		{
			cout << "There are some chesses in the front of Ju." << endl; return false;
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		if (CB.Jiang_Opposite_Check(y, newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		x = newX; y = newY;
		return true;
	}
};
class Bing :public Chess
{
public:
	Bing(int xx, int yy, int o) :Chess(xx, yy, o)
	{ }
	void print()
	{
		if (owner == 0)
		{
			SetConsoleColor(FOREGROUND_RED);
			cout << "B";
		}
		else
		{
			SetConsoleColor(FOREGROUND_GREEN);
			cout << "B";
		}
	}
	bool move(Chessboard& c, int newX = EOF, int newY = EOF)
	{
		if (newX >= 10 || newY >= 9 || newX < 0 || newY < 0)
		{
			cout << "You can't move like this.(X Y not in the area)" << endl; return false;
		}
		if (newX < x && owner == 1)
		{
			cout << "Bing can't move backward" << endl; return false;
		}
		else if (newX > x&& owner == 0)
		{
			cout << "Bing can't move backward" << endl; return false;
		}
		if ((x == 3 || x == 4) && owner == 1)
		{
			if (newY != y)
			{
				cout << "Bing can't move beside before getting opposite" << endl;  return false;
			}
		}
		else	if ((x == 5 || x == 6) && owner == 0)
		{
			if  (newY != y)
			{
				cout << "Bing can't move beside before getting opposite" << endl;  return false;
			}
		}
		if (CB.Jiang_Opposite_Check(y, newY) == 0)
		{
			cout << "Jiangs can't face each other." << endl;
			return false;
		}
		if (c.output(newX, newY)->Getowner() == owner)
		{
			cout << "You can't kill the chess of your own." << endl; return false;
		}
		x = newX; y = newY;
		return true;
	}
};
//已完成 兵 士 象 马 車 炮 将（尚不能解决对视问题）
void Chessboard::Chessboard_Initial()
{
	CHESS[0][0] = new Ju(0, 0, 1); CHESS[0][1] = new Ma(0, 1, 1);
	CHESS[0][2] = new Xiang(0, 2, 1); CHESS[0][3] = new Shi(0, 3, 1);
	CHESS[0][4] = new Jiang(0, 4, 1); CHESS[0][5] = new Shi(0, 5, 1);
	CHESS[0][6] = new Xiang(0, 6, 1); CHESS[0][7] = new Ma(0, 7, 1);
	CHESS[0][8] = new Ju(0, 8, 1); CHESS[2][1] = new Pao(2, 1, 1);
	CHESS[2][7] = new Pao(2, 7, 1); CHESS[3][0] = new Bing(3, 0, 1);
	CHESS[3][2] = new Bing(3, 2, 1); CHESS[3][4] = new Bing(3, 4, 1);
	CHESS[3][6] = new Bing(3, 6, 1); CHESS[3][8] = new Bing(3, 8, 1);

	CHESS[9][0] = new Ju(9, 0, 0); CHESS[9][1] = new Ma(9, 1, 0);
	CHESS[9][2] = new Xiang(9, 2, 0); CHESS[9][3] = new Shi(9, 3, 0);
	CHESS[9][4] = new Jiang(9, 4, 0); CHESS[9][5] = new Shi(9, 5, 0);
	CHESS[9][6] = new Xiang(9, 6, 0); CHESS[9][7] = new Ma(9, 7, 0);
	CHESS[9][8] = new Ju(9, 8, 0); CHESS[7][1] = new Pao(7, 1, 0);
	CHESS[7][7] = new Pao(7, 7, 0); CHESS[6][0] = new Bing(6, 0, 0);
	CHESS[6][2] = new Bing(6, 2, 0); CHESS[6][4] = new Bing(6, 4, 0);
	CHESS[6][6] = new Bing(6, 6, 0); CHESS[6][8] = new Bing(6, 8, 0);
}

int Chessboard::Between_Calculate(int x1, int x2, int y1, int y2)
{
	int betcal = 0;
	if (x1 == x2)
	{
		if (y1 >= y2)
		{
			for (int y = y1 - 1; y > y2; y--)
			{
				if (CHESS[x1][y]) betcal++;
			}
		}
		else
		{
			for (int y = y1 + 1; y < y2; y++)
			{
				if (CHESS[x1][y]) betcal++;
			}
		}
	}
	else if (y1 == y2)
	{
		if (x1 >= x2)
		{
			for (int x = x1 - 1; x > x2; x--)
			{
				if (CHESS[x][y1]) betcal++;
			}
		}
		else
		{
			for (int x = x1 + 1; x < x2; x++)
			{
				if (CHESS[x][y1]) betcal++;
			}
		}
	}
	return betcal;
}

int main()
{
	CB.Chessboard_Initial();
	CB.Chessboard_Print();
	CB.Start_The_Game();
	return 0;
}
