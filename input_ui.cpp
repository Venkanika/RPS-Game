#include "rock_paper_scissors.h"
#include <raylib.h>
#include <cmath>
#include <string>
using namespace std;
namespace {

const Color paper = {248, 243, 229, 255};
const Color ink = {47, 57, 48, 255};
const Color mutedInk = {115, 116, 99, 255};
const Color orange = {221, 121, 82, 255};
const Color green = {114, 142, 108, 255};
const Color blue = {111, 139, 158, 255};
const Color cardColor = {255, 252, 241, 255};
const Color paleGreen = {230, 235, 218, 255};

struct Button {
    Rectangle bounds;
    Move move;
    const char* label;
    Color accent;
};

Button moveButtons[3];
Font interfaceFont;
bool ownsInterfaceFont = false;

void setMoveButtons(int width) {
    const float buttonWidth = 150;
    const float buttonHeight = 62;
    const float gap = 22;
    const float totalWidth = buttonWidth * 3 + gap * 2;
    const float startX = (width - totalWidth) / 2.0f;
    const float y = 172;
    moveButtons[0] = {{startX, y, buttonWidth, buttonHeight}, Move::Rock, "ROCK", orange};
    moveButtons[1] = {{startX + buttonWidth + gap, y, buttonWidth, buttonHeight}, Move::Paper, "PAPER", green};
    moveButtons[2] = {{startX + (buttonWidth + gap) * 2, y, buttonWidth, buttonHeight}, Move::Scissors, "SCISSORS", blue};
}

float handwrittenWidth(Font font, const string& text, float fontSize, float spacing) {
    float width = 0;
    for (size_t index = 0; index < text.size(); ++index) {
        const char glyph[] = {text[index], '\0'};
        width += MeasureTextEx(font, glyph, fontSize, spacing).x;
        if (index + 1 < text.size()) {
            width += spacing;
        }
    }
    return width;
}

void drawHandwritten(Font font, const string& text, Vector2 position, float fontSize,
                     float spacing, Color color, bool centered = false) {
    float x = position.x;
    if (centered) {
        x -= handwrittenWidth(font, text, fontSize, spacing) / 2.0f;
    }

    for (size_t index = 0; index < text.size(); ++index) {
        const char glyph[] = {text[index], '\0'};
        const float wobble = sin(static_cast<float>(index) * 1.7f) * 1.4f;
        const float tilt = sin(static_cast<float>(index) * 2.3f) * 1.8f;
        DrawTextPro(font, glyph, {x, position.y + wobble}, {0, 0}, tilt,
                    fontSize, spacing, color);
        x += MeasureTextEx(font, glyph, fontSize, spacing).x;
        if (index + 1 < text.size()) {
            x += spacing;
        }
    }
}

void drawRoughRectangle(Rectangle bounds, Color color, float thickness = 2.0f) {
    DrawRectangleLinesEx(bounds, thickness, color);
    DrawRectangleLinesEx({bounds.x + 2.2f, bounds.y - 1.3f,
                          bounds.width - 1.5f, bounds.height + 2.0f},
                         1.0f, Fade(color, 0.48f));
}

void drawPaperBackground(int width, int height) {
    ClearBackground(paper);
    for (int x = 25; x < width; x += 53) {
        for (int y = 19; y < height; y += 47) {
            const int variation = (x * 7 + y * 11) % 4;
            DrawCircle(x + variation, y, 0.7f, Fade(ink, 0.10f));
        }
    }
    DrawLineEx({34, 30}, {width - 34.0f, 30}, 1.0f, Fade(orange, 0.45f));
    DrawLineEx({34, height - 31.0f}, {width - 34.0f, height - 31.0f},
               1.0f, Fade(orange, 0.45f));
}

void drawMoveIcon(Move move, float centerX, float centerY, Color color) {
    if (move == Move::Rock) {
        DrawCircleLines(static_cast<int>(centerX), static_cast<int>(centerY), 38, color);
        DrawCircleLines(static_cast<int>(centerX + 1), static_cast<int>(centerY - 1), 36, Fade(color, 0.55f));
        DrawLineEx({centerX - 18, centerY + 2}, {centerX - 5, centerY - 15}, 2.0f, color);
        DrawLineEx({centerX - 5, centerY - 15}, {centerX + 8, centerY - 10}, 2.0f, color);
        DrawLineEx({centerX + 8, centerY - 10}, {centerX + 20, centerY + 7}, 2.0f, color);
    } else if (move == Move::Paper) {
        const Rectangle sheet = {centerX - 27, centerY - 37, 54, 74};
        drawRoughRectangle(sheet, color, 2.0f);
        DrawLineEx({centerX - 15, centerY - 12}, {centerX + 13, centerY - 12}, 2.0f, color);
        DrawLineEx({centerX - 15, centerY + 2}, {centerX + 13, centerY + 2}, 2.0f, color);
        DrawLineEx({centerX - 15, centerY + 16}, {centerX + 6, centerY + 16}, 2.0f, color);
    } else {
        DrawLineEx({centerX - 25, centerY - 27}, {centerX + 27, centerY + 28}, 4.0f, color);
        DrawLineEx({centerX + 25, centerY - 27}, {centerX - 27, centerY + 28}, 4.0f, color);
        DrawCircleLines(static_cast<int>(centerX - 25), static_cast<int>(centerY - 27), 8, color);
        DrawCircleLines(static_cast<int>(centerX + 25), static_cast<int>(centerY - 27), 8, color);
        DrawCircleLines(static_cast<int>(centerX - 27), static_cast<int>(centerY + 28), 8, color);
        DrawCircleLines(static_cast<int>(centerX + 27), static_cast<int>(centerY + 28), 8, color);
    }
}

void drawChoicePanel(Font font, Rectangle bounds, const char* title, Move move,
                     bool hasChoice, Color accent, bool isPlayer) {
    DrawRectangleRounded(bounds, 0.08f, 8, cardColor);
    drawRoughRectangle(bounds, Fade(ink, 0.65f), 1.6f);
    drawHandwritten(font, title, {bounds.x + 20, bounds.y + 16}, 22, 1.0f, accent);
    DrawLineEx({bounds.x + 19, bounds.y + 49},
               {bounds.x + bounds.width - 20, bounds.y + 49}, 1.5f, Fade(accent, 0.55f));

    if (hasChoice) {
        const float centerX = bounds.x + bounds.width / 2.0f;
        const float iconY = bounds.y + 113;
        drawMoveIcon(move, centerX, iconY, accent);
        drawHandwritten(font, moveName(move), {centerX, bounds.y + 166},
                        27, 1.2f, ink, true);
        if (isPlayer) {
            drawHandwritten(font, "nice pick!", {bounds.x + bounds.width - 97, bounds.y + 74},
                            15, 0.8f, orange);
        }
    } else {
        drawHandwritten(font, isPlayer ? "pick one above" : "waiting...",
                        {bounds.x + bounds.width / 2.0f, bounds.y + 120},
                        22, 1.0f, mutedInk, true);
        DrawCircleLines(static_cast<int>(bounds.x + bounds.width / 2.0f),
                        static_cast<int>(bounds.y + 171), 17, Fade(mutedInk, 0.45f));
        DrawLineEx({bounds.x + bounds.width / 2.0f - 8, bounds.y + 171},
                   {bounds.x + bounds.width / 2.0f + 8, bounds.y + 171},
                   1.5f, Fade(mutedInk, 0.55f));
    }
}

bool wasPressed(const Button& button) {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           CheckCollisionPointRec(GetMousePosition(), button.bounds);
}

void playRound(GameState& state, Move playerMove) {
    state.playerMove = playerMove;
    state.computerMove = getComputerChoice();
    state.result = determineWinner(playerMove, state.computerMove);
    state.hasPlayed = true;
    state.resultRevealTime = 0.0f;
    ++state.rounds;

    if (state.result == RoundResult::Win) {
        ++state.wins;
    } else if (state.result == RoundResult::Loss) {
        ++state.losses;
    } else {
        ++state.draws;
    }
}

string resultMessage(const GameState& state) {
    switch (state.result) {
        case RoundResult::Win:
            return "you win this round!";
        case RoundResult::Loss:
            return "the computer got this one";
        case RoundResult::Draw:
            return "a tie! great minds think alike";
    }
    return "";
}

void drawScore(Font font, const GameState& state, int width) {
    const Rectangle scoreCard = {width - 301.0f, 51, 251, 91};
    DrawRectangleRounded(scoreCard, 0.18f, 8, paleGreen);
    drawRoughRectangle(scoreCard, Fade(green, 0.8f), 1.7f);
    drawHandwritten(font, "YOUR SCORE", {scoreCard.x + 18, scoreCard.y + 10},
                    16, 0.8f, mutedInk);

    const string score = "W  " + to_string(state.wins) + "    D  " +
                                 to_string(state.draws) + "    L  " +
                                 to_string(state.losses);
    drawHandwritten(font, score, {scoreCard.x + 18, scoreCard.y + 45},
                    17, 0.5f, ink);
    drawHandwritten(font, to_string(state.rounds) + " rounds",
                    {scoreCard.x + 18, scoreCard.y + 68}, 13, 0.5f, mutedInk);
}

} // namespace

void initializeGameUi() {
    const char* chalkFontPath = "/System/Library/Fonts/Supplemental/Chalkduster.ttf";
    if (FileExists(chalkFontPath)) {
        interfaceFont = LoadFontEx(chalkFontPath, 64, nullptr, 0);
        ownsInterfaceFont = interfaceFont.texture.id != 0;
    }
    if (!ownsInterfaceFont) {
        interfaceFont = GetFontDefault();
    }
}

void updateGameUi(GameState& state, float deltaTime) {
    state.resultRevealTime += deltaTime;
    const int width = GetScreenWidth();
    setMoveButtons(width);

    if (IsKeyPressed(KEY_R)) {
        state = {};
        return;
    }

    Move selectedMove = Move::None;
    if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
        selectedMove = Move::Rock;
    } else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
        selectedMove = Move::Paper;
    } else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) {
        selectedMove = Move::Scissors;
    } else {
        for (const Button& button : moveButtons) {
            if (wasPressed(button)) {
                selectedMove = button.move;
                break;
            }
        }
    }

    if (selectedMove != Move::None) {
        playRound(state, selectedMove);
    }
}

void drawGameUi(const GameState& state, float elapsedTime) {
    const int width = GetScreenWidth();
    const int height = GetScreenHeight();
    setMoveButtons(width);
    drawPaperBackground(width, height);

    const Font font = interfaceFont;
    const string title = "rock paper scissors";
    const size_t titleCharacters = static_cast<size_t>(
        fmin(title.size(), elapsedTime * 28.0f));
    drawHandwritten(font, title.substr(0, titleCharacters), {58, 52},
                    38, 1.5f, ink);
    drawHandwritten(font, "a tiny hand-drawn showdown", {62, 107},
                    17, 0.9f, mutedInk);
    drawScore(font, state, width);

    drawHandwritten(font, "make your move", {width / 2.0f, 147},
                    19, 0.9f, mutedInk, true);

    for (const Button& button : moveButtons) {
        const bool hovered = CheckCollisionPointRec(GetMousePosition(), button.bounds);
        const Color fill = hovered ? Fade(button.accent, 0.18f) : cardColor;
        DrawRectangleRounded(button.bounds, 0.22f, 8, fill);
        drawRoughRectangle(button.bounds, button.accent, hovered ? 2.7f : 1.8f);
        drawHandwritten(font, button.label,
                        {button.bounds.x + button.bounds.width / 2.0f,
                         button.bounds.y + 19},
                        21, 1.1f, ink, true);
        DrawCircle(static_cast<int>(button.bounds.x + button.bounds.width / 2.0f),
                   static_cast<int>(button.bounds.y + 49), 2.0f, button.accent);
    }

    const float panelY = 260;
    const float panelWidth = (width - 164.0f) / 2.0f;
    const Rectangle playerPanel = {56, panelY, panelWidth, 207};
    const Rectangle computerPanel = {width - panelWidth - 56, panelY, panelWidth, 207};
    drawChoicePanel(font, playerPanel, "YOU", state.playerMove, state.hasPlayed,
                    orange, true);
    drawChoicePanel(font, computerPanel, "THE COMPUTER", state.computerMove,
                    state.hasPlayed, blue, false);

    drawHandwritten(font, "vs", {width / 2.0f, panelY + 98},
                    22, 1.0f, mutedInk, true);

    const Rectangle resultCard = {56, 493, width - 112.0f, 112};
    DrawRectangleRounded(resultCard, 0.12f, 8, cardColor);
    drawRoughRectangle(resultCard, Fade(orange, 0.68f), 1.8f);
    if (state.hasPlayed) {
        const string message = resultMessage(state);
        const size_t visibleCharacters = static_cast<size_t>(
            fmin(message.size(), state.resultRevealTime * 25.0f));
        const Color resultColor = state.result == RoundResult::Win ? green :
                                  state.result == RoundResult::Loss ? orange : blue;
        const float messageWidth = handwrittenWidth(font, message, 24, 1.0f);
        drawHandwritten(font, message.substr(0, visibleCharacters),
                        {width / 2.0f - messageWidth / 2.0f, resultCard.y + 24},
                        24, 1.0f, resultColor);
        drawHandwritten(font, "choose again for another round",
                        {width / 2.0f, resultCard.y + 65},
                        16, 0.7f, mutedInk, true);
    } else {
        drawHandwritten(font, "ready when you are...", {width / 2.0f, resultCard.y + 41},
                        22, 1.0f, mutedInk, true);
    }

    drawHandwritten(font, "click a card  /  keys 1, 2, 3 to play  /  R to reset",
                    {width / 2.0f, height - 61.0f}, 14, 0.45f, mutedInk, true);
}

void shutdownGameUi() {
    if (ownsInterfaceFont) {
        UnloadFont(interfaceFont);
        ownsInterfaceFont = false;
    }
}
