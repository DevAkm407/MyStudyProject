// #include<iostream>
// #include<unistd.h>
// #include<stdio.h>
// #include<pthread.h>
// void* thread_main(void *arg);

// int main()
// {
//     pthread_t t_id;

//     int  thread_param=5;

//     if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param)!=0)
//     {
//         std::cout<<"phread_create() error";
//         return -1;
//     }
//     sleep(10),std::cout<<"end of main";
//     return 0;
// }

// void* thread_main(void *arg)
// {
//     int i;
//     int cnt=*((int*)arg);
//     for ( i = 0; i < cnt; i++)
//     {
//         sleep(1);
//         std::cout<<"running thread"<<std::endl;
//     }
//     return NULL;
// }

// #include<iostream>
// #include<unistd.h>
// #include<stdio.h>
// #include<pthread.h>
// #include<string.h>
// using namespace std;
// void* thread_main(void *arg);

// int main(int argc,char * argv[])
// {
//     pthread_t t_id;
//     int thread_parm=5;
//     void * thr_ret;
//     if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_parm)!=0)
//     {
//         cout<<"pthread_create() error";
//         return -1;
//     }

//     if(pthread_join(t_id,&thr_ret)!=0)
//     {
//         cout<<"phtread_join() error";
//         return -1;
//     }

//     cout<<"Thread return message "<<(char*)thr_ret<<endl;
//     free(thr_ret);
    
//     return 0;
// }   

// void* thread_main(void *arg)
// {
//     int i;
//     int cnt=*((int*)arg);
//     char * msg =new char[50];
//     strcpy(msg,"Hello,I'am thread~ \n");
//     for ( i = 0; i < cnt; i++)
//     {
//         sleep(1);
//         std::cout<<"running thread"<<std::endl;
//     }
//     return (void*)msg;
// }

// #include<iostream>
// #include<unistd.h>
// #include<stdio.h>
// #include<pthread.h>
// using namespace std;
// void* thread_summation(void *arg);
// int sum=0;
// int main()
// {
//     pthread_t id_t1,id_t2;
//     int range1[]={1,5};
//     int range2[]={6,10};

//     pthread_create(&id_t1,NULL,thread_summation,(void*)range1);
//     pthread_create(&id_t2,NULL,thread_summation,(void*)range2);

//     pthread_join(id_t1,NULL);
//     pthread_join(id_t2,NULL);
//     cout<<"result: "<<sum<<"\n";

//     return 0;
// }


// void* thread_summation(void *arg)
// {
//     int start=((int*)arg)[0];
//     int end=((int*)arg)[1];
//     while (start<=end)
//     {
//         sum+=start;
//         start++;
//     }
//     return NULL;
// }

// #include<iostream>
// #include<unistd.h>
// #include<stdio.h>
// #include<pthread.h>
// #define NUM_THREAD 100
// using namespace std;
// void* thread_inc(void *arg);
// void* thread_des(void *arg);
// long long num=0;
// int main()
// {
//     pthread_t thread_id[NUM_THREAD];
//     int i;
//     cout<<"size of long long:"<<sizeof(long long)<<endl;
//     for ( i = 0; i < NUM_THREAD; i++)
//     {
//         if(i%2)
//             pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);
//         else
//             pthread_create(&(thread_id[i]),NULL,thread_des,NULL);

//     }
    
//     for(i=0; i<NUM_THREAD;i++) 
//         pthread_join((thread_id[i]),NULL);
   
//     cout<<"result: "<<num<<"\n";

//     return 0;
// }


// void* thread_inc(void *arg)
// {
//     int i;
//     for ( i = 0; i <50000000 ; i++)
//     {
//         num+=1;
//     }
    
//     return NULL;
// }

// void* thread_des(void *arg)
// {
//     int i;
//     for ( i = 0; i <50000000 ; i++)
//     {
//         num-=1;
//     }
    
//     return NULL;
// }

// #include<iostream>
// #include<unistd.h>
// #include<stdio.h>
// #include<pthread.h>
// #define NUM_THREAD 100
// using namespace std;
// void* thread_inc(void *arg);
// void* thread_des(void *arg);
// long long num=0;
// pthread_mutex_t mutex;
// int main()
// {
//     pthread_t thread_id[NUM_THREAD];
//     int i;
//     pthread_mutex_init(&mutex,NULL);
//     for ( i = 0; i < NUM_THREAD; i++)
//     {
//         if(i%2)
//             pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);
//         else
//             pthread_create(&(thread_id[i]),NULL,thread_des,NULL);

//     }
    
//     for(i=0; i<NUM_THREAD;i++) 
//         pthread_join((thread_id[i]),NULL);
   
//     cout<<"result: "<<num<<"\n";

//     return 0;
// }


// void* thread_inc(void *arg)
// {
//     int i;
//     pthread_mutex_lock(&mutex);
//     for ( i = 0; i <5000000 ; i++)
//     {
//         num+=1;
//     }
//     pthread_mutex_unlock(&mutex);
//     return NULL;
// }

// void* thread_des(void *arg)
// {
//     int i;
//     pthread_mutex_lock(&mutex);
//     for ( i = 0; i <5000000 ; i++)
//     {
//         num-=1;
//     }
//     pthread_mutex_unlock(&mutex);
//     return NULL;
// }

// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <iostream>

// void * read(void * arg);
// void * accu(void * arg);
// static sem_t sem_one;
// static sem_t sem_two;
// static int num;
// using namespace std;
// int main()
// {
//     pthread_t id_t1,id_t2;
//     sem_init(&sem_one,0,0);
//     sem_init(&sem_two,0,1);

//     pthread_create(&id_t1,NULL,read,NULL);
//     pthread_create(&id_t2,NULL,accu,NULL);

//     pthread_join(id_t1,NULL);
//     pthread_join(id_t2,NULL);

//     sem_destroy(&sem_one);
//     sem_destroy(&sem_two);

//     return 0;
// }

// void* read(void* arg)
// {
//     int i;
//     for ( i = 0; i < 5; i++)
//     {
//         cout<<"Input num: \n";
//         sem_wait(&sem_two);
//         std::cin>>num;
//         sem_post(&sem_one);
//     }
//     return NULL;
// }

// void* accu(void* arg)
// {
//     int sum=0,i;
//     for ( i = 0; i < 5; i++)
//     {
//         sem_wait(&sem_one);
//         sum+=num;
//         sem_post(&sem_two);
//     }
//     cout<<"Result: "<<sum<<endl;

//     return NULL;

// }
