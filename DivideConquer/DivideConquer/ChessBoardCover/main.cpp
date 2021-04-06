/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
ChessBoardCover
*/
#include <iostream>
using namespace std;
void ChessBoard(int tr, int tc, int dr, int dc, int size)
{
	int tile = 0;
	if (size == 1) return;
	int t = tile++;
	int s = size / 2;

	if (dr < tr + s&&dc < tc + s)
		ChessBoard(tr, tc, dr, dc, s);
	else{
		Board[tr + s - 1][tc + s - 1] = t;
		ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
	}
	if (dr < tr + s&&dc >= tc + s)
		ChessBoard(tr, tc + s, dr, dc, s);
	else{
		Board[tr + s - 1][tc + s] = t;
		ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
	}
	if (dr >= tr + s&&dc < tc + s)
		ChessBoard(tr + s, tc, dr, dc, s);
	else{
		Board[tr + s][tc + s - 1] = t;
		ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);

	}
	if (dr >= tr + s&&dc >= tc + s)
		ChessBoard(tr + s, tc + s, dr, dc, s);
	else{
		Board[tr + s][tc + s] = t;
		ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
	}
}
int main(int argc, char* argv[])
{

}