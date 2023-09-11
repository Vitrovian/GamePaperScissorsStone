#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;


//Вибір
enum class optionСhoice {
    rock,
    scissors,
    paper
};


//Вибір комп'ютера
optionСhoice computerСhoice() {
    int choice = rand() % 3 + 1;//випадкове число від 1 до 3
    if (choice == 1) {
        return optionСhoice::rock;
    }
    else if (choice == 2) {
        return optionСhoice::scissors;
    }
    else {
        return optionСhoice::paper;
    }
}



int main(){
    
    srand(time(NULL));
    
    RenderWindow win(VideoMode(1280, 720), L" Камінь, Ножиці, Папір");
    
    //Іконка програми
    Image icon;
    if (!icon.loadFromFile("Image/scissors2.png")) {
        return 1;
    }
    win.setIcon(64, 64, icon.getPixelsPtr());

    //Шрифт
    Font font;
    if (!font.loadFromFile("Font/DejaVuSans-Bold.ttf")) {
        cout << "Failed to load font" << "\n";
        return 2;
    }

    //Тло гри
    Texture TexturBack;
    TexturBack.loadFromFile("Image/back.jpg");
    RectangleShape GameTextur(Vector2f(1280, 720));
    GameTextur.setTexture(&TexturBack);
    GameTextur.setPosition(0,0);


    //Зображення ножиць
    Texture scissorsTexture;
    scissorsTexture.loadFromFile("Image/scissors.png");
    Sprite scissorsSprite(scissorsTexture);
    scissorsSprite.setPosition(300, 165);
    scissorsSprite.setScale( 0.7f, 0.7f);

    // Зображення Каменю
    Texture rockTexture;
    rockTexture.loadFromFile("Image/stone.png");
    Sprite rockSprite(rockTexture);
    rockSprite.setPosition(470, 165);
    rockSprite.setScale(0.7f, 0.7f);

    // Зображення Паперу
    Texture paperTexture;
    paperTexture.loadFromFile("Image/paper.png");
    Sprite paperSprite(paperTexture);
    paperSprite.setPosition(670, 165);
    paperSprite.setScale(0.7f, 0.7f);

    //Зображення ножиць комп
    Texture scissorsTextureComp;
    scissorsTextureComp.loadFromFile("Image/scissors.png");
    Sprite scissorsSpriteComp(scissorsTextureComp);
    scissorsSpriteComp.setPosition(500, 365);
    scissorsSpriteComp.setScale(0.7f, 0.7f);

    // Зображення Каменю комп
    Texture rockTextureComp;
    rockTextureComp.loadFromFile("Image/stone.png");
    Sprite rockSpriteComp(rockTextureComp);
    rockSpriteComp.setPosition(670, 365);
    rockSpriteComp.setScale(0.7f, 0.7f);

    // Зображення Паперу комп
    Texture paperTextureComp;
    paperTextureComp.loadFromFile("Image/paper.png");
    Sprite paperSpriteComp(paperTextureComp);
    paperSpriteComp.setPosition(870, 365);
    paperSpriteComp.setScale(0.7f, 0.7f);
    
    //Зображення скидування рахунку
    Texture resetTexture;
    resetTexture.loadFromFile("Image/reset.png");
    Sprite resetSprite(resetTexture);
    resetSprite.setPosition(1110, 130);

    //Заголовок
    Text title(L"Камінь, Ножиці, Папір ", font, 45);
    title.setFillColor(Color::White);
    title.setPosition(350, 40);

    // Панель гравця
    Text playerText(L"Ваш вибір: ", font, 30);
    playerText.setFillColor(Color::White);
    playerText.setPosition(50, 200);

    //Панель Комп'ютера
    Text computerText(L"Вибір комп'ютера: ", font, 30);
    computerText.setFillColor(Color::White);
    computerText.setPosition(50, 390);

    //Статистика гри
    Text statsText(L"Статистика гри ", font, 35);
    statsText.setFillColor(Color::White);
    statsText.setPosition(750, 520);

    //Результат 
    Text resultText(L"Результат  ", font, 35);
    resultText.setFillColor(Color::White);
    resultText.setPosition(110, 520);
    
    //Статистика
    Text playerScoreText("Player: 0", font, 24);
    Text computerScoreText("0 - Computer ", font, 24);
    Text statWinText(L"Виграші: 0 ",font, 24);
    Text statDrawText(L"Нічиї: 0 ", font, 24);
    Text statLossText(L"Програші: 0 ", font, 24);
    
    // Рахунок
    computerScoreText.setPosition(250, 600);
    computerScoreText.setFillColor(Color::White);
    playerScoreText.setPosition(50, 600);
    playerScoreText.setFillColor(Color::White);
    statWinText.setPosition(600, 600);
    statDrawText.setPosition(820, 600);
    statLossText.setPosition(1000, 600);
    int computerScore = 0;
    int playerScore = 0;
    int statWin = 0, statDraw = 0, statLoss = 0;


    // Змінна для зберігання вибору гравця
    optionСhoice playerChoice = optionСhoice::rock;

    while (win.isOpen())
    {
        Vector2i  mousePos = Mouse::getPosition(win);

        Event event;
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
                win.close();
            //Вибір мишкою 
            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    if(resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        resultText.setString(L"Рахунок Скинуто!");
                        resetSprite.setColor(Color(255, 0, 0));
                        playerScore = 0;
                        computerScore = 0;
                        statDraw = 0;
                        statLoss = 0;
                        statWin = 0;
                    }

                    if (scissorsSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = optionСhoice::scissors;
                        scissorsSprite.setColor(Color(255, 0, 0));
                        // Отримання вибору комп'ютера
                        optionСhoice computerChoice = computerСhoice();

                        // Логіка порівняння виборів гравця та комп'ютера
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"Нічия!");
                            scissorsSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == optionСhoice::scissors && computerChoice == optionСhoice::paper))
                        {
                            resultText.setString(L"Ви перемогли!");
                            playerScore++;
                            paperSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"Ви програли!");
                            computerScore++;
                            rockSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                    else if (rockSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = optionСhoice::rock;
                        rockSprite.setColor(Color(255, 0, 0));
                        // Отримання вибору комп'ютера
                        optionСhoice computerChoice = computerСhoice();

                        // Логіка порівняння виборів гравця та комп'ютера
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"Нічия!");
                            rockSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == optionСhoice::rock && computerChoice == optionСhoice::scissors))
                        {
                            resultText.setString(L"Ви перемогли!");
                            playerScore++;
                            scissorsSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"Ви програли!");
                            computerScore++;
                            paperSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                    else if (paperSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = optionСhoice::paper;
                        paperSprite.setColor(Color(255, 0, 0));

                        // Отримання вибору комп'ютера
                        optionСhoice computerChoice = computerСhoice();

                        // Логіка порівняння виборів гравця та комп'ютера
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"Нічия!");
                            paperSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == optionСhoice::paper && computerChoice == optionСhoice::rock))
                        {
                            resultText.setString(L"Ви перемогли!");
                            playerScore++;
                            rockSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"Ви програли!");
                            computerScore++;
                            scissorsSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                }
            }
            // Відпускаю ліву клавішу миші
            if (event.type == Event::MouseButtonReleased) {
                if (event.key.code == Mouse::Left) {
                    //повертаю колір текстурі
                    paperSpriteComp.setColor(Color::White);
                    scissorsSpriteComp.setColor(Color::White);
                    rockSpriteComp.setColor(Color::White);
                    resetSprite.setColor(Color::White);
                    if (scissorsSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        scissorsSprite.setColor(Color::White); 
                    }
                    else if (rockSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        rockSprite.setColor(Color::White);
                    }
                    else if (paperSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        paperSprite.setColor(Color::White);
                    }
                }
            }
                

        }
     
        //Відвалювання елементів
        win.clear(Color::Black);
        win.draw(GameTextur);

        win.draw(title);
        win.draw(playerText);
        win.draw(computerText);
        win.draw(statsText);
        win.draw(resultText);

        win.draw(scissorsSprite);
        win.draw(rockSprite);
        win.draw(paperSprite);

        win.draw(scissorsSpriteComp);
        win.draw(rockSpriteComp);
        win.draw(paperSpriteComp);


        win.draw(playerScoreText);
        win.draw(computerScoreText);
        win.draw(statWinText);
        win.draw(statDrawText);
        win.draw(statLossText);
        win.draw(resetSprite);

        playerScoreText.setString(L"Гравець  " +to_string(playerScore));
        computerScoreText.setString(to_string(computerScore)+ L"  Комп'ютер");
        statWinText.setString(L"Виграші " + to_string(statWin));
        statDrawText.setString(L"Нічиї " + to_string(statDraw));
        statLossText.setString(L"Програші " + to_string(statLoss));
        
        
        
        win.display();
        
    }

    return 0;
}