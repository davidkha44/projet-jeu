#define ON_KEY_DBG(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;printf("%d \n",key);ins }
#define ON_KEY(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;ins}
#define CEIL(var,m) if(var >= m){ var = m}
#define FLOOR(var,m) if(var <= m){ var = m}
#define RANGE(var,min,max) if(var <= min){ var = min;} if (var >= max) {var = max;}
#define ATTRIBUTE(type,var) private : type _##var; public : type Get##var() {return _##var;} void Set##var(type value) {_##var = value;}
#define PRINTLN(str) std::cout << str << endl;
#define COLOR(c) sf::Color::c;
class MainFrame
{
    ATTRIBUTE(std::string,Name);
    public : 
    MainFrame(std::string n)
    {
        SetName(n);
    }

};