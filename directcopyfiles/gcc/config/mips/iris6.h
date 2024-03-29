/* Definitions of target machine for GNU compiler.  IRIX 6.5 version.
   Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 2000,
   2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* We are compiling for IRIX 6 now.  */
#undef TARGET_IRIX6
#define TARGET_IRIX6 1

/* we use GNU binutils here */
#define IRIX_USING_GNU_LD 1

/* Default to -mabi=n32 and -mips3.  */
#undef MULTILIB_DEFAULTS
#define MULTILIB_DEFAULTS { "mabi=n32" }

/* -march=native handling only makes sense with compiler running on
   a MIPS chip.  */
#if defined(__mips__)
extern const char *host_detect_local_cpu (int argc, const char **argv);
# define EXTRA_SPEC_FUNCTIONS \
  { "local_cpu_detect", host_detect_local_cpu },

# define MARCH_MTUNE_NATIVE_SPECS				\
  " %{march=native:%<march=native %:local_cpu_detect(arch)}"	\
  " %{mtune=native:%<mtune=native %:local_cpu_detect(tune)}"
#else
# define MARCH_MTUNE_NATIVE_SPECS ""
#endif

#define PREFERRRED_DEBUGGING_TYPE DWARF2_DEBUG

/* Force the default ABI onto the command line in order to make the specs
   easier to write.  */
#undef DRIVER_SELF_SPECS
#define DRIVER_SELF_SPECS 			\
  "%{!mabi=*: -mabi=n32}", 			\
  /* Configuration-independent MIPS rules.  */	\
  BASE_DRIVER_SELF_SPECS,			\
  MARCH_MTUNE_NATIVE_SPECS

/* IRIX 6.5 has the float and long double forms of math functions.  */
/* #define TARGET_C99_FUNCTIONS 1 */

/* MIPS specific debugging info */
/* #define MIPS_DEBUGGING_INFO 1 */
#define SGUG_DEBUGGING_INFO 1

/* Force the generation of dwarf .debug_frame sections even if not
   compiling -g.  This guarantees that we can unwind the stack.  */
#define DWARF2_FRAME_INFO 1

/* The system unwinder in libexc requires a specific dwarf return address
   column to work.  */
#undef  DWARF_FRAME_RETURN_COLUMN
#define DWARF_FRAME_RETURN_COLUMN (FP_REG_LAST + 1)

/* The size in bytes of a DWARF field indicating an offset or length
   relative to a debug info section, specified to be 4 bytes in the DWARF-2
   specification.  The SGI/MIPS ABI defines it to be the same as PTR_SIZE.  */
#define DWARF_OFFSET_SIZE PTR_SIZE

/* The size in bytes of the initial length field in a debug info
   section.  The DWARF 3 (draft) specification defines this to be
   either 4 or 12 (with a 4-byte "escape" word when it's 12), but the
   SGI/MIPS ABI predates this standard and defines it to be the same
   as DWARF_OFFSET_SIZE.  */
#define DWARF_INITIAL_LENGTH_SIZE DWARF_OFFSET_SIZE

/* MIPS assemblers don't have the usual .set foo,bar construct;
   .set is used for assembler options instead.  */
#undef SET_ASM_OP
#define ASM_OUTPUT_DEF(FILE, LABEL1, LABEL2)			\
  do								\
    {								\
      fputc ('\t', FILE);					\
      assemble_name (FILE, LABEL1);				\
      fputs (" = ", FILE);					\
      assemble_name (FILE, LABEL2);				\
      fputc ('\n', FILE);					\
    }								\
  while (0)

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."

#undef ASM_DECLARE_OBJECT_NAME
#define ASM_DECLARE_OBJECT_NAME mips_declare_object_name

#undef ASM_FINISH_DECLARE_OBJECT
#define ASM_FINISH_DECLARE_OBJECT mips_finish_declare_object

/* The native IRIX 6 linker does not support merging without a special
   elspec(5) file.  */
#ifndef IRIX_USING_GNU_LD
#undef HAVE_GAS_SHF_MERGE
#define HAVE_GAS_SHF_MERGE 0
#endif

/* Specify wchar_t types.  */
#undef WCHAR_TYPE
#define WCHAR_TYPE (Pmode == DImode ? "int" : "long int")

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE INT_TYPE_SIZE

/* Same for wint_t.  */
#undef WINT_TYPE
#define WINT_TYPE (Pmode == DImode ? "int" : "long int")

#undef WINT_TYPE_SIZE
#define WINT_TYPE_SIZE INT_TYPE_SIZE

#ifndef USED_FOR_TARGET
/* Use long for intmax_t, uintmax_t?  */
extern int long_intmax;
#endif

/* C99 stdint.h types.  */
#define INT8_TYPE "signed char"
#define INT16_TYPE "short int"
#define INT32_TYPE "int"
#define INT64_TYPE "long long int"
#define UINT8_TYPE "unsigned char"
#define UINT16_TYPE "short unsigned int"
#define UINT32_TYPE "unsigned int"
#define UINT64_TYPE "long long unsigned int"

#define INT_LEAST8_TYPE "signed char"
#define INT_LEAST16_TYPE "short int"
#define INT_LEAST32_TYPE "int"
#define INT_LEAST64_TYPE "long long int"
#define UINT_LEAST8_TYPE "unsigned char"
#define UINT_LEAST16_TYPE "short unsigned int"
#define UINT_LEAST32_TYPE "unsigned int"
#define UINT_LEAST64_TYPE "long long unsigned int"

#define INT_FAST8_TYPE "signed char"
#define INT_FAST16_TYPE "short int"
#define INT_FAST32_TYPE "int"
#define INT_FAST64_TYPE "long long int"
#define UINT_FAST8_TYPE "unsigned char"
#define UINT_FAST16_TYPE "short unsigned int"
#define UINT_FAST32_TYPE "unsigned int"
#define UINT_FAST64_TYPE "long long unsigned int"

#define INTMAX_TYPE (long_intmax ? "long int" : "long long int")
#define UINTMAX_TYPE (long_intmax ? "long unsigned int" : "long long unsigned int")

#define INTPTR_TYPE "long int"
#define UINTPTR_TYPE "long unsigned int"

#define SIG_ATOMIC_TYPE "int"

/* Plain char is unsigned in the SGI compiler.  */
#undef DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR 0

#define TARGET_OS_CPP_BUILTINS()				\
  do								\
    {								\
      builtin_define_std ("host_mips");				\
      builtin_define_std ("sgi");				\
      builtin_define_std ("unix");				\
      builtin_define_std ("SYSTYPE_SVR4");			\
      builtin_define ("_MODERN_C");				\
      builtin_define ("_SVR4_SOURCE");				\
      builtin_define ("__DSO__");				\
      builtin_assert ("system=unix");				\
      builtin_assert ("system=svr4");				\
      builtin_assert ("machine=sgi");				\
								\
      if (!ISA_MIPS1 && !ISA_MIPS2)				\
	builtin_define ("_COMPILER_VERSION=601");		\
								\
      /* We must always define _LONGLONG, even when -ansi is	\
	 used, because IRIX 5 system header files require it.	\
	 This is OK, because gcc never warns when long long	\
	 is used in system header files.			\
								\
	 An alternative would be to support the SGI builtin	\
	 type __long_long.  */					\
      builtin_define ("_LONGLONG");				\
								\
      /* IRIX 6.5.18 and above provide many ISO C99		\
	 features protected by the __c99 macro.			\
	 libstdc++ v3 needs them as well.  */			\
      if (flag_isoc99 || c_dialect_cxx ())			\
	builtin_define ("__c99");				\
								\
      /* The GNU C++ standard library requires that		\
	 __EXTENSIONS__ and _SGI_SOURCE be defined on at	\
	 least IRIX 6.2 and probably all IRIX 6 prior to 6.5.	\
	 We don't need this on IRIX 6.5 itself, but it		\
	 shouldn't hurt other than the namespace pollution.  */	\
      if (!flag_iso || c_dialect_cxx ())			\
	{							\
	  builtin_define ("__EXTENSIONS__");			\
	  builtin_define ("_SGI_SOURCE");			\
	}							\
    }								\
  while (0)

/* SUBTARGET_OVERRIDE_OPTIONS is run after C_COMMON_OVERRIDE_OPTIONS, so
   only set long_intmax if uninitialized.  */
#undef SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS 		\
  do						\
    {						\
      if (long_intmax == -1)			\
	long_intmax = mips_abi == ABI_64;	\
    }						\
  while (0)

/*
      if (!global_options_set.x_dwarf_strict)	\
	dwarf_strict = 1;			\
      if (!global_options_set.x_dwarf_version)	\
	dwarf_version = 2;			\
*/

extern void irix6_c_common_override_options (void);
#define C_COMMON_OVERRIDE_OPTIONS irix6_c_common_override_options()

#undef SUBTARGET_CC1_SPEC
#define SUBTARGET_CC1_SPEC "%{static: -mno-abicalls}"

#undef SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC "%{pthread:-D_REENTRANT}"

#undef INIT_SECTION_ASM_OP
#define INIT_SECTION_ASM_OP "\t.section\t.gcc_init,\"ax\",@progbits"

#undef FINI_SECTION_ASM_OP
#define FINI_SECTION_ASM_OP "\t.section\t.gcc_fini,\"ax\",@progbits"

#ifdef IRIX_USING_GNU_LD
#define IRIX_NO_UNRESOLVED ""
#else
#define IRIX_NO_UNRESOLVED "-no_unresolved"
#endif

#ifdef IRIX_USING_GNU_LD
#define SUBTARGET_DONT_WARN_UNUSED_SPEC ""
#define SUBTARGET_WARN_UNUSED_SPEC ""
#else
#define SUBTARGET_DONT_WARN_UNUSED_SPEC "-dont_warn_unused"
#define SUBTARGET_WARN_UNUSED_SPEC "-warn_unused"
#endif

/* Profiling is supported via libprof1.a not -lc_p as in IRIX 3.  */
#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
  "%{!shared: \
     %{mabi=n32: \
       %{mips4:%{pg:/usr/lib32/mips4/gcrt1.o%s} \
         %{!pg:%{p:/usr/lib32/mips4/mcrt1.o%s /usr/lib32/mips4/libprof1.a%s} \
           %{!p:/usr/lib32/mips4/crt1.o%s}}} \
       %{!mips4:%{pg:/usr/lib32/mips3/gcrt1.o%s} \
         %{!pg:%{p:/usr/lib32/mips3/mcrt1.o%s /usr/lib32/mips3/libprof1.a%s} \
           %{!p:/usr/lib32/mips3/crt1.o%s}}}} \
     %{mabi=64: \
       %{mips4:%{pg:/usr/lib64/mips4/gcrt1.o} \
         %{!pg:%{p:/usr/lib64/mips4/mcrt1.o /usr/lib64/mips4/libprof1.a} \
           %{!p:/usr/lib64/mips4/crt1.o}}} \
       %{!mips4:%{pg:/usr/lib64/mips3/gcrt1.o} \
         %{!pg:%{p:/usr/lib64/mips3/mcrt1.o /usr/lib64/mips3/libprof1.a} \
           %{!p:/usr/lib64/mips3/crt1.o}}}}} \
  irix-crti.o%s crtbegin.o%s"

#undef LIB_SPEC
#define LIB_SPEC \
  "%{mabi=n32: %{mips4:-L/usr/lib32/mips4} %{!mips4:-L/usr/lib32/mips3} \
     -L/usr/lib32} \
   %{mabi=64: %{mips4:-L/usr/lib64/mips4} %{!mips4:-L/usr/lib64/mips3} \
     -L/usr/lib64} \
   %{!shared:" \
     SUBTARGET_DONT_WARN_UNUSED_SPEC \
     " %{pthread:-lpthread} %{p:libprof1.a%s}%{pg:libprof1.a%s} -lc " \
     SUBTARGET_WARN_UNUSED_SPEC "}"

/* Avoid getting two warnings for libgcc.a everytime we link.  libgcc.a
   contains references to copysignl, so link with libm to resolve them.  */
#undef LIBGCC_SPEC
#define LIBGCC_SPEC \
  SUBTARGET_DONT_WARN_UNUSED_SPEC " -lgcc -lm " SUBTARGET_WARN_UNUSED_SPEC

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
  "%{Ofast|ffast-math|funsafe-math-optimizations:crtfastmath.o%s} \
   crtend.o%s irix-crtn.o%s \
   %{!shared: \
     %{mabi=n32:%{mips4:/usr/lib32/mips4/crtn.o%s}\
       %{!mips4:/usr/lib32/mips3/crtn.o%s}}\
     %{mabi=64:%{mips4:/usr/lib64/mips4/crtn.o%s}\
       %{!mips4:/usr/lib64/mips3/crtn.o%s}}}"

/* Generic part of the LINK_SPEC.  */
#undef LINK_SPEC
#define LINK_SPEC "\
%{G*} %{EB} %{EL} %{mips1} %{mips2} %{mips3} %{mips4} \
%{bestGnum} %{shared} %{non_shared} \
%{call_shared} %{no_archive} %{exact_version} \
%{!shared: \
  %{!non_shared: %{!call_shared:%{!r: -call_shared " IRIX_NO_UNRESOLVED "}}}} \
%{rpath} %{!r: -init __gcc_init -fini __gcc_fini} " IRIX_SUBTARGET_LINK_SPEC

#ifdef IRIX_USING_GNU_LD
#define IRIX_SUBTARGET_LINK_SPEC \
  "%{mabi=n32: -melf32bmipn32}%{mabi=64: -melf64bmip}"
#else
  /* Explicitly hide crt symbols that would normally be marked with
     a "hidden" visibility attribute.
     
     We have traditionally disabled this attribute when using the
     native linker because the native linker's visibility support is
     not fully-compatible with the GNU linker's.  In particular, the
     native linker does not pull in archive objects purely to resolve
     references to the object's hidden symbols, whereas the GNU
     linker does.
     
     The gcc build system currently hides symbols in some static
     libraries (typically libgcov.a or libgcc.a) whenever visibility
     attributes are supported.  On targets with GNU semantics, this
     makes sure that uses of libx.so symbols in one dynamic object are
     not resolved to libx.a symbols in another dynamic object.  But
     on targets with IRIX semantics, hiding the symbols prevents the
     static archive from working at all.
     
     It would probably be better to enable visiblity attributes for
     IRIX ld and disable the static archives versioning.  It shouldn't
     make anything worse, since libx.a symbols are global by default
     anyway.  However, no-one has volunteered to do this yet.  */

#define IRIX_SUBTARGET_LINK_SPEC \
  "%{w} -_SYSTYPE_SVR4 -woff 131 \
   %{shared:-hidden_symbol __dso_handle} \
   %{mabi=n32: -n32}%{mabi=64: -64}%{!mabi*: -n32}"
#endif

/* A linker error can empirically be avoided by removing duplicate
   library search directories.  */
/* #define LINK_ELIMINATE_DUPLICATE_LDIRECTORIES 1 */

/* The SGI linker doesn't understand constructor priorities.  */
#ifndef IRIX_USING_GNU_LD
#define SUPPORTS_INIT_PRIORITY 0
#endif

/* Add -g to mips.h default to avoid confusing gas with local symbols
   generated from stabs info.  */
#undef NM_FLAGS
#define NM_FLAGS "-Bng"

/* The system header files are C++ aware.  */
/* ??? Unfortunately, most but not all of the headers are C++ aware.
   Specifically, curses.h is not, and as a consequence, defining this
   used to prevent libg++ building.  This is no longer the case so
   define it again to prevent other problems, e.g. with getopt in
   unistd.h.  We still need some way to fix just those files that need
   fixing.  */
#define NO_IMPLICIT_EXTERN_C 1

/* -G is incompatible with -KPIC which is the default, so only allow objects
   in the small data section if the user explicitly asks for it.  */
#undef MIPS_DEFAULT_GVALUE
#define MIPS_DEFAULT_GVALUE 0

#define MIPS_TFMODE_FORMAT mips_extended_format
