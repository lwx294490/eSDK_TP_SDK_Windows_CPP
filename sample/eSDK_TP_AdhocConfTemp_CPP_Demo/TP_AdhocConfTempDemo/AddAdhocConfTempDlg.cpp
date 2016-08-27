// AddAdhocConfTempDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_AdhocConfTempDemo.h"
#include "AddAdhocConfTempDlg.h"
#include "afxdialogex.h"


// CAddAdhocConfTempDlg dialog

IMPLEMENT_DYNAMIC(CAddAdhocConfTempDlg, CPropertyPage)

CAddAdhocConfTempDlg::CAddAdhocConfTempDlg()
	: CPropertyPage(CAddAdhocConfTempDlg::IDD)
{

}

CAddAdhocConfTempDlg::~CAddAdhocConfTempDlg()
{
}

void CAddAdhocConfTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editAdhocConfTempName);
	DDX_Control(pDX, IDC_EDIT2, m_editAdhocConfTempAccessCode);
	DDX_Control(pDX, IDC_EDIT3, m_editAdhocConfTempDuration);
	DDX_Control(pDX, IDC_EDIT6, m_editAdhocConfTempBillCode);
	DDX_Control(pDX, IDC_EDIT4, m_editAdhocConfTempPassword);
	DDX_Control(pDX, IDC_EDIT5, m_editAdhocConfTempMaxSitesCount);
	DDX_Control(pDX, IDC_EDIT7, m_editAdhocConfTempMainSiteUri);
	DDX_Control(pDX, IDC_EDIT8, m_editAdhocConfTempChairmanPassword);
	DDX_Control(pDX, IDC_EDIT9, m_editAdhocConfTempEmail);
	DDX_Control(pDX, IDC_EDIT10, m_editAdhocConfTempContent);
	DDX_Control(pDX, IDC_EDIT11, m_editAdhocConfTempTelephone);
	DDX_Control(pDX, IDC_EDIT12, m_editAdhocConfTempReservedCsdPorts);
	DDX_Control(pDX, IDC_COMBO3, m_cbbAdhocConfTempCpResouce);
	DDX_Control(pDX, IDC_COMBO4, m_cbbAdhocConfTempMediaEncryptType);
	DDX_Control(pDX, IDC_COMBO1, m_cbbAdhocConfTempRate);
	DDX_Control(pDX, IDC_COMBO2, m_cbbAdhocConfTempIsLiveBroadcast);
	DDX_Control(pDX, IDC_COMBO5, m_cbbAdhocConfTempIsRecording);
	DDX_Control(pDX, IDC_COMBO6, m_cbbAdhocConfTempPresentation);
	DDX_Control(pDX, IDC_COMBO7, m_cbbAdhocConfTempVideoFormat);
	DDX_Control(pDX, IDC_COMBO8, m_cbbAdhocConfTempVideoProtocol);
	DDX_Control(pDX, IDC_COMBO9, m_cbbAdhocConfTempState);
	DDX_Control(pDX, IDC_LIST1, m_listAllSites);
}


BEGIN_MESSAGE_MAP(CAddAdhocConfTempDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddAdhocConfTempDlg::OnBnClickedButton1)
	//ON_NOTIFY(NM_CLICK, IDC_LIST1, &CAddAdhocConfTempDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &CAddAdhocConfTempDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddAdhocConfTempDlg message handlers


BOOL CAddAdhocConfTempDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editAdhocConfTempDuration.SetWindowText("120");

	m_cbbAdhocConfTempCpResouce.AddString("1");
	m_cbbAdhocConfTempCpResouce.AddString("2");
	m_cbbAdhocConfTempCpResouce.AddString("3");
	m_cbbAdhocConfTempCpResouce.AddString("4");
	m_cbbAdhocConfTempCpResouce.AddString("5");
	m_cbbAdhocConfTempCpResouce.AddString("6");
	m_cbbAdhocConfTempCpResouce.AddString("7");
	m_cbbAdhocConfTempCpResouce.AddString("8");
	m_cbbAdhocConfTempCpResouce.SetCurSel(1);

	m_cbbAdhocConfTempMediaEncryptType.AddString("AutoEncrypt(�Զ�Э��)");
	m_cbbAdhocConfTempMediaEncryptType.AddString("ForceEncrypt(ǿ�Ƽ���)");
	m_cbbAdhocConfTempMediaEncryptType.AddString("None(������)");
	m_cbbAdhocConfTempMediaEncryptType.SetCurSel(2);

	m_cbbAdhocConfTempRate.AddString("64kbit/s");
	m_cbbAdhocConfTempRate.AddString("128kbit/s");
	m_cbbAdhocConfTempRate.AddString("256kbit/s");
	m_cbbAdhocConfTempRate.AddString("512kbit/s");
	m_cbbAdhocConfTempRate.AddString("1Mbit/s");
	m_cbbAdhocConfTempRate.AddString("2Mbit/s");
	m_cbbAdhocConfTempRate.AddString("4Mbit/s");
	m_cbbAdhocConfTempRate.AddString("8Mbit/s");
	m_cbbAdhocConfTempRate.SetCurSel(5);

	m_cbbAdhocConfTempIsLiveBroadcast.AddString("��֧��");
	m_cbbAdhocConfTempIsLiveBroadcast.AddString("֧��");
	m_cbbAdhocConfTempIsLiveBroadcast.SetCurSel(0);

	m_cbbAdhocConfTempIsRecording.AddString("��֧��");
	m_cbbAdhocConfTempIsRecording.AddString("֧��");
	m_cbbAdhocConfTempIsRecording.SetCurSel(0);

	m_cbbAdhocConfTempPresentation.AddString("��Ƭ��ʾ��ʽ");
	m_cbbAdhocConfTempPresentation.AddString("�ͼ��ʽ");
	m_cbbAdhocConfTempPresentation.AddString("��֧��");
	m_cbbAdhocConfTempPresentation.SetCurSel(2);

	m_cbbAdhocConfTempVideoFormat.AddString("Auto");
	m_cbbAdhocConfTempVideoFormat.AddString("QCIF");
	m_cbbAdhocConfTempVideoFormat.AddString("CIF");
	m_cbbAdhocConfTempVideoFormat.AddString("SQCIF");
	m_cbbAdhocConfTempVideoFormat.AddString("CIF2");
	m_cbbAdhocConfTempVideoFormat.AddString("CIF4");
	m_cbbAdhocConfTempVideoFormat.AddString("P720");
	m_cbbAdhocConfTempVideoFormat.AddString("P1080");
	m_cbbAdhocConfTempVideoFormat.AddString("I1080");
	m_cbbAdhocConfTempVideoFormat.AddString("P480");
	m_cbbAdhocConfTempVideoFormat.AddString("I480");
	m_cbbAdhocConfTempVideoFormat.AddString("P720_60f");
	m_cbbAdhocConfTempVideoFormat.AddString("P1080_60f");
	m_cbbAdhocConfTempVideoFormat.AddString("P360");
	m_cbbAdhocConfTempVideoFormat.AddString("VGA");
	m_cbbAdhocConfTempVideoFormat.SetCurSel(0);

	m_cbbAdhocConfTempVideoProtocol.AddString("Auto");
	m_cbbAdhocConfTempVideoProtocol.AddString("H.261Э��");
	m_cbbAdhocConfTempVideoProtocol.AddString("H.263Э��");
	m_cbbAdhocConfTempVideoProtocol.AddString("H.264Э��");
	m_cbbAdhocConfTempVideoProtocol.AddString("H264HP");
	m_cbbAdhocConfTempVideoProtocol.AddString("H265");
	m_cbbAdhocConfTempVideoProtocol.SetCurSel(0);

	m_cbbAdhocConfTempState.AddString("RegGkFailed");
	m_cbbAdhocConfTempState.AddString("RegGkSuccess");
	m_cbbAdhocConfTempState.AddString("NotNeedReg");
	m_cbbAdhocConfTempState.SetCurSel(2);

	m_listAllSites.ModifyStyle(0,LVS_REPORT);
	DWORD dwStyle = m_listAllSites.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listAllSites.SetExtendedStyle(dwStyle); // ������չ��� 
	m_listAllSites.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(1,"����",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(2,"����",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(3,"����",LVCFMT_CENTER,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddAdhocConfTempDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateSiteList();
}

void CAddAdhocConfTempDlg::UpdateSiteList()
{
	m_allSitesInfo.clear();
	m_listAllSites.DeleteAllItems();

	TPSDKResponseEx<list<SiteInfoEx>> siteList = querySitesEx();
	if (siteList.resultCode==0)
	{
		int j=0;
		list<SiteInfoEx>::iterator i; 
		for (i = siteList.result.begin(); i != siteList.result.end(); ++i) 
		{
			m_allSitesInfo.push_back(*i);
			m_listAllSites.InsertItem(j,i->uri.c_str());
			m_listAllSites.SetItemText(j,1,i->name.c_str());
			CString str;
			str.Format("%d",i->type);
			m_listAllSites.SetItemText(j,2,str);
			str.Format("%s",i->rate.c_str());
			m_listAllSites.SetItemText(j,3,str);
			j++;
		}
	}
	else
	{
		CString cstrErrMsg; 
		cstrErrMsg.Format("��ȡ�᳡�б�ʧ�ܣ������룺%d",siteList.resultCode);
		AfxMessageBox(cstrErrMsg);
	}
}

void CAddAdhocConfTempDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listAllSites.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listAllSites.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllSites.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_listAllSites.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllSites.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}
	*pResult = 0;
}


void CAddAdhocConfTempDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	std::string strOrgId = "1";
	AdhocConfTemplateParamEx adhocConfTemplate;
	adhocConfTemplate.adhocConfTemplateId = "0";
	CString cstrTemp;
	//������
	if ( m_editAdhocConfTempName.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempName.GetWindowText(cstrTemp);
		adhocConfTemplate.name = cstrTemp.Trim().GetBuffer();
	}
	else
	{
		AfxMessageBox(_T("����������Ϊ��"));
		return;
	}
	//���鼤����
	if ( m_editAdhocConfTempAccessCode.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempAccessCode.GetWindowText(cstrTemp);
		adhocConfTemplate.accessCode = cstrTemp.Trim().GetBuffer();
	}
	else
	{
		AfxMessageBox(_T("���鼤���벻��Ϊ��"));
		return;
	}
	//����ʱ��
	if ( m_editAdhocConfTempDuration.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempDuration.GetWindowText(cstrTemp);
		int minutes = atoi(cstrTemp.Trim().GetBuffer());
		int hours = minutes / 60;
		minutes = minutes - hours * 60;
		cstrTemp.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
		adhocConfTemplate.duration = cstrTemp.GetBuffer();
	}
	//�Ʒ���
	if ( m_editAdhocConfTempBillCode.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempBillCode.GetWindowText(cstrTemp);
		adhocConfTemplate.billCode = cstrTemp.Trim().GetBuffer();
	}
	//����
	if (m_editAdhocConfTempPassword.GetWindowTextLength() > 0)
	{
		m_editAdhocConfTempPassword.GetWindowText(cstrTemp);
		adhocConfTemplate.password = cstrTemp.Trim().GetBuffer();
	}
	//�໭����Դ��
	adhocConfTemplate.cpResouce = m_cbbAdhocConfTempCpResouce.GetCurSel() + 1;
	//����
	m_cbbAdhocConfTempRate.GetLBText( m_cbbAdhocConfTempRate.GetCurSel(), cstrTemp );
	adhocConfTemplate.rate = cstrTemp.Trim().GetBuffer();
	//��ý����ܷ�ʽ
	adhocConfTemplate.mediaEncryptType = m_cbbAdhocConfTempMediaEncryptType.GetCurSel();
	//֧��ֱ��
	adhocConfTemplate.isLiveBroadcast = m_cbbAdhocConfTempIsLiveBroadcast.GetCurSel();
	//֧��¼��
	adhocConfTemplate.isRecording = m_cbbAdhocConfTempIsRecording.GetCurSel();
	//�����᷽��
	if ( m_editAdhocConfTempMaxSitesCount.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempMaxSitesCount.GetWindowText(cstrTemp);
		adhocConfTemplate.maxSitesCount = atoi(cstrTemp.Trim());
	}
	//�᳡�б�
	vector<int> indexTemp;
	for (int i=0; i<m_listAllSites.GetItemCount(); i++)
	{
		if(m_listAllSites.GetCheck(i)) 
		{ 
			indexTemp.push_back(i);
		} 
	}
	for ( unsigned int j = 0; j<indexTemp.size(); j++ )
	{
		adhocConfTemplate.sites.push_back( m_allSitesInfo[ indexTemp[j] ] );
	}
	//��ϯ�᳡
	if ( m_editAdhocConfTempMainSiteUri.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempMainSiteUri.GetWindowText(cstrTemp);
		adhocConfTemplate.mainSiteUri = cstrTemp.Trim().GetBuffer();
	}
	//��ϯ����
	if ( m_editAdhocConfTempChairmanPassword.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempChairmanPassword.GetWindowText(cstrTemp);
		adhocConfTemplate.chairmanPassword = cstrTemp.Trim().GetBuffer();
	}
	//��ʾ��ʽ
	adhocConfTemplate.presentation = m_cbbAdhocConfTempPresentation.GetCurSel();
	//������Ƶ��ʽ
	adhocConfTemplate.presentationVideo.videoFormat = m_cbbAdhocConfTempVideoFormat.GetCurSel();
	//������ƵЭ��
	adhocConfTemplate.presentationVideo.videoProtocol = m_cbbAdhocConfTempVideoProtocol.GetCurSel();
	//����
	if ( m_editAdhocConfTempEmail.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempEmail.GetWindowText(cstrTemp);
		adhocConfTemplate.notice.email = cstrTemp.Trim().GetBuffer();
	}
	//֪ͨ����
	if ( m_editAdhocConfTempContent.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempContent.GetWindowText(cstrTemp);
		adhocConfTemplate.notice.content = cstrTemp.Trim().GetBuffer();
	}
	//�绰
	if ( m_editAdhocConfTempTelephone.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempTelephone.GetWindowText(cstrTemp);
		adhocConfTemplate.notice.telephone = cstrTemp.Trim().GetBuffer();
	}
	//ע��״̬
	adhocConfTemplate.state = m_cbbAdhocConfTempState.GetCurSel();
	//��������ͨ����
	if ( m_editAdhocConfTempReservedCsdPorts.GetWindowTextLength() > 0 )
	{
		m_editAdhocConfTempReservedCsdPorts.GetWindowText(cstrTemp);
		adhocConfTemplate.reservedCsdPorts = atoi(cstrTemp.Trim());
	}
	TPSDKResponseEx<std::string> response = addAdhocConfTemplateEx( strOrgId, adhocConfTemplate );
	if ( 0 == response.resultCode )
	{
		CString cstrMsg; 
		cstrMsg.Format("��������ģ��ɹ���ģ��ID��%s",response.result.c_str());
		AfxMessageBox(cstrMsg);
	} 
	else
	{
		CString cstrErrMsg; 
		cstrErrMsg.Format("��������ģ��ʧ�ܣ������룺%d",response.resultCode);
		AfxMessageBox(cstrErrMsg);
	}
}
