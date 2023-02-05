#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum CardSuit
{
    Spades,Clubs,Hearts,Diamonds
};
enum CardValue
{
    Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King
};
sf::RenderWindow window;
sf::Font font;
sf::Texture CardFaceTexture;
sf::Texture CardBackTexture;
sf::Texture SpadesTexture;
sf::Texture ClubsTexture;
sf::Texture HeartsTexture;
sf::Texture DiamondsTexture;
sf::Texture TitleTexture;
sf::Texture TextBoxTexture;
sf::Image IconImage;
sf::SoundBuffer DrawCardSoundData;
sf::SoundBuffer ShuffleCardSoundData;
class Card
{
    public:
    int Suit = 0;
    int Value = 0;
    Card(int suit, int value)
    {
        Suit = suit;
        Value = value;
    }
    std::string GetSuitString()
    {
        switch(Suit)
        {
            case Spades:
            return "Spades";
            break;
            case Clubs:
            return "Clubs";
            break;
            case Hearts:
            return "Hearts";
            break;
            case Diamonds:
            return "Diamonds";
            break;
        }
    }
    std::string GetValueString()
    {
        switch(Value)
        {
            case Ace:
            return "Ace";
            break;
            case Two:
            return "Two";
            break;
            case Three:
            return "Three";
            break;
            case Four:
            return "Four";
            break;
            case Five:
            return "Five";
            break;
            case Six:
            return "Six";
            break;
            case Seven:
            return "Seven";
            break;
            case Eight:
            return "Eight";
            break;
            case Nine:
            return "Nine";
            break;
            case Ten:
            return "Ten";
            break;
            case Jack:
            return "Jack";
            break;
            case Queen:
            return "Queen";
            break;
            case King:
            return "King";
            break;
        }
    }
    std::string GetValueSymbolString()
    {
        switch(Value)
        {
            case Ace:
            return "A";
            break;
            case Two:
            return "2";
            break;
            case Three:
            return "3";
            break;
            case Four:
            return "4";
            break;
            case Five:
            return "5";
            break;
            case Six:
            return "6";
            break;
            case Seven:
            return "7";
            break;
            case Eight:
            return "8";
            break;
            case Nine:
            return "9";
            break;
            case Ten:
            return "10";
            break;
            case Jack:
            return "J";
            break;
            case Queen:
            return "Q";
            break;
            case King:
            return "K";
            break;
        }
    }
    void RenderCard(sf::Vector2f position)
    {
         sf::Sprite CardFaceSprite;
        CardFaceSprite.setTexture(CardFaceTexture);
        CardFaceSprite.setPosition(position);
        sf::Sprite SuitSprite;
        switch(Suit)
        {
            case Spades:
            SuitSprite.setTexture(SpadesTexture);
            break;
            case Clubs:
            SuitSprite.setTexture(ClubsTexture);
            break;
            case Hearts:
            SuitSprite.setTexture(HeartsTexture);
            break;
            case Diamonds:
            SuitSprite.setTexture(DiamondsTexture);
            break;
        }
        SuitSprite.setPosition(sf::Vector2f(position.x + 30.0f,position.y + 30.0f));

        sf::Text text;

        text.setFont(font);
        text.setCharacterSize(32);
        text.setStyle(sf::Text::Bold);
        text.setPosition(sf::Vector2f(position.x + 86.0f,position.y + 30.0f));
        if((Suit == Spades) || (Suit == Clubs))
        {
            text.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color::Red);
        }
        text.setString(GetValueSymbolString());
        window.draw(CardFaceSprite);
        window.draw(SuitSprite);
        window.draw(text);
    }
    void RenderFlippedCard(sf::Vector2f position)
    {
        sf::Sprite CardBackSprite;
        CardBackSprite.setTexture(CardBackTexture);
        CardBackSprite.setPosition(position);
        window.draw(CardBackSprite);
    }
};
class Deck
{
    public:
    std::vector<Card> Cards;
    Deck()
    {
        for(int s = 0;s <= 3;s++)
        {
            for(int v = 0;v <= 12;v++)
            {
                Cards.push_back(Card(s,v));
            }
        }
    }
    void Shuffle()
    {
        std::random_shuffle(std::begin(Cards), std::end(Cards));
    }
    Card DrawCard()
    {
        if(Cards.size() == 0)
        {
            //no cards to draw
            std::cout << "no cards in deck to draw" << std::endl;
        }
        //card drawn is last card in vector
        Card DrawnCard = Cards.back();
        Cards.pop_back();
        return DrawnCard;
    }
};
int GetBlackjackHandValue(std::vector<Card> hand)
{
    int HandValue = 0;
    for(int c = 0; c < hand.size();c++)
    {
        if(hand.at(c).Value > 0 && hand.at(c).Value < 10)
        {
            HandValue += (hand.at(c).Value + 1);
        }
        else if(hand.at(c).Value >= 10)
        {
            HandValue += 10;
        }
    }
    for(int c = 0; c < hand.size();c++)
    {
        if(hand.at(c).Value == 0)
        {
            if((HandValue + 11) <= 21)
            {
                HandValue += 11;
            }
            else HandValue += 1;
        }
    }
    return HandValue;
}
class RectButton
{
    private:
    bool PrevButtonState = false;
    public:
    sf::RectangleShape ButtonRect;
    sf::Vector2f Position;
    sf::Vector2f Size;
    sf::Text ButtonText;

    RectButton(sf::Vector2f size, sf::Vector2f position, sf::Text text)
    {
        Position = position;
        Size = size;
        ButtonRect.setPosition(Position);
        ButtonRect.setSize(Size);
        ButtonText = text;
        ButtonText.setOrigin(ButtonText.getLocalBounds().width / 2.0f,ButtonText.getLocalBounds().height / 2.0f);
        ButtonText.setPosition(sf::Vector2f(Position.x + (Size.x / 2.0f), Position.y + (Size.y / 2.0f)));
    }
    void DrawButton()
    {
        ButtonRect.setPosition(Position);
        ButtonRect.setSize(Size);
        ButtonText.setOrigin(ButtonText.getLocalBounds().width / 2.0f,ButtonText.getLocalBounds().height / 2.0f);
        ButtonText.setPosition(sf::Vector2f(Position.x + (Size.x / 2.0f), Position.y + (Size.y / 2.0f)));
        window.draw(ButtonRect);
        window.draw(ButtonText);
    }
    bool IsButtonPressed(bool allowrepeat = false)
    {
        ButtonRect.setPosition(Position);
        ButtonRect.setSize(Size);
        sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
        bool IsMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if(ButtonRect.getGlobalBounds().contains(MousePosition.x,MousePosition.y) && IsMousePressed)
        {
            if(allowrepeat)return true;
            if(!PrevButtonState && !allowrepeat)
            {
                PrevButtonState = true;
                return true;
            }
        }
        else 
        {
            PrevButtonState = false;
            return false;
        }
    }
};

int main()
{
    //try to open casino.data
    std::ifstream ChipDataFile("casino.data");
    int Chips = 0;
    if(ChipDataFile.good())//if casino.data exists read it
    {
        std::string filestring;
        std::getline(ChipDataFile,filestring);
        Chips = std::stoi(filestring);
        std::cout << "Chips Loaded: " << Chips << std::endl;
        ChipDataFile.close();
    }
    else //if no casino.data exists create one
    {
        std::cout << "Creating new casino.data" << std::endl;
        std::ofstream NewChipDataFile("casino.data");
        NewChipDataFile << "500";
        NewChipDataFile.close();
        Chips = 500;
    }
    if(ChipDataFile.is_open())ChipDataFile.close();

    font.loadFromFile(".\\resources\\OldSansBlack.ttf");
    DrawCardSoundData.loadFromFile(".\\resources\\drawcard.wav");
    ShuffleCardSoundData.loadFromFile(".\\resources\\shuffle.wav");
    CardFaceTexture.loadFromFile(".\\resources\\cardface_blank.png");
    CardFaceTexture.setSmooth(false);
    CardBackTexture.loadFromFile(".\\resources\\cardback.png");
    CardBackTexture.setSmooth(false);
    TextBoxTexture.loadFromFile(".\\resources\\blanktextbox.png");
    TextBoxTexture.setSmooth(false);
    SpadesTexture.loadFromFile(".\\resources\\suit_spades.png");
    SpadesTexture.setSmooth(false);
    ClubsTexture.loadFromFile(".\\resources\\suit_clubs.png");
    ClubsTexture.setSmooth(false);
    HeartsTexture.loadFromFile(".\\resources\\suit_hearts.png");
    HeartsTexture.setSmooth(false);
    DiamondsTexture.loadFromFile(".\\resources\\suit_diamonds.png");
    DiamondsTexture.setSmooth(false);
    TitleTexture.loadFromFile(".\\resources\\title.png");
    TitleTexture.setSmooth(false);
    IconImage.loadFromFile(".\\resources\\logo.png");
    sf::Sprite TitleSprite;
    TitleSprite.setTexture(TitleTexture);
    TitleSprite.setOrigin(sf::Vector2f(299.0f,149.0f));
    TitleSprite.setPosition(sf::Vector2f(400.0f,200.0f));
    
    // create the window
    window.create(sf::VideoMode(800, 600), "Rauch Casino");
    window.setIcon(57,57,IconImage.getPixelsPtr());

    sf::RectangleShape background(sf::Vector2f(760.f, 560.f));
    background.setPosition(20.0f,20.0f);
    background.setFillColor(sf::Color(53,101,77));
    background.setOutlineThickness(20.0f);
    background.setOutlineColor(sf::Color(150,111,58));

    sf::View view = window.getDefaultView();

    RectButton BlackjackButton(sf::Vector2f(150.0f,80.0f), sf::Vector2f(400.0f - 60.0f,360.0f), sf::Text("Blackjack", font));
    BlackjackButton.ButtonRect.setFillColor(sf::Color::Yellow);
    BlackjackButton.ButtonText.setFillColor(sf::Color::Black);
    bool Blackjack = false;
    bool BlackjackRestart = false;
    sf::Text ChipText;
    ChipText.setFont(font);
    ChipText.setFillColor(sf::Color::Black);
    ChipText.setCharacterSize(36);
    ChipText.setPosition(sf::Vector2f(50.0f, static_cast<float>(window.getSize().y) - 64.0f));
    ChipText.setString("Chips: " + std::to_string(Chips));

    sf::Sound DrawCardSound;
    DrawCardSound.setBuffer(DrawCardSoundData);
    sf::Sound ShuffleSound;
    ShuffleSound.setBuffer(ShuffleCardSoundData);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;

        // while there are pending events...
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                // window resized
                case sf::Event::Resized:
                    // set view to new window size
                    view.setSize({
                        static_cast<float>(event.size.width),
                        static_cast<float>(event.size.height)
                    });
                    view.setCenter(static_cast<float>(event.size.width) / 2.0f, static_cast<float>(event.size.height) / 2.0f);
                    window.setView(view);
                    background.setSize({
                        static_cast<float>(event.size.width) - 40.0f,
                        static_cast<float>(event.size.height) - 40.0f
                    });
                    TitleSprite.setPosition(sf::Vector2f(static_cast<float>(event.size.width) / 2.0f, 200.0f));
                    BlackjackButton.Position = (sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) - 60.0f, 360.0f));
                    ChipText.setPosition(sf::Vector2f(50.0f, static_cast<float>(event.size.height) - 64.0f));
                    break;
                // we don't process other types of events
                default:
                    break;
            }
        }
        if(BlackjackButton.IsButtonPressed() || BlackjackRestart)
        {
            Blackjack = true;
            BlackjackRestart = false;
            bool Stood = false;
            bool Hit = false;
            bool DealerStood = false;
            int Bet = 10;
            if(Chips > 10)Chips -= Bet;
            ChipText.setString("Chips: " + std::to_string(Chips));
            //0 = Game in progress, 1 = Win, 2 = Blackjack, 3 = Tie, 4 = Lose
            int GameOver = 0;
            Deck deck;
            deck.Shuffle();
            ShuffleSound.play();
            std::vector<Card> PlayerHand;
            std::vector<Card> DealerHand;
            
            sf::Sprite CardBackSprite;
            CardBackSprite.setTexture(CardBackTexture);
            sf::Sprite GameOverTextBox;
            GameOverTextBox.setTexture(TextBoxTexture);
            GameOverTextBox.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) / 2.0f) - 200.0f, 400.0f));
            sf::Text GameOverText;
            GameOverText.setFont(font);
            GameOverText.setFillColor(sf::Color::Black);
            GameOverText.setCharacterSize(32);
            GameOverText.setStyle(sf::Text::Bold);
            sf::Text DealerValueText;
            DealerValueText.setFont(font);
            DealerValueText.setFillColor(sf::Color::Black);
            DealerValueText.setCharacterSize(25);
            DealerValueText.setPosition(sf::Vector2f(320.0f, 380.0f));
            sf::Text PlayerValueText;
            PlayerValueText.setFont(font);
            PlayerValueText.setFillColor(sf::Color::Black);
            PlayerValueText.setCharacterSize(25);
            PlayerValueText.setPosition(sf::Vector2f(320.0f, 410.0f));
            RectButton HitButton(sf::Vector2f(100.0f,72.0f), sf::Vector2f(50.0f, static_cast<float>(window.getSize().y) - 200.0f), sf::Text("Hit", font, 36));
            HitButton.ButtonRect.setFillColor(sf::Color::Yellow);
            HitButton.ButtonText.setFillColor(sf::Color::Black);
            RectButton StayButton(sf::Vector2f(100.0f,72.0f), sf::Vector2f(50.0f, static_cast<float>(window.getSize().y) - 300.0f), sf::Text("Stay", font, 36));
            StayButton.ButtonRect.setFillColor(sf::Color::Yellow);
            StayButton.ButtonText.setFillColor(sf::Color::Black);
            RectButton RestartButton(sf::Vector2f(100.0f,72.0f), sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f - 150.0f, 500.0f), sf::Text("Restart", font, 28));
            RestartButton.ButtonRect.setFillColor(sf::Color::Yellow);
            RestartButton.ButtonText.setFillColor(sf::Color::Black);
            RectButton MenuButton(sf::Vector2f(100.0f,72.0f), sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f + 50.0f, 500.0f), sf::Text("Menu", font, 28));
            MenuButton.ButtonRect.setFillColor(sf::Color::Yellow);
            MenuButton.ButtonText.setFillColor(sf::Color::Black);

            DealerHand.push_back(deck.DrawCard());
            DealerHand.push_back(deck.DrawCard());     
            PlayerHand.push_back(deck.DrawCard());
            PlayerHand.push_back(deck.DrawCard());
        
            while(Blackjack && window.isOpen())
            {
                sf::Event event;
                
                // while there are pending events...
                while (window.pollEvent(event))
                {
                    // check the type of the event...
                    switch (event.type)
                    {
                        // window closed
                        case sf::Event::Closed:
                            window.close();
                            break;
                        // key pressed
                        case sf::Event::KeyPressed:
                            if (event.key.code == sf::Keyboard::H)
                            {
                                if(deck.Cards.size() > 0 && !Stood && (GameOver == 0))
                                {
                                    PlayerHand.push_back(deck.DrawCard());
                                    DrawCardSound.play();
                                    Hit = true;
                                }
                            }
                            if (event.key.code == sf::Keyboard::S)
                            {
                                Stood = true;
                            }
                            if (event.key.code == sf::Keyboard::Escape)
                            {
                                Blackjack = false;
                            }
                            if (event.key.code == sf::Keyboard::R)
                            {
                                Blackjack = false;
                                BlackjackRestart = true;
                            }
                            break;
                        // window resized
                        case sf::Event::Resized:
                            // set view to new window size
                            view.setSize({
                                static_cast<float>(event.size.width),
                                static_cast<float>(event.size.height)
                            });
                            view.setCenter(static_cast<float>(event.size.width) / 2.0f, static_cast<float>(event.size.height) / 2.0f);
                            window.setView(view);
                            background.setSize({
                                static_cast<float>(event.size.width) - 40.0f,
                                static_cast<float>(event.size.height) - 40.0f
                            });
                            TitleSprite.setPosition(sf::Vector2f(static_cast<float>(event.size.width) / 2.0f, 200.0f));
                            BlackjackButton.Position = (sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) - 60.0f, 360.0f));
                            GameOverTextBox.setPosition(sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) - 200.0f, 400.0f));
                            GameOverText.setPosition(sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) - (GameOverText.getLocalBounds().width / 2.0f), 432.0f));
                            RestartButton.Position = (sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) - 150.0f, 500.0f));
                            MenuButton.Position = (sf::Vector2f((static_cast<float>(event.size.width) / 2.0f) + 50.0f, 500.0f));
                            ChipText.setPosition(sf::Vector2f(50.0f, static_cast<float>(event.size.height) - 64.0f));
                            HitButton.Position = sf::Vector2f(50.0f, static_cast<float>(window.getSize().y) - 200.0f);
                            StayButton.Position = sf::Vector2f(50.0f, static_cast<float>(window.getSize().y) - 300.0f);
                            break;
                        // we don't process other types of events
                        default:
                            break;
                    }
                }
                if(HitButton.IsButtonPressed())
                {
                    if(deck.Cards.size() > 0 && !Stood && (GameOver == 0))
                        {
                            PlayerHand.push_back(deck.DrawCard());
                            DrawCardSound.play();
                            Hit = true;
                        }
                }
                if(StayButton.IsButtonPressed())
                {
                    Stood = true;
                }
                if(GameOver == 0)
                {
                    if(GetBlackjackHandValue(DealerHand) == 21 && !Stood && !Hit)
                    {
                        if(GetBlackjackHandValue(PlayerHand) == 21)
                        {
                            std::cout << "Blackjack tie" << std::endl;
                            GameOver = 3;
                            Chips += Bet;
                            ChipText.setString("Chips: " + std::to_string(Chips));
                        }
                        else
                        {
                            std::cout << "Dealer Blackjack win" << std::endl;
                            GameOver = 4;
                        }
                    }
                    if(GetBlackjackHandValue(PlayerHand) == 21 && !Stood && !Hit)
                    {
                        std::cout << "Player Blackjack win" << std::endl;
                        GameOver = 2;
                        Chips += (Bet * 2.5);
                        ChipText.setString("Chips: " + std::to_string(Chips));
                    }
                    if(Hit)
                    {
                        if(GetBlackjackHandValue(PlayerHand) > 21)
                        {
                            std::cout << "Player bust, Dealer win" << std::endl;
                            GameOver = 4;
                        }
                    }
                    if(Stood)
                    {
                        if(DealerStood)
                        {
                            if(GetBlackjackHandValue(DealerHand) > GetBlackjackHandValue(PlayerHand))
                            {
                                std::cout << "Dealer win, stood on higher value" << std::endl;
                                GameOver = 4;
                            }
                            if(GetBlackjackHandValue(DealerHand) < GetBlackjackHandValue(PlayerHand))
                            {
                                std::cout << "Player win, stood on higher value" << std::endl;
                                GameOver = 1;
                                Chips += (Bet * 2);
                                ChipText.setString("Chips: " + std::to_string(Chips));
                            }
                            if(GetBlackjackHandValue(DealerHand) == GetBlackjackHandValue(PlayerHand))
                            {
                                std::cout << "Tie, stood on same value" << std::endl;
                                GameOver = 3;
                                Chips += Bet;
                                ChipText.setString("Chips: " + std::to_string(Chips));
                            }
                        }
                        if(GetBlackjackHandValue(DealerHand) < 17)
                        {
                            DealerHand.push_back(deck.DrawCard());
                            DrawCardSound.play();
                        }
                        if(GetBlackjackHandValue(DealerHand) > 21)
                        {
                            std::cout << "Player win, Dealer bust" << std::endl;
                            GameOver = 1;
                            Chips += (Bet * 2);
                            ChipText.setString("Chips: " + std::to_string(Chips));
                        }
                        if(GetBlackjackHandValue(DealerHand) >= 17)
                        {
                            DealerStood = true;
                        }
                    }
                }
                // clear the window with white color
                window.clear(sf::Color::White);

                window.draw(background);
                CardBackSprite.setPosition(sf::Vector2f(40.0f, 40.0f));
                for(int c = 0;c < deck.Cards.size();c++)
                {
                    CardBackSprite.move(sf::Vector2f(0.3f,-0.15f));
                    window.draw(CardBackSprite);
                }
                for(int c = 0;c < DealerHand.size();c++)
                {
                    if(c > 0 || Stood || (GameOver != 0))DealerHand.at(c).RenderCard(sf::Vector2f(320.0f + (150.0f * c), 40.0f));
                    else DealerHand.at(c).RenderFlippedCard(sf::Vector2f(320.0f + (150.0f * c), 40.0f));
                }
                int DealerHandValue;
                if(Stood || (GameOver != 0))DealerHandValue = GetBlackjackHandValue(DealerHand);
                else
                {
                    std::vector<Card> DealerHandNoFlip;
                    DealerHandNoFlip.push_back(DealerHand.at(1));
                    DealerHandValue = GetBlackjackHandValue(DealerHandNoFlip);
                }
                DealerValueText.setString("Dealer's Card Value: " + std::to_string(DealerHandValue));
                window.draw(DealerValueText);
                for(int c = 0;c < PlayerHand.size();c++)
                {
                    PlayerHand.at(c).RenderCard(sf::Vector2f(320.0f + (150.0f * c), 440.0f));
                }
                PlayerValueText.setString("Player's Card Value: " + std::to_string(GetBlackjackHandValue(PlayerHand)));
                window.draw(PlayerValueText);
                switch(GameOver)
                {
                    case 0:
                    break;
                    case 1:
                    GameOverText.setString("You Win!");
                    GameOverText.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) / 2.0f) - (GameOverText.getLocalBounds().width / 2.0f), 432.0f));
                    break;
                    case 2:
                    GameOverText.setString("Blackjack!");
                    GameOverText.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) / 2.0f) - (GameOverText.getLocalBounds().width / 2.0f), 432.0f));
                    break;
                    case 3:
                    GameOverText.setString("Tie");
                    GameOverText.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) / 2.0f) - (GameOverText.getLocalBounds().width / 2.0f), 432.0f));
                    break;
                    case 4:
                    GameOverText.setString("You Lose");
                    GameOverText.setPosition(sf::Vector2f((static_cast<float>(window.getSize().x) / 2.0f) - (GameOverText.getLocalBounds().width / 2.0f), 432.0f));
                    break;

                }
                if(GameOver != 0)
                {
                    if(RestartButton.IsButtonPressed())
                    {
                        Blackjack = false;
                        BlackjackRestart = true;
                    }
                    if(MenuButton.IsButtonPressed())
                    {
                        Blackjack = false;
                    }
                    window.draw(GameOverTextBox);
                    window.draw(GameOverText);
                    RestartButton.DrawButton();
                    MenuButton.DrawButton();
                }
                HitButton.DrawButton();
                StayButton.DrawButton();
                window.draw(ChipText);

                // end the current frame
                window.display();
            }
        }
        // clear the window with white color
        window.clear(sf::Color::White);

        window.draw(background);
        window.draw(TitleSprite);
        BlackjackButton.DrawButton();
        window.draw(ChipText);


        // end the current frame
        window.display();
    }
    std::cout << "Saving casino.data" << std::endl;
    std::ofstream NewChipDataFile("casino.data");
    NewChipDataFile << Chips;
    NewChipDataFile.close();
    return 0;
}