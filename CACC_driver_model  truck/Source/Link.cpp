#include "Link.h"



Link::Link()
{
}

Link::Link(long No, long isConn, long LanesNum,double Length, long LineFrom, long LaneFrom, double posFrom,
	long LinkTo, long LaneTo, double posTo) :
	No(No), isConn(isConn), LanesNum(LanesNum), LinkFrom(LineFrom), LaneFrom(LaneFrom), posFrom(posFrom),
	LinkTo(LinkTo), LaneTo(LaneTo), posTo(posTo), Length(Length)
{
}

Link::~Link()
{
}
