// RAII and smart pointers
// In the last section, we have discussed the powerful RAII idiom, which reduces the risk of improperly managed resources. Applied to the concept of memory management, RAII enables us to encapsulate new and delete calls within a class and thus present the programmer with a clean interface to the resource he intends to use. Since C++11, there exists a language feature called smart pointers, which builds on the concept of RAII and - without exaggeration - revolutionizes the way we use resources on the heap. Let’s take a look.

// Smart pointer overview
// Since C++11, the standard library includes smart pointers, which help to ensure that programs are free of memory leaks while also remaining exception-safe. With smart pointers, resource acquisition occurs at the same time that the object is initialized (when instantiated with make_shared or make_unique), so that all resources for the object are created and initialized in a single line of code.

// In modern C++, raw pointers managed with new and delete should only be used in small blocks of code with limited scope, where performance is critical (such as with placement new) and ownership rights of the memory resource are clear. We will look at some guidelines on where to use which pointer later.

// C++11 has introduced three types of smart pointers, which are defined in the header of the standard library:

// 1. The unique pointer std::unique_ptr is a smart pointer which exclusively owns a dynamically allocated resource on the heap. There must not be a second unique pointer to the same resource.

// 2. The shared pointer std::shared_ptr points to a heap resource but does not explicitly own it. There may even be several shared pointers to the same resource, each of which will increase an internal reference count. As soon as this count reaches zero, the resource will automatically be deallocated.

// 3. The weak pointer std::weak_ptr behaves similar to the shared pointer but does not increase the reference counter.

// Prior to C++11, there was a concept called std::auto_ptr, which tried to realize a similar idea. However, this concept can now be safely considered as deprecated and should not be used anymore.

// Let us now look at each of the three smart pointer types in detail.