#include <cstring>
#include <cstdlib>
#include "CGameBoard.hpp"
/*===================================================================*/
CGameBoard::CGameBoard ( int x, int y )
: m_y (y), m_x (x), m_cy (0), m_cx (0), m_last (-1,-1,-1), m_prev (-1,-1,-1), m_turns (0)
 {
 	m_Board = new int *[x];
 	for ( int i = 0; i < x; ++i )
 	{
 		m_Board[i] = new int [y];
 	}
 }
/*===================================================================*/
CGameBoard::CGameBoard ( const CGameBoard & Board )
:m_y (Board.m_y), m_x(Board.m_x), m_cy(Board.m_cy), m_cx(Board.m_cx), m_last(Board.m_last), m_prev(Board.m_prev), m_turns (Board.m_turns)
 {
 	m_Board = new int *[m_x];
 	for ( int i = 0; i < m_x; ++i )
 	{
 		m_Board[i] = new int [m_y];
 	}

 	for ( int i = 0 ; i < m_x ; i++)
 		for ( int y = 0 ; y < m_y ; y++ )
 		{
 			m_Board[i][y] = Board.m_Board[i][y];
 		}	
 }
/*===================================================================*/
CGameBoard::~CGameBoard ( void )
 {
 	for ( int i = 0; i < m_x; ++i )
 	{
 		delete [] m_Board[i];
 	}
 	delete [] m_Board;
 }
/*===================================================================*/
void CGameBoard::Window ( void ) 
 {
 	int V = 2; //VERTICAL
 	int H = 4; //HORIZONTAL
 	move((LINES-V*m_y+1)/2,(COLS-H*m_x+1)/2);
 	addch(ACS_ULCORNER);
 	for ( int i = 1 ; i < (H*m_x+1) ; i++)
 	{
 		if ( i == (H*m_x+1)-1 ) addch(ACS_URCORNER);
 		else
 		{
 			if ( i%H ) addch(ACS_HLINE); 
 			else addch(ACS_TTEE); 	
 		}	
 	}

 	move((LINES-V*m_y+1)/2+1,(COLS-H*m_x+1)/2);
 	for ( int i = 1 ; i < (V*m_y+1) ; i++)
 	{
 		
 		if ( i % V ) addch(ACS_LTEE);
 		else addch(ACS_VLINE);
 		for ( int z = 1 ; z < (H*m_x+1); z++)
 		{
 			if ( !(i % V) )
 			{
 				if( z%H ) addch(' ');
 				else addch(ACS_VLINE);
 			}
 			else
 			{
 				if ( z == H*m_x ) addch(ACS_RTEE);
 				else 
 				{
 					if ( z%H ) addch(ACS_HLINE); 
 					else addch(ACS_PLUS); 	
 				}
 			}
 		}
 		move((LINES-V*m_y+1)/2+i,(COLS-H*m_x+1)/2);
 	}
 	
 	addch(ACS_LLCORNER);
 	for ( int i = 1 ; i < (H*m_x+1) ; i++)
 	{
 		if ( i == (H*m_x+1)-1 ) addch(ACS_LRCORNER);
 		else
 		{
 			if ( i%H ) addch(ACS_HLINE); 
 			else addch(ACS_BTEE); 	
 		}	
 	}
 	
 	m_nx = (COLS-H*m_x+1)/2+2;
 	m_ny = (LINES-V*m_y+1)/2+1;
 	move(m_ny,m_nx);
 }																										/*PRINT THE GAME BOARD ON THE SCREEN*/
/*===================================================================*/
void CGameBoard::Left ( void )
 {
 	if ( m_cx -1 >= 0 )
 	{
 		m_cx --;
 		int y, x;
 		getyx ( stdscr,y,x );
 		move ( y, x-4 );
 	}
 }																										/* MOVE CURSOR AND CURRENT COORD LEFT*/
/*===================================================================*/
void CGameBoard::Right ( void )
 {
 	if ( m_cx +1 < m_x )
 	{
 		m_cx ++;
 		int y, x;
 		getyx ( stdscr,y,x );
 		move ( y, x+4 );
 	}
 }																										/* MOVE CURSOR AND CURRENT COORD RIGHT*/
/*===================================================================*/
void CGameBoard::Up ( void )
 {
 	if ( m_cy -1 >= 0 )
 	{
 		m_cy --;
 		int y, x;
 		getyx ( stdscr,y,x );
 		move ( y-2, x );
 	}
 }																										/* MOVE CURSOR AND CURRENT COORD UP*/
/*===================================================================*/
void CGameBoard::Down ( void )
 {
 	if ( m_cy +1 < m_y )
 	{
 		m_cy ++;
 		int y, x;
 		getyx ( stdscr,y,x );
 		move ( y+2, x );
 	}	
 }																										/* MOVE CURSOR AND CURRENT COORD DOWN*/
/*===================================================================*/
void CGameBoard::ShowLast ( void ) const
 {	
 	int y, x;
 	getyx ( stdscr,y,x );
 	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
 	if ( m_Board[m_last.m_x][m_last.m_y]+48 == '1' ) 
 	{
 		attron(COLOR_PAIR(1));
 		mvaddch (m_ny+2*m_last.m_y,m_nx+4*m_last.m_x, 'X');
 		attroff(COLOR_PAIR(1));
 	}
 	else 
 	{
 		attron(COLOR_PAIR(2));
 		mvaddch (m_ny+2*m_last.m_y,m_nx+4*m_last.m_x, 'O');
 		attroff(COLOR_PAIR(2));
 	}
 	move (y,x);
 }																										/* PRINT THE LAST PLAYED TURN IN GAMEBOAR ON THE SCREEN*/
/*===================================================================*/ 
bool CGameBoard::TerminalCheck ( void ) const
 {
  if(COLS < m_x*4+1 || LINES < m_y*2+4)
  {
  	mvprintw (LINES/2, (COLS-strlen("RESIZE TERMINAL"))/2, "RESIZE TERMINAL" );
 	getch();
  	return false;
  }
  
  return true;
 }																										/* CHECK IF THE TERMINAL IS ENOUGH WIDE AND HEIGHT*/
/*===================================================================*/
STurn CGameBoard::Move ( int player ) const
 {
 	return STurn (m_cx, m_cy, player);
 }																										/* RETURN STRUN THAHT CORESPOND WITH CURRENT COORDS */
/*===================================================================*/
void CGameBoard::Reset ( void )
 {
 	for ( int i = 0 ; i < m_x ; i++)
 		for ( int y = 0 ; y < m_y ; y++ )
 		{
 			m_Board[i][y] = 0;
 		}
 }																										/* INITIALIZE THE BOARD WITH 0 */
/*===================================================================*/
bool CGameBoard::Turn ( const STurn & Turn )
 {
 	if ( Turn.m_x < 0 || Turn.m_x >= m_x || Turn.m_y < 0 || Turn.m_y >= m_y ) return false ;
 	if ( m_Board[Turn.m_x][Turn.m_y] ) return false ;
 	m_prev = m_last;
 	m_last = Turn ;
 	m_Board[Turn.m_x][Turn.m_y] = Turn.m_sign;

 	m_turns++;
 	return true;
 }																										/* PUT THE TURN INTO A GAME BOARD IF THE TURN IS VALID */
/*===================================================================*/
void CGameBoard::DeleteLast ( const STurn & Turn ) 
 { 
 	m_turns--;
 	m_Board[Turn.m_x][Turn.m_y] = 0 ;
 }																										/* DELETE THE LAST PALAYED TURN */
/*===================================================================*/
bool CGameBoard::ValidTurn ( const STurn & Turn ) const
 {
 	if ( Turn.m_x < 0 || Turn.m_x >= m_x || Turn.m_y < 0 || Turn.m_y >= m_y ) return false ;
 	if ( m_Board[Turn.m_x][Turn.m_y] ) return false ;
 	return true;
 }																										/* CHECK IF THE TURN IS VALID */
/*===================================================================*/

bool CGameBoard::HasNeighbours ( int x, int y) const
{
	const int scan_radius = 2;
	for ( int dx = -scan_radius ; dx <= scan_radius; dx+=1) {
		for ( int dy = -scan_radius ; dy <= scan_radius; dy+=1) {
			if (x+dx < 0) { continue; }
			if (y+dy < 0) { continue; }
			if (x+dx >= m_x) { continue; }
			if (y+dy >= m_y) { continue; }
			if ((dx == 0) && (dy == 0)) { continue; }
			if (m_Board[x+dx][y+dy] != 0) { return true; }
		}
	}
	return false;
			
}

vector <STurn> CGameBoard::Moves ( int cur ) const
 {

	vector <STurn> moves;
	vector <STurn> unexpected_moves;

    for ( int i = 0 ; i < m_x ; i++ )
    	for ( int y = 0 ; y < m_y ; y++ ) {
    		if ( m_Board[i][y] == 0 ) {
			if (HasNeighbours(i,y)) {
				moves.push_back( STurn ( i,y, cur) );
			} else {
				unexpected_moves.push_back( STurn ( i,y, cur) );
			}
		}
	}

	//if (moves.size() <= 0) {
		moves.insert(moves.end(), unexpected_moves.begin(), unexpected_moves.end());
	//}

	return moves;
 }																										/* RETURN ALL MOVES IN BOARD THAT HAVE 0 VALUE*/
/*===================================================================*/
bool CGameBoard::Win ( void ) const
 {
 	int x = m_last.m_x;
 	int y = m_last.m_y;
 	int player = m_last.m_sign;
 	int cnt = 1;
 	if ( m_turns == m_x*m_y ) return true;
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( x+i >= m_x ) break;
 		if ( m_Board[x+i][y] == player ) cnt ++;
 		else break;
 	}
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( x-i < 0 ) break;
 		if ( m_Board[x-i][y] == player ) cnt ++;
 		else break;
 	}
 	if ( cnt >= 5 ) return true; 
 	cnt = 1;
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y+i >= m_y ) break;
 		if ( m_Board[x][y+i] == player ) cnt ++;
 		else break;
 	}
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y-i < 0 ) break;
 		if ( m_Board[x][y-i] == player ) cnt ++;
 		else break;
 	}
 	if ( cnt >= 5 ) return true; 
 	cnt = 1;
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y+i >= m_y || x+i >= m_x ) break;
 		if ( m_Board[x+i][y+i] == player ) cnt ++;
 		else break;
 	}
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y-i < 0 || x-i < 0 ) break;
 		if ( m_Board[x-i][y-i] == player ) cnt ++;
 		else break;
 	}
 	if ( cnt >= 5 ) return true; 
 	cnt = 1;
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y-i < 0 || x+i >= m_x ) break;
 		if ( m_Board[x+i][y-i] == player ) cnt ++;
 		else break;
 	}
 	for ( int i = 1 ; i < 5 ; i ++ )
 	{
 		if ( y+i >= m_y || x-i < 0 ) break;
 		if ( m_Board[x-i][y+i] == player ) cnt ++;
 		else break;
 	}
 	if ( cnt >= 5 ) return true; 
 	cnt = 1;
 	return false;
 }																							/* CHECK IF THE LAST PLAYED TURN IS WIN */
/*===================================================================*/
bool CGameBoard::Full() const
{
	return m_turns == m_x*m_y;
}																							/* RETURN THE VALUE OF PLAYED TURNS */
/*===================================================================*/
int CGameBoard::Value ( int first, int second ) const
 {
 	
 	int globalSum = 0;
 	globalSum += VerticalHorizontal(first);
	globalSum += TopLeftBotRight   (first);
	globalSum += TopRightBotLeft   (first);
	
	return globalSum/*-Neighbour(second)*/;

}																							/*HEURISTIC THAT GIVE THE CURRENT CONFIGURATION OF BOARD VALUE*/
/*===================================================================*/
int CGameBoard::VerticalHorizontal ( int first ) const
 {
 	int globalSum = 0;
		
	for(int y = 0; y < m_y ; y++)
	{
		bool found = false;
		int originX = -1;
		int inrow = 0;
		int sum = 0;
		bool found1 = false;
		int originY = -1;
		int inrow1 = 0;
		int sum1 = 0; 

		for ( int x = 0; x < m_x ; x++)	
		{
			/* PART FOR HORIZONTAL SEARCHING OF INROW MARKS */
			if ( found == false )
			{
				if ( m_Board[x][y] == first )
				{
					found = true;
					originX = x ;
					inrow = 1 ;
				}
			}
			else
			{
				if ( m_Board[x][y] == first )
				{
					inrow ++ ;
				}
				else 
				{
					found = false;
					bool k = false, l = false ;
					if (m_Board[x][y] == 0 )
					{
						k = true;
					}
					if (originX-1 >= 0)
					{
						if (m_Board[originX-1][y] == 0)
						{
							l = true;
						}
					}
					/* APRICIATING */
					sum = inrow;
					if ( k && l ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow;
					if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow/2;
					if ( !k && !l ) sum = 0;
					if ( inrow == 5 ) return 5000;
					globalSum += sum;
					inrow = 0;
					sum = 0;
					originX = -1;
				}

			}
			/* PART FOR VERTICAL SEARCHING OF INROW MARKS */
			if ( found1 == false )
			{
				if ( m_Board[y][x] == first )
				{
					found1 = true;
					originY = x ;
					inrow1 = 1 ;
				}
			}
			else
			{
				if ( m_Board[y][x] == first )
				{
					inrow1 ++ ;
				}
				else 
				{
					found1 = false;
					bool k = false, l = false ;
					if (m_Board[y][x] == 0 )
					{
						k = true;
					}
					if (originY-1 >= 0)
					{
						if (m_Board[y][originY-1] == 0)
						{
							l = true;
						}
					}
					/* APRICIATING */
					sum1 = inrow1;
					if ( k && l ) for ( int i = 0 ; i < inrow1 ; i++ ) sum1*= inrow1;
					if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow1 ; i++ ) sum1*= inrow1/2;
					if ( !k && !l ) sum1 = 0;
					if ( inrow1 == 5 ) return 5000;

					globalSum += sum1;
					inrow1 = 0;
					sum1 = 0;
					originY = -1;
				}		
			}
		}
	}
	return globalSum;
 }
/*===================================================================*/
int CGameBoard::TopLeftBotRight ( int first ) const
 {
 	int globalSum = 0;

 	for(int x = 0 ; x < m_x ; x++ )
	{
 		bool found = false;
 		bool found1 = false;
		int originX = -1;
		int originY = -1;
		int originX1 = -1;
		int originY1 = -1;
		int inrow = 0;
		int inrow1 = 0;
		int sum = 0;
		int sum1 = 0;

 		for(int y = 0 ; y < m_y-x ; y++) 
 		{
 		 /*PART TOP -> BOTTOM DIAGONAL TOP TRIANGLE SEARCHING */
 			if ( found == false )
			{
				if ( m_Board[x+y][y] == first )
				{
					found = true;
					originX = x+y ;
					originY = y ;
					inrow = 1 ;
				}
			}
			else
			{
				if ( m_Board[x+y][y] == first )
				{
					inrow ++ ;
				}
				else 
				{
					found = false;
					bool k = false, l = false ;
					if (m_Board[x+y][y] == 0 )
					{
						k = true;
					}
					if ( (originY-1 >= 0) &&  (originX-1 >=0) )  
					{
						if (m_Board[originX-1][originY-1] == 0)
						{
							l = true;
						}
					}
					/* APRICIATING */
					sum = inrow;
					if ( k && l ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow;
					if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow/2;
					if ( !k && !l ) sum = 0;
					if ( inrow == 5 ) return 5000;

					globalSum += sum;
					inrow = 0;
					sum = 0;
					originY = -1;
					originX = -1;
				}		
			}

			/*PART TOP -> BOTTOM DIAGONAL BOTTOM TRIANGLE SEARCHING */
			if ( x != 0 )	/* WITHOUT THE MAIN DIAGONAL AGAIN */
			{
				if ( found1 == false )
				{
					if ( m_Board[y][x+y] == first )
					{
						found1 = true;
						originX1 = y ;
						originY1 = x+y ;
						inrow1 = 1 ;
					}
				}
				else
				{
					if ( m_Board[y][x+y] == first )
					{
						inrow1 ++ ;
					}
					else 
					{
						found1 = false;
						bool k = false, l = false ;
						if (m_Board[y][x+y] == 0 )
						{
							k = true;
						}
						if ( (originY1-1 >= 0) && (originX1-1 >=0 ) )  
						{
							if (m_Board[originY1-1][originX1-1] == 0)
							{
								l = true;
							}
						}
						/* APRICIATING */
						sum1 = inrow1;
						if ( k && l ) for ( int i = 0 ; i < inrow1 ; i++ ) sum1*= inrow1;
						if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow ; i++ ) sum1*= inrow1/2;
						if ( !k && !l ) sum1 = 0;
						if ( inrow1 == 5 ) return 5000;
	
							globalSum += sum1;
							inrow1 = 0;
							sum1 = 0;
							originY1 = -1;
							originX1 = -1;
						}		
				}
			}
	 	}
	}
	return globalSum;
 }
/*===================================================================*/
int CGameBoard::TopRightBotLeft ( int first ) const
 {
 	int globalSum = 0;
	/*PART TOP -> BOTTOM DIAGONAL TOP TRIANGLE SEARCHING */
 	for ( int x = m_x-1; x >= 0 ; x--)
	{
 		bool found = false;	
		int originX = -1;
		int originY = -1;
		int inrow = 0;
		int sum = 0;		
 		for ( int y = 0 ; y <= x ; y++)
 		{
  			if ( found == false )
			{
				if ( m_Board[x-y][y] == first )
				{
					found = true;
					originX = x-y ;
					originY = y ;
					inrow = 1 ;
				}
			}
			else
			{
				if ( m_Board[x-y][y] == first )
				{
					inrow ++ ;
				}
				else 
				{
					found = false;
					bool k = false, l = false ;
					if (m_Board[x-y][y] == 0 )
					{
						k = true;
					}
					if ( (originY-1 >= 0 ) &&  (originX+1 < m_y) )  
					{
						if (m_Board[originX+1][originY-1] == 0)
						{
							l = true;
						}
					}
					/* APRICIATING */
					sum = inrow;
					if ( k && l ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow;
					if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow/2;
					if ( !k && !l ) sum = 0;
					if ( inrow == 5 ) return 5000;

					globalSum += sum;
					inrow = 0;
					sum = 0;
					originY = -1;
					originX = -1;
				}		
			}
 		}
	}
	/*PART TOP -> BOTTOM DIAGONAL BOTTOM TRIANGLE SEARCHING */
	for( int y = 0; y < m_y ; y++)
	{
		bool found = false;	
		int originX = -1;
		int originY = -1;
		int inrow = 0;
		int sum = 0;	
 		for(int yy = 0, x = m_x-1; x >= y; x--,yy++)
 		{
 			if ( found == false )
			{
				if ( m_Board[x][y+yy] == first )
				{
					found = true;
					originX = x ;
					originY = y+yy ;
					inrow = 1 ;
				}
			}
			else
			{
				if ( m_Board[x][y+yy] == first )
				{
					inrow ++ ;
				}
				else 
				{
					found = false;
					bool k = false, l = false ;
					if ( m_Board[x][y+yy] == 0 )
					{
						k = true;
					}
					if ( (originY-1 >= 0 ) &&  (originX+1 < m_y) )  
					{
						if (m_Board[originX+1][originY-1] == 0)
						{
							l = true;
						}
					}
					/* APRICIATING */
					sum = inrow;
					if ( k && l ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow;
					if ( (!k && l) || (k && !l) ) for ( int i = 0 ; i < inrow ; i++ ) sum*= inrow/2;
					if ( !k && !l ) sum = 0;
					if ( inrow == 5 ) return 5000;

					globalSum += sum;
					inrow = 0;
					sum = 0;
					originY = -1;
					originX = -1;
				}		
			}
 		 
		}
	}
	return globalSum;
 }
/*===================================================================*/
int CGameBoard::Neighbour ( int first ) const
{
	int cnt = 0;
	for ( int x = 0 ; x < m_x ; x++ )
	{
		for ( int y = 0 ; y < m_y; y++)
		{
			if ( m_Board[x][y] == first )
			{
				if ( x-1 >= 0 ) if (m_Board[x-1][y] == first) cnt++;
				if ( x+1 < m_x ) if (m_Board[x+1][y] == first) cnt++;
				if ( y-1 >= 0 ) if (m_Board[x][y-1] == first) cnt++;
				if ( y+1 < m_y ) if (m_Board[x][y+1] == first) cnt++;

				if ( (x-1 >= 0) && (y-1 >=0 )) if (m_Board[x-1][y-1] == first) cnt++;
				if ( (x-1 >= 0) && (y+1 < m_y )) if (m_Board[x-1][y+1] == first) cnt++;
				if ( (x+1 < m_x) && (y-1 >=0 )) if (m_Board[x+1][y-1] == first) cnt++;
				if ( (x+1 < m_x) && (y+1 < m_y )) if (m_Board[x+1][y+1] == first) cnt++;
			}
		}
	}
	
	return cnt;
}																										/*HEURISTIC VALUATED FUNCTION ON NEIGHTBOUR */
/*===================================================================*/
void CGameBoard::Print ( void ) const
 {
 	int y,x;
 	getyx (stdscr, y,x);
 	for ( int i = 0; i < m_x ; i++)
 		for ( int l = 0; l < m_y ; l++)
 			mvprintw(i+5,l,"%d",m_Board[i][l]);
 	getch();
 	move (y,x);
 }																										/*PRINT THE BOARD ON SCREEN (DEBUG)*/
/*===================================================================*/
