#ifndef _I_SERVER_
#define _I_SERVER_

class IServer
{
public:
	~IServer(){};

	virtual void Launch() = 0;
	virtual void Close() = 0;
};

#endif /* _I_SERVER_ */