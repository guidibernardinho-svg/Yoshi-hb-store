#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

void download_file(const char* url, const char* path)
{
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(path, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
}

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Yoshi Homebrew Store\n");
    printf("A = baixar ftpd\n");
    printf("START = sair\n");

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break;

        if (kDown & KEY_A)
        {
            printf("Baixando...\n");

            download_file(
                "https://github.com/mtheall/ftpd/releases/latest/download/ftpd.3dsx",
                "sdmc:/3ds/ftpd/ftpd.3dsx"
            );

            printf("Instalado!\n");
        }

        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
