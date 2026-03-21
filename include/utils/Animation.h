#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

namespace Animation {

    enum Color {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
        BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW,
        BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE
    };

    inline const char* getAnsiCode(Color c) {
        switch(c) {
            case BLACK:         return "\033[30m";
            case RED:           return "\033[31m";
            case GREEN:         return "\033[32m";
            case YELLOW:        return "\033[33m";
            case BLUE:          return "\033[34m";
            case MAGENTA:       return "\033[35m";
            case CYAN:          return "\033[36m";
            case WHITE:         return "\033[37m";
            case BRIGHT_BLACK:  return "\033[90m";
            case BRIGHT_RED:    return "\033[91m";
            case BRIGHT_GREEN:  return "\033[92m";
            case BRIGHT_YELLOW: return "\033[93m";
            case BRIGHT_BLUE:   return "\033[94m";
            case BRIGHT_MAGENTA:return "\033[95m";
            case BRIGHT_CYAN:   return "\033[96m";
            case BRIGHT_WHITE:  return "\033[97m";
            default:            return "\033[0m"; 
        }
    }

    // Reset Color
    inline void reset() {
         std::cout << "\033[0m";
    }

    inline void sq(Color c) {
        // Block character (ASCII extended 178 or Unicode equivalent)
        // Note: In some terminals, extended ASCII might act weird. 
        // Using a safe UTF-8 block is better, but stick to your char if it works for you.
         
        std::cout << getAnsiCode(c) << "\u2588";
    }

    inline void clearScreen() {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    inline void moveCursor(int row, int col) {
        std::cout << "\033[" << row << ";" << col << "H" << std::flush;
    }

    inline void repeatChar(char ch, int count) {
        for(int i = 0; i < count; i++)
            std::cout << ch;
    }

    inline void wait(int s){
        std::this_thread::sleep_for(std::chrono::seconds(s));
    }


    //--- [Complex animations ] ---

    inline void writeLine(const std::string s = "", Color c = WHITE, int delay = 100){
        std::cout << getAnsiCode(c);
        for(char ch : s){
            std::cout << ch << std::flush; 
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        } 
        std::cout << getAnsiCode(WHITE);
    }

    inline void writeColumnText(const std::string& s, int width, Color c = WHITE, int delay = 0) {
        std::cout << getAnsiCode(c);
        for(char ch : s){
            std::cout << ch << std::flush;
            if(delay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        if ((int)s.length() < width) {
            std::cout << std::string(width - s.length(), ' ');
        }
        std::cout << getAnsiCode(WHITE);
    }

    inline void loading(const std::string& text = "", int rotation = 3, int delay = 300, Color c = WHITE){
        const std::string s = "-/|\\-/|\\";
        std::cout << getAnsiCode(c);
        for(int x = 1; x <= rotation; x++){
            for(size_t i=0; i < s.length(); i++){
                std::cout << text << " " << s[i] << std::flush; 
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "\r";
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << getAnsiCode(WHITE);
    }

    inline void thinking(const std::string& text = "", Color c = WHITE, int rotation = 3, int delay = 300){
        const std::string sequence[] = {"", ".", ". .", ". . ."};
        std::cout << getAnsiCode(c);
        for(int x = 1; x <= rotation; x++){
            for(const std::string& s : sequence) {
                std::cout << "\r" << text << " " << s << "     " << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
        }
        std::cout << getAnsiCode(WHITE);
    }

    inline void bar(int seg = 4 ,Color c = WHITE, int delay = 300){
    // Unicode Block
    std::cout << getAnsiCode(c) << "[ ";
    for(int i=0; i<seg; i++){
        std::cout << "\u2588" << std::flush; // using unicode directly
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << " ]" << getAnsiCode(WHITE) << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

    inline void blinking(const std::string s = "", Color c = WHITE, int delay = 300, int reps = 3) {
        std::string blank(s.size(), ' ');
        
        std::cout << "\033[?25l" << std::flush; 
        
        for(int i = 0; i < reps; i++){
            std::cout << getAnsiCode(c) << "\033[?25l" << s << getAnsiCode(WHITE) << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            
            std::cout << "\r" << blank << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        std::cout << "\033[?25h" << std::flush;
    }


} //namespace Animation

#endif