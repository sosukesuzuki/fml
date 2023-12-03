#ifndef FML_VM_STACK_H
#define FML_VM_STACK_H

typedef struct Thread {
    int pc;
    int sp;
} Thread;

typedef struct VMStack {
    Thread** threads;
    int top;
    int cap;
} VMStack;

void initVMStack(VMStack* stack);
int pushVMStack(VMStack* stack, Thread* thread);
Thread* popVMStack(VMStack* stack);

#endif
