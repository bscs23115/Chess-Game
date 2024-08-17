#include<iostream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
#include<fstream>
using namespace std;
#define white 0
#define black 1
#define dim 8
#define indr 22
#define indc 57



struct position
{
	int r, c;
};
struct piece
{
	char sym;
	position pos;
	int clr;
	bool move;
};
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void selectloc(position& p)
{
	int r, c;
	getRowColbyLeftClick(r, c);
	p.r = (r - indr - 1) / 6;
	p.c = (c - indc - 1) / 6;
}
void initfromfile(const char fname[], int& turn, piece* board[][dim])
{
	char s;
	int ri, ci, cl;
	bool m;
	ifstream read(fname);
	if (!read)
	{
		gotoRowCol(0, 0);
		cout << "UNABLE TO READ FILE";
		exit(1);
	}
	read >> turn;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			read >> s;
			if (s == '-')
			{
				board[r][c] = nullptr;
			}
			else
			{
				read >> cl >> m >> ri >> ci;
				board[r][c] = new piece[1];
				board[r][c]->sym = s;
				board[r][c]->clr = cl;
				board[r][c]->move = m;
				board[r][c]->pos.r = ri;
				board[r][c]->pos.c = ci;
			}
		}
	}
}
void init(piece* board[][dim], int& turn)
{

	turn = white;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (r >= 2 && r <= 5)
			{
				board[r][c] = nullptr;
			}
			else if (r == 1)
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'p';
				board[r][c]->move = false;
			}
			else if ((r == 0 && c == 0) || (r == 0 && c == 7))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'r';
				board[r][c]->move = false;
			}
			else if ((r == 0 && c == 1) || (r == 0 && c == 6))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'h';
				board[r][c]->move = false;
			}
			else if ((r == 0 && c == 2) || (r == 0 && c == 5))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'b';
				board[r][c]->move = false;
			}
			else if ((r == 0 && c == 3))
			{

				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'q';
				board[r][c]->move = false;
			}
			else if (r == 0 && c == 4)
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = black;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'k';
				board[r][c]->move = false;
			}
			else if (r == 6)
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'P';
				board[r][c]->move = false;
			}
			else if ((r == 7 && c == 0) || (r == 7 && c == 7))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'R';
				board[r][c]->move = false;
			}
			else if ((r == 7 && c == 1) || (r == 7 && c == 6))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'H';
				board[r][c]->move = false;
			}
			else if ((r == 7 && c == 2) || (r == 7 && c == 5))
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'B';
				board[r][c]->move = false;
			}
			else if ((r == 7 && c == 3))
			{

				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'Q';
				board[r][c]->move = false;
			}
			else if (r == 7 && c == 4)
			{
				board[r][c] = new piece[1];
				board[r][c]->clr = white;
				board[r][c]->pos.c = c;
				board[r][c]->pos.r = r;
				board[r][c]->sym = 'K';
				board[r][c]->move = false;
			}
		}
	}


}
void turnmsg(int turn)
{
	gotoRowCol(5, 72);
	SetClr(6);
	cout << "PLAYER " << turn + 1 << "'s TURN" << endl;
}
void selectposition(string msg, position& p)
{
	char a, b;
	gotoRowCol(15, 0);
	cout << msg;
	cin >> a >> b;
	a = tolower(a);
	p.c = a - 'a';
	b -= '1';
	p.r = 8 - b - 1;
}
void updateboard(piece* board[][dim], position s, position d)
{
	board[d.r][d.c] = board[s.r][s.c];
	board[s.r][s.c] = nullptr;
}
void turnchange(int& turn)
{
	turn++;
	turn %= 2;
}
bool isvalidsource(piece* board[][dim], position p, int turn)
{
	if (p.r > 7 || p.r < 0 || p.c>7 || p.c < 0)
		return false;
	if (board[p.r][p.c] != nullptr)
	{
		if (board[p.r][p.c]->clr == turn)
			return true;
	}
	return false;
}
bool isvaliddestination(piece* board[][dim], position p, int turn)
{
	if (board[p.r][p.c] == nullptr)
		return true;
	return board[p.r][p.c]->clr != turn;
}
bool isverticalmove(position s, position d)
{
	return (s.c == d.c && abs(s.r - d.r) > 0);
}
bool ishorizontalmove(position s, position d)
{
	return (s.r == d.r && abs(s.c - d.c) > 0);
}
bool isdiagonalmove(position s, position d)
{
	int r = abs(s.r - d.r);
	int c = abs(s.c - d.c);
	if (r == 0 || c == 0)
		return false;
	return r == c;
}
bool vpathclear(piece* board[][dim], position s, position d)
{
	int delta = s.r - d.r;
	for (int i = 1; i < abs(delta); i++)
	{
		if (delta > 0)
		{
			if (board[s.r - i][s.c] != nullptr)
				return false;
		}
		else
		{
			if (board[s.r + i][s.c] != nullptr)
				return false;
		}
	}
	return true;
}
bool hpathclear(piece* board[][dim], position s, position d)
{
	int delta = s.c - d.c;
	for (int i = 1; i < abs(delta); i++)
	{
		if (delta > 0)
		{
			if (board[s.r][s.c - i] != nullptr)
				return false;
		}
		else
		{
			if (board[s.r][s.c + i] != nullptr)
				return false;
		}
	}
	return true;
}
bool dpathclear(piece* board[][dim], position s, position d, int turn)
{
	int dr = s.r - d.r;
	int dc = s.c - d.c;
	int j = abs(dr);

	for (int i = 1; i < j; i++)
	{
		if (dr > 0)
		{
			if (dc < 0)
			{
				if (board[s.r - i][s.c + i] != nullptr)
					return false;
			}
			else if (dc > 0)
			{
				if (board[s.r - i][s.c - i] != nullptr)
					return false;
			}
		}
		else if (dr < 0)
		{
			if (dc > 0)
			{
				if (board[s.r + i][s.c - i] != nullptr)
					return false;
			}
			else if (dc < 0)
			{
				if (board[s.r + i][s.c + i] != nullptr)
					return false;
			}
		}
	}
	return true;
}
bool islower(char sym)
{
	if (sym >= 'a' && sym <= 'z')
		return true;
	return false;
}
bool isupper(char sym)
{
	if (sym >= 'A' && sym <= 'Z')
		return true;

	return false;
}
void printalphabet()
{
	for (int i = 0; i < dim; i++)
	{
		SetClr(8);
		gotoRowCol(indr - 5, indc + 2 + (i * 6));
		cout << char('a' + i);
	}
}
void printhline(int r, int sc, int ec, char sym)
{
	SetClr(8);
	for (int c = sc; c <= ec; c++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void printvline(int c, int sr, int er, char sym)
{
	SetClr(8);
	for (int r = sr; r <= er; r++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void printnum()
{
	for (int i = 0; i < dim; i++)
	{
		SetClr(8);
		gotoRowCol(indr + 2 + (i * 6), indc - 3);
		cout << 8 - i;
	}
}
void msg()
{
	gotoRowCol(87, 60);
	SetClr(6);
	cout << "CHESS IS LIFE AND THERE IS NO UNDO IN LIFE";
}
void printclr(int r, int c, int clr)
{
	SetClr(clr);
	char sym = -37;
	for (int ri = 0; ri < 5; ri++)
	{
		for (int ci = 0; ci < 5; ci++)
		{
			gotoRowCol(ri + r, ci + c);
			cout << sym;
		}
	}
}
void printboundaries(int rows, int cols)
{
	for (int i = 0; i < 5; i++)
	{
		printhline(rows / 2 - (i * 6), cols / 2 - 24, cols / 2 + 24, -37);
		printhline(rows / 2 + (i * 6), cols / 2 - 24, cols / 2 + 24, -37);
		printvline(cols / 2 - (i * 6), rows / 2 - 24, rows / 2 + 24, -37);
		printvline(cols / 2 + (i * 6), rows / 2 - 24, rows / 2 + 24, -37);
	}
}
void printsymbols(int rows, int cols, piece* board[][dim])
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] == nullptr)
			{
				if ((r % 2 == 0 && c % 2 == 1) || (r % 2 == 1 && c % 2 == 0))
					SetClr(2);
				else
					SetClr(3);

				gotoRowCol((r * 6 + 3) + (rows / 2 - 24), (c * 6 + 3) + (cols / 2 - 24));
				cout << (char)-37;
			}
			else if (board[r][c] != nullptr)
			{
				gotoRowCol((r * 6 + 3) + (rows / 2 - 24), (c * 6 + 3) + (cols / 2 - 24));
				if (islower(board[r][c]->sym))
					SetClr(6);
				else if (isupper(board[r][c]->sym))
					SetClr(15);
				cout << board[r][c]->sym;
			}
		}
	}
}
void printboard(int rows, int cols, piece* board[][dim])
{
	printalphabet();
	for (int i = 0; i < 5; i++)
	{
		printhline(rows / 2 - (i * 6), cols / 2 - 24, cols / 2 + 24, -37);
		printhline(rows / 2 + (i * 6), cols / 2 - 24, cols / 2 + 24, -37);
		printvline(cols / 2 - (i * 6), rows / 2 - 24, rows / 2 + 24, -37);
		printvline(cols / 2 + (i * 6), rows / 2 - 24, rows / 2 + 24, -37);
	}
	printnum();
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if ((r % 2 == 0 && c % 2 == 1) || (r % 2 == 1 && c % 2 == 0))
				printclr(indr + (r * 6), indc + (c * 6), 2);
			else
				printclr(indr + (r * 6), indc + (c * 6), 3);
		}
	}
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] != nullptr)
			{
				gotoRowCol((r * 6 + 3) + (rows / 2 - 24), (c * 6 + 3) + (cols / 2 - 24));
				if (islower(board[r][c]->sym))
					SetClr(6);
				else if (isupper(board[r][c]->sym))
					SetClr(15);
				cout << board[r][c]->sym;
			}
		}
	}
}
void printborder(int r, int c, int clr)
{
	SetClr(clr);
	char sym = -37;
	for (int i = 0; i <= 6; i++)
	{
		gotoRowCol(indr - 1 + (r * 6) + i, indc - 1 + (c * 6));
		cout << sym;
		gotoRowCol(indr - 1 + (r * 6), indc - 1 + (c * 6) + i);
		cout << sym;
		gotoRowCol(indr - 1 + (r * 6) + 6, indc - 1 + (c * 6) + i);
		cout << sym;
		gotoRowCol(indr - 1 + (r * 6) + i, indc - 1 + (c * 6) + 6);
		cout << sym;
	}
}
void findking(piece* board[][dim], int turn, position& k)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] != nullptr)
			{
				if (board[r][c]->clr == turn)
				{
					if (board[r][c]->sym == 'k' || board[r][c]->sym == 'K')
					{
						k.c = c;
						k.r = r;
						return;
					}
				}
			}
		}
	}
}
bool isvalidmove(piece* board[][dim], position s, position d, int turn)
{
	if (!isvalidsource(board, s, turn))
		return false;
	if (!isvaliddestination(board, d, turn))
		return false;
	char c = board[s.r][s.c]->sym;
	switch (c)
	{
	case 'r':
	case 'R':
	{
		if ((isverticalmove(s, d) && vpathclear(board, s, d)) || (ishorizontalmove(s, d) && hpathclear(board, s, d)))
			return true;

		return false;
	}
	break;
	case 'B':
	case 'b':
	{
		if (isdiagonalmove(s, d))
		{
			if (dpathclear(board, s, d, turn))
				return true;
		}
		return false;
	}
	break;
	case 'H':
	case 'h':
	{
		int dr = abs(s.r - d.r);
		int dc = abs(s.c - d.c);
		if ((dr == 1 && dc == 2) || (dr == 2 && dc == 1))
			return true;


		return false;
	}
	break;
	case 'q':
	case 'Q':
	{
		if ((isverticalmove(s, d) && vpathclear(board, s, d)) ||
			(ishorizontalmove(s, d) && hpathclear(board, s, d))
			|| (isdiagonalmove(s, d) && dpathclear(board, s, d, turn)))
			return true;

		return false;
	}
	break;
	case 'k':
	case 'K':
	{
		int dr = abs(s.r - d.r);
		int dc = abs(s.c - d.c);
		if (dr > 1 || dc > 1)
			return false;
		if (dr == 1 || dc == 1)
		{
			if ((isverticalmove(s, d) && vpathclear(board, s, d)) ||
				(ishorizontalmove(s, d) && hpathclear(board, s, d))
				|| (isdiagonalmove(s, d) && dpathclear(board, s, d, turn)))
				return true;

			return false;
		}
		return false;
	}
	break;

	case 'p':
	{
		int dr = s.r - d.r;
		int dc = abs(s.c - d.c);
		if (dr < -2 || dr >= 0 || dc > 1)
			return false;
		if (dr == -1 && dc == 1 && board[d.r][d.c] == nullptr)
			return false;
		if (s.r == 1 && dr == -2 && dc == 0 && board[s.r + 1][s.c] == nullptr
			&& board[s.r + 2][s.c] == nullptr)
			return true;
		if (dr == -1 && dc == 1 && board[d.r][d.c]->clr != turn)
			return true;
		if (dr == -1 && board[d.r][d.c] == nullptr)
			return true;
		return false;
	}
	break;
	case 'P':
	{
		int dr = s.r - d.r;
		int dc = abs(s.c - d.c);
		if (dr > 2 || dr <= 0 || dc > 1)
			return false;
		if (dr == 1 && dc == 1 && board[d.r][d.c] == nullptr)
			return false;
		if (s.r == 6 && dr == 2 && dc == 0 && board[s.r - 1][s.c] == nullptr
			&& board[s.r - 2][s.c] == nullptr)
			return true;

		if (dr == 1 && dc == 1 && board[d.r][d.c]->clr != turn)
			return true;

		if (dr == 1 && board[d.r][d.c] == nullptr)
			return true;


		return false;
	}
	break;

	default:
		return false;
	}
}
bool check(piece* board[][dim], int turn)
{
	position k;
	position s;
	turnchange(turn);
	findking(board, turn, k);
	turnchange(turn);
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			s.r = r;
			s.c = c;
			if (isvalidmove(board, s, k, turn))
			{
				return true;
			}
		}
	}
	return false;
}
void makecopy(piece* board[][dim], piece* copy[][dim])
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] == nullptr)
				copy[r][c] = nullptr;

			else
			{
				copy[r][c] = new piece[1];
				copy[r][c]->clr = board[r][c]->clr;
				copy[r][c]->sym = board[r][c]->sym;
				copy[r][c]->pos.c = board[r][c]->pos.c;
				copy[r][c]->pos.r = board[r][c]->pos.r;
				copy[r][c]->move = board[r][c]->move;
			}
		}
	}
}
void asalupdate(piece* board[][dim], position s, position d)
{
	board[s.r][s.c]->move = true;
	board[d.r][d.c] = board[s.r][s.c];
	board[s.r][s.c] = nullptr;
}
void delcopy(piece* b[][dim])
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			delete[]b[r][c];
		}
	}
}
bool selfcheck(int turn, piece* B[][dim])
{
	turnchange(turn);
	return check(B, turn);
}
void delbool(bool**& p)
{
	for (int i = 0; i < dim; i++)
	{
		delete[]p[i];
	}
	delete[]p;
	p = nullptr;
}
void highlight(position s, bool** p, int turn, int clr, piece* board[][dim])
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (p[r][c] == 1)
			{
				printborder(r, c, clr);
			}
		}
	}
}
void alllegalmoves(piece* board[][dim], position s, int turn, bool**& p)
{
	p = new bool* [dim];
	position n;
	for (int i = 0; i < dim; i++)
	{
		p[i] = new bool[dim] {0};
	}

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			n.r = r, n.c = c;
			if (isvalidmove(board, s, n, turn))
			{
				p[r][c] = 1;
			}
		}
	}
}
bool bachathai(piece* board[][dim], int turn, position pce)
{
	bool** p;
	alllegalmoves(board, pce, turn, p);
	position d;
	bool bachat = false;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (p[r][c] == 1)
			{
				d.c = c;
				d.r = r;
				updateboard(board, pce, d);
				if (!selfcheck(turn, board))
					bachat = true;

				updateboard(board, d, pce);
			}
			if (bachat)
				break;
		}
		if (bachat)
			break;
	}
	delbool(p);
	return bachat;
}
bool checkmate(piece* board[][dim], int turn)
{
	position p;
	turnchange(turn);
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] != nullptr)
			{
				if (board[r][c]->clr == turn)
				{
					p.c = c;
					p.r = r;
					if (bachathai(board, turn, p))
						return false;
				}
			}
		}
	}
	turnchange(turn);
	return true;
}

void gameend(int turn)
{
	SetClr(6);
	gotoRowCol(7, 75);
	cout << "GAME OVER";
	gotoRowCol(9, 72);
	cout << "PLAYER " << turn + 1 << " WINS!!!";
	gotoRowCol(0, 0);
}
void warning(int turn)
{
	gotoRowCol(7, 70);
	SetClr(4);
	cout << "IS's A CHECK BY PLAYER " << turn + 1;
	gotoRowCol(0, 0);
	Sleep(1200);
	for (int i = 0; i < 25; i++)
	{
		gotoRowCol(7, i + 70);
		cout << ' ';
	}
}
void drawgame()
{
	SetClr(8);
	gotoRowCol(9, 73);
	cout << "GAME DRAW !!!";
	gotoRowCol(0, 0);
	Sleep(10000000);
}

bool presentlegal(piece* board[][dim], int turn, position s)
{
	bool** p;
	alllegalmoves(board, s, turn, p);
	position d;
	bool ok = false;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (p[r][c] == 1)
			{
				d.c = c;
				d.r = r;

				updateboard(board, s, d);
				if (selfcheck(turn, board))
					p[r][c] = 0;
				updateboard(board, d, s);

				if (p[r][c] == 1)
					ok = true;
			}
			if (ok)
				break;
		}
		if (ok)
			break;
	}
	ok != ok;

	delbool(p);
	return ok;


}
bool stalemate(piece* board[][dim], int turn)
{
	position s;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] != nullptr)
			{
				if (board[r][c]->clr == turn)
				{
					s.r = r;
					s.c = c;
					if (presentlegal(board, turn, s))
						return false;
				}
			}

		}
	}
	return true;
}
void self(piece* copy[][dim], bool& rep, position source, position dest, int turn)
{

	updateboard(copy, source, dest);
	if (selfcheck(turn, copy))
		rep = true;
	updateboard(copy, dest, source);
}
bool validate(bool**& p, position d)
{
	if (p[d.r][d.c] == 1)
	{
		return true;
	}
	return false;
}
void pawnpromotion(piece* board[][dim], int turn, position d, int rows, int cols)
{
	char c = 'l';
	system("cls");
	gotoRowCol(25, 70);
	cout << "PAWN PROMOTION INTO : ";
	gotoRowCol(27, 70);
	cout << "PRESS Q/q for Queen";
	gotoRowCol(29, 70);
	cout << "PRESS B/b for Bishop";
	gotoRowCol(31, 70);
	cout << "PRESS H/h for Horse";
	gotoRowCol(33, 70);
	cout << "PRESS R/r for Rook";
	gotoRowCol(35, 70);
	cout << "Press ENTER to Continue after selection";
	c = _getch();


	switch (c)
	{
	case 'b':
	case 'B':
	{
		if (turn == 0)
		{
			c = toupper(c);
			board[d.r][d.c]->sym = c;
		}
		else if (turn == 1)
		{
			c = tolower(c);
			board[d.r][d.c]->sym = c;
		}
	}
	break;
	case 'Q':
	case 'q':
	{
		if (turn == 0)
		{
			c = toupper(c);
			board[d.r][d.c]->sym = c;
		}
		else if (turn == 1)
		{
			c = tolower(c);
			board[d.r][d.c]->sym = c;

		}
	}
	break;
	case 'R':
	case 'r':
	{
		if (turn == 0)
		{
			c = toupper(c);
			board[d.r][d.c]->sym = c;
		}
		else if (turn == 1)
		{
			c = tolower(c);
			board[d.r][d.c]->sym = c;

		}
	}
	break;
	case 'h':
	case 'H':
	{
		if (turn == 0)
		{
			c = toupper(c);
			board[d.r][d.c]->sym = c;
		}
		else if (turn == 1)
		{
			c = tolower(c);
			board[d.r][d.c]->sym = c;

		}
	}
	break;

	default:
		break;
	}
	system("cls");
	printboard(rows, cols, board);
}
bool islcast(int turn, position s, piece* board[][dim])
{
	position d;

	bool self = false;
	if (turn == 0)
	{
		if (board[s.r][s.c]->sym != 'K' || board[s.r][s.c]->move == true)
			return false;
		if (board[7][0] == nullptr || board[7][0]->sym != 'R' || board[7][0]->move == true)
			return false;
		for (int i = 1; i < 4; i++)
		{
			if (board[7][s.c - i] != nullptr)
				return false;
			int k = s.c;

			d.r = 7;
			d.c = k - i;
			updateboard(board, s, d);
			if (selfcheck(turn, board))
				self = true;
			updateboard(board, d, s);
			if (self)
				return false;
		}

		return true;
	}



	else if (turn == 1)
	{
		if (board[s.r][s.c]->sym != 'k' || board[s.r][s.c]->move == true)
			return false;
		if (board[0][0] == nullptr || board[0][0]->sym != 'r' || board[0][0]->move == true)
			return false;
		for (int i = 1; i < 4; i++)
		{
			if (board[0][s.c - i] != nullptr)
				return false;

			int k = s.c;
			d.r = 0;
			d.c = k - i;
			updateboard(board, s, d);
			if (selfcheck(turn, board))
				self = true;
			updateboard(board, d, s);
			if (self)
				return false;
		}
	}

	return true;


}
bool isrcast(int turn, position s, piece* board[][dim])
{
	position d;

	bool self = false;
	if (turn == 0)
	{
		if (board[s.r][s.c]->sym != 'K' || board[s.r][s.c]->move == true)
			return false;
		if (board[7][7] == nullptr || board[7][7]->sym != 'R' || board[7][7]->move == true)
			return false;
		for (int i = 1; i < 3; i++)
		{
			if (board[7][s.c + i] != nullptr)
				return false;
			int k = s.c;

			d.r = 7;
			d.c = k + i;
			updateboard(board, s, d);
			if (selfcheck(turn, board))
				self = true;
			updateboard(board, d, s);
			if (self)
				return false;
		}

		return true;
	}



	else if (turn == 1)
	{
		if (board[s.r][s.c]->sym != 'k' || board[s.r][s.c]->move == true)
			return false;
		if (board[0][7] == nullptr || board[0][7]->sym != 'r' || board[0][7]->move == true)
			return false;
		for (int i = 1; i < 3; i++)
		{
			if (board[0][s.c + i] != nullptr)
				return false;

			int k = s.c;
			d.r = 0;
			d.c = k + i;
			updateboard(board, s, d);
			if (selfcheck(turn, board))
				self = true;
			updateboard(board, d, s);
			if (self)
				return false;
		}
	}

	return true;


}
void refineboolmap(bool** p, int turn, piece* board[][dim], position s, bool& c, int& cas)
{
	position d;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (p[r][c] == 1)
			{
				d.r = r;
				d.c = c;
				updateboard(board, s, d);
				if (selfcheck(turn, board))
					p[r][c] = 0;
				updateboard(board, d, s);
			}
		}
	}

	if (isrcast(turn, s, board))
	{
		c = true;
		if (turn == 0)
		{
			p[7][6] = 1;
			cas = 1;
		}

		else if (turn == 1)
		{
			p[0][6] = 1;
			cas = 2;
		}

	}
	else if (islcast(turn, s, board))
	{
		c = true;
		if (turn == 0)
		{
			p[7][1] = 1;
			cas = 3;
		}

		else if (turn == 1)
		{
			p[0][1] = 1;
			cas = 4;
		}

	}
}
void writeinfile(const char fname[], int turn, piece* board[][dim])
{
	ofstream rtr(fname);
	if (!rtr)
	{
		gotoRowCol(0, 0);
		cout << "UNABLE TO WRITE ";
		exit(1);
	}
	rtr << turn << endl;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (board[r][c] == nullptr)
				rtr << '-';
			else
			{
				rtr << board[r][c]->sym << ' ' <<
					board[r][c]->clr << ' ' << board[r][c]->move << ' ' <<
					' ' << board[r][c]->pos.r << ' ' << board[r][c]->pos.c << ' ';
			}
			rtr << endl;
		}
	}
	rtr.close();

}
void ask(int& c)
{
	gotoRowCol(45, 74);
	cout << "PRESS 1 FOR NEW GAME";
	gotoRowCol(47, 74);
	cout << "PRESS 2 TO LOAD GAME";
	gotoRowCol(49, 83);
	cin >> c;
	system("cls");
}

int main()
{
	_getch();
	int rows = 91, cols = 160;
	piece* board[dim][dim];
	piece* copy[dim][dim];
	int turn;
	bool rep = false, ch = false, chalao = true;
	position source, dest;
	int choice;


	ask(choice);
	if (choice == 1)
		init(board, turn);
	else if (choice == 2)
		initfromfile("SAVE.txt", turn, board);
	bool castle = false;
	int c = -1;
	printboard(rows, cols, board);



	do
	{
		castle = false;
		c = -1;
		makecopy(board, copy);//copy created 
		if (!ch)
		{
			if (stalemate(copy, turn))
			{
				drawgame();
				chalao = false;
				break;
			}
		}
		delcopy(copy);//copy deleted
		bool** p;
		ch = false;
		cout << endl;
		turnmsg(turn);
		do {
			printboundaries(rows, cols);
			do
			{
				selectloc(source);
			} while (!isvalidsource(board, source, turn));
			makecopy(board, copy);//copy created

			alllegalmoves(board, source, turn, p);
			refineboolmap(p, turn, copy, source, castle, c);
			highlight(source, p, turn, 11, board);
			delcopy(copy);//copy deleted

			selectloc(dest);
		} while (p[dest.r][dest.c] == 0);//!validmove


		highlight(source, p, turn, 8, board);

		asalupdate(board, source, dest);
		if (castle)
		{
			position d;
			d.r = dest.r;
			position r;
			switch (c)
			{
			case 1:
			{
				d.c = dest.c - 1;
				r.r = 7;
				r.c = 7;
				asalupdate(board, r, d);
			}
			break;
			case 2:
			{
				d.c = dest.c - 1;
				r.r = 0;
				r.c = 7;
				asalupdate(board, r, d);
			}
			break;
			case 3:
			{
				d.c = dest.c + 1;
				r.r = 7;
				r.c = 0;
				asalupdate(board, r, d);
			}
			break;
			case 4:
			{
				d.c = dest.c + 1;
				r.r = 0;
				r.c = 0;
				asalupdate(board, r, d);
			}
			break;
			default:
				break;
			}
		}

		makecopy(board, copy);//copy created
		if (check(copy, turn))
		{
			if (checkmate(copy, turn))
			{
				gameend(turn);
				chalao = false;
			}
			if (chalao)
				ch = true;
		}
		delcopy(copy);//copy deleted

		if ((board[dest.r][dest.c]->sym == 'p' && dest.r == 7) ||
			(board[dest.r][dest.c]->sym == 'P' && dest.r == 0))
		{
			pawnpromotion(board, turn, dest, rows, cols);
			makecopy(board, copy);//copy created
			if (check(copy, turn))
			{
				if (checkmate(copy, turn))
				{
					gameend(turn);
					chalao = false;
				}
				if (chalao)
					ch = true;
			}
			delcopy(copy);
		}

		printsymbols(rows, cols, board);

		if (ch)
			warning(turn);
		turnchange(turn);
		writeinfile("SAVE.txt", turn, board);
		delbool(p);
	} while (chalao);

	return 0;
}