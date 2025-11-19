#include <iostream>
#include <map>
#include <memory>
#include <cstddef>

template <typename T>
class MapAllocator {
private:
    inline static std::map<void*, size_t> allocations;

public:
    using value_type = T;

    MapAllocator() = default;

    template <class U>
    MapAllocator(const MapAllocator<U>&) noexcept {}
    T* allocate(std::size_t n) {
        void* ptr = ::operator new(n * sizeof(T));
        allocations[ptr] = n * sizeof(T);
        std::cout << "[ALLOC] " << n * sizeof(T) << " bytes at " << ptr << std::endl;
        return static_cast<T*>(ptr);
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "[FREE ] " << n * sizeof(T) << " bytes at " << p << std::endl;
        allocations.erase(p);
        ::operator delete(p);
    }

    static void print_allocations() {
        std::cout << "\n--- Active allocations ---\n";
        for (auto& [ptr, size] : allocations)
            std::cout << ptr << " -> " << size << " bytes\n";
        std::cout << "---------------------------\n";
    }
};

template <class T, class U>
bool operator==(const MapAllocator<T>&, const MapAllocator<U>&) { return true; }

template <class T, class U>
bool operator!=(const MapAllocator<T>&, const MapAllocator<U>&) { return false; }

template <class T, class Alloc = std::allocator<T>>
class Stack {
private:
    struct Element {
        T data;
        Element* n;
        Element(const T& d, Element* next = nullptr) : data(d), n(next) {}
    };

    using ElementAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Element>;
    ElementAlloc alloc;
    Element* data;
    size_t size;

public:
    class Iterator {
    private:
        Element* data;
    public:
        Iterator(Element* e) : data(e) {}
        T& operator*() const { return data->data; }
        T* operator->() const { return &(data->data); }
        Iterator& operator++() { if (data) data = data->n; return *this; }
        bool operator!=(const Iterator& other) const { return data != other.data; }
    };

    Stack() : data(nullptr), size(0) {}
    ~Stack() { clear(); }

    bool is_void() const { return data == nullptr; }

    void push(const T& d) {
        Element* e = std::allocator_traits<ElementAlloc>::allocate(alloc, 1);
        std::allocator_traits<ElementAlloc>::construct(alloc, e, d, data);
        data = e;
        ++size;
    }

    void delfirst() {
        if (is_void()) return;
        Element* p = data;
        data = data->n;
        std::allocator_traits<ElementAlloc>::destroy(alloc, p);
        std::allocator_traits<ElementAlloc>::deallocate(alloc, p, 1);
        --size;
    }

    void clear() {
        while (!is_void()) delfirst();
    }

    T& top() {
        return data->data;
    }

    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(nullptr); }
};
