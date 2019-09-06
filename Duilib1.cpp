#if 0
#include <Windows.h> 
#include <tchar.h> //消息回调函数 
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
	switch (message) 
	{
	case WM_CLOSE: 
		if (IDOK == MessageBox(hWnd, _T("你确定退出？"), _T("退出"), MB_OKCANCEL)) 
		{ 
			DestroyWindow(hWnd); 
			return 0; 
		} 
	case WM_DESTROY: 
		PostQuitMessage(0);
		return 0; 
	default: 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{ 
	//Step1:注册一个窗口类 
	HWND hwnd; //窗口的句柄 
	WNDCLASSEX wc; //窗口类结构 
	wc.cbSize = sizeof(WNDCLASSEX); 
	wc.style = CS_VREDRAW | CS_HREDRAW; 
	wc.lpszMenuName = 0; 
	wc.lpszClassName = _T("Win32");//消息回调函数
	wc.lpfnWndProc = WinProc;  
	wc.hInstance = hInstance; 
	wc.hIcon = NULL; 
	wc.hCursor = NULL; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 
	wc.cbWndExtra = 0; 
	wc.cbClsExtra = 0;

	//注册窗口 
	wc.hIconSm = NULL; 
	RegisterClassEx(&wc); 
	//Step2:创建一个窗口 
	hwnd = CreateWindow( 

		_T("Win32"), 
		//窗口的类名，也就是上面我们自定义的窗口类的名字 
		_T("我的第一个Win32程序"), 
		//窗口的标题 
		WS_OVERLAPPEDWINDOW, //窗口style 
		500, //窗口位置x坐标 
		300, //窗口位置y坐标 
		800, //窗口宽度 
		600, //窗口高度 
		NULL, //父窗口句柄 
		NULL, //菜单句柄 
		hInstance, //实例句柄 
		NULL //创建数据 
	); 
		
	if (!hwnd)
	{
		return FALSE;
	}

	ShowWindow(hwnd, SW_SHOW); 	//显示窗口 
	UpdateWindow(hwnd); //刷新 
	
	//Step3:消息循环 
	MSG msg; while (GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}

	return 0;
}
#endif




#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif


#if  0

//duilib :本职业是win32程序，将win32的流程封装
class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	//设置窗口类的名称
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	
	//捕获消息：Duilib封装的消息
	virtual void    Notify(TNotifyUI& msg) 
	{
		//添加鼠标点击按钮消息，进行弹窗
		if (msg.sType == _T("click"))
		{
			MessageBox(NULL, _T("hello"), _T("test"), IDOK);
		}
	}

	// 拦截系统的消息
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), 
				(UINT)0, NULL, &m_PaintManager);   
			// duilib.xml需要放到exe目录下
			ASSERT(pRoot && "Failed to parse XML");

			m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this);   
			// 添加控件等消息响应，这样消息就会传达到duilib的消息循环，
			//我们可以在Notify函数里做消息处理
			return lRes;
			
#if 0
			CControlUI* pWnd = new CButtonUI;
			pWnd->SetText(_T("Duilib"));   // 设置文字
			
			// 使用光得三原色
			pWnd->SetBkColor(0xFFFF00FFFF);       // 设置背景色

			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this);//增加点击响应
			return lRes;
#endif
		}

		// 以下3个消息WM_NCACTIVATE、WM_NCCALCSIZE、WM_NCPAINT用于屏蔽系统标题栏
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if (uMsg == WM_NCCALCSIZE)
		{
			return 0;
		}
		else if (uMsg == WM_NCPAINT)
		{
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.ShowModal();
	return 0;
}
#endif 

#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma once
#include <UIlib.h>
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif


#if 0
class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const 
	{
		return _T("DUIMainFrame"); 
	}

	virtual void    Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("btnHello"))
			{
				::MessageBox(NULL, _T("我是按钮"), _T("点击了按钮"), NULL);
			}
		}
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), 
				(UINT)0, NULL, &m_PaintManager);   
			// duilib.xml需要放到exe目录下
			ASSERT(pRoot && "Failed to parse XML");

			m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this);   
			// 添加控件等消息响应，这样消息就会传达到duilib的消息循环，
			//我们可以在Notify函数里做消息处理
			return lRes;
		}

		// 以下3个消息WM_NCACTIVATE、WM_NCCALCSIZE、WM_NCPAINT用于屏蔽系统标题栏
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if (uMsg == WM_NCCALCSIZE)
		{
			return 0;
		}
		else if (uMsg == WM_NCPAINT)
		{
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());   
	// 设置资源的默认路径（此处设置为和exe在同一目录）

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();
	return 0;
}

#endif



#if 0
// 窗口对应的XML文件：用户自己写
// 使用designer图形化工具进行写：
//bug-->突然崩溃，可能会修改XML文件中的其他控件，支持常用常规的控件
class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile() { return _T("duilib.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }


	virtual void    Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender == m_PaintManager.FindControl(_T("BTN_CLOSE")))
			{
				MessageBox(NULL, _T("Test"), _T("hello"), IDOK);
				Close();
			}
			else if (msg.pSender == m_PaintManager.FindControl(_T("BTN_MIN")))
			{
				//MessageBox(NULL, _T("Test"), _T("hello"), IDOK);
			}
			
		}
	}

};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();//生成的是模态对话框,
	//duiFrame.ShowWindow();//生成的是普通的对话框
	
	return 0;
}
#endif


#include "MainWnd.h"
#include "login.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	LogInWnd LogInWnd;
	LogInWnd.Create(NULL, _T("LogInWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	LogInWnd.CenterWindow();
	LogInWnd.ShowModal();//生成的是模态对话框,
	//duiFrame.ShowWindow();//生成的是普通的对话框

	//CPaintManagerUI::SetInstance(hInstance);
	//MainWnd duiFrame;
	//duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//duiFrame.CenterWindow();
	//duiFrame.ShowModal();//生成的是模态对话框,
	////duiFrame.ShowWindow();//生成的是普通的对话框

	return 0;
}


