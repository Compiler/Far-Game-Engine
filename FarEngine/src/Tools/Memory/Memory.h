#pragma once

namespace far{
    namespace mem{
        #define FAR_NEW(type, arena) new (arena.Allocate(sizeof(type), __FILE__, __LINE__)) type

        #define FAR_DELETE(object, arena) _deleter(object, arena);

        #define FAR_NEW_ARRAY(type, arena) NewArray<TypeProxy<type>::Type>(arena, TypeProxy<type>::Count, __FILE__, __LINE__, IsItPOD<JustData<TypeProxy<type>::Type>::Value>());

        #define FAR_DELETE_ARRAY(object, arena) _del_array(object, arena);


        //determine type at compile time
        template<typename T>
        struct TypeProxy{};

        template<typename T, size_t N>
        struct TypeProxy<T[N]>{ typedef T Type; static const size_t Count = N; };

        //determine type information at compile time
        template <typename T>
        struct JustData
        {
          static const bool Value = std::is_pod<T>::value;
        };

        //type-based dispatch
        template<bool I>
        struct IsItPOD{};

        typedef IsItPOD<false> isNotPOD;
        typedef IsItPOD<true> isPOD;


        //deletes single instance custom allocated memory
        template<typename T, class Arena>
        void _deleter(T* object, Arena& arena)
        {
            //per C++ standards, destructor must be called before memory is freed
            object->~T();
            
            arena.free(object);
        }

        //creates array of non-POD types
        template<typename T, class Arena>
        T* _new_array(Arena& arena, size_t N, const char* file, int line, isNotPOD){
            union{
                void* as_void;
                size_t as_size_t;
                T* as_T;
            };

            as_void = arena.Allocate(sizeof(T)*N + sizeof(size_t), file, line);

            *as_size_t++ = N;

            const T* const eoaPlusOne = as_T + N;
            while(as_T < eoaPlusOne){
                new (as_T++) T;
            }

            return (as_T - N);
        }

        //deletes array of non-POD types
        template<typename T, class Arena>
        void _del_array(T* ptr, Arena& arena, isNotPOD){
            union{
                size_t* as_size_t;
                T* as_T;
            };
            as_T = ptr;
            const size_t N = as_size_t[-1];

            for(size_t i = N; i>0; i--){
                as_T[i-1].~T();
            }
            arena.Free(as_size_t-1);
        }

        template<typename T, class Arena>
        T* _new_array(Arena& arena, size_t N, const char* file, int line, isPOD){
            union{
                void* as_void;
                size_t as_size_t;
                T* as_T;
            };

            as_void = arena.Allocate(sizeof(T)*N + sizeof(size_t), file, line);

            *as_size_t++ = N;

            const T* const eoaPlusOne = as_T + N;
            while(as_T < eoaPlusOne){
                new (as_T++) T;
            }

            return (as_T - N);
        }

        template<typename T, class Arena>
        void _del_array(T* ptr, Arena& arena, isPOD){
            union{
                size_t* as_size_t;
                T* as_T;
            };
            as_T = ptr;
            const size_t N = as_size_t[-1];

            for(size_t i = N; i>0; i--){
                as_T[i-1].~T();
            }
            arena.Free(as_size_t-1);
        }

        template<typename T, class Arena>
        void _del_array(T* ptr, Arena& arena){
            _del_array(ptr, arena, IsItPOD<JustData<T>::Value>());
        }

    }
}