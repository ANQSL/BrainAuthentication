#ifndef LOGIN_H
#define LOGIN_H
#include "QObject"
#include "brainrecognition.h"
#include "authoritymanage.h"
class Login:public QObject 
{
	Q_OBJECT
public:
	enum Status {
		LoginStatus = 0,
		RegisterStatus
	};
	explicit Login(QObject *parent=nullptr);
	~Login();
	void start();
	void setStatus(int status);
	void append(std::vector<float>);
	bool getLoginStatus();
signals:
	void loginSuccessed();
private:
	int status;
	Calculate::DeepLearn::BrainRecognition brain_recognition;
	QString name;
	AuthorityManage authority_manage;
	bool login_status;
};
#endif // !LOGIN_H
