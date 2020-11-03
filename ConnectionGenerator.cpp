/*******************************************************************
*
*  DESCRIPTION: The Atomic Model ConnectionGenerator
*
*  AUTHOR: Ismaeel and Ardeshir 
*  
*  DATE: October 26, 2008
*
*******************************************************************/

/** include files **/
#include "ConnectionGenerator.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"  

/** public functions **/

/*******************************************************************
* Function Name: ConnectionGenerator
* Description: 
********************************************************************/
ConnectionGenerator::ConnectionGenerator( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, reset( addInputPort("reset"))
, timeOut(0, 0, 0, 1)
, zero(0,0,0,0)
{	/*string time2( MainSimulator::Instance().getParameter( description(), "timeOut" ) ) ;

	if( time2 != "" )
		timeOut = time2 ;	
	string time3( MainSimulator::Instance().getParameter( description(), "zero" ) ) ;

	if( time3 != "" )
		zero = time3 ;	*/
		
	index = 1;
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &ConnectionGenerator::initFunction()
{
	this-> passivate();
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &ConnectionGenerator::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in  /*&& this->state() == passive*/ && msg.value()!=0)
	{	index ++;
		holdIn(active, timeOut ); 
		//holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) );
	}
	
	//if( msg.port() == reset && msg.value()!=0)
	//{	
	//	holdIn(passive, zero ); 
	//}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &ConnectionGenerator::internalFunction( const InternalMessage & )
{
	if(state()==active)
	{
		holdIn( passive  , timeOut );
	}
	else
		this->passivate();
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &ConnectionGenerator::outputFunction( const InternalMessage &msg )
{
	if(state()==passive)
	{
		sendOutput( msg.time(), out, false ) ;
	}
	else
		sendOutput( msg.time(), out, static_cast<float>( fabs( distribution().get() ) ) ) ;
	return *this ;
}

