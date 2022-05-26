#ifndef USER_H
#define USER_H
#include "QString"

class User
{
public:
	User();
	QString Nameget(){
		return this->Name;
	}
private:
	QString Name;

};

#endif // USER_H
