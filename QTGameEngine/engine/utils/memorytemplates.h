#ifndef MEMORYTEMPLATES_H
#define MEMORYTEMPLATES_H

template<typename T> void safe_delete(T* pointer){

    if (pointer != NULL){
        delete pointer;
        pointer = NULL;
    }
}

template<typename T> void safe_delete_list(QList<T*> list){

    foreach (T* item, list) {
        safe_delete(item);
    }
}

template<typename T> void clear_qptr(QPointer<T> ptr){
    if (ptr != NULL)
        ptr.clear();
}

template<typename T> void clear_qptr_list(QList<QPointer<T> > list){
    foreach(QPointer<T> item, list){
        clear_qptr(item);
    }
}

#endif // MEMORYTEMPLATES_H
