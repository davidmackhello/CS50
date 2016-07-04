// calling function
// opens file
//   
    ****Calling function
    BYTE* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        error(500);
        return;
    }

//


bool load(FILE* file, BYTE** content, size_t* length)
{
    // initialize content and length, and create tracker for buffer size
    *content = NULL;
    *length = 0;
    ssizet bytes;
    
    // create buffer
    BYTE buffer[BYTES];
    
    // read file data into buffer
    do
    {
        // store size of buffer read
        bytes = fread(buffer, 1, BYTES, file);
        
        // reallocate memory for *content with new size
        realloc(*content, (*length + bytes));
        if (*content == NULL)
        {
            error(501);
            return false;
        }
        
        // copy buffer contents into *content at appropriate position
        memcpy((*content + *length), buffer, bytes);
        
        // update length
        *length += bytes;
    
    // end loop when bytes does not equal expected return value (signifying EOF)    
    } while (bytes != BYTES)
    
    // ensure data loaded properly
    if (*content == NULL)
    {
        return false;
    }
    
    else
    {
        return true;
    }
}






bool request(char** message, size_t* length)
{
    
    // initialize message and its length
    *message = NULL;
    *length = 0;

    // read message 
    while (*length < LimitRequestLine + LimitRequestFields * LimitRequestFieldSize + 4)
    {
        // read from socket
        BYTE buffer[BYTES];
        ssize_t bytes = read(cfd, buffer, BYTES);
        if (bytes < 0)
        {
            if (*message != NULL)
            {
                free(*message);
                *message = NULL;
            }
            *length = 0;
            break;
        }

        // append bytes to message 
        *message = realloc(*message, *length + bytes + 1);
        if (*message == NULL)
        {
            *length = 0;
            break;
        }
        memcpy(*message + *length, buffer, bytes);
        *length += bytes;

        // null-terminate message thus far
        *(*message + *length) = '\0';

        // search for CRLF CRLF
        int offset = (*length - bytes < 3) ? *length - bytes : 3;
        char* haystack = *message + *length - bytes - offset;
        char* needle = strstr(haystack, "\r\n\r\n");
        if (needle != NULL)
        {
            // trim to one CRLF and null-terminate
            *length = needle - *message + 2;
            *message = realloc(*message, *length + 1);
            if (*message == NULL)
            {
                break;
            }
            *(*message + *length) = '\0';

            // ensure request-line is no longer than LimitRequestLine
            haystack = *message;
            needle = strstr(haystack, "\r\n");
            if (needle == NULL || (needle - haystack + 2) > LimitRequestLine)
            {
                break;
            }

            // count fields in message
            int fields = 0;
            haystack = needle + 2;
            while (*haystack != '\0')
            {
                // look for CRLF
                needle = strstr(haystack, "\r\n");
                if (needle == NULL)
                {
                    break;
                }

                // ensure field is no longer than LimitRequestFieldSize
                if (needle - haystack + 2 > LimitRequestFieldSize)
                {
                    break;
                }

                // look beyond CRLF
                haystack = needle + 2;
            }

            // if we didn't get to end of message, we must have erred
            if (*haystack != '\0')
            {
                break;
            }

            // ensure message has no more than LimitRequestFields
            if (fields > LimitRequestFields)
            {
                break;
            }

            // valid
            return true;
        }
    }


















*****////Old version of lookup
const char* lookup(const char* path)
{
    // set pointer to last '.' in path string
    char* dot = strrchr(path);
    if (dot == NULL)
    {
        return NULL;
    }
    
    //return MIME type based on extensions
    if (strcasecmp(dot, ".css") == 0)
    {
        char* id = "text/css";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".html") == 0)
    {
        char* id = "text/html";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".gif") == 0)
    {
        char* id = "image/gif";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".ico") == 0)
    {
        char* id = "image/x-icon";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".jpg") == 0)
    {
        char* id = "image/jpeg";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".js") == 0)
    {
        char* id = "text/javascript";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".php") == 0)
    {
        char* id = "text/x-php";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    else if (strcasecmp(dot, ".png") == 0)
    {
        char* id = "image/png";
        char* type = malloc((strlen(id) + 1) * sizeof(char));
        strcpy(type, id);
        return type;
    }
    
    // file extension not supported
    else
    {
        return NULL;
    }
}