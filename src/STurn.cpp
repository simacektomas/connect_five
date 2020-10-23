#include "STurn.hpp"
/*===================================================================*/
STurn::STurn ( int x, int y , int player )
: m_x (x), m_y (y), m_sign (player)
 {}
/*===================================================================*/
STurn::~STurn ( void )
 {}
/*===================================================================*/
ostream & operator << ( ostream & os, const STurn & In ) 
 {
 	os << "[" << In.m_x << ':' << In.m_y <<']' << In.m_sign << endl; 
 	return os; 
 }
/*===================================================================*/
bool STurn::operator == ( const STurn & Instance ) const
 { 
 	if ((m_x == Instance.m_x) && (m_y == Instance.m_y))return true;
 	else return false;
 }
