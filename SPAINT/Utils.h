#pragma once
#include <string>
#include <Windows.h>

//input - char array filter for the files displayed in the save dialog 
//        hwnd owner - the parent window pointer
//output- returns the path which was selected by the user in the save dialog
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

//input - char array filter for the files displayed in the save dialog 
//        hwnd owner - the parent window pointer
//output- returns the path which was selected by the user in the save dialog
std::string openfile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL) {
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

    if (GetOpenFileName(&ofn)) {
        //fileNameStr = fileName;
        std::wstring ws(fileName);
        std::string filenamestr(ws.begin(), ws.end());
        return filenamestr;
    }
    return "inchis";
}

