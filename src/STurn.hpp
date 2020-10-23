#include <iostream>
using namespace std;
/*===================================================================*/
	/**
	*	This is a transfer class between classes derive from Player and CGameBoard. Each Player's method Play returns the STurn move which can be played in the CGameBoard.
	*	Also this class is transfer between computer in NET mode. So this class is only transfer class. It has 3 int member. Two for coords in the game array and one for players mark.
	* 	It has operator == so we can decide of equality of two STurns or we can print it on the board.
	*/
struct STurn 
 {
 	STurn ( int x, int y , int player );										//!< Constructor \param x - integer, x coord in CGameBoard \param y - integer y coord in board \param player - integer mark of owner.
 	~STurn ( void );															//!< destructor of STurn.
 	
 	friend ostream & operator << ( ostream & os, const STurn & In ) ;			//!< friend function that can print the STurn int the stream
 	bool operator == ( const STurn & Instance ) const ;							//!< operator == that can decide if is equal to another STurn
 	
 	int m_x ; 																	//!< X coord in CGameBoard array.
 	int m_y ;																	//!< Y coord in CGameBoard array.
 	int m_sign ;																//!< Mark of owner.
 };
/*===================================================================*/
