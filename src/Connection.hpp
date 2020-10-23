#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
 using namespace std;
/*===================================================================*/
/**
*	This class represent a connection between server and client or client and server, it depend what is chosen in menu.
*	It close all connection when the class is desctructed.
*/
class Connection 
 {
 public:
 	/**
 	* 	Counstruct empty class Connection.
 	*/
 	Connection ( void );
 	/**
 	*	This is a copy constructor with params ip and port.
 		\param ip - const char * argument that represent ip.
 		\param port - int argument that represent port.
 	*/
 	Connection ( const char * ip, int port );
 	/**
 	*	Destructor, it'll close the sokets that are still opent when the game will end.
 	*/
 	~Connection ( void );
 	/**
 	*	\brief This method try to open the connection on Client side, if it succes return a filedescriptor, if not return a negativ int value.
 		\return if the connection is not open return -1, if is open return value of filedescriptor for datacomunication.
 	*/
 	int openCliSocket ( void );
 	/**
 	*	\brief This method try to open the connection on Server side, if it succes return a filedescriptor, if not return a negativ int value.
 		\return if the connection is not open return -1, if is open return value of filedescriptor for comunication.
 	*/
 	int openSrvSocket ( void );
 	/**
 	*	\brief It takes a value of filedescriptor and close it.
 		\param fd - an integer that represet a file descriptor.	
 	*/
 	void closeSocket(int fd);
 	/**
 	*	\brief It start a server connection, open a socket for communication whit client and return a datasocket for data comunication.
 		\return return an iteger -1 if the connection is not opened, or value of opened socket for data communication.
 	*/
 	int Server ( void );
 	/**
 	*	\brief It print the the connection prarams in top-left corner.
 	*/
 	void Print ( void ) const;
 	
 private:
 	string m_name; 		/*< Variable m_name represet ip adress */
 	int port;			/*< Variable port represet port */
 	int m_Socket; 		/*< m_Socket represet opened cominication socket of server */
 	int m_DataSocket; 	//!< Variable m_DataSocket represent opened datasocket of client or server, data is coming and writing in this
 };

/*===================================================================*/