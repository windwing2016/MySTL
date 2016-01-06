#ifndef DEFALLOC_H
#define DEFALLOC_H

#include <new.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
//#include <iostream.h>
//#include <algobase.h>

//-------------------------------------------
//如果内存分配失败 则直接退出
template<class T>
inline T* allocate(ptrdiff_t size ,T*)
{
    set_new_handler(0);
    T *tmp=(T*)(::operator new((size_t)(size  *(sizeof)(T))));
    if(tmp==0)
    {
      cerr<<"out of memory"<<endl;
      exit(1);
    }
    return tmp;
}

//-------------------------------------
template<class T>
inline void deallocate(T* buffer)
{
    ::operator delete(buffer);
}
//-----------------------------------------------------
//标准stl allocator接口
template <class T>
class allocator
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T&  const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    pointer allocator(size_type n)
    {
        return ::allocate((difference_type)n, (pointer)(0));
    }

    void deallocate(pointer p)
    {
        ::deallocate(p);
    }

    pointer address(reference x)
    {
        return (pointer)&x;
    }

    const_pointer const_address(const_reference x)
    {
        return (const_pointer)&x;
    }

    size_type init_page_size()
    {
        return max(size_type(1),size_type(4096/sizeof(T)));

    }

    size_type max_size()const
    {
       return  max(size_type(1),size_type(UINT_MAX/sizeof(T)));
    }


};

class allocator<void>
{
public:
    typedef void* pointer;
};




#endif // DEFALLOC_H
