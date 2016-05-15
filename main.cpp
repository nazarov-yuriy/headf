#include <iostream>
#include <getopt.h>
#include <cstring>
#include <cstdio>

using namespace std;

void usage(char *prog_name) {
    cout << "Use: " << prog_name << " -n 42 -f filename" << endl;
}

//ToDo: impement file watching
void headf(int lines, const char *filename) {
    FILE *fp = stdin;
    if (strcmp("-", filename)) {
        fp = fopen(filename, "r");
    }
    char buf[4096];
    if (fp != NULL) {
        for (int i = 0; i < lines; i++) {
            buf[sizeof(buf) - 1] = 0;
            if (fgets(buf, sizeof(buf) - 1, fp) != NULL) {
                cout << buf;
            }
        }
        fclose(fp);
    } else {
        perror("Failed to open specified file");
    }
}

int main(int argc, char **argv) {
    int c;
    opterr = 0;
    int lines = 0;
    while ((c = getopt(argc, argv, "n:f:")) != -1) {
        switch (c) {
            case 'n':
                lines = atoi(optarg);
                if (lines <= 0) {
                    usage(argv[0]);
                    return 1;
                }
                break;
            default:
                usage(argv[0]);
                return 1;
        }
    }
    if (optind < argc) {
        headf(lines, argv[optind]);
    } else {
        headf(lines, "-");
    }
    return 0;
}