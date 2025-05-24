#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

class board
{
private:
  int x;
  int y;
  int mines;
  vector<vector<char>> boardPopulated;
  vector<int> bombPositions;

public:
  board(int x, int y, int mines)
  {
    this->x = x;
    this->y = y;
    this->mines = mines;
    populateBoard(x, y, mines, boardPopulated);
  }

  void populateBoard(int x, int y, int mines, vector<vector<char>> &boardPopulated)
  {
    cout << "Starting the initialization of the board..." << endl;

    boardPopulated.resize(x);
    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < y; j++)
      {
        boardPopulated.at(i).push_back('-');
      }
    }
    cout << "Finished initlializating the board." << endl;
    cout << "Starting the generation of mines' positions..." << endl;
    generateMinePositions(mines, (x * y), bombPositions);
    displayBoard();
    plantMines(boardPopulated, bombPositions);
    displayBoard();
    generateNumbers(boardPopulated);
    displayBoard();
  }

  void plantMines(vector<vector<char>> &boardPopulated, vector<int> bombPositions)
  {
    displayBombPositions();
    cout << "Starting planting mines..." << endl;
    while (bombPositions.size() != 0)
    {
      int pos = bombPositions.at(0) - 1;
      int i = pos / y;
      int j = pos - y * i;
      boardPopulated.at(i).at(j) = 'X';
      bombPositions.erase(bombPositions.begin());
    }

    cout << "Finished planting mines." << endl;
  }

  // M - M integers
  // N-  range from 1..N
  // Floyd's Algorithm implementantion from  "More Programming Pearls, connfesions of a coder byJon Bentley"
  vector<int> generateMinePositions(int M, int N, vector<int> &bombPositions)
  {
    if (M == 0)
    {
      cout << "Finishing the generation of mines' positions." << endl;
      return bombPositions;
    }
    else
    {
      generateMinePositions(M - 1, N - 1, bombPositions);
      int T = rand() % N + 1;
      auto it = find(bombPositions.begin(), bombPositions.end(), T);
      if (it == bombPositions.end())
      {
        bombPositions.push_back(T);
      }
      else
      {
        bombPositions.push_back(N);
      }
      return bombPositions;
    }
  }

  void displayBombPositions()
  {
    cout << "Displaying the positions of bombs..." << endl;
    for (int i = 0; i < bombPositions.size(); i++)
    {
      cout << bombPositions.at(i) << " ";
    }
    cout << endl
         << "Finished displaying the positions of bombs." << endl;
  }

  void displayBoard()
  {
    cout << "Displaying the board..." << endl;
    for (int i = 0; i < boardPopulated.size(); i++)
    {
      for (int j = 0; j < boardPopulated.at(i).size(); j++)
      {
        cout << boardPopulated.at(i).at(j) << " ";
      }
      cout << endl;
    }
    cout << "Displaying the board." << endl;
  }

  // szukamy jedynie bomb
  void generateNumbers(vector<vector<char>> &boardPopulated)
  {
    cout << "Starting to generate numbers on the board..." << endl;
    int cells = x * y;
    int i = 0, j = 0;
    while (cells != 0)
    {
      cout << "checking for i: " << i << " j: " << j << endl;
      // czy cell jest bomba;
      if (boardPopulated.at(i).at(j) == 'X')
      {
        cout << "i: " << i << " j: " << j << " is a bomb" << endl;
      }
      // jak nie jest bomba, to sprawdz czy sa bomby dookola
      else
      {
        int bombCounter = 0;
        for (int k = i - 1; k <= i + 1; k++)
        {
          cout << "1. k: " << k << endl;
          if (k >= 0 && k <= x - 1)
          {
            cout << "2. in: " << endl;

            for (int p = j - 1; p <= j + 1; p++)
            {
              cout << "3. p: " << p << endl;

              if (p >= 0 && p <= y - 1)
              {
                cout << "4. in: " << endl;
                if (boardPopulated.at(k).at(p) == 'X')
                {
                  cout << "5. in: " << endl;
                  bombCounter++;
                }
              }
            }
          }
        }
        boardPopulated.at(i).at(j) = '0' + bombCounter;
        cout << "i: " << i << " j: " << j << " is number: " << bombCounter << endl;
      }
      cells--;
      cout << "cells left: " << cells << endl
           << "---------------" << endl;

      if (j == y - 1)
      {
        i++;
        j = 0;
      }
      else
      {
        j++;
      }
    }
    cout << "Finished generating numbers on the board." << endl;
  }

  int getX()
  {
    return x;
  }
  int getY()
  {
    return y;
  }
  int getMines()
  {
    return mines;
  }
  vector<int> getBombPositions()
  {
    return bombPositions;
  }
  void setX(int x)
  {
    this->x = x;
  }
  void setY(int y)
  {
    this->y = y;
  }
  void setMines(int mines)
  {
    this->mines = mines;
  }
};

int main()
{
  srand(time(NULL));
  int x, y, mines;
  cout << "Provide board size x: ";
  cin >> x;
  cout << "Provide board size y: ";
  cin >> y;
  cout << "Provide board mines: ";
  cin >> mines;
  board board(x, y, mines);

  int x1 = board.getX();
  int y1 = board.getY();
  int mines1 = board.getMines();

  return 0;
}