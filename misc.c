#include <stdio.h>
#include <stdlib.h>
#define APP_VERSION "1.0"

void display_version()
{
    printf("----rtmodx64----\r\n");
    printf("Utility written by Rohit Jacob\r\n");
    printf("Version=%s\r\n", APP_VERSION);
}

void display_help()
{
    printf("----rtmodx64----\r\n");
    printf("USAGE: rtmodx64 [<OPTIONS>] <FILE> [-o <OUTPUT-FILE>]\r\n");
    printf("If -o option is not given then a .rm file with same filename as input file will be generated...\r\n");
    printf("OPTIONS: \r\n");
    printf("-v or --version: Display version information\r\n");
    printf("-h or --help: Display this help menu\r\n");
    printf("NOTES: rtmod does not support redirections, which means don't do this:\r\n");
    printf("somecommand someinput | rtmodx64\r\n");
    printf("or this:\r\n");
    printf("rtmodx64 <INPUT> > somefile OR rtmodx64 <INPUT> | somecommand\r\n");
    printf("rtmod will simply exit with an error in this case instead of handling the redirection\r\n");
}