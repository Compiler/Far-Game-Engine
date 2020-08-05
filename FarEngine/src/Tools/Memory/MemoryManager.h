#pragma once
#include <cassert>
#include <cstdlib>
#include <vector>

using namespace std;

#define DEFAULT_ARENA_SIZE 5000000


namespace far{

namespace mem {
  
    typedef char byte_t;

  class MemoryManager {
      protected:
        void* start;
        void* current;
        size_t size;
        size_t space_left;

      public:
        MemoryManager() {
          size = DEFAULT_ARENA_SIZE;
          space_left = size;
          start = static_cast<byte_t*>(malloc(size));
          current = start;
        }

        MemoryManager(const size_t size_) : size(size_) {
          space_left = size;
          start = static_cast<byte_t*>(malloc(size));
          current = start;
        }

        size_t get_size_left() const { return space_left; }

        ~MemoryManager() {
          free(start);
        }

        void* alloc(size_t s) {
          space_left = space_left - s;
          assert(space_left > 0);
          void* to_alloc = current;
          current += s;
          return to_alloc;
        }

        template<typename T>
        T* allocate() {
          size_t s = sizeof(T);
          space_left = space_left - s;
          assert(space_left > 0);
          void* to_alloc = current;
          current += s;
          return static_cast<T*>(to_alloc);
        }

      };

    }
}
