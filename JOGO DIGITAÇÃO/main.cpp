#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

struct Pencil{
  	sf::Font font;
  	sf::Text text;
 	 sf::RenderWindow& window;

	Pencil(sf::RenderWindow& window) : window { window }{
        if(!font.loadFromFile("CozetteVector.ttf")){
        	std::cout << "Nao deu bom\n";
        }

        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color){
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }
};


struct Pencilfinal{
  sf::Font font;
  sf::Text text;
  sf::RenderWindow& window;

    Pencilfinal(sf::RenderWindow& window) : window { window }{
        if(!font.loadFromFile("satan.ttf")){
        std::cout << "Nao deu bom\n";
        }
        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color){
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }
};


struct Bubble{
	static const int radius {10};
	bool alive{true};
	int x;
	int y;
	int letter;
	int speed;

    Bubble(int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed}{}

    void update(){
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window){
        sf::CircleShape bubble(Bubble::radius);
        bubble.setPosition(x, y);
        bubble.setFillColor(sf::Color::Yellow);
        window.draw(bubble);
        static Pencil pencil(window);
        pencil.write(std::string(1, letter), x+ 0.4 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Black);
    }
};



struct Board{
    std::vector<Bubble> bubbles;
    sf::RenderWindow& window;
    Pencil pencil;

    int acertou{0};
    int perdeu{0};

    Board(sf::RenderWindow& window) : window{window}, pencil{window} {
        bubbles.push_back(Bubble(100, 100, 'A', 1));
        bubbles.push_back(Bubble(200, 100, 'B', 2));
        bubbles.push_back(Bubble(300, 100, 'C', 3));
    }

    void update(){
        if(this->check_new_bubbles()){
            this->add_bubble();
        }else{
            for(Bubble& bubble : bubbles){
            bubble.update();
        }
            this->bubbles_perdidas();
            this->remove_dead_bubbles();
        }
    }

    void add_bubble(){
        int x = rand() % (this->window.getSize().x-2*Bubble::radius);
        int y = -2 * Bubble::radius;
        int velocidade = rand() % 7 + 3;
        char letrinha = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letrinha, velocidade));
    }

    void bubbles_perdidas(){
        for(Bubble& bubble : bubbles){
            if(bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y){
                if(bubble.alive){
                    bubble.alive = false;
                    this->perdeu++;
                }
            }
        }
    }

    void acertos(char letrinha){
        for(Bubble& bubble : bubbles){
            if(bubble.alive){
                if(bubble.letter == letrinha){
                    bubble.alive = false;
                    this->acertou++;
                    break;
                }
            }
        }
    }

    bool check_new_bubbles(){
        static const int newBubbleTimeout{30};
        static int newBubbleTimer{0};
        newBubbleTimer--;
        if(newBubbleTimer <= 0){
            newBubbleTimer = newBubbleTimeout;
            return true;
        }
        return false;
    }

    void remove_dead_bubbles(){
        std::vector<Bubble> vivas;
        for(Bubble& bubble : bubbles){
            if(bubble.alive){
                vivas.push_back(bubble);
            }
        }

        this->bubbles = vivas;
    }

    void draw(){
        pencil.write("ACERTOS: " + std::to_string(this->acertou) + " PERDIDAS: " + std::to_string(this->perdeu), 10, 10, 30, sf::Color::Green);
        pencil.write("Bolinhas na tela: " + std::to_string(this->bubbles.size()), 10, 40, 20, sf::Color::Black);
        for(Bubble& bubble : bubbles){
        	bubble.draw(window);
        }
    }
};


struct Game{
    sf::RenderWindow window;
    Board board;
    std::function<void()> onUpdate;

    Game() : window(sf::VideoMode(800, 600), "Bubbles"), board{window}{
            this->onUpdate = [&]() {
            this->jogar();
        };
        window.setFramerateLimit(30);
    }

    void process_events(){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
			else if(event.type == sf::Event::TextEntered){
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.acertos(code);
            }
        }
    }

    void jogar(){
        board.update();
        window.clear(sf::Color::Blue);
        board.draw();
        window.display();

        if (board.perdeu >= 5){
            this->onUpdate = [&](){
            this->game_over();
            };
        }
    }

    void game_over(){
        window.clear(sf::Color::Red);
        static Pencilfinal pencil(window);
        pencil.write("E MORREU", 100, 70, 250, sf::Color::Blue);
        window.display();
    }

    void main_loop(){
        while (window.isOpen()){
            process_events();
            this->onUpdate();
        }
    }
};

int main(){
    Game game;
	game.main_loop();

    return 0;
}