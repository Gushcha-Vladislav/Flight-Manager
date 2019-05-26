#include <iostream>

template <class V, class T>
struct VertexAllocator {
    using value_type = T;

    using Traits = std::allocator_traits<VertexAllocator<V,T>>;

#if !defined _MSC_VER
    // libstdc++ использует конструктор по умолчанию:
    // __a == _Alloc()
    VertexAllocator() : m_arena(nullptr) {}

    // libstdc++ требует следующие определения
    using size_type = typename std::allocator<T>::size_type;
    using difference_type = typename std::allocator<T>::difference_type;
    using pointer = typename std::allocator<T>::pointer;
    using const_pointer = typename std::allocator<T>::const_pointer;
    // "reference" не входит Allocator Requirements,
    // но libstdc++ думает что она всегда работает с std::allocator.
    using reference = typename std::allocator<T>::reference;
    using const_reference = typename std::allocator<T>::const_reference;
#endif

    explicit VertexAllocator(V& arena) : m_arena(&arena) {}
    template<class U> VertexAllocator(const VertexAllocator<V,U>& other) : m_arena(other.m_arena) {}

    T* allocate(std::size_t n) { return (T*)m_arena->allocate(n * sizeof(T)); }
    void deallocate(T* p, std::size_t n) { m_arena->deallocate(p, n * sizeof(T)); }

    // требуется в VC++ и libstdc++
    template<class U, class... Args> void construct(U* p, Args&&... args) { std::allocator<T>().construct(p, std::forward<Args>(args)...); }
    template<class U> void destroy(U* p) { std::allocator<T>().destroy(p); }
    template<class U> struct rebind { using other = VertexAllocator<V,U>; };

    V* m_arena;
};

template<class V, class T, class U> bool operator==(const VertexAllocator<V,T>& lhs, const VertexAllocator<V,U>& rhs) { return lhs.m_arena == rhs.m_arena; }
template<class V, class T, class U> bool operator!=(const VertexAllocator<V,T>& lhs, const VertexAllocator<V,U>& rhs) { return !(lhs == rhs); }

#include <vector>

template <class V, class T> using v_vector = std::vector<T, VertexAllocator<V,T>>;


