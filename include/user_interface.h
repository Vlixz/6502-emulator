#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

#include <pthread.h>

extern int draw_memory_start_address;

extern pthread_mutex_t mutex_user_interface;
extern pthread_cond_t cond_user_interface;

void user_interface_init(void);

void user_interface_destory(void);

void display_input_box(const char *prompt, char *input, int max_length);

#endif /* INC_USER_INTERFACE_H_ */