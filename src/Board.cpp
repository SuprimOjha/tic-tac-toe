#include "Board.h"

#include <cmath>

namespace titan {
namespace {

constexpr Color kBoardLine = {57, 186, 235, 185};
constexpr Color kCellFill = {17, 31, 61, 210};
constexpr Color kHoverFill = {31, 73, 108, 220};
constexpr Color kCyan = {55, 221, 255, 255};
constexpr Color kPink = {255, 77, 174, 255};

} // namespace

void Board::Reset()
{
    cells_.fill(' ');
}

bool Board::PlaceMark(Vector2 mousePosition, char player)
{
    const int cell = CellAt(mousePosition, {static_cast<float>(GetScreenWidth()) * 0.5f,
                                            static_cast<float>(GetScreenHeight()) * 0.54f},
                            static_cast<float>(GetScreenHeight()) * 0.66f);
    if (cell < 0 || cells_[cell] != ' ') {
        return false;
    }
    cells_[cell] = player;
    return true;
}

bool Board::HasWinner(char player) const
{
    constexpr int winningLines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& line : winningLines) {
        if (cells_[line[0]] == player && cells_[line[1]] == player && cells_[line[2]] == player) {
            return true;
        }
    }
    return false;
}

bool Board::IsFull() const
{
    for (const char cell : cells_) {
        if (cell == ' ') {
            return false;
        }
    }
    return true;
}

int Board::CellAt(Vector2 mousePosition, Vector2 center, float size) const
{
    const float left = center.x - size / 2.0f;
    const float top = center.y - size / 2.0f;
    const float cellSize = size / 3.0f;
    if (mousePosition.x < left || mousePosition.x >= left + size ||
        mousePosition.y < top || mousePosition.y >= top + size) {
        return -1;
    }
    const int column = static_cast<int>((mousePosition.x - left) / cellSize);
    const int row = static_cast<int>((mousePosition.y - top) / cellSize);
    return row * 3 + column;
}

void Board::Draw(Vector2 center, float size, float time) const
{
    const float left = center.x - size / 2.0f;
    const float top = center.y - size / 2.0f;
    const float cellSize = size / 3.0f;
    const int hoveredCell = CellAt(GetMousePosition(), center, size);

    DrawRectangle(static_cast<int>(left - 16), static_cast<int>(top - 16),
                  static_cast<int>(size + 32), static_cast<int>(size + 32), {9, 22, 43, 235});
    DrawRectangleLinesEx({left - 16, top - 16, size + 32, size + 32}, 2.0f, {47, 150, 211, 120});

    for (int index = 0; index < 9; ++index) {
        const int row = index / 3;
        const int column = index % 3;
        const Rectangle cell = {left + column * cellSize + 5.0f, top + row * cellSize + 5.0f,
                                cellSize - 10.0f, cellSize - 10.0f};
        DrawRectangleRec(cell, index == hoveredCell ? kHoverFill : kCellFill);
        if (index == hoveredCell) {
            const unsigned char alpha = static_cast<unsigned char>(85 + 30 * std::sin(time * 4.0f));
            DrawRectangleLinesEx(cell, 2.0f, {86, 226, 255, alpha});
        }
        if (cells_[index] != ' ') {
            DrawMark({cell.x + cell.width / 2.0f, cell.y + cell.height / 2.0f}, cell.width,
                      cells_[index]);
        }
    }

    for (int divider = 1; divider < 3; ++divider) {
        const float position = left + divider * cellSize;
        DrawLineEx({position, top + 12.0f}, {position, top + size - 12.0f}, 3.0f, kBoardLine);
        const float horizontal = top + divider * cellSize;
        DrawLineEx({left + 12.0f, horizontal}, {left + size - 12.0f, horizontal}, 3.0f, kBoardLine);
    }
}

void Board::DrawMark(Vector2 center, float cellSize, char mark) const
{
    const Color color = mark == 'X' ? kCyan : kPink;
    const float offset = cellSize * 0.27f;
    for (int glow = 6; glow >= 1; --glow) {
        const Color glowColor = {color.r, color.g, color.b, static_cast<unsigned char>(10 + glow * 4)};
        if (mark == 'X') {
            DrawLineEx({center.x - offset, center.y - offset}, {center.x + offset, center.y + offset},
                       2.0f + glow, glowColor);
            DrawLineEx({center.x + offset, center.y - offset}, {center.x - offset, center.y + offset},
                       2.0f + glow, glowColor);
        } else {
            DrawCircleLinesV(center, offset, glowColor);
            DrawCircleLinesV(center, offset + glow, glowColor);
        }
    }
    if (mark == 'X') {
        DrawLineEx({center.x - offset, center.y - offset}, {center.x + offset, center.y + offset}, 4.0f, color);
        DrawLineEx({center.x + offset, center.y - offset}, {center.x - offset, center.y + offset}, 4.0f, color);
    } else {
        DrawCircleLinesV(center, offset, color);
        DrawCircleLinesV(center, offset - 4.0f, {color.r, color.g, color.b, 120});
    }
}

} // namespace titan