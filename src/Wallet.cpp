#include "Text.h"
#include "GameData.h"
#include "Wallet.h"
#include <iostream>


Wallet::Wallet(GameObject &associated, int initialMoney) : Component(associated) {
    this->money = initialMoney;

    textWallet = new Text(associated, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)) ,{255, 255, 255, SDL_ALPHA_OPAQUE}) ;
    associated.AddComponent(textWallet);
}

Wallet::~Wallet() {

}
void Wallet::Update(float dt) {
    if(this->money != GameData::currentMoney) {
        this->money = GameData::currentMoney;

        textWallet->SetText(("R$ " + std::to_string(this->money)));
    }
}

void Wallet::Restart(){
    this->money = GameData::currentMoney = 0;
}

int Wallet::GetMoney() {
    return this->money;
}

void Wallet::SetMoney(int moneyetted) {
    this->money = moneyetted;
    GameData::currentDay = moneyetted;
}

void Wallet::Render()
{
}

bool Wallet::Is(std::string type)
{
    return (type == Wallet::type);
}