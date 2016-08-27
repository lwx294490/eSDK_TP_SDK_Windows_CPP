/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#include "stdafx.h"
#include "TP_Native_Xml.h"


bool CXml::m_bFistInit = true;
bool CXml::m_bCondenseWhiteSpace = true;

CXml::CXml(const char *pszFileName)
    : m_pXMlDoc(NULL)
    , m_pXmlNode(NULL)
    , m_pXmlElem(NULL)
    , m_pszFileName(pszFileName)
    , m_strStream()
    , m_pBaseXmlNode(NULL)
    , m_pBaseXmlElem(NULL)
{
	// ȡ���ո�����,������ֻ���ڵ�һ��ʹ��xml��ʱ�����
	if (m_bFistInit)
	{
		TiXmlBase::SetCondenseWhiteSpace(m_bCondenseWhiteSpace);
		m_bFistInit = false;
	}	
}

CXml::~CXml()
{
    m_pXmlNode = NULL;
    m_pXmlElem = NULL;
    m_pszFileName = NULL;
	m_pBaseXmlNode = NULL;
	m_pBaseXmlElem = NULL;
	SAFE_DELETE(m_pXMlDoc);
}

bool CXml::SetCondenseWhiteSpace(bool bCondenseWhiteSpace)
{
	//���Ѿ���ʼ�����ˣ�����������
	if (!m_bFistInit)
	{
		return false;
	}
	m_bCondenseWhiteSpace = bCondenseWhiteSpace;
	return true;
}

bool CXml::IsWhiteSpaceCondensed()
{
	return m_bCondenseWhiteSpace;
}

/**************************************************************************
* name       : Load
* description: ����һ��xml�ļ�
* input      : NA
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::Load(TiXmlEncoding encode)
{
    CHECK_POINTER(m_pszFileName, false);

    SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774

    // �ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER(m_pXMlDoc, false); //lint !e774

    if (m_pXMlDoc->LoadFile(m_pszFileName, encode))
    {
        GetRootPos();

        return true;
    }
	
    return false;
}

/**************************************************************************
* name       : Load
* description: ����һ��xml�ļ�
* input      : pszFileName ���ص��ļ���
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::Load(const char *pszFileName, TiXmlEncoding encode)
{
    CHECK_POINTER(pszFileName, false);

    m_pszFileName = pszFileName;
	
    return Load(encode);
}

/**************************************************************************
* name       : Parse
* description: ����һ��xml����xml�ļ�
* input      : pszStream xml��
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::Parse(const char *pszStream, TiXmlEncoding encode)
{
    CHECK_POINTER(pszStream, false);

    //songyiqun
	SAFE_DELETE(m_pXMlDoc);
    SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774

    CHECK_POINTER(m_pXMlDoc, false);//lint !e774

    //TIXML_ENCODING_LEGACYΪTinyxmlʹ�õı��뷽ʽ
    (void)(m_pXMlDoc->Parse(pszStream, NULL, encode));
    if (0 != m_pXMlDoc->Error())
    {
        return false;
    }

    GetRootPos();

    return true;
}

/**************************************************************************
* name       : Save
* description: �洢xml�ļ�
* input      : pszFileName �洢���ļ���
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::Save(const char *pszFileName)
{
    CHECK_POINTER(pszFileName, false);

    m_pszFileName = pszFileName;
	
    return Save();
}

/**************************************************************************
* name       : Save
* description: �洢xml�ļ�
* input      : NA
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : ��Load(const char *pszFileName)���ʹ��
**************************************************************************/
bool CXml::Save()
{
    CHECK_POINTER(m_pszFileName, false);

    //SAFE_NEW(m_pXMlDoc, TiXmlDocument);

    CHECK_POINTER(m_pXMlDoc, false);//lint !e774
	
    return m_pXMlDoc->SaveFile(m_pszFileName);
}//lint !e1762

/**************************************************************************
* name       : Print
* description: ��Win32ƽ̨��ӡ��xml�ļ�
* input      : NA
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::Print() const
{
    CHECK_POINTER_VOID(m_pXMlDoc);

    // m_pXMlDoc->Print(stdout); ȥ��XML ��ӡ����ӡ���ײ��������쳣
}

/**************************************************************************
* name       : AddElem
* description: ���Ԫ��
* input      : pszElemName ����ӵ�Ԫ����
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::AddElem(const char *pszElemName)
{
    CHECK_POINTER(pszElemName, false);

    //Tinyxml��������е�������ڴ棬����Ҫ������delete
    TiXmlElement *pXmlAddElem = NULL;
    try
    {
        pXmlAddElem = new TiXmlElement(pszElemName);
    }
    catch (...)
    {
        pXmlAddElem = NULL;

        return false;//lint !e438
    }
    CHECK_POINTER(pXmlAddElem, false);//lint !e774

    if (NULL == m_pXmlNode)
    {
        if (NULL == m_pXMlDoc)
        {
            SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774
        }

        CHECK_POINTER(m_pXMlDoc, false);//lint !e774
        (void)(m_pXMlDoc->LinkEndChild(pXmlAddElem));
        GetRootPos();

        return true;
    }

    m_pXmlNode = m_pXmlNode->Parent();

	CHECK_POINTER(m_pXmlNode,false);

    // �ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER(m_pXmlNode, false); //lint !e774

    (void)(m_pXmlNode->LinkEndChild(pXmlAddElem));
    
	m_pXmlNode = m_pXmlNode->LastChild();
	CHECK_POINTER(m_pXmlNode,false);

    m_pXmlElem = pXmlAddElem;

    return true;
}

/**************************************************************************
* name       : AddElemBeforeCurNode
* description: �ڵ�ǰ�ڵ�ǰ���Ԫ��
* input      : pszElemName ����ӵ�Ԫ����
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::AddElemBeforeCurNode(const char *pszElemName)
{
	CHECK_POINTER(pszElemName, false);

	//Tinyxml��������е�������ڴ棬����Ҫ������delete
	TiXmlElement *pXmlAddElem = NULL;
	try
	{
		pXmlAddElem = new TiXmlElement(pszElemName);
	}
	catch (...)
	{
		pXmlAddElem = NULL;

		return false;//lint !e438
	}
    CHECK_POINTER(pXmlAddElem, false);//lint !e774

	if (NULL == m_pXmlNode)
	{
		if (NULL == m_pXMlDoc)
		{
			SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774
		}

		CHECK_POINTER(m_pXMlDoc, false);//lint !e774
		(void)(m_pXMlDoc->LinkEndChild(pXmlAddElem));
		GetRootPos();

		return true;
	}

	// �ж�ָ���Ƿ�Ϊ��
	CHECK_POINTER(m_pXmlNode, false); //lint !e774

	TiXmlNode *pParent = m_pXmlNode->Parent();

	CHECK_POINTER(pParent,false);	

	TiXmlNode *pXmlNode = pParent->InsertBeforeChild(m_pXmlNode,(*pXmlAddElem));

	if (NULL == pXmlNode)
	{
		return false;
	}
	m_pXmlNode = pXmlNode;
	m_pXmlElem = m_pXmlNode->ToElement();

	return true;
}

/**************************************************************************
* name       : AddChildElem
* description: �����Ԫ��
* input      : pszElemName ����ӵ���Ԫ����
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::AddChildElem(const char *pszElemName)
{
    CHECK_POINTER(pszElemName, false);

    CHECK_POINTER(m_pXmlElem, false);

    //Tinyxml��������е�������ڴ棬����Ҫ������delete
    TiXmlElement *pXmlElem = NULL;
    try
    {
        pXmlElem = new TiXmlElement(pszElemName);
    }
    catch (...)
    {
        pXmlElem = NULL;

        return false;//lint !e438
    }
    CHECK_POINTER(pXmlElem, false);//lint !e774

    (void)(m_pXmlElem->LinkEndChild(pXmlElem));

    return true;//lint !e429
}

/**************************************************************************
* name       : SetElemValue
* description: �趨��ǰԪ��ֵ
* input      : pszElemValue ���趨��Ԫ��ֵ
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::SetElemValue(const char* pszElemValue)
{
    CHECK_POINTER(pszElemValue, false);

    CHECK_POINTER(m_pXmlElem, false);

    //Tinyxml��������е�������ڴ棬����Ҫ������delete
    TiXmlText *pXmlText = NULL;

    try
    {
        pXmlText = new TiXmlText(pszElemValue);
    }
    catch (...)
    {
        pXmlText = NULL;

        return false;//lint !e438
    }
    CHECK_POINTER(pXmlText, false);//lint !e774

    (void)(m_pXmlElem->LinkEndChild(pXmlText));

    return true;//lint !e429
}


/**************************************************************************
* name       : SetElemValueCDATA
* description: �趨��ǰԪ��ֵ <![CDATA[ElemValue]]>
* input      : pszElemValue ���趨��Ԫ��ֵ
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::SetElemValueCDATA(const char* pszElemValue)
{
    CHECK_POINTER(pszElemValue, false);
    CHECK_POINTER(m_pXmlElem, false);

    TiXmlText *pXmlText = NULL;

    try
    {
        pXmlText = new TiXmlText(pszElemValue);
        CHECK_POINTER(pXmlText, false);//lint !e774
        pXmlText->SetCDATA(true);  // ���ø��ı�ΪCDATA,�������
    }
    catch (...)
    {
        pXmlText = NULL;
        return false;//lint !e438
    }
    CHECK_POINTER(pXmlText, false);//lint !e774

    (void)(m_pXmlElem->LinkEndChild(pXmlText));
    return true;//lint !e429
}

/**************************************************************************
* name       : GetElemValue
* description: ��ȡ��ǰԪ��ֵ
* input      : NA
* output     : NA
* return     : const char*
* remark     : NA
**************************************************************************/
const char* CXml::GetElemValue() const
{
    CHECK_POINTER(m_pXmlElem, NULL);

	const char * pRet = m_pXmlElem->GetText();
	if (NULL == pRet)
	{
		return "";//����ҵ��ǿգ�������ʱ�Ŀմ�
	}
    return pRet;
}

/**************************************************************************
* name       : GetElem
* description: ��ȡ��ǰԪ��
* input      : NA
* output     : NA
* return     : const char*
* remark     : NA
**************************************************************************/
const char* CXml::GetElem()
{
    if (NULL == m_pXmlNode)
    {
        return NULL;
    }

    //����Ԫ��������
    //NULLָ��ǰ�ڵ㲻��Ԫ�أ������Ǽ������²���
    TiXmlNode *pXmlNode = NULL;
    while (NULL == m_pXmlNode->ToElement())
    {
        pXmlNode = m_pXmlNode->NextSibling();
        if (NULL == pXmlNode)
        {
            return NULL;
        }

        m_pXmlNode = pXmlNode;
    }

    m_pXmlElem = m_pXmlNode->ToElement();

    // �ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER(m_pXmlNode, NULL); //lint !e774

    return m_pXmlNode->Value();
}

/**************************************************************************
* name       : IntoElem
* description: ������һ��
* input      : NA
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::IntoElem()
{
    CHECK_POINTER(m_pXmlNode, false);

    if ((NULL == m_pXmlNode->FirstChild())
        || m_pXmlNode->FirstChild()->ToText())
    {
        return false;
    }

    m_pXmlNode = m_pXmlNode->FirstChild();
    m_pXmlElem = m_pXmlNode->ToElement();

    return true;
}

/**************************************************************************
* name       : OutOfElem
* description: �˳�����һ��
* input      : NA
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::OutOfElem()
{
    CHECK_POINTER_VOID (m_pXmlNode);

    m_pXmlNode = m_pXmlNode->Parent();
    m_pXmlElem = m_pXmlNode->ToElement();
}

/**************************************************************************
* name       : FindElem
* description: ����Ԫ��
* input      : pszElemName �����ҵ�Ԫ����
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::FindElem(const char *pszElemName)
{
    CHECK_POINTER(pszElemName, false);
    CHECK_POINTER(m_pXmlNode, false);

    TiXmlNode* pTmpNode = m_pXmlNode;

	// ��ָ��ָ���һ��Ԫ��
	m_pXmlNode = m_pXmlNode->Parent()->FirstChild();

    // �ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER(m_pXmlNode, false);

	m_pXmlElem = m_pXmlNode->ToElement();

	// ����һ���������������
	const char* pChkTmpNode = NULL;
    while (((pChkTmpNode = GetElem()) != NULL) && (0 != strcmp(pszElemName, pChkTmpNode))) //lint !e838
    {
        if (NULL == m_pXmlNode->NextSibling())
        {
            break;
        }

        m_pXmlNode = m_pXmlNode->NextSibling();
        m_pXmlElem = m_pXmlNode->ToElement();
    }
/*
	while (0 != strcmp(pszElemName, GetElem()))
    {
        if (NULL == m_pXmlNode->PreviousSibling())
        {
            return false;
        }

        m_pXmlNode = m_pXmlNode->PreviousSibling();
        m_pXmlElem = m_pXmlNode->ToElement();
    }
*/
	const char* pNextTmpElem = this->GetElem();
	CHECK_POINTER(pNextTmpElem, false);
    if (0 == strcmp(pszElemName, pNextTmpElem))
    {
        return true;
    }

	// ����Ҳ���ƥ��ڵ㣬ָ�뻹ԭ
	m_pXmlNode = pTmpNode;
	m_pXmlElem = m_pXmlNode->ToElement();
	
    return false;
}



/**************************************************************************
* name       : AddAttribute
* description: ���Ԫ������
* input      : pszAttriName ����ӵ�������
               pszAttriValue ��Ӧ������ֵ
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::AddAttribute(const char *pszAttriName, const char *pszAttriValue)
{
    if ((NULL == pszAttriName) || (NULL == pszAttriValue))
    {
        return;
    }

    CHECK_POINTER_VOID(m_pXmlElem);

    m_pXmlElem->SetAttribute(pszAttriName, pszAttriValue);
}

/**************************************************************************
* name       : GetAttributeValue
* description: ���Ԫ������ֵ
* input      : pszAttriName Ԫ�ص�������
* output     : NA
* return     : const char* Ԫ�ص�����ֵ
* remark     : NA
**************************************************************************/
const char* CXml::GetAttributeValue(const char*pszAttriName) const
{
    if (NULL == m_pXmlElem)
    {
        return NULL;
    }
	
    return m_pXmlElem->Attribute(pszAttriName);
}

/**************************************************************************
* name       : GetRootPos
* description: �������ڵ�
* input      : NA
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::GetRootPos()
{
    if (NULL == m_pXMlDoc)
    {
        return;
    }

    m_pXmlNode = m_pXMlDoc->RootElement();

    if (NULL == m_pXmlNode)
    {
        return;
    }

    m_pXmlElem = m_pXmlNode->ToElement();
}

/**************************************************************************
* name       : NextElem
* description: ����ͬ����һ��Ԫ��
* input      : NA
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::NextElem()
{
    if (NULL == m_pXmlNode)
    {
        return false;
    }
	
	//���˵�ע�ͣ�NextSibling�����ע�ͣ�����ΪTINYXML_COMMENT
	do 
	{
		if (NULL == m_pXmlNode->NextSibling())
		{
			return false;
		}

		m_pXmlNode = m_pXmlNode->NextSibling();
	} while (m_pXmlNode->Type() == m_pXmlNode->TINYXML_COMMENT);
    
    m_pXmlElem = m_pXmlNode->ToElement();

    return true;
}

/**************************************************************************
* name       : RemoveAttribute
* description: ɾ��Ԫ������
* input      : pszAttriName Ԫ�ص�������
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::RemoveAttribute(const char*pszAttriName)
{
    if (NULL == pszAttriName)
    {
        return;
    }

    if (NULL == m_pXmlElem)
    {
        return;
    }

    m_pXmlElem->RemoveAttribute(pszAttriName);
}

/**************************************************************************
* name       : ModifyAttributeValue
* description: �޸�Ԫ������ֵ
* input      : pszAttriName ���޸ĵ�������
               pszAttriValue ��Ӧ������ֵ
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::ModifyAttributeValue(const char *pszAttriName, const char *pszAttriValue)
{
    if ((NULL == pszAttriName) || (NULL == pszAttriValue))
    {
        return;
    }

    if (NULL == m_pXmlElem)
    {
        return;
    }

    if (NULL != GetAttributeValue(pszAttriName))
    {
        m_pXmlElem->SetAttribute(pszAttriName, pszAttriValue);
    }
}

/**************************************************************************
* name       : ModifyElemValue
* description: �޸�Ԫ��ֵ
* input      : pszElemValue Ԫ��ֵ
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::ModifyElemValue(const char *pszElemValue)
{
    if (NULL == pszElemValue)
    {
        return;
    }

    if (NULL == m_pXmlNode)
    {
        return;
    }

	if (NULL == m_pXmlNode->FirstChild())
	{
		(void)SetElemValue(pszElemValue);
		return;
	}

    TiXmlText *pXmlText = m_pXmlNode->FirstChild()->ToText();

    //�ж�ָ���Ƿ�Ϊ��
    if (NULL == pXmlText)
    {
        return;
    }

    pXmlText->SetValue(pszElemValue);
}

/**************************************************************************
* name       : ModifyElemName
* description: �޸�Ԫ��
* input      : pszElemName Ԫ����
* output     : NA
* return     : NA
* remark     : NA
**************************************************************************/
void CXml::ModifyElemName(const char *pszElemName)
{
    if (NULL == pszElemName)
    {
        return;
    }

    if (NULL == m_pXmlNode)
    {
        return;
    }

    m_pXmlNode->SetValue(pszElemName);
}

/**************************************************************************
* name       : RemoveElem
* description: ɾ��Ԫ��
* input      : NA
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::RemoveElem()
{
    if (NULL == m_pXmlNode)
    {
        return false;
    }

    TiXmlNode* pTempParentNode = NULL;
    TiXmlNode* pTempNode = NULL;

    pTempParentNode = m_pXmlNode->Parent();//lint !e838

    if ((m_pXmlNode->PreviousSibling()) && (m_pXmlNode->PreviousSibling()->ToElement()))
    {
        pTempNode = m_pXmlNode->PreviousSibling();
    }
    else if ((m_pXmlNode->NextSibling()) && (m_pXmlNode->NextSibling()->ToElement()))
    {
        pTempNode = m_pXmlNode->NextSibling();
    }
    else
    {
        pTempNode = pTempParentNode;
    }

    //�ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER(pTempParentNode,false);

    if (!pTempParentNode->RemoveChild(m_pXmlNode))
    {
        return false;
    }

    m_pXmlNode = pTempNode;

    return true;
}

/**************************************************************************
* name       : GetXMLStream
* description: ��ȡxml��
* input      : NA
* output     : nXMLStreamLength
* return     : const char* xml��
* remark     : NA
**************************************************************************/
const char*  CXml::GetXMLStream(unsigned int &uiXMLStreamLength)
{
	TiXmlPrinter xmlPrinter;
	xmlPrinter.SetStreamPrinting();		

	if (NULL == m_pXMlDoc)
	{
		SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774
	}

	CHECK_POINTER(m_pXMlDoc, NULL);//lint !e774
	if (!m_pXMlDoc->Accept(&xmlPrinter))
	{
		return NULL;
	}

    uiXMLStreamLength = xmlPrinter.Size();

	m_strStream = xmlPrinter.CStr();
    return m_strStream.c_str();
}

/**************************************************************************
* name       : AddDeclaration
* description: ���xml�ļ���������
* input      : pszVersion �汾
               pszEncode ���뷽ʽ
               pszStdLone �������� yes��no
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::AddDeclaration(const char* pszVersion, const char* pszEncode, const char* pszStdLone)
{
    if ((NULL == pszVersion) || (NULL == pszEncode) || (NULL == pszStdLone))
    {
        return false;
    }

    if (NULL == m_pXMlDoc)
    {
        SAFE_NEW(m_pXMlDoc, TiXmlDocument);//lint !e774
    }

    CHECK_POINTER(m_pXMlDoc, false);//lint !e774

    TiXmlDeclaration *pXmlDeclaration;
    try
    {
        pXmlDeclaration = new TiXmlDeclaration(pszVersion, pszEncode, pszStdLone);
    }
    catch (...)
    {
        pXmlDeclaration = NULL;

        return false;//lint !e438
    }
    CHECK_POINTER(pXmlDeclaration, false);//lint !e774

    (void)(m_pXMlDoc->LinkEndChild(pXmlDeclaration));

    return true;//lint !e429
}

/**************************************************************************
* name       : AddChildAttribute
* description: �����Ԫ������
* input      : pszAttriName Ԫ��������
               pszAttriValue Ԫ������ֵ
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::AddChildAttribute( const char*pszAttriName, const char* pszAttriValue )
{
    if ((NULL == pszAttriName) || (NULL == pszAttriValue))
    {
        return false;
    }
    
    if (IntoElem())
    {
        AddAttribute(pszAttriName, pszAttriValue);
        OutOfElem();

        return true;
    }
	
    return false;
}

/**************************************************************************
* name       : SetChildData
* description: �����Ԫ��ֵ
* input      : pValue Ԫ��ֵ
* output     : NA
* return     : true - �ɹ���false - ʧ��
* remark     : NA
**************************************************************************/
bool CXml::SetChildData( const char *pszValue)
{
    if (NULL == pszValue)
    {
        return false;
    }

    if (IntoElem())
    {
        bool bRet = SetElemValue(pszValue);
        OutOfElem();
        if (bRet)
        {
            return true;
        }
    }
	
    return false;
}

bool CXml::FindElemEx(const char *pszElemPath)
{
	const char* seps = "/"; // �ַ����ָ���
	bool returnFlag = true;

	// ��鴫���·���Ƿ�Ϊ��
	CHECK_POINTER(pszElemPath,false);
    unsigned int iNewStrLen = strlen(pszElemPath) + 1;

	// ������ʱ�ַ���
    char* pszPath = NULL;
    SAFE_NEW_A(pszPath, char, iNewStrLen);
    CHECK_POINTER(pszPath,false);
    memset(pszPath, 0, iNewStrLen);
    char* pszTmpPath = pszPath;

    // �����ַ���
	if(strncpy_s(pszTmpPath, iNewStrLen, pszElemPath, iNewStrLen)!=0){}else{}
    //strcpy(pszTmpPath,pszElemPath);
    
    if(*pszTmpPath == '/')
    {
        ++pszTmpPath;   //lint !e810
        this->GetRootPos();
		(void)this->IntoElem();
    }
    else
    {
        // ��xml��ָ��ָ����ڵ�
        (void)this->GetBasePos();
    }
    char *saveptr = NULL;
    char* token = STRTOK( pszTmpPath, seps, &saveptr); 
	while( token != NULL )
    {//lint !e525
	   const char* tmpStr = strstr(token,"[");
	   if(NULL != tmpStr)
	   {   
		    // ������ͬ���ڵ�����
            int index = atoi(tmpStr + 1);
			std::string  strTemp(token,static_cast<unsigned int>(tmpStr - token));
			if(!this->FindElem(strTemp.c_str()))
			{
				returnFlag = false;
				break;
			}

			if(!this->NextElemEx(index))
			{
				returnFlag = false;
				break;
			}
	   }
	   else
	   {
		   // �����ڵ�����
		   if(!this->FindElem(token))
		   {
			   returnFlag = false;
			   break;
		   }
	   }

	   // ����ýڵ�
       (void)this->IntoElem();
	  // Get next token: 
	  token = STRTOK( NULL, seps, &saveptr); 
    }
    SAFE_DELETE_A(pszPath);//lint !e774 !e1775
    return returnFlag;//lint !e438
}

bool CXml::FindElemValue( const char *pszElemName )
{
	CHECK_POINTER(pszElemName, false);
	CHECK_POINTER(m_pXmlNode, false);

	const char* pElem = GetElem();
	while ((NULL != pElem) && (0 != strcmp(pszElemName, pElem)))
	{
		if (NULL == m_pXmlNode->NextSibling())
		{
			return false;
		}

		m_pXmlNode = m_pXmlNode->NextSibling();
		m_pXmlElem = m_pXmlNode->ToElement();
	}

	pElem = GetElem();
	if (NULL == pElem)
	{
		return false;
	}

	if (0 == strcmp(pszElemName, pElem))
	{
		return true;
	}
	
	return false;
}

bool CXml::NextElemEx(int count)
{
	const char* pszNodeName = this->GetElem();
	CHECK_POINTER(pszNodeName, false);
	for(int i = 0;i < count;++i)
	{
		const char* pTmpElem = this->GetElem();
		CHECK_POINTER(pTmpElem, false);
		if (!this->NextElem() || 0 != strcmp(pszNodeName,pTmpElem))
		{
			return false;
		}
	}
	return true;
}

bool CXml::SetElemValueEx(const char *pszElemPath,const char *pszElemValue)
{
    //ָ���ж�
    CHECK_POINTER(pszElemPath, false);
    CHECK_POINTER(pszElemValue, false);

     if(FindElemEx(pszElemPath))
	 {
		 const char *str_value = GetElemValue();
		 if(NULL != str_value && 0 != strcmp("",str_value))
		 {
			 this->ModifyElemValue(pszElemValue);
			 return true;
		 }
         else
		 {
			 if (!this->SetElemValue(pszElemValue))
			 {
				 return false;
			 }
			 
			 //�����Ϊ�˷�ֹ������ֵΪ�մ���ʱ��set�ɹ���ֵȴû�ӽ�ȥ
			 this->ModifyElemValue(pszElemValue);
             return true;
		 }
	 }
	 return false;
}

bool CXml::SetElemValueCDATAEx(const char *pszElemPath,const char *pszElemValue)
{
    //ָ���ж�
    CHECK_POINTER(pszElemPath, false);
    CHECK_POINTER(pszElemValue, false);

	if(FindElemEx(pszElemPath))
	{
		const char *str_value = GetElemValue();
		if(NULL != str_value && 0 != strcmp("",str_value))
		{
			this->ModifyElemValueCDATA(pszElemValue);
			return true;
		}else
		{			
			if (!this->SetElemValueCDATA(pszElemValue))
			{
				return false;
			}

			//�����Ϊ�˷�ֹ������ֵΪ�մ���ʱ��set�ɹ���ֵȴû�ӽ�ȥ
			this->ModifyElemValueCDATA(pszElemValue);

			return true;
		}
	}
	return false;
}

void CXml::ModifyElemValueCDATA(const char *pszElemValue)
{
	if (NULL == pszElemValue)
	{
		return;
	}

	if (NULL == m_pXmlNode)
	{
		return;
	}

	TiXmlText *pXmlText = m_pXmlNode->FirstChild()->ToText();

    //�ж�ָ���Ƿ�Ϊ��
    CHECK_POINTER_VOID(pXmlText);

	pXmlText->SetCDATA(true);  // ���CDATA����
	pXmlText->SetValue(pszElemValue);
}

const char* CXml::GetElemValueEx(const char *pszElemPath)
{
    //�ж�ָ���Ƿ�Ϊ��
    if (NULL == pszElemPath)
    {
        return NULL;
    }

	if(FindElemEx(pszElemPath))
	{
		return this->GetElemValue();
	}
	return NULL;
}

bool CXml::MkAndNextElemEx(int count)
{
	const char* pszNodeName = this->GetElem();
	CHECK_POINTER(pszNodeName, false);
	int j = 0;
	for(int i = 0;i < count;++i)
	{
		const char* pTmpElem = this->GetElem();
		CHECK_POINTER(pTmpElem, false);
		if (this->NextElem() && 0 == strcmp(pszNodeName,pTmpElem))
		{
			++j;
		}
	}
	for(;j < count;++j)
	{
		(void)this->IntoElem();
		if(this->AddElem(pszNodeName))
		{
			const char* pTmpElem = this->GetElem();
			CHECK_POINTER(pTmpElem, false);
			//return false;
		}
	}
	return true;
}

bool CXml::SetBaseElem(const char* pszElemPath)
{
    if(NULL != pszElemPath)
    {
        (void)this->FindElemEx(pszElemPath);
    }
    m_pBaseXmlNode = m_pXmlNode;
    m_pBaseXmlElem = m_pXmlElem;
    return true;
}

bool CXml::GetBasePos()
{
    if (NULL == m_pBaseXmlNode)
    {
        GetRootPos();
    }
    else
    {
        m_pXmlNode = m_pBaseXmlNode;
        m_pXmlElem = m_pBaseXmlElem;
    }
    return true;
}

bool CXml::MkAndFindElemEx(const char *pszElemPath)
{
	// ������ʱ����
	
	char* token;
	const char* seps = "/"; // �ַ����ָ���
	bool returnFlag = true;

	// ��鴫���·���Ƿ�Ϊ��
	CHECK_POINTER(pszElemPath,true);

	// ��xml��ָ��ָ����ڵ�
	(void)this->GetBasePos();

	// ������ʱ�ַ���
    unsigned int iNewStrLen = strlen(pszElemPath) + 1;
    char* pszPath = NULL;
    SAFE_NEW_A(pszPath, char, iNewStrLen);
    CHECK_POINTER(pszPath, false);
    memset(pszPath, 0, iNewStrLen);
    char* pszTmpPath = pszPath;    

	// �����ַ���
	if(strncpy_s(pszTmpPath, iNewStrLen, pszElemPath, iNewStrLen)!=0){}else{}
	//strcpy(pszTmpPath,pszElemPath);
    char *saveptr = NULL;
	token = STRTOK( pszTmpPath, seps, &saveptr);
	std::string pszParentNode = "";
	while( token != NULL )
	{
		// ��ǰָ��ָ��Ľڵ�����
		const char* curNodeName = this->GetElem();
		char* pszTmpNode = strstr(token,"[");
		if(NULL != pszTmpNode)
		{   
			// ������ͬ���ڵ�����
			int index = atoi(pszTmpNode + 1);
			std::string  strTemp(token,static_cast<unsigned int>(pszTmpNode - token));
            if(NULL == curNodeName)
            {
                 (void)this->AddElem(strTemp.c_str());
            }
			if(!this->FindElem(strTemp.c_str()))
			{
				returnFlag = false;
				break;

				//// �������û�д˽ڵ��򴴽��ýڵ�
    //            if(0 != strcmp(curNodeName,pszParentNode.c_str()))//lint !e527
				//{
    //                 (void)this->AddElem(strTemp.c_str());
				//}else
				//{
    //                 (void)this->AddChildElem(strTemp.c_str());
				//}
    //            (void)this->FindElem(strTemp.c_str());
			}

			if(!this->MkAndNextElemEx(index))
			{
				returnFlag = false;
				break;
			}
			// ��¼��ǰ�ڵ�Ϊ��һ�ڵ�ĸ��ڵ�
		    pszParentNode = strTemp;
		}
		else
		{
            if(NULL == curNodeName)
            {
                (void)this->AddElem(token);
            }
			// �����ڵ�����
			if(!this->FindElem(token))
			{
                if (NULL != curNodeName)
                {
				    if(0 != strcmp(curNodeName,pszParentNode.c_str()))
				    {
                         (void)this->AddElem(token);
				    }else
				    {
                         (void)this->AddChildElem(token);
				    }
                }
                (void)this->FindElem(token);
			}
			// ��¼��ǰ�ڵ�Ϊ��һ�ڵ�ĸ��ڵ�
		    pszParentNode = token;
		}

		// ����ýڵ�
		(void)this->IntoElem();

		// Get next token: 
		token = STRTOK( NULL, seps, &saveptr ); 
	}
    SAFE_DELETE_A(pszPath);//lint !e424 !e774 !e1775
    return returnFlag;//lint !e438
  //return false;
}

bool CXml::MkAndSetElemValueEx(const char *pszElemPath,const char *pszElemValue)
{
    //���ָ���ж�
    if ((NULL == pszElemPath) || (NULL == pszElemValue))
    {
        return false;
    }
	if(MkAndFindElemEx(pszElemPath))
	{
		const char *str_value = GetElemValue();
		if(NULL != str_value && 0 != strcmp("",str_value))
		{
			this->ModifyElemValue(pszElemValue);
			return true;
		}
        else
		{
			if (!this->SetElemValue(pszElemValue))
			{
				return false;
			}

			//�����Ϊ�˷�ֹ������ֵΪ�մ���ʱ��set�ɹ���ֵȴû�ӽ�ȥ
			this->ModifyElemValue(pszElemValue);
			return true;
		}
	}
	return false;
}

//lint -e1554
CXml::CXml(const CXml &src)
{
    m_pBaseXmlElem = src.m_pBaseXmlElem;
    m_pBaseXmlNode = src.m_pBaseXmlNode;
    m_pXMlDoc = src.m_pXMlDoc;
    m_pXmlElem = src.m_pXmlElem;
    m_pXmlNode = src.m_pXmlNode;
    m_pszFileName = src.m_pszFileName;
}//lint -e1554

CXml& CXml::operator=(const CXml&)
{
    return *this;
}//lint !e1529 !e1745
