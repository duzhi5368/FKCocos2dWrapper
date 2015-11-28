#include "FileView.h"
#include "../../FKExpand/ComboBox.h"
#include "../../FKExpand/FileDirDialog.h"

bool FileView::init()
{
	if(!FKCW_UIWidget_WidgetWindow::init())
		return false;
	
	/************************************************************************/
	/* �ļ��˵�	                                                            */
	/************************************************************************/
	m_pFileMenuComboBox = ComboBox::create(CCSize(70, 32), 3);
	m_pFileMenuComboBox->setTag(1111);	//��ʶ
	m_pFileMenuComboBox->setPosition(CCSize(70, 25)/2);
	m_pFileMenuComboBox->setText(A2U("�ļ�").c_str());
	this->addChild(m_pFileMenuComboBox);
	
	m_pFileMenuComboBox->addString(A2U("�½�").c_str());
	m_pFileMenuComboBox->addString(A2U("�ļ�..").c_str());
	m_pFileMenuComboBox->addString(A2U("�ļ���..").c_str());

	m_pFileMenuComboBox->setOnComboBoxChangeListener(this, fkcw_uiwidget_combobox_change_selector(FileView::onFileComboBoxChange));

	/************************************************************************/
	/* �ļ�ѡ���                                                             */
	/************************************************************************/
	m_pFileSelectComboBox = ComboBox::create(CCSize(1080, 32), 3);
	m_pFileSelectComboBox->setTag(2222);	//��ʶ
	m_pFileSelectComboBox->setText(A2U("��������ļ��˵�,�½������������ļ�").c_str());
	m_pFileSelectComboBox->setPosition(CCSize(1080, 25)/2 + ccp(70+5, 0));
	this->addChild(m_pFileSelectComboBox);

	m_pFileSelectComboBox->setOnComboBoxChangeListener(this, fkcw_uiwidget_combobox_change_selector(FileView::onFileComboBoxChange));

	return true;
}

void FileView::onFileComboBoxChange(CCObject* pSender, int tag, const char* text)
{
	ComboBox* pComboBox = (ComboBox*)pSender;

	if (pComboBox->getTag() == 1111)	//�ļ��˵�
	{
		if(tag == 0)		//�½�
		{
			string strFilePath = OpenDir(L"��ѡ���ļ�����Ŀ¼");
			if(!strFilePath.empty())
			{
				if (m_pDelegate != NULL)
				{
					m_pDelegate->onFileViewNewFileMessage(A2U(strFilePath.c_str()));
				}
			}
		}
		else if (tag == 1)	//�ļ�
		{
			string strFilePath = OpenFile();
			if (!strFilePath.empty())
			{
				//����Ŀ¼������xml�ļ�
				vector<string> dfsFileNames = dfsFolder(FKCW_Base_Utils::DeleteLastPathOfComponment(strFilePath));
				//���ComboBox
				m_pFileSelectComboBox->clear();
				//��ComboBox���Ŀ¼�������ļ�
				for (unsigned int i=0; i<dfsFileNames.size(); i++)
				{
					m_pFileSelectComboBox->addString(A2U(dfsFileNames.at(i).c_str()).c_str());
				}
				m_pFileSelectComboBox->setText(A2U(strFilePath.c_str()).c_str());

				if (m_pDelegate != NULL)
				{
					m_pDelegate->onFileViewOpenFileMessage(A2U(strFilePath.c_str()));
				}
			}
		}
		else if(tag == 2)	//�ļ���
		{
			string strFilePath = OpenDir(L"��ѡ�������ļ��ļ���");
			if (!strFilePath.empty())
			{
				//����Ŀ¼������xml�ļ�
				vector<string> dfsFileNames = dfsFolder(strFilePath);
				//���ComboBox
				m_pFileSelectComboBox->clear();
				//��ComboBox���Ŀ¼�������ļ�
				for (unsigned int i=0; i<dfsFileNames.size(); i++)
				{
					m_pFileSelectComboBox->addString(A2U(dfsFileNames.at(i).c_str()).c_str());
				}
				m_pFileSelectComboBox->setText(A2U("�����ô�ѡ�������ļ�").c_str());
			}
		}
	}

	else if(pComboBox->getTag() == 2222)	//�ļ�ѡ���
	{
		if (m_pDelegate != NULL)
		{
			string strFilePath = m_pFileSelectComboBox->getText();
			m_pDelegate->onFileViewOpenFileMessage(strFilePath);
		}
	}
}

void FileView::setDelegate(FileViewDelegate* pDelegate)
{
	m_pDelegate = pDelegate;
}

FileView::FileView():
	m_pDelegate(NULL)
{
}

void FileView::setText(const char* title)
{
	m_pFileSelectComboBox->setText(title);
}
