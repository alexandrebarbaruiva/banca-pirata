/**
 * @file LetterState.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief LetterState class header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "LetterState.h"
#include "CameraFollower.h"

LetterState::LetterState() : State(), backgroundMusic("assets/audio/abertura.ogg")
{
    // Background
    GameObject *bg = new GameObject();
    Sprite *spriteBackground = new Sprite(*bg, "assets/img/placeholders/Grade_Anim_Start.png", 1, 1.0f);
    bg->AddComponent(spriteBackground);
	bg->AddComponent(new CameraFollower(*bg));
    bg->box.x = 0;
    bg->box.y = 0;
    this->AddObject(bg);

	GameObject *cartaGO = new GameObject();
	//cartaGO->AddComponent(new Sprite(*cartaGO, "assets/img/placeholders/Carta.png", 1, 1.0));
	cartaGO->AddComponent(new Sprite(*cartaGO , "assets/img/placeholders/CartaAnim-Sheet_3.png", 13, 0.2, 2.8));
	cartaGO->box.SetOrigin(300, 0);
	AddObject(cartaGO);
}

LetterState::~LetterState()
{
    objectArray.clear();
}

void LetterState::LoadAssets()
{
}

void LetterState::Pause()
{
    backgroundMusic.Stop(0);
}

void LetterState::Resume()
{
    backgroundMusic.Play();
    Camera::Reset();
}

void LetterState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    backgroundMusic.Play();
    started = true;
}

void LetterState::Update(float dt)
{
	InputManager input = InputManager::GetInstance();
    //std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> sprites = this->QueryObjectsByComponent("Sprite");
    if(sprites.size() <= 1)
    {
        std::cout << "Acabou sprite" << std::endl;
	    GameObject *cartaGO = new GameObject();
	    cartaGO->AddComponent(new Sprite(*cartaGO, "assets/img/placeholders/Carta.png", 1, 1.0));
	    //cartaGO->AddComponent(new Sprite(*cartaGO , "assets/img/placeholders/CartaAnim-Sheet_3.png", 13, 0.2, 2.8));
	    cartaGO->box.SetOrigin(70, 0);
	    AddObject(cartaGO);

        std::string textocarta = "Sua mãe me disse que voce estava atras de um bico pra ganhar uma graninha \n\n extra, e olha so que sorte a sua, acabou de abrir uma vaga com o seu nome \n\n\n na banquinha do seu tio! E não tem momento melhor pra isso, por que o tio\n\n ta precisando tirar umas \u0022ferias especiais\u0022 por causa de um\n\n\n desentendimento com um amigo, voce entende, ne? Enfim, o combinado e\n\n o seguinte: voce precisa juntar R$500,00 ate o fim do mes pra esse meu\n\n amigo, fora isso, pode ficar com o resto! Dificil de recusar, nao? E a parte\n\n de administrar a banca e moleza, e so lembrar daquelas vezes que voce\n\n veio me ajudar quando era mais novo e das dicas que eu te dei.\n\n Voce consegue garoto, confio em voce.";

        GameObject *textoCartaGO1 = new GameObject();
        textoCartaGO1->AddComponent(new Text(*textoCartaGO1, "assets/font/Karma Suture.otf", 40, Text::BLENDED, "Fala, garoto!", {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO1->box.SetOrigin(610,135);
        AddObject(textoCartaGO1);
        GameObject *textoCartaGO2 = new GameObject();
        textoCartaGO2->AddComponent(new Text(*textoCartaGO2, "assets/font/Karma Suture.otf", 20, Text::BLENDED, textocarta, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO2->box.SetOrigin(610,210);
        AddObject(textoCartaGO2);
        std::string textocarta3 = "Um Abraco"; 
        GameObject *textoCartaGO3 = new GameObject();
        textoCartaGO3->AddComponent(new Text(*textoCartaGO3, "assets/font/Karma Suture.otf", 30, Text::BLENDED, textocarta3, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO3->box.SetOrigin(610,800);
        AddObject(textoCartaGO3);
        std::string textocarta4 = "Seu Tio"; 
        GameObject *textoCartaGO4 = new GameObject();
        textoCartaGO4->AddComponent(new Text(*textoCartaGO4, "assets/font/Karma Suture.otf", 30, Text::BLENDED, textocarta4, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO4->box.SetOrigin(610,865);
        AddObject(textoCartaGO4);
        std::string textocartaFinal = "PS: e muito importante que voce consiga esse dinheiro, ouviu?\n\n\n Se nao conseguir, feche a banca e nao volte mais.";
        GameObject *textoCartaGO5 = new GameObject();
        textoCartaGO5->AddComponent(new Text(*textoCartaGO5, "assets/font/Karma Suture.otf", 20, Text::BLENDED, textocartaFinal, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO5->box.SetOrigin(610,935);
        AddObject(textoCartaGO5);

    }
    //for (unsigned i = 0; i < sprites.size(); i++)
    //{
    //    Sprite *sprite = ((Sprite *)(sprites[i].lock()->GetComponent("Sprite")));
    //    if ()
    //    {
    //        std::cout << "Acabou sprite" << std::endl;
    //    }
    //}

    if (input.QuitRequested())
    {
        quitRequested = true;
    }

    if(input.KeyPress(ESCAPE_KEY))
    {
        this->Pause();
        popRequested = true;
    }

    //if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "startButton")
    //{

    //    State *stage = new StageState();
    //    Game::GetInstance().Push(stage);
    //}

    //if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "continueButton")
    if (input.KeyPress(SPACE_KEY) or input.MousePress(LEFT_MOUSE_BUTTON))
    {
        State *stage = new StageState(true);
        Game::GetInstance().Push(stage);
    }

    UpdateArray(dt);
}

void LetterState::Render()
{
    RenderArray();
}
