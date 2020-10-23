#include <cstdio>
#include <cstdlib>
 using namespace std;
#include "CGameBoard.hpp"
/*===================================================================*/
	/**
	*	This is an abstract class that represent player playing the game. The derive class are Human, AI, LOCAL, REMOTE and MINIMAX
	*	All players have method Play, thesa represets their turns in CGameBoard. All method Play return a STurn that can be played in CGameBoard
	*	Each player has a pointer to CGameBoard where he play and a int value that represent thier mark in the game array.
	*/
class Player 
 {
 public:
 	/**
 	*	Constructor of Player class 
 		\param Board - is a pointer to CGameBoard where the players plays their turn.
 	*/
 	Player ( CGameBoard * Board ); 
 	virtual ~Player ( void );	//!< Virtual destructor of class Player
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/
 	virtual STurn Play ( int FD = -1 ) = 0;
 protected:
 	CGameBoard * m_Board;	//!< A pointer to the CGameBoard 
 	static int i;			//!< Static int that gives the concret instance of Player mark
 	int m_sign;				//!< Mark of the Player in the game Array 
 };
/*===================================================================*/
 	/**
	*	This is an concrete represent of a player, that play the game. 
	*	This player controle the game with arrows on keyboard.
	*/
class Human : public Player
 {
 public:
 	Human ( CGameBoard * Board ); 	//!< Constructor of Human \sa Player
 	~Human ( void );				//!< destructor of class Human
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/ 				
 	STurn Play ( int FD = -1 );		
 private:
 };
/*===================================================================*/
 	/**
	*	This is an concrete represent of a player, that play the game. 
	*	This player represent AI that plays random STurn.
	*/
class AI : public Player
 {
 public:
 	AI ( CGameBoard * Board );		//!< Constructor of AI \sa Player
 	~AI ( void );					//!< destructor of class AI
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/
 	STurn Play ( int FD = -1 );
 private:
 };
/*===================================================================*/
	/**
	*	This is an concrete represent of a player, that play the game. 
	*	This player represent a Human player that play in net the mode.
	*/
class LOCAL : public Player
 {
 public:
 	LOCAL ( CGameBoard * Board ) ;	//!< Constructor of LOCAL \sa Player
 	~LOCAL ( void ) ;				//!< destructor of class LOCAL
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/
 	STurn Play ( int FD = -1 );
 private:
 };
/*===================================================================*/
	/**
	* 	This is an concrete represent of a player, that play the game. 
	*	This player represent the second player in the net mode. This class only recieve the STurn from second player.
	*/
class REMOTE : public Player
 {
 public:
 	REMOTE ( CGameBoard * Board ) ;	//!< Constructor REMOTE \sa Player
 	~REMOTE ( void ) ;				//!< destructor of class REMOTE
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/
 	STurn Play ( int FD = -1 );
 private:
 };
/*===================================================================*/
	/**
	*	This is an concrete represent of a player, that play the game. 
	*	This player represent AI that plays "normal" STurn.
	*/
class MINIMAX : public Player
 {
 public:
 	MINIMAX ( CGameBoard * Board );	//!< Constructor REMOTE \sa Player
 	~MINIMAX ( void );				//!< destructor of class REMOTE
 	/**
 	*	Method Play represet the turn of each player.
 		\param FD - an integer that represent the filedescriptor where the players send the STurns.
 		\return STurn is turn that is played in CGameBoard.
 	*/
 	STurn Play ( int FD = -1 );
 	/**
 	*	This method erasa the move taken as parameter from possible moves of AI.
 		\param Turn - constant reference to STurn that should be remove from possible moves.
 		\return bool value, true - Turn was removed, falsa - Turn was not in possible moves.
 	*/
 private:
 	bool PopPossibleTurn ( const STurn & Turn );
 	/**
 	*	This method erasa the move taken as parameter from possible moves of AI.
 		\param maxdepth - an integer that represent max depth of resursive funcion Min and Max.
 		\return STurn value that represent turn which AI want to play.
 	*/
 	STurn Init ( int maxdepth );
 	/**
 	*	Method Min represent turn of player in the tree of MINIMAX algorithm
 		\param depth - an integer that represent current depth of recursion.
 		\param alpha - an integer that represent maximal turn of AI. 
 		\param beta - an integer that represent maximal turn of Player.
 		\param maxdepth - an integer that represent max depth of resursive funcion Min and Max.
 		\return an integer that represent beta value.
 	*/
 	int Min ( int depth, int alpha, int beta, int maxdepth );
 	/**
 	*	Method Max represent turn of AI in the tree of MINIMAX algorithm
 		\param depth - an integer that represent current depth of recursion.
 		\param alpha - an integer that represent maximal turn of AI. 
 		\param beta - an integer that represent maximal turn of Player.
 		\param maxdepth - an integer that represent max depth of resursive funcion Min and Max.
 		\return an integer that represent alpha value.
 	*/
 	int Max ( int depth, int alpha, int beta, int maxdepth );

 	vector <STurn> m_possibles; 	//!< std::vector of all posible turns that AI can play in concrete part of game.
 	int m_oponent;					//!< mark of oponent in CGameBoard
 };
/*===================================================================*/
