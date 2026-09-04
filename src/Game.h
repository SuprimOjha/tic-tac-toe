#pragma once

#include "Board.h"

namespace titan {

class Game {
public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Run();

private:
	void Update(float deltaTime);
	void Draw() const;
	void DrawBackground(float time) const;
	void DrawHud() const;

	Board board_;
	char currentPlayer_ = 'X';
	char winner_ = ' ';
	bool gameOver_ = false;
	int round_ = 1;
};

} // namespace titan
