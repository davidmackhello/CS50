// feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// number of bytes for buffers
#define BYTES 512

// header files
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    
    printf("the log value is %i\n", ((int) log10(100) + 1));
    
    unsigned short code = 401;
    
    const char* phrase = "im so sorry";
    
    // template for response's content
    char* templateb = "<html><head><title>%i %s</title></head><body><h1>%i %s</h1></body></html>";
    
    
    printf("the length of template alone is: %i\n", ((int) strlen(templateb)));


    // template for response's content
    char* template = "<html><head><title>%i %s</title></head><body><h1>%i %s</h1></body></html>";

    // render template
    char body[(strlen(template) - 2 - ((int) log10(code) + 1) - 2 + strlen(phrase)) * 2 + 1];
    int length = sprintf(body, template, code, phrase, code, phrase);
    
    printf("length is %i\n", length);

    
}


    