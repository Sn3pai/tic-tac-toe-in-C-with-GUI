#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

const int SIZE = 3;
const int CELL_SIZE = 200;
const int WINDOW_SIZE = SIZE * CELL_SIZE;

std::array<std::array<char, SIZE>, SIZE> board;
bool xTurn = true;
bool gameOver = false;
char winner = ' ';

void resetBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
    xTurn = true;
    gameOver = false;
    winner = ' ';
}

void checkWinner() {
    // rows & cols
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            winner = board[i][0];
            gameOver = true;
            return;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            winner = board[0][i];
            gameOver = true;
            return;
        }
    }
    // diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
        gameOver = true;
        return;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
        gameOver = true;
        return;
    }
    // draw
    bool full = true;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                full = false;
    if (full) {
        winner = 'D'; // Draw
        gameOver = true;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + 100), "Tic Tac Toe");

    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(32);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10, WINDOW_SIZE + 20);

    resetBoard();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver && event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / CELL_SIZE;
                int col = event.mouseButton.x / CELL_SIZE;

                if (row < SIZE && col < SIZE && board[row][col] == ' ') {
                    board[row][col] = xTurn ? 'X' : 'O';
                    xTurn = !xTurn;
                    checkWinner();
                }
            }

            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                resetBoard();
            }
        }

        window.clear(sf::Color::Black);

        // Draw grid
        for (int i = 1; i < SIZE; i++) {
            sf::RectangleShape line(sf::Vector2f(WINDOW_SIZE, 5));
            line.setPosition(0, i * CELL_SIZE);
            window.draw(line);

            sf::RectangleShape vline(sf::Vector2f(5, WINDOW_SIZE));
            vline.setPosition(i * CELL_SIZE, 0);
            window.draw(vline);
        }

        // Draw X and O
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != ' ') {
                    sf::Text symbol;
                    symbol.setFont(font);
                    symbol.setString(board[i][j]);
                    symbol.setCharacterSize(150);
                    symbol.setFillColor(sf::Color::Green);
                    symbol.setPosition(j * CELL_SIZE + 30, i * CELL_SIZE - 20);
                    window.draw(symbol);
                }
            }
        }

        // Status text
        if (!gameOver) {
            statusText.setString(xTurn ? "Player X's Turn" : "Player O's Turn");
        } else {
            if (winner == 'D')
                statusText.setString("Draw! Press R to Restart");
            else
                statusText.setString(std::string("Winner: ") + winner + " (Press R to Restart)");
        }
        window.draw(statusText);

        window.display();
    }

    return 0;
}
