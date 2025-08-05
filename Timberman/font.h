#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Font {
private :
	sf::Font font;
public:
	//���ؼ���
	sf::Font loadSTFANGSO() {
		if (!font.loadFromFile("resource/fonts/STFANGSO.TTF")) {
			std::cerr << "Failed to load font" << std::endl;
		}
		return font;
	 }
	 
	//����arialn.ttf
	void loadARIALN() {
		std::cerr << "Failed to load font" << std::endl;
	}
};
