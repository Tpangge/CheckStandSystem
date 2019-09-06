#include "Common.h"


class LogInWnd : public WindowImplBase
{
public:
	virtual void Notify(TNotifyUI& msg);
	void LogIn();
   
protected:
	// WindowImplBase 提供的纯虚函数
	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件的名字
	virtual CDuiString GetSkinFile();

	//返回窗口类的名字：在注册窗口的时候提供
	virtual LPCTSTR GetWindowClassName(void) const;

};