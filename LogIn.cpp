#include "login.h"
#include "MainWnd.h"
#include "Common.h"

//xml文件对应的目录
CDuiString LogInWnd::GetSkinFolder()
{
	return _T("");
}

//xml文件的名字
CDuiString LogInWnd::GetSkinFile()
{
	return _T("LogInWnd.xml");
}

//返回窗口类的名字：在注册窗口的时候提供
LPCTSTR LogInWnd::GetWindowClassName(void) const
{
	return _T("LogInWnd");
}

void LogInWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strName == _T("BTN_MIN"))
		{
			//使用系统自带的发送
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if(strName == _T("BTN_CLOSE"))
		{
			//点击关闭后，直接将窗口关闭
			Close();
		}
		else if (strName == _T("BTN_LOGIN"))
		{
			LogIn();
		}		
	}
}

void LogInWnd::LogIn()
{
	//从编辑框获取用户名和密码
	CEditUI* pEditUserName = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_NAME"));
	CDuiString strUserName = pEditUserName->GetText();

	CEditUI* pEditPassword = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_USER_PASSWORD"));
	CDuiString strUserPassword = pEditPassword->GetText();

	if (strUserName.IsEmpty())
	{
		MessageBox(m_hWnd, _T("请输入用户名"), _T("Cashier"), IDOK);
		return;
	}

	if (strUserPassword.IsEmpty())
	{
		MessageBox(m_hWnd, _T("请输入密码"), _T("Cashier"), IDOK);
		return;
	}
	//查询数据库，检测用户是否是合法用户


	//登录之后隐藏登录窗口
	ShowWindow(false);


	//创建登陆之后的主窗口
	MainWnd mainWnd;
	mainWnd.Create(NULL, _T("MainWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainWnd.CenterWindow();
	mainWnd.ShowModal();

	

}