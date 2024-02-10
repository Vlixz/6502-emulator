#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

#include <pthread.h>

extern pthread_mutex_t mutex_user_interface;
extern pthread_cond_t cond_user_interface;

void user_interface_init(void);

void user_interface_destory(void);

#endif /* INC_USER_INTERFACE_H_ */