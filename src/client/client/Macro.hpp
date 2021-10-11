#define ON_KEY_DBG(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;printf("%d \n",key);ins }
#define ON_KEY(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;ins}
#define ON_MOUSE_LEFT(ins) {if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { sf::Vector2i MousePos = sf::Mouse::getPosition();ins}}
#define ON_MOUSE_RIGHT(ins) {if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { sf::Vector2i MousePos = sf::Mouse::getPosition();ins}}
#define CEIL(var,m) if(var >= m){ var = m}
#define FLOOR(var,m) if(var <= m){ var = m}
#define RANGE(var,min,max) if(var <= min){ var = min;} if (var >= max) {var = max;}
#define ATTRIBUTE(type,var) private : type _##var; public : type var() {return _##var;} void var(type value) {_##var = value;}
#define STATIC_ATTRIBUTE(type,var) private : static type _##var; public : static type var() {return _##var;} static void var(type value) {_##var = value;}
#define PRINTLN(str) std::cout << str << endl;
#define STATIC(vardecl) public : static inline vardecl;
#define COLOR(c) sf::Color::c;