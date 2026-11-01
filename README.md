# Anti-VM

# Windows Environment & Anti-Analysis Detection Demo (C++)

A lightweight C++ educational tool showcasing standard techniques used to detect analysis environments, debuggers, and virtual machines (sandboxes) on Windows operating systems using native WinAPI.

## Overview

In the field of Malware Analysis and Reverse Engineering, it is crucial to understand how software can dynamically alter its execution flow when it senses it is being monitored. This project implements basic heuristics to determine whether the application is running inside a production-ready machine or a constrained malware analysis sandbox/virtual environment.

## Implemented Detection Techniques

The application sequentially executes the following checks. If any check fails (environment suspected), the process safely terminates using `ExitProcess(0)`.

*   **Active Debugger Detection:** Uses native API `IsDebuggerPresent()` to check if the current process is running under the context of a user-mode debugger (like x64dbg or Visual Studio).
*   **Process Name Blacklist (Anti-VM / Anti-RE):** Takes a snapshot of running processes via `CreateToolhelp32Snapshot` and scans for artifacts of popular hypervisors and debugging shells (e.g., VirtualBox, VMware, Xen, WinDbg, x64dbg).
*   **Hardware Heuristics (RAM):** Queries physical memory constraints via `GlobalMemoryStatusEx`. Terminates if total RAM is under **4GB**, which is typical for automated malware analysis sandboxes.
*   **Hardware Heuristics (CPU Cores):** Retrieves system information via `GetSystemInfo`. Terminates if the machine has fewer than **4 CPU cores**.
*   **Hardware Heuristics (Disk Capacity):** Checks the size of the primary storage drive (`C:\`) using `GetDiskFreeSpaceExW`. Terminates if the total disk capacity is less than **60GB**, another common indicator of disposable sandbox environments.

## Code Preview & Technologies Used

*   **Language:** C++17 / C++20
*   **Platform:** Windows (x86/x64)
*   **API utilized:** WinAPI (`<windows.h>`, `<tlhelp32.h>`)
*   **Key Standard Libraries:** `std::vector`, `std::wstring_view`

## Educational Disclaimer

This repository is for **educational and research purposes only**. Understanding these detection techniques helps security researchers and blue team engineers design better sandboxes and automated dynamic analysis pipelines that can bypass such checks (e.g., via sandbox hardening).
