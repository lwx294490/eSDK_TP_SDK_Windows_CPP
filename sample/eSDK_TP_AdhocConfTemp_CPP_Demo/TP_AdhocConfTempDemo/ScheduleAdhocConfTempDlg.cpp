// ScheduleAdhocConfTempDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_AdhocConfTempDemo.h"
#include "ScheduleAdhocConfTempDlg.h"
#include "afxdialogex.h"
#include <iterator>

// CScheduleAdhocConfTempDlg dialog

IMPLEMENT_DYNAMIC(CScheduleAdhocConfTempDlg, CPropertyPage)

CScheduleAdhocConfTempDlg::CScheduleAdhocConfTempDlg()
	: CPropertyPage(CScheduleAdhocConfTempDlg::IDD)
{
	m_choosedAdhocConfTempItem = -1;
}

CScheduleAdhocConfTempDlg::~CScheduleAdhocConfTempDlg()
{
}

void CScheduleAdhocConfTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listAllAdhocConfTemp);
}


BEGIN_MESSAGE_MAP(CScheduleAdhocConfTempDlg, CPropertyPage)
	ON_BN_CLICKED(IDOK, &CScheduleAdhocConfTempDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CScheduleAdhocConfTempDlg::OnNMClickList2)
	ON_BN_CLICKED(IDCANCEL, &CScheduleAdhocConfTempDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CScheduleAdhocConfTempDlg::OnNMRClickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CScheduleAdhocConfTempDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST2, &CScheduleAdhocConfTempDlg::OnNMRDblclkList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CScheduleAdhocConfTempDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CScheduleAdhocConfTempDlg message handlers


BOOL CScheduleAdhocConfTempDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listAllAdhocConfTemp.ModifyStyle(0,LVS_REPORT);
	DWORD dwStyle = m_listAllAdhocConfTemp.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listAllAdhocConfTemp.SetExtendedStyle(dwStyle); // ������չ��� 
	m_listAllAdhocConfTemp.InsertColumn(0,"ģ��ID",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemp.InsertColumn(1,"ģ������",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemp.InsertColumn(2,"���鼤����",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemp.InsertColumn(3,"����ʱ��",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemp.InsertColumn(4,"����",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemp.InsertColumn(5,"�໭��",LVCFMT_CENTER,80,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CScheduleAdhocConfTempDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	getAllAdhocConfTempList();
	showAllAdhocConfTempList();
}


void CScheduleAdhocConfTempDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//��ȡ�������ڵ��к�   
	//�ҳ����λ��   
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listAllAdhocConfTemp.ScreenToClient(&point);  
	//����ṹ��   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ   
	int nItem = m_listAllAdhocConfTemp.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//�ж��Ƿ�����CheckBox��   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_list2BeHit = TRUE;  
			m_list2ItemSel = lvinfo.iItem;   //��ǰ�к�   
		}
	}
	*pResult = 0;
}

void CScheduleAdhocConfTempDlg::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//��ȡ�������ڵ��к�   
	//�ҳ����λ��   
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listAllAdhocConfTemp.ScreenToClient(&point);  
	//����ṹ��   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ   
	int nItem = m_listAllAdhocConfTemp.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//�ж��Ƿ�����CheckBox��   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_list2BeHit = TRUE;  
			m_list2ItemSel = lvinfo.iItem;   //��ǰ�к�   
		}
	}
	*pResult = 0;
}

void CScheduleAdhocConfTempDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	list<AdhocConfTemplateParamEx>::iterator iter = getChoosedAdhocConfTemplate();
	if ( iter != m_listAllAdhocConferencesTemplate.end() )
	{
		ConferenceInfoEx scheduleConf;
		scheduleConf.name = iter->name;
		CTime m_time;
		m_time=CTime::GetCurrentTime(); //��ȡ��ǰʱ������  
		m_time.GetAsSystemTime(scheduleConf.beginTime);
		scheduleConf.duration = iter->duration;
		scheduleConf.accessCode = iter->accessCode;
		scheduleConf.password = iter->password;
		scheduleConf.mediaEncryptType = iter->mediaEncryptType;
		scheduleConf.auxVideoFormat = iter->presentationVideo.videoFormat;
		scheduleConf.auxVideoProtocol = iter->presentationVideo.videoProtocol;
		scheduleConf.cpResouce = iter->cpResouce;
		scheduleConf.rate = iter->rate;
		scheduleConf.isRecording = iter->isRecording;
		scheduleConf.isLiveBroadcast = iter->isLiveBroadcast;
		scheduleConf.presentation = iter->presentation;
		scheduleConf.chairmanPassword = iter->chairmanPassword;
		scheduleConf.billCode = iter->billCode;
		scheduleConf.mainSiteUri = iter->mainSiteUri;
		scheduleConf.conferenceNotice = iter->notice;
		std::copy(iter->sites.begin(), iter->sites.end(), std::back_inserter(scheduleConf.sites));	
		scheduleConf.maxSitesCount = iter->maxSitesCount;
		TPSDKResponseEx<ConferenceInfoEx> result = scheduleConfEx( scheduleConf );
		if ( 0 == result.resultCode )
		{
			CString cstrMsg;
			cstrMsg.Format("�������ɹ�������ID��%s", result.result.confId.c_str());
			AfxMessageBox(cstrMsg);
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format("�������ʧ�ܣ������룺%d", result.resultCode);
			AfxMessageBox(cstrMsg);
		}
	}
	else
	{
		AfxMessageBox("����ѡ�����");
	}
}

list<AdhocConfTemplateParamEx>::iterator CScheduleAdhocConfTempDlg::getChoosedAdhocConfTemplate()
{
	if ( -1 != m_choosedAdhocConfTempItem )
	{
		std::string cstrTempId = m_listAllAdhocConfTemp.GetItemText(m_choosedAdhocConfTempItem, 0).GetBuffer();
		for ( list<AdhocConfTemplateParamEx>::iterator iter = m_listAllAdhocConferencesTemplate.begin(); iter != m_listAllAdhocConferencesTemplate.end(); ++iter )
		{
			if ( cstrTempId == iter->adhocConfTemplateId )
			{
				return iter;
			}
		}
	}
	return m_listAllAdhocConferencesTemplate.end();
}

void CScheduleAdhocConfTempDlg::getAllAdhocConfTempList()
{
	m_listAllAdhocConfTemp.DeleteAllItems();
	m_listAllAdhocConferencesTemplate.clear();
	m_choosedAdhocConfTempItem = -1;
	int iCurrentPage = 1;
	bool bContinueLoop = true;
	do 
	{
		QueryConfigEx queryConfig;
		SortItemEx sortItemEx;
		sortItemEx.itemIndex = 4;		//������ģ�����������
		sortItemEx.sort = 0;
		queryConfig.sortItems.push_back(sortItemEx);
		queryConfig.focusItem = 1;
		queryConfig.pageParam.currentPage = iCurrentPage;
		queryConfig.pageParam.numberPerPage = 10;

		StringFilterEx stringFilterEx;
		stringFilterEx.columnIndex = 4;
		stringFilterEx.value = "";
		queryConfig.filters.push_back(stringFilterEx);
		TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> response = queryAdhocConfTemplateListEx( queryConfig );
		if ( 0 == response.resultCode )
		{
			m_listAllAdhocConferencesTemplate.splice(m_listAllAdhocConferencesTemplate.end(), response.result);
			if ( iCurrentPage >= response.pagesInfo.totalPages )
			{
				bContinueLoop = false;
			} 
			else
			{
				iCurrentPage++;
			}
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format("��ѯAdhoc����ģ����󣬷����룺%d", response.resultCode);
			AfxMessageBox(cstrMsg);
			bContinueLoop = false;
			return;
		}
	} while ( true == bContinueLoop);
}

void CScheduleAdhocConfTempDlg::showAllAdhocConfTempList()
{
	if ( m_listAllAdhocConferencesTemplate.size() > 0 )
	{
		int iTemplateCount = m_listAllAdhocConfTemp.GetItemCount();
		for ( list<AdhocConfTemplateParamEx>::reverse_iterator iter = m_listAllAdhocConferencesTemplate.rbegin(); iter != m_listAllAdhocConferencesTemplate.rend(); ++iter )
		{
			m_listAllAdhocConfTemp.InsertItem( iTemplateCount, iter->adhocConfTemplateId.c_str() );
			m_listAllAdhocConfTemp.SetItemText( iTemplateCount, 1, iter->name.c_str() );
			m_listAllAdhocConfTemp.SetItemText( iTemplateCount, 2, iter->accessCode.c_str() );
			m_listAllAdhocConfTemp.SetItemText( iTemplateCount, 3, iter->duration.c_str() );
			m_listAllAdhocConfTemp.SetItemText( iTemplateCount, 4, iter->rate.c_str() );
			CString cstrTemp;
			cstrTemp.Format("%d", iter->cpResouce);
			m_listAllAdhocConfTemp.SetItemText( iTemplateCount, 4, cstrTemp );
		}
	} 
}




void CScheduleAdhocConfTempDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//��ȡ�������ڵ��к�   
	//�ҳ����λ��   
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listAllAdhocConfTemp.ScreenToClient(&point);  
	//����ṹ��   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ   
	int nItem = m_listAllAdhocConfTemp.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//�ж��Ƿ�����CheckBox��   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_list2BeHit = TRUE;  
			m_list2ItemSel = lvinfo.iItem;   //��ǰ�к�   
		}
	}
	*pResult = 0;
}


void CScheduleAdhocConfTempDlg::OnNMRDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//��ȡ�������ڵ��к�   
	//�ҳ����λ��   
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listAllAdhocConfTemp.ScreenToClient(&point);  
	//����ṹ��   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ   
	int nItem = m_listAllAdhocConfTemp.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//�ж��Ƿ�����CheckBox��   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_list2BeHit = TRUE;  
			m_list2ItemSel = lvinfo.iItem;   //��ǰ�к�   
		}
	}
	*pResult = 0;
}


void CScheduleAdhocConfTempDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int ibak = -1;
	if(TRUE == m_list2BeHit)  
	{  
		m_list2BeHit = FALSE;     //��λ   

		if(TRUE == m_listAllAdhocConfTemp.GetCheck(m_list2ItemSel))  
		{       //CheckBox��ѡ��   
			//do your own processing  
			ibak = m_choosedAdhocConfTempItem;
			m_choosedAdhocConfTempItem = m_list2ItemSel;
			m_listAllAdhocConfTemp.SetItemState(m_list2ItemSel, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
		}  
		else  
		{      //CheckBoxȡ��ѡ��   
			//do your own processing 
			int iBAK = m_choosedAdhocConfTempItem;
			m_choosedAdhocConfTempItem = -1;
		}  
	}  
	if ( -1 != ibak)
	{
		m_listAllAdhocConfTemp.SetCheck( ibak, FALSE );
	}
}
