#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

using namespace std;

#include "Player.hpp"
#include "Connection.hpp"
/*===================================================================*/
	/**
	*	This is a main class of the game, it has pointer to CGameBoard on what the STurn are made. Also have pointer to class Connection
	*	that represent data connection between two computers and vector of Player class which play the game. This class has menu where the user make choice what mode will play. It has also configuration method 
	* 	where where the IP or port can be changed from default. Default ip is "localhost" and port is 6000. Also can be chane array size. After the game and the result will be shown on screen.
	*	Then you can change the mode of game.
	*/
class CGame 
 { 
 public:
 	CGame ( void );						//!< Default constructor create epmty CGame class with no connection and any players.
 	~CGame ( void );					//!< destructor delete the class.
 	/**
 	*	The Config method initalize the CGame class with the CGameBoard of selected size and push the players which are need to play chossen mode of game ( int Choice ).
 	*	If the net mode have been chosen the NetCongig method is called.
 		\param Choice - int value that represent choice in Menu method.
 		\return int value - 1 Terminal is too small, 2 Netconfig fail, 3 Cannot Start server or connect to server 
 	*/
 	int Config ( int Choice );
 	/**
 	*	Choosing method that alow user to make a choice in menus.
 		\param max - How many items in menu are.
 		\return int value that represent the made choice.
 	*/
 	int Choosing ( int max ) const ;
 	/**
 	*	Put the right player in the m_Players vector
 	*/
 	void SettingSingle ( void );
 	/**
 	*	The NetConfig method initalize the net setting as IP and port where the user want to conect.
 		\return bool value false - if the configuration fail , true - if configuration succed.
 	*/
 	bool NetConfig ( void );
 	/**
 	*	Menu method choose the mode which player want to play.
 		\return an integer, 0 - Singleplayer, 1 - LocalMultiplayer, 2 - NET (HOST), 3 - NET(CLIENT), 4 - END.
 	*/
 	int Menu ( void ) const ;
 	/**
 	*	It is the starting funcion of the choosen game mod.
 	*/
 	void Start ();
 	/**
 	*	It is whole cycle of the game. Where the method Play of each player is called until one win, or the board is full.
 	*/
 	void Game ();
 	/**
 	*	This method print the result of the game on the board.
 	*/
 	void Result ( void ) const ;

 private:
 	vector <Player *> m_Players; 			//!< vector of all players playing the game
 	CGameBoard * m_Board;					//!< pointer to the CGameBoard wher the Players are playing

 	unsigned int m_current;					//!< the player which is currnetly on the move
 	int m_Fd;								//!< it is the value of the open filedescriptor for data transfer
 	Connection * m_Connection;				//!< pointer to the class Connection which established the connection
 };

