#ifndef LIST_H
#define LIST_H

template <typename T>
class List{
public:
    List();
    int getSize() const;
    virtual T get(const int) const = 0;
    virtual void set(const int, const T) = 0;
    virtual void insert(const int, const T) = 0;
    virtual void remove(const int) = 0;
protected:
    unsigned int mSize;
};

template<typename T>
List<T>::List(){
    mSize = 0;
}

template<typename T>
int List<T>::getSize() const{
    return mSize;
}

#endif