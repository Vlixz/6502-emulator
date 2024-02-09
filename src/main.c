#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "6502.h"
#include "memory.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define PADDING 7
#define MAX_WINDOW_WIDTH 94
#define POP_UP_WIDTH 90
#define POP_UP_HEIGHT 5

WINDOW *window_current_instruction;
WINDOW *window_memory;
WINDOW *window_hints;
WINDOW *window_breakpoints;

int terminal_height;
int terminal_width;
int memory_start_addr = 0x0000;
int reset_vector;

char *binary_file_location;

execution_information current_execution_information;

void draw_ui(void);

void ncurses_init(void) {
    initscr();   // Start ncurses
    cbreak();    // Allow quiting with ^C
    noecho();    // Don't echo any keypresses
    curs_set(0); // Hide the cursor
}

void handle_resize(int sig) {
    endwin();    // End ncurses
    refresh();   // Refresh the terminal
    clear();     // Clear the terminal

    ncurses_init();

    draw_ui();   // Redraw the UI
}

bool running = false;
void sigterm_handler(int signum) {
    running = false;
}

void print_flags(WINDOW *window) {
    char flags[] = {'C', 'Z', 'I', 'D', 'B', 'V', 'N'};
 
    int y, x;
    getmaxyx(window, y, x);

    int offset = (x - 2 * PADDING) / sizeof(flags);

    mvwprintw(window, 0, 1, "Flags");

    mvwprintw(window, 4, PADDING + offset * 0, "%c: %d", flags[0], cpu.C);
    mvwprintw(window, 4, PADDING + offset * 1, "%c: %d", flags[1], cpu.Z);
    mvwprintw(window, 4, PADDING + offset * 2, "%c: %d", flags[2], cpu.I);
    mvwprintw(window, 4, PADDING + offset * 3, "%c: %d", flags[3], cpu.D);
    mvwprintw(window, 4, PADDING + offset * 4, "%c: %d", flags[4], cpu.B);
    mvwprintw(window, 4, PADDING + offset * 5, "%c: %d", flags[5], cpu.V);
    mvwprintw(window, 4, PADDING + offset * 6, "%c: %d", flags[6], cpu.N);
}

void print_registers(WINDOW *window) {
    mvwprintw(window, 0, 1, "Executed Instruction: %s", (current_execution_information.ins.name == NULL) ? "XXX" : current_execution_information.ins.name);

    mvwprintw(window, 2, PADDING, "Program Counter: 0x%04X", cpu.PC);
    mvwprintw(window, 6, PADDING, "Accumulator:   0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.A, BYTE_TO_BINARY(cpu.A), cpu.A);
    mvwprintw(window, 7, PADDING, "Register X:    0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.X, BYTE_TO_BINARY(cpu.X), cpu.X);
    mvwprintw(window, 8, PADDING, "Register Y:    0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.Y, BYTE_TO_BINARY(cpu.Y), cpu.Y);
    mvwprintw(window, 9, PADDING, "Stack Pointer: 0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.SP, BYTE_TO_BINARY(cpu.SP), cpu.SP);
}

void print_hints(WINDOW *window) {
    mvwprintw(window, 0, 1, "Hints");

    mvwprintw(window, 2, 2, "'q' : quit");
    mvwprintw(window, 3, 2, "'r' : reset");
    mvwprintw(window, 4, 2, "'s' : step");
    mvwprintw(window, 5, 2, "'c' : continue");
    mvwprintw(window, 6, 2, "'b' : set breakpoint");
    mvwprintw(window, 7, 2, "'d' : delete breakpoint");
    mvwprintw(window, 8, 2, "'m' : print memory");
    mvwprintw(window, 9, 2, "'p' : stop");
}

void print_breakpoints(WINDOW *window) {
    mvwprintw(window, 0, 1, "Breakpoints");

    mvwprintw(window, 2, 2, "not implemented yet");
}

void print_memory(WINDOW *window) {
    
    int y, x;
    getmaxyx(window, y, x);

    y -= 4; // padding 

    int x_offset = (x - 2 * 4 - 54) / 2;

    int character_len = 54;

    int mem_address = memory_start_addr;

    mvwprintw(window, 0, 1, "Memory");
    
    for (int i = 0; i < 16; i++) {
        mvwprintw(window, 2,  x_offset + 8 + 3 + i * 3, "%02X", i);
    }

    for (int i = 0; i < y && mem_address < 0xFFFF; i++) {
       
        mvwprintw(window, 3 + i, x_offset + 4, "0x%04X", mem_address);
        for (int j = 0; j < 16; j++) {
            int value = mem_read(mem_address++);

            mvwprintw(window, 3 + i, x_offset + 8 + 3 + j * 3, "%02X", value);
        }
    }
}
void draw_ui(void) {
    clear();

    getmaxyx(stdscr, terminal_height, terminal_width);
    
    int x_offset = 0;
    if (terminal_width > MAX_WINDOW_WIDTH) {
        x_offset = (terminal_width - MAX_WINDOW_WIDTH) / 2;
        terminal_width = MAX_WINDOW_WIDTH;
    }
    
    int totalWidth = 26 + 58 + 2 + (2 *  4);

    // nLines, nCols, y, x

    /* Window Hints */
    window_hints = newwin(12, 26, 2, terminal_width - 30 + x_offset);
    box(window_hints, 0, 0);
    print_hints(window_hints);

    /* Window Current instruction */
    window_current_instruction= newwin(12, 58, 2, 4 + x_offset);
    box(window_current_instruction, 0, 0);

    /* Window Breakpoints */
    window_breakpoints = newwin(terminal_height - 3 - 12, 26, 14, terminal_width - 30 + x_offset);
    box(window_breakpoints, 0, 0);

    /* Window Memory */
    window_memory = newwin(terminal_height - 3 - 12, 58, 14, 4 + x_offset);
    box(window_memory, 0, 0);

    print_flags(window_current_instruction);
    print_registers(window_current_instruction);
    print_breakpoints(window_breakpoints);
    print_memory(window_memory);

    refresh();

    wrefresh(window_current_instruction);
    wrefresh(window_hints);
    wrefresh(window_breakpoints);
    wrefresh(window_memory);
}

void update_ui(void) {
    print_flags(window_current_instruction);
    print_registers(window_current_instruction);
    print_breakpoints(window_breakpoints);
    print_memory(window_memory);

    wrefresh(window_current_instruction);
    wrefresh(window_hints);
    wrefresh(window_breakpoints);
    wrefresh(window_memory);
}

// Display an input box popup
void display_input_box(const char *prompt, char *input, int max_length) {

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int start_y = (screen_height - POP_UP_HEIGHT) / 2;
    int start_x = (screen_width - POP_UP_WIDTH) / 2;

    WINDOW *popup = newwin(POP_UP_HEIGHT, POP_UP_WIDTH, start_y, start_x);
    box(popup, 0, 0);

    mvwprintw(popup, 2, 2, "%s: ", prompt);

    wmove(popup, 2, strlen(prompt) + 4);
    echo();
    wgetnstr(popup, input, max_length);
    noecho();

    wrefresh(popup);

    delwin(popup);
    clear();
    draw_ui();
}

int handle_input() {
    
    char ch, input[10];
    int pid; 
    while((ch = getch()) != 'q') {

        switch (ch) {
            case 'r':
                // reset cpu

                if (running) {
                    running = false;
                    kill(pid, SIGTERM);
                    wait(NULL);
                }

                mem_read_bin_file(binary_file_location);

                em6502_reset(&cpu, reset_vector);

                draw_ui();

                break;
            case 's':
                
                if (running) 
                    break;

                current_execution_information = em6502_execute_instruction();

                break;
            case 'c':                
                // continue
                
                if(running)
                    break;

                running = true;
                pid = fork();
                
                if (pid < 0) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (pid == 0) {
                    while (1) {
                        current_execution_information = em6502_execute_instruction();
                        update_ui();
                        if (!running) {
                            exit(EXIT_SUCCESS);
                        }
                    }
                }

                break;
            case 'b':
                // set breakpoint
                break;
            case 'd':
                // delete breakpoint
                break;
            case 'm':
                // print memory

                if (running) {
                    running = false;
                    kill(pid, SIGTERM);
                    wait(NULL);
                }
                
                display_input_box("memory address", input, 10);
                memory_start_addr = strtol(input, NULL, 16) & 0xFFF0;
                
                // clear the screen and redraw the UI
                // clear();
                draw_ui();

                break;
            case 'p':
                // stop

                if (running) { 
                    running = false;
                    kill(pid, SIGTERM);
                    wait(NULL);
                }

                break;
        }

        update_ui();
    }
}


int main(int argc, char **argv) {

    if (argc < 2 || argc > 5 || argc == 3) {
        printf("Usage: %s <bin_file>\n", argv[0]);
        printf("Usage: %s <bin_file> -r <reset_vector>\n", argv[0]);
        return 1;
    }

    ncurses_init();

    signal(SIGWINCH, handle_resize);
    signal(SIGTERM, sigterm_handler);

    draw_ui();

    // Load the binary file into memory
    binary_file_location = argv[1];
    reset_vector = strtol(argv[3], NULL, 16);

    mem_read_bin_file(binary_file_location);

    em6502_reset(&cpu, reset_vector);

    update_ui();

    handle_input();

    delwin(window_current_instruction);
    endwin();

    return 0;
}
