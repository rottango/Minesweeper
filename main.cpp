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
      cout << i << " ";
      for (int j = 0; j < y; j++)
      {
        cout << j << " ";
        boardPopulated.at(i).push_back('-');
        cout << j << "";
      }
      cout << endl;
    }
    cout << "Finished initlializating the board." << endl;
    cout << "Starting the generation of mines' positions..." << endl;
    generateMinePositions(mines, (x * y), bombPositions);
    plantMines(boardPopulated, bombPositions);
  }

  // bombPositions zaczyna od indexu 0, wartosci min 1
  // pos odnosii sie do wartosci 1 do N
  // index odnosi sie do kolejnych liczb w bombPositions
  // tutaj trzeba naprawic funkcje, poniewaz jest blad gdzies w pos i index

  void plantMines(vector<vector<char>> &boardPopulated, vector<int> &bombPositions)
  {
    cout << "Starting planting mines..." << endl;
    sort(bombPositions.begin(), bombPositions.end());
    displayBombPositions();
    int pos = 0;
    int index = 0;
    for (int i = 0; i < boardPopulated.size(); i++)
    {
      pos++;
      cout << "pos1: " << pos << endl;
      for (int j = 0; j < boardPopulated.at(i).size(); j++)
      {
        if (pos == bombPositions[index] && index < bombPositions.size())
        {
          boardPopulated[i][j] = 'X';
          index++;
        }
        if (j < boardPopulated.size())
        {
          pos++;
          cout << "pos2: " << pos << endl;
        }
      }
    }
    cout << "Finished planting mines." << endl;
  }

  // M - M integers
  // N-  range from 1..N
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
    cout << "Finished displaying the positions of bombs." << endl;
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

  cout << "displayBombPositions: " << endl;
  board.displayBombPositions();
  cout << endl;
  cout << "displayBoard: " << endl;
  board.displayBoard();
  return 0;
}