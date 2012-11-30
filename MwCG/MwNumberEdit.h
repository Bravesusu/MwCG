#pragma once
#include "afxribbonedit.h"

class MwRibbonNumEditCtrl : public CMFCRibbonRichEditCtrl
{
protected:
	float m_nValidNum;

	DECLARE_MESSAGE_MAP()

public:
	MwRibbonNumEditCtrl::MwRibbonNumEditCtrl(CMFCRibbonEdit& edit) : CMFCRibbonRichEditCtrl(edit)
	{
		m_nValidNum = 0;
	}

	virtual void OnKillFocus(CWnd* pNewWnd)
	{
		CMFCRibbonRichEditCtrl::OnKillFocus(pNewWnd);
		float nTempVal = (float)_ttof(m_strOldText);
		if (nTempVal != 0) 
		{
			m_nValidNum = nTempVal;
		}
		else
		{
			m_strOldText.Empty();
			m_nValidNum = 0;
		}

		CString strText;
		strText.Format(_T("%f"), m_nValidNum);
		m_edit.SetEditText(strText);
	}
};

class MwNumberEdit :
	public CMFCRibbonEdit
{
public:
	MwNumberEdit(UINT uiID, int nWidth, LPCTSTR lpszLabel, int nImage = -1)
		: CMFCRibbonEdit(uiID, nWidth, lpszLabel, nImage) {};
	~MwNumberEdit(void);

	virtual CMFCRibbonRichEditCtrl* CreateEdit(CWnd* pWndParent, DWORD dwEditStyle)
	{
		ASSERT_VALID(this);
		ASSERT_VALID(pWndParent);

		MwRibbonNumEditCtrl* pWndEdit = new MwRibbonNumEditCtrl(*this);

		if (!pWndEdit->Create(dwEditStyle, CRect(0, 0, 0, 0), pWndParent, m_nID))
		{
			delete pWndEdit;
			return NULL;
		}

		if (m_bHasSpinButtons)
		{
			CreateSpinButton(pWndEdit, pWndParent);
		}

		return pWndEdit;
	}
};

