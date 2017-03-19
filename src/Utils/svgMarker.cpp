#include <string>
#include <fstream>
#include <iostream>
#include <Configs.h>

using namespace std;

bool parseSvgLine(const string &line, double &x1, double &y1, double &x2, double &y2) {
    int x1a = line.find_first_of('"',     0); if (x1a == -1) { return false; }
    int x1b = line.find_first_of('"', x1a+1); if (x1b == -1) { return false; }
    int y1a = line.find_first_of('"', x1b+1); if (y1a == -1) { return false; }
    int y1b = line.find_first_of('"', y1a+1); if (y1b == -1) { return false; }
    int x2a = line.find_first_of('"', y1b+1); if (x2a == -1) { return false; }
    int x2b = line.find_first_of('"', x2a+1); if (x2b == -1) { return false; }
    int y2a = line.find_first_of('"', x2b+1); if (y2a == -1) { return false; }
    int y2b = line.find_first_of('"', y2a+1); if (y2b == -1) { return false; }
    if (1 != sscanf(line.substr(x1a+1, x1b-x1a-1).c_str(), "%lf", &x1)) { return false; }
    if (1 != sscanf(line.substr(y1a+1, y1b-y1a-1).c_str(), "%lf", &y1)) { return false; }
    if (1 != sscanf(line.substr(x2a+1, x2b-x2a-1).c_str(), "%lf", &x2)) { return false; }
    if (1 != sscanf(line.substr(y2a+1, y2b-y2a-1).c_str(), "%lf", &y2)) { return false; }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_svg> <output_svg>\n", argv[0]);
        return -1;
    }
    string input_path  = CMAKE_SOURCE_DIR "/pano.pgm.elsd.svg";
    string output_path = CMAKE_SOURCE_DIR "/pano.pgm.elsd.svg.marked.svg";
    if (argc >= 2) { input_path  = argv[1]; }
    if (argc >= 3) { output_path = argv[2]; }
    ifstream input(  input_path.c_str(), ifstream::in);
    ofstream output(output_path.c_str(), ifstream::out);
    if (!input || !output ) {
        fprintf(stderr, "Cannot open svg image for reading a/o writing.\n");
        return -2;
    }
    string line;
    int id = 0;
    while (getline(input, line)) {
        double x1, y1, x2, y2;
        bool okay = true;
        if (line.substr(0,5) == "<line" && (okay = parseSvgLine(line, x1, y1, x2, y2))) {
            output << "<g><title>" << id++ << "</title>";
            output << line;
            char *format = "<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:limegreen;stroke:maroon;stroke-width:1\" />";
            char buf[500];
            snprintf(buf, 500, format,
                x1 + 1, y1 - 1,
                x1 - 1, y1 - 1,
                x1 - 1, y1 + 1,
                x1 + 1, y1 + 1);
            output << buf;
            snprintf(buf, 500, format,
                x2 + 1, y2 - 1,
                x2 - 1, y2 - 1,
                x2 - 1, y2 + 1,
                x2 + 1, y2 + 1);
            output << buf;
            output << "</g>\n";
        } else {
            if (!okay) {
                cerr << "#BadLine: " << line << "\n";
            }
            output << line << "\n";
        }
    }
    input.close();
    output.close();
    return 0;
}