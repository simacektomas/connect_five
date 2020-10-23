#include <vector>
using namespace std;

/*===================================================================*/
int MINIMAX::Max ( int depth, int alpha, int beta, int maxdepth )
 {
 	if ( depth >= maxdepth )
 		return m_Board -> Value( m_sign, m_oponent ) - 2*m_Board -> Value( m_oponent, m_sign );
	

	
	for (vector<STurn>::iterator it = m_possibles.begin() ; it != m_possibles.end(); it ++)
 	{		
 		if (beta <= alpha) break;

 		STurn c = *it;
 		c.m_sign = m_sign;
 		m_Board->Turn(c);
 		m_possibles.erase(it);
 		int newalpha = Min( depth+1, alpha, beta, maxdepth );
 		m_Board->DeleteLast(c);
 		m_possibles.insert(it,c);

 		if ( newalpha > alpha )
 		{
 			alpha = newalpha;
 		}
 	}
 	return alpha;
 }																									/*RECURSIVE ALGORYTHM MINIMAX, SEARCHING FOR BEST MOVES*/
/*===================================================================*/
int MINIMAX::Min ( int depth, int alpha, int beta, int maxdepth )
 {
 	if ( depth >= maxdepth )
 		return m_Board -> Value( m_sign, m_oponent ) - 2*m_Board -> Value( m_oponent, m_sign );


	
	for (vector<STurn>::iterator it = m_possibles.begin() ; it != m_possibles.end(); it ++)
 	{
 		if (beta <= alpha) break;
 		
 		STurn c = *it;
 		c.m_sign = m_oponent;
 		m_Board->Turn(c);
 		m_possibles.erase(it);
 		int newbeta = Max( depth+1, alpha, beta, maxdepth );
		m_Board->DeleteLast(c);
		c.m_sign = m_sign;
 		m_possibles.insert(it,c);

 		if ( newbeta < beta )
 		{
 			beta = newbeta;
 		}
 		
 	}

 	return beta;
 }																									/*RECURSIVE ALGORYTHM MINIMAX, SEARCHING FOR BEST MOVES*/
/*===================================================================*/
STurn MINIMAX::Init ( int maxdepth )
 {
 	int depth = 0;	
 	

 	int alpha = -100000;
 	int beta = 100000;

 	int max = 0;
 	int i = 0;
 	for (vector<STurn>::iterator it = m_possibles.begin() ; it != m_possibles.end(); it ++)
 	{				
 		
 		STurn c = *it;
 		c.m_sign = m_sign;
 		m_Board->Turn(c);
 		m_possibles.erase(it);
 		
 		int newalpha = Min( depth+1, alpha,beta, maxdepth );
 		
 		m_Board->DeleteLast(c);
 		m_possibles.insert(it,c);
 			
 		if ( newalpha > alpha )
 		{
 			alpha = newalpha;
 			max = i ;
 		}
 		i++;	
 	}

 	
 	return m_possibles[max];
 }																									/* INIT OF RECURSIVE ALGORYTHM MINIMAX, SEARCHING FOR BEST MOVES*/
/*===================================================================*/