#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall {
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX = 0, int posY = 0) {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset() {
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir d) {
		direction = d;
	}

	void randomDirection() {
		direction = (eDir)((rand() % 6) + 1);
	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }

	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x -= 2;
			break;
		case RIGHT:
			x += 2;
			break;
		case UPRIGHT:
			x++;
			y++;
			break;
		case UPLEFT:
			x--;
			y++;
			break;
		case DOWNRIGHT:
			x++;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y--;
			break;
		default:
			break;
		}
	}

	friend ostream& operator << (ostream& o, cBall c) {
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]" << endl;
		return o;
	}
};

class cPaddle {
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle() {
		x = 0;
		y = 0;
	}

	cPaddle(int posX, int posY) : cPaddle() {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y -= 2; }
	inline void moveDown() { y += 2; }

	friend ostream& operator << (ostream& o, cPaddle p) {
		o << "Paddle [" << p.x << "," << p.y << "]" << endl;
		return o;
	}
};

class cGameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall * ball;
	cPaddle * player1;
	cPaddle * player2;
public:
	cGameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w;
		height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2-3);
		player2 = new cPaddle(w - 2, h / 2-3);
	}

	~cGameManager() {
		delete ball, player1, player2;
	}

	void scoreUp(cPaddle* player) {
		if (player == player1) {
			score1++;
		}
		else if (player == player1) {
			score2++;
		}

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw() {
		system("cls");
		cout << "Score (1): " << score1 << endl;
		cout << "Score (2): " << score2 << endl;
		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}
		cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1X = player1->getX();
				int player2X = player2->getX();
				int player1Y = player1->getY();
				int player2Y = player2->getY();

				if (j == 0) {
					cout << "\xB2";
				}

				if (ballX == j && ballY == i) {
					cout << "\xFE";
				}

				else if ((player1X == j && player1Y == i) || (player2X == j && player2Y == i)) {
					cout << "\xDB";
				}

				else if ((player1X == j && player1Y+1 == i) || (player2X == j && player2Y+1 == i)) {
					cout << "\xDB";
				}

				else if ((player1X == j && player1Y+2 == i) || (player2X == j && player2Y+2 == i)) {
					cout << "\xDB";
				}

				else if ((player1X == j && player1Y+3 == i) || (player2X == j && player2Y+3 == i)) {
					cout << "\xDB";
				}

				else {
					cout << " ";
				}

				if (j == width - 1) {
					cout << "\xB2";
				}
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}
		cout << endl;
	}

	void Input() {
		ball->Move();
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player2X = player2->getX();
		int player1Y = player1->getY();
		int player2Y = player2->getY();

		if (_kbhit()) {
			char current = _getch();
			if (current == up1) {
				if (player1Y > 0) {
					player1->moveUp();
				}
			}
			if (current == up2) {
				if (player2Y > 0) {
					player2->moveUp();
				}
			}
			if (current == down1) {
				if (player1Y + 4 < height) {
					player1->moveDown();
				}
			}
			if (current == down2) {
				if (player2Y + 4 < height) {
					player2->moveDown();
				}
			}
			if (ball->getDirection() == STOP) {
				ball->randomDirection();
			}
			if (current == 'q') {
				quit = true;
			}

		}
	}

	void Logic() {
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player2X = player2->getX();
		int player1Y = player1->getY();
		int player2Y = player2->getY();

		// Left Paddle
		for (int i = 0; i < 4; i++) {
			if (ballX == player1X + 1) {
				if (ballY == player1Y + i) {
					ball->changeDirection((eDir)((rand() % 3) + 4));
				}
			}
		}

		// Right Paddle
		for (int i = 0; i < 4; i++) {
			if (ballX == player2X - 1) {
				if (ballY == player2Y + i) {
					ball->changeDirection((eDir)((rand() % 3) + 1));
				}
			}
		}

		// Bottom Wall
		if (ballY == 0) {
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		}

		// Top Wall
		if (ballY == height - 1) {
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		}

		if (ballX == width - 1) {
			scoreUp(player1);
		}

		if (ballX == 0) {
			scoreUp(player2);
		}
	}

	void Run() {
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};

int main() {

	cGameManager c(41, 21);
	c.Run();

	return 0;
}