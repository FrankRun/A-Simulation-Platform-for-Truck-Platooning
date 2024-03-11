/*==========================================================================*/
/*  Link.h                                for Driver DLL Module for VISSIM  */
/*                                                                          */
/*  The abstract class which defines some basic properties of the Link      */
/*  class.                                                                  */
/*                                                                          */
/*  Version of 2018-4-10                                   Yi Zhao          */
/*==========================================================================*/

#pragma once
#pragma once
#ifndef __LINK_H
#define __LINK_H


class Link
{
public:
	Link();
	Link(long No, long isConn, long LanesNum,  double Length, long LinkFrom, long LankFrom, double posFrom,
		long LinkTo, long LaneTo, double posTo);
	virtual ~Link();

	long No=0;           //The number of the link.

	long isConn = 0;     //Whether the link is a connector, 0 for normal link and 1 for connector.
	long LanesNum = 0;   //The numbers of lanes of the link.
	double Length = 0; //The length of the link

	long LinkFrom = 0;   //The link the connector is from if the object is a connector.
	long LaneFrom = 0; //The lane the connector is from if the object is a connector. 
	double posFrom = 0; //The posistion of the link the connector is from if the object is a connector.

	long LinkTo = 0;   //The link the connector connects to if the object is a connector.
	long LaneTo = 0; //The lane the connector connects to if the object is a connector.
	double posTo = 0;  //The posistion of the link the connector connects to if the object is a connector.

};
#endif
