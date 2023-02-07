/**
 * @file Wallet.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief Wallet class header file
 * @version 0.1
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef WALLET_HEADER
#define WALLET_HEADER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "Text.h"
#include <string>

class Wallet : public Component
{
private:
    int money;
    Text *textWallet;

public:
    Wallet(GameObject &associated, int initialMoney = 1);
    ~Wallet();

    std::string type = "Wallet";

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Restart();
    int GetMoney();
    void SetMoney(int moneySetted);
};

#endif