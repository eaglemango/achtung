#include <csetjmp>
#include <iostream>

enum AchtungType {
    IO = 0,
    FS = 10,
    DOES_NOT_EXIST,
    FD_LIMIT,
    MEMORY = 20
};

struct RecursionStackItem {
    jmp_buf env;
    int val;

    RecursionStackItem* next_item;
};

struct RecursionStack {
    RecursionStackItem* root = nullptr;
};

RecursionStack global_recursion_stack;

#define TRY(code_block) \
    RecursionStackItem* new_item = new RecursionStackItem(); \
    \
    new_item->val = setjmp(new_item->env); \
    if (new_item->val == 0) { \
        new_item->next_item = global_recursion_stack.root; \
        global_recursion_stack.root = new_item; \
        \
        /* Исполняем переданный блок кода */ \
        code_block \
    } \

#define CATCH(achtung, code_block) \
    else if (new_item->val == achtung) { \
        /* Исполняем переданный блок кода */ \
        code_block \
    } \

#define FAIL_IF_UNCAUGHT \
    else { \
        std::cout << "Failed with achtung " << new_item->val << std::endl; \
        abort(); \
    } \

#define THROW(achtung) \
    RecursionStackItem* top_item = global_recursion_stack.root; \
    \
    if (top_item == nullptr) { \
        std::cout << "Uncaught achtung " << achtung << std::endl; \
    } else { \
        global_recursion_stack.root = top_item->next_item; \
        longjmp(top_item->env, achtung); \
    } \
