#include <string.h>

int strStr(char* haystack, char* needle) {
    for (int i = 0, n = strlen(haystack); i < n; i++) {
        if (haystack[i] == needle[0]) {
            int found = 1;
            for (int j = 0, m = strlen(needle); j < m; j++) {
                if (i + j >= n) return -1;
                if (haystack[i + j] != needle[j]) {
                    found = 0;
                    break;
                }
            }
            if (found) return i;
        }
    }

    return -1;    
}