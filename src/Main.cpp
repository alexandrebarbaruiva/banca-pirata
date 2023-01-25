/**
 * @file Main.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Main file to run game
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Game.h"
#include "TitleState.h"

int main(int argc, char **argv)
{
    Game game = Game::GetInstance();
    State *initialState = new TitleState("TitleState");
    game.Push(initialState);
    game.Run();
    return 0;
}