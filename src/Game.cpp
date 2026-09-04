#include "Game.h"

#include <cmath>

#include "raylib.h"

namespace titan {
namespace {

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 800;
constexpr Color kBackground = {7, 11, 24, 255};
constexpr Color kText = {225, 237, 255, 255};
constexpr Color kMutedText = {117, 143, 177, 255};
constexpr Color kCyan = {55, 221, 255, 255};
constexpr Color kPink = {255, 77, 174, 255};

} // namespace

Game::Game()
{
	board_.Reset();
	InitWindow(kWindowWidth, kWindowHeight, "TITAN TACTICS | Ultimate Tic-Tac-Toe");
	SetWindowMinSize(720, 560);
	SetTargetFPS(60);
}

Game::~Game()
{
	CloseWindow();
}

void Game::Run()
{
	while (!WindowShouldClose()) {
		const float deltaTime = GetFrameTime();
		Update(deltaTime);
		BeginDrawing();
		Draw();
		EndDrawing();
	}
}

void Game::Update(float deltaTime)
{
	(void)deltaTime;

	if (IsKeyPressed(KEY_R)) {
		board_.Reset();
		currentPlayer_ = 'X';
		winner_ = ' ';
		gameOver_ = false;
		++round_;
	}

	if (!gameOver_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		const Vector2 mouse = GetMousePosition();
		if (board_.PlaceMark(mouse, currentPlayer_)) {
			if (board_.HasWinner(currentPlayer_)) {
				winner_ = currentPlayer_;
				gameOver_ = true;
			} else if (board_.IsFull()) {
				gameOver_ = true;
			} else {
				currentPlayer_ = currentPlayer_ == 'X' ? 'O' : 'X';
			}
		}
	}
}

void Game::Draw() const
{
	const float time = static_cast<float>(GetTime());
	ClearBackground(kBackground);
	DrawBackground(time);

	const float boardWidth = static_cast<float>(GetScreenHeight()) * 0.66f;
	const Vector2 boardCenter = {
		static_cast<float>(GetScreenWidth()) * 0.5f,
		static_cast<float>(GetScreenHeight()) * 0.54f};
	board_.Draw(boardCenter, boardWidth, time);
	DrawHud();
}

void Game::DrawBackground(float time) const
{
	const int width = GetScreenWidth();
	const int height = GetScreenHeight();

	for (int ring = 0; ring < 5; ++ring) {
		const float radius = 180.0f + ring * 95.0f + std::sin(time * 0.35f + ring) * 8.0f;
		const unsigned char alpha = static_cast<unsigned char>(16 - ring * 2);
		DrawCircleLines(width / 2, height / 2 + 25, radius, {45, 109, 180, alpha});
	}

	for (int x = 0; x < width; x += 48) {
		const float offset = std::fmod(time * 8.0f, 48.0f);
		DrawLine(x, 0, x, height, {29, 64, 105, 24});
		DrawLine(x + offset, 0, x + offset, height, {40, 101, 157, 18});
	}
	for (int y = 0; y < height; y += 48) {
		DrawLine(0, y, width, y, {29, 64, 105, 24});
	}

	for (int i = 0; i < 45; ++i) {
		const float x = std::fmod(i * 277.0f + time * (4.0f + i % 3), static_cast<float>(width));
		const float y = std::fmod(i * 131.0f, static_cast<float>(height));
		const unsigned char alpha = static_cast<unsigned char>(35 + (i % 4) * 12);
		DrawCircle(static_cast<int>(x), static_cast<int>(y), 1.5f, {118, 205, 255, alpha});
	}

	DrawRectangleGradientV(0, 0, width, height / 3, {6, 13, 31, 115}, {6, 13, 31, 0});
}

void Game::DrawHud() const
{
	DrawText("TITAN TACTICS", 48, 34, 32, kText);
	DrawText("ULTIMATE TIC-TAC-TOE", 51, 72, 14, kCyan);
	DrawText("PHASE 01  //  ARENA ONLINE", 48, GetScreenHeight() - 38, 14, kMutedText);

	const char* turnText = currentPlayer_ == 'X' ? "PLAYER X" : "PLAYER O";
	const Color turnColor = currentPlayer_ == 'X' ? kCyan : kPink;
	DrawText(turnText, GetScreenWidth() - 210, 46, 20, turnColor);
	DrawText("YOUR TURN", GetScreenWidth() - 210, 74, 13, kMutedText);

	DrawText(TextFormat("ROUND %02d", round_), GetScreenWidth() - 150, GetScreenHeight() - 38, 14, kMutedText);
	DrawText("R  RESET", GetScreenWidth() / 2 - 42, GetScreenHeight() - 38, 14, kMutedText);

	if (winner_ != ' ') {
		const Color winnerColor = winner_ == 'X' ? kCyan : kPink;
		DrawText(TextFormat("PLAYER %c WINS", winner_), GetScreenWidth() / 2 - 105,
		         118, 26, winnerColor);
	} else if (gameOver_) {
		DrawText("STALEMATE", GetScreenWidth() / 2 - 77, 118, 26, kMutedText);
	}
}

} // namespace titan
