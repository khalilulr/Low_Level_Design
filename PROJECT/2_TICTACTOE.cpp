#include<bits/stdc++.h>
using namespace std;

struct Move {
    int r;
    int c;
    int player;
};

class Board {
private:
    vector<vector<char>> board;
    int cur_player;

    bool isValid(int r, int c) {
        return r >= 0 && r < 3 &&
               c >= 0 && c < 3 &&
               board[r][c] == ' ';
    }

public:
    Board() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        cur_player = 1;
    }

    int getCurPlayer() {
        return cur_player;
    }

    void changeTurn() {
        cur_player == 1 ? cur_player = 2 : cur_player = 1;
    }

    bool move(Move m) {
        int r = m.r;
        int c = m.c;
        int player = m.player;

        if (!isValid(r, c)) {
            cout << "Wrong move\n";
            return false;
        }

        board[r][c] = player == 1 ? 'X' : 'O';
        return true;
    }

    bool checkWinner() {

        // Rows and columns
        for (int i = 0; i < 3; i++) {

            if (board[i][0] != ' ' &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2]) {
                return true;
            }

            if (board[0][i] != ' ' &&
                board[0][i] == board[1][i] &&
                board[1][i] == board[2][i]) {
                return true;
            }
        }

        // Main diagonal
        if (board[0][0] != ' ' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) {
            return true;
        }

        // Other diagonal
        if (board[0][2] != ' ' &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0]) {
            return true;
        }

        return false;
    }

    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];

                if (j != 2)
                    cout << " | ";
            }
            cout << "\n";

            if (i != 2)
                cout << "---------\n";
        }
    }

    bool isDraw(){
        for(auto row:board){
            for(auto el:row)
                if(el==' ')
                    return false;
        }
        return true;
    }
};

int main() {

    Board board;

    while (true) {

        board.printBoard();

        int r, c;

        cout << "Player " << board.getCurPlayer()
             << " enter row and column: ";

        cin >> r >> c;

        Move m = {r, c, board.getCurPlayer()};

        bool isValidMove=board.move(m);

        if (board.checkWinner() || board.isDraw()) {
            board.printBoard();

            cout << "Player "
                 << m.player
                 << " wins!\n";

            break;
        }
        if(isValidMove)
            board.changeTurn();
    }

    return 0;
}