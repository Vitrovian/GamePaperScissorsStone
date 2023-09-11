#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;


//����
enum class option�hoice {
    rock,
    scissors,
    paper
};


//���� ����'�����
option�hoice computer�hoice() {
    int choice = rand() % 3 + 1;//��������� ����� �� 1 �� 3
    if (choice == 1) {
        return option�hoice::rock;
    }
    else if (choice == 2) {
        return option�hoice::scissors;
    }
    else {
        return option�hoice::paper;
    }
}



int main(){
    
    srand(time(NULL));
    
    RenderWindow win(VideoMode(1280, 720), L" �����, ������, ����");
    
    //������ ��������
    Image icon;
    if (!icon.loadFromFile("Image/scissors2.png")) {
        return 1;
    }
    win.setIcon(64, 64, icon.getPixelsPtr());

    //�����
    Font font;
    if (!font.loadFromFile("Font/DejaVuSans-Bold.ttf")) {
        cout << "Failed to load font" << "\n";
        return 2;
    }

    //��� ���
    Texture TexturBack;
    TexturBack.loadFromFile("Image/back.jpg");
    RectangleShape GameTextur(Vector2f(1280, 720));
    GameTextur.setTexture(&TexturBack);
    GameTextur.setPosition(0,0);


    //���������� ������
    Texture scissorsTexture;
    scissorsTexture.loadFromFile("Image/scissors.png");
    Sprite scissorsSprite(scissorsTexture);
    scissorsSprite.setPosition(300, 165);
    scissorsSprite.setScale( 0.7f, 0.7f);

    // ���������� ������
    Texture rockTexture;
    rockTexture.loadFromFile("Image/stone.png");
    Sprite rockSprite(rockTexture);
    rockSprite.setPosition(470, 165);
    rockSprite.setScale(0.7f, 0.7f);

    // ���������� ������
    Texture paperTexture;
    paperTexture.loadFromFile("Image/paper.png");
    Sprite paperSprite(paperTexture);
    paperSprite.setPosition(670, 165);
    paperSprite.setScale(0.7f, 0.7f);

    //���������� ������ ����
    Texture scissorsTextureComp;
    scissorsTextureComp.loadFromFile("Image/scissors.png");
    Sprite scissorsSpriteComp(scissorsTextureComp);
    scissorsSpriteComp.setPosition(500, 365);
    scissorsSpriteComp.setScale(0.7f, 0.7f);

    // ���������� ������ ����
    Texture rockTextureComp;
    rockTextureComp.loadFromFile("Image/stone.png");
    Sprite rockSpriteComp(rockTextureComp);
    rockSpriteComp.setPosition(670, 365);
    rockSpriteComp.setScale(0.7f, 0.7f);

    // ���������� ������ ����
    Texture paperTextureComp;
    paperTextureComp.loadFromFile("Image/paper.png");
    Sprite paperSpriteComp(paperTextureComp);
    paperSpriteComp.setPosition(870, 365);
    paperSpriteComp.setScale(0.7f, 0.7f);
    
    //���������� ���������� �������
    Texture resetTexture;
    resetTexture.loadFromFile("Image/reset.png");
    Sprite resetSprite(resetTexture);
    resetSprite.setPosition(1110, 130);

    //���������
    Text title(L"�����, ������, ���� ", font, 45);
    title.setFillColor(Color::White);
    title.setPosition(350, 40);

    // ������ ������
    Text playerText(L"��� ����: ", font, 30);
    playerText.setFillColor(Color::White);
    playerText.setPosition(50, 200);

    //������ ����'�����
    Text computerText(L"���� ����'�����: ", font, 30);
    computerText.setFillColor(Color::White);
    computerText.setPosition(50, 390);

    //���������� ���
    Text statsText(L"���������� ��� ", font, 35);
    statsText.setFillColor(Color::White);
    statsText.setPosition(750, 520);

    //��������� 
    Text resultText(L"���������  ", font, 35);
    resultText.setFillColor(Color::White);
    resultText.setPosition(110, 520);
    
    //����������
    Text playerScoreText("Player: 0", font, 24);
    Text computerScoreText("0 - Computer ", font, 24);
    Text statWinText(L"�������: 0 ",font, 24);
    Text statDrawText(L"ͳ��: 0 ", font, 24);
    Text statLossText(L"��������: 0 ", font, 24);
    
    // �������
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


    // ����� ��� ��������� ������ ������
    option�hoice playerChoice = option�hoice::rock;

    while (win.isOpen())
    {
        Vector2i  mousePos = Mouse::getPosition(win);

        Event event;
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
                win.close();
            //���� ������ 
            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    if(resetSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        resultText.setString(L"������� �������!");
                        resetSprite.setColor(Color(255, 0, 0));
                        playerScore = 0;
                        computerScore = 0;
                        statDraw = 0;
                        statLoss = 0;
                        statWin = 0;
                    }

                    if (scissorsSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = option�hoice::scissors;
                        scissorsSprite.setColor(Color(255, 0, 0));
                        // ��������� ������ ����'�����
                        option�hoice computerChoice = computer�hoice();

                        // ����� ��������� ������ ������ �� ����'�����
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"ͳ���!");
                            scissorsSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == option�hoice::scissors && computerChoice == option�hoice::paper))
                        {
                            resultText.setString(L"�� ���������!");
                            playerScore++;
                            paperSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"�� ��������!");
                            computerScore++;
                            rockSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                    else if (rockSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = option�hoice::rock;
                        rockSprite.setColor(Color(255, 0, 0));
                        // ��������� ������ ����'�����
                        option�hoice computerChoice = computer�hoice();

                        // ����� ��������� ������ ������ �� ����'�����
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"ͳ���!");
                            rockSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == option�hoice::rock && computerChoice == option�hoice::scissors))
                        {
                            resultText.setString(L"�� ���������!");
                            playerScore++;
                            scissorsSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"�� ��������!");
                            computerScore++;
                            paperSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                    else if (paperSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        playerChoice = option�hoice::paper;
                        paperSprite.setColor(Color(255, 0, 0));

                        // ��������� ������ ����'�����
                        option�hoice computerChoice = computer�hoice();

                        // ����� ��������� ������ ������ �� ����'�����
                        if (playerChoice == computerChoice)
                        {
                            resultText.setString(L"ͳ���!");
                            paperSpriteComp.setColor(Color::Red);
                            statDraw++;
                        }
                        else if ((playerChoice == option�hoice::paper && computerChoice == option�hoice::rock))
                        {
                            resultText.setString(L"�� ���������!");
                            playerScore++;
                            rockSpriteComp.setColor(Color::Red);
                            statWin++;
                        }
                        else
                        {
                            resultText.setString(L"�� ��������!");
                            computerScore++;
                            scissorsSpriteComp.setColor(Color::Red);
                            statLoss++;
                        }
                    }
                }
            }
            // ³������� ��� ������ ����
            if (event.type == Event::MouseButtonReleased) {
                if (event.key.code == Mouse::Left) {
                    //�������� ���� �������
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
     
        //³���������� ��������
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

        playerScoreText.setString(L"�������  " +to_string(playerScore));
        computerScoreText.setString(to_string(computerScore)+ L"  ����'����");
        statWinText.setString(L"������� " + to_string(statWin));
        statDrawText.setString(L"ͳ�� " + to_string(statDraw));
        statLossText.setString(L"�������� " + to_string(statLoss));
        
        
        
        win.display();
        
    }

    return 0;
}