#include <vector>
#include <ncurses.h>
#include "STurn.hpp"
/*===================================================================*/
	/**
	*	This is the main data class of whole game. This class store all data and STurn int one 2d array of int. It is part of CGame class and it prvovide 
	* 	move of on the screen, storing the STurn in the array, showing the turn on the screen and checking end of the game or full array. It comunicate with players 
	* 	who send STurn to play.
	*/
class CGameBoard 
 {
 public:
 	CGameBoard ( int x, int y );												//!< Constructor with two parameters \param x - integer, width of array \param y - integer , height of array
 	CGameBoard ( const CGameBoard & Board );									//!< Copy constructor, it initalize CGameBoard with data from parameter \param Board - const CGameBoard &, represent another CGameBoard
 	~CGameBoard ( void );														//!< Destructor - delete the array and desctruct the instance.
 	/*NCURSES*/
 	void Window ( void ) ;														//!< It print the Initial empty array on the board. (NCURSES)
 	void Left ( void );															//!< Move the cursor to left field, and set current coords. (NCURSES)
 	void Right ( void );														//!< Move the cursor to right field, and set current coords. (NCURSES) 
 	void Up ( void );															//!< Move the cursor to upper field, and set current coords. (NCURSES)
 	void Down ( void );															//!< Move the cursor to bottom field, and set current coords. (NCURSES)
 	void ShowLast ( void ) const;												//!< Print the last turn on the board. (NCURSES)
 	bool TerminalCheck ( void ) const ;											//!< Check if the terminal is enough big to play the game \return bool value false - terminal is too small, bool value true - if the terminal is enough. (NCURSES)
 	/*METHOD*/
 	/**
 	*	This method return STurn which belong to player in parameter and the STurn values are asi the current values in the board.
 		\param player - int mark of the player
 		\return STurn - represetn currnet coord in CGameBoard
 	*/
 	STurn Move ( int player ) const ;													
 	void Reset ( void );														//!< Set all array field to 0.
 	bool Turn ( const STurn & Turn );											//!< Place the turn in parameter in the array \param Turn - const STurn & - Turn to play \return bool value true - if the turn is valid, flase if the turn is not valid.
 	bool ValidTurn ( const STurn & Turn ) const;								//!< Check if the turn is valid \param Turn - const STurn & - Turn to check \return bool value true - if the turn is valid, flase if the turn is not valid.
 	/**
 	*	This funciton give a heuristic value to currnet cgameboard configuration
 		\param first - int the player for who the value should be. \param second - int the second player. 
 		\return int the Value of current configuration
 	*/
 	int Value ( int first, int second ) const;
 	/**
 	*	This function can give a value to current configuration of the CGameBoard int vertical and horizontal direction
 		\param first - int the player for who the value should be. 
 		\return int the part Value of current configuration
 	*/
 	int VerticalHorizontal ( int first ) const;
 	/**
 	*	This function can give a value to current configuration of the CGameBoard int Diagonals direction
 		\param first - int the player for who the value should be.  
 		\return int the part Value of current configuration
 	*/
 	int TopLeftBotRight ( int first ) const;
 	/**
 	*	This function can give a value to current configuration of the CGameBoard int Diagonals direction
 		\param first - int the player for who the value should be.
 		\return int the part Value of current configuration
 	*/
 	int TopRightBotLeft ( int first ) const;
 	/**
 	*	This method return vector of possible moves in this configuration of the CGameBoard and give the STurns value of player from parameter
 		\param cur - int player for who the turns are.
 		\return vector of STurn which conntain all possible moves.
 	*/
 	vector <STurn> Moves ( int cur ) const;
	bool HasNeighbours ( int x, int y) const;
 	bool Win ( void ) const;													//!< Check if the last turn was a winner turn \return bool true - if the last turn won, false - if not.
 	bool Full ( void ) const;													//!< Check if the board is full \return bool true - if board is full, false - if not.
 	int Empty ( void ) const													//!< Check if the board is epmty \return int how many turns were played.
 	{
 	 	return m_turns;
 	};	

 	STurn Last ( void ) const 													//!< Return the last played STurn \return STurn 
 	{
 		return m_last;
 	};	

 	STurn Prev ( void ) const													//!< Return the second last plyed STurn \return STurn
 	{
 		return m_prev;
 	};	

 	void DeleteLast ( const STurn & Turn );										//!< Delete the STurn from parameter from the board \param Turn - const STurn &, Turn that should be deleted.
 	
 	void Print ( void ) const ;													//!< Print the data array on the board.
 	int Neighbour ( int first ) const ;											//!< Value function for AI.\param first - int what players neighbour \return int Number of neighbour
 private:
 	int ** m_Board ;
 	int m_y, m_x; 																/*SIZES*/
 	int m_cy, m_cx; 															/*CURRENT POSITION*/
 	int m_ny, m_nx; 															/*INIT OF NCURSES*/
 	STurn m_last;
 	STurn m_prev;
 	int m_turns;

 	
 };
/*===================================================================*/
