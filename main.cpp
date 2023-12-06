#include <iostream>
#include <vector>
#include <stack>
#include <time.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#define RESET_COLOR "\e[m"
bool _FAST = false;
int _DELAY = 100;
int _AVERAGE = 0;
int _BEST = 0;
void wait() {
	//usleep(_DELAY * 1000);
}

const char* COLORS[] = {
	RESET_COLOR,
	"\033[22;31m",
	"\033[22;32m",
	"\033[22;34m",
	"\033[22;36m",
	"\033[22;33m",
	"\033[22;35m",
	"\033[01;31m",
	"\033[01;32m",
	"\033[01;34m",
	"\033[01;36m",
	"\033[01;33m",
	"\033[01;35m",
};

// Facile
//~ int GRID[9][9] = {
	//~ {0,1,0,6,0,0,0,0,3},
	//~ {0,3,0,0,0,5,8,6,0},
	//~ {0,8,7,3,4,9,0,5,0},
	//~ {0,0,0,7,8,0,0,4,9},
	//~ {0,2,0,0,0,0,0,1,0},
	//~ {7,4,0,0,5,1,0,0,0},
	//~ {0,7,0,2,9,6,1,8,0},
	//~ {0,6,5,8,0,0,0,9,0},
	//~ {2,0,0,0,0,7,0,3,0},
//~ };

// Démoniaque
//~ int GRID[9][9] = {
	//~ {5,0,0,0,0,8,1,0,0},
	//~ {0,8,0,1,0,0,0,0,5},
	//~ {0,0,0,9,3,0,0,7,4},
	//~ {0,0,7,0,0,0,0,0,9},
	//~ {0,0,0,0,6,0,0,0,0},
	//~ {1,0,0,0,0,0,2,0,0},
	//~ {9,6,0,0,8,2,0,0,0},
	//~ {2,0,0,0,0,9,0,5,0},
	//~ {0,0,0,6,0,0,0,0,2},
//~ };

// Démoniaque
//~ int GRID[9][9] = {
	//~ {6,0,0,0,0,1,0,5,3},
	//~ {0,0,0,0,0,0,0,0,7},
	//~ {0,0,0,6,2,0,8,0,0},
	//~ {0,0,9,4,0,8,0,0,6},
	//~ {0,0,6,0,7,0,1,0,0},
	//~ {7,0,0,1,0,5,9,0,0},
	//~ {0,0,7,0,1,4,0,0,0},
	//~ {5,0,0,0,0,0,0,0,0},
	//~ {4,9,0,5,0,0,0,0,1},
//~ };

// Antoine
//~ int GRID[9][9] = {
	//~ {0,8,0,0,3,0,0,0,1},
	//~ {1,0,2,0,0,6,3,0,0},
	//~ {0,0,0,9,0,0,2,4,0},
	//~ {8,1,0,6,0,0,0,0,0},
	//~ {0,2,3,0,0,0,8,0,0},
	//~ {5,6,0,8,0,0,0,0,0},
	//~ {0,0,0,1,0,0,4,2,0},
	//~ {9,0,1,0,0,8,7,0,0},
	//~ {0,7,0,0,6,0,0,0,3},
//~ };

//~ int GRID[9][9] = {
	//~ {0,0,0,5,0,0,0,6,0},
	//~ {8,0,9,0,0,0,0,1,0},
	//~ {1,6,0,0,8,7,0,0,0},
	//~ {3,0,0,0,2,6,0,0,0},
	//~ {0,0,7,0,1,0,6,0,0},
	//~ {0,0,0,8,5,0,0,0,0},
	//~ {0,0,0,4,7,0,0,2,1},
	//~ {0,4,0,0,0,0,9,0,8},
	//~ {0,8,0,0,0,3,0,0,0},
//~ };

int GRID[9][9] = {
	{0,8,0,5,7,0,2,0,0},
	{0,0,9,6,0,0,0,0,0},
	{4,0,1,0,9,0,0,0,0},
	{9,0,4,0,0,3,0,0,0},
	{0,0,0,0,0,0,3,0,0},
	{0,5,0,0,0,0,0,7,8},
	{0,9,0,0,0,7,5,0,0},
	{2,0,0,0,0,0,0,6,4},
	{0,0,0,0,0,6,0,2,9},
};

// Vide
//~ int GRID[9][9] = {
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
	//~ {0,0,0,0,0,0,0,0,0},
//~ };

class HypoNumber {
	public :
	int _i, _j;
	HypoNumber(int i, int j) {
		_i = i;
		_j = j;
	}
};

class Hypo {
	public :
	std::vector<HypoNumber>* _numbers;

	Hypo() {
		_numbers = new std::vector<HypoNumber>();
	}
	~Hypo() {
		delete _numbers;
	}
};

class Grid {
	public:

	int _grid[9][9];
	int* _squares[9][9];
	std::stack<Hypo*>* _hypos;
	bool _pos[9];
	bool _change;
	bool _possible;

	Grid(int grid[9][9]) {

		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				_grid[i][j] = grid[i][j];

		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				_squares[i][j] = &_grid[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3];

		_hypos = new std::stack<Hypo*>();

		if (not _FAST) {
			Draw();

			for (int i = 3; i > 0; --i) {
				std::cout << "\033[20;1HDépart dans " << i << " secondes..." << std::endl;
				//usleep(800000);
			}
			std::cout << "\033[20;1H                                         "  << std::endl;
		}
	}

	~Grid() {
		while (!_hypos->empty()) {
			delete _hypos->top();
			_hypos->pop();
		}
		delete _hypos;
	}

	void SolveNormal() {
		do {
			_change = false;
			CheckDirect();
			if (_change) continue;
			CheckTiles();
			if (_change) continue;
		    CheckBalayageLines();
		    if (_change) continue;
		    CheckBalayageColumns();
		    if (_change) continue;
		    CheckBalayageSquares();

		} while (_change);
	}

	void SolveHypo() {
		SolveHypoStep();
	}

	bool SolveHypoStep() {

		std::vector<int> pos;

		// on recherche les cases vides
		int bestPos = 10;
		int bestI, bestJ;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (not _grid[i][j]) {
					int numPos = GetPossibilities(i, j);
					if (numPos == 2) {
						pos.clear();
						for (int p = 0; p < 9; ++p) if (_pos[p]) pos.push_back(p + 1);
						bestI = i;
						bestJ = j;
						break;
					} else if (numPos < bestPos) {
						pos.clear();
						for (int p = 0; p < 9; ++p) if (_pos[p]) pos.push_back(p + 1);
						bestPos = numPos;
						bestI = i;
						bestJ = j;
					}
				}
			}
		}

		// on crée l'hypothèse avec les possibilités
		Hypo* hypo = new Hypo();
		_hypos->push(hypo);

		random_shuffle(pos.begin(), pos.end());

		for (int p = 0; p < pos.size(); ++p) {

			SetTile(bestI, bestJ, pos.at(p));

			// on avance la résolution
			bool contradiction = false;
			do {
				_change = false;
				_possible = false;

				if (not CheckTiles()) { // contradiction
					contradiction = true;
					break;
				}
				if (_change) continue;

				CheckBalayageLines();
				if (_change) continue;
				CheckBalayageColumns();
				if (_change) continue;
				CheckBalayageSquares();

			} while (_change);

			if (not contradiction && IsSolved()) {
				// Résolu ! on remonte sans annuler
				delete hypo;
				_hypos->pop();
				return true;

			} else {
				if (not contradiction && _possible) {
					// on peut encore résoudre des cases
					if (SolveHypoStep()) {
						delete hypo;
						_hypos->pop();
						return true;
					}
				}
				// on ne peut plus résoudre de cases : contradiction
				std::vector<HypoNumber>* numbers = hypo->_numbers;
				while (numbers->size() > 0) {
					SetTile(numbers->at(0)._i, numbers->at(0)._j, 0);
					numbers->erase(numbers->begin());
				}
			}
		}

		// cette hypothèse ne menait à rien, on la supprime et on remonte
		delete hypo;
		_hypos->pop();

		return false;
	}

	void SetTile(int i, int j, int num) {
		_grid[i][j] = num;

		if (num == 0) {
			if (not _FAST) {
				ClearNumber(i,j);
				wait();
			}
		} else {

			if (_hypos->size() > 0) {
				_hypos->top()->_numbers->push_back(HypoNumber(i,j));
			}
			if (not _FAST) {
				DrawNumber(i,j,num, _hypos->size() < 12 ? COLORS[_hypos->size()] : RESET_COLOR);
				wait();
			}
		}

	}

	void CheckDirect() {
		for (int i = 0; i < 9; ++i) {
			if (SolveLine(i)) _change = true;
			if (SolveColumn(i)) _change = true;
			if (SolveSquare(i)) _change = true;
		}
	}

	bool SolveLine(int line) {
		int count = 0;
		int tile;
		for (int i = 0; i < 9; ++i) {
			if (not _grid[line][i]) {
				tile = i;
				++count;
			}
			if (count > 1) return false;
		}
		if (count == 1) {
			int num = 0; // numéro manquant à trouver
			for (int i = 1; i <= 9; ++i) {
				int j;
				for (j = 0; j < 9; ++j) {
					if (_grid[line][j] == i) break;
				}
				if (j == 9) { // pas trouvé
					num = i; break;
				}
			}
			SetTile(line, tile, num);
			return true;
		}
		return false;
	}

	bool SolveColumn(int column) {
		int count = 0;
		int tile;
		for (int i = 0; i < 9; ++i) {
			if (not _grid[i][column]) {
				++count;
				tile = i;
			}
			if (count > 1) return false;
		}
		if (count == 1) {
			int num = 0;
			for (int i = 1; i <= 9; ++i) {
				int j;
				for (j = 0; j < 9; ++j) {
					if (_grid[j][column] == i) break;
				}
				if (j == 9) {
					num = i; break;
				}
			}
			SetTile(tile, column, num);
			return true;
		}
		return false;
	}

	bool SolveSquare(int square) {
		int count = 0;
		int tile;
		for (int t = 0; t < 9; ++t) {
			if (*_squares[square][t] == 0) {
				++count;
				tile = t;
			}
			if (count > 1) return false;
		}
		if (count == 1) {
			int num = 0;
			for (int n = 1; n <= 9; ++n) {
				int k;
				for (k = 0; k < 9; ++k) {
					if (*_squares[square][k] == n) break;
				}
				if (k == 9) {
					num = n; break;
				}
			}
			SetTile((square / 3) * 3 + tile/3, (square % 3) * 3 + tile % 3, num);
			return true;
		}
		return false;
	}

	bool CheckTiles() {

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (not _grid[i][j]) {

					int count = GetPossibilities(i,j);

					if (count > 0) {
						_possible = true;

						if (count == 1) {
							for (int p = 0; p < 9; ++p) {
								if (_pos[p]) {
									SetTile(i,j, p + 1);
									_change = true;
									break;
								}
							}
						}
					} else {
						return false;
					}
				}
			}
		}
		return true;
	}

	void CheckBalayageLines() {

		for (int i = 0; i < 9; ++i) {

			for (int n = 1; n <= 9; ++n) {
				int j;
				for (j = 0; j < 9; ++j) {
					if (_grid[i][j] == n) break;
				}
				if (j == 9) {
					// n n'est pas dans la ligne
					int possibilities = 9;
					int last = 0;

					for (int l = 0; l < 9; ++l) {
						if (_grid[i][l] == 0) {

							bool possible = true;
							int ci = (i / 3) * 3;
							int cj = (l / 3) * 3;

							for (int k = 0; k < 9; ++k) {

								// recherche dans la colonne
								if (_grid[k][l] == n) {
									possibilities--;
									possible = false; break;
								}

								// recherche dans le carré
								int y = ci + k / 3;
								int x = cj + k % 3;
								if (_grid[y][x] == n) {
									possibilities--;
									possible = false; break;
								}
							}

							if (possible) last = l;

						} else {
							possibilities--;
						}
					}

					// une seule possibilité pour n ! (last)
					if (possibilities == 1)	{
						SetTile(i, last, n);
						_change = true;
					}
				}
			}
		}
	}

	void CheckBalayageColumns() {

		for (int i = 0; i < 9; ++i) {

			for (int n = 1; n <= 9; ++n) {
				int j;
				for (j = 0; j < 9; ++j) {
					if (_grid[j][i] == n) break;
				}
				if (j == 9) {
					// n n'est pas dans la ligne
					int possibilities = 9;
					int last = 0;

					for (int l = 0; l < 9; ++l) {
						if (_grid[l][i] == 0) {

							bool possible = true;
							int ci = l / 3;
							int cj = i / 3;

							for (int k = 0; k < 9; ++k) {

								if (_grid[l][k] == n) {
									possibilities--;
									possible = false;
									break;
								}

								int y = ci * 3 + k / 3;
								int x = cj * 3 + k % 3;
								if (_grid[y][x] == n) {
									possibilities--;
									possible = false; break;
								}
							}
							if (possible) last = l;

						} else {
							possibilities--;
						}
					}

					if (possibilities == 1)	{
						SetTile(last, i, n);
						_change = true;
						//~ return;
					}
				}
			}
		}
	}

	void CheckBalayageSquares() {

		for (int s = 0; s < 9; ++s) {
			for (int t = 0; t < 9; ++t) {

				if (*_squares[s][t] == 0) {

					for (int n = 1; n <= 9; ++n) {
						int j;
						for (j = 0; j < 9; ++j) {
							if (*_squares[s][j] == n) break;
						}

						if (j == 9) {
							// n n'est pas dans le carré
							int possibilities = 9;
							int lastI = 0;
							int lastJ = 0;

							int ci = (s / 3) * 3;
							int cj = (s % 3) * 3;

							for (int l = 0; l < 9; ++l) {

								if (*_squares[s][l] == 0) {

									bool possible = true;

									int ti = ci + l / 3;
									int tj = cj + l % 3;

									for (int k = 0; k < 9; ++k) {

										// recherche dans la colonne
										if (_grid[k][tj] == n) {
											possibilities--;
											possible = false; break;
										}

										// recherche dans la ligne
										if (_grid[ti][k] == n) {
											possibilities--;
											possible = false; break;
										}
									}

									if (possible) {
										lastI = ti;
										lastJ = tj;
									}
								} else {
									possibilities--;
								}
							}

							// une seule possibilité pour n ! (last)
							if (possibilities == 1)	{
								SetTile(lastI, lastJ, n);
								_change = true;
							}
						}
					}
				}
			}
		}
	}


	int GetPossibilities(int i, int j) {

		for (int p = 0; p < 9; ++p) _pos[p] = true;

		int ci = i / 3;
		int cj = j / 3;
		int pos = 9;

		for (int l = 0; l < 9; ++l) {
			if (_grid[i][l] != 0) {
				if (_pos[_grid[i][l] - 1]) {
					--pos;
					_pos[_grid[i][l] - 1] = false;
				}
			}
			if (_grid[l][j] != 0) {
				if (_pos[_grid[l][j] - 1]) {
					--pos;
					_pos[_grid[l][j] - 1] = false;
				}
			}
			int y = ci * 3 + l / 3;
			int x = cj * 3 + l % 3;
			if (_grid[y][x] != 0) {
				if (_pos[_grid[y][x] - 1]) {
					--pos;
					_pos[_grid[y][x] - 1] = false;
				}
			}
		}
		return pos;
	}

	bool IsSolved() {

		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				if (_grid[i][j] == 0)
					return false;
		return true;
	}

	void Draw() {

		std::cout << "\033[2J\033[1;1H"; // clear

		std::cout << "╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╠───┼───┼───╬───┼───┼───╬───┼───┼───╣" << std::endl;
		std::cout << "║   │   │   │   │   │   │   │   │   ║" << std::endl;
		std::cout << "╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝" << std::endl;

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (_grid[i][j] != 0)
					DrawNumber(i,j, _grid[i][j], RESET_COLOR);
			}
		}
	}

	void ClearNumber(int i, int j) {
		std::cout << "\033[" << 2 + i * 2 << ";" << 3 + j * 4 << "H" << " " << std::endl;
		std::cout << "\033[19;1H" << std::endl;
	}

	void DrawNumber(int i, int j, int num, const char* color) {
		std::cout << "\033[" << 2 + i * 2 << ";" << 3 + j * 4 << "H" << color << num << RESET_COLOR << std::endl;
		std::cout << "\033[19;1H" << std::endl;
	}
};

class Sudoku {
	public:

	Grid* _grid;

	Sudoku(Grid* grid) {
		_grid = grid;
	}

	~Sudoku() {
		delete _grid;
	}

	void Draw() {
		_grid->Draw();
	}

	Sudoku* Solve() {

		// Essai classique
		_grid->SolveNormal();

		// Essai avec hypothèses
		if (not _grid->IsSolved()) {
			_grid->SolveHypo();
		}

		return this;
	}
};

int main(int argn, char** argv) {

	srand(unsigned(time(NULL)));

	// arguments
	if (argn > 1) {
		std::string arg(argv[1]);

		if (arg.compare("-fast") == 0) {

			_FAST = true;

		} else if (arg.compare("-delay") == 0) {

			if (argn > 2) {
				std::stringstream ss(argv[2]);
				int i;
				ss >> i;
				if (not ss.fail()) {
					if (i > 0) {
						_DELAY = i;
					}
				}
			}
		} else if (arg.compare("-average") == 0) {
			if (argn > 2) {
				std::stringstream ss(argv[2]);
				int i;
				ss >> i;
				if (not ss.fail()) {
					if (i > 0) {
						_FAST = true;
						_AVERAGE = i;
					}
				}
			}
		} else if (arg.compare("-best") == 0) {
			if (argn > 2) {
				std::stringstream ss(argv[2]);
				int i;
				ss >> i;
				if (not ss.fail()) {
					if (i > 0) {
						_FAST = true;
						_BEST = i;
					}
				}
			}
		}
	}

	Sudoku* sudoku;
	timespec start, end;
	float time;

	if (_AVERAGE > 1) {

		float totalTime = 0;

		for (int i = 0; i < _AVERAGE; ++i) {
			sudoku = new Sudoku(new Grid(GRID));

			clock_gettime(CLOCK_REALTIME, &start);
			sudoku->Solve();
			clock_gettime(CLOCK_REALTIME, &end);
			totalTime += (float)((end.tv_sec * 1000000000 + end.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec)) / 1000000000;

			delete sudoku;
		}
		time = totalTime / _AVERAGE;

	} else if (_BEST > 1) {

		float bestTime = -1;

		for (int i = 0; i < _BEST; ++i) {

			sudoku = new Sudoku(new Grid(GRID));

			clock_gettime(CLOCK_REALTIME, &start);
			sudoku->Solve();
			clock_gettime(CLOCK_REALTIME, &end);

			delete sudoku;

			float currentTime = (float)((end.tv_sec * 1000000000 + end.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec)) / 1000000000;
			if (bestTime == -1 || currentTime < bestTime) {
				bestTime = currentTime;
			}
		}
		time = bestTime;

	} else {

		sudoku = new Sudoku(new Grid(GRID));

		clock_gettime(CLOCK_REALTIME, &start);
		sudoku->Solve(); // Solve !
		clock_gettime(CLOCK_REALTIME, &end);

		if (_FAST) sudoku->Draw();
		delete sudoku;

		time = (float)((end.tv_sec * 1000000000 + end.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec)) / 1000000000;
	}

	if (_FAST) std::cout << "Temps : " << time * 1000 << " ms" << std::endl;

	return 0;
}
