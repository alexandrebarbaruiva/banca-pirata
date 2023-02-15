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
#include "GameData.h"

LetterState::LetterState() : State(), backgroundMusic("assets/audio/abertura.ogg")
{
    // Background
    GameObject *bg = new GameObject();
    Sprite *spriteBackground = new Sprite(*bg, BASE_ASSET_PATH + "Grade_Anim_Start.png", 1, 1.0f);
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

    cartaFechada = false;
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
    if (cartaFechada)
    {
        std::cout << "Carta já fechou" << std::endl;
        this->Pause();
        popRequested = true;
    }
    InputManager input = InputManager::GetInstance();
    // std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> sprites = this->QueryObjectsByComponent("Sprite");
    if(sprites.size() <= 1)
    {

	    GameObject *cartaGO = new GameObject();
	    cartaGO->AddComponent(new Sprite(*cartaGO, BASE_ASSET_PATH + "Carta.png", 1, 1.0));
	    //cartaGO->AddComponent(new Sprite(*cartaGO , "assets/img/placeholders/CartaAnim-Sheet_3.png", 13, 0.2, 2.8));
	    cartaGO->box.SetOrigin(285, 0);
	    AddObject(cartaGO);

        std::string textocarta = "Sua mãe me disse que voce estava atras de um bico pra ganhar uma graninha \n\n extra, e olha so que sorte a sua, acabou de abrir uma vaga com o seu nome \n\n\n na banquinha do seu tio! E não tem momento melhor pra isso, por que o tio\n\n ta precisando tirar umas \u0022ferias especiais\u0022 por causa de um\n\n\n desentendimento com um amigo, voce entende, ne? Enfim, o combinado e\n\n o seguinte: voce precisa juntar R$500,00 ate o fim do mes pra esse meu\n\n amigo, fora isso, pode ficar com o resto! Dificil de recusar, nao? E a parte\n\n de administrar a banca e moleza, e so lembrar daquelas vezes que voce\n\n veio me ajudar quando era mais novo e das dicas que eu te dei.\n\n Voce consegue garoto, confio em voce.";
        std::string linha1 = "Sua mãe me disse que você estava atras de um bico pra ganhar uma graninha ";
        std::string linha2 = "extra, e olha só que sorte a sua, acabou de abrir uma vaga com o seu nome ";
        std::string linha3 = "na banquinha do seu tio! E não tem momento melhor pra isso, por que o tio";
        std::string linha4 = "tá precisando tirar umas \u0022férias especiais\u0022 por causa de um desentendimento";
        std::string linha5 = "com um amigo, você entende, né? Enfim, o combinado é o seguinte:";
        std::string linha6 = "você precisa juntar R$500,00 ate o fim do mês pra esse meu amigo,";
        std::string linha7 = "fora isso, pode ficar com o resto! Difícil de recusar, não? E a parte";
        std::string linha8 = "de administrar a banca é moleza, é só lembrar daquelas vezes que você";
        std::string linha9 = "veio me ajudar quando era mais novo e das dicas que eu te dei.";
        std::string linha10 = "Você consegue garoto, confio em você!";

        std::string textocartaFinal1 = "PS: e muito importante que voce consiga esse dinheiro, ouviu?";
        std::string textocartaFinal2 = "Se nao conseguir, feche a banca e nao volte mais.";

        GameObject *textoCartaGO1 = new GameObject();
        textoCartaGO1->AddComponent(new Text(*textoCartaGO1, "assets/font/Karma Suture.otf", 40, Text::BLENDED, "Fala, garoto!", {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO1->box.SetOrigin(610,130);
        AddObject(textoCartaGO1);
        //GameObject *textoCartaGO2 = new GameObject();
        //textoCartaGO2->AddComponent(new Text(*textoCartaGO2, "assets/font/Karma Suture.otf", 20, Text::BLENDED, textocarta, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        //textoCartaGO2->box.SetOrigin(610,210);
        //AddObject(textoCartaGO2);

        GameObject *linha1CartaGO = new GameObject();
        linha1CartaGO->AddComponent(new Text(*linha1CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha1, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha1CartaGO->box.SetOrigin(610,210);
        AddObject(linha1CartaGO);

        GameObject *linha2CartaGO = new GameObject();
        linha2CartaGO->AddComponent(new Text(*linha2CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha2, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha2CartaGO->box.SetOrigin(610,270);
        AddObject(linha2CartaGO);

        GameObject *linha3CartaGO = new GameObject();
        linha3CartaGO->AddComponent(new Text(*linha3CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha3, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha3CartaGO->box.SetOrigin(610,330);
        AddObject(linha3CartaGO);

        GameObject *linha4CartaGO = new GameObject();
        linha4CartaGO->AddComponent(new Text(*linha4CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha4, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha4CartaGO->box.SetOrigin(610,390);
        AddObject(linha4CartaGO);

        GameObject *linha5CartaGO = new GameObject();
        linha5CartaGO->AddComponent(new Text(*linha5CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha5, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha5CartaGO->box.SetOrigin(610,450);
        AddObject(linha5CartaGO);

        GameObject *linha6CartaGO = new GameObject();
        linha6CartaGO->AddComponent(new Text(*linha6CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha6, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha6CartaGO->box.SetOrigin(610,510);
        AddObject(linha6CartaGO);

        GameObject *linha7CartaGO = new GameObject();
        linha7CartaGO->AddComponent(new Text(*linha7CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha7, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha7CartaGO->box.SetOrigin(610,570);
        AddObject(linha7CartaGO);

        GameObject *linha8CartaGO = new GameObject();
        linha8CartaGO->AddComponent(new Text(*linha8CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha8, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha8CartaGO->box.SetOrigin(610,630);
        AddObject(linha8CartaGO);

        GameObject *linha9CartaGO = new GameObject();
        linha9CartaGO->AddComponent(new Text(*linha9CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha9, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha9CartaGO->box.SetOrigin(610,690);
        AddObject(linha9CartaGO);

        GameObject *linha10CartaGO = new GameObject();
        linha10CartaGO->AddComponent(new Text(*linha10CartaGO, "assets/font/Karma Suture.otf", 20, Text::BLENDED, linha10, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        linha10CartaGO->box.SetOrigin(610,750);
        AddObject(linha10CartaGO);

        std::string textocarta3 = "Um Abraco"; 
        GameObject *textoCartaGO3 = new GameObject();
        textoCartaGO3->AddComponent(new Text(*textoCartaGO3, "assets/font/Karma Suture.otf", 30, Text::BLENDED, textocarta3, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO3->box.SetOrigin(610,800);
        AddObject(textoCartaGO3);

        std::string textocarta4 = "Seu Tio"; 
        GameObject *textoCartaGO4 = new GameObject();
        textoCartaGO4->AddComponent(new Text(*textoCartaGO4, "assets/font/Karma Suture.otf", 30, Text::BLENDED, textocarta4, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO4->box.SetOrigin(610,860);
        AddObject(textoCartaGO4);

        GameObject *textoCartaGO5 = new GameObject();
        textoCartaGO5->AddComponent(new Text(*textoCartaGO5, "assets/font/Karma Suture.otf", 20, Text::BLENDED, textocartaFinal1, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO5->box.SetOrigin(610,930);
        AddObject(textoCartaGO5);

        GameObject *textoCartaGO6 = new GameObject();
        textoCartaGO6->AddComponent(new Text(*textoCartaGO6, "assets/font/Karma Suture.otf", 20, Text::BLENDED, textocartaFinal2, {0, 0, 0, SDL_ALPHA_OPAQUE}));
        textoCartaGO6->box.SetOrigin(610,990);
        AddObject(textoCartaGO6);

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
        cartaFechada = true;
        State *stage = new StageState(true);
        Game::GetInstance().Push(stage);
    }

    UpdateArray(dt);
}

void LetterState::Render()
{
    RenderArray();
}
