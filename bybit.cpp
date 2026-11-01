#include <windows.h>
#include <tlhelp32.h>
#include <vector>

const std::vector<std::wstring_view> aioyq1 = {
    L"vboxservice.exe",
    L"vboxtray.exe",
    L"vmtoolsd.exe",
    L"vmwaretray.exe",
    L"xenservice.exe",
    L"joeboxserver.exe",
    L"vmusrvc.exe",
    L"vmsrvc.exe",
    L"prl_cc.exe",
    L"prl_tools.exe",
    L"sharedintapp.exe",
    L"vmconnect.exe",
    L"vmms.exe",
    L"vmwp.exe",
    L"vmusr.exe",
    L"VBoxWindowsAdditions.exe",
    L"x64dbg.exe",
    L"x64gui.exe",
    L"x32gui.exe",
    L"windbg.exe",
    L"dbgx.shell.exe",
    L"dbgsrv.exe",
    L"dbgrpc.exe",
    L"gflags.exe"
};

bool upd() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);

    if (Process32FirstW(snap, &pe)) {
        do {
            for (const auto& vm_proc : aioyq1) {
                if (_wcsicmp(pe.szExeFile, vm_proc.data()) == 0) {
                    CloseHandle(snap);
                    return true;
                }
            }
        } while (Process32NextW(snap, &pe));
    }

    CloseHandle(snap);
    return false;
}

void rim(unsigned long long min_ram_mb) {
    MEMORYSTATUSEX mem_info{};
    mem_info.dwLength = sizeof(mem_info);
    
    if (GlobalMemoryStatusEx(&mem_info)) {
        unsigned long long ram_mb = mem_info.ullTotalPhys / 1024 / 1024;
        if (ram_mb < min_ram_mb) {
            ExitProcess(0);
        }
    }
}

void zah() {
    SYSTEM_INFO sysinf;
    GetSystemInfo(&sysinf);

    unsigned long long cor = sysinf.dwNumberOfProcessors;
    if (cor < 4) {
        ExitProcess(0);
    }
}

void dsk() {
    ULARGE_INTEGER freeToCaller, total, freeTotal;

    if (GetDiskFreeSpaceExW(L"C:\\", &freeToCaller, &total, &freeTotal)) {
        double totalGB = (double)total.QuadPart / (1024.0 * 1024.0 * 1024.0);
        if (totalGB < 60.0) {
            ExitProcess(0);
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (IsDebuggerPresent()) {
        ExitProcess(0);
    }

    if (upd()) {
        ExitProcess(0);
    }

    rim(4096);
    zah();
    dsk();

    return 0;
}