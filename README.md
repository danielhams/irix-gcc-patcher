Care: gcc9.1 and onwards need patches to:

gcc/config/mips/iris6.h (comment out of NO_IMPLICIT_EXTERN_C)
libgcc/libgcov-driver-system.c - (fix to printf of getpid())
