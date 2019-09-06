
#include "MainWnd.h"

//xml文件对应的目录
CDuiString MainWnd::GetSkinFolder() 
{
	return _T("");
}

//xml文件的名字
CDuiString MainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

//返回窗口类的名字：在注册窗口的时候提供
LPCTSTR MainWnd::GetWindowClassName(void) const
{
	return _T("MainWnd");
}


void MainWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{		
		if (strName == _T("BTN_CLOSE"))
			Close();
		else if (strName == _T("BTN_MIN"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strName == _T("BTN_MAX"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		else if (strName == _T("BTN_SELECT"))
			MessageBox(m_hWnd, _T("SELECT"), _T("Cashier"), IDOK);
		else if (strName == _T("BTN_INSERT"))
			MessageBox(m_hWnd, _T("INSERT"), _T("Cashier"), IDOK);
		else if (strName == _T("BTN_UPDATE"))
			MessageBox(m_hWnd, _T("UPDATE"), _T("Cashier"), IDOK);
		else if (strName == _T("BTN_DELETE"))
			DeleteEmployeeInfo();
		else if (strName == _T("BTN_RECORD"))
			MessageBox(m_hWnd, _T("RECORD"), _T("Cashier"), IDOK);

		
	}

	else if (msg.sType == _T("selectchanged"))
	{
		CTabLayoutUI* pTab = (CTabLayoutUI*)m_PaintManager.FindControl(_T("TABLAYOUT_1"));
		if (strName == _T("OPTION_EMPLOYEE"))
		{
			pTab->SelectItem(0);
		}
		else
		{
			pTab->SelectItem(1);
		}
	}
	else if (msg.sType == _T("windowinit"))
	{
		CComboBoxUI* pSex = (CComboBoxUI*)m_PaintManager.FindControl(_T("USER_SEX"));
		pSex->SelectItem(0);

		CComboBoxUI* pPosition = (CComboBoxUI*)m_PaintManager.FindControl(_T("USER_POSITION"));
		pPosition->SelectItem(0);

	}


}

//
//void MainWnd::SelectEmployeeInfo()
//{
//	string strSQL("select * from employee");
//
//	CComboBoxUI* pCombo = (CComboBoxUI*)m_PaintManager.FindControl(_T("USER_SELECT"))->;
//	CDuiString strStyle = pCombo->GetText();
//	if (strStyle == _T("无"))
//		strSQL += ";";
//	else if (strStyle == _T("名字"))
//	{
//		strSQL += " where Name = '";
//		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("USE_NAME")));
//		if (strName.IsEmpty())
//		{
//			MessageBox(m_hWnd, _T("请输入查询用户的名字"), _T("Cashier"), IDOK);
//			return;
//		}
//
//		strSQL += UnicodeToANSI(strName);
//		strSQL += "';";
//	}
//	else if (strStyle == _T("性别"))
//		;
//	else if (strStyle == _T("薪资"))
//		;
//
//	vector<vector<string>> vRet = m_pMySQL->Select();
//	
//
//}
/*
void MainWnd::DeleteEmployeeInfo()
{
	// 获取当前选中的数据
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployee"));
	pListUI->RemoveAll();
	int lineNo = pListUI->GetCurSel();
	CListTextElementUI* pRow = (CListTextElementUI*)pListUI->GetItemAt(lineNo);


	// 从数据库中将该员工的信息删除
	//构造SQL命令
	string strSQL("delete ");
	
	CDuiString strName = pRow->GetText(0);

	//从数据库中将该条记录删除
	//m_pMySQL->Delete(strSQL);

	//从List中将信息移除
	pListUI->RemoveAt(lineNo);
}*/

/*
void MainWnd::InsertEmployeeInfo()
{
	//从界面中获取员工消息
	 CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("USE_NAME")))->GetText();
	 CDuiString strGender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("USER_SEX")))->GetText();
	 CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("USER_BRITHDAY")))->GetText();
	 CDuiString strPosition = ((CComboBoxUI*)m_PaintManager.FindControl(_T("USER_POSITION")))->GetText();
	 CDuiString strTel = ((CEditUI*)m_PaintManager.FindControl(_T("USER_TAL")))->GetText();
	 CDuiString strSalary = ((CEditUI*)m_PaintManager.FindControl(_T("USER_SALARY")))->GetText();

	//构造SQL命令
	 string strSQL("insert into employee values(name='");
	 strSQL += UnicodeToANSI(strName);
	 strSQL += "',Gender='";
	 strSQL += UnicodeToANSI(strGender);
	 strSQL += "',Birthday='";
	 strSQL += UnicodeToANSI(strBirthday);
	 strSQL += "',password='000000',position='";
	 strSQL += UnicodeToANSI(strPosition);
	 strSQL += "',telphone='";
	 strSQL += UnicodeToANSI(strTel);
	 strSQL += "',salary='";
	 strSQL += "');";

	//相应SQL命令
	 m_pMySQL->Insert(strSQL);

	//将员工消息插入List
	 CListTextElementUI* pItem = new CListTextElementUI;
	 CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListEmployee"));
	 pListUI->AddAt(pItem);
	 pItem->SetText(0, strName);
	 pItem->SetText(1, strGender);
	 pItem->SetText(2, strBirthday);
	 pItem->SetText(3, strPosition);
	 pItem->SetText(4, strTel);
	 pItem->SetText(5, strSalary);
}*/
