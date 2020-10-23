#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "Player.hpp"
#include "Minimax.cpp"

int Player::i = 1;
/*===================================================================*/
Player::Player ( CGameBoard * Board )
 : m_Board ( Board ), m_sign (i)
 { i++ ;}
/*===================================================================*/
Player::~Player ( void )
 {i=1;}
/*===================================================================*/
Human::Human ( CGameBoard * Board  )
: Player ( Board )
 {}
/*===================================================================*/
Human::~Human ( void )
 {}
/*===================================================================*/
AI::AI ( CGameBoard * Board )
: Player ( Board )
 {}
/*===================================================================*/
AI::~AI ( void )
 {}
/*===================================================================*/
LOCAL::LOCAL ( CGameBoard * Board )
: Player ( Board )
 {}
/*===================================================================*/
LOCAL::~LOCAL ( void )
 {}
/*===================================================================*/
REMOTE::REMOTE ( CGameBoard * Board )
: Player ( Board )
 {}
/*===================================================================*/
REMOTE::~REMOTE ( void )
 {}
/*===================================================================*/
STurn Human::Play ( int FD )
 {
 	while ( true )
 	{
 		int ch = getch ( );
 		switch ( ch ){
  			case KEY_UP: m_Board->Up(); break;
  			case KEY_DOWN: m_Board->Down(); break;
  			case KEY_LEFT: m_Board->Left(); break;
  			case KEY_RIGHT: m_Board->Right(); break;
  			case '\n': 
  			if (!m_Board->ValidTurn(m_Board->Move(m_sign))) {
  				continue;
  			} 
  			else return m_Board->Move(m_sign);
  		}
 	}
 }
/*===================================================================*/
STurn AI::Play ( int FD )
 {
 	vector <STurn> moves = m_Board->Moves (m_sign);
 	if ( moves.size() )
 	{
 		STurn a = moves[rand()%(moves.size()-1)];
 		usleep(50000);
 		if ( FD != -1 ) write ( FD, &a, sizeof ( a ));
 		return a ;
 	}
 	else 
 	{
 		STurn  a ( rand()%15, rand()%15, m_sign );
 		while ( !m_Board->ValidTurn(a) )
 		{
 			a = STurn ( rand()%15, rand()%15, m_sign );
 		}
 		usleep(50000);
 		if ( FD != -1 ) write ( FD, &a, sizeof ( a ));
 		return a;
 	}
 }                                                                                        /*RANDOM TURNS */
/*===================================================================*/
/*===================================================================*/
STurn LOCAL::Play ( int FD )
 {
 	while ( true )
 	{
 		int ch = getch ( );
 		switch ( ch ){
  			case KEY_UP: m_Board->Up(); break;
  			case KEY_DOWN: m_Board->Down(); break;
  			case KEY_LEFT: m_Board->Left(); break;
  			case KEY_RIGHT: m_Board->Right(); break;
  			case '\n': 
  			if (!m_Board->ValidTurn(m_Board->Move(m_sign))) {
  				continue;
  			} 
  			else 
  			{
  				STurn a = m_Board->Move(m_sign);
  				if ( FD != -1 ) write ( FD, &a, sizeof ( a ));
  				return a;
  			}
  		}
  		refresh();
 	}
 	return m_Board->Move(m_sign);
 }
/*===================================================================*/
STurn REMOTE::Play ( int FD )
 {
 	STurn a ( -1,-1,-1 ) ;
 	if (!read ( FD, &a, sizeof ( a ) ) || FD < 0 ) return STurn (-1,-1,-1);
 	return a ;
 }
/*===================================================================*/
MINIMAX::MINIMAX ( CGameBoard * Board )
: Player (Board)
 {
 	if (m_sign == 1) m_oponent = 2;
 	else m_oponent = 1;
 }
/*===================================================================*/
MINIMAX::~MINIMAX ( void )
 {}
/*===================================================================*/
bool MINIMAX::PopPossibleTurn ( const STurn & Turn )
 {
 	STurn a = Turn;
 	a.m_sign = m_sign;
 	for ( vector<STurn>::iterator i = m_possibles.begin() ; i != m_possibles.end(); i++)
 	{		
 		if ( *i == a )
 		{
 			m_possibles.erase(i);
 			return true;
 		}
 	}

 	return false;
 }                                                                                           /*ERASING THE TURN FROM POSSIBLE TURN OF AI*/
/*===================================================================*/
STurn MINIMAX::Play ( int FD )
 {
 		
 		STurn  a = STurn ( rand()%15, rand()%15, m_sign );
  
 		//if ( !m_possibles.size() ) 
		m_possibles = m_Board->Moves(m_sign);
 		//else PopPossibleTurn(m_Board->Last());                                                   /* POPING THE TURN THAT PLAYED OTHER PLAYER */

		/* HERE TO CHANGE THE DIFFICULTY */
 		if ( m_Board -> Empty () != 0 ) a =  this->Init(4) ;                                     /* CALLING THE INIT OF RECURSIV MINIMAX ALGORIYTHM */
 		else a = STurn (15/2,15/2,m_sign);
 		
 		if ( FD != -1 ) write ( FD, &a, sizeof ( a ));
 		PopPossibleTurn(a);                                                                      /* POPING THE TURN THAT MINIMAX WANT TO PLAY*/
 	
 		return a;
 	
 }
/*===================================================================*/
