#include "CGame.hpp"
#include "cstring"

/*===================================================================*/
CGame::CGame ( void ) 
: m_current ( 0 ), m_Fd( -1 ), m_Connection ( NULL )
 { }
/*===================================================================*/
CGame::~CGame ( void )
 { 
 	for ( vector <Player *> :: const_iterator it = m_Players.begin(); it != m_Players.end(); it++) 
 		delete *it;
 	delete m_Board;                       
  delete m_Connection;                                                                    /*ENDING CONNECTION, DESTROYING PLAYERS AND DESTROYING GAME ARRAY*/
 }
/*===================================================================*/
int CGame::Menu ( void ) const
 {
  clear();
  int ch;
  int i = strlen ( "1. SINGLE PLAYER" )/2;
  int y = LINES/2-2 ;
  int x = COLS/2-i ;
  mvprintw ( y, x, "1. SIGLE PLAYER" ); y++;
  mvprintw ( y, x, "2. MULTIPLAYER (LOCAL)" ); y++;
  mvprintw ( y, x, "3. MULTIPLAYER (HOST)" ); y++;
  mvprintw ( y, x, "4. MULTIPLAYER (CLIENT)" ); y++;
  mvprintw ( y, x, "5. END" ); y++;
  move(y-5,x-1);
  i = Choosing (4);
  
  clear();
  refresh();
  return i;                                                                               /* MEMBER THAT PRINT MENU ON SCREEN AND RETURN VALUE OF MODE, WAITING FOR USER INPUT */
 }
/*===================================================================*/
bool CGame::NetConfig ( void )
 {
  clear();
  char ip[60];
  char port[30];
  int PORT;
  echo();
  mvprintw (0,0, "INSERT IP ADRESS WITHOUT PORT: ");
  getstr(ip);
  mvprintw (1,0, "INSERT PORT: ");
  getstr(port);
  PORT = atoi(port); 
  noecho(); 
 
  if (PORT == 0) PORT = 6000;
  if ( strlen(ip) == 0 ) m_Connection = new Connection ( "localhost", PORT );
  else m_Connection = new Connection ( ip, PORT );
  return true;                                                                            /* MEMBER THAT TAKES PORT AND IP FROM STDIN, IF NOT SET UP DEFAULT SETTINGS */
 }
/*===================================================================*/
int CGame::Choosing ( int max ) const
 {
    int ch, i = 0;
    int y, x;
    getyx(stdscr, y,x);
    while ( (ch = getch()) != '\n' )
    {   
      switch (ch)
      {
        case KEY_DOWN: 
          if ( i != max )i++;
          move(y+i,x);
          break;
        case KEY_UP:
          if ( i != 0 )i--;
          move(y+i,x);  
          break;  
         default:
          break;  
      }
      refresh();  
    }
  return i; 
 }                                                                                        /* CHOOSING LOOP THAT PROVIDE USER TO CHOOSE SOME ITEM FROM MENU */
/*===================================================================*/
void CGame::SettingSingle ( void )
 {
    clear();
    int ch = 0;
    int i = 0;
    mvprintw (0,0, "CHOOSE DIFFICULTY OF AI: ");
    mvprintw (1,1, "1 - EASY(RANDOM)");
    mvprintw (2,1, "2 - MEDIUM(MINIMAX)");
    move(1,0);
    int y = 1, x = 0;
    int choice = Choosing ( 1 );
    switch ( choice )
    {
        case 0: 
            m_Players.push_back ( new AI (m_Board) );  
            m_Players.push_back ( new Human (m_Board) );
            break;       
        case 1:
            m_Players.push_back ( new MINIMAX (m_Board) );  
            m_Players.push_back ( new Human (m_Board) );
            break;  
    }
 }                                                                                          /* SETTING OF AI'S DIFFICULTY IN SIGLE PLAYER MODE */                                                         /* SETTING OF PLAYER IN MULTIPLAYER */
/*===================================================================*/
int CGame::Config ( int Choice )
 {
 	int x = 15;
 	int y = 15;
 	m_Board = new CGameBoard (x,y);	
  if ( Choice != 4 ) if(!m_Board -> TerminalCheck()) return 1;
 	m_Board -> Reset ();

  switch ( Choice )
  {
      case 0:        
            this->SettingSingle ();                                     
            break;
      case 1:
            m_Players.push_back ( new Human (m_Board));
            m_Players.push_back ( new Human (m_Board));      
            break;
      case 2:
            m_Players.push_back ( new REMOTE (m_Board));
            m_Players.push_back ( new LOCAL (m_Board));
            if(!this->NetConfig()) return 2;          
            refresh();
            m_Fd = m_Connection->Server ();
            if ( m_Fd < 0 ) return 3;          
            break;
      case 3:
            m_Players.push_back ( new LOCAL (m_Board));
            m_Players.push_back ( new REMOTE (m_Board) );
            if(!this->NetConfig()) return 2;
            refresh();
            m_Fd = m_Connection->openCliSocket ();
            if ( m_Fd < 0 ) return 3;                                               
            break;
      case 4: return 4;

 	}
 	return 0;                                                                            /* CONFIGURATION METHOD THAT PREPARE PLAYERS BASE ON THE CHOICE PAREMETER TAKEN FROM METHOD MENU */
 }
/*===================================================================*/
void CGame::Result ( void ) const
 { 
   if ( m_Board->Full() )
   {
     mvprintw ( 0, (COLS-strlen("FULL BOARD"))/2, "FULL BOARD");
     mvprintw ( 1, (COLS-strlen("PRES ENTER TO CONTINUE"))/2, "PRES ENTER TO CONTINUE");
     getch();
     clear();
   }
   else
   {
     mvprintw ( 0, (COLS-strlen("WINNER IS PLAYER "))/2, "WINNER IS PLAYER %d", m_current+1);
     mvprintw ( 1, (COLS-strlen("PRES ENTER TO CONTINUE"))/2, "PRES ENTER TO CONTINUE");
     getch();
     clear();
   }
 }                                                                                         /* PRINT ON THE SCREEN WHO IS WINNER ON THE END OF GAME OR IF THE GAMEBOARD IS FULL */
/*===================================================================*/
void CGame::Game ( void )
 { 
  while ( true )
 		 {
      STurn a = m_Players[m_current]->Play(m_Fd);
      if (!m_Board->Turn (a)) break;
      m_Board->ShowLast();
      refresh();
      if ( m_Board -> Win ()) break;
      m_current++;
      if ( m_current == m_Players.size()) m_current= 0;
 		 }                                                                                     /* THIS IS UNIVERSAL GAME CYCLE FOR ALL TYPE OF GAME MODES */
 }
/*===================================================================*/
void CGame::Start ( void )
 {
  clear();
  m_Board -> Window ();
  refresh();
  this->Game();
  this->Result();
 }                                                                                         /* INITIALIZE THE WINDOW ON THE SCREEN END START THE GAME */
/*===================================================================*/
 int main ( void )
  {
  	srand(time(NULL));
    initscr();
  	noecho();
  	cbreak();
    start_color();
  	keypad(stdscr, TRUE);
    int fail = 0;
    while (true)
    {
        CGame a;
        if( fail = a.Config( a.Menu() ))
        {
            endwin();
            if ( fail == 4 )return 0;                       
            return fail;                                                                  /* 1 Terminal is too small, 2 Netconfig fail, 3 Cannot Start server or connect to server */
        }
        a.Start();
    }   
  	endwin();
  
  	return 0;
  }
/*===================================================================*/