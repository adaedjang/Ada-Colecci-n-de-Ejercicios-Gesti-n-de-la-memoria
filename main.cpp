#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

int main() {
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        SIZE,
        NULL);

    if (hMapFile == NULL) {
        printf("Error al crear la memoria compartida (%d).\n", GetLastError());
        return 1;
    }

    char *shared_memory = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        SIZE);

    if (shared_memory == NULL) {
        printf("Error al mapear la memoria compartida (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(shared_memory, "Hello, child process!");
    printf("Mensaje en memoria compartida: %s\n", shared_memory);
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);

    return 0;
}

// Explicacion:Este código es una implementación en C que utiliza memoria compartida en el sistema operativo Windows. A diferencia del código anterior para sistemas UNIX (Linux). UNIX usa mmap para crear y mapear la memoria anónima compartida, y munmap para liberarla. UNIX usa mmap para crear y mapear la memoria anónima compartida, y munmap para liberarla. Windows usa CreateFileMapping para crear el objeto de memoria compartida y MapViewOfFile para asignarlo en el espacio de direcciones del proceso; UnmapViewOfFile y CloseHandle son necesarios para liberar los recursos. (fuente chatgpt)


