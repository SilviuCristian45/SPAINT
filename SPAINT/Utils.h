#pragma once
#include <string>
#include <Windows.h>

std::string savefile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL) {
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    if (GetSaveFileName(&ofn)) {
        //fileNameStr = fileName;
        std::wstring ws(fileName);
        std::string filenamestr(ws.begin(), ws.end());
        return filenamestr;
    }
    return "inchis";
}


