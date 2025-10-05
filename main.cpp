#include <windows.h>
#include "window.h"


using namespace std;

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    

    int result = CreateAndShowWindow(hInstance, SW_SHOW);
    return result;
}