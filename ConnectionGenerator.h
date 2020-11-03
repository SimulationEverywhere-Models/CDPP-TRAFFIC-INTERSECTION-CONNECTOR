/*******************************************************************
*
*  DESCRIPTION: Atomic Model ConnectionGenerator
*
*  AUTHOR: Ismaeel and Ardeshir 
*  
*  DATE: October 26, 2008
*
*******************************************************************/

#ifndef __CONNECTIONGENERATOR_H
#define __CONNECTIONGENERATOR_H


#include "atomic.h"     // class Atomic
class Distribution ;
class ConnectionGenerator : public Atomic
{
public:
	ConnectionGenerator( const string &name = "ConnectionGenerator" );  //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &out;
	Port &reset;
	Time timeOut, zero;
	Distribution * dist;
	int index;
	
	Distribution &distribution()
	{return *dist;}




};	// class ConnectionGenerator

// ** inline ** // 
inline
string ConnectionGenerator::className() const
{
	return "ConnectionGenerator" ;
}

#endif   //__CONNECTIONGENERATOR_H
