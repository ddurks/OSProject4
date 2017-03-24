#include <pthread.h>
#include <list>

using namespace std;

template <typename T>
class WorkQueue{
    list<T>   m_queue;
    pthread_mutex_t mutex_;
    pthread_cond_t  cond_;

public:
    WorkQueue(){
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&cond_, NULL);
    }
    ~WorkQueue(){
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&cond_);
    }
    void add(T item){
        pthread_mutex_lock(&mutex_);
        m_queue.push_back(item);
        pthread_cond_signal(&cond_);
        pthread_mutex_unlock(&mutex_);
    }
    T remove(){
        pthread_mutex_lock(&mutex_);
        while (m_queue.size() == 0) {
            pthread_cond_wait(&cond_, &mutex_);
        }
        T item = m_queue.front();
        m_queue.pop_front();
        pthread_mutex_unlock(&mutex_);
        return item;
    }
    int size(){
        pthread_mutex_lock(&mutex_);
        int size = m_queue.size();
        pthread_mutex_unlock(&mutex_);
        return size;
    }
};
