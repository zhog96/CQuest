#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//---------------------------------------------------------

int sortFileStrCmp(const char * str1, const char * str2) {
    assert(str1);
    assert(str2);
    assert(str1 != str2);

    char ignore[] = ",.?<>\"\'()!*%:;-~[]&";

    while(*str1 || *str2) {
        while(*str1 && strchr(ignore, *str1)) str1++;
        while(*str2 && strchr(ignore, *str2)) str2++;
        if(!*str2) return 1;
        if(!*str1) return -1;
        if(*str1 < *str2) return -1;
        if(*str2 < *str1) return 1;
        str1++;
        str2++;
    }
    return 0;
}

//---------------------------------------------------------

int sortFileCmp(const void * v1, const void * v2) {
    assert(v1);
    assert(v2);
    assert(v1 != v2);

    const char * str1 = *((char **) v1);
    const char * str2 = *((char **) v2);
    return sortFileStrCmp(str1, str2);
}

//---------------------------------------------------------

int sortFile(const char * in_path, const char * out_path) {
    assert(in_path);
    assert(out_path);
    assert(strcmp(in_path, out_path) != 0);
    
    FILE *in = NULL;
    
    assert(in = fopen(in_path, "r"));

    int in_size = 0;
    fseek(in, 0ll, SEEK_END);
    assert(in_size = ftell(in));

    char * buffer = new char[in_size + 1];
    assert(buffer);
    buffer[in_size] = 0;

    fseek(in, 0ll, SEEK_SET);
    fread(buffer, sizeof(char), in_size, in);

    int lines_count = 0;
    for(int i = 0; i < in_size; i++) {
        if(buffer[i] == '\n' || i == in_size - 1) {
            lines_count++;
        }
    }

    char ** lines = new char * [lines_count];
    lines[0] = buffer;
    for(int i = 0, line_k = 1; i < in_size; i++) {
        if(buffer[i] == '\n') {
            if(i < in_size) lines[line_k++] = buffer + i + 1;
            buffer[i] = 0;
        }
    }

    qsort(lines, lines_count, sizeof(char *), sortFileCmp);

    FILE * out = NULL;

    assert(out = fopen(out_path, "w"));
    
    fseek(out, 0ll, SEEK_SET);

    for(int i = 0; i < lines_count; i++) {
        int size = 0;
        assert(lines[i]);
        size = strlen(lines[i]);

        char * buf = new char[size + 1];
        assert(buf);

        strcpy(buf, lines[i]);
        buf[size] = '\n';
        
        fwrite(buf, sizeof(char), size + 1, out);

        delete [] buf;
    }

    delete [] buffer;
    delete [] lines;

    return 0;
}

//---------------------------------------------------------

int main() {
    sortFile("Onegin.txt", "SortedOnegin.txt");

    return 0;
};
