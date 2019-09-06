#pragma once
//#include "MySQL.h"
#include "Common.h"


class MainWnd : public WindowImplBase
{
//public:
//	MainWnd(MySQL* pMySQL);
//	~MainWnd();

	virtual void Notify(TNotifyUI& msg);


protected:
	// WindowImplBase 提供的纯虚函数
	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件的名字
	virtual CDuiString GetSkinFile();

	//返回窗口类的名字：在注册窗口的时候提供
	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectEmployeeInfo();

	void DeleteEmployeeInfo();

	void InsertEmployeeInfo();

//private:
//	MySQL* m_pMySQL;
};