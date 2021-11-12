#include <vector>
#include <iostream>
#include <fstream>

#define ON_KEY_DBG(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;printf("%d \n",key);ins }
#define ON_KEY(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::_key)) { char key = sf::Keyboard::_key + 65;ins}
#define ON_KEY_ENUM(_key,ins) if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_key))) {ins}
#define ON_MOUSE_LEFT(ins) {if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) { sf::Vector2i MousePos = sf::Mouse::getPosition(*MainFrame::Window);ins}}
#define ON_MOUSE_RIGHT(ins) {if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { sf::Vector2i MousePos = sf::Mouse::getPosition(*MainFrame::Window);ins}}
#define CEIL(var,m) if(var >= m){ var = m}
#define FLOOR(var,m) if(var <= m){ var = m}
#define RANGE(var,min,max) if(var <= min){ var = min;} if (var >= max) {var = max;}
#define IN_RANGE(var,min,max) if(var <= min || var >= max) {}
#define ATTRIBUTE(type,var) private : type _##var; public : type var() {return _##var;} void var(type value) {_##var = value;}
#define ATTRIBUTE_EVENT(type,var) private : type _##var; public : type var() {return _##var;} void Event_##var(); void var(type value) {_##var = value;Event_##var();}
#define STATIC_ATTRIBUTE(type,var) private : static type _##var; public : static type var() {return _##var;} static void var(type value) {_##var = value;}
#define STATIC_EVENT(type,var) private : static inline type _##var; public : static type var() {return _##var;} static void Event_##var(); static void var(type value) {_##var = value;Event_##var();}
#define PRINTLN(str) std::cout << str << std::endl;
#define STATIC(vardecl) public : static inline vardecl;
#define COLOR(c) sf::Color::c;
#define BG_TILE(x,y) Manager::GetMgrByName("BG_MGR")->GetByName("TILE_"+std::to_string(x)+"_"+std::to_string(y))->front()
#define FETCH_FROM_MGR(mgr,item) Manager::GetMgrByName(mgr)->GetByName(item)
#define GET_SET(c,type,var) type c::var() {return _##var;} void c::var(type value) {_##var = value;}
#define PARSE_CSV_LINES(path,comment,ins)       std::ifstream file(path); \
                                                for( std::string line; getline( file, line ); ) {if(line.find(comment) == std::string::npos) { \
                                                std::string str = line;std::string separator(",");size_t pos_start = 0, pos_end, delim_len = separator.length();std::string token;std::vector<std::string> items;\
                                                while ((pos_end = str.find (separator, pos_start)) != std::string::npos) { token = str.substr (pos_start, pos_end - pos_start);pos_start = pos_end + delim_len;items.push_back (token);}\
                                                items.push_back (str.substr (pos_start));\
                                                \
                                                \
                                                \
                                                \
                                                \
                                                     ins} }\

#define STRING_SWITCH(S) char *_S = (char*)S.c_str(); if (0)
#define CASE(S) } else if (strcmp(_S, S) == 0) {switch(1) { case 1
#define BREAK }
#define DEFAULT } else {switch(1) { case 1
#define DESERIALIZE(x) template std::vector<x*> render::FileHandler::DeserializeTable<x>(std::string path, std::string format);





 



