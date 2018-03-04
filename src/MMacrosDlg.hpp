// MMacrosDlg.hpp --- Dialogs for Predefined Macros
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

#ifndef MZC4_MMACROSDLG_HPP_
#define MZC4_MMACROSDLG_HPP_

#include "MWindowBase.hpp"
#include "RisohSettings.hpp"
#include "ConstantsDB.hpp"
#include "MResizable.hpp"
#include "MComboBoxAutoComplete.hpp"
#include "resource.h"

class MMacrosDlg;

//////////////////////////////////////////////////////////////////////////////

struct MACRO_ENTRY
{
    TCHAR szKey[128];
    TCHAR szValue[256];
};

class MMacrosDlg : public MDialogBase
{
public:
    macro_map_type& m_map;
    ConstantsDB& m_db;
    MResizable m_resizable;
    HICON m_hIcon;
    HICON m_hIconSm;

    MMacrosDlg(macro_map_type& map, ConstantsDB& db)
        : MDialogBase(IDD_MACROS), m_map(map), m_db(db)
    {
        m_hIcon = LoadIconDx(IDI_SMILY);
        m_hIconSm = LoadSmallIconDx(IDI_SMILY);
    }

    ~MMacrosDlg()
    {
        DestroyIcon(m_hIcon);
        DestroyIcon(m_hIconSm);
    }

    void OnUp(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT iItem = ListView_GetNextItem(hCtl1, -1, LVNI_ALL | LVNI_SELECTED);
        if (iItem == 0)
            return;

        MACRO_ENTRY me0, me1;
        ListView_GetItemText(hCtl1, iItem - 1, 0, me0.szKey, _countof(me0.szKey));
        ListView_GetItemText(hCtl1, iItem - 1, 1, me0.szValue, _countof(me0.szValue));
        ListView_GetItemText(hCtl1, iItem, 0, me1.szKey, _countof(me1.szKey));
        ListView_GetItemText(hCtl1, iItem, 1, me1.szValue, _countof(me1.szValue));

        ListView_SetItemText(hCtl1, iItem - 1, 0, me1.szKey);
        ListView_SetItemText(hCtl1, iItem - 1, 1, me1.szValue);
        ListView_SetItemText(hCtl1, iItem, 0, me0.szKey);
        ListView_SetItemText(hCtl1, iItem, 1, me0.szValue);

        UINT state = LVIS_SELECTED | LVIS_FOCUSED;
        ListView_SetItemState(hCtl1, iItem - 1, state, state);
    }

    void OnDown(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT iItem = ListView_GetNextItem(hCtl1, -1, LVNI_ALL | LVNI_SELECTED);
        if (iItem + 1 == ListView_GetItemCount(hCtl1))
            return;

        MACRO_ENTRY me0, me1;
        ListView_GetItemText(hCtl1, iItem, 0, me0.szKey, _countof(me0.szKey));
        ListView_GetItemText(hCtl1, iItem, 1, me0.szValue, _countof(me0.szValue));
        ListView_GetItemText(hCtl1, iItem + 1, 0, me1.szKey, _countof(me1.szKey));
        ListView_GetItemText(hCtl1, iItem + 1, 1, me1.szValue, _countof(me1.szValue));

        ListView_SetItemText(hCtl1, iItem, 0, me1.szKey);
        ListView_SetItemText(hCtl1, iItem, 1, me1.szValue);
        ListView_SetItemText(hCtl1, iItem + 1, 0, me0.szKey);
        ListView_SetItemText(hCtl1, iItem + 1, 1, me0.szValue);

        UINT state = LVIS_SELECTED | LVIS_FOCUSED;
        ListView_SetItemState(hCtl1, iItem + 1, state, state);
    }

    void OnDelete(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT iItem = ListView_GetNextItem(hCtl1, -1, LVNI_ALL | LVNI_SELECTED);
        if (iItem >= 0)
        {
            ListView_DeleteItem(hCtl1, iItem);
        }
    }

    void OnAdd(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT iItem = ListView_GetNextItem(hCtl1, -1, LVNI_ALL | LVNI_SELECTED);
        if (iItem < 0)
        {
            return;
        }
    }

    void OnModify(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT iItem = ListView_GetNextItem(hCtl1, -1, LVNI_ALL | LVNI_SELECTED);
        if (iItem < 0)
        {
            return;
        }

        MACRO_ENTRY m_entry;
        ListView_GetItemText(hCtl1, iItem, 0, m_entry.szKey, _countof(m_entry.szKey));
        ListView_GetItemText(hCtl1, iItem, 1, m_entry.szValue, _countof(m_entry.szValue));
    }

    void OnOK(HWND hwnd)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);

        INT i, nCount = ListView_GetItemCount(hCtl1);

        if (nCount == 0)
        {
            ErrorBoxDx(IDS_DATAISEMPTY);
            return;
        }

        EndDialog(IDOK);
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case psh1:
            OnAdd(hwnd);
            break;
        case psh2:
            OnModify(hwnd);
            break;
        case psh3:
            OnDelete(hwnd);
            break;
        case psh4:
            OnUp(hwnd);
            break;
        case psh5:
            OnDown(hwnd);
            break;
        case IDOK:
            OnOK(hwnd);
            break;
        case IDCANCEL:
            EndDialog(IDCANCEL);
            break;
        }
    }

    LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnmhdr)
    {
        if (idFrom == ctl1)
        {
            if (pnmhdr->code == LVN_KEYDOWN)
            {
                LV_KEYDOWN *KeyDown = (LV_KEYDOWN *)pnmhdr;
                if (KeyDown->wVKey == VK_DELETE)
                {
                    OnDelete(hwnd);
                    return 0;
                }
            }
            if (pnmhdr->code == NM_DBLCLK)
            {
                OnModify(hwnd);
                return 0;
            }
        }
        return 0;
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
            HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
            HANDLE_MSG(hwnd, WM_NOTIFY, OnNotify);
            HANDLE_MSG(hwnd, WM_SIZE, OnSize);
        }
        return DefaultProcDx();
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_resizable.OnSize();
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        HWND hCtl1 = GetDlgItem(hwnd, ctl1);
        ListView_SetExtendedListViewStyle(hCtl1, LVS_EX_FULLROWSELECT);

        LV_COLUMN column;
        ZeroMemory(&column, sizeof(column));

        column.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
        column.fmt = LVCFMT_LEFT;
        column.cx = 105;
        column.pszText = LoadStringDx(IDS_MACRONAME);
        column.iSubItem = 0;
        ListView_InsertColumn(hCtl1, 0, &column);

        column.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
        column.fmt = LVCFMT_LEFT;
        column.cx = 75;
        column.pszText = LoadStringDx(IDS_MACROVALUE);
        column.iSubItem = 1;
        ListView_InsertColumn(hCtl1, 1, &column);

        UINT state = LVIS_SELECTED | LVIS_FOCUSED;
        ListView_SetItemState(hCtl1, 0, state, state);
        SetFocus(hCtl1);

        m_resizable.OnParentCreate(hwnd);

        m_resizable.SetLayoutAnchor(ctl1, mzcLA_TOP_LEFT, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(psh1, mzcLA_TOP_RIGHT);
        m_resizable.SetLayoutAnchor(psh2, mzcLA_TOP_RIGHT);
        m_resizable.SetLayoutAnchor(psh3, mzcLA_TOP_RIGHT);
        m_resizable.SetLayoutAnchor(psh4, mzcLA_TOP_RIGHT);
        m_resizable.SetLayoutAnchor(psh5, mzcLA_TOP_RIGHT);
        m_resizable.SetLayoutAnchor(IDOK, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(IDCANCEL, mzcLA_BOTTOM_RIGHT);

        SendMessageDx(WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);
        SendMessageDx(WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSm);

        CenterWindowDx();
        return TRUE;
    }
};

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMACROSDLG_HPP_