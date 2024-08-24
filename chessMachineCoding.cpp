#include<bits/stdc++.h>

using namespace std;

class ChessPiece {

public:

    string chessPiece;

    ChessPiece(){}

    string getPiece(){
        return chessPiece; 
    }

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol,vector<vector<ChessPiece*>>& board) = 0;

    virtual ~ChessPiece() {}

};

class King : public ChessPiece {
public:

    King(string piece){
        chessPiece = piece;
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol,vector<vector<ChessPiece*>>& board) override {
        if(abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1) 
          return true;

        return false;   
    }

};

class Queen : public ChessPiece {
public:

    Queen(string piece){
        chessPiece = piece; 
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, vector<vector<ChessPiece*>>& board)override {
        if(startRow == endRow || startCol == endCol || abs(startRow - endRow) == abs(startCol - endCol))
          return true;

        return false;  
    }

};

class Knight : public ChessPiece {
public:

    Knight(string piece){
        chessPiece = piece;
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol,vector<vector<ChessPiece*>>& board)override {
        if((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) || (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2))
            return true;

        return false;  
    }

};

class Bishop : public ChessPiece {
public:

    Bishop(string piece){
        chessPiece = piece;
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol,vector<vector<ChessPiece*>>& board) override {
        if(abs(startRow - endRow) == abs(startCol - endCol))
         return true;

        return false;

    }

};

class Rook : public ChessPiece {
public:

    Rook(string piece){
        chessPiece = piece;
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, vector<vector<ChessPiece*>>& board)override {
        
        if(startRow == endRow || startCol == endCol)
         return true;

        return false; 
    }
};

class Pawn : public ChessPiece {
public:

    Pawn(string piece){
        chessPiece = piece;
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, vector<vector<ChessPiece*>>& board)override {
        
        int steps;
        int firstRow;

        if(chessPiece[0] == 'W'){
            steps = -1;
            firstRow = 6;

        }
        else{
            steps = 1;
            firstRow = 1;
        }  

        if (startCol == endCol){

            if (endRow == startRow + steps)
              return true;
            if (endRow == startRow + 2*steps && startRow == firstRow)
               return true;

        }
        else if(abs(startCol - endCol) == 1 && endRow == startRow + steps )
          return true; 
        
        return false;

    }

};

class ChessBoard {
private:
    vector<vector<ChessPiece*>> board;
    bool currentTurn; 

    void initializeBoard() {
        
        
        for (int i = 0; i < 8; ++i) {
            board[1][i] = new Pawn("BP");
            board[6][i] = new Pawn("WP");
        }

        board[0][0] = board[0][7] = new Rook("BR");
        board[0][1] = board[0][6] = new Knight("BN");
        board[0][2] = board[0][5] = new Bishop("BB");
        board[0][3] = new Queen("BQ");
        board[0][4] = new King("BK");

        board[7][0] = board[7][7] = new Rook("WR");
        board[7][1] = board[7][6] = new Knight("WN");
        board[7][2] = board[7][5] = new Bishop("WB");
        board[7][3] = new Queen("WQ");
        board[7][4] = new King("WK");
        
        printBoard();

    }

    void printBoard() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr) {
                    cout << board[i][j]->getPiece() << " ";
                } else {
                    cout << "-- ";
                }
            }
            cout << endl;
        }
    }

    bool isValidPosition(int row, int col){
        if(row >= 8 || row < 0 && col >= 8 && col < 0)
         return false;

        return true;  
    }

    bool isValidStartPosition(int startRow,int startCol,bool){
        ChessPiece* piece = board[startRow][startCol];
        char pieceColor = piece->getPiece()[0];

        if(pieceColor == 'W' && currentTurn == true)
         return true;
        if(pieceColor == 'B' && currentTurn == false)
         return true;

        return false;     
    }

    bool isValidEndPosition(int endRow,int endCol,bool currentTurn){
        ChessPiece* piece = board[endRow][endCol];
        if(piece == nullptr)
         return true;

        char pieceColor = piece->getPiece()[0];

        if(pieceColor == 'B' && currentTurn == true)
         return true;
        if(pieceColor == 'W' && currentTurn == false)
         return true;

        return false;   

    }

    bool isValidMove(ChessPiece* piece, int startRow, int startCol, int endRow, int endCol){
        if(piece->isValidMove(startRow, startCol, endRow, endCol, board))
         return true;

        return false;  
    }

public:

    ChessBoard(){ 
        board.resize(8, vector<ChessPiece*>(8, nullptr));
        currentTurn = true;

        initializeBoard();
    }


    void move(string& start,string& end) {


        int startRow = 8 - (start[1] - '0');
        int startCol = start[0] - 'a';
        int endRow = 8 - (end[1] - '0');
        int endCol = end[0] - 'a';

        if (!isValidPosition(startRow, startCol) || !isValidPosition(endRow, endCol)) {
            cout << "Invalid Move";
            cout << endl;
            return;
        }

        if(!isValidStartPosition(startRow,startCol,currentTurn)){
            cout << "Invalid Move";
            cout << endl;
            return;
        }

        if(!isValidEndPosition(endRow,endCol,currentTurn)){
            cout << "Invalid Move";
            cout << endl;
            return;
        }

        ChessPiece* piece = board[startRow][startCol];

        cout << piece->getPiece();

        if (!isValidMove(piece, startRow, startCol, endRow, endCol)) {
            cout << "Invalid Move";
            cout << endl;
            return;
        }

        board[endRow][endCol] = piece;
        board[startRow][startCol] = nullptr;

        currentTurn = !currentTurn;

        printBoard();
  
    }

};

int main() {
    ChessBoard chessBoard;

    while (true) {
        string startPosition,endPosition;
        cin >> startPosition >> endPosition;
        
        if(startPosition ==  "exit")
         break;

        chessBoard.move(startPosition,endPosition);
    }

    return 0;
}
