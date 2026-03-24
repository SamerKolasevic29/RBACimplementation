#include "../../include/editor/Editor.h"
#include <fstream>

  // Load file into lines vector. If file doesn't exist, initialize with one empty line
  // so the editor always has a valid state to work with
  Editor::Editor(const std::string& filename, const std::string& username, const std::string& role)
      : _cx(0), _cy(0), _offsetY(0),
        _filename(filename), _username(username), _role(role), _modified(false) {
  
      std::ifstream f(filename);
      if (!f) { _lines.push_back(""); return; }
  
      std::string line;
      while (getline(f, line)) _lines.push_back(line);
      if (_lines.empty()) _lines.push_back("");
  }

  // Status bar occupies the last terminal row.
  // Displays: [ROLE] username | filename [+] on the left, cursor position + shortcuts on the right.
  void Editor::drawStatusBar() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    attron(A_REVERSE);
    std::string left = " [" + _role + "] " + _username + " | " + _filename;
    if (_modified) left += " [+]"; // [+] indicates unsaved changes
    std::string right = std::to_string(_cy + 1) + ":" + std::to_string(_cx + 1)
                      + " | ^S Save  ^Q Quit ";

    std::string bar = left;
    while ((int)bar.size() < cols - (int)right.size()) bar += " ";
    bar += right;

    mvprintw(rows - 1, 0, "%s", bar.substr(0, cols).c_str());
    attroff(A_REVERSE);
}

  // Keep cursor within the visible terminal window.
  // _offsetY tracks which line of _lines is rendered at the top of the screen.
  void Editor::scrollView() {
      int rows, cols;
      getmaxyx(stdscr, rows, cols);
      (void)cols;
      if (_cy < _offsetY) _offsetY = _cy;  // scroll up
      if (_cy >= _offsetY + rows - 1) _offsetY = _cy - rows + 2; // scroll down
  }
  
  // Render current state of _lines to screen.
  // rows-1 lines are available for text content, last row is reserved for status bar.
  // Screen position of cursor: (_cy - _offsetY, _cx) — vector index offset by scroll.
  void Editor::draw() {
      int rows, cols;
      getmaxyx(stdscr, rows, cols);
      clear();
  
      for (int i = 0; i < rows - 1; i++) {
          int lineIdx = i + _offsetY;
          if (lineIdx < (int)_lines.size())
              mvprintw(i, 0, "%s", _lines[lineIdx].substr(0, cols).c_str());
      }
  
      drawStatusBar();
      move(_cy - _offsetY, _cx);
      refresh();
  }
  
  void Editor::handleKey(int ch) {
      std::string& line = _lines[_cy];  // reference to current line — edits apply directly to vector
  
      switch(ch) {

        // --- Navigation ---
          case KEY_UP:
              if (_cy > 0) { _cy--; _cx = std::min(_cx, (int)_lines[_cy].size()); }
              break;

          case KEY_DOWN:
              if (_cy < (int)_lines.size() - 1) { _cy++; _cx = std::min(_cx, (int)_lines[_cy].size()); }
              break;

          case KEY_LEFT:
              if (_cx > 0) _cx--;
              else if (_cy > 0) { _cy--; _cx = _lines[_cy].size(); }
              break;

          case KEY_RIGHT:
              if (_cx < (int)line.size()) _cx++;
              else if (_cy < (int)_lines.size() - 1) { _cy++; _cx = 0; }
              break;

          case KEY_HOME: _cx = 0; break;
          case KEY_END:  _cx = line.size(); break;
  
          case '\n': case KEY_ENTER: {
              std::string rest = line.substr(_cx);
              _lines[_cy] = line.substr(0, _cx);
              _lines.insert(_lines.begin() + _cy + 1, rest);
              _cy++; _cx = 0;
              _modified = true;
              break;
          }

          case 127: case KEY_BACKSPACE:
              if (_cx > 0) { line.erase(_cx - 1, 1); _cx--; _modified = true; }
              else if (_cy > 0) {
                  _cx = _lines[_cy - 1].size();
                  _lines[_cy - 1] += line;
                  _lines.erase(_lines.begin() + _cy);
                  _cy--; _modified = true;
              }
              break;
              
          case KEY_DC:
              if (_cx < (int)line.size()) { line.erase(_cx, 1); _modified = true; }
              else if (_cy < (int)_lines.size() - 1) {
                  _lines[_cy] += _lines[_cy + 1];
                  _lines.erase(_lines.begin() + _cy + 1);
                  _modified = true;
              }
              break;

          case 19: // Ctrl+S
              {
                  std::ofstream f(_filename, std::ios::trunc);
                  for (const auto& l : _lines) f << l << "\n";
                  _modified = false;
              }
              break;

          default:
              if (ch >= 32 && ch < 127) {
                  line.insert(_cx, 1, (char)ch);
                  _cx++; _modified = true;
              }
              break;
      }
      scrollView();
  }
  
  bool Editor::isModified() const { return _modified; }
  
  std::string Editor::getContent() const {
      std::string result;

      for (const auto& l : _lines) result += l + "\n";
        return result;
  }
  
  // Main editor loop. Returns true if user exited cleanly, false if exited without saving.
  // Caller (WorkerController) uses return value to decide whether to log the action.
  bool Editor::run() {
      initscr();
      raw();
      noecho();
      keypad(stdscr, TRUE);
  
      while (true) {
          draw();
          int ch = getch();
  
          if (ch == 17) { // Ctrl+Q
              if (_modified) {
                  int rows, cols;
                  getmaxyx(stdscr, rows, cols);
                  attron(A_REVERSE);
                  mvprintw(rows - 1, 0, "%-*s", cols, " Unsaved changes! Quit? (y/n): ");
                  attroff(A_REVERSE);
                  refresh();
                  int c = getch();
                  if (c == 'y' || c == 'Y') { endwin(); return false; } 
              } else { endwin(); return true; }
          } else {
              handleKey(ch);
          }
      }
  }
  
  