// MCloneInNewNameDlg.hpp --- "Clone In New Name" Dialog
//////////////////////////////////////////////////////////////////////////////
// RisohEditor --- Another free Win32 resource editor
// Copyright (C) 2017-2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCLONEINNEWNAMEDLG_HPP_
#define MZC4_MCLONEINNEWNAMEDLG_HPP_

//////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"
#include "ConstantsDB.hpp"
#include "Res.hpp"
#include "MComboBoxAutoComplete.hpp"
#include "resource.h"

BOOL CheckTypeComboBox(HWND hCmb1, MIdOrString& type);
BOOL CheckNameComboBox(HWND hCmb2, MIdOrString& name);
void InitResNameComboBox(HWND hCmb, MIdOrString id, IDTYPE_ nIDTYPE_);

//////////////////////////////////////////////////////////////////////////////

class MCloneInNewNameDlg : public MDialogBase
{
public:
    EntryBase *m_entry;
    MIdOrString m_type;
    MIdOrString m_name;
    WORD m_lang;
    MComboBoxAutoComplete m_cmb2;

    MCloneInNewNameDlg(EntryBase *entry)
        : MDialogBase(IDD_CLONEINNEWNAME), m_entry(entry), 
          m_type(entry->m_type), m_name(entry->m_name), m_lang(entry->m_lang)
    {
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
            HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        }
        return DefaultProcDx(hwnd, uMsg, wParam, lParam);
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        // for Types
        INT k;
        HWND hCmb1 = GetDlgItem(hwnd, cmb1);

        auto table = g_db.GetTable(L"RESOURCE");
        for (auto& table_entry : table)
        {
            WCHAR sz[MAX_PATH];
            StringCchPrintfW(sz, _countof(sz), L"%s (%lu)",
                             table_entry.name.c_str(), table_entry.value);
            k = ComboBox_AddString(hCmb1, sz);
            if (m_type == WORD(table_entry.value))
            {
                ComboBox_SetCurSel(hCmb1, k);
            }
        }

        table = g_db.GetTable(L"RESOURCE.STRING.TYPE");
        for (auto& table_entry : table)
        {
            k = ComboBox_AddString(hCmb1, table_entry.name.c_str());
            if (m_type == table_entry.name.c_str())
            {
                ComboBox_SetCurSel(hCmb1, k);
            }
        }

        // for Names
        IDTYPE_ nIDTYPE_ = g_db.IDTypeFromResType(m_type);
        HWND hCmb2 = GetDlgItem(hwnd, cmb2);
        InitResNameComboBox(hCmb2, m_name, nIDTYPE_);
        SubclassChildDx(m_cmb2, cmb2);

        CenterWindowDx();
        return TRUE;
    }

    void OnOK(HWND hwnd)
    {
        MIdOrString type;
        HWND hCmb1 = GetDlgItem(hwnd, cmb1);
        const ConstantsDB::TableType& table = g_db.GetTable(L"RESOURCE");
        INT iType = ComboBox_GetCurSel(hCmb1);
        if (iType != CB_ERR && iType < INT(table.size()))
        {
            type = WORD(table[iType].value);
        }
        else
        {
            if (!CheckTypeComboBox(hCmb1, type))
                return;
        }

        // for Names
        HWND hCmb2 = GetDlgItem(hwnd, cmb2);
        MIdOrString name;
        if (!CheckNameComboBox(hCmb2, name))
            return;

        if (m_name == name)
        {
            ErrorBoxDx(IDS_SAMENAME);
            return;
        }

        if (g_res.find(ET_NAME, m_type, name, m_lang))
        {
            if (MsgBoxDx(IDS_EXISTSOVERWRITE, MB_ICONINFORMATION | MB_YESNOCANCEL) != IDYES)
            {
                return;
            }
        }

        m_name = name;

        EndDialog(IDOK);
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDOK:
            OnOK(hwnd);
            break;
        case IDCANCEL:
            EndDialog(IDCANCEL);
            break;
        case psh1:
            OnPsh1(hwnd);
            break;
        case cmb2:
            if (codeNotify == CBN_EDITCHANGE)
            {
                m_cmb2.OnEditChange();
            }
            break;
        }
    }

    void OnPsh1(HWND hwnd)
    {
        SendMessage(GetParent(hwnd), WM_COMMAND, ID_IDLIST, 0);
    }
};

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCLONEINNEWNAMEDLG_HPP_
