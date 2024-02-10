#include <string.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "6502.h"
#include "memory.h"

#include "user_interface.h"
#include <regex.h>

int reset_vector;

char *binary_file_location;

enum program_state { RUNNING, PAUSED };

enum program_state program_state;

pthread_t thread_process;
pthread_t thread_execution;

pthread_mutex_t mutex_running;

bool is_valid_hex(const char *str) {
    regex_t regex;
    const char *pattern = "^[0-9a-fA-F]+$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex.\n");
        return false;
    }

    int match = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);

    return (match == 0);
}


/**
 * @brief Handles continous execution, stops on breakpoints, or when the user stops the thread.
 *
 * 
*/
void* handle_execution(void *arg) {

    while (1) {
        pthread_mutex_lock(&mutex_running);
        pthread_mutex_lock(&mutex_user_interface);

        em6502_execute_instruction();

        pthread_cond_signal(&cond_user_interface);

        pthread_mutex_unlock(&mutex_user_interface);

        pthread_mutex_unlock(&mutex_running);
    }

    return NULL;
}

/**
 * @brief Processes the input from the user
 * 
*/
void* handle_process(void *arg) {

    pthread_mutex_lock(&mutex_running);
    program_state = PAUSED;

    while(1) {
        char c = getch();

        switch(c) {
            case 's':

                if (program_state == RUNNING)
                    break;

                pthread_mutex_lock(&mutex_user_interface);

                em6502_execute_instruction();

                pthread_cond_signal(&cond_user_interface);
                pthread_mutex_unlock(&mutex_user_interface);
                
                break;
            case 'c': 
                if(program_state == RUNNING)
                    break;
                
                pthread_mutex_unlock(&mutex_running);
                program_state = RUNNING;
                break;
            case 'p':
                if(program_state == PAUSED)
                    break;

                pthread_mutex_lock(&mutex_running);
                program_state = PAUSED;
                break;

            case 'm':
                char input[6];
                display_input_box("Enter memory address: ", input, 6);

                if (!is_valid_hex(input))
                    break;

                uint16_t address = strtol(input, NULL, 16);

                draw_memory_start_address = address;

                pthread_cond_signal(&cond_user_interface);
                break;

            case 'q':
                return NULL;
        }
    }
}


int main(int argc, char **argv) {

    if (argc < 2 || argc > 5 || argc == 3) {
        printf("Usage: %s <bin_file>\n", argv[0]);
        printf("Usage: %s <bin_file> -r <reset_vector>\n", argv[0]);
        return 1;
    }

    user_interface_init();


    /**
     * Initialize the 6502
     * 
    */
    binary_file_location = argv[1];
    reset_vector = strtol(argv[3], NULL, 16);
    mem_read_bin_file(binary_file_location);
    em6502_reset(&cpu, reset_vector);


    pthread_mutex_init(&mutex_running, NULL);

    if (pthread_create(&thread_process, NULL, handle_process, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread_execution, NULL, handle_execution, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }

    /**
     * Main thread waits for the process_thread to finish and does cleanup.
     * 
    */

    pthread_join(thread_process, NULL);

    if(pthread_cancel(thread_execution)) {
        fprintf(stderr, "Error closing thread\n");
        return EXIT_FAILURE;
    }   

    user_interface_destory();

    return EXIT_SUCCESS;
}