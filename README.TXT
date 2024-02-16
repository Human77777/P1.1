Project Overview:
This project involves the implementation of custom versions of the malloc() and free() functions, named mymalloc() and myfree(), respectively. These functions aim to simulate the behavior of the standard memory management functions in C, with added functionality for error detection and reporting. The goal is to enhance understanding of dynamic memory management, error handling, and the challenges involved in implementing such critical system functions.

Member:
Name:         NetID:
Mingen Liu    ML1594

Design Description:
Our design for mymalloc.c and mymalloc.h focuses on efficiency, minimal fragmentation, and robust error detection. We use a single large array to simulate the heap memory. Each allocated block includes a header storing the block size and allocation status. This approach enables us to efficiently traverse the memory, allocate, and deallocate memory blocks. Our allocation strategy is a simple first-fit method, chosen for its straightforward implementation and reasonable performance for our test cases.

Test Plan:
We developed a comprehensive test plan to verify the correctness and robustness of our memory management system, including tests for:
- Basic functionality: allocating and freeing memory blocks of various sizes.
- Error detection: attempting to free unallocated blocks, double freeing, and out-of-bound memory access.
- Edge cases: allocating the maximum possible block size and requesting memory when none is available.
- Fragmentation: sequences of allocations and deallocations designed to fragment memory and test coalescing.
- Stress tests: rapid sequences of random allocations and deallocations to simulate heavy usage.

Test Program Descriptions:
- memgrind.c: This program executes a series of tests (described in the Test Plan section) to evaluate the performance and correctness of our custom malloc and free implementations. It reports average execution time for each test, helping to identify potential inefficiencies.

Design Notes:
Implementing a custom memory allocator presented several challenges, particularly in handling edge cases and minimizing fragmentation. We addressed these by carefully managing block headers and implementing coalescing of adjacent free blocks upon deallocation. A limitation of our current design is the lack of support for realloc() and calloc(), which could be added in future iterations.

Build Instructions:
To compile and run the test program, use the following commands:
1. Compile: gcc -o memgrind memgrind.c mymalloc.c
2. Run: ./memgrind

Additional Notes:
Our implementation focuses on the educational aspects of memory management systems. As such, it may not be as efficient or robust as production-level allocators. We welcome feedback and suggestions for improvement.

