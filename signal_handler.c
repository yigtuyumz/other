#define _POSIX_C_SOURCE 199309L // for siginfo_t

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <ucontext.h>
#include <stdlib.h>
#include <string.h>

// gregset `General Register Set`
// gregset_t is ucontext_t->uc_mcontext.__gregs
void
display_gregset(gregset_t regset)
{
#ifdef __x86_64__
    static char *reg_names[__NGREG] = {
        "R8", "R9", "R10", "R11", "R12",
        "R13", "R14", "R15", "RDI", "RSI",
        "RBP", "RBX", "RDX", "RAX", "RCX",
        "RSP", "RIP", "EFL", "CSGSFS", "ERR",
        "TRAPNO", "OLDMASK", "CR2"
    };

    unsigned char iter = 0;

    while (iter < __NGREG) {
        printf("%-8s: ", reg_names[iter]);
        if (regset[iter]) {
            printf("%#018lx  %20lu", (unsigned long) regset[iter],
                   (unsigned long) regset[iter]);
        } else {
            printf("%18s  %20s", "NULL", "-");
        }
        printf("\n");
        iter++;
    }
#else
# error "Unsupported arch."
#endif /* __x86_64__ */
}

void
sigint_handler(ucontext_t *context)
{
    if (context) {
        display_gregset(context->uc_mcontext.__gregs);
    }
    printf("\rSIGINT captured, exit(1)\n");
    exit(1);
}

void
sigsegv_handler(ucontext_t *context)
{
    if (context) {
        display_gregset(context->uc_mcontext.__gregs);
    }
    printf("\rSIGSEGV captured, exit(1)\n");
    exit(1);
}

void
signal_handler(int signum, siginfo_t *siginfo, void *context)
{
    if (!siginfo) {
        // siginfo should not be NULL.
        (void) fprintf(stderr,
                       "signal_handler's siginfo is NULL, it should not be.\n");
        exit(1);
    }
    printf("\rsignal number: %d\n", siginfo->si_signo);
    // siginfo_t.si_errno:
    // the errno value if a system call has failed during the event that triggers the signal.
    if (siginfo->si_errno) {
        (void) fprintf(stderr,
                       "An error occured while running the systemcall which generates this signal. Error code: %d Error message: %s",
                       siginfo->si_errno, strerror(siginfo->si_errno));
        exit(1);
    }
    // Optional, get the program context from userspace.
    // Requires <ucontext.h>
    ucontext_t *uc = (ucontext_t *) context;

    // any singal that requires an action, is dispatched here.
    if (signum == SIGINT) {
        sigint_handler(uc);
    } else if (signum == SIGSEGV) {
        sigsegv_handler(uc);
    }
}

void
signal_action(void)
{
    struct sigaction sigact;

    sigact.sa_sigaction = signal_handler;

    // Clear all signals from SET. This function always returns '0'
    sigemptyset(&sigact.sa_mask);

    // Invoke signal-catching function with three arguments instead of one.
    sigact.sa_flags = SA_SIGINFO;

    // Activating a signal, sigaction returns '0' on success.
    if (sigaction(SIGINT, &sigact, NULL) == -1) {
        // sigaction fails.
    } else {
        // sigaction success.
    }

    if (sigaction(SIGSEGV, &sigact, NULL) == -1) {
        // sigaction fails.
    } else {
        // sigaction success.
    }
}

int
main(int argc, char *argv[])
{
    char *c = "";               // for segfaulting

    signal_action();
    int counter = 0;

    while (++counter) {
        sleep(1);
        printf("Slept 1sec..\n");
        if (counter == 3) {
            c[0] = '0';         // segfault for a purpose.
        }
    }

    return (0);
}
