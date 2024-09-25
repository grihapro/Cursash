#include "file.h"

using namespace std;

bool win(SDL_Renderer* renderer, int score)
{
    background menu_back(renderer);
    SDL_bool done = SDL_FALSE;
    bool flagend = 0;
    menu_text scoret(renderer);
    text next(renderer);
    while (!done) {
        SDL_Event ev;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        menu_back.show("back4.png");
        scoret.show(u8"��� ����: " + to_string(score), 100, 200, 60);
        next.show(u8"��� �������� � ������� ���� ������� ������", 20, 450, 20);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                done = SDL_TRUE;
                flagend = 1;
            }
            if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                done = SDL_TRUE;
            }
        }
    }
    return flagend;
}

bool game(SDL_Renderer* renderer, string player)
{
    fish1 = loadTexture("fish.png", renderer);
    fish2 = loadTexture("fish2.png", renderer);
    inversed_fish1 = loadTexture("fish_inversed.png", renderer);
    inversed_fish2 = loadTexture("fish2_inversed.png", renderer);
    trash1 = loadTexture("trash1.png", renderer);
    trash2 = loadTexture("trash2.png", renderer);
    SDL_bool done = SDL_FALSE;
    background menu_back(renderer);
    bool s = 0, flag = 0, flagend = 0; int ifish, score = 0, a; double time = 100;
    vector <class object*> VectorObject;
    vector <class menu_text*> VectorText;
    for (int i = 0; i < 3; i++)
    {
        VectorText.push_back(new menu_text(renderer));
    }
    for (int i = 0, x = 200; i < 5; i++, x += 50)// ������ �� 0 �� 4
    {
        VectorObject.push_back(new fish(renderer, x, s));
        s = !s;
    }
    VectorObject.push_back(new hook(renderer)); //������ 5
    hook* h = dynamic_cast<hook*>(VectorObject.at(5));
    while (!done)
    {
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        menu_back.show("back2.jpg");
        h->move(&flag, &VectorObject, &ifish);
        for (int i = 0; i < 5; i++)
        {
            fish* f = dynamic_cast<fish*>(VectorObject.at(i));
            if (i != ifish)
                f->move(i);
            else
            {
                a = f->moveup(i);
                if (a)
                {
                    ifish = -1;
                    score += a;
                }
            }
        }
        string sc = u8"����: ";
        string t = u8"�����: ";
        sc = sc + to_string(score);
        t = t + to_string(int(time));
        time -= 0.01;
        VectorText.at(0)->show(sc, 500, 20, 20);
        VectorText.at(1)->show(t, 500, 50, 20);
        VectorText.at(2)->show(u8"������� ""����"", ����� �������� ������.", 10, 450, 20);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        if (time < 0)
            done = SDL_TRUE;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = SDL_TRUE;
                flagend = 1;
            }
            if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    flag = 1;
                }
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                done = SDL_TRUE;
            }
        }
    }
    write(score, player);
    if (win(renderer, score))
        flagend = 1;
    return flagend;
}

bool enter_player(SDL_Renderer* renderer, string* player)
{
    background menu_back(renderer);
    SDL_bool done = SDL_FALSE;
    bool flagend = 0; int num = 0;
    SDL_StartTextInput();
    string in;
    text name(renderer), warning(renderer);
    while (!done) {
        SDL_Event ev;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        menu_back.show("back3.jpg");
        string input = u8"������� ���: ";
        input += in;
        name.show(input, 220, 180, 20);
        warning.show(u8"������������ ���������� �������� 14", 220, 210, 15);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&ev)) {
            if (ev.key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                *player = in;
                done = SDL_TRUE;
            }
            if (ev.type == SDL_TEXTINPUT) {
                if (num == 14)
                {
                }
                else
                {
                    in += ev.text.text; 
                    num++;
                }
                //cout << " > " << in << endl;
            }
            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && in.size()) {
                in.pop_back(); num--;
                //cout << " > " << in << endl;
            }
            if (ev.type == SDL_QUIT) {
                done = SDL_TRUE;
                flagend = 1;
            }
        }
    }

    SDL_StopTextInput();
    return flagend;
}

bool records(SDL_Renderer* renderer)
{
    background menu_back(renderer);
    SDL_bool done = SDL_FALSE;
    bool flagend = 0;
    while (!done) {
        SDL_Event ev;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); 
        SDL_RenderClear(renderer); 
        menu_back.show("back3.jpg");
        read(renderer);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                done = SDL_TRUE;
                flagend = 1;
            }
            if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                done = SDL_TRUE;
            }
        }
    }
    return flagend;
}

bool options(SDL_Renderer* renderer)
{
    background menu_back(renderer);
    SDL_bool done = SDL_FALSE;
    bool flagend = 0;
    while (!done) {
        SDL_Event ev;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        menu_back.show("back3.jpg");
        readtxt(renderer);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                done = SDL_TRUE;
                flagend = 1;
            }
            if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                done = SDL_TRUE;
            }
        }
    }
    return flagend;
}

void menu(SDL_Renderer* renderer)
{
    SDL_Cursor* cursor;
    background menu_back(renderer);
    SDL_bool done = SDL_FALSE;
    int x=-1, y=-1; 
    vector<class base_text*> buttons;
    vector<string> texts = {u8"�����", u8"����� ������", u8"�������", u8"�������", u8"�����"};
    string player = u8"NONAME";
    if (enter_player(renderer, &player))
        done = SDL_TRUE;
    for (int i = 0; i < 5; i++)
    {
        buttons.push_back(new menu_text(renderer));
    }
    buttons.push_back(new text(renderer));
    while (!done)
    {
        SDL_Event event;
        menu_text* t;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        menu_back.show("back3.jpg");
        for (int i = 0, x = 140; i < 5; i++, x+=40)
        {
            t = dynamic_cast<menu_text*>(buttons.at(i));
            t->show(texts.at(i), 20, x, 30);
        }
        text* tt = dynamic_cast<text*>(buttons.at(5));
        tt->show(u8"�����: " + player, 10, 10, 20);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = SDL_TRUE;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < 5; i++)
                {
                    t = dynamic_cast<menu_text*>(buttons.at(i));
                    if (t->click(x, y))
                    {
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                        SDL_SetCursor(cursor); break;
                    }
                    else {
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                        SDL_SetCursor(cursor); 
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
                SDL_GetMouseState(&x, &y);
                t = dynamic_cast<menu_text*>(buttons.at(0));
                if (t->click(x, y))
                    if (game(renderer, player))
                        done = SDL_TRUE;
                t = dynamic_cast<menu_text*>(buttons.at(1));
                if (t->click(x, y))
                    if (enter_player(renderer, &player))
                        done = SDL_TRUE;
                t = dynamic_cast<menu_text*>(buttons.at(2));
                if (t->click(x, y))
                    if (options(renderer))
                        done = SDL_TRUE;
                t = dynamic_cast<menu_text*>(buttons.at(3));
                if (t->click(x, y))
                    if (records(renderer))
                        done = SDL_TRUE;
                t = dynamic_cast<menu_text*>(buttons.at(4));
                if (t->click(x, y))
                    done = SDL_TRUE;
            }
        }
    }
}

void screen(SDL_Renderer* renderer)
{
    background menu_back(renderer);
    vector<class text*> texts;
    for (int i = 0; i < 3; i++)
    {
        texts.push_back(new text(renderer));
    }
    bool flagend = 0;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    menu_back.show("back1.jpg");
    texts.at(0)->show(u8"�������", 20, 20, 60);
    texts.at(1)->show(u8"�724�", 520, 20, 30);
    texts.at(2)->show(u8"������", 520, 50, 30);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}

int main(int argc, char* argv[])
{
    system("chcp 1251");
    system("cls");
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() < 0)
    {
        printf("Err load TTF library");
    }
    SDL_Window* window = SDL_CreateWindow(u8"�������!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    screen(renderer);
    menu(renderer);
    SDL_RenderPresent(renderer);
    if (renderer)SDL_DestroyRenderer(renderer);
    if (window)SDL_DestroyWindow(window);
    atexit(SDL_Quit);
    return 0;
}
