#pragma once

#include <array>

#include "raylib.h"

namespace titan {

class Board {
public:
    void Reset();
    bool PlaceMark(Vector2 mousePosition, char player);
    bool HasWinner(char player) const;
    bool IsFull() const;
    void Draw(Vector2 center, float size, float time) const;

private:
    int CellAt(Vector2 mousePosition, Vector2 center, float size) const;
    void DrawMark(Vector2 center, float cellSize, char mark) const;

    std::array<char, 9> cells_{};
};

} // namespace titan