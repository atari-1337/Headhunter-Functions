// add these pre-processor statements
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// gets the path of the dll (place this above the custom functions)
std::string GetDLLPath()
{
    HMODULE hModule = GetModuleHandleA("headhunter.dll");
    if (hModule == NULL)
        return "";
    char buffer[MAX_PATH + 1];
    GetModuleFileNameA(hModule, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

// readfile
int readfile(std::uintptr_t rl) 
    {
        std::ifstream file;
        const char* string = **reinterpret_cast<const char***>(rl + offsets::luastate::base) + 0x14;
        std::string path = GetDLLPath() + "\\workspace\\" + string;

        file.open(path);

        if (file.fail()) {
            output << "Read fail\n";
            return 0;
        }
        else 
        {
            std::string file_contents;
            file_contents = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            rbx_pushstring(rl, file_contents);
        }
        return 1;
    }
    
// writefile
int writefile(std::uintptr_t rl)
    {
        std::string name = get_string(rl, -2);

        std::string npath = GetDLLPath() + "\\workspace\\" + std::string(name));

        ofstream MyFile(npath);
        MyFile << get_string(rl, -1);
        MyFile.close();
        return 0;
    }

// setclipboard
int setclipboard(std::uintptr_t rl)
    {
        const char* string = **reinterpret_cast<const char***>(rl + offsets::luastate::base) + 0x14;
        const size_t len = strlen(string) + 1;

        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);

        memcpy(GlobalLock(hMem), string, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();

        return 1;
    }
