#ifndef ACCEL_RES_HPP_
#define ACCEL_RES_HPP_

#include <windows.h>
#include <cassert>
#include <vector>

#include "ByteStream.hpp"
#include "Text.hpp"

struct AccelTableEntry
{
    WORD   fFlags;
    WORD   wAscii;
    WORD   wId;
    WORD   padding;
};

class AccelRes
{
public:
    typedef AccelTableEntry             entry_type;
    typedef std::vector<entry_type>     entries_type;
    AccelRes() { }

    BOOL LoadFromStream(const ByteStream& stream)
    {
        m_entries.clear();
        if (stream.size() < sizeof(entry_type))
            return FALSE;

        entry_type entry;
        size_t i, count = stream.size() / sizeof(entry_type);
        for (i = 0; i < count; ++i)
        {
            if (!stream.ReadRaw(entry))
                return FALSE;

            m_entries.push_back(entry);

            if (entry.fFlags & 0x80)
                break;
        }

        return TRUE;
    }

    void Update()
    {
        size_t i, count = m_entries.size();
        for (i = 0; i < count; ++i)
        {
            entry_type& entry = m_entries[i];

            if (i + 1 == count)
                entry.fFlags |= 0x80;
            else
                entry.fFlags &= ~0x80;
        }
    }

    std::vector<BYTE> data() const
    {
        DWORD size = m_entries.size() * sizeof(entry_type);
        const BYTE *pb = (const BYTE *)&m_entries[0];
        return std::vector<BYTE>(pb, pb + size);
    }

    std::wstring Dump(const ID_OR_STRING &id_or_str) const
    {
        std::wstring ret;

        ret += id_or_str.wstr();
        ret += L" ";
        ret += L"ACCELERATORS\r\n";
        ret += L"{\r\n";

        entries_type::const_iterator it, end = m_entries.end();
        for (it = m_entries.begin(); it != end; ++it)
        {
            BOOL VIRTKEY = (it->fFlags & FVIRTKEY);
            BOOL NOINVERT = (it->fFlags & FNOINVERT);
            BOOL SHIFT = (it->fFlags & FSHIFT);
            BOOL CONTROL = (it->fFlags & FCONTROL);
            BOOL ALT = (it->fFlags & FALT);

            ret += L"    ";
            if (VIRTKEY)
            {
                ret += virtkey(it->wAscii);
            }
            else
            {
                std::string str;
                str += (char)it->wAscii;
                ret += AnsiToWide(quote(str));
            }
            ret += L", ";
            ret += deci(it->wId);

            if (NOINVERT)
                ret += L", NOINVERT";
            if (ALT)
                ret += L", ALT";
            if (CONTROL)
                ret += L", CONTROL";
            if (SHIFT)
                ret += L", SHIFT";

            if (VIRTKEY)
                ret += L", VIRTKEY";
            else
                ret += L", ASCII";

            ret += L"\r\n";
        }

        ret += L"}\r\n";
        return ret;
    }

    entries_type& Entries()
    {
        return m_entries;
    }
    const entries_type& Entries() const
    {
        return m_entries;
    }

protected:
    entries_type    m_entries;
};

#endif  // ndef ACCEL_RES_HPP_
