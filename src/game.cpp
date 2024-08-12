#include <game.hpp>

Game ::Game()
{
    initvariables();
    initwindows();
    initenemies();
    initfonts();
    inittext();
}

void Game::update()
{
    pollevents();
 
    if (endgame == false)
    {

        updatemousepositions();

        updatetext();

        updateenemies();
    }
    if (health <= 0)
    {
        endgame = true;
    }
}

void Game::render()
{
    m_window->clear();

    // draw game objects
    renderenemies(*m_window);

    rendertext(*m_window);

    m_window->display();
}

void Game::pollevents()
{

    // event polling

    while (m_window->pollEvent(event))
    {

        switch (event.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_window->close();
                break;
            }
        }
    }
}


void Game ::updatemousepositions()
{
    mouseposwindow = sf::Mouse::getPosition(*m_window);
    mouseposview = m_window->mapPixelToCoords(mouseposwindow);
}



void Game ::updatetext()
{

    std::stringstream ss;

    ss << "Points: " << points << "\n"
       << "Health: " << health << "\n";
    uitext.setString(ss.str());
}


void Game::updateenemies()
{
    // updating the timer for enemy spawning
    if (enemies.size() < maxenemies)
    {
        if (EnemySpawnTimer >= EnemySpawnTimerMax)
        {
            // spawn the enemy and reset the timer
            spawnenemies();
            EnemySpawnTimer = 0.f;
        }
        else
        {
            EnemySpawnTimer += 1.f;
        }
    }

    // check if clicked upon

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (mouseheld == false)
        {
            mouseheld = true;

            for (size_t i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].getGlobalBounds().contains(mouseposview))
                {
                    //points
                    if(enemies[i].getFillColor()== sf::Color::Magenta){
                        points +=10;
                    }
                    else if(enemies[i].getFillColor()== sf::Color::Blue){
                        points +=7;
                    }
                    else if(enemies[i].getFillColor()== sf::Color::Cyan){
                        points +=5;
                    }
                    else if(enemies[i].getFillColor()== sf::Color::Red){
                        points +=3;
                    }
                    else if(enemies[i].getFillColor()== sf::Color::Green){
                        points +=1;
                    }

                    std::cout<<"points:"<<points<<"\n";
                    enemies.erase(enemies.begin() + i);
                    break;
                }
            }
        }
    }
    else
    {
        mouseheld = false;
    }


    // moving and updating the enemies

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].move(0.f, 2.f);

        if (enemies[i].getPosition().y > m_window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health -= 1;
            std::cout<<"Health: "<<health<<"\n";
        }
    }
}



void Game::spawnenemies()
{
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(m_window->getSize().x - enemy.getSize().x)),
        0.f);

    // randomise enemy

    int type = rand() % 5;

    switch (type)
    {

    case 0:
        enemy.setSize(sf::Vector2f(30.f, 30.f));
        enemy.setFillColor(sf::Color::Magenta);
        break;

    case 1:
        enemy.setSize(sf::Vector2f(50.f, 50.f));
        enemy.setFillColor(sf::Color::Blue);
        break;

    case 2:
        enemy.setSize(sf::Vector2f(70.f, 70.f));
        enemy.setFillColor(sf::Color::Cyan);
        break;

    case 3:
        enemy.setSize(sf::Vector2f(85.f, 85.f));
        enemy.setFillColor(sf::Color::Red);
        break;

    case 4:
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Green);
        break;

    default:
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    enemies.push_back(enemy);
}

void Game::renderenemies(sf::RenderTarget &target)
{
    for (auto &e : enemies)
    {
        target.draw(e);
    }
}



void ::Game ::rendertext(sf::RenderTarget &target)
{
    target.draw(uitext);
}

// Accessors
const bool Game ::running() const
{
    return m_window->isOpen();
}
const bool Game ::getendgame() const
{
    return endgame;
}

void Game ::initvariables()
{
    m_window = nullptr;

    // game logic
    points = 0;
    EnemySpawnTimerMax = 100.f;
    EnemySpawnTimer = EnemySpawnTimerMax;
    maxenemies = 5;
    mouseheld = false;
    endgame = false;
    health = 10;
    font_size = 20;
}

void Game ::initwindows()
{
    videomode.width = 800;
    videomode.height = 600;
    m_window = new sf::RenderWindow(videomode, "My window", sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(144);
}

void Game ::initenemies()
{
    enemy.setOrigin(sf::Vector2f(10.f, 10.f));
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    // enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Green);
    // enemy.setOutlineThickness(1.f);
    enemy.setOutlineColor(sf::Color::Red);
}

void Game ::initfonts()
{
    if (!font.loadFromFile("./Fonts/Dosis/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::INITFONTS::Failed lo load fonts" << std::endl;
    }
}

void ::Game ::inittext()
{
    uitext.setFont(font);
    uitext.setCharacterSize(font_size);
    uitext.setFillColor(sf::Color::White);
    uitext.setString("NONE");
}

Game::~Game()
{
    delete m_window;
}