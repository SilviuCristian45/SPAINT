#pragma once
#include <string>
#include <Windows.h>

//input - char array filter for the files displayed in the save dialog 
//        hwnd owner - the parent window pointer
//output- returns the path which was selected by the user in the save dialog
std::string savefile(const wchar_t* filter = L"All files (*.*)\0*.*\0", HWND owner = NULL) {
    OPENFILENAME ofn; //object which contains information used to initialize the dialog box
    wchar_t fileName[MAX_PATH] = L""; //the filename 
    ZeroMemory(&ofn, sizeof(ofn)); //un fel de bitset

    ofn.lStructSize = sizeof(OPENFILENAME); //lungimea structurii in bytes
    ofn.hwndOwner = owner;                  //fereastra de mai sus 
    ofn.lpstrFilter = filter;               //filtrul pt ce se afiseaza in dialog  
    ofn.lpstrFile = fileName;               //adresa in care vom stoca rezultatul 
    ofn.nMaxFile = MAX_PATH;                //nr maxim de fisiere afisate
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    if (GetSaveFileName(&ofn)) { //returneaza bool , daca s-a salvat intr-un fisier
        std::wstring ws(fileName); //convertim in wstring din wchar_t pointer
        std::string filenamestr(ws.begin(), ws.end()); //convertim in string din wstring
        return filenamestr; //returnam string-ul pt ca pe urma sa fie manipulat mai usor
    }
    return "inchis";
}

//input - char array filter for the files displayed in the save dialog 
//        hwnd owner - the parent window pointer
//output- returns the path which was selected by the user in the save dialog
std::string openfile(const wchar_t* filter = L"All files (*.*)\0*.*\0", HWND owner = NULL) {
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

