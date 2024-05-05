#include "user_interface.h"

#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "6502.h"
#include "memory.h"

#define FPS 60
#define FRAME_TIME (1000 / FPS)

#define PADDING 7
#define MAX_WINDOW_WIDTH 94

#define POP_UP_WIDTH 90
#define POP_UP_HEIGHT 5

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


WINDOW *window_current_instruction;
WINDOW *window_breakpoints;
WINDOW *window_memory;
WINDOW *window_hints;

int terminal_height;
int terminal_width;

char* current_instruction_name; 

int draw_memory_start_address = 0x0000;

pthread_t thread_user_interface;
 
pthread_mutex_t mutex_user_interface;
pthread_cond_t cond_user_interface;

void ncurses_init(void);
void user_interface_create(void);

void update_window_hints(void);
void update_window_memory(void);
void update_window_breakpoints(void);
void update_window_current_instruction(void);

/**
 * Handle logic stuff
 * 
*/

void *handle_user_interface(void *arg) {
  
    while(1) {
        pthread_mutex_lock(&mutex_user_interface);

        pthread_cond_wait(&cond_user_interface, &mutex_user_interface);

        update_window_memory();
        update_window_current_instruction();

        pthread_mutex_unlock(&mutex_user_interface);

        usleep(FRAME_TIME * 1000);
    }
}

void handle_resize(int sig) {

    delwin(window_current_instruction);
    delwin(window_breakpoints);
    delwin(window_memory);
    delwin(window_hints);
   
    endwin();

    ncurses_init();

    user_interface_create();   // Redraw the user interface
}

/**
 * Helper functions
 * 
*/

WINDOW* create_newwin(int height, int width, int starty, int startx) {
    WINDOW *window = newwin(height, width, starty, startx);
    box(window, 0, 0);
    return window;
}

void ncurses_init(void) {
    initscr();   // Start ncurses
    cbreak();    // Allow quiting with ^C
    noecho();    // Don't echo any keypresses
    curs_set(0); // Hide the cursor

    signal(SIGWINCH, handle_resize);
}

/**
 * Public functions
 * 
*/

void user_interface_init(void) {
    
    ncurses_init();
    user_interface_create();

    pthread_cond_init(&cond_user_interface, NULL);
    pthread_mutex_init(&mutex_user_interface, NULL);

    if (pthread_create(&thread_user_interface, NULL, handle_user_interface, NULL) != 0) {
        fprintf(stderr, "Error creating user interface thread\n");
        exit(EXIT_FAILURE);
    }
}

void user_interface_destory(void) {

    pthread_cancel(thread_user_interface);

    pthread_join(thread_user_interface, NULL);

    pthread_mutex_destroy(&mutex_user_interface);
    pthread_cond_destroy(&cond_user_interface);

    delwin(window_current_instruction);
    delwin(window_breakpoints);
    delwin(window_memory);
    delwin(window_hints);

    endwin();
}

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

    user_interface_create();
}


/**
 * All the different windows
 * 
*/

void user_interface_create(void) {
    
    clear();
    getmaxyx(stdscr, terminal_height, terminal_width);
    
    /* Center everything */
    int x_offset = (terminal_width > MAX_WINDOW_WIDTH) ? (terminal_width - MAX_WINDOW_WIDTH) / 2 : 0;
    terminal_width = (terminal_width > MAX_WINDOW_WIDTH) ? MAX_WINDOW_WIDTH : terminal_width;
    
    window_current_instruction = create_newwin(12, 58, 2, 4 + x_offset);
    window_breakpoints = create_newwin(terminal_height - 3 - 12, 26, 14, terminal_width - 30 + x_offset);
    window_memory = create_newwin(terminal_height - 3 - 12, 58, 14, 4 + x_offset);
    window_hints = create_newwin(12, 26, 2, terminal_width - 30 + x_offset);

    refresh();

    update_window_memory();
    update_window_current_instruction();

    /* Never updated after this */
    update_window_hints();
    update_window_breakpoints();
}

void update_window_hints(void) {
    werase(window_hints);
    box(window_hints, 0, 0);

    mvwprintw(window_hints, 0, 1, "Hints");

    mvwprintw(window_hints, 2, 2, "'q' : quit");
    mvwprintw(window_hints, 3, 2, "'r' : reset");
    mvwprintw(window_hints, 4, 2, "'s' : step");
    mvwprintw(window_hints, 5, 2, "'c' : continue");
    mvwprintw(window_hints, 6, 2, "'b' : set breakpoint");
    mvwprintw(window_hints, 7, 2, "'d' : delete breakpoint");
    mvwprintw(window_hints, 8, 2, "'m' : print memory");
    mvwprintw(window_hints, 9, 2, "'p' : stop");

    wrefresh(window_hints);
}

void update_window_breakpoints(void) {
    werase(window_breakpoints);
    box(window_breakpoints, 0, 0);

    mvwprintw(window_breakpoints, 0, 1, "Breakpoints");
    mvwprintw(window_breakpoints, 2, 2, "not implemented yet");

    wrefresh(window_breakpoints);
}

void update_window_current_instruction(void) {
    werase(window_current_instruction);
    box(window_current_instruction, 0, 0);

    const char flags[] = {'C', 'Z', 'I', 'D', 'B', 'V', 'N'};

    int y, x;
    getmaxyx(window_current_instruction, y, x);

    int offset = (x - 2 * PADDING) / sizeof(flags);
    
    mvwprintw(window_current_instruction, 0, 1, "Last instruction %s", current_instruction_name);
    
    mvwprintw(window_current_instruction, 4, PADDING + offset * 0, "%c: %d", flags[0], cpu.C);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 1, "%c: %d", flags[1], cpu.Z);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 2, "%c: %d", flags[2], cpu.I);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 3, "%c: %d", flags[3], cpu.D);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 4, "%c: %d", flags[4], cpu.B);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 5, "%c: %d", flags[5], cpu.V);
    mvwprintw(window_current_instruction, 4, PADDING + offset * 6, "%c: %d", flags[6], cpu.N);

    mvwprintw(window_current_instruction, 2, PADDING, "Program Counter: 0x%04X", cpu.PC);
    mvwprintw(window_current_instruction, 6, PADDING, "Accumulator:   0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.A, BYTE_TO_BINARY(cpu.A), cpu.A);
    mvwprintw(window_current_instruction, 7, PADDING, "Register X:    0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.X, BYTE_TO_BINARY(cpu.X), cpu.X);
    mvwprintw(window_current_instruction, 8, PADDING, "Register Y:    0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.Y, BYTE_TO_BINARY(cpu.Y), cpu.Y);
    mvwprintw(window_current_instruction, 9, PADDING, "Stack Pointer: 0x%02X 0b"BYTE_TO_BINARY_PATTERN" %d", cpu.SP, BYTE_TO_BINARY(cpu.SP), cpu.SP);

    wrefresh(window_current_instruction);
}

void update_window_memory(void) {
    werase(window_memory);
    box(window_memory, 0, 0);

    int y, x;
    getmaxyx(window_memory, y, x);

    y -= 4; // padding 

    int x_offset = (x - 2 * 4 - 54) / 2;

    int character_len = 54;

    int mem_address = draw_memory_start_address;

    mvwprintw(window_memory, 0, 1, "Memory");
    
    for (int i = 0; i < 16; i++) {
        mvwprintw(window_memory, 2,  x_offset + 8 + 3 + i * 3, "%02X", i);
    }

    for (int i = 0; i < y && mem_address < 0xFFFF; i++) {
       
        mvwprintw(window_memory, 3 + i, x_offset + 4, "0x%04X", mem_address);
        for (int j = 0; j < 16; j++) {
            int value = mem_read(mem_address++);

            mvwprintw(window_memory, 3 + i, x_offset + 8 + 3 + j * 3, "%02X", value);
        }
    }

    wrefresh(window_memory);
}
