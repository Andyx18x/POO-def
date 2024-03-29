#include "GameOver.h"
#include <fstream>
#include "Menu.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Nivel1.h"

using namespace std;

GameOver::GameOver() {
	m_font.loadFromFile("fuente_menu.ttf");
	
	
	
	game_overtxt.setFont(m_font);
	game_overtxt.setCharacterSize(46);
	game_overtxt.setFillColor(Color::White);
	game_overtxt.setPosition(200.f,100.f);

	sonido_perder.loadFromFile("lose.wav");
	perder.setBuffer(sonido_perder);
	
	scoretxt.setFont(m_font);
	scoretxt.setCharacterSize(24);
	scoretxt.setFillColor(Color::White);
	scoretxt.setPosition(300.f,250.f);
	
	int Var_y = 500;
	option.resize(Max_Items_Menu);
	
	for(int i=0;i<Max_Items_Menu;i++){
		option[i].setFont(m_font);
		option[i].setCharacterSize(16);
		option[i].setPosition(280,Var_y);
		Var_y +=40;
	}
	
	option[0].setFillColor(Color::Green);
	option[1].setFillColor(Color::White);
	
	option[0].setString("<Volver a Jugar>");
	option[1].setString("<Volver al Menu>");
	
	
	ifstream archi("puntos.txt");
	archi>>m_score;
	archi.close();
	
	
	game_overtxt.setString("GAME OVER");
	perder.play();
	scoretxt.setString("SCORE: "+to_string(m_score));
	
	
	selectItem = 0;

}


void GameOver::Update(Game &g) {
	
	
	
}

void GameOver::Draw(RenderWindow &w){
	w.clear({0,0,0});
	w.draw(game_overtxt);
	w.draw(scoretxt);
	
	for(auto &x : option){
		w.draw(x);
	}

}

void GameOver::ProcesarEventos(Game &g, Event &ev){
	if (option[selectItem].getString() == option[0].getString() and ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return) {  /// Procesador de eventos para ir a menu y/o jugar nuevamente
		g.SetScene(new Nivel1());
	}
	
	
	if (option[selectItem].getString() == option[1].getString()and ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return) {
		g.SetScene(new Menu());
	}
	
	
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Up){
		MoveUp();
	}
	
	
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Down){
		MoveDown();
	}
}


void GameOver::MoveUp(){
	if(selectItem - 1 >= 0 ){
		option[selectItem].setFillColor(Color::White);
		selectItem--;										/// Nos permite pintar los text del vector option cuando usamos las flechitas
		option[selectItem].setFillColor(Color::Green);
	}
}


void GameOver::MoveDown(){
	if(selectItem + 1 < Max_Items_Menu ){
		option[selectItem].setFillColor(Color::White);
		selectItem++;									/// Nos permite pintar los text del vector option cuando usamos las flechitas
		option[selectItem].setFillColor(Color::Green);
	}
}

