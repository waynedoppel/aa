#include <Windows.h>
#using <System.Windows.Forms.dll>
#include "form1.h"

using namespace System;
using namespace System::Windows::Forms;

// Proteção para não executar duas vezes
bool g_hasAlreadyExecuted = false;
HMODULE g_hSelf = NULL;

// Função que roda o painel
static void __clrcall RunPainelForm() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew BraveDllFull::form1());
}

// Thread principal (chamada por DllMain ou EntryPoint)
DWORD WINAPI MainThread(LPVOID) {
    if (g_hasAlreadyExecuted)
        return 0;

    g_hasAlreadyExecuted = true;

    System::Threading::Thread^ t = gcnew System::Threading::Thread(
        gcnew System::Threading::ThreadStart(&RunPainelForm)
    );
    t->SetApartmentState(System::Threading::ApartmentState::STA);
    t->Start();

    return 0;
}

// 🚀 Para hijacking (executado automaticamente ao ser carregado)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_hSelf = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
    }
    return TRUE;
}

// 🚀 Para uso com rundll32.exe
extern "C" __declspec(dllexport) void EntryPoint() {
    CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
}
