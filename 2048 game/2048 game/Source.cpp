#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>


constexpr int IMG_SIZE = 64;
constexpr int ILGIS = 8;
constexpr int PLOTIS = 8;
int OpacityDim = 120;

void Divider(sf::RenderWindow &window, bool Lost) {
    sf::Texture white;
    white.loadFromFile("images/Black.png");
    sf::Sprite swhite;
    swhite.setTexture(white);
    if (Lost) {
        sf::Color cwhite(swhite.getColor().r, swhite.getColor().g, swhite.getColor().b, 120); swhite.setColor(cwhite);
    }

    for (int b = 0; b < PLOTIS; b++) {
        swhite.setPosition(ILGIS * IMG_SIZE, b * IMG_SIZE);
        window.draw(swhite);
    }
}
void Texture_Render(sf::Texture& i0, sf::Texture& i2, sf::Texture& i4, sf::Texture& i8, sf::Texture& i16, sf::Texture& i32, sf::Texture& i64, sf::Texture& i128, sf::Texture& i256, sf::Texture& i512, sf::Texture& i1024, sf::Texture& i2048, sf::Sprite &s0, sf::Sprite &s2, sf::Sprite &s4, sf::Sprite &s8, sf::Sprite &s16, sf::Sprite &s32,sf::Sprite &s64, sf::Sprite &s128, sf::Sprite &s256, sf::Sprite &s512, sf::Sprite &s1024,sf::Sprite &s2048) {
    i0.loadFromFile("images/blank.png");
    i2.loadFromFile("images/2.png");
    i4.loadFromFile("images/4.png");
    i8.loadFromFile("images/8.png");
    i16.loadFromFile("images/16.png");
    i32.loadFromFile("images/32.png");
    i64.loadFromFile("images/64.png");
    i128.loadFromFile("images/128.png");
    i256.loadFromFile("images/256.png");
    i512.loadFromFile("images/512.png");
    i1024.loadFromFile("images/1024.png");
    i2048.loadFromFile("images/2048.png");

    s0.setTexture(i0);
    s2.setTexture(i2);
    s4.setTexture(i4);
    s8.setTexture(i8);
    s16.setTexture(i16);
    s32.setTexture(i32);
    s64.setTexture(i64);
    s128.setTexture(i128);
    s256.setTexture(i256);
    s512.setTexture(i512);
    s1024.setTexture(i1024);
    s2048.setTexture(i2048);
    sf::Color a(s2.getColor().r, s2.getColor().g, s2.getColor().b, 255);
    //s16.setColor(a);
}
void Texture_Dimmer(int Opacity,sf::Sprite& s0, sf::Sprite& s2, sf::Sprite& s4, sf::Sprite& s8, sf::Sprite& s16, sf::Sprite& s32, sf::Sprite& s64, sf::Sprite& s128, sf::Sprite& s256, sf::Sprite& s512, sf::Sprite& s1024, sf::Sprite& s2048) {

    sf::Color c0(s0.getColor().r, s0.getColor().g, s0.getColor().b, Opacity); s0.setColor(c0);
    sf::Color c2(s2.getColor().r, s2.getColor().g, s2.getColor().b, Opacity); s2.setColor(c2);
    sf::Color c4(s4.getColor().r, s4.getColor().g, s4.getColor().b, Opacity); s4.setColor(c4);
    sf::Color c8(s8.getColor().r, s8.getColor().g, s8.getColor().b, Opacity); s8.setColor(c8);
    sf::Color c16(s16.getColor().r, s16.getColor().g, s16.getColor().b, Opacity); s16.setColor(c16);
    sf::Color c32(s32.getColor().r, s32.getColor().g, s32.getColor().b, Opacity); s32.setColor(c32);
    sf::Color c64(s64.getColor().r, s64.getColor().g, s64.getColor().b, Opacity); s64.setColor(c64);
    sf::Color c128(s128.getColor().r, s128.getColor().g, s128.getColor().b, Opacity); s128.setColor(c128);
    sf::Color c256(s256.getColor().r, s256.getColor().g, s256.getColor().b, Opacity); s256.setColor(c256);
    sf::Color c512(s512.getColor().r, s512.getColor().g, s512.getColor().b, Opacity); s512.setColor(c512);
    sf::Color c1024(s1024.getColor().r, s1024.getColor().g, s1024.getColor().b, Opacity); s1024.setColor(c1024);
    sf::Color c2048(s2048.getColor().r, s2048.getColor().g, s2048.getColor().b, Opacity); s2048.setColor(c2048);
}

class Lenta {
protected:
    int Grid[ILGIS][PLOTIS] = {0};
    int push = 0;
    sf::Texture i0, i2, i4, i8, i16, i32, i64, i128, i256, i512, i1024, i2048;
    sf::Sprite s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048;
    int SpecialCount = 1;
    bool WonGame = 0;
    bool LostGame = 0;
public: 
    Lenta() {};
    ~Lenta(){};
    void RenderPng() { // uzdeda ant sprites .png
        Texture_Render(i0, i2, i4, i8, i16, i32, i64, i128, i256, i512, i1024, i2048, s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048); //perkelia .png failus i sprites
    }
    void DimPng(int Opacity) { // sumazina ryskuma visu sprites
        Texture_Dimmer(Opacity,s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048);
    }
    void NewTile() { // sukuria nauja tile (2 arba 4)
        int temp;
        srand(time(NULL));
        if (rand() % 10 < 5)
            temp = 2;
        else
            temp = 4;

        int x, y;
        bool laisva = false; // ar yra bent vienas laisvas langelis
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                if (Grid[i][b] == 0) {
                    i = ILGIS;
                    b = PLOTIS;
                    laisva = true;
                }
            }
        }

        while (true && laisva) {
            x = rand() % ILGIS;
            y = rand() % PLOTIS;
            if (Grid[x][y] == 0) {
                Grid[x][y] = temp;
                break;
            }
        }
    }
    void PushInput(int x) { // gauna, kiek reikia pastumti visus piesiamus objektus (kad nesikirsti su kitais zaidejais)
        push = x;
    }
    void Shift(int x) { // pajudina visus langelius i pasirinkta krypti
        if (!LostGame) {
            bool changes = false;
            int tempGrid[ILGIS][PLOTIS];
            for (int i = 0; i < ILGIS; i++) {
                for (int b = 0; b < PLOTIS; b++) {
                    tempGrid[i][b] = Grid[i][b];
                }
            }
            if (x == 0) {
                for (int i = 0; i < ILGIS; i++) {
                    for (int b = 1; b < PLOTIS; b++) {
                        if (b != 0) {
                            if (Grid[i][b - 1] == Grid[i][b]) {
                                Grid[i][b - 1] = Grid[i][b - 1] * 2;
                                Grid[i][b] = 0;
                            }
                            else if (Grid[i][b - 1] == 0 && Grid[i][b] != 0) {
                                Grid[i][b - 1] = Grid[i][b];
                                Grid[i][b] = 0;
                                b -= 2;
                            }
                        }
                    }
                }
            }
            else if (x == 1) { // Down
                for (int i = 0; i < ILGIS; i++) {
                    for (int b = PLOTIS - 2; b >= 0; b--) {
                        if (b != PLOTIS - 1) {
                            if (Grid[i][b + 1] == Grid[i][b]) {
                                Grid[i][b + 1] = Grid[i][b + 1] * 2;
                                Grid[i][b] = 0;
                            }
                            else if (Grid[i][b + 1] == 0 && Grid[i][b] != 0) {
                                Grid[i][b + 1] = Grid[i][b];
                                Grid[i][b] = 0;
                                b += 2;
                            }
                        }
                    }
                }
            }
            else if (x == 2) { // Left
                for (int b = 0; b < PLOTIS; b++) {
                    for (int i = 0; i < ILGIS; i++) {
                        if (i != 0) {
                            if (Grid[i - 1][b] == Grid[i][b]) {
                                Grid[i - 1][b] = Grid[i - 1][b] * 2;
                                Grid[i][b] = 0;
                            }
                            else if (Grid[i - 1][b] == 0 && Grid[i][b] != 0) {
                                Grid[i - 1][b] = Grid[i][b];
                                Grid[i][b] = 0;
                                i -= 2;
                            }
                        }
                    }
                }
            }
            else if (x == 3) {
                for (int b = 0; b < PLOTIS; b++) {
                    for (int i = ILGIS - 1; i >= 0; i--) {
                        if (i != ILGIS - 1) {
                            if (Grid[i + 1][b] == Grid[i][b]) {
                                Grid[i + 1][b] = Grid[i + 1][b] * 2;
                                Grid[i][b] = 0;
                            }
                            else if (Grid[i + 1][b] == 0 && Grid[i][b] != 0) {
                                Grid[i + 1][b] = Grid[i][b];
                                Grid[i][b] = 0;
                                i += 2;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < ILGIS; i++) {
                for (int b = 0; b < PLOTIS; b++) {
                    if (tempGrid[i][b] != Grid[i][b])
                        changes = true;
                }
            }
            if (changes) {
                NewTile();
            }
        }
        

    }
    void Special() { // special ability, panaikina visus 2 ir 4 langelius
        
        if (SpecialCount > 0) {
            bool galima = false;
            for (int i = 0; i < ILGIS && !galima; i++) {
                for (int b = 0; b < PLOTIS && !galima; b++) {
                    if (Grid[i][b] != 2 && Grid[i][b] != 4)
                        galima = true;
                }
            }
            if (galima) {
                for (int i = 0; i < ILGIS; i++) {
                    for (int b = 0; b < PLOTIS; b++) {
                        if (Grid[i][b] == 2 || Grid[i][b] == 4)
                            Grid[i][b] = 0;
                    }
                }
                SpecialCount--;
            }
            
        }
        
    }
    int Score() { // apskaiciuoja visu langeliu suma
        int suma = 0;
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                suma += Grid[i][b];
            }
        }
        return suma;
    }
    void Win() { // Patikrina, ar laimeta (ar yra 2048 langelis)
        bool b2048 = false;
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                if (Grid[i][b] == 2048) {
                    b2048 = true;
                    i = ILGIS;
                    b = PLOTIS;
                }
            }
        }
        if (b2048)
            WonGame = true;
    }
    bool Lose() { // Patikrina, ar pralosta
        bool laisva = false;
        for (int i = 0; i < ILGIS && SpecialCount == 0; i++) {
            for (int b = 0; b < PLOTIS && SpecialCount == 0; b++) {
                if (Grid[i][b] == 0) {
                    laisva = true;
                    i = ILGIS;
                    b = PLOTIS;
                }
            }
        }
        if (!laisva && SpecialCount == 0) {
            int TempGrid[ILGIS][PLOTIS];
            for (int i = 0; i < ILGIS; i++) {
                for (int b = 0; b < PLOTIS; b++) {
                    TempGrid[i][b] = Grid[i][b];
                }
            }
            bool pasikeite = false;
            Shift(0);
            for (int i = 0; i < ILGIS && !pasikeite; i++) {
                for (int b = 0; b < PLOTIS && !pasikeite; b++) {
                    if (Grid[i][b] != TempGrid[i][b]) {
                        pasikeite = true;
                        i = ILGIS;
                        b = PLOTIS;
                    }
                }
            }
            Shift(1);
            for (int i = 0; i < ILGIS && !pasikeite; i++) {
                for (int b = 0; b < PLOTIS && !pasikeite; b++) {
                    if (Grid[i][b] != TempGrid[i][b]) {
                        pasikeite = true;
                        i = ILGIS;
                        b = PLOTIS;
                    }
                }
            }
            Shift(2);
            for (int i = 0; i < ILGIS && !pasikeite; i++) {
                for (int b = 0; b < PLOTIS && !pasikeite; b++) {
                    if (Grid[i][b] != TempGrid[i][b]) {
                        pasikeite = true;
                        i = ILGIS;
                        b = PLOTIS;
                    }
                }
            }
            Shift(3);
            for (int i = 0; i < ILGIS && !pasikeite; i++) {
                for (int b = 0; b < PLOTIS && !pasikeite; b++) {
                    if (Grid[i][b] != TempGrid[i][b]) {
                        pasikeite = true;
                        i = ILGIS;
                        b = PLOTIS;
                    }
                }
            }

            if (pasikeite) {
                for (int i = 0; i < ILGIS; i++) {
                    for (int b = 0; b < PLOTIS; b++) {
                        Grid[i][b] = TempGrid[i][b];
                    }
                }
            }
            if (!pasikeite) {
                LostGame = true;
                DimPng(OpacityDim);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    void Reset() {
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                Grid[i][b] = 0;
            }
        }
        SpecialCount = 1;
        WonGame = false;
        LostGame = false;
    }
    void Draw(sf::RenderWindow &window, sf::Font font, int fontsize) {
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                switch (Grid[i][b]) {
                case 0:
                    s0.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s0);
                    break;
                case 2:
                    s2.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s2);
                    break;
                case 4:
                    s4.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s4);
                    break;
                case 8:
                    s8.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s8);
                    break;
                case 16:
                    s16.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s16);
                    break;
                case 32:
                    s32.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s32);
                    break;
                case 64:
                    s64.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s64);
                    break;
                case 128:
                    s128.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s128);
                    break;
                case 256:
                    s256.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s256);
                    break;
                case 512:
                    s512.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s512);
                    break;
                case 1024:
                    s1024.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s1024);
                    break;
                case 2048:
                    s2048.setPosition((i * IMG_SIZE)+push, b * IMG_SIZE);
                    window.draw(s2048);
                    break;
                }
                
            }
        }
        std::string ScoreString;

        ScoreString = "Score:";
        ScoreString += std::to_string(Score());
        ScoreString += "\nSpecial:";
        ScoreString += std::to_string(SpecialCount);

        if (WonGame)
            ScoreString += "  WON!";
        else if (LostGame)
            ScoreString += "  Lost :[";

        int tempPush;
        if (push == 0)
            tempPush = 0;
        else
            tempPush = push - 12;

        sf::Text ScoreTekstas; ScoreTekstas.setString(ScoreString); ScoreTekstas.setFont(font); ScoreTekstas.setCharacterSize(fontsize-12); ScoreTekstas.setPosition(tempPush, PLOTIS * IMG_SIZE); ScoreTekstas.setFillColor(sf::Color::Red);
        window.draw(ScoreTekstas);
    }
};

class Player:public Lenta {
};

class AI :public Lenta {
private:
    int paskutinesEigos[100][4] = {0};
public:
    int LaisvuLangeliuKiekis(){
        int kiekis = 0;
        for (int i = 0; i < ILGIS; i++) {
            for (int b = 0; b < PLOTIS; b++) {
                if (Grid[i][b] != 0)
                    kiekis++;
            }
        }

        return kiekis;
    }
    bool Lost() {
        return LostGame;
    }
    void Auto() {
        if (!WonGame && !LostGame) {
            int tempGrid[ILGIS][PLOTIS];
            for (int i = 0; i < ILGIS; i++) {
                for (int b = 0; b < PLOTIS; b++) {
                    tempGrid[i][b] = Grid[i][b];
                }
            }

            int minimumLangeliu = ILGIS * PLOTIS;
            int minimumScore = 0;
            int eiga[4] = {5,5,5,5};
            bool reikiaSpecial = true;

            for (int w = 1; w < 4; w++) {
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y < 4; y++) {
                        for (int z = 0; z < 4; z++) {

                            for (int i = 0; i < ILGIS; i++) {
                                for (int b = 0; b < PLOTIS; b++) {
                                    Grid[i][b] = tempGrid[i][b];
                                }

                            }
                            Shift(w); Shift(x); Shift(y); Shift(z);
                            if (LaisvuLangeliuKiekis() < minimumLangeliu && minimumScore < Score()) {
                                minimumScore = Score();
                                minimumLangeliu = LaisvuLangeliuKiekis();
                                eiga[0] = w; eiga[1] = x; eiga[2] = y; eiga[3] = z;
                            }
                            //std::cout << w << x << y << z << std::endl;
                        }
                    }
                }
            }
            for (int i = 0; i < ILGIS; i++) {
                for (int b = 0; b < PLOTIS; b++) {
                    if (Grid[i][b] != tempGrid[i][b]) {
                        Grid[i][b] = tempGrid[i][b];
                        reikiaSpecial = false;
                    }

                }
            }

            for (int i = 99; i >= 0; i--) {
                if (i != 0) {
                    for (int b = 0; b < 4; b++) {
                        paskutinesEigos[i][b] = paskutinesEigos[i - 1][b];
                    }
                }
                else if (i == 0) {
                    for (int b = 0; b < 4; b++) {
                        paskutinesEigos[i][b] = eiga[b];
                    }
                }
            }

            bool nesikartoja10kartu = true;
            for (int i = 0; i < 99 && nesikartoja10kartu; i++) {
                for (int b = 0; b < 4; b++) {
                    if (paskutinesEigos[i][b] != paskutinesEigos[i + 1][b])
                        nesikartoja10kartu = false;
                }
            }
            
            if (nesikartoja10kartu) {
                LostGame = 1;
                DimPng(OpacityDim);
            } 
            if (reikiaSpecial && SpecialCount > 0)
                Special();
            else {
                for (int i = 0; i < 4; i++) {
                    Shift(eiga[i]);
                }
            }
        }
       
    }
};

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(((ILGIS*2+1) * IMG_SIZE), ((PLOTIS+1) * IMG_SIZE)), "2048 game", sf::Style::Close | sf::Style::Titlebar); // sukuriamas langas
    window.setFramerateLimit(60);
    sf::Image windowIcon;
    windowIcon.loadFromFile("images/windowIcon.png");
    window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

    bool OptionSelect = false;
    int Option = 0;
    int fontsize = 36;

    sf::Font font;
    if (!font.loadFromFile("fonts/slkscr.ttf")) {
        return EXIT_FAILURE;
    }
   sf::Text menu[3];
   std::string text[3] = { "Player vs AI", "Player vs Player" , "AI showcase" };
   menu[0].setFont(font);menu[1].setFont(font);menu[2].setFont(font);
   menu[0].setString(text[0]); menu[1].setString(text[1]); menu[2].setString(text[2]);
   menu[0].setCharacterSize(fontsize);menu[1].setCharacterSize(fontsize);menu[2].setCharacterSize(fontsize);
   menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
   menu[0].setOrigin(menu[0].getGlobalBounds().width / 2.0, menu[0].getGlobalBounds().height / 2.0); menu[1].setOrigin(menu[1].getGlobalBounds().width / 2.0, menu[1].getGlobalBounds().height / 2.0); menu[2].setOrigin(menu[2].getGlobalBounds().width / 2.0, menu[2].getGlobalBounds().height / 2.0);
   menu[0].setPosition(window.getSize().x/2.0, window.getSize().y / 10 *2 ); menu[1].setPosition(window.getSize().x / 2.0, window.getSize().y / 10 * 5); menu[2].setPosition(window.getSize().x / 2.0, window.getSize().y / 10 * 8);

   //sf::Text testas;testas.setString("Avis"); testas.setFont(font); testas.setCharacterSize(fontsize); testas.setPosition((ILGIS + 1) * IMG_SIZE, PLOTIS*IMG_SIZE); testas.setFillColor(sf::Color::Red);

   bool FirstRender = true;

   Player player1;
   Player player2;
   AI Ai;
   AI Ai2;

   player2.PushInput((ILGIS + 1) * IMG_SIZE);
   Ai.PushInput((ILGIS + 1) * IMG_SIZE);

   player1.RenderPng();
   player2.RenderPng();
   Ai.RenderPng();
   Ai2.RenderPng();

    while (window.isOpen())
    {
        sf::Event Press;
  
        if (OptionSelect)
        {
            if (Option == 0) {
                if (FirstRender) {
                    FirstRender = false;
                    player1.Reset();
                    Ai.Reset();

                    player1.DimPng(255);
                    Ai.DimPng(255);

                    player1.NewTile(); player1.NewTile();
                    Ai.NewTile(); Ai.NewTile();
                }
                while (window.pollEvent(Press))
                {
                    if (Press.type == sf::Event::KeyPressed)
                    {
                             if (Press.key.code == sf::Keyboard::A || Press.key.code == sf::Keyboard::Left)  { player1.Shift(2); Ai.Auto(); }
                        else if (Press.key.code == sf::Keyboard::D || Press.key.code == sf::Keyboard::Right) { player1.Shift(3); Ai.Auto(); }
                        else if (Press.key.code == sf::Keyboard::W || Press.key.code == sf::Keyboard::Up)  { player1.Shift(0); Ai.Auto(); }
                        else if (Press.key.code == sf::Keyboard::S || Press.key.code == sf::Keyboard::Down) { player1.Shift(1); Ai.Auto(); }
                        else if (Press.key.code == sf::Keyboard::X) { player1.Special(); }
                        else if (Press.key.code == sf::Keyboard::R) {
                            OptionSelect = false;
                            Option = 0;
                            FirstRender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (Press.type == sf::Event::Closed)
                        window.close();
                }
                player1.Lose();
                player1.Win();
                Ai.Win();

                window.clear();
                player1.Draw(window, font, fontsize);
                Ai.Draw(window, font, fontsize);
                Divider(window, Ai.Lost());
                window.display();
            }
            else if (Option == 1) {
                if (FirstRender) {
                    FirstRender = false;
                    player1.Reset();
                    player2.Reset();

                    player1.DimPng(255);
                    player2.DimPng(255);

                    player1.NewTile(); player1.NewTile();
                    player2.NewTile(); player2.NewTile();
                }
                while (window.pollEvent(Press))
                {
                    if (Press.type == sf::Event::KeyPressed)
                    {
                        if (Press.key.code == sf::Keyboard::A)
                            player1.Shift(2);
                        else if (Press.key.code == sf::Keyboard::D)
                            player1.Shift(3);
                        else if (Press.key.code == sf::Keyboard::W)
                            player1.Shift(0);
                        else if (Press.key.code == sf::Keyboard::S)
                            player1.Shift(1);
                        else if (Press.key.code == sf::Keyboard::Left)
                            player2.Shift(2);
                        else if (Press.key.code == sf::Keyboard::Right)
                            player2.Shift(3);
                        else if (Press.key.code == sf::Keyboard::Up)
                            player2.Shift(0);
                        else if (Press.key.code == sf::Keyboard::Down)
                            player2.Shift(1);
                        else if (Press.key.code == sf::Keyboard::X)
                            player1.Special();
                        else if (Press.key.code == sf::Keyboard::M)
                            player2.Special();
                        else if (Press.key.code == sf::Keyboard::R) {
                            OptionSelect = false;
                            Option = 0;
                            FirstRender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (Press.type == sf::Event::Closed)
                        window.close();
                }
                player1.Lose();
                player2.Lose();
                player1.Win();
                player2.Win();

                window.clear();
                player1.Draw(window, font, fontsize);
                player2.Draw(window, font, fontsize);
                Divider(window, player2.Lose());
                window.display();

            }
            else if (Option == 2) {
                if (FirstRender) {
                    FirstRender = false;
                    Ai.Reset();
                    Ai2.Reset();

                    Ai.DimPng(255);
                    Ai2.DimPng(255);

                    Ai2.NewTile(); Ai2.NewTile(); Ai2.NewTile();
                    Ai.NewTile(); Ai.NewTile();
                }
                while (window.pollEvent(Press))
                {
                    if (Press.type == sf::Event::KeyPressed)
                    {
                        if (Press.key.code == sf::Keyboard::R) {
                            OptionSelect = false;
                            Option = 0;
                            FirstRender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (Press.type == sf::Event::Closed)
                        window.close();
                }
                Ai.Auto();
                Ai2.Auto();
                Ai.Win();
                Ai2.Win();

                window.clear();
                Ai2.Draw(window, font, fontsize);
                Ai.Draw(window, font, fontsize);
                Divider(window, Ai.Lost());
                window.display();
            }
            else if (Option == 4) {



                if (FirstRender) {
                    FirstRender = false;
                    player1.NewTile(); player1.NewTile();
                    Ai.NewTile(); Ai.NewTile();
                }


                while (window.pollEvent(Press))
                {
                    if (Press.type == sf::Event::KeyPressed)
                    {
                        if (Press.key.code == sf::Keyboard::Left || Press.key.code == sf::Keyboard::A)
                            Ai.Auto();
                        else if (Press.key.code == sf::Keyboard::Right || Press.key.code == sf::Keyboard::D)
                            player1.Shift(3);
                        else if (Press.key.code == sf::Keyboard::Up || Press.key.code == sf::Keyboard::W)
                            player1.Shift(0);
                        else if (Press.key.code == sf::Keyboard::Down || Press.key.code == sf::Keyboard::S)
                            player1.Shift(1);
                        else if (Press.key.code == sf::Keyboard::X)
                            player1.Special();
                    }
                    else if (Press.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                player1.Draw(window, font, fontsize);
                Ai.Draw(window, font, fontsize);
                Divider(window, 0);
                window.display();
            }
            
        }
        else {
            
            window.clear();
            sf::Texture iblanko;
            iblanko.loadFromFile("images/blankopace.png");
            sf::Sprite sblanko;
            sblanko.setTexture(iblanko);
            for (int i = 0; i < (ILGIS*2+1); i++) {
                for (int b = 0; b < PLOTIS+1; b++) {
                    sblanko.setPosition((i * IMG_SIZE), b * IMG_SIZE);
                    window.draw(sblanko);
                }
            }
            window.draw(menu[0]);
            window.draw(menu[1]);
            window.draw(menu[2]);
            window.display();
            while (window.pollEvent(Press))
            {
                if (Press.type == sf::Event::KeyPressed)
                {
                    if ((Press.key.code == sf::Keyboard::Down || Press.key.code == sf::Keyboard::S) && Option != 2) {
                        Option++;
                        for (int i = 0; i < 3; i++) {
                            if (i == Option)
                                menu[i].setFillColor(sf::Color::Red);
                            else
                                menu[i].setFillColor(sf::Color::White);
                        }
                    }
                    else if ((Press.key.code == sf::Keyboard::Up || Press.key.code == sf::Keyboard::W) && Option != 0) {
                        Option--;
                        for (int i = 0; i < 3; i++) {
                            if (i == Option)
                                menu[i].setFillColor(sf::Color::Red);
                            else
                                menu[i].setFillColor(sf::Color::White);
                        }
                        
                    }
                    else if (Press.key.code == sf::Keyboard::Enter) {
                        OptionSelect = true;
                        if (Option != 1 && Option != 0 && Option != 2)
                            Option = 4;
                    }

                    window.clear();
                    for (int i = 0; i < (ILGIS * 2 + 1); i++) {
                        for (int b = 0; b < PLOTIS+1; b++) {
                            sblanko.setPosition((i * IMG_SIZE), b * IMG_SIZE);
                            window.draw(sblanko);
                        }
                    }
                    window.draw(menu[0]);
                    window.draw(menu[1]);
                    window.draw(menu[2]);
                    window.display();
                    
                        
                }
                else if (Press.type == sf::Event::Closed)
                    window.close();
            }
            
        }
    }
    return 0;
}
