#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>


constexpr int IMG_SIZE = 64; // dimensions of used .png (64x64)
constexpr int LENGTH = 5;    // grid length
constexpr int WIDTH = 5;     // grid width
int opacitydim = 120;        // opacity which will be set for tiles if a player loses
int specialamount = 1;       //how many special abilites are given to the player each game

void Divider(sf::RenderWindow &window, bool lost) { // creates a dividing line between the two players
    sf::Texture divider;
    divider.loadFromFile("images/Black.png");
    sf::Sprite sdivider;
    sdivider.setTexture(divider);
    if (lost) {
        sf::Color cdivider(sdivider.getColor().r, sdivider.getColor().g, sdivider.getColor().b, 120); sdivider.setColor(cdivider);
    }

    for (int b = 0; b < WIDTH; b++) {
        sdivider.setPosition(LENGTH * IMG_SIZE, b * IMG_SIZE);
        window.draw(sdivider);
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

class Player { // main player class
protected:
    int grid[LENGTH][WIDTH] = {0};  // each tile's value
    int push;                       // how much the tiles that are drawn will have to be pushed to not draw over the first player
    sf::Texture i0, i2, i4, i8, i16, i32, i64, i128, i256, i512, i1024, i2048;
    sf::Sprite s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048;
    int specialcount;               // how many times the special ability can be used (to delete all tiles with 2 and 4)
    bool wongame;                   // flag for if the game is won (a tile of 2048 exists
    bool lostgame;                  // flag if the game is lost (no special ability left and can't move to any direction)
public: 
    Player() { push = 0; specialcount = specialamount; wongame = 0; lostgame = 0; };
    ~Player(){};
    void RenderPng() { // puts the .png over the sprites
        Texture_Render(i0, i2, i4, i8, i16, i32, i64, i128, i256, i512, i1024, i2048, s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048); //perkelia .png failus i sprites
    }
    void DimPng(int Opacity) { // dims the tiles
        Texture_Dimmer(Opacity,s0, s2, s4, s8, s16, s32, s64, s128, s256, s512, s1024, s2048);
    }
    void NewTile() { // creates a new tile (2 or 4)
        int temp;
        srand(time(NULL));
        if (rand() % 10 < 5)
            temp = 2;
        else
            temp = 4;

        int x, y;
        bool anyfreetiles = false; // flag for checking if atleast one tile is empty
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                if (grid[i][b] == 0) {
                    i = LENGTH;
                    b = WIDTH;
                    anyfreetiles = true;
                }
            }
        }

        while (true && anyfreetiles) {
            x = rand() % LENGTH;
            y = rand() % WIDTH;
            if (grid[x][y] == 0) {
                grid[x][y] = temp;
                break;
            }
        }
    }
    void PushInput(int x) { // input for how much the tiles will have to be pushed to the right when they are drawn
        push = x;
    }
    void Shift(int x) { // moves the tiles in the chosen direction
        if (!lostgame) {
            bool changes = false; // flag for checking if anything has changed
            int tempgrid[LENGTH][WIDTH]; // for storing initial tile values (before shifting)
            for (int i = 0; i < LENGTH; i++) {
                for (int b = 0; b < WIDTH; b++) {
                    tempgrid[i][b] = grid[i][b];
                }
            }
            if (x == 0) { // up
                for (int i = 0; i < LENGTH; i++) {
                    for (int b = 1; b < WIDTH; b++) {
                        if (b != 0) {
                            if (grid[i][b - 1] == grid[i][b]) {
                                grid[i][b - 1] = grid[i][b - 1] * 2;
                                grid[i][b] = 0;
                            }
                            else if (grid[i][b - 1] == 0 && grid[i][b] != 0) {
                                grid[i][b - 1] = grid[i][b];
                                grid[i][b] = 0;
                                b -= 2;
                            }
                        }
                    }
                }
            }
            else if (x == 1) { // down
                for (int i = 0; i < LENGTH; i++) {
                    for (int b = WIDTH - 2; b >= 0; b--) {
                        if (b != WIDTH - 1) {
                            if (grid[i][b + 1] == grid[i][b]) {
                                grid[i][b + 1] = grid[i][b + 1] * 2;
                                grid[i][b] = 0;
                            }
                            else if (grid[i][b + 1] == 0 && grid[i][b] != 0) {
                                grid[i][b + 1] = grid[i][b];
                                grid[i][b] = 0;
                                b += 2;
                            }
                        }
                    }
                }
            }
            else if (x == 2) { // left
                for (int b = 0; b < WIDTH; b++) {
                    for (int i = 0; i < LENGTH; i++) {
                        if (i != 0) {
                            if (grid[i - 1][b] == grid[i][b]) {
                                grid[i - 1][b] = grid[i - 1][b] * 2;
                                grid[i][b] = 0;
                            }
                            else if (grid[i - 1][b] == 0 && grid[i][b] != 0) {
                                grid[i - 1][b] = grid[i][b];
                                grid[i][b] = 0;
                                i -= 2;
                            }
                        }
                    }
                }
            }
            else if (x == 3) { // right
                for (int b = 0; b < WIDTH; b++) {
                    for (int i = LENGTH - 1; i >= 0; i--) {
                        if (i != LENGTH - 1) {
                            if (grid[i + 1][b] == grid[i][b]) {
                                grid[i + 1][b] = grid[i + 1][b] * 2;
                                grid[i][b] = 0;
                            }
                            else if (grid[i + 1][b] == 0 && grid[i][b] != 0) {
                                grid[i + 1][b] = grid[i][b];
                                grid[i][b] = 0;
                                i += 2;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < LENGTH; i++) { // checking if anything changed
                for (int b = 0; b < WIDTH; b++) {
                    if (tempgrid[i][b] != grid[i][b])
                        changes = true;
                }
            }
            if (changes) { // if any changes happened, a new tile is created
                NewTile();
            }
        }
        

    }
    void Special() { // special ability, removes all tiles with 2 and 4
        
        if (specialcount > 0) {
            bool allowed = false;
            for (int i = 0; i < LENGTH && !allowed; i++) { // checks if there are other tiles besides 2 and 4
                for (int b = 0; b < WIDTH && !allowed; b++) {
                    if (grid[i][b] != 2 && grid[i][b] != 4 && grid[i][b] != 0)
                        allowed = true;
                }
            }
            if (allowed) {
                for (int i = 0; i < LENGTH; i++) {
                    for (int b = 0; b < WIDTH; b++) {
                        if (grid[i][b] == 2 || grid[i][b] == 4)
                            grid[i][b] = 0;
                    }
                }
                specialcount--;
            }
            
        }
        
    }
    int Score() { // gets the sum of all tiles
        int score = 0;
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                score += grid[i][b];
            }
        }
        return score;
    }
    void Win() { // checks if the player has won (if a tile with the value of 2048 exists)
        bool b2048 = false;
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                if (grid[i][b] == 2048) {
                    b2048 = true;
                    i = LENGTH;
                    b = WIDTH;
                }
            }
        }
        if (b2048)
            wongame = true;
    }
    bool Lose() { // checks if the game is lost (no special ability left and can't move to any direction)
        bool anyfreetiles = false;
        for (int i = 0; i < LENGTH && specialcount == 0; i++) { // checks if all the tiles are taken
            for (int b = 0; b < WIDTH; b++) {
                if (grid[i][b] == 0) {
                    anyfreetiles = true;
                    i = LENGTH;
                    b = WIDTH;
                }
            }
        }
        if (!anyfreetiles && specialcount == 0) { // if there are no free tiles and the player dosen't have any more special abilities
            int tempgrid[LENGTH][WIDTH];
            for (int i = 0; i < LENGTH; i++) {
                for (int b = 0; b < WIDTH; b++) {
                    tempgrid[i][b] = grid[i][b];
                }
            }
            bool changed = false; // checks if it's possible to move in any directions
            Shift(0);
            for (int i = 0; i < LENGTH && !changed; i++) {
                for (int b = 0; b < WIDTH && !changed; b++) {
                    if (grid[i][b] != tempgrid[i][b]) {
                        changed = true;
                        i = LENGTH;
                        b = WIDTH;
                    }
                }
            }
            Shift(1);
            for (int i = 0; i < LENGTH && !changed; i++) {
                for (int b = 0; b < WIDTH && !changed; b++) {
                    if (grid[i][b] != tempgrid[i][b]) {
                        changed = true;
                        i = LENGTH;
                        b = WIDTH;
                    }
                }
            }
            Shift(2);
            for (int i = 0; i < LENGTH && !changed; i++) {
                for (int b = 0; b < WIDTH && !changed; b++) {
                    if (grid[i][b] != tempgrid[i][b]) {
                        changed = true;
                        i = LENGTH;
                        b = WIDTH;
                    }
                }
            }
            Shift(3);
            for (int i = 0; i < LENGTH && !changed; i++) {
                for (int b = 0; b < WIDTH && !changed; b++) {
                    if (grid[i][b] != tempgrid[i][b]) {
                        changed = true;
                        i = LENGTH;
                        b = WIDTH;
                    }
                }
            }

            if (changed) { // if the tiles can change, the original tile values are returned
                for (int i = 0; i < LENGTH; i++) {
                    for (int b = 0; b < WIDTH; b++) {
                        grid[i][b] = tempgrid[i][b];
                    }
                }
            }
            if (!changed) { // if nothing can change
                lostgame = true;
                DimPng(opacitydim);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    void Reset() { // resets the values for a new game
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                grid[i][b] = 0;
            }
        }
        specialcount = specialamount;
        wongame = false;
        lostgame = false;
    }
    void Draw(sf::RenderWindow &window, sf::Font font, int fontsize) { // draws the tiles and the information of the player
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                switch (grid[i][b]) {
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
       
        std::string playerinformation;
        playerinformation = "Score:";
        playerinformation += std::to_string(Score());
        playerinformation += "\nSpecial:";
        playerinformation += std::to_string(specialcount);
        // /\ Shows the current score and the amount of special abilites left
        
        if (wongame)
            playerinformation += "  WON!";
        else if (lostgame)
            playerinformation += "  Lost :[";
        // /\ checks if the player has either won or lost and add's the appropriate message

        int tempPush;
        if (push == 0)
            tempPush = 0;
        else
            tempPush = push - 12;
        // /\ used for allinging the playerinformation text

        sf::Text scoretext; scoretext.setString(playerinformation); scoretext.setFont(font); scoretext.setCharacterSize(fontsize-12); scoretext.setPosition(tempPush, WIDTH * IMG_SIZE); scoretext.setFillColor(sf::Color::Red);
        window.draw(scoretext);
    }
};

class AI :public Player {
private:
    int lastmoves[100][4] = {0}; // used for storing the last 100 movesets that the AI tried to do. Used for checking if the AI is stuck
public:
    int OccupiedTiles(){ // counts how many tiles are taken
        int count = 0;
        for (int i = 0; i < LENGTH; i++) {
            for (int b = 0; b < WIDTH; b++) {
                if (grid[i][b] != 0)
                    count++;
            }
        }

        return count;
    }
    bool ReturnLost() { // returns if the game is lost without checking if the game is lost (unlike Lose())
        return lostgame;
    }
    void Auto() { // make automatic movements
        if (!wongame && !lostgame) {
            int tempgrid[LENGTH][WIDTH]; // for storing initial tile values (before shifting)
            for (int i = 0; i < LENGTH; i++) {
                for (int b = 0; b < WIDTH; b++) {
                    tempgrid[i][b] = grid[i][b];
                }
            }

            int smallesttilecount = LENGTH * WIDTH; // stores the smallest tile count achieved by the currently best moveset
            int largestscore = 0; // stores the largest score achieved by the currently best moveset
            int moveset[4] = { 5,5,5,5 }; // for storing the best moveset
            bool specialNeeded = true; // flag for if the AI will need to use a special ability

            for (int w = 1; w < 4; w++) { // checks 4 moves into the future to find one moveset with the best outcome
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y < 4; y++) {
                        for (int z = 0; z < 4; z++) {

                            for (int i = 0; i < LENGTH; i++) {
                                for (int b = 0; b < WIDTH; b++) {
                                    grid[i][b] = tempgrid[i][b];
                                }

                            }
                            Shift(w); Shift(x); Shift(y); Shift(z);
                            if (OccupiedTiles() < smallesttilecount && largestscore < Score()) {
                                largestscore = Score();
                                smallesttilecount = OccupiedTiles();
                                moveset[0] = w; moveset[1] = x; moveset[2] = y; moveset[3] = z;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < LENGTH; i++) { // if the AI might be stuck
                for (int b = 0; b < WIDTH; b++) {
                    if (grid[i][b] != tempgrid[i][b]) {
                        grid[i][b] = tempgrid[i][b];
                        specialNeeded = false;
                    }

                }
            }

            for (int i = 99; i >= 0; i--) { // moves the new moveset into the database of last 100 movesets
                if (i != 0) {
                    for (int b = 0; b < 4; b++) {
                        lastmoves[i][b] = lastmoves[i - 1][b];
                    }
                }
                else if (i == 0) {
                    for (int b = 0; b < 4; b++) {
                        lastmoves[i][b] = moveset[b];
                    }
                }
            }

            bool last100isdifferent = true; // flag for checking if the last 100 movesets aren't identical
            for (int i = 0; i < 99 && last100isdifferent; i++) {
                for (int b = 0; b < 4; b++) {
                    if (lastmoves[i][b] != lastmoves[i + 1][b])
                        last100isdifferent = false;
                }
            }

            if (last100isdifferent) { //if the last 100 movesets are the same
                if (specialcount > 0) // use special ability if there any left
                    Special();
                else { // if no special abilities left
                    lostgame = 1;
                    DimPng(opacitydim);
                }
                
            }

            if (specialNeeded && specialcount > 0) // if the AI thinks it needs to use a special ability
                Special();
            else {
                for (int i = 0; i < 4; i++) { //applies the best moveset found
                    Shift(moveset[i]);
                }
            }
        }

    }
};

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(((LENGTH*2+1) * IMG_SIZE), ((WIDTH+1) * IMG_SIZE)), "2048 game", sf::Style::Close | sf::Style::Titlebar); // creates the window
    window.setFramerateLimit(60);

    sf::Image windowIcon; windowIcon.loadFromFile("images/windowIcon.png"); window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr()); // sets the windows icon

    bool optionselect = false; // for checking if an option has been selected from the menu
    int option = 0; // which option is selected
    int fontsize = 36; // font size used

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
   // /\ creates the menu text and applies the necessary parameters

   bool firstrender = true; // if the chosen game is rendered for the first time

   Player player1; Player player2; // player1 is on the left, player2 on the right
   AI ai; AI ai2; // ai is on the right, ai2 is on the left

   player2.PushInput((LENGTH + 1) * IMG_SIZE); ai.PushInput((LENGTH + 1) * IMG_SIZE); // telling player2 and ai how much their tiles will have to be pushed to the right when drawn
   player1.RenderPng();player2.RenderPng();ai.RenderPng();ai2.RenderPng(); // renders all the tile sprites for each class

    while (window.isOpen())
    {
        sf::Event press;
  
        if (optionselect) // if an option is chosen
        {
            if (option == 0) { // Player vs AI
                if (firstrender) {
                    firstrender = false;
                    player1.Reset(); ai.Reset();
                    player1.DimPng(255); ai.DimPng(255);
                    player1.NewTile(); player1.NewTile();
                    ai.NewTile(); ai.NewTile();
                }
                while (window.pollEvent(press))
                {
                    if (press.type == sf::Event::KeyPressed)
                    {
                             if (press.key.code == sf::Keyboard::A || press.key.code == sf::Keyboard::Left)  { player1.Shift(2); ai.Auto(); }
                        else if (press.key.code == sf::Keyboard::D || press.key.code == sf::Keyboard::Right) { player1.Shift(3); ai.Auto(); }
                        else if (press.key.code == sf::Keyboard::W || press.key.code == sf::Keyboard::Up)    { player1.Shift(0); ai.Auto(); }
                        else if (press.key.code == sf::Keyboard::S || press.key.code == sf::Keyboard::Down)  { player1.Shift(1); ai.Auto(); }
                        else if (press.key.code == sf::Keyboard::X) { player1.Special(); } // uses the special ability
                        else if (press.key.code == sf::Keyboard::R) { // Goes back to the menu
                            optionselect = false; option = 0; firstrender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (press.type == sf::Event::Closed)
                        window.close();
                }
                player1.Lose(); player1.Win(); ai.Win(); // checks if the player has won or lost and checks if the ai has won (the ai can check if it lost itself)
                window.clear(); // the current screen is wiped
                player1.Draw(window, font, fontsize); ai.Draw(window, font, fontsize); Divider(window, ai.ReturnLost()); // new screen is drawn
                window.display(); // new screen is displayed
            }
            else if (option == 1) {
                if (firstrender) {
                    firstrender = false;
                    player1.Reset(); player2.Reset();
                    player1.DimPng(255); player2.DimPng(255);
                    player1.NewTile(); player1.NewTile();
                    player2.NewTile(); player2.NewTile();
                }
                while (window.pollEvent(press))
                {
                    if (press.type == sf::Event::KeyPressed)
                    {
                             if (press.key.code == sf::Keyboard::A) { player1.Shift(2); }
                        else if (press.key.code == sf::Keyboard::D) { player1.Shift(3); }
                        else if (press.key.code == sf::Keyboard::W) { player1.Shift(0); }
                        else if (press.key.code == sf::Keyboard::S) { player1.Shift(1); }
                        else if (press.key.code == sf::Keyboard::Left) { player2.Shift(2); }
                        else if (press.key.code == sf::Keyboard::Right){ player2.Shift(3); }
                        else if (press.key.code == sf::Keyboard::Up)   { player2.Shift(0); }
                        else if (press.key.code == sf::Keyboard::Down) { player2.Shift(1); }
                        else if (press.key.code == sf::Keyboard::X)    { player1.Special();}
                        else if (press.key.code == sf::Keyboard::M)    { player2.Special(); }
                        else if (press.key.code == sf::Keyboard::R) {
                            optionselect = false; option = 0; firstrender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (press.type == sf::Event::Closed)
                        window.close();
                }
                player1.Lose(); player2.Lose(); // checks if any of the players have lost
                player1.Win(); player2.Win();   // checks if any of the players have won
                window.clear(); // the current screen is wiped
                player1.Draw(window, font, fontsize); player2.Draw(window, font, fontsize); Divider(window, player2.Lose()); // new screen is drawn
                window.display(); // new screen is displayed

            }
            else if (option == 2) {
                if (firstrender) {
                    firstrender = false;
                    ai.Reset(); ai2.Reset();
                    ai.DimPng(255); ai2.DimPng(255);
                    ai.NewTile(); ai.NewTile();
                    ai2.NewTile(); ai2.NewTile(); ai2.NewTile(); // an addition tile is added to ai2, so that it would solve the game in a diffrent way
                }
                while (window.pollEvent(press))
                {
                    if (press.type == sf::Event::KeyPressed)
                    {
                        if (press.key.code == sf::Keyboard::R) {
                            optionselect = false; option = 0; firstrender = 1;
                            menu[0].setFillColor(sf::Color::Red); menu[1].setFillColor(sf::Color::White); menu[2].setFillColor(sf::Color::White);
                        }
                    }
                    else if (press.type == sf::Event::Closed)
                        window.close();
                }
                ai.Auto(); ai2.Auto(); // lets the AI move
                ai.Win(); ai2.Win();   // checks if one of them has won

                window.clear(); // the current screen is wiped
                ai2.Draw(window, font, fontsize); ai.Draw(window, font, fontsize); Divider(window, ai.ReturnLost()); // new screen is drawn
                window.display(); // new screen is displayed
            }
            
        }
        else {
            
            window.clear();

            sf::Texture iblanko;
            iblanko.loadFromFile("images/blankopace.png"); //used for the menu screen tiles
            sf::Sprite sblanko;
            sblanko.setTexture(iblanko);

            for (int i = 0; i < (LENGTH*2+1); i++) { // puts the tiles all over the screen
                for (int b = 0; b < WIDTH+1; b++) {
                    sblanko.setPosition((i * IMG_SIZE), b * IMG_SIZE);
                    window.draw(sblanko);
                }
            }
            window.draw(menu[0]); window.draw(menu[1]); window.draw(menu[2]); // draws the menu text
            window.display();
            while (window.pollEvent(press))
            {
                if (press.type == sf::Event::KeyPressed)
                {
                    if ((press.key.code == sf::Keyboard::Down || press.key.code == sf::Keyboard::S) && option != 2) { // moves the selection down
                        option++;
                        for (int i = 0; i < 3; i++) {
                            if (i == option)
                                menu[i].setFillColor(sf::Color::Red);
                            else
                                menu[i].setFillColor(sf::Color::White);
                        }
                    }
                    else if ((press.key.code == sf::Keyboard::Up || press.key.code == sf::Keyboard::W) && option != 0) { // moves the selection up
                        option--;
                        for (int i = 0; i < 3; i++) {
                            if (i == option)
                                menu[i].setFillColor(sf::Color::Red);
                            else
                                menu[i].setFillColor(sf::Color::White);
                        }
                        
                    }
                    else if (press.key.code == sf::Keyboard::Enter) { // selects the highlighted option
                        optionselect = true;
                        if (option != 1 && option != 0 && option != 2)
                            option = 4;
                    }

                    window.clear();
                    for (int i = 0; i < (LENGTH * 2 + 1); i++) {
                        for (int b = 0; b < WIDTH+1; b++) {
                            sblanko.setPosition((i * IMG_SIZE), b * IMG_SIZE);
                            window.draw(sblanko);
                        }
                    }
                    window.draw(menu[0]); window.draw(menu[1]); window.draw(menu[2]);
                    window.display();
                    
                        
                }
                else if (press.type == sf::Event::Closed)
                    window.close();
            }
            
        }
    }
    return 0;
}
