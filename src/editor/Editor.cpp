#include "../../include/editor/Editor.h"
#include <fstream>

Editor::Editor(const std::string& filename, const std::string& username, const std::string& role)
    : _cx(0), _cy(0), _offsetY(0),
      _filename(filename), _username(username), _role(role), _modified(false) {

    std::ifstream f(filename);
    if (!f) { _lines.push_back(""); return; }

    std::string line;
    while (getline(f, line)) _lines.push_back(line);
    if (_lines.empty()) _lines.push_back("");
}