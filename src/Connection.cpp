#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>
#include "Connection.hpp"

/* METHOD USED FROM https://edux.fit.cvut.cz/courses/BI-PA2/_media/networking-2014.tgz BUT REMAKE OR CUSTOMIZE */
/*===================================================================*/
Connection::Connection ( void )
:  m_name ("localhost"), port ( 6000 ), m_DataSocket ( -1 )
 {}
/*===================================================================*/
Connection::Connection ( const char * ip, int port )
: m_name (ip), port (port), m_Socket (-1), m_DataSocket ( -1 )
 {}
/*===================================================================*/
Connection::~Connection ( void )
 {
 	if (m_Socket != -1) this->closeSocket(m_Socket);
 	if (m_DataSocket != -1) this->closeSocket(m_DataSocket);
 }
/*===================================================================*/
int Connection::openCliSocket ( void )
 {
   struct addrinfo * ai;
   char portStr[10];
   const char * name = m_name.c_str();

   snprintf ( portStr, sizeof ( portStr ), "%d", port );
   if ( getaddrinfo ( name, portStr, NULL, &ai ) )
    {
      port++;
      freeaddrinfo ( ai );
      char portStr2[10];
      snprintf ( portStr2, sizeof ( portStr2 ), "%d", port );
 	  if ( getaddrinfo ( name, portStr2, NULL, &ai ) )
      {
      int y,x;
  	  getyx(stdscr, y ,x);
   	  mvprintw (LINES-1,0, "addrinfo problem, PRESS ENTER" );
      getch();
  	  move ( y,x );
      return -1;
 	  }
    }

   int fd = socket ( ai -> ai_family, SOCK_STREAM, 0 );
   if ( fd == -1 )
    {
      freeaddrinfo ( ai );
      int y,x;
  	  getyx(stdscr, y ,x);
   	  mvprintw (LINES-1,0, "socket problem, PRESS ENTER" );
      getch();
  	  move ( y,x );
      return -1;
    }

   if ( connect ( fd, ai -> ai_addr, ai -> ai_addrlen ) == - 1 )
    {
      close ( fd );
      freeaddrinfo ( ai );	  
   	  int y,x;
  	  getyx(stdscr, y ,x);
   	  mvprintw (LINES-1,0, "Cannot connect to server, PRESS ENTER" );
      getch();
  	  move ( y,x );
      	return -1;
      }
     
      
    
   freeaddrinfo ( ai );
   m_Socket = fd;
   this->Print();
   refresh();
   return fd;
 }                                                                              /*TRY TO OPEN SOCKET ON CLIENT SIDE, TRY TO COMINUCATE WITH SERVER*/
/*===================================================================*/
int Connection::openSrvSocket ( void )
 {
   struct addrinfo * ai;
   char portStr[10];
   const char * name = m_name.c_str();
 
   snprintf ( portStr, sizeof ( portStr ), "%d", port );
   if ( getaddrinfo ( name, portStr, NULL, &ai ) )
    {   
      int y,x;
  	  getyx(stdscr, y ,x);
  	  mvprintw (LINES-1,0, "addrinfo problem, PRESS ENTER" );
      getch();
  	  move ( y,x );
      return -1;
  	  
    }
  
   int fd = socket ( ai -> ai_family, SOCK_STREAM, 0 );

   if ( fd == -1 )
    {
      freeaddrinfo ( ai );
      int y,x;
  	  getyx(stdscr, y ,x);
  	  mvprintw (LINES-1,0, "socket problem, PRESS ENTER" );
      getch();
  	  move ( y,x );
      return -1;
    }
    int optval = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
  
   if ( bind ( fd, ai -> ai_addr, ai -> ai_addrlen ) == -1 )
    {
     
      close ( fd );
      freeaddrinfo ( ai );
      int y,x;
  	  getyx(stdscr, y ,x);
  	  mvprintw (LINES-1,0, "bind problem, PRESS ENTER " );
      getch();
  	  move ( y,x );
      return -1;
    	
    
    }
   freeaddrinfo ( ai );
  
   if ( listen ( fd, 10 ) == -1 )
    {
      close ( fd );
      int y,x;
  	  getyx(stdscr, y ,x);
  	  mvprintw (LINES-1,0, "cannot listenm PRESS ENTER" );
      getch();
  	  move ( y,x );
      return -1;
    }
   m_Socket = fd;
   return fd;
 }                                                                                          /*TRY TO OPEN COMUNICATION SOCKET ON SERVER SIDE*/
/*===================================================================*/
int Connection::Server ( void )
 {
   int FD;
   if ((FD = openSrvSocket()) == -1) return -1;
   struct sockaddr remote;
   socklen_t remoteLen = sizeof ( remote );
   clear();
   mvprintw (0,0,"WAITING FOR CONECTION");
   refresh();
   int dataFd = accept ( FD, &remote, &remoteLen );
   closeSocket(FD);
   m_Socket = -1;
   this->Print();
   m_DataSocket = dataFd;	
   return dataFd;
 }                                                                                          /*WAIT FOR CONNECTION AND OPEN DATA SOCKET IF COMUNICATION COME*/
/*===================================================================*/
void Connection::closeSocket(int fd) 
{         
     if (close(fd) < 0) mvprintw(LINES+20,0,"FAIL");
}
/*===================================================================*/
void Connection::Print ( void ) const
  { 
    clear();
    int x,y;
    getyx ( stdscr, y,x);
    mvprintw (0,0, "CONNECTED TO: %s:%d", m_name.c_str(), port);
    move(y,x);
    refresh();
  }                                                                                         /* PRINT THE CONNECTION PARAMS */
/*===================================================================*/
