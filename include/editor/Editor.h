#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>
#include <ncurses.h>

class Editor {
private:
    std::vector<std::string> _lines;
    int _cx, _cy;        // cursor position
    int _offsetY;        // scroll offset
    std::string _filename;
    std::string _username;
    std::string _role;
    bool _modified;

    void drawStatusBar();
    void scrollView();

public:
    Editor(const std::string& filename, const std::string& username, const std::string& role);

    void draw();
    void handleKey(int ch);
    bool isModified() const;

    // vraca sadrzaj kao string za logger
    std::string getContent() const;

    // pokrece editor, vraca false ako je korisnik izasao bez snimanja
    bool run();
};

#endif
