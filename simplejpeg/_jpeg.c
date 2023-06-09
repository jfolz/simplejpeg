 

 

#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#endif  
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03030000)
    #error Cython requires Python 2.6+ or Python 3.3+.
#else
#define CYTHON_ABI "0_29_35"
#define CYTHON_HEX_VERSION 0x001D23F0
#define CYTHON_FUTURE_DIVISION 1
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#define __PYX_COMMA ,
#ifndef HAVE_LONG_LONG
  #if PY_VERSION_HEX >= 0x02070000
    #define HAVE_LONG_LONG
  #endif
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 0
  #undef CYTHON_USE_TYPE_SLOTS
  #define CYTHON_USE_TYPE_SLOTS 0
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #if PY_VERSION_HEX < 0x03050000
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #undef CYTHON_USE_UNICODE_INTERNALS
  #define CYTHON_USE_UNICODE_INTERNALS 0
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #undef CYTHON_AVOID_BORROWED_REFS
  #define CYTHON_AVOID_BORROWED_REFS 1
  #undef CYTHON_ASSUME_SAFE_MACROS
  #define CYTHON_ASSUME_SAFE_MACROS 0
  #undef CYTHON_UNPACK_METHODS
  #define CYTHON_UNPACK_METHODS 0
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #if PY_VERSION_HEX < 0x03090000
    #undef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #elif !defined(CYTHON_PEP489_MULTI_PHASE_INIT)
    #define CYTHON_PEP489_MULTI_PHASE_INIT 1
  #endif
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE 0
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 0
  #endif
#elif defined(PYSTON_VERSION)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #undef CYTHON_PEP489_MULTI_PHASE_INIT
  #define CYTHON_PEP489_MULTI_PHASE_INIT 0
  #undef CYTHON_USE_TP_FINALIZE
  #define CYTHON_USE_TP_FINALIZE 0
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 0
  #endif
#elif defined(PY_NOGIL)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #define CYTHON_COMPILING_IN_NOGIL 1
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_PYTYPE_LOOKUP
  #define CYTHON_USE_PYTYPE_LOOKUP 0
  #ifndef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
  #ifndef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT 1
  #endif
  #ifndef CYTHON_USE_TP_FINALIZE
    #define CYTHON_USE_TP_FINALIZE 1
  #endif
  #undef CYTHON_USE_DICT_VERSIONS
  #define CYTHON_USE_DICT_VERSIONS 0
  #undef CYTHON_USE_EXC_INFO_STACK
  #define CYTHON_USE_EXC_INFO_STACK 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
  #define CYTHON_COMPILING_IN_NOGIL 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYTYPE_LOOKUP
    #define CYTHON_USE_PYTYPE_LOOKUP 0
  #elif !defined(CYTHON_USE_PYTYPE_LOOKUP)
    #define CYTHON_USE_PYTYPE_LOOKUP 1
  #endif
  #if PY_MAJOR_VERSION < 3
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYLONG_INTERNALS
    #define CYTHON_USE_PYLONG_INTERNALS 0
  #elif !defined(CYTHON_USE_PYLONG_INTERNALS)
    #define CYTHON_USE_PYLONG_INTERNALS (PY_VERSION_HEX < 0x030C00A5)
  #endif
  #ifndef CYTHON_USE_PYLIST_INTERNALS
    #define CYTHON_USE_PYLIST_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #if PY_VERSION_HEX < 0x030300F0 || PY_VERSION_HEX >= 0x030B00A2
    #undef CYTHON_USE_UNICODE_WRITER
    #define CYTHON_USE_UNICODE_WRITER 0
  #elif !defined(CYTHON_USE_UNICODE_WRITER)
    #define CYTHON_USE_UNICODE_WRITER 1
  #endif
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #if PY_VERSION_HEX >= 0x030B00A4
    #undef CYTHON_FAST_THREAD_STATE
    #define CYTHON_FAST_THREAD_STATE 0
  #elif !defined(CYTHON_FAST_THREAD_STATE)
    #define CYTHON_FAST_THREAD_STATE 1
  #endif
  #ifndef CYTHON_FAST_PYCALL
    #define CYTHON_FAST_PYCALL (PY_VERSION_HEX < 0x030A0000)
  #endif
  #ifndef CYTHON_PEP489_MULTI_PHASE_INIT
    #define CYTHON_PEP489_MULTI_PHASE_INIT (PY_VERSION_HEX >= 0x03050000)
  #endif
  #ifndef CYTHON_USE_TP_FINALIZE
    #define CYTHON_USE_TP_FINALIZE (PY_VERSION_HEX >= 0x030400a1)
  #endif
  #ifndef CYTHON_USE_DICT_VERSIONS
    #define CYTHON_USE_DICT_VERSIONS ((PY_VERSION_HEX >= 0x030600B1) && (PY_VERSION_HEX < 0x030C00A5))
  #endif
  #if PY_VERSION_HEX >= 0x030B00A4
    #undef CYTHON_USE_EXC_INFO_STACK
    #define CYTHON_USE_EXC_INFO_STACK 0
  #elif !defined(CYTHON_USE_EXC_INFO_STACK)
    #define CYTHON_USE_EXC_INFO_STACK (PY_VERSION_HEX >= 0x030700A3)
  #endif
  #ifndef CYTHON_UPDATE_DESCRIPTOR_DOC
    #define CYTHON_UPDATE_DESCRIPTOR_DOC 1
  #endif
#endif
#if !defined(CYTHON_FAST_PYCCALL)
#define CYTHON_FAST_PYCCALL  (CYTHON_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #if PY_MAJOR_VERSION < 3
    #include "longintrepr.h"
  #endif
  #undef SHIFT
  #undef BASE
  #undef MASK
  #ifdef SIZEOF_VOID_P
    enum { __pyx_check_sizeof_voidp = 1 / (int)(SIZEOF_VOID_P == sizeof(void*)) };
  #endif
#endif
#ifndef __has_attribute
  #define __has_attribute(x) 0
#endif
#ifndef __has_cpp_attribute
  #define __has_cpp_attribute(x) 0
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_MAYBE_UNUSED_VAR
#  if defined(__cplusplus)
     template<class T> void CYTHON_MAYBE_UNUSED_VAR( const T& ) { }
#  else
#    define CYTHON_MAYBE_UNUSED_VAR(x) (void)(x)
#  endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)
#ifdef _MSC_VER
    #ifndef _MSC_STDINT_H_
        #if _MSC_VER < 1300
           typedef unsigned char     uint8_t;
           typedef unsigned int      uint32_t;
        #else
           typedef unsigned __int8   uint8_t;
           typedef unsigned __int32  uint32_t;
        #endif
    #endif
#else
   #include <stdint.h>
#endif
#ifndef CYTHON_FALLTHROUGH
  #if defined(__cplusplus) && __cplusplus >= 201103L
    #if __has_cpp_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH [[fallthrough]]
    #elif __has_cpp_attribute(clang::fallthrough)
      #define CYTHON_FALLTHROUGH [[clang::fallthrough]]
    #elif __has_cpp_attribute(gnu::fallthrough)
      #define CYTHON_FALLTHROUGH [[gnu::fallthrough]]
    #endif
  #endif
  #ifndef CYTHON_FALLTHROUGH
    #if __has_attribute(fallthrough)
      #define CYTHON_FALLTHROUGH __attribute__((fallthrough))
    #else
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
  #if defined(__clang__ ) && defined(__apple_build_version__)
    #if __apple_build_version__ < 7000000
      #undef  CYTHON_FALLTHROUGH
      #define CYTHON_FALLTHROUGH
    #endif
  #endif
#endif

#ifndef CYTHON_INLINE
  #if defined(__clang__)
    #define CYTHON_INLINE __inline__ __attribute__ ((__unused__))
  #elif defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif

#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
  #define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_DefaultClassType PyType_Type
#if PY_VERSION_HEX >= 0x030B00A1
    static CYTHON_INLINE PyCodeObject* __Pyx_PyCode_New(int a, int k, int l, int s, int f,
                                                    PyObject *code, PyObject *c, PyObject* n, PyObject *v,
                                                    PyObject *fv, PyObject *cell, PyObject* fn,
                                                    PyObject *name, int fline, PyObject *lnos) {
        PyObject *kwds=NULL, *argcount=NULL, *posonlyargcount=NULL, *kwonlyargcount=NULL;
        PyObject *nlocals=NULL, *stacksize=NULL, *flags=NULL, *replace=NULL, *call_result=NULL, *empty=NULL;
        const char *fn_cstr=NULL;
        const char *name_cstr=NULL;
        PyCodeObject* co=NULL;
        PyObject *type, *value, *traceback;
        PyErr_Fetch(&type, &value, &traceback);
        if (!(kwds=PyDict_New())) goto end;
        if (!(argcount=PyLong_FromLong(a))) goto end;
        if (PyDict_SetItemString(kwds, "co_argcount", argcount) != 0) goto end;
        if (!(posonlyargcount=PyLong_FromLong(0))) goto end;
        if (PyDict_SetItemString(kwds, "co_posonlyargcount", posonlyargcount) != 0) goto end;
        if (!(kwonlyargcount=PyLong_FromLong(k))) goto end;
        if (PyDict_SetItemString(kwds, "co_kwonlyargcount", kwonlyargcount) != 0) goto end;
        if (!(nlocals=PyLong_FromLong(l))) goto end;
        if (PyDict_SetItemString(kwds, "co_nlocals", nlocals) != 0) goto end;
        if (!(stacksize=PyLong_FromLong(s))) goto end;
        if (PyDict_SetItemString(kwds, "co_stacksize", stacksize) != 0) goto end;
        if (!(flags=PyLong_FromLong(f))) goto end;
        if (PyDict_SetItemString(kwds, "co_flags", flags) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_code", code) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_consts", c) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_names", n) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_varnames", v) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_freevars", fv) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_cellvars", cell) != 0) goto end;
        if (PyDict_SetItemString(kwds, "co_linetable", lnos) != 0) goto end;
        if (!(fn_cstr=PyUnicode_AsUTF8AndSize(fn, NULL))) goto end;
        if (!(name_cstr=PyUnicode_AsUTF8AndSize(name, NULL))) goto end;
        if (!(co = PyCode_NewEmpty(fn_cstr, name_cstr, fline))) goto end;
        if (!(replace = PyObject_GetAttrString((PyObject*)co, "replace"))) goto cleanup_code_too;
        if (!(empty = PyTuple_New(0))) goto cleanup_code_too;  
        if (!(call_result = PyObject_Call(replace, empty, kwds))) goto cleanup_code_too;
        Py_XDECREF((PyObject*)co);
        co = (PyCodeObject*)call_result;
        call_result = NULL;
        if (0) {
            cleanup_code_too:
            Py_XDECREF((PyObject*)co);
            co = NULL;
        }
        end:
        Py_XDECREF(kwds);
        Py_XDECREF(argcount);
        Py_XDECREF(posonlyargcount);
        Py_XDECREF(kwonlyargcount);
        Py_XDECREF(nlocals);
        Py_XDECREF(stacksize);
        Py_XDECREF(replace);
        Py_XDECREF(call_result);
        Py_XDECREF(empty);
        if (type) {
            PyErr_Restore(type, value, traceback);
        }
        return co;
    }
#else
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#endif
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#ifndef METH_STACKLESS
  #define METH_STACKLESS 0
#endif
#if PY_VERSION_HEX <= 0x030700A3 || !defined(METH_FASTCALL)
  #ifndef METH_FASTCALL
     #define METH_FASTCALL 0x80
  #endif
  typedef PyObject *(*__Pyx_PyCFunctionFast) (PyObject *self, PyObject *const *args, Py_ssize_t nargs);
  typedef PyObject *(*__Pyx_PyCFunctionFastWithKeywords) (PyObject *self, PyObject *const *args,
                                                          Py_ssize_t nargs, PyObject *kwnames);
#else
  #define __Pyx_PyCFunctionFast _PyCFunctionFast
  #define __Pyx_PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords
#endif
#if CYTHON_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func)\
    ((PyCFunction_Check(func) && (METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS | METH_STACKLESS)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030400A1
  #define PyMem_RawMalloc(n)           PyMem_Malloc(n)
  #define PyMem_RawRealloc(p, n)       PyMem_Realloc(p, n)
  #define PyMem_RawFree(p)             PyMem_Free(p)
#endif
#if CYTHON_COMPILING_IN_PYSTON
  #define __Pyx_PyCode_HasFreeVars(co)  PyCode_HasFreeVars(co)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno) PyFrame_SetLineNumber(frame, lineno)
#else
  #define __Pyx_PyCode_HasFreeVars(co)  (PyCode_GetNumFree(co) > 0)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno)  (frame)->f_lineno = (lineno)
#endif
#if !CYTHON_FAST_THREAD_STATE || PY_VERSION_HEX < 0x02070000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#elif PY_VERSION_HEX >= 0x03060000
  #define __Pyx_PyThreadState_Current _PyThreadState_UncheckedGet()
#elif PY_VERSION_HEX >= 0x03000000
  #define __Pyx_PyThreadState_Current PyThreadState_GET()
#else
  #define __Pyx_PyThreadState_Current _PyThreadState_Current
#endif
#if PY_VERSION_HEX < 0x030700A2 && !defined(PyThread_tss_create) && !defined(Py_tss_NEEDS_INIT)
#include "pythread.h"
#define Py_tss_NEEDS_INIT 0
typedef int Py_tss_t;
static CYTHON_INLINE int PyThread_tss_create(Py_tss_t *key) {
  *key = PyThread_create_key();
  return 0;
}
static CYTHON_INLINE Py_tss_t * PyThread_tss_alloc(void) {
  Py_tss_t *key = (Py_tss_t *)PyObject_Malloc(sizeof(Py_tss_t));
  *key = Py_tss_NEEDS_INIT;
  return key;
}
static CYTHON_INLINE void PyThread_tss_free(Py_tss_t *key) {
  PyObject_Free(key);
}
static CYTHON_INLINE int PyThread_tss_is_created(Py_tss_t *key) {
  return *key != Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE void PyThread_tss_delete(Py_tss_t *key) {
  PyThread_delete_key(*key);
  *key = Py_tss_NEEDS_INIT;
}
static CYTHON_INLINE int PyThread_tss_set(Py_tss_t *key, void *value) {
  return PyThread_set_key_value(*key, value);
}
static CYTHON_INLINE void * PyThread_tss_get(Py_tss_t *key) {
  return PyThread_get_key_value(*key);
}
#endif
#if CYTHON_COMPILING_IN_CPYTHON || defined(_PyDict_NewPresized)
#define __Pyx_PyDict_NewPresized(n)  ((n <= 8) ? PyDict_New() : _PyDict_NewPresized(n))
#else
#define __Pyx_PyDict_NewPresized(n)  PyDict_New()
#endif
#if PY_MAJOR_VERSION >= 3 || CYTHON_FUTURE_DIVISION
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1 && CYTHON_USE_UNICODE_INTERNALS
#define __Pyx_PyDict_GetItemStr(dict, name)  _PyDict_GetItem_KnownHash(dict, name, ((PyASCIIObject *) name)->hash)
#else
#define __Pyx_PyDict_GetItemStr(dict, name)  PyDict_GetItem(dict, name)
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #if PY_VERSION_HEX >= 0x030C0000
    #define __Pyx_PyUnicode_READY(op)       (0)
  #else
    #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                                0 : _PyUnicode_Ready((PyObject *)(op)))
  #endif
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   PyUnicode_MAX_CHAR_VALUE(u)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  PyUnicode_WRITE(k, d, i, ch)
  #if PY_VERSION_HEX >= 0x030C0000
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_LENGTH(u))
  #else
    #if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x03090000
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : ((PyCompactUnicodeObject *)(u))->wstr_length))
    #else
    #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
    #endif
  #endif
#else
  #define CYTHON_PEP393_ENABLED 0
  #define PyUnicode_1BYTE_KIND  1
  #define PyUnicode_2BYTE_KIND  2
  #define PyUnicode_4BYTE_KIND  4
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  (((void)(k)), ((Py_UNICODE*)d)[i] = ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None || (PyString_Check(b) && !PyString_CheckExact(b)))) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None || (PyUnicode_Check(b) && !PyUnicode_CheckExact(b)))) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#ifndef PyObject_Unicode
  #define PyObject_Unicode             PyObject_Str
#endif
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#if PY_VERSION_HEX >= 0x030900A4
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_SET_REFCNT(obj, refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SET_SIZE(obj, size)
#else
  #define __Pyx_SET_REFCNT(obj, refcnt) Py_REFCNT(obj) = (refcnt)
  #define __Pyx_SET_SIZE(obj, size) Py_SIZE(obj) = (size)
#endif
#if CYTHON_ASSUME_SAFE_MACROS
  #define __Pyx_PySequence_SIZE(seq)  Py_SIZE(seq)
#else
  #define __Pyx_PySequence_SIZE(seq)  PySequence_Size(seq)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   __Pyx_PyIndex_AsHash_t
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   __Pyx_PyIndex_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? ((void)(klass), PyMethod_New(func, self)) : __Pyx_NewRef(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if CYTHON_USE_ASYNC_SLOTS
  #if PY_VERSION_HEX >= 0x030500B1
    #define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
    #define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
  #else
    #define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
  #endif
#else
  #define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef __Pyx_PyAsyncMethodsStruct
    typedef struct {
        unaryfunc am_await;
        unaryfunc am_aiter;
        unaryfunc am_anext;
    } __Pyx_PyAsyncMethodsStruct;
#endif

#if defined(_WIN32) || defined(WIN32) || defined(MS_WINDOWS)
  #if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES
  #endif
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif

#define __PYX_MARK_ERR_POS(f_index, lineno) \
    { __pyx_filename = __pyx_f[f_index]; (void)__pyx_filename; __pyx_lineno = lineno; (void)__pyx_lineno; __pyx_clineno = __LINE__; (void)__pyx_clineno; }
#define __PYX_ERR(f_index, lineno, Ln_error) \
    { __PYX_MARK_ERR_POS(f_index, lineno) goto Ln_error; }

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__simplejpeg___jpeg
#define __PYX_HAVE_API__simplejpeg___jpeg
 
#include <string.h>
#include <stdio.h>
#include "numpy/arrayobject.h"
#include "numpy/ndarrayobject.h"
#include "numpy/ndarraytypes.h"
#include "numpy/arrayscalars.h"
#include "numpy/ufuncobject.h"

     
    
#include "pythread.h"
#include "turbojpeg.h"
#include "_color.h"
#include <stdlib.h>
#include "pystate.h"
#ifdef _OPENMP
#include <omp.h>
#endif  

#if defined(PYREX_WITHOUT_ASSERTIONS) && !defined(CYTHON_WITHOUT_ASSERTIONS)
#define CYTHON_WITHOUT_ASSERTIONS
#endif

typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_UTF8 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT (PY_MAJOR_VERSION >= 3 && __PYX_DEFAULT_STRING_ENCODING_IS_UTF8)
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
static CYTHON_INLINE int __Pyx_is_valid_index(Py_ssize_t i, Py_ssize_t limit) {
    return (size_t) i < (size_t) limit;
}
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER)
    #define __Pyx_sst_abs(value) ((Py_ssize_t)_abs64(value))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE const char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE const char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyBytes_AsWritableString(s)     ((char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableSString(s)    ((signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsWritableUString(s)    ((unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsString(s)     ((const char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsSString(s)    ((const signed char*) PyBytes_AS_STRING(s))
#define __Pyx_PyBytes_AsUString(s)    ((const unsigned char*) PyBytes_AS_STRING(s))
#define __Pyx_PyObject_AsWritableString(s)    ((char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsSString(s)    ((const signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((const unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u) {
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
static CYTHON_INLINE PyObject * __Pyx_PyBool_FromLong(long b);
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE int __Pyx_PyObject_IsTrueAndDecref(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
#define __Pyx_PySequence_Tuple(obj)\
    (likely(PyTuple_CheckExact(obj)) ? __Pyx_NewRef(obj) : PySequence_Tuple(obj))
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
static CYTHON_INLINE Py_hash_t __Pyx_PyIndex_AsHash_t(PyObject*);
#if CYTHON_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c) + 1);
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


 
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else  
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif  
static CYTHON_INLINE void __Pyx_pretend_to_initialize(void* ptr) { (void)ptr; }

static PyObject *__pyx_m = NULL;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_cython_runtime = NULL;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;

 
#if !defined(CYTHON_CCOMPLEX)
  #if defined(__cplusplus)
    #define CYTHON_CCOMPLEX 1
  #elif defined(_Complex_I)
    #define CYTHON_CCOMPLEX 1
  #else
    #define CYTHON_CCOMPLEX 0
  #endif
#endif
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #include <complex>
  #else
    #include <complex.h>
  #endif
#endif
#if CYTHON_CCOMPLEX && !defined(__cplusplus) && defined(__sun__) && defined(__GNUC__)
  #undef _Complex_I
  #define _Complex_I 1.0fj
#endif


static const char *__pyx_f[] = {
  "simplejpeg/_jpeg.pyx",
  "__init__.pxd",
  "stringsource",
  "type.pxd",
  "bool.pxd",
  "complex.pxd",
};
 
#define __Pyx_PyGILState_Ensure PyGILState_Ensure
#define __Pyx_PyGILState_Release PyGILState_Release
#define __Pyx_FastGIL_Remember()
#define __Pyx_FastGIL_Forget()
#define __Pyx_FastGilFuncInit()

 
#ifndef __PYX_FORCE_INIT_THREADS
  #define __PYX_FORCE_INIT_THREADS 0
#endif

 
struct __pyx_memoryview_obj;
typedef struct {
  struct __pyx_memoryview_obj *memview;
  char *data;
  Py_ssize_t shape[8];
  Py_ssize_t strides[8];
  Py_ssize_t suboffsets[8];
} __Pyx_memviewslice;
#define __Pyx_MemoryView_Len(m)  (m.shape[0])

 
#include <pythread.h>
#ifndef CYTHON_ATOMICS
    #define CYTHON_ATOMICS 1
#endif
#define __PYX_CYTHON_ATOMICS_ENABLED() CYTHON_ATOMICS
#define __pyx_atomic_int_type int
#if CYTHON_ATOMICS && (__GNUC__ >= 5 || (__GNUC__ == 4 &&\
                    (__GNUC_MINOR__ > 1 ||\
                    (__GNUC_MINOR__ == 1 && __GNUC_PATCHLEVEL__ >= 2))))
    #define __pyx_atomic_incr_aligned(value) __sync_fetch_and_add(value, 1)
    #define __pyx_atomic_decr_aligned(value) __sync_fetch_and_sub(value, 1)
    #ifdef __PYX_DEBUG_ATOMICS
        #warning "Using GNU atomics"
    #endif
#elif CYTHON_ATOMICS && defined(_MSC_VER) && CYTHON_COMPILING_IN_NOGIL
    #include <intrin.h>
    #undef __pyx_atomic_int_type
    #define __pyx_atomic_int_type long
    #pragma intrinsic (_InterlockedExchangeAdd)
    #define __pyx_atomic_incr_aligned(value) _InterlockedExchangeAdd(value, 1)
    #define __pyx_atomic_decr_aligned(value) _InterlockedExchangeAdd(value, -1)
    #ifdef __PYX_DEBUG_ATOMICS
        #pragma message ("Using MSVC atomics")
    #endif
#else
    #undef CYTHON_ATOMICS
    #define CYTHON_ATOMICS 0
    #ifdef __PYX_DEBUG_ATOMICS
        #warning "Not using atomics"
    #endif
#endif
typedef volatile __pyx_atomic_int_type __pyx_atomic_int;
#if CYTHON_ATOMICS
    #define __pyx_add_acquisition_count(memview)\
             __pyx_atomic_incr_aligned(__pyx_get_slice_count_pointer(memview))
    #define __pyx_sub_acquisition_count(memview)\
            __pyx_atomic_decr_aligned(__pyx_get_slice_count_pointer(memview))
#else
    #define __pyx_add_acquisition_count(memview)\
            __pyx_add_acquisition_count_locked(__pyx_get_slice_count_pointer(memview), memview->lock)
    #define __pyx_sub_acquisition_count(memview)\
            __pyx_sub_acquisition_count_locked(__pyx_get_slice_count_pointer(memview), memview->lock)
#endif

 
#define IS_UNSIGNED(type) (((type) -1) > 0)
struct __Pyx_StructField_;
#define __PYX_BUF_FLAGS_PACKED_STRUCT (1 << 0)
typedef struct {
  const char* name;
  struct __Pyx_StructField_* fields;
  size_t size;
  size_t arraysize[8];
  int ndim;
  char typegroup;
  char is_unsigned;
  int flags;
} __Pyx_TypeInfo;
typedef struct __Pyx_StructField_ {
  __Pyx_TypeInfo* type;
  const char* name;
  size_t offset;
} __Pyx_StructField;
typedef struct {
  __Pyx_StructField* field;
  size_t parent_offset;
} __Pyx_BufFmt_StackElem;
typedef struct {
  __Pyx_StructField root;
  __Pyx_BufFmt_StackElem* head;
  size_t fmt_offset;
  size_t new_count, enc_count;
  size_t struct_alignment;
  int is_complex;
  char enc_type;
  char new_packmode;
  char enc_packmode;
  char is_valid_array;
} __Pyx_BufFmt_Context;


 
typedef npy_int8 __pyx_t_5numpy_int8_t;

 
typedef npy_int16 __pyx_t_5numpy_int16_t;

 
typedef npy_int32 __pyx_t_5numpy_int32_t;

 
typedef npy_int64 __pyx_t_5numpy_int64_t;

 
typedef npy_uint8 __pyx_t_5numpy_uint8_t;

 
typedef npy_uint16 __pyx_t_5numpy_uint16_t;

 
typedef npy_uint32 __pyx_t_5numpy_uint32_t;

 
typedef npy_uint64 __pyx_t_5numpy_uint64_t;

 
typedef npy_float32 __pyx_t_5numpy_float32_t;

 
typedef npy_float64 __pyx_t_5numpy_float64_t;

 
typedef npy_long __pyx_t_5numpy_int_t;

 
typedef npy_longlong __pyx_t_5numpy_long_t;

 
typedef npy_longlong __pyx_t_5numpy_longlong_t;

 
typedef npy_ulong __pyx_t_5numpy_uint_t;

 
typedef npy_ulonglong __pyx_t_5numpy_ulong_t;

 
typedef npy_ulonglong __pyx_t_5numpy_ulonglong_t;

 
typedef npy_intp __pyx_t_5numpy_intp_t;

 
typedef npy_uintp __pyx_t_5numpy_uintp_t;

 
typedef npy_double __pyx_t_5numpy_float_t;

 
typedef npy_double __pyx_t_5numpy_double_t;

 
typedef npy_longdouble __pyx_t_5numpy_longdouble_t;
 
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< float > __pyx_t_float_complex;
  #else
    typedef float _Complex __pyx_t_float_complex;
  #endif
#else
    typedef struct { float real, imag; } __pyx_t_float_complex;
#endif
static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float, float);

 
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< double > __pyx_t_double_complex;
  #else
    typedef double _Complex __pyx_t_double_complex;
  #endif
#else
    typedef struct { double real, imag; } __pyx_t_double_complex;
#endif
static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double, double);


 
struct __pyx_array_obj;
struct __pyx_MemviewEnum_obj;
struct __pyx_memoryview_obj;
struct __pyx_memoryviewslice_obj;

 
typedef npy_cfloat __pyx_t_5numpy_cfloat_t;

 
typedef npy_cdouble __pyx_t_5numpy_cdouble_t;

 
typedef npy_clongdouble __pyx_t_5numpy_clongdouble_t;

 
typedef npy_cdouble __pyx_t_5numpy_complex_t;

 
struct __pyx_array_obj {
  PyObject_HEAD
  struct __pyx_vtabstruct_array *__pyx_vtab;
  char *data;
  Py_ssize_t len;
  char *format;
  int ndim;
  Py_ssize_t *_shape;
  Py_ssize_t *_strides;
  Py_ssize_t itemsize;
  PyObject *mode;
  PyObject *_format;
  void (*callback_free_data)(void *);
  int free_data;
  int dtype_is_object;
};


 
struct __pyx_MemviewEnum_obj {
  PyObject_HEAD
  PyObject *name;
};


 
struct __pyx_memoryview_obj {
  PyObject_HEAD
  struct __pyx_vtabstruct_memoryview *__pyx_vtab;
  PyObject *obj;
  PyObject *_size;
  PyObject *_array_interface;
  PyThread_type_lock lock;
  __pyx_atomic_int acquisition_count[2];
  __pyx_atomic_int *acquisition_count_aligned_p;
  Py_buffer view;
  int flags;
  int dtype_is_object;
  __Pyx_TypeInfo *typeinfo;
};


 
struct __pyx_memoryviewslice_obj {
  struct __pyx_memoryview_obj __pyx_base;
  __Pyx_memviewslice from_slice;
  PyObject *from_object;
  PyObject *(*to_object_func)(char *);
  int (*to_dtype_func)(char *, PyObject *);
};



 

struct __pyx_vtabstruct_array {
  PyObject *(*get_memview)(struct __pyx_array_obj *);
};
static struct __pyx_vtabstruct_array *__pyx_vtabptr_array;


 

struct __pyx_vtabstruct_memoryview {
  char *(*get_item_pointer)(struct __pyx_memoryview_obj *, PyObject *);
  PyObject *(*is_slice)(struct __pyx_memoryview_obj *, PyObject *);
  PyObject *(*setitem_slice_assignment)(struct __pyx_memoryview_obj *, PyObject *, PyObject *);
  PyObject *(*setitem_slice_assign_scalar)(struct __pyx_memoryview_obj *, struct __pyx_memoryview_obj *, PyObject *);
  PyObject *(*setitem_indexed)(struct __pyx_memoryview_obj *, PyObject *, PyObject *);
  PyObject *(*convert_item_to_object)(struct __pyx_memoryview_obj *, char *);
  PyObject *(*assign_item_from_object)(struct __pyx_memoryview_obj *, char *, PyObject *);
};
static struct __pyx_vtabstruct_memoryview *__pyx_vtabptr_memoryview;


 

struct __pyx_vtabstruct__memoryviewslice {
  struct __pyx_vtabstruct_memoryview __pyx_base;
};
static struct __pyx_vtabstruct__memoryviewslice *__pyx_vtabptr__memoryviewslice;

 
 
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

 
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

 
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

 
#include <string.h>

 
static CYTHON_INLINE PyObject *__Pyx_PyUnicode_DecodeUTF16(const char *s, Py_ssize_t size, const char *errors) {
    int byteorder = 0;
    return PyUnicode_DecodeUTF16(s, size, errors, &byteorder);
}
static CYTHON_INLINE PyObject *__Pyx_PyUnicode_DecodeUTF16LE(const char *s, Py_ssize_t size, const char *errors) {
    int byteorder = -1;
    return PyUnicode_DecodeUTF16(s, size, errors, &byteorder);
}
static CYTHON_INLINE PyObject *__Pyx_PyUnicode_DecodeUTF16BE(const char *s, Py_ssize_t size, const char *errors) {
    int byteorder = 1;
    return PyUnicode_DecodeUTF16(s, size, errors, &byteorder);
}

 
static CYTHON_INLINE PyObject* __Pyx_decode_c_string(
         const char* cstring, Py_ssize_t start, Py_ssize_t stop,
         const char* encoding, const char* errors,
         PyObject* (*decode_func)(const char *s, Py_ssize_t size, const char *errors));

 
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

 
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

 
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = __Pyx_PyThreadState_Current;
#define __Pyx_PyErr_Occurred()  __pyx_tstate->curexc_type
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#define __Pyx_PyErr_Occurred()  PyErr_Occurred()
#endif

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_Clear() __Pyx_ErrRestore(NULL, NULL, NULL)
#define __Pyx_ErrRestoreWithState(type, value, tb)  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)    __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)    __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyErr_SetNone(exc) (Py_INCREF(exc), __Pyx_ErrRestore((exc), NULL, NULL))
#else
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#endif
#else
#define __Pyx_PyErr_Clear() PyErr_Clear()
#define __Pyx_PyErr_SetNone(exc) PyErr_SetNone(exc)
#define __Pyx_ErrRestoreWithState(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestoreInState(tstate, type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchInState(tstate, type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)  PyErr_Fetch(type, value, tb)
#endif

 
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause);

 
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func, PyObject **args, Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs)  (assert(0), NULL)
#endif

 
#if CYTHON_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs)\
    __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, Py_ssize_t nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#define __Pyx_BUILD_ASSERT_EXPR(cond)\
    (sizeof(char [1 - 2*!(cond)]) - 1)
#ifndef Py_MEMBER_SIZE
#define Py_MEMBER_SIZE(type, member) sizeof(((type *)0)->member)
#endif
#if CYTHON_FAST_PYCALL
  static size_t __pyx_pyframe_localsplus_offset = 0;
  #include "frameobject.h"
#if PY_VERSION_HEX >= 0x030b00a6
  #ifndef Py_BUILD_CORE
    #define Py_BUILD_CORE 1
  #endif
  #include "internal/pycore_frame.h"
#endif
  #define __Pxy_PyFrame_Initialize_Offsets()\
    ((void)__Pyx_BUILD_ASSERT_EXPR(sizeof(PyFrameObject) == offsetof(PyFrameObject, f_localsplus) + Py_MEMBER_SIZE(PyFrameObject, f_localsplus)),\
     (void)(__pyx_pyframe_localsplus_offset = ((size_t)PyFrame_Type.tp_basicsize) - Py_MEMBER_SIZE(PyFrameObject, f_localsplus)))
  #define __Pyx_PyFrame_GetLocalsplus(frame)\
    (assert(__pyx_pyframe_localsplus_offset), (PyObject **)(((char *)(frame)) + __pyx_pyframe_localsplus_offset))
#endif  
#endif

 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

 
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

 
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

 
#define __Pyx_BUF_MAX_NDIMS %(BUF_MAX_NDIMS)d
#define __Pyx_MEMVIEW_DIRECT   1
#define __Pyx_MEMVIEW_PTR      2
#define __Pyx_MEMVIEW_FULL     4
#define __Pyx_MEMVIEW_CONTIG   8
#define __Pyx_MEMVIEW_STRIDED  16
#define __Pyx_MEMVIEW_FOLLOW   32
#define __Pyx_IS_C_CONTIG 1
#define __Pyx_IS_F_CONTIG 2
static int __Pyx_init_memviewslice(
                struct __pyx_memoryview_obj *memview,
                int ndim,
                __Pyx_memviewslice *memviewslice,
                int memview_is_new_reference);
static CYTHON_INLINE int __pyx_add_acquisition_count_locked(
    __pyx_atomic_int *acquisition_count, PyThread_type_lock lock);
static CYTHON_INLINE int __pyx_sub_acquisition_count_locked(
    __pyx_atomic_int *acquisition_count, PyThread_type_lock lock);
#define __pyx_get_slice_count_pointer(memview) (memview->acquisition_count_aligned_p)
#define __pyx_get_slice_count(memview) (*__pyx_get_slice_count_pointer(memview))
#define __PYX_INC_MEMVIEW(slice, have_gil) __Pyx_INC_MEMVIEW(slice, have_gil, __LINE__)
#define __PYX_XDEC_MEMVIEW(slice, have_gil) __Pyx_XDEC_MEMVIEW(slice, have_gil, __LINE__)
static CYTHON_INLINE void __Pyx_INC_MEMVIEW(__Pyx_memviewslice *, int, int);
static CYTHON_INLINE void __Pyx_XDEC_MEMVIEW(__Pyx_memviewslice *, int, int);

 
#define __Pyx_ArgTypeTest(obj, type, none_allowed, name, exact)\
    ((likely((Py_TYPE(obj) == type) | (none_allowed && (obj == Py_None)))) ? 1 :\
        __Pyx__ArgTypeTest(obj, type, name, exact))
static int __Pyx__ArgTypeTest(PyObject *obj, PyTypeObject *type, const char *name, int exact);

 
#if PY_MAJOR_VERSION >= 3 && !CYTHON_COMPILING_IN_PYPY
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key);
#define __Pyx_PyObject_Dict_GetItem(obj, name)\
    (likely(PyDict_CheckExact(obj)) ?\
     __Pyx_PyDict_GetItem(obj, name) : PyObject_GetItem(obj, name))
#else
#define __Pyx_PyDict_GetItem(d, key) PyObject_GetItem(d, key)
#define __Pyx_PyObject_Dict_GetItem(obj, name)  PyObject_GetItem(obj, name)
#endif

 
static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type);

 
static CYTHON_INLINE int __Pyx_Is_Little_Endian(void);

 
static const char* __Pyx_BufFmt_CheckString(__Pyx_BufFmt_Context* ctx, const char* ts);
static void __Pyx_BufFmt_Init(__Pyx_BufFmt_Context* ctx,
                              __Pyx_BufFmt_StackElem* stack,
                              __Pyx_TypeInfo* type);

 
#define __Pyx_GetBufferAndValidate(buf, obj, dtype, flags, nd, cast, stack)\
    ((obj == Py_None || obj == NULL) ?\
    (__Pyx_ZeroBuffer(buf), 0) :\
    __Pyx__GetBufferAndValidate(buf, obj, dtype, flags, nd, cast, stack))
static int  __Pyx__GetBufferAndValidate(Py_buffer* buf, PyObject* obj,
    __Pyx_TypeInfo* dtype, int flags, int nd, int cast, __Pyx_BufFmt_StackElem* stack);
static void __Pyx_ZeroBuffer(Py_buffer* buf);
static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info);
static Py_ssize_t __Pyx_minusones[] = { -1, -1, -1, -1, -1, -1, -1, -1 };
static Py_ssize_t __Pyx_zeros[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

 
static void __Pyx_RaiseBufferFallbackError(void);

#define __Pyx_BufPtrStrided3d(type, buf, i0, s0, i1, s1, i2, s2) (type)((char*)buf + i0 * s0 + i1 * s1 + i2 * s2)
 
static CYTHON_INLINE PyObject* __Pyx_PyObject_FormatSimpleAndDecref(PyObject* s, PyObject* f);
static CYTHON_INLINE PyObject* __Pyx_PyObject_FormatAndDecref(PyObject* s, PyObject* f);

 
#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define __Pyx_HAS_GCC_DIAGNOSTIC
#endif

 
static PyObject* __Pyx_PyUnicode_BuildFromAscii(Py_ssize_t ulength, char* chars, int clength,
                                                int prepend_sign, char padding_char);

 
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_From_int(int value, Py_ssize_t width, char padding_char, char format_char);

 
static PyObject* __Pyx_PyUnicode_Join(PyObject* value_tuple, Py_ssize_t value_count, Py_ssize_t result_ulength,
                                      Py_UCS4 max_char);

 
#if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_TYPE_SLOTS
#define __PYX_DICT_VERSION_INIT  ((PY_UINT64_T) -1)
#define __PYX_GET_DICT_VERSION(dict)  (((PyDictObject*)(dict))->ma_version_tag)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)\
    (version_var) = __PYX_GET_DICT_VERSION(dict);\
    (cache_var) = (value);
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP) {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    if (likely(__PYX_GET_DICT_VERSION(DICT) == __pyx_dict_version)) {\
        (VAR) = __pyx_dict_cached_value;\
    } else {\
        (VAR) = __pyx_dict_cached_value = (LOOKUP);\
        __pyx_dict_version = __PYX_GET_DICT_VERSION(DICT);\
    }\
}
static CYTHON_INLINE PY_UINT64_T __Pyx_get_tp_dict_version(PyObject *obj);
static CYTHON_INLINE PY_UINT64_T __Pyx_get_object_dict_version(PyObject *obj);
static CYTHON_INLINE int __Pyx_object_dict_version_matches(PyObject* obj, PY_UINT64_T tp_dict_version, PY_UINT64_T obj_dict_version);
#else
#define __PYX_GET_DICT_VERSION(dict)  (0)
#define __PYX_UPDATE_DICT_CACHE(dict, value, cache_var, version_var)
#define __PYX_PY_DICT_LOOKUP_IF_MODIFIED(VAR, DICT, LOOKUP)  (VAR) = (LOOKUP);
#endif

 
#if CYTHON_USE_DICT_VERSIONS
#define __Pyx_GetModuleGlobalName(var, name)  do {\
    static PY_UINT64_T __pyx_dict_version = 0;\
    static PyObject *__pyx_dict_cached_value = NULL;\
    (var) = (likely(__pyx_dict_version == __PYX_GET_DICT_VERSION(__pyx_d))) ?\
        (likely(__pyx_dict_cached_value) ? __Pyx_NewRef(__pyx_dict_cached_value) : __Pyx_GetBuiltinName(name)) :\
        __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
} while(0)
#define __Pyx_GetModuleGlobalNameUncached(var, name)  do {\
    PY_UINT64_T __pyx_dict_version;\
    PyObject *__pyx_dict_cached_value;\
    (var) = __Pyx__GetModuleGlobalName(name, &__pyx_dict_version, &__pyx_dict_cached_value);\
} while(0)
static PyObject *__Pyx__GetModuleGlobalName(PyObject *name, PY_UINT64_T *dict_version, PyObject **dict_cached_value);
#else
#define __Pyx_GetModuleGlobalName(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
#define __Pyx_GetModuleGlobalNameUncached(var, name)  (var) = __Pyx__GetModuleGlobalName(name)
static CYTHON_INLINE PyObject *__Pyx__GetModuleGlobalName(PyObject *name);
#endif

 
static CYTHON_UNUSED PyObject* __Pyx_PyObject_Call2Args(PyObject* function, PyObject* arg1, PyObject* arg2);

 
static int __pyx_memviewslice_is_contig(const __Pyx_memviewslice mvs, char order, int ndim);

 
#define __pyx_memviewslice_is_contig_C3(slice)\
    __pyx_memviewslice_is_contig(slice, 'C', 3)

 
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_Unicode(PyObject *obj);

 
#if CYTHON_USE_EXC_INFO_STACK
static _PyErr_StackItem * __Pyx_PyErr_GetTopmostException(PyThreadState *tstate);
#endif

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_ExceptionMatches(err) __Pyx_PyErr_ExceptionMatchesInState(__pyx_tstate, err)
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err);
#else
#define __Pyx_PyErr_ExceptionMatches(err)  PyErr_ExceptionMatches(err)
#endif

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

 
static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals);

 
static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals);

 
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Equals __Pyx_PyUnicode_Equals
#else
#define __Pyx_PyString_Equals __Pyx_PyBytes_Equals
#endif

 
static CYTHON_INLINE Py_ssize_t __Pyx_div_Py_ssize_t(Py_ssize_t, Py_ssize_t);

 
#define UNARY_NEG_WOULD_OVERFLOW(x)\
        (((x) < 0) & ((unsigned long)(x) == 0-(unsigned long)(x)))

static CYTHON_UNUSED int __pyx_array_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
static PyObject *__pyx_array_get_memview(struct __pyx_array_obj *);  
 
static CYTHON_INLINE PyObject *__Pyx_GetAttr(PyObject *, PyObject *);

 
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject *__Pyx_PyObject_GetItem(PyObject *obj, PyObject* key);
#else
#define __Pyx_PyObject_GetItem(obj, key)  PyObject_GetItem(obj, key)
#endif

 
static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *, PyObject *, PyObject *);

 
static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

 
static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

 
static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void);

 
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSwap(type, value, tb)  __Pyx__ExceptionSwap(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSwap(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static CYTHON_INLINE void __Pyx_ExceptionSwap(PyObject **type, PyObject **value, PyObject **tb);
#endif

 
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

 
#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_TypeCheck(obj, type) __Pyx_IsSubtype(Py_TYPE(obj), (PyTypeObject *)type)
static CYTHON_INLINE int __Pyx_IsSubtype(PyTypeObject *a, PyTypeObject *b);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches(PyObject *err, PyObject *type);
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches2(PyObject *err, PyObject *type1, PyObject *type2);
#else
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyErr_GivenExceptionMatches(err, type) PyErr_GivenExceptionMatches(err, type)
#define __Pyx_PyErr_GivenExceptionMatches2(err, type1, type2) (PyErr_GivenExceptionMatches(err, type1) || PyErr_GivenExceptionMatches(err, type2))
#endif
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)

static CYTHON_UNUSED int __pyx_memoryview_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
 
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_ListComp_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len)) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        __Pyx_SET_SIZE(list, len + 1);
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L,x) PyList_Append(L,x)
#endif

 
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace, int zerodivision_check);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace, zerodivision_check)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

 
static CYTHON_INLINE int __Pyx_PyList_Extend(PyObject* L, PyObject* v) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject* none = _PyList_Extend((PyListObject*)L, v);
    if (unlikely(!none))
        return -1;
    Py_DECREF(none);
    return 0;
#else
    return PyList_SetSlice(L, PY_SSIZE_T_MAX, PY_SSIZE_T_MAX, v);
#endif
}

 
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        __Pyx_SET_SIZE(list, len + 1);
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

 
static CYTHON_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname);

 
static CYTHON_INLINE long __Pyx_div_long(long, long);

 
static CYTHON_INLINE int __Pyx_PySequence_ContainsTF(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

 
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

 
static CYTHON_INLINE int __Pyx_HasAttr(PyObject *, PyObject *);

 
#if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static CYTHON_INLINE PyObject* __Pyx_PyObject_GenericGetAttrNoDict(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GenericGetAttrNoDict PyObject_GenericGetAttr
#endif

 
#if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject* __Pyx_PyObject_GenericGetAttr(PyObject* obj, PyObject* attr_name);
#else
#define __Pyx_PyObject_GenericGetAttr PyObject_GenericGetAttr
#endif

 
static int __Pyx_SetVtable(PyObject *dict, void *vtable);

 
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStrNoError(PyObject* obj, PyObject* attr_name);

 
static int __Pyx_setup_reduce(PyObject* type_obj);

 
#ifndef __PYX_HAVE_RT_ImportType_proto_0_29_35
#define __PYX_HAVE_RT_ImportType_proto_0_29_35
#if __STDC_VERSION__ >= 201112L
#include <stdalign.h>
#endif
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#define __PYX_GET_STRUCT_ALIGNMENT_0_29_35(s) alignof(s)
#else
#define __PYX_GET_STRUCT_ALIGNMENT_0_29_35(s) sizeof(void*)
#endif
enum __Pyx_ImportType_CheckSize_0_29_35 {
   __Pyx_ImportType_CheckSize_Error_0_29_35 = 0,
   __Pyx_ImportType_CheckSize_Warn_0_29_35 = 1,
   __Pyx_ImportType_CheckSize_Ignore_0_29_35 = 2
};
static PyTypeObject *__Pyx_ImportType_0_29_35(PyObject* module, const char *module_name, const char *class_name, size_t size, size_t alignment, enum __Pyx_ImportType_CheckSize_0_29_35 check_size);
#endif

 
static CYTHON_INLINE int __Pyx_IterFinish(void);

 
static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected);

 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

 
static int __Pyx_PyObject_GetMethod(PyObject *obj, PyObject *name, PyObject **method);

 
static PyObject* __Pyx_PyObject_CallMethod1(PyObject* obj, PyObject* method_name, PyObject* arg);

 
static CYTHON_INLINE int __Pyx_PyObject_Append(PyObject* L, PyObject* x);

 
#ifdef CYTHON_CLINE_IN_TRACEBACK
#define __Pyx_CLineForTraceback(tstate, c_line)  (((CYTHON_CLINE_IN_TRACEBACK)) ? c_line : 0)
#else
static int __Pyx_CLineForTraceback(PyThreadState *tstate, int c_line);
#endif

 
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

 
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

#if PY_MAJOR_VERSION < 3
    static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags);
    static void __Pyx_ReleaseBuffer(Py_buffer *view);
#else
    #define __Pyx_GetBuffer PyObject_GetBuffer
    #define __Pyx_ReleaseBuffer PyBuffer_Release
#endif


 
typedef struct {
  Py_ssize_t shape, strides, suboffsets;
} __Pyx_Buf_DimInfo;
typedef struct {
  size_t refcount;
  Py_buffer pybuffer;
} __Pyx_Buffer;
typedef struct {
  __Pyx_Buffer *rcbuffer;
  char *data;
  __Pyx_Buf_DimInfo diminfo[8];
} __Pyx_LocalBuf_ND;

 
static int __pyx_slices_overlap(__Pyx_memviewslice *slice1,
                                __Pyx_memviewslice *slice2,
                                int ndim, size_t itemsize);

 
static CYTHON_INLINE PyObject *__pyx_capsule_create(void *p, const char *sig);

 
static int __pyx_typeinfo_cmp(__Pyx_TypeInfo *a, __Pyx_TypeInfo *b);

 
static int __Pyx_ValidateAndInit_memviewslice(
                int *axes_specs,
                int c_or_f_flag,
                int buf_flags,
                int ndim,
                __Pyx_TypeInfo *dtype,
                __Pyx_BufFmt_StackElem stack[],
                __Pyx_memviewslice *memviewslice,
                PyObject *original_obj);

 
static CYTHON_INLINE __Pyx_memviewslice __Pyx_PyObject_to_MemoryviewSlice_ds_unsigned_char__const__(PyObject *, int writable_flag);

 
static CYTHON_INLINE __Pyx_memviewslice __Pyx_PyObject_to_MemoryviewSlice_dsdsds_unsigned_char__const__(PyObject *, int writable_flag);

 
static CYTHON_INLINE PyObject *__pyx_memview_get_unsigned_char__const__(const char *itemp);

 
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #define __Pyx_CREAL(z) ((z).real())
    #define __Pyx_CIMAG(z) ((z).imag())
  #else
    #define __Pyx_CREAL(z) (__real__(z))
    #define __Pyx_CIMAG(z) (__imag__(z))
  #endif
#else
    #define __Pyx_CREAL(z) ((z).real)
    #define __Pyx_CIMAG(z) ((z).imag)
#endif
#if defined(__cplusplus) && CYTHON_CCOMPLEX\
        && (defined(_WIN32) || defined(__clang__) || (defined(__GNUC__) && (__GNUC__ >= 5 || __GNUC__ == 4 && __GNUC_MINOR__ >= 4 )) || __cplusplus >= 201103)
    #define __Pyx_SET_CREAL(z,x) ((z).real(x))
    #define __Pyx_SET_CIMAG(z,y) ((z).imag(y))
#else
    #define __Pyx_SET_CREAL(z,x) __Pyx_CREAL(z) = (x)
    #define __Pyx_SET_CIMAG(z,y) __Pyx_CIMAG(z) = (y)
#endif

 
#if CYTHON_CCOMPLEX
    #define __Pyx_c_eq_float(a, b)   ((a)==(b))
    #define __Pyx_c_sum_float(a, b)  ((a)+(b))
    #define __Pyx_c_diff_float(a, b) ((a)-(b))
    #define __Pyx_c_prod_float(a, b) ((a)*(b))
    #define __Pyx_c_quot_float(a, b) ((a)/(b))
    #define __Pyx_c_neg_float(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zero_float(z) ((z)==(float)0)
    #define __Pyx_c_conj_float(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_abs_float(z)     (::std::abs(z))
        #define __Pyx_c_pow_float(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zero_float(z) ((z)==0)
    #define __Pyx_c_conj_float(z)    (conjf(z))
    #if 1
        #define __Pyx_c_abs_float(z)     (cabsf(z))
        #define __Pyx_c_pow_float(a, b)  (cpowf(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eq_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sum_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_diff_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prod_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_neg_float(__pyx_t_float_complex);
    static CYTHON_INLINE int __Pyx_c_is_zero_float(__pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conj_float(__pyx_t_float_complex);
    #if 1
        static CYTHON_INLINE float __Pyx_c_abs_float(__pyx_t_float_complex);
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_pow_float(__pyx_t_float_complex, __pyx_t_float_complex);
    #endif
#endif

 
#if CYTHON_CCOMPLEX
    #define __Pyx_c_eq_double(a, b)   ((a)==(b))
    #define __Pyx_c_sum_double(a, b)  ((a)+(b))
    #define __Pyx_c_diff_double(a, b) ((a)-(b))
    #define __Pyx_c_prod_double(a, b) ((a)*(b))
    #define __Pyx_c_quot_double(a, b) ((a)/(b))
    #define __Pyx_c_neg_double(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zero_double(z) ((z)==(double)0)
    #define __Pyx_c_conj_double(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_abs_double(z)     (::std::abs(z))
        #define __Pyx_c_pow_double(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zero_double(z) ((z)==0)
    #define __Pyx_c_conj_double(z)    (conj(z))
    #if 1
        #define __Pyx_c_abs_double(z)     (cabs(z))
        #define __Pyx_c_pow_double(a, b)  (cpow(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eq_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg_double(__pyx_t_double_complex);
    static CYTHON_INLINE int __Pyx_c_is_zero_double(__pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj_double(__pyx_t_double_complex);
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs_double(__pyx_t_double_complex);
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow_double(__pyx_t_double_complex, __pyx_t_double_complex);
    #endif
#endif

 
static __Pyx_memviewslice
__pyx_memoryview_copy_new_contig(const __Pyx_memviewslice *from_mvs,
                                 const char *mode, int ndim,
                                 size_t sizeof_dtype, int contig_flag,
                                 int dtype_is_object);

 
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value);

 
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

 
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

 
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_unsigned_char(unsigned char value);

 
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_Py_intptr_t(Py_intptr_t value);

 
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

 
static CYTHON_INLINE char __Pyx_PyInt_As_char(PyObject *);

 
static int __Pyx_check_binary_version(void);

 
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);

static PyObject *__pyx_array_get_memview(struct __pyx_array_obj *__pyx_v_self);  
static char *__pyx_memoryview_get_item_pointer(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index);  
static PyObject *__pyx_memoryview_is_slice(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_obj);  
static PyObject *__pyx_memoryview_setitem_slice_assignment(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_dst, PyObject *__pyx_v_src);  
static PyObject *__pyx_memoryview_setitem_slice_assign_scalar(struct __pyx_memoryview_obj *__pyx_v_self, struct __pyx_memoryview_obj *__pyx_v_dst, PyObject *__pyx_v_value);  
static PyObject *__pyx_memoryview_setitem_indexed(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value);  
static PyObject *__pyx_memoryview_convert_item_to_object(struct __pyx_memoryview_obj *__pyx_v_self, char *__pyx_v_itemp);  
static PyObject *__pyx_memoryview_assign_item_from_object(struct __pyx_memoryview_obj *__pyx_v_self, char *__pyx_v_itemp, PyObject *__pyx_v_value);  
static PyObject *__pyx_memoryviewslice_convert_item_to_object(struct __pyx_memoryviewslice_obj *__pyx_v_self, char *__pyx_v_itemp);  
static PyObject *__pyx_memoryviewslice_assign_item_from_object(struct __pyx_memoryviewslice_obj *__pyx_v_self, char *__pyx_v_itemp, PyObject *__pyx_v_value);  

 

 

 

 

 

 

 
static PyTypeObject *__pyx_ptype_7cpython_4type_type = 0;

 

 

 

 

 

 

 

 

 

 

 

 

 
static PyTypeObject *__pyx_ptype_7cpython_4bool_bool = 0;

 

 

 

 
static PyTypeObject *__pyx_ptype_7cpython_7complex_complex = 0;

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 
static PyTypeObject *__pyx_ptype_5numpy_dtype = 0;
static PyTypeObject *__pyx_ptype_5numpy_flatiter = 0;
static PyTypeObject *__pyx_ptype_5numpy_broadcast = 0;
static PyTypeObject *__pyx_ptype_5numpy_ndarray = 0;
static PyTypeObject *__pyx_ptype_5numpy_generic = 0;
static PyTypeObject *__pyx_ptype_5numpy_number = 0;
static PyTypeObject *__pyx_ptype_5numpy_integer = 0;
static PyTypeObject *__pyx_ptype_5numpy_signedinteger = 0;
static PyTypeObject *__pyx_ptype_5numpy_unsignedinteger = 0;
static PyTypeObject *__pyx_ptype_5numpy_inexact = 0;
static PyTypeObject *__pyx_ptype_5numpy_floating = 0;
static PyTypeObject *__pyx_ptype_5numpy_complexfloating = 0;
static PyTypeObject *__pyx_ptype_5numpy_flexible = 0;
static PyTypeObject *__pyx_ptype_5numpy_character = 0;
static PyTypeObject *__pyx_ptype_5numpy_ufunc = 0;
static CYTHON_INLINE int __pyx_f_5numpy_import_array(void);  

 
static PyTypeObject *__pyx_array_type = 0;
static PyTypeObject *__pyx_MemviewEnum_type = 0;
static PyTypeObject *__pyx_memoryview_type = 0;
static PyTypeObject *__pyx_memoryviewslice_type = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__cnames = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__cconst = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg_COLORSPACES = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg_COLORSPACE_NAMES = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__snames = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__sconst = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING_NAMES = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__pfnames = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg__pfconst = 0;
static PyObject *__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS = 0;
static int __pyx_v_10simplejpeg_5_jpeg_DECODE_BUFFER_FLAGS;
static PyObject *__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i;
static PyObject *__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c;
static PyObject *__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name;
static PyObject *__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub;
static PyObject *generic = 0;
static PyObject *strided = 0;
static PyObject *indirect = 0;
static PyObject *contiguous = 0;
static PyObject *indirect_contiguous = 0;
static int __pyx_memoryview_thread_locks_used;
static PyThread_type_lock __pyx_memoryview_thread_locks[8];
static PyObject *__pyx_f_10simplejpeg_5_jpeg___tj_error(tjhandle);  
static void __pyx_f_10simplejpeg_5_jpeg_calc_height_width(int *, int *, int, int, float);  
static struct __pyx_array_obj *__pyx_array_new(PyObject *, Py_ssize_t, char *, char *, char *);  
static void *__pyx_align_pointer(void *, size_t);  
static PyObject *__pyx_memoryview_new(PyObject *, int, int, __Pyx_TypeInfo *);  
static CYTHON_INLINE int __pyx_memoryview_check(PyObject *);  
static PyObject *_unellipsify(PyObject *, int);  
static PyObject *assert_direct_dimensions(Py_ssize_t *, int);  
static struct __pyx_memoryview_obj *__pyx_memview_slice(struct __pyx_memoryview_obj *, PyObject *);  
static int __pyx_memoryview_slice_memviewslice(__Pyx_memviewslice *, Py_ssize_t, Py_ssize_t, Py_ssize_t, int, int, int *, Py_ssize_t, Py_ssize_t, Py_ssize_t, int, int, int, int);  
static char *__pyx_pybuffer_index(Py_buffer *, char *, Py_ssize_t, Py_ssize_t);  
static int __pyx_memslice_transpose(__Pyx_memviewslice *);  
static PyObject *__pyx_memoryview_fromslice(__Pyx_memviewslice, int, PyObject *(*)(char *), int (*)(char *, PyObject *), int);  
static __Pyx_memviewslice *__pyx_memoryview_get_slice_from_memoryview(struct __pyx_memoryview_obj *, __Pyx_memviewslice *);  
static void __pyx_memoryview_slice_copy(struct __pyx_memoryview_obj *, __Pyx_memviewslice *);  
static PyObject *__pyx_memoryview_copy_object(struct __pyx_memoryview_obj *);  
static PyObject *__pyx_memoryview_copy_object_from_slice(struct __pyx_memoryview_obj *, __Pyx_memviewslice *);  
static Py_ssize_t abs_py_ssize_t(Py_ssize_t);  
static char __pyx_get_best_slice_order(__Pyx_memviewslice *, int);  
static void _copy_strided_to_strided(char *, Py_ssize_t *, char *, Py_ssize_t *, Py_ssize_t *, Py_ssize_t *, int, size_t);  
static void copy_strided_to_strided(__Pyx_memviewslice *, __Pyx_memviewslice *, int, size_t);  
static Py_ssize_t __pyx_memoryview_slice_get_size(__Pyx_memviewslice *, int);  
static Py_ssize_t __pyx_fill_contig_strides_array(Py_ssize_t *, Py_ssize_t *, Py_ssize_t, int, char);  
static void *__pyx_memoryview_copy_data_to_temp(__Pyx_memviewslice *, __Pyx_memviewslice *, char, int);  
static int __pyx_memoryview_err_extents(int, Py_ssize_t, Py_ssize_t);  
static int __pyx_memoryview_err_dim(PyObject *, char *, int);  
static int __pyx_memoryview_err(PyObject *, char *);  
static int __pyx_memoryview_copy_contents(__Pyx_memviewslice, __Pyx_memviewslice, int, int, int);  
static void __pyx_memoryview_broadcast_leading(__Pyx_memviewslice *, int, int);  
static void __pyx_memoryview_refcount_copying(__Pyx_memviewslice *, int, int, int);  
static void __pyx_memoryview_refcount_objects_in_slice_with_gil(char *, Py_ssize_t *, Py_ssize_t *, int, int);  
static void __pyx_memoryview_refcount_objects_in_slice(char *, Py_ssize_t *, Py_ssize_t *, int, int);  
static void __pyx_memoryview_slice_assign_scalar(__Pyx_memviewslice *, int, size_t, void *, int);  
static void __pyx_memoryview__slice_assign_scalar(char *, Py_ssize_t *, Py_ssize_t *, int, size_t, void *);  
static PyObject *__pyx_unpickle_Enum__set_state(struct __pyx_MemviewEnum_obj *, PyObject *);  
static __Pyx_TypeInfo __Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t = { "uint8_t", NULL, sizeof(__pyx_t_5numpy_uint8_t), { 0 }, 0, IS_UNSIGNED(__pyx_t_5numpy_uint8_t) ? 'U' : 'I', IS_UNSIGNED(__pyx_t_5numpy_uint8_t), 0 };
static __Pyx_TypeInfo __Pyx_TypeInfo_unsigned_char__const__ = { "const unsigned char", NULL, sizeof(unsigned char const ), { 0 }, 0, IS_UNSIGNED(unsigned char const ) ? 'U' : 'I', IS_UNSIGNED(unsigned char const ), 0 };
#define __Pyx_MODULE_NAME "simplejpeg._jpeg"
extern int __pyx_module_is_main_simplejpeg___jpeg;
int __pyx_module_is_main_simplejpeg___jpeg = 0;

 
static PyObject *__pyx_builtin_zip;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_RuntimeError;
static PyObject *__pyx_builtin_ValueError;
static PyObject *__pyx_builtin_ImportError;
static PyObject *__pyx_builtin_MemoryError;
static PyObject *__pyx_builtin_enumerate;
static PyObject *__pyx_builtin_TypeError;
static PyObject *__pyx_builtin_Ellipsis;
static PyObject *__pyx_builtin_id;
static PyObject *__pyx_builtin_IndexError;
static const char __pyx_k_O[] = "O";
static const char __pyx_k_c[] = "c";
static const char __pyx_k_d[] = "d";
static const char __pyx_k_i[] = "i";
static const char __pyx_k__3[] = ", ";
static const char __pyx_k_id[] = "id";
static const char __pyx_k_np[] = "np";
static const char __pyx_k_pf[] = "pf";
static const char __pyx_k_411[] = "411";
static const char __pyx_k_420[] = "420";
static const char __pyx_k_422[] = "422";
static const char __pyx_k_440[] = "440";
static const char __pyx_k_444[] = "444";
static const char __pyx_k_BGR[] = "BGR";
static const char __pyx_k_RGB[] = "RGB";
static const char __pyx_k_msg[] = "msg";
static const char __pyx_k_new[] = "__new__";
static const char __pyx_k_obj[] = "obj";
static const char __pyx_k_out[] = "out";
static const char __pyx_k_rgb[] = "rgb";
static const char __pyx_k_sub[] = "sub";
static const char __pyx_k_tmp[] = "tmp";
static const char __pyx_k_zip[] = "zip";
static const char __pyx_k_ABGR[] = "ABGR";
static const char __pyx_k_ARGB[] = "ARGB";
static const char __pyx_k_BGRA[] = "BGRA";
static const char __pyx_k_BGRX[] = "BGRX";
static const char __pyx_k_CMYK[] = "CMYK";
static const char __pyx_k_Gray[] = "Gray";
static const char __pyx_k_None[] = "None";
static const char __pyx_k_RGBA[] = "RGBA";
static const char __pyx_k_RGBX[] = "RGBX";
static const char __pyx_k_XBGR[] = "XBGR";
static const char __pyx_k_XRGB[] = "XRGB";
static const char __pyx_k_YCCK[] = "YCCK";
static const char __pyx_k_base[] = "base";
static const char __pyx_k_data[] = "data";
static const char __pyx_k_dict[] = "__dict__";
static const char __pyx_k_dims[] = "dims";
static const char __pyx_k_jpeg[] = "jpeg";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_mode[] = "mode";
static const char __pyx_k_name[] = "name";
static const char __pyx_k_ndim[] = "ndim";
static const char __pyx_k_pack[] = "pack";
static const char __pyx_k_size[] = "size";
static const char __pyx_k_step[] = "step";
static const char __pyx_k_stop[] = "stop";
static const char __pyx_k_test[] = "test";
static const char __pyx_k_view[] = "view";
static const char __pyx_k_ASCII[] = "ASCII";
static const char __pyx_k_YCbCr[] = "YCbCr";
static const char __pyx_k_class[] = "__class__";
static const char __pyx_k_error[] = "error";
static const char __pyx_k_flags[] = "flags";
static const char __pyx_k_image[] = ") image";
static const char __pyx_k_lower[] = "lower";
static const char __pyx_k_numpy[] = "numpy";
static const char __pyx_k_out_p[] = "out_p";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_shape[] = "shape";
static const char __pyx_k_start[] = "start";
static const char __pyx_k_tmp_p[] = "tmp_p";
static const char __pyx_k_uint8[] = "uint8";
static const char __pyx_k_upper[] = "upper";
static const char __pyx_k_width[] = "width";
static const char __pyx_k_append[] = "append";
static const char __pyx_k_buffer[] = "buffer";
static const char __pyx_k_data_p[] = "data_p";
static const char __pyx_k_encode[] = "encode";
static const char __pyx_k_format[] = "format";
static const char __pyx_k_height[] = "height";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_name_2[] = "__name__";
static const char __pyx_k_outlen[] = "outlen";
static const char __pyx_k_pickle[] = "pickle";
static const char __pyx_k_reduce[] = "__reduce__";
static const char __pyx_k_strict[] = "strict";
static const char __pyx_k_struct[] = "struct";
static const char __pyx_k_test_2[] = "__test__";
static const char __pyx_k_tmplen[] = "tmplen";
static const char __pyx_k_unpack[] = "unpack";
static const char __pyx_k_update[] = "update";
static const char __pyx_k_decoder[] = "decoder";
static const char __pyx_k_encoder[] = "encoder";
static const char __pyx_k_fastdct[] = "fastdct";
static const char __pyx_k_fortran[] = "fortran";
static const char __pyx_k_image_2[] = "image";
static const char __pyx_k_image_p[] = "image_p";
static const char __pyx_k_is_cmyk[] = "is_cmyk";
static const char __pyx_k_jpegbuf[] = "jpegbuf";
static const char __pyx_k_memview[] = "memview";
static const char __pyx_k_quality[] = "quality";
static const char __pyx_k_reshape[] = "reshape";
static const char __pyx_k_retcode[] = "retcode";
static const char __pyx_k_unknown[] = "unknown";
static const char __pyx_k_Ellipsis[] = "Ellipsis";
static const char __pyx_k_channels[] = "channels";
static const char __pyx_k_data_len[] = "data_len";
static const char __pyx_k_getstate[] = "__getstate__";
static const char __pyx_k_itemsize[] = "itemsize";
static const char __pyx_k_jpegsize[] = "jpegsize";
static const char __pyx_k_pyx_type[] = "__pyx_type";
static const char __pyx_k_setstate[] = "__setstate__";
static const char __pyx_k_TypeError[] = "TypeError";
static const char __pyx_k_bufferlen[] = "bufferlen";
static const char __pyx_k_enumerate[] = "enumerate";
static const char __pyx_k_min_width[] = "min_width";
static const char __pyx_k_pyx_state[] = "__pyx_state";
static const char __pyx_k_reduce_ex[] = "__reduce_ex__";
static const char __pyx_k_IndexError[] = "IndexError";
static const char __pyx_k_ValueError[] = "ValueError";
static const char __pyx_k_colorspace[] = "colorspace";
static const char __pyx_k_frombuffer[] = "frombuffer";
static const char __pyx_k_jpegbufbuf[] = "jpegbufbuf";
static const char __pyx_k_min_factor[] = "min_factor";
static const char __pyx_k_min_height[] = "min_height";
static const char __pyx_k_pyx_result[] = "__pyx_result";
static const char __pyx_k_pyx_vtable[] = "__pyx_vtable__";
static const char __pyx_k_ImportError[] = "ImportError";
static const char __pyx_k_MemoryError[] = "MemoryError";
static const char __pyx_k_PickleError[] = "PickleError";
static const char __pyx_k_decode_jpeg[] = "decode_jpeg";
static const char __pyx_k_encode_jpeg[] = "encode_jpeg";
static const char __pyx_k_jpegSubsamp[] = "jpegSubsamp";
static const char __pyx_k_RuntimeError[] = "RuntimeError";
static const char __pyx_k_colorspace_2[] = "colorspace_";
static const char __pyx_k_fastupsample[] = "fastupsample";
static const char __pyx_k_pyx_checksum[] = "__pyx_checksum";
static const char __pyx_k_stringsource[] = "stringsource";
static const char __pyx_k_pyx_getbuffer[] = "__pyx_getbuffer";
static const char __pyx_k_reduce_cython[] = "__reduce_cython__";
static const char __pyx_k_jpegColorspace[] = "jpegColorspace";
static const char __pyx_k_tmp_colorspace[] = "tmp_colorspace";
static const char __pyx_k_View_MemoryView[] = "View.MemoryView";
static const char __pyx_k_allocate_buffer[] = "allocate_buffer";
static const char __pyx_k_dtype_is_object[] = "dtype_is_object";
static const char __pyx_k_pyx_PickleError[] = "__pyx_PickleError";
static const char __pyx_k_setstate_cython[] = "__setstate_cython__";
static const char __pyx_k_colorsubsampling[] = "colorsubsampling";
static const char __pyx_k_simplejpeg__jpeg[] = "simplejpeg._jpeg";
static const char __pyx_k_output_colorspace[] = "output_colorspace";
static const char __pyx_k_pyx_unpickle_Enum[] = "__pyx_unpickle_Enum";
static const char __pyx_k_cline_in_traceback[] = "cline_in_traceback";
static const char __pyx_k_colorsubsampling_2[] = "colorsubsampling_";
static const char __pyx_k_decode_jpeg_header[] = "decode_jpeg_header";
static const char __pyx_k_strided_and_direct[] = "<strided and direct>";
static const char __pyx_k_unknown_JPEG_error[] = "unknown JPEG error";
static const char __pyx_k_simplejpeg__jpeg_pyx[] = "simplejpeg/_jpeg.pyx";
static const char __pyx_k_strided_and_indirect[] = "<strided and indirect>";
static const char __pyx_k_contiguous_and_direct[] = "<contiguous and direct>";
static const char __pyx_k_MemoryView_of_r_object[] = "<MemoryView of %r object>";
static const char __pyx_k_MemoryView_of_r_at_0x_x[] = "<MemoryView of %r at 0x%x>";
static const char __pyx_k_contiguous_and_indirect[] = "<contiguous and indirect>";
static const char __pyx_k_Cannot_index_with_type_s[] = "Cannot index with type '%s'";
static const char __pyx_k_Invalid_shape_in_axis_d_d[] = "Invalid shape in axis %d: %d.";
static const char __pyx_k_image_must_be_C_contiguous[] = "image must be C contiguous";
static const char __pyx_k_itemsize_0_for_cython_array[] = "itemsize <= 0 for cython.array";
static const char __pyx_k_could_not_create_JPEG_decoder[] = "could not create JPEG decoder";
static const char __pyx_k_could_not_create_JPEG_encoder[] = "could not create JPEG encoder";
static const char __pyx_k_unable_to_allocate_array_data[] = "unable to allocate array data.";
static const char __pyx_k_strided_and_direct_or_indirect[] = "<strided and direct or indirect>";
static const char __pyx_k_byte_buffer_is_too_small_to_dec[] = " byte buffer is too small to decode (";
static const char __pyx_k_channels_does_not_match_given_c[] = " channels does not match given colorspace ";
static const char __pyx_k_numpy_core_multiarray_failed_to[] = "numpy.core.multiarray failed to import";
static const char __pyx_k_Buffer_view_does_not_expose_stri[] = "Buffer view does not expose strides";
static const char __pyx_k_Can_only_create_a_buffer_that_is[] = "Can only create a buffer that is contiguous in memory.";
static const char __pyx_k_Cannot_assign_to_read_only_memor[] = "Cannot assign to read-only memoryview";
static const char __pyx_k_Cannot_create_writable_memory_vi[] = "Cannot create writable memory view from read-only memoryview";
static const char __pyx_k_Empty_shape_tuple_for_cython_arr[] = "Empty shape tuple for cython.array";
static const char __pyx_k_Incompatible_checksums_0x_x_vs_0[] = "Incompatible checksums (0x%x vs (0xb068931, 0x82a3537, 0x6ae9995) = (name))";
static const char __pyx_k_Indirect_dimensions_not_supporte[] = "Indirect dimensions not supported";
static const char __pyx_k_Invalid_mode_expected_c_or_fortr[] = "Invalid mode, expected 'c' or 'fortran', got %s";
static const char __pyx_k_Out_of_bounds_on_buffer_access_a[] = "Out of bounds on buffer access (axis %d)";
static const char __pyx_k_Unable_to_convert_item_to_object[] = "Unable to convert item to object";
static const char __pyx_k_buffer_object_must_support_buffe[] = "buffer object must support buffer interface and must be writable and contiguous";
static const char __pyx_k_got_differing_extents_in_dimensi[] = "got differing extents in dimension %d (got %d and %d)";
static const char __pyx_k_no_default___reduce___due_to_non[] = "no default __reduce__ due to non-trivial __cinit__";
static const char __pyx_k_numpy_core_umath_failed_to_impor[] = "numpy.core.umath failed to import";
static const char __pyx_k_unable_to_allocate_shape_and_str[] = "unable to allocate shape and strides.";
static PyObject *__pyx_kp_u_411;
static PyObject *__pyx_kp_u_420;
static PyObject *__pyx_kp_u_422;
static PyObject *__pyx_kp_u_440;
static PyObject *__pyx_kp_u_444;
static PyObject *__pyx_n_u_ABGR;
static PyObject *__pyx_n_u_ARGB;
static PyObject *__pyx_n_s_ASCII;
static PyObject *__pyx_n_u_BGR;
static PyObject *__pyx_n_u_BGRA;
static PyObject *__pyx_n_u_BGRX;
static PyObject *__pyx_kp_s_Buffer_view_does_not_expose_stri;
static PyObject *__pyx_n_u_CMYK;
static PyObject *__pyx_kp_s_Can_only_create_a_buffer_that_is;
static PyObject *__pyx_kp_s_Cannot_assign_to_read_only_memor;
static PyObject *__pyx_kp_s_Cannot_create_writable_memory_vi;
static PyObject *__pyx_kp_s_Cannot_index_with_type_s;
static PyObject *__pyx_n_s_Ellipsis;
static PyObject *__pyx_kp_s_Empty_shape_tuple_for_cython_arr;
static PyObject *__pyx_n_u_Gray;
static PyObject *__pyx_n_s_ImportError;
static PyObject *__pyx_kp_s_Incompatible_checksums_0x_x_vs_0;
static PyObject *__pyx_n_s_IndexError;
static PyObject *__pyx_kp_s_Indirect_dimensions_not_supporte;
static PyObject *__pyx_kp_s_Invalid_mode_expected_c_or_fortr;
static PyObject *__pyx_kp_s_Invalid_shape_in_axis_d_d;
static PyObject *__pyx_n_s_MemoryError;
static PyObject *__pyx_kp_s_MemoryView_of_r_at_0x_x;
static PyObject *__pyx_kp_s_MemoryView_of_r_object;
static PyObject *__pyx_kp_u_None;
static PyObject *__pyx_n_b_O;
static PyObject *__pyx_kp_s_Out_of_bounds_on_buffer_access_a;
static PyObject *__pyx_n_s_PickleError;
static PyObject *__pyx_n_u_RGB;
static PyObject *__pyx_n_u_RGBA;
static PyObject *__pyx_n_u_RGBX;
static PyObject *__pyx_n_s_RuntimeError;
static PyObject *__pyx_n_s_TypeError;
static PyObject *__pyx_kp_s_Unable_to_convert_item_to_object;
static PyObject *__pyx_n_s_ValueError;
static PyObject *__pyx_n_s_View_MemoryView;
static PyObject *__pyx_n_u_XBGR;
static PyObject *__pyx_n_u_XRGB;
static PyObject *__pyx_n_u_YCCK;
static PyObject *__pyx_n_u_YCbCr;
static PyObject *__pyx_kp_u__3;
static PyObject *__pyx_n_s_allocate_buffer;
static PyObject *__pyx_n_s_append;
static PyObject *__pyx_n_s_base;
static PyObject *__pyx_n_s_buffer;
static PyObject *__pyx_kp_u_buffer_object_must_support_buffe;
static PyObject *__pyx_n_s_bufferlen;
static PyObject *__pyx_kp_u_byte_buffer_is_too_small_to_dec;
static PyObject *__pyx_n_s_c;
static PyObject *__pyx_n_u_c;
static PyObject *__pyx_n_s_channels;
static PyObject *__pyx_kp_u_channels_does_not_match_given_c;
static PyObject *__pyx_n_s_class;
static PyObject *__pyx_n_s_cline_in_traceback;
static PyObject *__pyx_n_s_colorspace;
static PyObject *__pyx_n_s_colorspace_2;
static PyObject *__pyx_n_s_colorsubsampling;
static PyObject *__pyx_n_s_colorsubsampling_2;
static PyObject *__pyx_kp_s_contiguous_and_direct;
static PyObject *__pyx_kp_s_contiguous_and_indirect;
static PyObject *__pyx_kp_u_could_not_create_JPEG_decoder;
static PyObject *__pyx_kp_u_could_not_create_JPEG_encoder;
static PyObject *__pyx_n_u_d;
static PyObject *__pyx_n_s_data;
static PyObject *__pyx_n_s_data_len;
static PyObject *__pyx_n_s_data_p;
static PyObject *__pyx_n_s_decode_jpeg;
static PyObject *__pyx_n_s_decode_jpeg_header;
static PyObject *__pyx_n_s_decoder;
static PyObject *__pyx_n_s_dict;
static PyObject *__pyx_n_s_dims;
static PyObject *__pyx_n_s_dtype_is_object;
static PyObject *__pyx_n_s_encode;
static PyObject *__pyx_n_s_encode_jpeg;
static PyObject *__pyx_n_s_encoder;
static PyObject *__pyx_n_s_enumerate;
static PyObject *__pyx_n_s_error;
static PyObject *__pyx_n_s_fastdct;
static PyObject *__pyx_n_s_fastupsample;
static PyObject *__pyx_n_s_flags;
static PyObject *__pyx_n_s_format;
static PyObject *__pyx_n_s_fortran;
static PyObject *__pyx_n_u_fortran;
static PyObject *__pyx_n_s_frombuffer;
static PyObject *__pyx_n_s_getstate;
static PyObject *__pyx_kp_s_got_differing_extents_in_dimensi;
static PyObject *__pyx_n_s_height;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_id;
static PyObject *__pyx_kp_u_image;
static PyObject *__pyx_n_s_image_2;
static PyObject *__pyx_kp_u_image_must_be_C_contiguous;
static PyObject *__pyx_n_s_image_p;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_is_cmyk;
static PyObject *__pyx_n_s_itemsize;
static PyObject *__pyx_kp_s_itemsize_0_for_cython_array;
static PyObject *__pyx_n_s_jpeg;
static PyObject *__pyx_n_s_jpegColorspace;
static PyObject *__pyx_n_s_jpegSubsamp;
static PyObject *__pyx_n_s_jpegbuf;
static PyObject *__pyx_n_s_jpegbufbuf;
static PyObject *__pyx_n_s_jpegsize;
static PyObject *__pyx_n_s_lower;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_memview;
static PyObject *__pyx_n_s_min_factor;
static PyObject *__pyx_n_s_min_height;
static PyObject *__pyx_n_s_min_width;
static PyObject *__pyx_n_s_mode;
static PyObject *__pyx_n_s_msg;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_name_2;
static PyObject *__pyx_n_s_ndim;
static PyObject *__pyx_n_s_new;
static PyObject *__pyx_kp_s_no_default___reduce___due_to_non;
static PyObject *__pyx_n_s_np;
static PyObject *__pyx_n_s_numpy;
static PyObject *__pyx_kp_u_numpy_core_multiarray_failed_to;
static PyObject *__pyx_kp_u_numpy_core_umath_failed_to_impor;
static PyObject *__pyx_n_s_obj;
static PyObject *__pyx_n_s_out;
static PyObject *__pyx_n_s_out_p;
static PyObject *__pyx_n_s_outlen;
static PyObject *__pyx_n_s_output_colorspace;
static PyObject *__pyx_n_s_pack;
static PyObject *__pyx_n_s_pf;
static PyObject *__pyx_n_s_pickle;
static PyObject *__pyx_n_s_pyx_PickleError;
static PyObject *__pyx_n_s_pyx_checksum;
static PyObject *__pyx_n_s_pyx_getbuffer;
static PyObject *__pyx_n_s_pyx_result;
static PyObject *__pyx_n_s_pyx_state;
static PyObject *__pyx_n_s_pyx_type;
static PyObject *__pyx_n_s_pyx_unpickle_Enum;
static PyObject *__pyx_n_s_pyx_vtable;
static PyObject *__pyx_n_s_quality;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_reduce;
static PyObject *__pyx_n_s_reduce_cython;
static PyObject *__pyx_n_s_reduce_ex;
static PyObject *__pyx_n_s_reshape;
static PyObject *__pyx_n_s_retcode;
static PyObject *__pyx_n_u_rgb;
static PyObject *__pyx_n_s_setstate;
static PyObject *__pyx_n_s_setstate_cython;
static PyObject *__pyx_n_s_shape;
static PyObject *__pyx_n_s_simplejpeg__jpeg;
static PyObject *__pyx_kp_s_simplejpeg__jpeg_pyx;
static PyObject *__pyx_n_s_size;
static PyObject *__pyx_n_s_start;
static PyObject *__pyx_n_s_step;
static PyObject *__pyx_n_s_stop;
static PyObject *__pyx_n_s_strict;
static PyObject *__pyx_kp_s_strided_and_direct;
static PyObject *__pyx_kp_s_strided_and_direct_or_indirect;
static PyObject *__pyx_kp_s_strided_and_indirect;
static PyObject *__pyx_kp_s_stringsource;
static PyObject *__pyx_n_s_struct;
static PyObject *__pyx_n_s_sub;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_test_2;
static PyObject *__pyx_n_s_tmp;
static PyObject *__pyx_n_s_tmp_colorspace;
static PyObject *__pyx_n_s_tmp_p;
static PyObject *__pyx_n_s_tmplen;
static PyObject *__pyx_n_s_uint8;
static PyObject *__pyx_kp_s_unable_to_allocate_array_data;
static PyObject *__pyx_kp_s_unable_to_allocate_shape_and_str;
static PyObject *__pyx_n_u_unknown;
static PyObject *__pyx_kp_u_unknown_JPEG_error;
static PyObject *__pyx_n_s_unpack;
static PyObject *__pyx_n_s_update;
static PyObject *__pyx_n_s_upper;
static PyObject *__pyx_n_s_view;
static PyObject *__pyx_n_s_width;
static PyObject *__pyx_n_s_zip;
static PyObject *__pyx_pf_10simplejpeg_5_jpeg_decode_jpeg_header(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_data, int __pyx_v_min_height, int __pyx_v_min_width, float __pyx_v_min_factor, int __pyx_v_strict);  
static PyObject *__pyx_pf_10simplejpeg_5_jpeg_2decode_jpeg(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_data, PyObject *__pyx_v_colorspace, int __pyx_v_fastdct, int __pyx_v_fastupsample, int __pyx_v_min_height, int __pyx_v_min_width, float __pyx_v_min_factor, PyObject *__pyx_v_buffer, int __pyx_v_strict);  
static PyObject *__pyx_pf_10simplejpeg_5_jpeg_4encode_jpeg(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_image, int __pyx_v_quality, PyObject *__pyx_v_colorspace, PyObject *__pyx_v_colorsubsampling, int __pyx_v_fastdct);  
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array___cinit__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_shape, Py_ssize_t __pyx_v_itemsize, PyObject *__pyx_v_format, PyObject *__pyx_v_mode, int __pyx_v_allocate_buffer);  
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_2__getbuffer__(struct __pyx_array_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
static void __pyx_array___pyx_pf_15View_dot_MemoryView_5array_4__dealloc__(struct __pyx_array_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_5array_7memview___get__(struct __pyx_array_obj *__pyx_v_self);  
static Py_ssize_t __pyx_array___pyx_pf_15View_dot_MemoryView_5array_6__len__(struct __pyx_array_obj *__pyx_v_self);  
static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_8__getattr__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_attr);  
static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_10__getitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item);  
static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_12__setitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value);  
static PyObject *__pyx_pf___pyx_array___reduce_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_array_2__setstate_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state);  
static int __pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum___init__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v_name);  
static PyObject *__pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum_2__repr__(struct __pyx_MemviewEnum_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_MemviewEnum___reduce_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_MemviewEnum_2__setstate_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v___pyx_state);  
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview___cinit__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_obj, int __pyx_v_flags, int __pyx_v_dtype_is_object);  
static void __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_2__dealloc__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_4__getitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index);  
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_6__setitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value);  
static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_8__getbuffer__(struct __pyx_memoryview_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_1T___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4base___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_5shape___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_7strides___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_10suboffsets___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4ndim___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_8itemsize___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_6nbytes___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4size___get__(struct __pyx_memoryview_obj *__pyx_v_self);  
static Py_ssize_t __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_10__len__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_12__repr__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_14__str__(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_16is_c_contig(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_18is_f_contig(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_20copy(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_22copy_fortran(struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_memoryview___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_memoryview_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state);  
static void __pyx_memoryviewslice___pyx_pf_15View_dot_MemoryView_16_memoryviewslice___dealloc__(struct __pyx_memoryviewslice_obj *__pyx_v_self);  
static PyObject *__pyx_pf_15View_dot_MemoryView_16_memoryviewslice_4base___get__(struct __pyx_memoryviewslice_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_memoryviewslice___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self);  
static PyObject *__pyx_pf___pyx_memoryviewslice_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_pf_15View_dot_MemoryView___pyx_unpickle_Enum(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_tp_new_array(PyTypeObject *t, PyObject *a, PyObject *k);  
static PyObject *__pyx_tp_new_Enum(PyTypeObject *t, PyObject *a, PyObject *k);  
static PyObject *__pyx_tp_new_memoryview(PyTypeObject *t, PyObject *a, PyObject *k);  
static PyObject *__pyx_tp_new__memoryviewslice(PyTypeObject *t, PyObject *a, PyObject *k);  
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_112105877;
static PyObject *__pyx_int_136983863;
static PyObject *__pyx_int_184977713;
static PyObject *__pyx_int_neg_1;
static PyObject *__pyx_tuple_;
static PyObject *__pyx_tuple__2;
static PyObject *__pyx_tuple__4;
static PyObject *__pyx_tuple__5;
static PyObject *__pyx_tuple__6;
static PyObject *__pyx_tuple__7;
static PyObject *__pyx_tuple__8;
static PyObject *__pyx_tuple__9;
static PyObject *__pyx_slice__22;
static PyObject *__pyx_tuple__10;
static PyObject *__pyx_tuple__11;
static PyObject *__pyx_tuple__12;
static PyObject *__pyx_tuple__13;
static PyObject *__pyx_tuple__14;
static PyObject *__pyx_tuple__15;
static PyObject *__pyx_tuple__16;
static PyObject *__pyx_tuple__17;
static PyObject *__pyx_tuple__18;
static PyObject *__pyx_tuple__19;
static PyObject *__pyx_tuple__20;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__23;
static PyObject *__pyx_tuple__24;
static PyObject *__pyx_tuple__25;
static PyObject *__pyx_tuple__26;
static PyObject *__pyx_tuple__27;
static PyObject *__pyx_tuple__29;
static PyObject *__pyx_tuple__31;
static PyObject *__pyx_tuple__33;
static PyObject *__pyx_tuple__34;
static PyObject *__pyx_tuple__35;
static PyObject *__pyx_tuple__36;
static PyObject *__pyx_tuple__37;
static PyObject *__pyx_tuple__38;
static PyObject *__pyx_codeobj__28;
static PyObject *__pyx_codeobj__30;
static PyObject *__pyx_codeobj__32;
static PyObject *__pyx_codeobj__39;
 

 

static PyObject *__pyx_f_10simplejpeg_5_jpeg___tj_error(tjhandle __pyx_v_decoder_) {
  char *__pyx_v_error;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__tj_error", 0);

   
  __pyx_v_error = tjGetErrorStr2(__pyx_v_decoder_);

   
  __pyx_t_1 = ((__pyx_v_error == NULL) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(__pyx_kp_u_unknown_JPEG_error);
    __pyx_r = __pyx_kp_u_unknown_JPEG_error;
    goto __pyx_L0;

     
  }

   
    {
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __Pyx_decode_c_string(__pyx_v_error, 0, strlen(__pyx_v_error), NULL, ((char const *)"replace"), PyUnicode_DecodeUTF8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 158, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_r = ((PyObject*)__pyx_t_2);
    __pyx_t_2 = 0;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("simplejpeg._jpeg.__tj_error", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static void __pyx_f_10simplejpeg_5_jpeg_calc_height_width(int *__pyx_v_height, int *__pyx_v_width, int __pyx_v_min_height, int __pyx_v_min_width, float __pyx_v_min_factor) {
  int __pyx_v_numscalingfactors;
  tjscalingfactor *__pyx_v_factors;
  tjscalingfactor __pyx_v_fac;
  int __pyx_v_f;
  int __pyx_v_height_;
  int __pyx_v_width_;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;

   
  __pyx_v_factors = tjGetScalingFactors((&__pyx_v_numscalingfactors));

   
  __pyx_v_f = -1;

   
  __pyx_v_height_ = (__pyx_v_height[0]);

   
  __pyx_v_width_ = (__pyx_v_width[0]);

   
  __pyx_t_1 = __pyx_v_min_height;
  __pyx_t_2 = __pyx_v_height_;
  if (((__pyx_t_1 < __pyx_t_2) != 0)) {
    __pyx_t_3 = __pyx_t_1;
  } else {
    __pyx_t_3 = __pyx_t_2;
  }
  __pyx_v_min_height = __pyx_t_3;

   
  __pyx_t_3 = __pyx_v_min_width;
  __pyx_t_1 = __pyx_v_width_;
  if (((__pyx_t_3 < __pyx_t_1) != 0)) {
    __pyx_t_2 = __pyx_t_3;
  } else {
    __pyx_t_2 = __pyx_t_1;
  }
  __pyx_v_min_width = __pyx_t_2;

   
  __pyx_t_5 = ((__pyx_v_min_height > 0) != 0);
  if (!__pyx_t_5) {
  } else {
    __pyx_t_4 = __pyx_t_5;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_5 = ((__pyx_v_min_width > 0) != 0);
  __pyx_t_4 = __pyx_t_5;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_4) {

     
    for (__pyx_t_2 = (__pyx_v_numscalingfactors - 1); __pyx_t_2 > -1; __pyx_t_2-=1) {
      __pyx_v_f = __pyx_t_2;

       
      __pyx_v_fac = (__pyx_v_factors[__pyx_v_f]);

       
      __pyx_t_4 = ((__pyx_v_fac.num == __pyx_v_fac.denom) != 0);
      if (__pyx_t_4) {

         
        goto __pyx_L7_break;

         
      }

       
      __pyx_t_5 = ((TJSCALED(__pyx_v_width_, __pyx_v_fac) >= __pyx_v_min_width) != 0);
      if (__pyx_t_5) {
      } else {
        __pyx_t_4 = __pyx_t_5;
        goto __pyx_L10_bool_binop_done;
      }

       
      __pyx_t_5 = ((TJSCALED(__pyx_v_height_, __pyx_v_fac) >= __pyx_v_min_height) != 0);
      __pyx_t_4 = __pyx_t_5;
      __pyx_L10_bool_binop_done:;

       
      if (__pyx_t_4) {

         
        goto __pyx_L7_break;

         
      }
    }
    __pyx_L7_break:;

     
  }

   
  __pyx_t_5 = ((__pyx_v_f >= 0) != 0);
  if (__pyx_t_5) {
  } else {
    __pyx_t_4 = __pyx_t_5;
    goto __pyx_L13_bool_binop_done;
  }
  __pyx_t_5 = ((__pyx_v_fac.denom >= (__pyx_v_min_factor * __pyx_v_fac.num)) != 0);
  __pyx_t_4 = __pyx_t_5;
  __pyx_L13_bool_binop_done:;
  if (__pyx_t_4) {

     
    (__pyx_v_height[0]) = TJSCALED(__pyx_v_height_, __pyx_v_fac);

     
    (__pyx_v_width[0]) = TJSCALED(__pyx_v_width_, __pyx_v_fac);

     
  }

   

   
}

 

 
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_1decode_jpeg_header(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static char __pyx_doc_10simplejpeg_5_jpeg_decode_jpeg_header[] = "\n    Decode the header of a JPEG image.\n    Returns height and width in pixels\n    and colorspace and subsampling as string.\n\n    Parameters:\n        data: JPEG data\n        min_height: height should be >= this minimum\n                    height in pixels; values <= 0 are ignored\n        min_width: width should be >= this minimum\n                   width in pixels; values <= 0 are ignored\n        min_factor: minimum scaling factor when decoding to smaller\n                    ize; factors smaller than 2 may take longer to\n                    decode; default 1\n        strict: if True, raise ValueError for recoverable errors;\n                default True\n\n    Returns:\n        height, width, colorspace, color subsampling\n    ";
static PyMethodDef __pyx_mdef_10simplejpeg_5_jpeg_1decode_jpeg_header = {"decode_jpeg_header", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_10simplejpeg_5_jpeg_1decode_jpeg_header, METH_VARARGS|METH_KEYWORDS, __pyx_doc_10simplejpeg_5_jpeg_decode_jpeg_header};
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_1decode_jpeg_header(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  __Pyx_memviewslice __pyx_v_data = { 0, 0, { 0 }, { 0 }, { 0 } };
  int __pyx_v_min_height;
  int __pyx_v_min_width;
  float __pyx_v_min_factor;
  int __pyx_v_strict;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("decode_jpeg_header (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_data,&__pyx_n_s_min_height,&__pyx_n_s_min_width,&__pyx_n_s_min_factor,&__pyx_n_s_strict,0};
    PyObject* values[5] = {0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_data)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_height);
          if (value) { values[1] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_width);
          if (value) { values[2] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_factor);
          if (value) { values[3] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_strict);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "decode_jpeg_header") < 0)) __PYX_ERR(0, 194, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_data = __Pyx_PyObject_to_MemoryviewSlice_ds_unsigned_char__const__(values[0], 0); if (unlikely(!__pyx_v_data.memview)) __PYX_ERR(0, 195, __pyx_L3_error)
    if (values[1]) {
      __pyx_v_min_height = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_min_height == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 196, __pyx_L3_error)
    } else {
      __pyx_v_min_height = ((int)0);
    }
    if (values[2]) {
      __pyx_v_min_width = __Pyx_PyInt_As_int(values[2]); if (unlikely((__pyx_v_min_width == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 197, __pyx_L3_error)
    } else {
      __pyx_v_min_width = ((int)0);
    }
    if (values[3]) {
      __pyx_v_min_factor = __pyx_PyFloat_AsFloat(values[3]); if (unlikely((__pyx_v_min_factor == (float)-1) && PyErr_Occurred())) __PYX_ERR(0, 198, __pyx_L3_error)
    } else {
      __pyx_v_min_factor = ((float)1.0);
    }
    if (values[4]) {
      __pyx_v_strict = __Pyx_PyObject_IsTrue(values[4]); if (unlikely((__pyx_v_strict == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 199, __pyx_L3_error)
    } else {

       
      __pyx_v_strict = ((int)1);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("decode_jpeg_header", 0, 1, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 194, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("simplejpeg._jpeg.decode_jpeg_header", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(((PyObject *)__pyx_v_data.memview) == Py_None)) {
    PyErr_Format(PyExc_TypeError, "Argument '%.200s' must not be None", "data"); __PYX_ERR(0, 195, __pyx_L1_error)
  }
  __pyx_r = __pyx_pf_10simplejpeg_5_jpeg_decode_jpeg_header(__pyx_self, __pyx_v_data, __pyx_v_min_height, __pyx_v_min_width, __pyx_v_min_factor, __pyx_v_strict);

   

   
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_10simplejpeg_5_jpeg_decode_jpeg_header(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_data, int __pyx_v_min_height, int __pyx_v_min_width, float __pyx_v_min_factor, int __pyx_v_strict) {
  unsigned char const *__pyx_v_data_p;
  unsigned long __pyx_v_data_len;
  int __pyx_v_retcode;
  int __pyx_v_width;
  int __pyx_v_height;
  int __pyx_v_jpegSubsamp;
  int __pyx_v_jpegColorspace;
  tjhandle __pyx_v_decoder;
  PyObject *__pyx_v_msg = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  size_t __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("decode_jpeg_header", 0);

   
  __pyx_t_1 = 0;
  if (__pyx_t_1 < 0) __pyx_t_1 += __pyx_v_data.shape[0];
  __pyx_v_data_p = (&(*((unsigned char const  *) (   (__pyx_v_data.data + __pyx_t_1 * __pyx_v_data.strides[0]) ))));

   
  __pyx_t_2 = __Pyx_MemoryView_Len(__pyx_v_data); 
  __pyx_v_data_len = __pyx_t_2;

   
  __pyx_v_width = -1;

   
  __pyx_v_height = -1;

   
  __pyx_v_jpegSubsamp = -1;

   
  __pyx_v_jpegColorspace = -1;

   
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      __Pyx_FastGIL_Remember();
      #endif
        {

         
        __pyx_v_decoder = tjInitDecompress();

         
        __pyx_t_3 = ((__pyx_v_decoder == NULL) != 0);
        if (__pyx_t_3) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {
                __pyx_t_4 = __Pyx_PyObject_Call(__pyx_builtin_RuntimeError, __pyx_tuple_, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 232, __pyx_L8_error)
                __Pyx_GOTREF(__pyx_t_4);
                __Pyx_Raise(__pyx_t_4, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
                __PYX_ERR(0, 232, __pyx_L8_error)
              }
                {
                __pyx_L8_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L4_error;
                }
              }
          }

           
        }

         
        __pyx_v_retcode = tjDecompressHeader3(__pyx_v_decoder, __pyx_v_data_p, __pyx_v_data_len, (&__pyx_v_width), (&__pyx_v_height), (&__pyx_v_jpegSubsamp), (&__pyx_v_jpegColorspace));

         
        __pyx_t_5 = ((__pyx_v_retcode != 0) != 0);
        if (__pyx_t_5) {
        } else {
          __pyx_t_3 = __pyx_t_5;
          goto __pyx_L11_bool_binop_done;
        }
        __pyx_t_5 = (__pyx_v_strict != 0);
        if (!__pyx_t_5) {
        } else {
          __pyx_t_3 = __pyx_t_5;
          goto __pyx_L11_bool_binop_done;
        }
        __pyx_t_5 = ((tjGetErrorCode(__pyx_v_decoder) == TJERR_FATAL) != 0);
        __pyx_t_3 = __pyx_t_5;
        __pyx_L11_bool_binop_done:;
        if (__pyx_t_3) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {

                 
                __pyx_t_4 = __pyx_f_10simplejpeg_5_jpeg___tj_error(__pyx_v_decoder); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 244, __pyx_L15_error)
                __Pyx_GOTREF(__pyx_t_4);
                __pyx_v_msg = ((PyObject*)__pyx_t_4);
                __pyx_t_4 = 0;

                 
                (void)(tjDestroy(__pyx_v_decoder));

                 
                __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_v_msg); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 246, __pyx_L15_error)
                __Pyx_GOTREF(__pyx_t_4);
                __Pyx_Raise(__pyx_t_4, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
                __PYX_ERR(0, 246, __pyx_L15_error)
              }

               
                {
                __pyx_L15_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L4_error;
                }
              }
          }

           
        }

         
        (void)(tjDestroy(__pyx_v_decoder));

         
        __pyx_f_10simplejpeg_5_jpeg_calc_height_width((&__pyx_v_height), (&__pyx_v_width), __pyx_v_min_height, __pyx_v_min_width, __pyx_v_min_factor);
      }

       
        {
         {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L5;
        }
        __pyx_L4_error: {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L1_error;
        }
        __pyx_L5:;
      }
  }

   
  __Pyx_XDECREF(__pyx_r);

   
  __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_height); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 250, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

   
  __pyx_t_6 = __Pyx_PyInt_From_int(__pyx_v_width); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 251, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);

   
  __pyx_t_7 = __Pyx_GetItemInt(__pyx_v_10simplejpeg_5_jpeg_COLORSPACE_NAMES, __pyx_v_jpegColorspace, int, 1, __Pyx_PyInt_From_int, 0, 1, 0); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 252, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);

   
  __pyx_t_8 = __Pyx_GetItemInt(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING_NAMES, __pyx_v_jpegSubsamp, int, 1, __Pyx_PyInt_From_int, 0, 1, 0); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);

   
  __pyx_t_9 = PyTuple_New(4); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 250, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_9, 1, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_7);
  PyTuple_SET_ITEM(__pyx_t_9, 2, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_8);
  PyTuple_SET_ITEM(__pyx_t_9, 3, __pyx_t_8);
  __pyx_t_4 = 0;
  __pyx_t_6 = 0;
  __pyx_t_7 = 0;
  __pyx_t_8 = 0;
  __pyx_r = __pyx_t_9;
  __pyx_t_9 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("simplejpeg._jpeg.decode_jpeg_header", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_msg);
  __PYX_XDEC_MEMVIEW(&__pyx_v_data, 1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_3decode_jpeg(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static char __pyx_doc_10simplejpeg_5_jpeg_2decode_jpeg[] = "\n    Decode a JPEG (JFIF) string.\n    Returns a numpy array.\n\n    Parameters:\n        data: JPEG data\n        colorspace: target colorspace, any of the following:\n                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',\n                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB';\n                   'CMYK' may be used for images already in CMYK space.\n        fastdct: If True, use fastest DCT method;\n                 speeds up decoding by 4-5% for a minor loss in quality\n        fastupsample: If True, use fastest color upsampling method;\n                      speeds up decoding by 4-5% for a minor loss\n                      in quality\n        min_height: height should be >= this minimum in pixels;\n                    values <= 0 are ignored\n        min_width: width should be >= this minimum in pixels;\n                   values <= 0 are ignored\n        min_factor: minimum scaling factor (original size / decoded size);\n                    factors smaller than 2 may take longer to decode;\n                    default 1\n        buffer: use given object as output buffer;\n                must support the buffer protocol and be writable, e.g.,\n                numpy ndarray or bytearray;\n                use decode_jpeg_header to find out required minimum size\n                if image dimensions are unknown\n        strict: if True, raise ValueError for recoverable errors;\n                default True\n\n    Returns:\n        image as numpy array\n    ";
static PyMethodDef __pyx_mdef_10simplejpeg_5_jpeg_3decode_jpeg = {"decode_jpeg", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_10simplejpeg_5_jpeg_3decode_jpeg, METH_VARARGS|METH_KEYWORDS, __pyx_doc_10simplejpeg_5_jpeg_2decode_jpeg};
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_3decode_jpeg(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  __Pyx_memviewslice __pyx_v_data = { 0, 0, { 0 }, { 0 }, { 0 } };
  PyObject *__pyx_v_colorspace = 0;
  int __pyx_v_fastdct;
  int __pyx_v_fastupsample;
  int __pyx_v_min_height;
  int __pyx_v_min_width;
  float __pyx_v_min_factor;
  PyObject *__pyx_v_buffer = 0;
  int __pyx_v_strict;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("decode_jpeg (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_data,&__pyx_n_s_colorspace,&__pyx_n_s_fastdct,&__pyx_n_s_fastupsample,&__pyx_n_s_min_height,&__pyx_n_s_min_width,&__pyx_n_s_min_factor,&__pyx_n_s_buffer,&__pyx_n_s_strict,0};
    PyObject* values[9] = {0,0,0,0,0,0,0,0,0};
    values[1] = ((PyObject*)__pyx_n_u_rgb);

     
    values[7] = ((PyObject *)Py_None);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        CYTHON_FALLTHROUGH;
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        CYTHON_FALLTHROUGH;
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        CYTHON_FALLTHROUGH;
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        CYTHON_FALLTHROUGH;
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_data)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_colorspace);
          if (value) { values[1] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_fastdct);
          if (value) { values[2] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_fastupsample);
          if (value) { values[3] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_height);
          if (value) { values[4] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  5:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_width);
          if (value) { values[5] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  6:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_min_factor);
          if (value) { values[6] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  7:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_buffer);
          if (value) { values[7] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  8:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_strict);
          if (value) { values[8] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "decode_jpeg") < 0)) __PYX_ERR(0, 260, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        CYTHON_FALLTHROUGH;
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        CYTHON_FALLTHROUGH;
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        CYTHON_FALLTHROUGH;
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        CYTHON_FALLTHROUGH;
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_data = __Pyx_PyObject_to_MemoryviewSlice_ds_unsigned_char__const__(values[0], 0); if (unlikely(!__pyx_v_data.memview)) __PYX_ERR(0, 261, __pyx_L3_error)
    __pyx_v_colorspace = ((PyObject*)values[1]);
    if (values[2]) {
      __pyx_v_fastdct = __Pyx_PyObject_IsTrue(values[2]); if (unlikely((__pyx_v_fastdct == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 263, __pyx_L3_error)
    } else {

       
      __pyx_v_fastdct = ((int)0);
    }
    if (values[3]) {
      __pyx_v_fastupsample = __Pyx_PyObject_IsTrue(values[3]); if (unlikely((__pyx_v_fastupsample == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 264, __pyx_L3_error)
    } else {

       
      __pyx_v_fastupsample = ((int)0);
    }
    if (values[4]) {
      __pyx_v_min_height = __Pyx_PyInt_As_int(values[4]); if (unlikely((__pyx_v_min_height == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 265, __pyx_L3_error)
    } else {
      __pyx_v_min_height = ((int)0);
    }
    if (values[5]) {
      __pyx_v_min_width = __Pyx_PyInt_As_int(values[5]); if (unlikely((__pyx_v_min_width == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 266, __pyx_L3_error)
    } else {
      __pyx_v_min_width = ((int)0);
    }
    if (values[6]) {
      __pyx_v_min_factor = __pyx_PyFloat_AsFloat(values[6]); if (unlikely((__pyx_v_min_factor == (float)-1) && PyErr_Occurred())) __PYX_ERR(0, 267, __pyx_L3_error)
    } else {
      __pyx_v_min_factor = ((float)1.0);
    }
    __pyx_v_buffer = values[7];
    if (values[8]) {
      __pyx_v_strict = __Pyx_PyObject_IsTrue(values[8]); if (unlikely((__pyx_v_strict == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 269, __pyx_L3_error)
    } else {

       
      __pyx_v_strict = ((int)1);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("decode_jpeg", 0, 1, 9, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 260, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("simplejpeg._jpeg.decode_jpeg", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(((PyObject *)__pyx_v_data.memview) == Py_None)) {
    PyErr_Format(PyExc_TypeError, "Argument '%.200s' must not be None", "data"); __PYX_ERR(0, 261, __pyx_L1_error)
  }
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_colorspace), (&PyUnicode_Type), 1, "colorspace", 1))) __PYX_ERR(0, 262, __pyx_L1_error)
  __pyx_r = __pyx_pf_10simplejpeg_5_jpeg_2decode_jpeg(__pyx_self, __pyx_v_data, __pyx_v_colorspace, __pyx_v_fastdct, __pyx_v_fastupsample, __pyx_v_min_height, __pyx_v_min_width, __pyx_v_min_factor, __pyx_v_buffer, __pyx_v_strict);

   

   
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_10simplejpeg_5_jpeg_2decode_jpeg(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_data, PyObject *__pyx_v_colorspace, int __pyx_v_fastdct, int __pyx_v_fastupsample, int __pyx_v_min_height, int __pyx_v_min_width, float __pyx_v_min_factor, PyObject *__pyx_v_buffer, int __pyx_v_strict) {
  CYTHON_UNUSED unsigned char __pyx_v_test;
  unsigned char const *__pyx_v_data_p;
  unsigned long __pyx_v_data_len;
  int __pyx_v_retcode;
  int __pyx_v_width;
  int __pyx_v_height;
  int __pyx_v_jpegSubsamp;
  int __pyx_v_jpegColorspace;
  tjhandle __pyx_v_decoder;
  PyObject *__pyx_v_msg = NULL;
  int __pyx_v_tmp_colorspace;
  int __pyx_v_output_colorspace;
  int __pyx_v_is_cmyk;
  CYTHON_UNUSED npy_intp __pyx_v_tmplen;
  npy_intp __pyx_v_outlen;
  PyArrayObject *__pyx_v_tmp = 0;
  PyArrayObject *__pyx_v_out = 0;
  unsigned char *__pyx_v_tmp_p;
  unsigned char *__pyx_v_out_p;
  Py_buffer __pyx_v_view;
  npy_intp __pyx_v_bufferlen;
  npy_intp *__pyx_v_dims;
  int __pyx_v_flags;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_out;
  __Pyx_Buffer __pyx_pybuffer_out;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_tmp;
  __Pyx_Buffer __pyx_pybuffer_tmp;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  size_t __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  int __pyx_t_6;
  npy_intp __pyx_t_7[3];
  PyArrayObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  Py_ssize_t __pyx_t_12;
  Py_ssize_t __pyx_t_13;
  Py_ssize_t __pyx_t_14;
  Py_UCS4 __pyx_t_15;
  PyObject *__pyx_t_16 = NULL;
  PyObject *__pyx_t_17 = NULL;
  PyObject *__pyx_t_18 = NULL;
  PyObject *__pyx_t_19 = NULL;
  PyObject *__pyx_t_20 = NULL;
  PyObject *__pyx_t_21 = NULL;
  npy_intp __pyx_t_22[3];
  PyArrayObject *__pyx_t_23 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("decode_jpeg", 0);
  __pyx_pybuffer_tmp.pybuffer.buf = NULL;
  __pyx_pybuffer_tmp.refcount = 0;
  __pyx_pybuffernd_tmp.data = NULL;
  __pyx_pybuffernd_tmp.rcbuffer = &__pyx_pybuffer_tmp;
  __pyx_pybuffer_out.pybuffer.buf = NULL;
  __pyx_pybuffer_out.refcount = 0;
  __pyx_pybuffernd_out.data = NULL;
  __pyx_pybuffernd_out.rcbuffer = &__pyx_pybuffer_out;

   
  __pyx_v_test = 5;

   
  __pyx_t_1 = 0;
  if (__pyx_t_1 < 0) __pyx_t_1 += __pyx_v_data.shape[0];
  __pyx_v_data_p = (&(*((unsigned char const  *) (   (__pyx_v_data.data + __pyx_t_1 * __pyx_v_data.strides[0]) ))));

   
  __pyx_t_2 = __Pyx_MemoryView_Len(__pyx_v_data); 
  __pyx_v_data_len = __pyx_t_2;

   
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      __Pyx_FastGIL_Remember();
      #endif
        {

         
        __pyx_v_decoder = tjInitDecompress();

         
        __pyx_t_3 = ((__pyx_v_decoder == NULL) != 0);
        if (__pyx_t_3) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {
                __pyx_t_4 = __Pyx_PyObject_Call(__pyx_builtin_RuntimeError, __pyx_tuple_, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 316, __pyx_L8_error)
                __Pyx_GOTREF(__pyx_t_4);
                __Pyx_Raise(__pyx_t_4, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
                __PYX_ERR(0, 316, __pyx_L8_error)
              }
                {
                __pyx_L8_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L4_error;
                }
              }
          }

           
        }

         
        __pyx_v_retcode = tjDecompressHeader3(__pyx_v_decoder, __pyx_v_data_p, __pyx_v_data_len, (&__pyx_v_width), (&__pyx_v_height), (&__pyx_v_jpegSubsamp), (&__pyx_v_jpegColorspace));

         
        __pyx_t_3 = ((__pyx_v_retcode != 0) != 0);
        if (__pyx_t_3) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {

                 
                __pyx_t_4 = __pyx_f_10simplejpeg_5_jpeg___tj_error(__pyx_v_decoder); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 328, __pyx_L12_error)
                __Pyx_GOTREF(__pyx_t_4);
                __pyx_v_msg = ((PyObject*)__pyx_t_4);
                __pyx_t_4 = 0;

                 
                (void)(tjDestroy(__pyx_v_decoder));

                 
                __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_v_msg); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 330, __pyx_L12_error)
                __Pyx_GOTREF(__pyx_t_4);
                __Pyx_Raise(__pyx_t_4, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
                __PYX_ERR(0, 330, __pyx_L12_error)
              }

               
                {
                __pyx_L12_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L4_error;
                }
              }
          }

           
        }

         
        __pyx_f_10simplejpeg_5_jpeg_calc_height_width((&__pyx_v_height), (&__pyx_v_width), __pyx_v_min_height, __pyx_v_min_width, __pyx_v_min_factor);
      }

       
        {
         {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L5;
        }
        __pyx_L4_error: {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L1_error;
        }
        __pyx_L5:;
      }
  }

   
  __pyx_t_4 = __Pyx_PyObject_Dict_GetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_v_colorspace); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyInt_As_int(__pyx_t_4); if (unlikely((__pyx_t_5 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_tmp_colorspace = __pyx_t_5;

   
  __pyx_t_4 = __Pyx_PyObject_Dict_GetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_v_colorspace); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyInt_As_int(__pyx_t_4); if (unlikely((__pyx_t_5 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_output_colorspace = __pyx_t_5;

   
  __pyx_v_is_cmyk = 0;

   
  __pyx_t_6 = ((__pyx_v_jpegColorspace == TJCS_CMYK) != 0);
  if (!__pyx_t_6) {
  } else {
    __pyx_t_3 = __pyx_t_6;
    goto __pyx_L15_bool_binop_done;
  }
  __pyx_t_6 = ((__pyx_v_jpegColorspace == TJCS_YCCK) != 0);
  __pyx_t_3 = __pyx_t_6;
  __pyx_L15_bool_binop_done:;
  if (__pyx_t_3) {

     
    __pyx_v_tmp_colorspace = TJPF_CMYK;

     
    __pyx_v_is_cmyk = 1;

     
  }

   
  __pyx_v_tmplen = ((__pyx_v_height * __pyx_v_width) * (tjPixelSize[__pyx_v_tmp_colorspace]));

   
  __pyx_v_outlen = ((__pyx_v_height * __pyx_v_width) * (tjPixelSize[__pyx_v_output_colorspace]));

   
  __pyx_v_bufferlen = 0;

   
  __pyx_t_7[0] = __pyx_v_height;
  __pyx_t_7[1] = __pyx_v_width;
  __pyx_t_7[2] = (tjPixelSize[__pyx_v_output_colorspace]);
  __pyx_v_dims = __pyx_t_7;

   
  __pyx_t_3 = (__pyx_v_buffer == Py_None);
  __pyx_t_6 = (__pyx_t_3 != 0);
  if (__pyx_t_6) {

     
    __pyx_t_4 = PyArray_EMPTY(3, __pyx_v_dims, NPY_UINT8, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 355, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 355, __pyx_L1_error)
    __pyx_t_8 = ((PyArrayObject *)__pyx_t_4);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out.rcbuffer->pybuffer);
      __pyx_t_5 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out.rcbuffer->pybuffer, (PyObject*)__pyx_t_8, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack);
      if (unlikely(__pyx_t_5 < 0)) {
        PyErr_Fetch(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out.rcbuffer->pybuffer, (PyObject*)__pyx_v_out, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_11);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        }
        __pyx_t_9 = __pyx_t_10 = __pyx_t_11 = 0;
      }
      __pyx_pybuffernd_out.diminfo[0].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_out.diminfo[0].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_out.diminfo[1].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_out.diminfo[1].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[1]; __pyx_pybuffernd_out.diminfo[2].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[2]; __pyx_pybuffernd_out.diminfo[2].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[2];
      if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 355, __pyx_L1_error)
    }
    __pyx_t_8 = 0;
    __pyx_v_out = ((PyArrayObject *)__pyx_t_4);
    __pyx_t_4 = 0;

     
    __pyx_t_1 = 0;
    __pyx_t_12 = 0;
    __pyx_t_13 = 0;
    if (__pyx_t_1 < 0) __pyx_t_1 += __pyx_pybuffernd_out.diminfo[0].shape;
    if (__pyx_t_12 < 0) __pyx_t_12 += __pyx_pybuffernd_out.diminfo[1].shape;
    if (__pyx_t_13 < 0) __pyx_t_13 += __pyx_pybuffernd_out.diminfo[2].shape;
    __pyx_v_out_p = (&(*__Pyx_BufPtrStrided3d(__pyx_t_5numpy_uint8_t *, __pyx_pybuffernd_out.rcbuffer->pybuffer.buf, __pyx_t_1, __pyx_pybuffernd_out.diminfo[0].strides, __pyx_t_12, __pyx_pybuffernd_out.diminfo[1].strides, __pyx_t_13, __pyx_pybuffernd_out.diminfo[2].strides)));

     
    goto __pyx_L17;
  }

   
    {
    __pyx_t_5 = PyObject_GetBuffer(__pyx_v_buffer, (&__pyx_v_view), __pyx_v_10simplejpeg_5_jpeg_DECODE_BUFFER_FLAGS); if (unlikely(__pyx_t_5 == ((int)-1))) __PYX_ERR(0, 359, __pyx_L1_error)
    __pyx_t_6 = ((__pyx_t_5 != 0) != 0);
    if (unlikely(__pyx_t_6)) {

       
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__2, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 360, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_Raise(__pyx_t_4, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __PYX_ERR(0, 360, __pyx_L1_error)

       
    }

     
    __pyx_t_14 = __pyx_v_view.len;
    __pyx_v_bufferlen = __pyx_t_14;

     
    __pyx_t_6 = ((__pyx_v_bufferlen < __pyx_v_outlen) != 0);
    if (unlikely(__pyx_t_6)) {

       
      PyBuffer_Release((&__pyx_v_view));

       
      __pyx_t_4 = PyTuple_New(8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 366, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_14 = 0;
      __pyx_t_15 = 127;

       
      __pyx_t_16 = __Pyx_PyInt_From_Py_intptr_t(__pyx_v_bufferlen); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __pyx_t_17 = __Pyx_PyObject_FormatAndDecref(__Pyx_PyNumber_IntOrLong(__pyx_t_16), __pyx_n_u_d); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      __pyx_t_15 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_17) > __pyx_t_15) ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_17) : __pyx_t_15;
      __pyx_t_14 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_17);
      __Pyx_GIVEREF(__pyx_t_17);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_17);
      __pyx_t_17 = 0;
      __Pyx_INCREF(__pyx_kp_u_byte_buffer_is_too_small_to_dec);
      __pyx_t_14 += 37;
      __Pyx_GIVEREF(__pyx_kp_u_byte_buffer_is_too_small_to_dec);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_kp_u_byte_buffer_is_too_small_to_dec);
      __pyx_t_17 = __Pyx_PyUnicode_From_int(__pyx_v_height, 0, ' ', 'd'); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __pyx_t_14 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_17);
      __Pyx_GIVEREF(__pyx_t_17);
      PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_t_17);
      __pyx_t_17 = 0;
      __Pyx_INCREF(__pyx_kp_u__3);
      __pyx_t_14 += 2;
      __Pyx_GIVEREF(__pyx_kp_u__3);
      PyTuple_SET_ITEM(__pyx_t_4, 3, __pyx_kp_u__3);
      __pyx_t_17 = __Pyx_PyUnicode_From_int(__pyx_v_width, 0, ' ', 'd'); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __pyx_t_14 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_17);
      __Pyx_GIVEREF(__pyx_t_17);
      PyTuple_SET_ITEM(__pyx_t_4, 4, __pyx_t_17);
      __pyx_t_17 = 0;
      __Pyx_INCREF(__pyx_kp_u__3);
      __pyx_t_14 += 2;
      __Pyx_GIVEREF(__pyx_kp_u__3);
      PyTuple_SET_ITEM(__pyx_t_4, 5, __pyx_kp_u__3);
      __pyx_t_17 = __Pyx_PyInt_From_int((tjPixelSize[__pyx_v_output_colorspace])); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __pyx_t_16 = __Pyx_PyObject_FormatAndDecref(__Pyx_PyNumber_IntOrLong(__pyx_t_17), __pyx_n_u_d); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 367, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __pyx_t_15 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_16) > __pyx_t_15) ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_16) : __pyx_t_15;
      __pyx_t_14 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_16);
      __Pyx_GIVEREF(__pyx_t_16);
      PyTuple_SET_ITEM(__pyx_t_4, 6, __pyx_t_16);
      __pyx_t_16 = 0;
      __Pyx_INCREF(__pyx_kp_u_image);
      __pyx_t_14 += 7;
      __Pyx_GIVEREF(__pyx_kp_u_image);
      PyTuple_SET_ITEM(__pyx_t_4, 7, __pyx_kp_u_image);

       
      __pyx_t_16 = __Pyx_PyUnicode_Join(__pyx_t_4, 8, __pyx_t_14, __pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 366, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_t_16); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 366, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      __Pyx_Raise(__pyx_t_4, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __PYX_ERR(0, 366, __pyx_L1_error)

       
    }

     
    __Pyx_GetModuleGlobalName(__pyx_t_17, __pyx_n_s_np); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 368, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_t_17, __pyx_n_s_frombuffer); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 368, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_18);
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_17, __pyx_n_s_np); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 369, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_19 = __Pyx_PyObject_GetAttrStr(__pyx_t_17, __pyx_n_s_uint8); if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 369, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_19);
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    __pyx_t_17 = __Pyx_PyInt_From_Py_intptr_t(__pyx_v_outlen); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 369, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_20 = NULL;
    __pyx_t_5 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_18))) {
      __pyx_t_20 = PyMethod_GET_SELF(__pyx_t_18);
      if (likely(__pyx_t_20)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_18);
        __Pyx_INCREF(__pyx_t_20);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_18, function);
        __pyx_t_5 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_18)) {
      PyObject *__pyx_temp[4] = {__pyx_t_20, __pyx_v_buffer, __pyx_t_19, __pyx_t_17};
      __pyx_t_16 = __Pyx_PyFunction_FastCall(__pyx_t_18, __pyx_temp+1-__pyx_t_5, 3+__pyx_t_5); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 368, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_18)) {
      PyObject *__pyx_temp[4] = {__pyx_t_20, __pyx_v_buffer, __pyx_t_19, __pyx_t_17};
      __pyx_t_16 = __Pyx_PyCFunction_FastCall(__pyx_t_18, __pyx_temp+1-__pyx_t_5, 3+__pyx_t_5); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 368, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    } else
    #endif
    {
      __pyx_t_21 = PyTuple_New(3+__pyx_t_5); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 368, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_21);
      if (__pyx_t_20) {
        __Pyx_GIVEREF(__pyx_t_20); PyTuple_SET_ITEM(__pyx_t_21, 0, __pyx_t_20); __pyx_t_20 = NULL;
      }
      __Pyx_INCREF(__pyx_v_buffer);
      __Pyx_GIVEREF(__pyx_v_buffer);
      PyTuple_SET_ITEM(__pyx_t_21, 0+__pyx_t_5, __pyx_v_buffer);
      __Pyx_GIVEREF(__pyx_t_19);
      PyTuple_SET_ITEM(__pyx_t_21, 1+__pyx_t_5, __pyx_t_19);
      __Pyx_GIVEREF(__pyx_t_17);
      PyTuple_SET_ITEM(__pyx_t_21, 2+__pyx_t_5, __pyx_t_17);
      __pyx_t_19 = 0;
      __pyx_t_17 = 0;
      __pyx_t_16 = __Pyx_PyObject_Call(__pyx_t_18, __pyx_t_21, NULL); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 368, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_DECREF(__pyx_t_21); __pyx_t_21 = 0;
    }
    __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

     
    __pyx_t_18 = __Pyx_PyObject_GetAttrStr(__pyx_t_16, __pyx_n_s_reshape); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_18);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    __pyx_t_16 = __Pyx_PyInt_From_int(__pyx_v_height); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __pyx_t_21 = __Pyx_PyInt_From_int(__pyx_v_width); if (unlikely(!__pyx_t_21)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_21);
    __pyx_t_17 = __Pyx_PyInt_From_int((tjPixelSize[__pyx_v_output_colorspace])); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_19 = PyTuple_New(3); if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_19);
    __Pyx_GIVEREF(__pyx_t_16);
    PyTuple_SET_ITEM(__pyx_t_19, 0, __pyx_t_16);
    __Pyx_GIVEREF(__pyx_t_21);
    PyTuple_SET_ITEM(__pyx_t_19, 1, __pyx_t_21);
    __Pyx_GIVEREF(__pyx_t_17);
    PyTuple_SET_ITEM(__pyx_t_19, 2, __pyx_t_17);
    __pyx_t_16 = 0;
    __pyx_t_21 = 0;
    __pyx_t_17 = 0;
    __pyx_t_17 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_18))) {
      __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_18);
      if (likely(__pyx_t_17)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_18);
        __Pyx_INCREF(__pyx_t_17);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_18, function);
      }
    }
    __pyx_t_4 = (__pyx_t_17) ? __Pyx_PyObject_Call2Args(__pyx_t_18, __pyx_t_17, __pyx_t_19) : __Pyx_PyObject_CallOneArg(__pyx_t_18, __pyx_t_19);
    __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
    __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 370, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
    if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 370, __pyx_L1_error)
    __pyx_t_8 = ((PyArrayObject *)__pyx_t_4);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out.rcbuffer->pybuffer);
      __pyx_t_5 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out.rcbuffer->pybuffer, (PyObject*)__pyx_t_8, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack);
      if (unlikely(__pyx_t_5 < 0)) {
        PyErr_Fetch(&__pyx_t_11, &__pyx_t_10, &__pyx_t_9);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_out.rcbuffer->pybuffer, (PyObject*)__pyx_v_out, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_11); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_9);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_11, __pyx_t_10, __pyx_t_9);
        }
        __pyx_t_11 = __pyx_t_10 = __pyx_t_9 = 0;
      }
      __pyx_pybuffernd_out.diminfo[0].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_out.diminfo[0].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_out.diminfo[1].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_out.diminfo[1].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[1]; __pyx_pybuffernd_out.diminfo[2].strides = __pyx_pybuffernd_out.rcbuffer->pybuffer.strides[2]; __pyx_pybuffernd_out.diminfo[2].shape = __pyx_pybuffernd_out.rcbuffer->pybuffer.shape[2];
      if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 368, __pyx_L1_error)
    }
    __pyx_t_8 = 0;
    __pyx_v_out = ((PyArrayObject *)__pyx_t_4);
    __pyx_t_4 = 0;

     
    __pyx_v_out_p = ((unsigned char *)__pyx_v_view.buf);

     
    PyBuffer_Release((&__pyx_v_view));
  }
  __pyx_L17:;

   
  __pyx_t_6 = ((__pyx_v_tmp_colorspace != __pyx_v_output_colorspace) != 0);
  if (__pyx_t_6) {

     
    __pyx_t_22[0] = __pyx_v_height;
    __pyx_t_22[1] = __pyx_v_width;
    __pyx_t_22[2] = (tjPixelSize[__pyx_v_tmp_colorspace]);
    memcpy(&(__pyx_v_dims[0]), __pyx_t_22, sizeof(__pyx_v_dims[0]) * (3));

     
    __pyx_t_4 = PyArray_EMPTY(3, __pyx_v_dims, NPY_UINT8, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 377, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 377, __pyx_L1_error)
    __pyx_t_23 = ((PyArrayObject *)__pyx_t_4);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_tmp.rcbuffer->pybuffer);
      __pyx_t_5 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_tmp.rcbuffer->pybuffer, (PyObject*)__pyx_t_23, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack);
      if (unlikely(__pyx_t_5 < 0)) {
        PyErr_Fetch(&__pyx_t_9, &__pyx_t_10, &__pyx_t_11);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_tmp.rcbuffer->pybuffer, (PyObject*)__pyx_v_tmp, &__Pyx_TypeInfo_nn___pyx_t_5numpy_uint8_t, PyBUF_FORMAT| PyBUF_STRIDES, 3, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_9); Py_XDECREF(__pyx_t_10); Py_XDECREF(__pyx_t_11);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_9, __pyx_t_10, __pyx_t_11);
        }
        __pyx_t_9 = __pyx_t_10 = __pyx_t_11 = 0;
      }
      __pyx_pybuffernd_tmp.diminfo[0].strides = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_tmp.diminfo[0].shape = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_tmp.diminfo[1].strides = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_tmp.diminfo[1].shape = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.shape[1]; __pyx_pybuffernd_tmp.diminfo[2].strides = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.strides[2]; __pyx_pybuffernd_tmp.diminfo[2].shape = __pyx_pybuffernd_tmp.rcbuffer->pybuffer.shape[2];
      if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 377, __pyx_L1_error)
    }
    __pyx_t_23 = 0;
    __pyx_v_tmp = ((PyArrayObject *)__pyx_t_4);
    __pyx_t_4 = 0;

     
    __pyx_t_13 = 0;
    __pyx_t_12 = 0;
    __pyx_t_1 = 0;
    if (__pyx_t_13 < 0) __pyx_t_13 += __pyx_pybuffernd_tmp.diminfo[0].shape;
    if (__pyx_t_12 < 0) __pyx_t_12 += __pyx_pybuffernd_tmp.diminfo[1].shape;
    if (__pyx_t_1 < 0) __pyx_t_1 += __pyx_pybuffernd_tmp.diminfo[2].shape;
    __pyx_v_tmp_p = (&(*__Pyx_BufPtrStrided3d(__pyx_t_5numpy_uint8_t *, __pyx_pybuffernd_tmp.rcbuffer->pybuffer.buf, __pyx_t_13, __pyx_pybuffernd_tmp.diminfo[0].strides, __pyx_t_12, __pyx_pybuffernd_tmp.diminfo[1].strides, __pyx_t_1, __pyx_pybuffernd_tmp.diminfo[2].strides)));

     
    goto __pyx_L20;
  }

   
    {
    __pyx_v_tmp_p = __pyx_v_out_p;
  }
  __pyx_L20:;

   
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      __Pyx_FastGIL_Remember();
      #endif
        {

         
        __pyx_v_flags = TJFLAG_NOREALLOC;

         
        __pyx_t_6 = (__pyx_v_fastdct != 0);
        if (__pyx_t_6) {

           
          __pyx_v_flags = (__pyx_v_flags | TJFLAG_FASTDCT);

           
        }

         
        __pyx_t_6 = (__pyx_v_fastupsample != 0);
        if (__pyx_t_6) {

           
          __pyx_v_flags = (__pyx_v_flags | TJFLAG_FASTUPSAMPLE);

           
        }

         
        __pyx_v_retcode = tjDecompress2(__pyx_v_decoder, __pyx_v_data_p, __pyx_v_data_len, __pyx_v_tmp_p, __pyx_v_width, 0, __pyx_v_height, __pyx_v_tmp_colorspace, __pyx_v_flags);

         
        __pyx_t_3 = ((__pyx_v_retcode != 0) != 0);
        if (__pyx_t_3) {
        } else {
          __pyx_t_6 = __pyx_t_3;
          goto __pyx_L27_bool_binop_done;
        }
        __pyx_t_3 = (__pyx_v_strict != 0);
        if (!__pyx_t_3) {
        } else {
          __pyx_t_6 = __pyx_t_3;
          goto __pyx_L27_bool_binop_done;
        }
        __pyx_t_3 = ((tjGetErrorCode(__pyx_v_decoder) == TJERR_FATAL) != 0);
        __pyx_t_6 = __pyx_t_3;
        __pyx_L27_bool_binop_done:;
        if (__pyx_t_6) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {

                 
                __pyx_t_4 = __pyx_f_10simplejpeg_5_jpeg___tj_error(__pyx_v_decoder); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 405, __pyx_L31_error)
                __Pyx_GOTREF(__pyx_t_4);
                __pyx_v_msg = ((PyObject*)__pyx_t_4);
                __pyx_t_4 = 0;

                 
                (void)(tjDestroy(__pyx_v_decoder));

                 
                __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_v_msg); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 407, __pyx_L31_error)
                __Pyx_GOTREF(__pyx_t_4);
                __Pyx_Raise(__pyx_t_4, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
                __PYX_ERR(0, 407, __pyx_L31_error)
              }

               
                {
                __pyx_L31_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L22_error;
                }
              }
          }

           
        }

         
        (void)(tjDestroy(__pyx_v_decoder));
      }

       
        {
         {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L23;
        }
        __pyx_L22_error: {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L1_error;
        }
        __pyx_L23:;
      }
  }

   
  __pyx_t_3 = (__pyx_v_is_cmyk != 0);
  if (__pyx_t_3) {
  } else {
    __pyx_t_6 = __pyx_t_3;
    goto __pyx_L34_bool_binop_done;
  }
  __pyx_t_3 = ((__pyx_v_output_colorspace != TJPF_CMYK) != 0);
  __pyx_t_6 = __pyx_t_3;
  __pyx_L34_bool_binop_done:;
  if (__pyx_t_6) {

     
    __pyx_t_3 = ((__pyx_v_output_colorspace == TJPF_RGBA) != 0);
    if (!__pyx_t_3) {
    } else {
      __pyx_t_6 = __pyx_t_3;
      goto __pyx_L37_bool_binop_done;
    }

     
    __pyx_t_3 = ((__pyx_v_output_colorspace == TJPF_BGRA) != 0);
    if (!__pyx_t_3) {
    } else {
      __pyx_t_6 = __pyx_t_3;
      goto __pyx_L37_bool_binop_done;
    }

     
    __pyx_t_3 = ((__pyx_v_output_colorspace == TJPF_ABGR) != 0);
    if (!__pyx_t_3) {
    } else {
      __pyx_t_6 = __pyx_t_3;
      goto __pyx_L37_bool_binop_done;
    }

     
    __pyx_t_3 = ((__pyx_v_output_colorspace == TJPF_ARGB) != 0);
    __pyx_t_6 = __pyx_t_3;
    __pyx_L37_bool_binop_done:;

     
    if (__pyx_t_6) {

       
      PyArray_FILLWBYTE(((PyObject *)__pyx_v_out), 0xFF);

       
    }

     
    __pyx_t_6 = ((__pyx_v_output_colorspace == TJPF_GRAY) != 0);
    if (__pyx_t_6) {

       
      cmyk2gray(__pyx_v_tmp_p, __pyx_v_out_p, (__pyx_v_height * __pyx_v_width));

       
      goto __pyx_L41;
    }

     
      {
      cmyk2color(__pyx_v_tmp_p, __pyx_v_out_p, (__pyx_v_height * __pyx_v_width), __pyx_v_output_colorspace);
    }
    __pyx_L41:;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_out));
  __pyx_r = ((PyObject *)__pyx_v_out);
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_16);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_XDECREF(__pyx_t_18);
  __Pyx_XDECREF(__pyx_t_19);
  __Pyx_XDECREF(__pyx_t_20);
  __Pyx_XDECREF(__pyx_t_21);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_tmp.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("simplejpeg._jpeg.decode_jpeg", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_out.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_tmp.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF(__pyx_v_msg);
  __Pyx_XDECREF((PyObject *)__pyx_v_tmp);
  __Pyx_XDECREF((PyObject *)__pyx_v_out);
  __PYX_XDEC_MEMVIEW(&__pyx_v_data, 1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_5encode_jpeg(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static char __pyx_doc_10simplejpeg_5_jpeg_4encode_jpeg[] = "\n    Encode an image to JPEG (JFIF) string.\n    Returns JPEG (JFIF) data.\n\n    Parameters:\n        image: uncompressed image as uint8 array\n        quality: JPEG quantization factor\n        colorspace: source colorspace; one of\n                   'RGB', 'BGR', 'RGBX', 'BGRX', 'XBGR', 'XRGB',\n                   'GRAY', 'RGBA', 'BGRA', 'ABGR', 'ARGB', 'CMYK'.\n        colorsubsampling: subsampling factor for color channels; one of\n                          '444', '422', '420', '440', '411', 'Gray'.\n        fastdct: If True, use fastest DCT method;\n                 speeds up encoding by 4-5% for a minor loss in quality\n\n    Returns:\n        encoded image as JPEG (JFIF) data\n    ";
static PyMethodDef __pyx_mdef_10simplejpeg_5_jpeg_5encode_jpeg = {"encode_jpeg", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_10simplejpeg_5_jpeg_5encode_jpeg, METH_VARARGS|METH_KEYWORDS, __pyx_doc_10simplejpeg_5_jpeg_4encode_jpeg};
static PyObject *__pyx_pw_10simplejpeg_5_jpeg_5encode_jpeg(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  __Pyx_memviewslice __pyx_v_image = { 0, 0, { 0 }, { 0 }, { 0 } };
  int __pyx_v_quality;
  PyObject *__pyx_v_colorspace = 0;
  PyObject *__pyx_v_colorsubsampling = 0;
  int __pyx_v_fastdct;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("encode_jpeg (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_image_2,&__pyx_n_s_quality,&__pyx_n_s_colorspace,&__pyx_n_s_colorsubsampling,&__pyx_n_s_fastdct,0};
    PyObject* values[5] = {0,0,0,0,0};
    values[2] = ((PyObject*)__pyx_n_u_rgb);
    values[3] = ((PyObject*)__pyx_kp_u_444);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_image_2)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_quality);
          if (value) { values[1] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_colorspace);
          if (value) { values[2] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_colorsubsampling);
          if (value) { values[3] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_fastdct);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "encode_jpeg") < 0)) __PYX_ERR(0, 427, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_image = __Pyx_PyObject_to_MemoryviewSlice_dsdsds_unsigned_char__const__(values[0], 0); if (unlikely(!__pyx_v_image.memview)) __PYX_ERR(0, 428, __pyx_L3_error)
    if (values[1]) {
      __pyx_v_quality = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_quality == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 429, __pyx_L3_error)
    } else {
      __pyx_v_quality = ((int)85);
    }
    __pyx_v_colorspace = ((PyObject*)values[2]);
    __pyx_v_colorsubsampling = ((PyObject*)values[3]);
    if (values[4]) {
      __pyx_v_fastdct = __Pyx_PyObject_IsTrue(values[4]); if (unlikely((__pyx_v_fastdct == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 432, __pyx_L3_error)
    } else {

       
      __pyx_v_fastdct = ((int)0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("encode_jpeg", 0, 1, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 427, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("simplejpeg._jpeg.encode_jpeg", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(((PyObject *)__pyx_v_image.memview) == Py_None)) {
    PyErr_Format(PyExc_TypeError, "Argument '%.200s' must not be None", "image"); __PYX_ERR(0, 428, __pyx_L1_error)
  }
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_colorspace), (&PyUnicode_Type), 1, "colorspace", 1))) __PYX_ERR(0, 430, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_colorsubsampling), (&PyUnicode_Type), 1, "colorsubsampling", 1))) __PYX_ERR(0, 431, __pyx_L1_error)
  __pyx_r = __pyx_pf_10simplejpeg_5_jpeg_4encode_jpeg(__pyx_self, __pyx_v_image, __pyx_v_quality, __pyx_v_colorspace, __pyx_v_colorsubsampling, __pyx_v_fastdct);

   

   
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_10simplejpeg_5_jpeg_4encode_jpeg(CYTHON_UNUSED PyObject *__pyx_self, __Pyx_memviewslice __pyx_v_image, int __pyx_v_quality, PyObject *__pyx_v_colorspace, PyObject *__pyx_v_colorsubsampling, int __pyx_v_fastdct) {
  unsigned char const *__pyx_v_image_p;
  int __pyx_v_retcode;
  int __pyx_v_height;
  int __pyx_v_width;
  int __pyx_v_channels;
  int __pyx_v_colorspace_;
  int __pyx_v_colorsubsampling_;
  unsigned char *__pyx_v_jpegbuf;
  unsigned char **__pyx_v_jpegbufbuf;
  unsigned long __pyx_v_jpegsize;
  int __pyx_v_flags;
  tjhandle __pyx_v_encoder;
  PyObject *__pyx_v_msg = NULL;
  PyObject *__pyx_v_jpeg = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  Py_ssize_t __pyx_t_6;
  int __pyx_t_7;
  Py_ssize_t __pyx_t_8;
  Py_UCS4 __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("encode_jpeg", 0);

   
  __pyx_t_1 = __pyx_memviewslice_is_contig_C3(__pyx_v_image); if (unlikely(__pyx_t_1 == ((int)-1))) __PYX_ERR(0, 452, __pyx_L1_error)
  __pyx_t_2 = ((!(__pyx_t_1 != 0)) != 0);
  if (unlikely(__pyx_t_2)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__4, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 453, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(0, 453, __pyx_L1_error)

     
  }

   
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  if (__pyx_t_4 < 0) __pyx_t_4 += __pyx_v_image.shape[0];
  if (__pyx_t_5 < 0) __pyx_t_5 += __pyx_v_image.shape[1];
  if (__pyx_t_6 < 0) __pyx_t_6 += __pyx_v_image.shape[2];
  __pyx_v_image_p = (&(*((unsigned char const  *) (   ((   ((   (__pyx_v_image.data + __pyx_t_4 * __pyx_v_image.strides[0]) ) + __pyx_t_5 * __pyx_v_image.strides[1]) ) + __pyx_t_6 * __pyx_v_image.strides[2]) ))));

   
  __pyx_v_height = (__pyx_v_image.shape[0]);

   
  __pyx_v_width = (__pyx_v_image.shape[1]);

   
  __pyx_v_channels = (__pyx_v_image.shape[2]);

   
  __pyx_t_3 = __Pyx_PyObject_Dict_GetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_v_colorspace); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 459, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_7 = __Pyx_PyInt_As_int(__pyx_t_3); if (unlikely((__pyx_t_7 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 459, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_colorspace_ = __pyx_t_7;

   
  __pyx_t_2 = (((tjPixelSize[__pyx_v_colorspace_]) != __pyx_v_channels) != 0);
  if (unlikely(__pyx_t_2)) {

     
    __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 461, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_8 = 0;
    __pyx_t_9 = 127;

     
    __pyx_t_10 = __Pyx_PyUnicode_From_int(__pyx_v_channels, 0, ' ', 'd'); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 462, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_8 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_10);
    __Pyx_GIVEREF(__pyx_t_10);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_10);
    __pyx_t_10 = 0;
    __Pyx_INCREF(__pyx_kp_u_channels_does_not_match_given_c);
    __pyx_t_8 += 42;
    __Pyx_GIVEREF(__pyx_kp_u_channels_does_not_match_given_c);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_kp_u_channels_does_not_match_given_c);
    __pyx_t_10 = __Pyx_PyUnicode_Unicode(__pyx_v_colorspace); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 462, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_9 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_10) > __pyx_t_9) ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_10) : __pyx_t_9;
    __pyx_t_8 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_10);
    __Pyx_GIVEREF(__pyx_t_10);
    PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_t_10);
    __pyx_t_10 = 0;

     
    __pyx_t_10 = __Pyx_PyUnicode_Join(__pyx_t_3, 3, __pyx_t_8, __pyx_t_9); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 461, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 461, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(0, 461, __pyx_L1_error)

     
  }

   
  __pyx_v_colorsubsampling_ = TJSAMP_GRAY;

   
  __pyx_t_2 = ((__pyx_v_colorspace_ != TJPF_GRAY) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_3 = __Pyx_PyObject_Dict_GetItem(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING, __pyx_v_colorsubsampling); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 465, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_7 = __Pyx_PyInt_As_int(__pyx_t_3); if (unlikely((__pyx_t_7 == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 465, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_colorsubsampling_ = __pyx_t_7;

     
  }

   
  __pyx_v_jpegbuf = NULL;

   
  __pyx_v_jpegbufbuf = (&__pyx_v_jpegbuf);

   
  __pyx_v_jpegsize = 0;

   
  {
      #ifdef WITH_THREAD
      PyThreadState *_save;
      Py_UNBLOCK_THREADS
      __Pyx_FastGIL_Remember();
      #endif
        {

         
        __pyx_v_encoder = tjInitCompress();

         
        __pyx_t_2 = ((__pyx_v_encoder == NULL) != 0);
        if (__pyx_t_2) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {
                __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_RuntimeError, __pyx_tuple__5, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 474, __pyx_L11_error)
                __Pyx_GOTREF(__pyx_t_3);
                __Pyx_Raise(__pyx_t_3, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
                __PYX_ERR(0, 474, __pyx_L11_error)
              }
                {
                __pyx_L11_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L7_error;
                }
              }
          }

           
        }

         
        __pyx_v_flags = 0;

         
        __pyx_t_2 = (__pyx_v_fastdct != 0);
        if (__pyx_t_2) {

           
          __pyx_v_flags = (__pyx_v_flags | TJFLAG_FASTDCT);

           
        }

         
        __pyx_v_retcode = tjCompress2(__pyx_v_encoder, __pyx_v_image_p, __pyx_v_width, 0, __pyx_v_height, __pyx_v_colorspace_, __pyx_v_jpegbufbuf, (&__pyx_v_jpegsize), __pyx_v_colorsubsampling_, __pyx_v_quality, __pyx_v_flags);

         
        __pyx_t_2 = ((__pyx_v_retcode != 0) != 0);
        if (__pyx_t_2) {

           
          {
              #ifdef WITH_THREAD
              PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
              #endif
                {

                 
                __pyx_t_3 = __pyx_f_10simplejpeg_5_jpeg___tj_error(__pyx_v_encoder); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 493, __pyx_L16_error)
                __Pyx_GOTREF(__pyx_t_3);
                __pyx_v_msg = ((PyObject*)__pyx_t_3);
                __pyx_t_3 = 0;

                 
                (void)(tjDestroy(__pyx_v_encoder));

                 
                __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_v_msg); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 495, __pyx_L16_error)
                __Pyx_GOTREF(__pyx_t_3);
                __Pyx_Raise(__pyx_t_3, 0, 0, 0);
                __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
                __PYX_ERR(0, 495, __pyx_L16_error)
              }

               
                {
                __pyx_L16_error: {
                  #ifdef WITH_THREAD
                  __Pyx_PyGILState_Release(__pyx_gilstate_save);
                  #endif
                  goto __pyx_L7_error;
                }
              }
          }

           
        }
      }

       
        {
         {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L8;
        }
        __pyx_L7_error: {
          #ifdef WITH_THREAD
          __Pyx_FastGIL_Forget();
          Py_BLOCK_THREADS
          #endif
          goto __pyx_L1_error;
        }
        __pyx_L8:;
      }
  }

   
  __pyx_t_3 = PyBytes_FromStringAndSize(((char *)__pyx_v_jpegbuf), __pyx_v_jpegsize); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 496, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_jpeg = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

   
  tjFree(__pyx_v_jpegbuf);

   
  (void)(tjDestroy(__pyx_v_encoder));

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_jpeg);
  __pyx_r = __pyx_v_jpeg;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("simplejpeg._jpeg.encode_jpeg", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_msg);
  __Pyx_XDECREF(__pyx_v_jpeg);
  __PYX_XDEC_MEMVIEW(&__pyx_v_image, 1);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew1(PyObject *__pyx_v_a) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew1", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(1, ((void *)__pyx_v_a)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 735, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew1", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew2(PyObject *__pyx_v_a, PyObject *__pyx_v_b) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew2", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(2, ((void *)__pyx_v_a), ((void *)__pyx_v_b)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 738, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew2", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew3(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew3", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(3, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 741, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew3", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew4(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew4", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(4, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 744, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew4", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew5(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d, PyObject *__pyx_v_e) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew5", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(5, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d), ((void *)__pyx_v_e)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 747, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew5", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyDataType_SHAPE(PyArray_Descr *__pyx_v_d) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("PyDataType_SHAPE", 0);

   
  __pyx_t_1 = (PyDataType_HASSUBARRAY(__pyx_v_d) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(((PyObject*)__pyx_v_d->subarray->shape));
    __pyx_r = ((PyObject*)__pyx_v_d->subarray->shape);
    goto __pyx_L0;

     
  }

   
    {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(__pyx_empty_tuple);
    __pyx_r = __pyx_empty_tuple;
    goto __pyx_L0;
  }

   

   
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE void __pyx_f_5numpy_set_array_base(PyArrayObject *__pyx_v_arr, PyObject *__pyx_v_base) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("set_array_base", 0);

   
  Py_INCREF(__pyx_v_base);

   
  (void)(PyArray_SetBaseObject(__pyx_v_arr, __pyx_v_base));

   

   
  __Pyx_RefNannyFinishContext();
}

 

static CYTHON_INLINE PyObject *__pyx_f_5numpy_get_array_base(PyArrayObject *__pyx_v_arr) {
  PyObject *__pyx_v_base;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("get_array_base", 0);

   
  __pyx_v_base = PyArray_BASE(__pyx_v_arr);

   
  __pyx_t_1 = ((__pyx_v_base == NULL) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_base));
  __pyx_r = ((PyObject *)__pyx_v_base);
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_f_5numpy_import_array(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("import_array", 0);

   
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
      {

       
      __pyx_t_4 = _import_array(); if (unlikely(__pyx_t_4 == ((int)-1))) __PYX_ERR(1, 942, __pyx_L3_error)

       
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L8_try_end;
    __pyx_L3_error:;

     
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_array", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 943, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

       
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__6, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 944, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 944, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

     
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L8_try_end:;
  }

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_array", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_f_5numpy_import_umath(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("import_umath", 0);

   
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
      {

       
      __pyx_t_4 = _import_umath(); if (unlikely(__pyx_t_4 == ((int)-1))) __PYX_ERR(1, 948, __pyx_L3_error)

       
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L8_try_end;
    __pyx_L3_error:;

     
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_umath", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 949, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

       
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__7, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 950, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 950, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

     
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L8_try_end:;
  }

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_umath", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_f_5numpy_import_ufunc(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("import_ufunc", 0);

   
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
      {

       
      __pyx_t_4 = _import_umath(); if (unlikely(__pyx_t_4 == ((int)-1))) __PYX_ERR(1, 954, __pyx_L3_error)

       
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L8_try_end;
    __pyx_L3_error:;

     
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_ufunc", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 955, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

       
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__7, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 956, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 956, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

     
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L8_try_end:;
  }

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_ufunc", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_f_5numpy_is_timedelta64_object(PyObject *__pyx_v_obj) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("is_timedelta64_object", 0);

   
  __pyx_r = PyObject_TypeCheck(__pyx_v_obj, (&PyTimedeltaArrType_Type));
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_f_5numpy_is_datetime64_object(PyObject *__pyx_v_obj) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("is_datetime64_object", 0);

   
  __pyx_r = PyObject_TypeCheck(__pyx_v_obj, (&PyDatetimeArrType_Type));
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE npy_datetime __pyx_f_5numpy_get_datetime64_value(PyObject *__pyx_v_obj) {
  npy_datetime __pyx_r;

   
  __pyx_r = ((PyDatetimeScalarObject *)__pyx_v_obj)->obval;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static CYTHON_INLINE npy_timedelta __pyx_f_5numpy_get_timedelta64_value(PyObject *__pyx_v_obj) {
  npy_timedelta __pyx_r;

   
  __pyx_r = ((PyTimedeltaScalarObject *)__pyx_v_obj)->obval;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static CYTHON_INLINE NPY_DATETIMEUNIT __pyx_f_5numpy_get_datetime64_unit(PyObject *__pyx_v_obj) {
  NPY_DATETIMEUNIT __pyx_r;

   
  __pyx_r = ((NPY_DATETIMEUNIT)((PyDatetimeScalarObject *)__pyx_v_obj)->obmeta.base);
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

 
static int __pyx_array___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static int __pyx_array___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_shape = 0;
  Py_ssize_t __pyx_v_itemsize;
  PyObject *__pyx_v_format = 0;
  PyObject *__pyx_v_mode = 0;
  int __pyx_v_allocate_buffer;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__cinit__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_shape,&__pyx_n_s_itemsize,&__pyx_n_s_format,&__pyx_n_s_mode,&__pyx_n_s_allocate_buffer,0};
    PyObject* values[5] = {0,0,0,0,0};
    values[3] = ((PyObject *)__pyx_n_s_c);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_shape)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_itemsize)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__cinit__", 0, 3, 5, 1); __PYX_ERR(2, 123, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_format)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__cinit__", 0, 3, 5, 2); __PYX_ERR(2, 123, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  3:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_mode);
          if (value) { values[3] = value; kw_args--; }
        }
        CYTHON_FALLTHROUGH;
        case  4:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_allocate_buffer);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__cinit__") < 0)) __PYX_ERR(2, 123, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        CYTHON_FALLTHROUGH;
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        CYTHON_FALLTHROUGH;
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_shape = ((PyObject*)values[0]);
    __pyx_v_itemsize = __Pyx_PyIndex_AsSsize_t(values[1]); if (unlikely((__pyx_v_itemsize == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 123, __pyx_L3_error)
    __pyx_v_format = values[2];
    __pyx_v_mode = values[3];
    if (values[4]) {
      __pyx_v_allocate_buffer = __Pyx_PyObject_IsTrue(values[4]); if (unlikely((__pyx_v_allocate_buffer == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 124, __pyx_L3_error)
    } else {

       
      __pyx_v_allocate_buffer = ((int)1);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__cinit__", 0, 3, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 123, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("View.MemoryView.array.__cinit__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_shape), (&PyTuple_Type), 1, "shape", 1))) __PYX_ERR(2, 123, __pyx_L1_error)
  if (unlikely(((PyObject *)__pyx_v_format) == Py_None)) {
    PyErr_Format(PyExc_TypeError, "Argument '%.200s' must not be None", "format"); __PYX_ERR(2, 123, __pyx_L1_error)
  }
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array___cinit__(((struct __pyx_array_obj *)__pyx_v_self), __pyx_v_shape, __pyx_v_itemsize, __pyx_v_format, __pyx_v_mode, __pyx_v_allocate_buffer);

   

   
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array___cinit__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_shape, Py_ssize_t __pyx_v_itemsize, PyObject *__pyx_v_format, PyObject *__pyx_v_mode, int __pyx_v_allocate_buffer) {
  int __pyx_v_idx;
  Py_ssize_t __pyx_v_i;
  Py_ssize_t __pyx_v_dim;
  PyObject **__pyx_v_p;
  char __pyx_v_order;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  char *__pyx_t_7;
  int __pyx_t_8;
  Py_ssize_t __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  Py_ssize_t __pyx_t_11;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__cinit__", 0);
  __Pyx_INCREF(__pyx_v_format);

   
  if (unlikely(__pyx_v_shape == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 130, __pyx_L1_error)
  }
  __pyx_t_1 = PyTuple_GET_SIZE(__pyx_v_shape); if (unlikely(__pyx_t_1 == ((Py_ssize_t)-1))) __PYX_ERR(2, 130, __pyx_L1_error)
  __pyx_v_self->ndim = ((int)__pyx_t_1);

   
  __pyx_v_self->itemsize = __pyx_v_itemsize;

   
  __pyx_t_2 = ((!(__pyx_v_self->ndim != 0)) != 0);
  if (unlikely(__pyx_t_2)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__8, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 134, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 134, __pyx_L1_error)

     
  }

   
  __pyx_t_2 = ((__pyx_v_itemsize <= 0) != 0);
  if (unlikely(__pyx_t_2)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__9, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 137, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 137, __pyx_L1_error)

     
  }

   
  __pyx_t_2 = PyBytes_Check(__pyx_v_format); 
  __pyx_t_4 = ((!(__pyx_t_2 != 0)) != 0);
  if (__pyx_t_4) {

     
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_format, __pyx_n_s_encode); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    __pyx_t_3 = (__pyx_t_6) ? __Pyx_PyObject_Call2Args(__pyx_t_5, __pyx_t_6, __pyx_n_s_ASCII) : __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_n_s_ASCII);
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF_SET(__pyx_v_format, __pyx_t_3);
    __pyx_t_3 = 0;

     
  }

   
  if (!(likely(PyBytes_CheckExact(__pyx_v_format))||((__pyx_v_format) == Py_None)||((void)PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "bytes", Py_TYPE(__pyx_v_format)->tp_name), 0))) __PYX_ERR(2, 141, __pyx_L1_error)
  __pyx_t_3 = __pyx_v_format;
  __Pyx_INCREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __Pyx_GOTREF(__pyx_v_self->_format);
  __Pyx_DECREF(__pyx_v_self->_format);
  __pyx_v_self->_format = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

   
  if (unlikely(__pyx_v_self->_format == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "expected bytes, NoneType found");
    __PYX_ERR(2, 142, __pyx_L1_error)
  }
  __pyx_t_7 = __Pyx_PyBytes_AsWritableString(__pyx_v_self->_format); if (unlikely((!__pyx_t_7) && PyErr_Occurred())) __PYX_ERR(2, 142, __pyx_L1_error)
  __pyx_v_self->format = __pyx_t_7;

   
  __pyx_v_self->_shape = ((Py_ssize_t *)PyObject_Malloc((((sizeof(Py_ssize_t)) * __pyx_v_self->ndim) * 2)));

   
  __pyx_v_self->_strides = (__pyx_v_self->_shape + __pyx_v_self->ndim);

   
  __pyx_t_4 = ((!(__pyx_v_self->_shape != 0)) != 0);
  if (unlikely(__pyx_t_4)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_MemoryError, __pyx_tuple__10, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 149, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 149, __pyx_L1_error)

     
  }

   
  __pyx_t_8 = 0;
  __pyx_t_3 = __pyx_v_shape; __Pyx_INCREF(__pyx_t_3); __pyx_t_1 = 0;
  for (;;) {
    if (__pyx_t_1 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_5 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_1); __Pyx_INCREF(__pyx_t_5); __pyx_t_1++; if (unlikely(0 < 0)) __PYX_ERR(2, 152, __pyx_L1_error)
    #else
    __pyx_t_5 = PySequence_ITEM(__pyx_t_3, __pyx_t_1); __pyx_t_1++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 152, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    #endif
    __pyx_t_9 = __Pyx_PyIndex_AsSsize_t(__pyx_t_5); if (unlikely((__pyx_t_9 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 152, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_v_dim = __pyx_t_9;
    __pyx_v_idx = __pyx_t_8;
    __pyx_t_8 = (__pyx_t_8 + 1);

     
    __pyx_t_4 = ((__pyx_v_dim <= 0) != 0);
    if (unlikely(__pyx_t_4)) {

       
      __pyx_t_5 = __Pyx_PyInt_From_int(__pyx_v_idx); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_6 = PyInt_FromSsize_t(__pyx_v_dim); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_10 = PyTuple_New(2); if (unlikely(!__pyx_t_10)) __PYX_ERR(2, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_10, 1, __pyx_t_6);
      __pyx_t_5 = 0;
      __pyx_t_6 = 0;
      __pyx_t_6 = __Pyx_PyString_Format(__pyx_kp_s_Invalid_shape_in_axis_d_d, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __pyx_t_10 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(2, 154, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_Raise(__pyx_t_10, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __PYX_ERR(2, 154, __pyx_L1_error)

       
    }

     
    (__pyx_v_self->_shape[__pyx_v_idx]) = __pyx_v_dim;

     
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

   
  __pyx_t_4 = (__Pyx_PyString_Equals(__pyx_v_mode, __pyx_n_s_fortran, Py_EQ)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(2, 158, __pyx_L1_error)
  if (__pyx_t_4) {

     
    __pyx_v_order = 'F';

     
    __Pyx_INCREF(__pyx_n_u_fortran);
    __Pyx_GIVEREF(__pyx_n_u_fortran);
    __Pyx_GOTREF(__pyx_v_self->mode);
    __Pyx_DECREF(__pyx_v_self->mode);
    __pyx_v_self->mode = __pyx_n_u_fortran;

     
    goto __pyx_L10;
  }

   
  __pyx_t_4 = (__Pyx_PyString_Equals(__pyx_v_mode, __pyx_n_s_c, Py_EQ)); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(2, 161, __pyx_L1_error)
  if (likely(__pyx_t_4)) {

     
    __pyx_v_order = 'C';

     
    __Pyx_INCREF(__pyx_n_u_c);
    __Pyx_GIVEREF(__pyx_n_u_c);
    __Pyx_GOTREF(__pyx_v_self->mode);
    __Pyx_DECREF(__pyx_v_self->mode);
    __pyx_v_self->mode = __pyx_n_u_c;

     
    goto __pyx_L10;
  }

   
    {
    __pyx_t_3 = __Pyx_PyString_FormatSafe(__pyx_kp_s_Invalid_mode_expected_c_or_fortr, __pyx_v_mode); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_10 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_t_3); if (unlikely(!__pyx_t_10)) __PYX_ERR(2, 165, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_Raise(__pyx_t_10, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __PYX_ERR(2, 165, __pyx_L1_error)
  }
  __pyx_L10:;

   
  __pyx_v_self->len = __pyx_fill_contig_strides_array(__pyx_v_self->_shape, __pyx_v_self->_strides, __pyx_v_itemsize, __pyx_v_self->ndim, __pyx_v_order);

   
  __pyx_v_self->free_data = __pyx_v_allocate_buffer;

   
  __pyx_t_10 = PyObject_RichCompare(__pyx_v_format, __pyx_n_b_O, Py_EQ); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(2, 171, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 171, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_v_self->dtype_is_object = __pyx_t_4;

   
  __pyx_t_4 = (__pyx_v_allocate_buffer != 0);
  if (__pyx_t_4) {

     
    __pyx_v_self->data = ((char *)malloc(__pyx_v_self->len));

     
    __pyx_t_4 = ((!(__pyx_v_self->data != 0)) != 0);
    if (unlikely(__pyx_t_4)) {

       
      __pyx_t_10 = __Pyx_PyObject_Call(__pyx_builtin_MemoryError, __pyx_tuple__11, NULL); if (unlikely(!__pyx_t_10)) __PYX_ERR(2, 177, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_Raise(__pyx_t_10, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __PYX_ERR(2, 177, __pyx_L1_error)

       
    }

     
    __pyx_t_4 = (__pyx_v_self->dtype_is_object != 0);
    if (__pyx_t_4) {

       
      __pyx_v_p = ((PyObject **)__pyx_v_self->data);

       
      if (unlikely(__pyx_v_itemsize == 0)) {
        PyErr_SetString(PyExc_ZeroDivisionError, "integer division or modulo by zero");
        __PYX_ERR(2, 181, __pyx_L1_error)
      }
      else if (sizeof(Py_ssize_t) == sizeof(long) && (!(((Py_ssize_t)-1) > 0)) && unlikely(__pyx_v_itemsize == (Py_ssize_t)-1)  && unlikely(UNARY_NEG_WOULD_OVERFLOW(__pyx_v_self->len))) {
        PyErr_SetString(PyExc_OverflowError, "value too large to perform division");
        __PYX_ERR(2, 181, __pyx_L1_error)
      }
      __pyx_t_1 = __Pyx_div_Py_ssize_t(__pyx_v_self->len, __pyx_v_itemsize);
      __pyx_t_9 = __pyx_t_1;
      for (__pyx_t_11 = 0; __pyx_t_11 < __pyx_t_9; __pyx_t_11+=1) {
        __pyx_v_i = __pyx_t_11;

         
        (__pyx_v_p[__pyx_v_i]) = Py_None;

         
        Py_INCREF(Py_None);
      }

       
    }

     
  }

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("View.MemoryView.array.__cinit__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_format);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static CYTHON_UNUSED int __pyx_array_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
static CYTHON_UNUSED int __pyx_array_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getbuffer__ (wrapper)", 0);
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array_2__getbuffer__(((struct __pyx_array_obj *)__pyx_v_self), ((Py_buffer *)__pyx_v_info), ((int)__pyx_v_flags));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_2__getbuffer__(struct __pyx_array_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_v_bufmode;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  char *__pyx_t_4;
  Py_ssize_t __pyx_t_5;
  int __pyx_t_6;
  Py_ssize_t *__pyx_t_7;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  if (__pyx_v_info == NULL) {
    PyErr_SetString(PyExc_BufferError, "PyObject_GetBuffer: view==NULL argument is obsolete");
    return -1;
  }
  __Pyx_RefNannySetupContext("__getbuffer__", 0);
  __pyx_v_info->obj = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(__pyx_v_info->obj);

   
  __pyx_v_bufmode = -1;

   
  __pyx_t_1 = (__Pyx_PyUnicode_Equals(__pyx_v_self->mode, __pyx_n_u_c, Py_EQ)); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 188, __pyx_L1_error)
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __pyx_v_bufmode = (PyBUF_C_CONTIGUOUS | PyBUF_ANY_CONTIGUOUS);

     
    goto __pyx_L3;
  }

   
  __pyx_t_2 = (__Pyx_PyUnicode_Equals(__pyx_v_self->mode, __pyx_n_u_fortran, Py_EQ)); if (unlikely(__pyx_t_2 < 0)) __PYX_ERR(2, 190, __pyx_L1_error)
  __pyx_t_1 = (__pyx_t_2 != 0);
  if (__pyx_t_1) {

     
    __pyx_v_bufmode = (PyBUF_F_CONTIGUOUS | PyBUF_ANY_CONTIGUOUS);

     
  }
  __pyx_L3:;

   
  __pyx_t_1 = ((!((__pyx_v_flags & __pyx_v_bufmode) != 0)) != 0);
  if (unlikely(__pyx_t_1)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__12, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 193, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 193, __pyx_L1_error)

     
  }

   
  __pyx_t_4 = __pyx_v_self->data;
  __pyx_v_info->buf = __pyx_t_4;

   
  __pyx_t_5 = __pyx_v_self->len;
  __pyx_v_info->len = __pyx_t_5;

   
  __pyx_t_6 = __pyx_v_self->ndim;
  __pyx_v_info->ndim = __pyx_t_6;

   
  __pyx_t_7 = __pyx_v_self->_shape;
  __pyx_v_info->shape = __pyx_t_7;

   
  __pyx_t_7 = __pyx_v_self->_strides;
  __pyx_v_info->strides = __pyx_t_7;

   
  __pyx_v_info->suboffsets = NULL;

   
  __pyx_t_5 = __pyx_v_self->itemsize;
  __pyx_v_info->itemsize = __pyx_t_5;

   
  __pyx_v_info->readonly = 0;

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_FORMAT) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_4 = __pyx_v_self->format;
    __pyx_v_info->format = __pyx_t_4;

     
    goto __pyx_L5;
  }

   
    {
    __pyx_v_info->format = NULL;
  }
  __pyx_L5:;

   
  __Pyx_INCREF(((PyObject *)__pyx_v_self));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
  __Pyx_GOTREF(__pyx_v_info->obj);
  __Pyx_DECREF(__pyx_v_info->obj);
  __pyx_v_info->obj = ((PyObject *)__pyx_v_self);

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.array.__getbuffer__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  if (__pyx_v_info->obj != NULL) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = 0;
  }
  goto __pyx_L2;
  __pyx_L0:;
  if (__pyx_v_info->obj == Py_None) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = 0;
  }
  __pyx_L2:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static void __pyx_array___dealloc__(PyObject *__pyx_v_self);  
static void __pyx_array___dealloc__(PyObject *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__ (wrapper)", 0);
  __pyx_array___pyx_pf_15View_dot_MemoryView_5array_4__dealloc__(((struct __pyx_array_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
}

static void __pyx_array___pyx_pf_15View_dot_MemoryView_5array_4__dealloc__(struct __pyx_array_obj *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__dealloc__", 0);

   
  __pyx_t_1 = ((__pyx_v_self->callback_free_data != NULL) != 0);
  if (__pyx_t_1) {

     
    __pyx_v_self->callback_free_data(__pyx_v_self->data);

     
    goto __pyx_L3;
  }

   
  __pyx_t_1 = (__pyx_v_self->free_data != 0);
  if (__pyx_t_1) {

     
    __pyx_t_1 = (__pyx_v_self->dtype_is_object != 0);
    if (__pyx_t_1) {

       
      __pyx_memoryview_refcount_objects_in_slice(__pyx_v_self->data, __pyx_v_self->_shape, __pyx_v_self->_strides, __pyx_v_self->ndim, 0);

       
    }

     
    free(__pyx_v_self->data);

     
  }
  __pyx_L3:;

   
  PyObject_Free(__pyx_v_self->_shape);

   

   
  __Pyx_RefNannyFinishContext();
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_5array_7memview_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_5array_7memview_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_5array_7memview___get__(((struct __pyx_array_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_5array_7memview___get__(struct __pyx_array_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = ((struct __pyx_vtabstruct_array *)__pyx_v_self->__pyx_vtab)->get_memview(__pyx_v_self); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 224, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.array.memview.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_array_get_memview(struct __pyx_array_obj *__pyx_v_self) {
  int __pyx_v_flags;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_memview", 0);

   
  __pyx_v_flags = ((PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) | PyBUF_WRITABLE);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_flags); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 229, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_v_self->dtype_is_object); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 229, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 229, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(((PyObject *)__pyx_v_self));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
  PyTuple_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_v_self));
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_t_2);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(((PyObject *)__pyx_memoryview_type), __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 229, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.array.get_memview", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static Py_ssize_t __pyx_array___len__(PyObject *__pyx_v_self);  
static Py_ssize_t __pyx_array___len__(PyObject *__pyx_v_self) {
  Py_ssize_t __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__len__ (wrapper)", 0);
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array_6__len__(((struct __pyx_array_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static Py_ssize_t __pyx_array___pyx_pf_15View_dot_MemoryView_5array_6__len__(struct __pyx_array_obj *__pyx_v_self) {
  Py_ssize_t __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__len__", 0);

   
  __pyx_r = (__pyx_v_self->_shape[0]);
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_array___getattr__(PyObject *__pyx_v_self, PyObject *__pyx_v_attr);  
static PyObject *__pyx_array___getattr__(PyObject *__pyx_v_self, PyObject *__pyx_v_attr) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getattr__ (wrapper)", 0);
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array_8__getattr__(((struct __pyx_array_obj *)__pyx_v_self), ((PyObject *)__pyx_v_attr));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_8__getattr__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_attr) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__getattr__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_memview); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 235, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_GetAttr(__pyx_t_1, __pyx_v_attr); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 235, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.array.__getattr__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_array___getitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_item);  
static PyObject *__pyx_array___getitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_item) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getitem__ (wrapper)", 0);
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array_10__getitem__(((struct __pyx_array_obj *)__pyx_v_self), ((PyObject *)__pyx_v_item));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_array___pyx_pf_15View_dot_MemoryView_5array_10__getitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__getitem__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_memview); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 238, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetItem(__pyx_t_1, __pyx_v_item); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 238, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.array.__getitem__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static int __pyx_array___setitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value);  
static int __pyx_array___setitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setitem__ (wrapper)", 0);
  __pyx_r = __pyx_array___pyx_pf_15View_dot_MemoryView_5array_12__setitem__(((struct __pyx_array_obj *)__pyx_v_self), ((PyObject *)__pyx_v_item), ((PyObject *)__pyx_v_value));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_array___pyx_pf_15View_dot_MemoryView_5array_12__setitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setitem__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_memview); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 241, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(PyObject_SetItem(__pyx_t_1, __pyx_v_item, __pyx_v_value) < 0)) __PYX_ERR(2, 241, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.array.__setitem__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_array_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_pw___pyx_array_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_array___reduce_cython__(((struct __pyx_array_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_array___reduce_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__13, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 2, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.array.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_array_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_pw___pyx_array_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_array_2__setstate_cython__(((struct __pyx_array_obj *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_array_2__setstate_cython__(CYTHON_UNUSED struct __pyx_array_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__14, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 4, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.array.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static struct __pyx_array_obj *__pyx_array_new(PyObject *__pyx_v_shape, Py_ssize_t __pyx_v_itemsize, char *__pyx_v_format, char *__pyx_v_mode, char *__pyx_v_buf) {
  struct __pyx_array_obj *__pyx_v_result = 0;
  struct __pyx_array_obj *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("array_cwrapper", 0);

   
  __pyx_t_1 = ((__pyx_v_buf == NULL) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_itemsize); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 250, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyBytes_FromString(__pyx_v_format); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 250, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = __Pyx_decode_c_string(__pyx_v_mode, 0, strlen(__pyx_v_mode), NULL, NULL, PyUnicode_DecodeASCII); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 250, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(4); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 250, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_INCREF(__pyx_v_shape);
    __Pyx_GIVEREF(__pyx_v_shape);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_v_shape);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_2);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_5, 3, __pyx_t_4);
    __pyx_t_2 = 0;
    __pyx_t_3 = 0;
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(((PyObject *)__pyx_array_type), __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 250, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_v_result = ((struct __pyx_array_obj *)__pyx_t_4);
    __pyx_t_4 = 0;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_itemsize); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 252, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = __Pyx_PyBytes_FromString(__pyx_v_format); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 252, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_3 = __Pyx_decode_c_string(__pyx_v_mode, 0, strlen(__pyx_v_mode), NULL, NULL, PyUnicode_DecodeASCII); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 252, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = PyTuple_New(4); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 252, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_v_shape);
    __Pyx_GIVEREF(__pyx_v_shape);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_shape);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_2, 2, __pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_2, 3, __pyx_t_3);
    __pyx_t_4 = 0;
    __pyx_t_5 = 0;
    __pyx_t_3 = 0;

     
    __pyx_t_3 = __Pyx_PyDict_NewPresized(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 253, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_allocate_buffer, Py_False) < 0) __PYX_ERR(2, 253, __pyx_L1_error)

     
    __pyx_t_5 = __Pyx_PyObject_Call(((PyObject *)__pyx_array_type), __pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 252, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_result = ((struct __pyx_array_obj *)__pyx_t_5);
    __pyx_t_5 = 0;

     
    __pyx_v_result->data = __pyx_v_buf;
  }
  __pyx_L3:;

   
  __Pyx_XDECREF(((PyObject *)__pyx_r));
  __Pyx_INCREF(((PyObject *)__pyx_v_result));
  __pyx_r = __pyx_v_result;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.array_cwrapper", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_result);
  __Pyx_XGIVEREF((PyObject *)__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static int __pyx_MemviewEnum___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static int __pyx_MemviewEnum___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_name = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_name,0};
    PyObject* values[1] = {0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_name)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) __PYX_ERR(2, 282, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 1) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
    }
    __pyx_v_name = values[0];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 1, 1, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 282, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("View.MemoryView.Enum.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum___init__(((struct __pyx_MemviewEnum_obj *)__pyx_v_self), __pyx_v_name);

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum___init__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v_name) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__", 0);

   
  __Pyx_INCREF(__pyx_v_name);
  __Pyx_GIVEREF(__pyx_v_name);
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(__pyx_v_self->name);
  __pyx_v_self->name = __pyx_v_name;

   

   
  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_MemviewEnum___repr__(PyObject *__pyx_v_self);  
static PyObject *__pyx_MemviewEnum___repr__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__repr__ (wrapper)", 0);
  __pyx_r = __pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum_2__repr__(((struct __pyx_MemviewEnum_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_MemviewEnum___pyx_pf_15View_dot_MemoryView_4Enum_2__repr__(struct __pyx_MemviewEnum_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__repr__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->name);
  __pyx_r = __pyx_v_self->name;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_MemviewEnum_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_pw___pyx_MemviewEnum_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_MemviewEnum___reduce_cython__(((struct __pyx_MemviewEnum_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_MemviewEnum___reduce_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self) {
  PyObject *__pyx_v_state = 0;
  PyObject *__pyx_v__dict = 0;
  int __pyx_v_use_setstate;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

   
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_self->name);
  __Pyx_GIVEREF(__pyx_v_self->name);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_self->name);
  __pyx_v_state = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

   
  __pyx_t_1 = __Pyx_GetAttr3(((PyObject *)__pyx_v_self), __pyx_n_s_dict, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v__dict = __pyx_t_1;
  __pyx_t_1 = 0;

   
  __pyx_t_2 = (__pyx_v__dict != Py_None);
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (__pyx_t_3) {

     
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v__dict);
    __Pyx_GIVEREF(__pyx_v__dict);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v__dict);
    __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_v_state, __pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 8, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF_SET(__pyx_v_state, ((PyObject*)__pyx_t_4));
    __pyx_t_4 = 0;

     
    __pyx_v_use_setstate = 1;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_3 = (__pyx_v_self->name != Py_None);
    __pyx_v_use_setstate = __pyx_t_3;
  }
  __pyx_L3:;

   
  __pyx_t_3 = (__pyx_v_use_setstate != 0);
  if (__pyx_t_3) {

     
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_4, __pyx_n_s_pyx_unpickle_Enum); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_184977713);
    __Pyx_GIVEREF(__pyx_int_184977713);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_int_184977713);
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    PyTuple_SET_ITEM(__pyx_t_1, 2, Py_None);
    __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 13, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_1);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_v_state);
    __pyx_t_4 = 0;
    __pyx_t_1 = 0;
    __pyx_r = __pyx_t_5;
    __pyx_t_5 = 0;
    goto __pyx_L0;

     
  }

   
    {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_pyx_unpickle_Enum); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_GIVEREF(((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))));
    __Pyx_INCREF(__pyx_int_184977713);
    __Pyx_GIVEREF(__pyx_int_184977713);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_int_184977713);
    __Pyx_INCREF(__pyx_v_state);
    __Pyx_GIVEREF(__pyx_v_state);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_v_state);
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_1);
    __pyx_t_5 = 0;
    __pyx_t_1 = 0;
    __pyx_r = __pyx_t_4;
    __pyx_t_4 = 0;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.Enum.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_state);
  __Pyx_XDECREF(__pyx_v__dict);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_MemviewEnum_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_pw___pyx_MemviewEnum_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_MemviewEnum_2__setstate_cython__(((struct __pyx_MemviewEnum_obj *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_MemviewEnum_2__setstate_cython__(struct __pyx_MemviewEnum_obj *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

   
  if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||((void)PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(2, 17, __pyx_L1_error)
  __pyx_t_1 = __pyx_unpickle_Enum__set_state(__pyx_v_self, ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 17, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.Enum.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static void *__pyx_align_pointer(void *__pyx_v_memory, size_t __pyx_v_alignment) {
  Py_intptr_t __pyx_v_aligned_p;
  size_t __pyx_v_offset;
  void *__pyx_r;
  int __pyx_t_1;

   
  __pyx_v_aligned_p = ((Py_intptr_t)__pyx_v_memory);

   
  __pyx_v_offset = (__pyx_v_aligned_p % __pyx_v_alignment);

   
  __pyx_t_1 = ((__pyx_v_offset > 0) != 0);
  if (__pyx_t_1) {

     
    __pyx_v_aligned_p = (__pyx_v_aligned_p + (__pyx_v_alignment - __pyx_v_offset));

     
  }

   
  __pyx_r = ((void *)__pyx_v_aligned_p);
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

 
static int __pyx_memoryview___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static int __pyx_memoryview___cinit__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_obj = 0;
  int __pyx_v_flags;
  int __pyx_v_dtype_is_object;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__cinit__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_obj,&__pyx_n_s_flags,&__pyx_n_s_dtype_is_object,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_obj)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_flags)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__cinit__", 0, 2, 3, 1); __PYX_ERR(2, 346, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (kw_args > 0) {
          PyObject* value = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_dtype_is_object);
          if (value) { values[2] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__cinit__") < 0)) __PYX_ERR(2, 346, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_obj = values[0];
    __pyx_v_flags = __Pyx_PyInt_As_int(values[1]); if (unlikely((__pyx_v_flags == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 346, __pyx_L3_error)
    if (values[2]) {
      __pyx_v_dtype_is_object = __Pyx_PyObject_IsTrue(values[2]); if (unlikely((__pyx_v_dtype_is_object == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 346, __pyx_L3_error)
    } else {
      __pyx_v_dtype_is_object = ((int)0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__cinit__", 0, 2, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 346, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("View.MemoryView.memoryview.__cinit__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview___cinit__(((struct __pyx_memoryview_obj *)__pyx_v_self), __pyx_v_obj, __pyx_v_flags, __pyx_v_dtype_is_object);

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview___cinit__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_obj, int __pyx_v_flags, int __pyx_v_dtype_is_object) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__cinit__", 0);

   
  __Pyx_INCREF(__pyx_v_obj);
  __Pyx_GIVEREF(__pyx_v_obj);
  __Pyx_GOTREF(__pyx_v_self->obj);
  __Pyx_DECREF(__pyx_v_self->obj);
  __pyx_v_self->obj = __pyx_v_obj;

   
  __pyx_v_self->flags = __pyx_v_flags;

   
  __pyx_t_2 = (((PyObject *)Py_TYPE(((PyObject *)__pyx_v_self))) == ((PyObject *)__pyx_memoryview_type));
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (!__pyx_t_3) {
  } else {
    __pyx_t_1 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_3 = (__pyx_v_obj != Py_None);
  __pyx_t_2 = (__pyx_t_3 != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_1) {

     
    __pyx_t_4 = __Pyx_GetBuffer(__pyx_v_obj, (&__pyx_v_self->view), __pyx_v_flags); if (unlikely(__pyx_t_4 == ((int)-1))) __PYX_ERR(2, 350, __pyx_L1_error)

     
    __pyx_t_1 = ((((PyObject *)__pyx_v_self->view.obj) == NULL) != 0);
    if (__pyx_t_1) {

       
      ((Py_buffer *)(&__pyx_v_self->view))->obj = Py_None;

       
      Py_INCREF(Py_None);

       
    }

     
  }

   
  __pyx_t_1 = ((!(__PYX_CYTHON_ATOMICS_ENABLED() != 0)) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_1 = ((__pyx_memoryview_thread_locks_used < 8) != 0);
    if (__pyx_t_1) {

       
      __pyx_v_self->lock = (__pyx_memoryview_thread_locks[__pyx_memoryview_thread_locks_used]);

       
      __pyx_memoryview_thread_locks_used = (__pyx_memoryview_thread_locks_used + 1);

       
    }

     
    __pyx_t_1 = ((__pyx_v_self->lock == NULL) != 0);
    if (__pyx_t_1) {

       
      __pyx_v_self->lock = PyThread_allocate_lock();

       
      __pyx_t_1 = ((__pyx_v_self->lock == NULL) != 0);
      if (unlikely(__pyx_t_1)) {

         
        PyErr_NoMemory(); __PYX_ERR(2, 363, __pyx_L1_error)

         
      }

       
    }

     
  }

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_FORMAT) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = (((__pyx_v_self->view.format[0]) == 'O') != 0);
    if (__pyx_t_2) {
    } else {
      __pyx_t_1 = __pyx_t_2;
      goto __pyx_L12_bool_binop_done;
    }
    __pyx_t_2 = (((__pyx_v_self->view.format[1]) == '\x00') != 0);
    __pyx_t_1 = __pyx_t_2;
    __pyx_L12_bool_binop_done:;
    __pyx_v_self->dtype_is_object = __pyx_t_1;

     
    goto __pyx_L11;
  }

   
    {
    __pyx_v_self->dtype_is_object = __pyx_v_dtype_is_object;
  }
  __pyx_L11:;

   
  __pyx_v_self->acquisition_count_aligned_p = ((__pyx_atomic_int *)__pyx_align_pointer(((void *)(&(__pyx_v_self->acquisition_count[0]))), (sizeof(__pyx_atomic_int))));

   
  __pyx_v_self->typeinfo = NULL;

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("View.MemoryView.memoryview.__cinit__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static void __pyx_memoryview___dealloc__(PyObject *__pyx_v_self);  
static void __pyx_memoryview___dealloc__(PyObject *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__ (wrapper)", 0);
  __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_2__dealloc__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
}

static void __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_2__dealloc__(struct __pyx_memoryview_obj *__pyx_v_self) {
  int __pyx_v_i;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  PyThread_type_lock __pyx_t_6;
  PyThread_type_lock __pyx_t_7;
  __Pyx_RefNannySetupContext("__dealloc__", 0);

   
  __pyx_t_1 = (__pyx_v_self->obj != Py_None);
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __Pyx_ReleaseBuffer((&__pyx_v_self->view));

     
    goto __pyx_L3;
  }

   
  __pyx_t_2 = ((((Py_buffer *)(&__pyx_v_self->view))->obj == Py_None) != 0);
  if (__pyx_t_2) {

     
    ((Py_buffer *)(&__pyx_v_self->view))->obj = NULL;

     
    Py_DECREF(Py_None);

     
  }
  __pyx_L3:;

   
  __pyx_t_2 = ((__pyx_v_self->lock != NULL) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_3 = __pyx_memoryview_thread_locks_used;
    __pyx_t_4 = __pyx_t_3;
    for (__pyx_t_5 = 0; __pyx_t_5 < __pyx_t_4; __pyx_t_5+=1) {
      __pyx_v_i = __pyx_t_5;

       
      __pyx_t_2 = (((__pyx_memoryview_thread_locks[__pyx_v_i]) == __pyx_v_self->lock) != 0);
      if (__pyx_t_2) {

         
        __pyx_memoryview_thread_locks_used = (__pyx_memoryview_thread_locks_used - 1);

         
        __pyx_t_2 = ((__pyx_v_i != __pyx_memoryview_thread_locks_used) != 0);
        if (__pyx_t_2) {

           
          __pyx_t_6 = (__pyx_memoryview_thread_locks[__pyx_memoryview_thread_locks_used]);
          __pyx_t_7 = (__pyx_memoryview_thread_locks[__pyx_v_i]);

           
          (__pyx_memoryview_thread_locks[__pyx_v_i]) = __pyx_t_6;
          (__pyx_memoryview_thread_locks[__pyx_memoryview_thread_locks_used]) = __pyx_t_7;

           
        }

         
        goto __pyx_L6_break;

         
      }
    }
      {

       
      PyThread_free_lock(__pyx_v_self->lock);
    }
    __pyx_L6_break:;

     
  }

   

   
  __Pyx_RefNannyFinishContext();
}

 

static char *__pyx_memoryview_get_item_pointer(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index) {
  Py_ssize_t __pyx_v_dim;
  char *__pyx_v_itemp;
  PyObject *__pyx_v_idx = NULL;
  char *__pyx_r;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *(*__pyx_t_4)(PyObject *);
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  char *__pyx_t_7;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_item_pointer", 0);

   
  __pyx_v_itemp = ((char *)__pyx_v_self->view.buf);

   
  __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_v_index)) || PyTuple_CheckExact(__pyx_v_index)) {
    __pyx_t_2 = __pyx_v_index; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    __pyx_t_4 = NULL;
  } else {
    __pyx_t_3 = -1; __pyx_t_2 = PyObject_GetIter(__pyx_v_index); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 399, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = Py_TYPE(__pyx_t_2)->tp_iternext; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 399, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_4)) {
      if (likely(PyList_CheckExact(__pyx_t_2))) {
        if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_5 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_5); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 399, __pyx_L1_error)
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 399, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        #endif
      } else {
        if (__pyx_t_3 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_5 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_5); __pyx_t_3++; if (unlikely(0 < 0)) __PYX_ERR(2, 399, __pyx_L1_error)
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 399, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        #endif
      }
    } else {
      __pyx_t_5 = __pyx_t_4(__pyx_t_2);
      if (unlikely(!__pyx_t_5)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(2, 399, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_5);
    }
    __Pyx_XDECREF_SET(__pyx_v_idx, __pyx_t_5);
    __pyx_t_5 = 0;
    __pyx_v_dim = __pyx_t_1;
    __pyx_t_1 = (__pyx_t_1 + 1);

     
    __pyx_t_6 = __Pyx_PyIndex_AsSsize_t(__pyx_v_idx); if (unlikely((__pyx_t_6 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 400, __pyx_L1_error)
    __pyx_t_7 = __pyx_pybuffer_index((&__pyx_v_self->view), __pyx_v_itemp, __pyx_t_6, __pyx_v_dim); if (unlikely(__pyx_t_7 == ((char *)NULL))) __PYX_ERR(2, 400, __pyx_L1_error)
    __pyx_v_itemp = __pyx_t_7;

     
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

   
  __pyx_r = __pyx_v_itemp;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.memoryview.get_item_pointer", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_idx);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview___getitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_index);  
static PyObject *__pyx_memoryview___getitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_index) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getitem__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_4__getitem__(((struct __pyx_memoryview_obj *)__pyx_v_self), ((PyObject *)__pyx_v_index));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_4__getitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index) {
  PyObject *__pyx_v_have_slices = NULL;
  PyObject *__pyx_v_indices = NULL;
  char *__pyx_v_itemp;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  char *__pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__getitem__", 0);

   
  __pyx_t_1 = (__pyx_v_index == __pyx_builtin_Ellipsis);
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(((PyObject *)__pyx_v_self));
    __pyx_r = ((PyObject *)__pyx_v_self);
    goto __pyx_L0;

     
  }

   
  __pyx_t_3 = _unellipsify(__pyx_v_index, __pyx_v_self->view.ndim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 409, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (likely(__pyx_t_3 != Py_None)) {
    PyObject* sequence = __pyx_t_3;
    Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(2, 409, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_4 = PyTuple_GET_ITEM(sequence, 0); 
    __pyx_t_5 = PyTuple_GET_ITEM(sequence, 1); 
    __Pyx_INCREF(__pyx_t_4);
    __Pyx_INCREF(__pyx_t_5);
    #else
    __pyx_t_4 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 409, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 409, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    #endif
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __Pyx_RaiseNoneNotIterableError(); __PYX_ERR(2, 409, __pyx_L1_error)
  }
  __pyx_v_have_slices = __pyx_t_4;
  __pyx_t_4 = 0;
  __pyx_v_indices = __pyx_t_5;
  __pyx_t_5 = 0;

   
  __pyx_t_2 = __Pyx_PyObject_IsTrue(__pyx_v_have_slices); if (unlikely(__pyx_t_2 < 0)) __PYX_ERR(2, 412, __pyx_L1_error)
  if (__pyx_t_2) {

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_3 = ((PyObject *)__pyx_memview_slice(__pyx_v_self, __pyx_v_indices)); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 413, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_r = __pyx_t_3;
    __pyx_t_3 = 0;
    goto __pyx_L0;

     
  }

   
    {
    __pyx_t_6 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->get_item_pointer(__pyx_v_self, __pyx_v_indices); if (unlikely(__pyx_t_6 == ((char *)NULL))) __PYX_ERR(2, 415, __pyx_L1_error)
    __pyx_v_itemp = __pyx_t_6;

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_3 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->convert_item_to_object(__pyx_v_self, __pyx_v_itemp); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 416, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_r = __pyx_t_3;
    __pyx_t_3 = 0;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__getitem__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_have_slices);
  __Pyx_XDECREF(__pyx_v_indices);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static int __pyx_memoryview___setitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value);  
static int __pyx_memoryview___setitem__(PyObject *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setitem__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_6__setitem__(((struct __pyx_memoryview_obj *)__pyx_v_self), ((PyObject *)__pyx_v_index), ((PyObject *)__pyx_v_value));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_6__setitem__(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value) {
  PyObject *__pyx_v_have_slices = NULL;
  PyObject *__pyx_v_obj = NULL;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setitem__", 0);
  __Pyx_INCREF(__pyx_v_index);

   
  __pyx_t_1 = (__pyx_v_self->view.readonly != 0);
  if (unlikely(__pyx_t_1)) {

     
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__15, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 420, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __PYX_ERR(2, 420, __pyx_L1_error)

     
  }

   
  __pyx_t_2 = _unellipsify(__pyx_v_index, __pyx_v_self->view.ndim); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 422, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (likely(__pyx_t_2 != Py_None)) {
    PyObject* sequence = __pyx_t_2;
    Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(2, 422, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_3 = PyTuple_GET_ITEM(sequence, 0); 
    __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
    __Pyx_INCREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_t_4);
    #else
    __pyx_t_3 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 422, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 422, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    #endif
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __Pyx_RaiseNoneNotIterableError(); __PYX_ERR(2, 422, __pyx_L1_error)
  }
  __pyx_v_have_slices = __pyx_t_3;
  __pyx_t_3 = 0;
  __Pyx_DECREF_SET(__pyx_v_index, __pyx_t_4);
  __pyx_t_4 = 0;

   
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_have_slices); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 424, __pyx_L1_error)
  if (__pyx_t_1) {

     
    __pyx_t_2 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->is_slice(__pyx_v_self, __pyx_v_value); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 425, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_v_obj = __pyx_t_2;
    __pyx_t_2 = 0;

     
    __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_obj); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 426, __pyx_L1_error)
    if (__pyx_t_1) {

       
      __pyx_t_2 = __Pyx_PyObject_GetItem(((PyObject *)__pyx_v_self), __pyx_v_index); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 427, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_4 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->setitem_slice_assignment(__pyx_v_self, __pyx_t_2, __pyx_v_obj); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 427, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

       
      goto __pyx_L5;
    }

     
      {
      __pyx_t_4 = __Pyx_PyObject_GetItem(((PyObject *)__pyx_v_self), __pyx_v_index); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 429, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (!(likely(((__pyx_t_4) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_4, __pyx_memoryview_type))))) __PYX_ERR(2, 429, __pyx_L1_error)
      __pyx_t_2 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->setitem_slice_assign_scalar(__pyx_v_self, ((struct __pyx_memoryview_obj *)__pyx_t_4), __pyx_v_value); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 429, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
    __pyx_L5:;

     
    goto __pyx_L4;
  }

   
    {
    __pyx_t_2 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->setitem_indexed(__pyx_v_self, __pyx_v_index, __pyx_v_value); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 431, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __pyx_L4:;

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__setitem__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_have_slices);
  __Pyx_XDECREF(__pyx_v_obj);
  __Pyx_XDECREF(__pyx_v_index);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_is_slice(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_obj) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_t_9;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("is_slice", 0);
  __Pyx_INCREF(__pyx_v_obj);

   
  __pyx_t_1 = __Pyx_TypeCheck(__pyx_v_obj, __pyx_memoryview_type); 
  __pyx_t_2 = ((!(__pyx_t_1 != 0)) != 0);
  if (__pyx_t_2) {

     
    {
      __Pyx_PyThreadState_declare
      __Pyx_PyThreadState_assign
      __Pyx_ExceptionSave(&__pyx_t_3, &__pyx_t_4, &__pyx_t_5);
      __Pyx_XGOTREF(__pyx_t_3);
      __Pyx_XGOTREF(__pyx_t_4);
      __Pyx_XGOTREF(__pyx_t_5);
        {

         
        __pyx_t_6 = __Pyx_PyInt_From_int(((__pyx_v_self->flags & (~PyBUF_WRITABLE)) | PyBUF_ANY_CONTIGUOUS)); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 436, __pyx_L4_error)
        __Pyx_GOTREF(__pyx_t_6);

         
        __pyx_t_7 = __Pyx_PyBool_FromLong(__pyx_v_self->dtype_is_object); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 437, __pyx_L4_error)
        __Pyx_GOTREF(__pyx_t_7);

         
        __pyx_t_8 = PyTuple_New(3); if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 436, __pyx_L4_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_INCREF(__pyx_v_obj);
        __Pyx_GIVEREF(__pyx_v_obj);
        PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_v_obj);
        __Pyx_GIVEREF(__pyx_t_6);
        PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_7);
        PyTuple_SET_ITEM(__pyx_t_8, 2, __pyx_t_7);
        __pyx_t_6 = 0;
        __pyx_t_7 = 0;
        __pyx_t_7 = __Pyx_PyObject_Call(((PyObject *)__pyx_memoryview_type), __pyx_t_8, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 436, __pyx_L4_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        __Pyx_DECREF_SET(__pyx_v_obj, __pyx_t_7);
        __pyx_t_7 = 0;

         
      }
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      goto __pyx_L9_try_end;
      __pyx_L4_error:;
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;

       
      __pyx_t_9 = __Pyx_PyErr_ExceptionMatches(__pyx_builtin_TypeError);
      if (__pyx_t_9) {
        __Pyx_AddTraceback("View.MemoryView.memoryview.is_slice", __pyx_clineno, __pyx_lineno, __pyx_filename);
        if (__Pyx_GetException(&__pyx_t_7, &__pyx_t_8, &__pyx_t_6) < 0) __PYX_ERR(2, 438, __pyx_L6_except_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_GOTREF(__pyx_t_6);

         
        __Pyx_XDECREF(__pyx_r);
        __pyx_r = Py_None; __Pyx_INCREF(Py_None);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
        goto __pyx_L7_except_return;
      }
      goto __pyx_L6_except_error;
      __pyx_L6_except_error:;

       
      __Pyx_XGIVEREF(__pyx_t_3);
      __Pyx_XGIVEREF(__pyx_t_4);
      __Pyx_XGIVEREF(__pyx_t_5);
      __Pyx_ExceptionReset(__pyx_t_3, __pyx_t_4, __pyx_t_5);
      goto __pyx_L1_error;
      __pyx_L7_except_return:;
      __Pyx_XGIVEREF(__pyx_t_3);
      __Pyx_XGIVEREF(__pyx_t_4);
      __Pyx_XGIVEREF(__pyx_t_5);
      __Pyx_ExceptionReset(__pyx_t_3, __pyx_t_4, __pyx_t_5);
      goto __pyx_L0;
      __pyx_L9_try_end:;
    }

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_obj);
  __pyx_r = __pyx_v_obj;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("View.MemoryView.memoryview.is_slice", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_obj);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_setitem_slice_assignment(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_dst, PyObject *__pyx_v_src) {
  __Pyx_memviewslice __pyx_v_dst_slice;
  __Pyx_memviewslice __pyx_v_src_slice;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice *__pyx_t_1;
  __Pyx_memviewslice *__pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("setitem_slice_assignment", 0);

   
  if (!(likely(((__pyx_v_src) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_src, __pyx_memoryview_type))))) __PYX_ERR(2, 447, __pyx_L1_error)
  __pyx_t_1 = __pyx_memoryview_get_slice_from_memoryview(((struct __pyx_memoryview_obj *)__pyx_v_src), (&__pyx_v_src_slice)); if (unlikely(__pyx_t_1 == ((__Pyx_memviewslice *)NULL))) __PYX_ERR(2, 447, __pyx_L1_error)

   
  if (!(likely(((__pyx_v_dst) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_dst, __pyx_memoryview_type))))) __PYX_ERR(2, 448, __pyx_L1_error)
  __pyx_t_2 = __pyx_memoryview_get_slice_from_memoryview(((struct __pyx_memoryview_obj *)__pyx_v_dst), (&__pyx_v_dst_slice)); if (unlikely(__pyx_t_2 == ((__Pyx_memviewslice *)NULL))) __PYX_ERR(2, 448, __pyx_L1_error)

   
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_src, __pyx_n_s_ndim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 449, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyInt_As_int(__pyx_t_3); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 449, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_dst, __pyx_n_s_ndim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 449, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_PyInt_As_int(__pyx_t_3); if (unlikely((__pyx_t_5 == (int)-1) && PyErr_Occurred())) __PYX_ERR(2, 449, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

   
  __pyx_t_6 = __pyx_memoryview_copy_contents((__pyx_t_1[0]), (__pyx_t_2[0]), __pyx_t_4, __pyx_t_5, __pyx_v_self->dtype_is_object); if (unlikely(__pyx_t_6 == ((int)-1))) __PYX_ERR(2, 447, __pyx_L1_error)

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.setitem_slice_assignment", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_setitem_slice_assign_scalar(struct __pyx_memoryview_obj *__pyx_v_self, struct __pyx_memoryview_obj *__pyx_v_dst, PyObject *__pyx_v_value) {
  int __pyx_v_array[0x80];
  void *__pyx_v_tmp;
  void *__pyx_v_item;
  __Pyx_memviewslice *__pyx_v_dst_slice;
  __Pyx_memviewslice __pyx_v_tmp_slice;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice *__pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  char const *__pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("setitem_slice_assign_scalar", 0);

   
  __pyx_v_tmp = NULL;

   
  __pyx_t_1 = __pyx_memoryview_get_slice_from_memoryview(__pyx_v_dst, (&__pyx_v_tmp_slice)); if (unlikely(__pyx_t_1 == ((__Pyx_memviewslice *)NULL))) __PYX_ERR(2, 458, __pyx_L1_error)
  __pyx_v_dst_slice = __pyx_t_1;

   
  __pyx_t_2 = ((((size_t)__pyx_v_self->view.itemsize) > (sizeof(__pyx_v_array))) != 0);
  if (__pyx_t_2) {

     
    __pyx_v_tmp = PyMem_Malloc(__pyx_v_self->view.itemsize);

     
    __pyx_t_2 = ((__pyx_v_tmp == NULL) != 0);
    if (unlikely(__pyx_t_2)) {

       
      PyErr_NoMemory(); __PYX_ERR(2, 463, __pyx_L1_error)

       
    }

     
    __pyx_v_item = __pyx_v_tmp;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_v_item = ((void *)__pyx_v_array);
  }
  __pyx_L3:;

   
    {

     
    __pyx_t_2 = (__pyx_v_self->dtype_is_object != 0);
    if (__pyx_t_2) {

       
      (((PyObject **)__pyx_v_item)[0]) = ((PyObject *)__pyx_v_value);

       
      goto __pyx_L8;
    }

     
      {
      __pyx_t_3 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->assign_item_from_object(__pyx_v_self, ((char *)__pyx_v_item), __pyx_v_value); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 472, __pyx_L6_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __pyx_L8:;

     
    __pyx_t_2 = ((__pyx_v_self->view.suboffsets != NULL) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_3 = assert_direct_dimensions(__pyx_v_self->view.suboffsets, __pyx_v_self->view.ndim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 477, __pyx_L6_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

       
    }

     
    __pyx_memoryview_slice_assign_scalar(__pyx_v_dst_slice, __pyx_v_dst->view.ndim, __pyx_v_self->view.itemsize, __pyx_v_item, __pyx_v_self->dtype_is_object);
  }

   
    {
     {
      PyMem_Free(__pyx_v_tmp);
      goto __pyx_L7;
    }
    __pyx_L6_error:;
     {
      __Pyx_PyThreadState_declare
      __Pyx_PyThreadState_assign
      __pyx_t_7 = 0; __pyx_t_8 = 0; __pyx_t_9 = 0; __pyx_t_10 = 0; __pyx_t_11 = 0; __pyx_t_12 = 0;
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (PY_MAJOR_VERSION >= 3) __Pyx_ExceptionSwap(&__pyx_t_10, &__pyx_t_11, &__pyx_t_12);
      if ((PY_MAJOR_VERSION < 3) || unlikely(__Pyx_GetException(&__pyx_t_7, &__pyx_t_8, &__pyx_t_9) < 0)) __Pyx_ErrFetch(&__pyx_t_7, &__pyx_t_8, &__pyx_t_9);
      __Pyx_XGOTREF(__pyx_t_7);
      __Pyx_XGOTREF(__pyx_t_8);
      __Pyx_XGOTREF(__pyx_t_9);
      __Pyx_XGOTREF(__pyx_t_10);
      __Pyx_XGOTREF(__pyx_t_11);
      __Pyx_XGOTREF(__pyx_t_12);
      __pyx_t_4 = __pyx_lineno; __pyx_t_5 = __pyx_clineno; __pyx_t_6 = __pyx_filename;
      {
        PyMem_Free(__pyx_v_tmp);
      }
      if (PY_MAJOR_VERSION >= 3) {
        __Pyx_XGIVEREF(__pyx_t_10);
        __Pyx_XGIVEREF(__pyx_t_11);
        __Pyx_XGIVEREF(__pyx_t_12);
        __Pyx_ExceptionReset(__pyx_t_10, __pyx_t_11, __pyx_t_12);
      }
      __Pyx_XGIVEREF(__pyx_t_7);
      __Pyx_XGIVEREF(__pyx_t_8);
      __Pyx_XGIVEREF(__pyx_t_9);
      __Pyx_ErrRestore(__pyx_t_7, __pyx_t_8, __pyx_t_9);
      __pyx_t_7 = 0; __pyx_t_8 = 0; __pyx_t_9 = 0; __pyx_t_10 = 0; __pyx_t_11 = 0; __pyx_t_12 = 0;
      __pyx_lineno = __pyx_t_4; __pyx_clineno = __pyx_t_5; __pyx_filename = __pyx_t_6;
      goto __pyx_L1_error;
    }
    __pyx_L7:;
  }

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.setitem_slice_assign_scalar", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_setitem_indexed(struct __pyx_memoryview_obj *__pyx_v_self, PyObject *__pyx_v_index, PyObject *__pyx_v_value) {
  char *__pyx_v_itemp;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  char *__pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("setitem_indexed", 0);

   
  __pyx_t_1 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->get_item_pointer(__pyx_v_self, __pyx_v_index); if (unlikely(__pyx_t_1 == ((char *)NULL))) __PYX_ERR(2, 484, __pyx_L1_error)
  __pyx_v_itemp = __pyx_t_1;

   
  __pyx_t_2 = ((struct __pyx_vtabstruct_memoryview *)__pyx_v_self->__pyx_vtab)->assign_item_from_object(__pyx_v_self, __pyx_v_itemp, __pyx_v_value); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 485, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.setitem_indexed", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_convert_item_to_object(struct __pyx_memoryview_obj *__pyx_v_self, char *__pyx_v_itemp) {
  PyObject *__pyx_v_struct = NULL;
  PyObject *__pyx_v_bytesitem = 0;
  PyObject *__pyx_v_result = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  size_t __pyx_t_10;
  int __pyx_t_11;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("convert_item_to_object", 0);

   
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_struct, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 490, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_struct = __pyx_t_1;
  __pyx_t_1 = 0;

   
  __pyx_t_1 = __Pyx_PyBytes_FromStringAndSize(__pyx_v_itemp + 0, __pyx_v_self->view.itemsize - 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 493, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_bytesitem = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

   
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_2, &__pyx_t_3, &__pyx_t_4);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_4);
      {

       
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_struct, __pyx_n_s_unpack); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 495, __pyx_L3_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_6 = __Pyx_PyBytes_FromString(__pyx_v_self->view.format); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 495, __pyx_L3_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_7 = NULL;
      __pyx_t_8 = 0;
      if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_5))) {
        __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_5);
        if (likely(__pyx_t_7)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_7);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_5, function);
          __pyx_t_8 = 1;
        }
      }
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_t_6, __pyx_v_bytesitem};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 495, __pyx_L3_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_t_6, __pyx_v_bytesitem};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 495, __pyx_L3_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      {
        __pyx_t_9 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 495, __pyx_L3_error)
        __Pyx_GOTREF(__pyx_t_9);
        if (__pyx_t_7) {
          __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_7); __pyx_t_7 = NULL;
        }
        __Pyx_GIVEREF(__pyx_t_6);
        PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_t_6);
        __Pyx_INCREF(__pyx_v_bytesitem);
        __Pyx_GIVEREF(__pyx_v_bytesitem);
        PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_v_bytesitem);
        __pyx_t_6 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 495, __pyx_L3_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      }
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_v_result = __pyx_t_1;
      __pyx_t_1 = 0;

       
    }

     
      {
      __pyx_t_10 = strlen(__pyx_v_self->view.format); 
      __pyx_t_11 = ((__pyx_t_10 == 1) != 0);
      if (__pyx_t_11) {

         
        __Pyx_XDECREF(__pyx_r);
        __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_result, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 500, __pyx_L5_except_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_r = __pyx_t_1;
        __pyx_t_1 = 0;
        goto __pyx_L6_except_return;

         
      }

       
      __Pyx_XDECREF(__pyx_r);
      __Pyx_INCREF(__pyx_v_result);
      __pyx_r = __pyx_v_result;
      goto __pyx_L6_except_return;
    }
    __pyx_L3_error:;
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;

     
    __Pyx_ErrFetch(&__pyx_t_1, &__pyx_t_5, &__pyx_t_9);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_struct, __pyx_n_s_error); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 496, __pyx_L5_except_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyErr_GivenExceptionMatches(__pyx_t_1, __pyx_t_6);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_ErrRestore(__pyx_t_1, __pyx_t_5, __pyx_t_9);
    __pyx_t_1 = 0; __pyx_t_5 = 0; __pyx_t_9 = 0;
    if (__pyx_t_8) {
      __Pyx_AddTraceback("View.MemoryView.memoryview.convert_item_to_object", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_9, &__pyx_t_5, &__pyx_t_1) < 0) __PYX_ERR(2, 496, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_1);

       
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__16, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 497, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_Raise(__pyx_t_6, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __PYX_ERR(2, 497, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

     
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_ExceptionReset(__pyx_t_2, __pyx_t_3, __pyx_t_4);
    goto __pyx_L1_error;
    __pyx_L6_except_return:;
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_XGIVEREF(__pyx_t_4);
    __Pyx_ExceptionReset(__pyx_t_2, __pyx_t_3, __pyx_t_4);
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("View.MemoryView.memoryview.convert_item_to_object", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_struct);
  __Pyx_XDECREF(__pyx_v_bytesitem);
  __Pyx_XDECREF(__pyx_v_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_assign_item_from_object(struct __pyx_memoryview_obj *__pyx_v_self, char *__pyx_v_itemp, PyObject *__pyx_v_value) {
  PyObject *__pyx_v_struct = NULL;
  char __pyx_v_c;
  PyObject *__pyx_v_bytesvalue = 0;
  Py_ssize_t __pyx_v_i;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  PyObject *__pyx_t_8 = NULL;
  Py_ssize_t __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  char *__pyx_t_11;
  char *__pyx_t_12;
  char *__pyx_t_13;
  char *__pyx_t_14;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("assign_item_from_object", 0);

   
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_struct, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 506, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_struct = __pyx_t_1;
  __pyx_t_1 = 0;

   
  __pyx_t_2 = PyTuple_Check(__pyx_v_value); 
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (__pyx_t_3) {

     
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_struct, __pyx_n_s_pack); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = __Pyx_PyBytes_FromString(__pyx_v_self->view.format); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = PyTuple_New(1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PySequence_Tuple(__pyx_v_value); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_6 = PyNumber_Add(__pyx_t_5, __pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_6, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 512, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (!(likely(PyBytes_CheckExact(__pyx_t_4))||((__pyx_t_4) == Py_None)||((void)PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "bytes", Py_TYPE(__pyx_t_4)->tp_name), 0))) __PYX_ERR(2, 512, __pyx_L1_error)
    __pyx_v_bytesvalue = ((PyObject*)__pyx_t_4);
    __pyx_t_4 = 0;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_struct, __pyx_n_s_pack); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 514, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_1 = __Pyx_PyBytes_FromString(__pyx_v_self->view.format); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 514, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = NULL;
    __pyx_t_7 = 0;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
        __pyx_t_7 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_6)) {
      PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_t_1, __pyx_v_value};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp+1-__pyx_t_7, 2+__pyx_t_7); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 514, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
      PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_t_1, __pyx_v_value};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp+1-__pyx_t_7, 2+__pyx_t_7); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 514, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else
    #endif
    {
      __pyx_t_8 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 514, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      if (__pyx_t_5) {
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_5); __pyx_t_5 = NULL;
      }
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_8, 0+__pyx_t_7, __pyx_t_1);
      __Pyx_INCREF(__pyx_v_value);
      __Pyx_GIVEREF(__pyx_v_value);
      PyTuple_SET_ITEM(__pyx_t_8, 1+__pyx_t_7, __pyx_v_value);
      __pyx_t_1 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_8, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 514, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (!(likely(PyBytes_CheckExact(__pyx_t_4))||((__pyx_t_4) == Py_None)||((void)PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "bytes", Py_TYPE(__pyx_t_4)->tp_name), 0))) __PYX_ERR(2, 514, __pyx_L1_error)
    __pyx_v_bytesvalue = ((PyObject*)__pyx_t_4);
    __pyx_t_4 = 0;
  }
  __pyx_L3:;

   
  __pyx_t_9 = 0;
  if (unlikely(__pyx_v_bytesvalue == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' is not iterable");
    __PYX_ERR(2, 516, __pyx_L1_error)
  }
  __Pyx_INCREF(__pyx_v_bytesvalue);
  __pyx_t_10 = __pyx_v_bytesvalue;
  __pyx_t_12 = PyBytes_AS_STRING(__pyx_t_10);
  __pyx_t_13 = (__pyx_t_12 + PyBytes_GET_SIZE(__pyx_t_10));
  for (__pyx_t_14 = __pyx_t_12; __pyx_t_14 < __pyx_t_13; __pyx_t_14++) {
    __pyx_t_11 = __pyx_t_14;
    __pyx_v_c = (__pyx_t_11[0]);

     
    __pyx_v_i = __pyx_t_9;

     
    __pyx_t_9 = (__pyx_t_9 + 1);

     
    (__pyx_v_itemp[__pyx_v_i]) = __pyx_v_c;
  }
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("View.MemoryView.memoryview.assign_item_from_object", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_struct);
  __Pyx_XDECREF(__pyx_v_bytesvalue);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static CYTHON_UNUSED int __pyx_memoryview_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags);  
static CYTHON_UNUSED int __pyx_memoryview_getbuffer(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getbuffer__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_8__getbuffer__(((struct __pyx_memoryview_obj *)__pyx_v_self), ((Py_buffer *)__pyx_v_info), ((int)__pyx_v_flags));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_8__getbuffer__(struct __pyx_memoryview_obj *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t *__pyx_t_4;
  char *__pyx_t_5;
  void *__pyx_t_6;
  int __pyx_t_7;
  Py_ssize_t __pyx_t_8;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  if (__pyx_v_info == NULL) {
    PyErr_SetString(PyExc_BufferError, "PyObject_GetBuffer: view==NULL argument is obsolete");
    return -1;
  }
  __Pyx_RefNannySetupContext("__getbuffer__", 0);
  __pyx_v_info->obj = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(__pyx_v_info->obj);

   
  __pyx_t_2 = ((__pyx_v_flags & PyBUF_WRITABLE) != 0);
  if (__pyx_t_2) {
  } else {
    __pyx_t_1 = __pyx_t_2;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_2 = (__pyx_v_self->view.readonly != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L4_bool_binop_done:;
  if (unlikely(__pyx_t_1)) {

     
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__17, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 522, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 522, __pyx_L1_error)

     
  }

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_ND) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_4 = __pyx_v_self->view.shape;
    __pyx_v_info->shape = __pyx_t_4;

     
    goto __pyx_L6;
  }

   
    {
    __pyx_v_info->shape = NULL;
  }
  __pyx_L6:;

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_STRIDES) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_4 = __pyx_v_self->view.strides;
    __pyx_v_info->strides = __pyx_t_4;

     
    goto __pyx_L7;
  }

   
    {
    __pyx_v_info->strides = NULL;
  }
  __pyx_L7:;

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_INDIRECT) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_4 = __pyx_v_self->view.suboffsets;
    __pyx_v_info->suboffsets = __pyx_t_4;

     
    goto __pyx_L8;
  }

   
    {
    __pyx_v_info->suboffsets = NULL;
  }
  __pyx_L8:;

   
  __pyx_t_1 = ((__pyx_v_flags & PyBUF_FORMAT) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_5 = __pyx_v_self->view.format;
    __pyx_v_info->format = __pyx_t_5;

     
    goto __pyx_L9;
  }

   
    {
    __pyx_v_info->format = NULL;
  }
  __pyx_L9:;

   
  __pyx_t_6 = __pyx_v_self->view.buf;
  __pyx_v_info->buf = __pyx_t_6;

   
  __pyx_t_7 = __pyx_v_self->view.ndim;
  __pyx_v_info->ndim = __pyx_t_7;

   
  __pyx_t_8 = __pyx_v_self->view.itemsize;
  __pyx_v_info->itemsize = __pyx_t_8;

   
  __pyx_t_8 = __pyx_v_self->view.len;
  __pyx_v_info->len = __pyx_t_8;

   
  __pyx_t_1 = __pyx_v_self->view.readonly;
  __pyx_v_info->readonly = __pyx_t_1;

   
  __Pyx_INCREF(((PyObject *)__pyx_v_self));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
  __Pyx_GOTREF(__pyx_v_info->obj);
  __Pyx_DECREF(__pyx_v_info->obj);
  __pyx_v_info->obj = ((PyObject *)__pyx_v_self);

   

   
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__getbuffer__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  if (__pyx_v_info->obj != NULL) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = 0;
  }
  goto __pyx_L2;
  __pyx_L0:;
  if (__pyx_v_info->obj == Py_None) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = 0;
  }
  __pyx_L2:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_1T_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_1T_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_1T___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_1T___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  struct __pyx_memoryviewslice_obj *__pyx_v_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __pyx_t_1 = __pyx_memoryview_copy_object(__pyx_v_self); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 556, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_memoryviewslice_type))))) __PYX_ERR(2, 556, __pyx_L1_error)
  __pyx_v_result = ((struct __pyx_memoryviewslice_obj *)__pyx_t_1);
  __pyx_t_1 = 0;

   
  __pyx_t_2 = __pyx_memslice_transpose((&__pyx_v_result->from_slice)); if (unlikely(__pyx_t_2 == ((int)0))) __PYX_ERR(2, 557, __pyx_L1_error)

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_result));
  __pyx_r = ((PyObject *)__pyx_v_result);
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview.T.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4base_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4base_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_4base___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4base___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->obj);
  __pyx_r = __pyx_v_self->obj;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_5shape_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_5shape_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_5shape___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_5shape___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  Py_ssize_t __pyx_v_length;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t *__pyx_t_2;
  Py_ssize_t *__pyx_t_3;
  Py_ssize_t *__pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 566, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = (__pyx_v_self->view.shape + __pyx_v_self->view.ndim);
  for (__pyx_t_4 = __pyx_v_self->view.shape; __pyx_t_4 < __pyx_t_3; __pyx_t_4++) {
    __pyx_t_2 = __pyx_t_4;
    __pyx_v_length = (__pyx_t_2[0]);
    __pyx_t_5 = PyInt_FromSsize_t(__pyx_v_length); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 566, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_1, (PyObject*)__pyx_t_5))) __PYX_ERR(2, 566, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __pyx_t_5 = PyList_AsTuple(((PyObject*)__pyx_t_1)); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 566, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_r = __pyx_t_5;
  __pyx_t_5 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.memoryview.shape.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_7strides_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_7strides_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_7strides___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_7strides___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  Py_ssize_t __pyx_v_stride;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t *__pyx_t_3;
  Py_ssize_t *__pyx_t_4;
  Py_ssize_t *__pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __pyx_t_1 = ((__pyx_v_self->view.strides == NULL) != 0);
  if (unlikely(__pyx_t_1)) {

     
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__18, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 572, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __PYX_ERR(2, 572, __pyx_L1_error)

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 574, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = (__pyx_v_self->view.strides + __pyx_v_self->view.ndim);
  for (__pyx_t_5 = __pyx_v_self->view.strides; __pyx_t_5 < __pyx_t_4; __pyx_t_5++) {
    __pyx_t_3 = __pyx_t_5;
    __pyx_v_stride = (__pyx_t_3[0]);
    __pyx_t_6 = PyInt_FromSsize_t(__pyx_v_stride); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 574, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_2, (PyObject*)__pyx_t_6))) __PYX_ERR(2, 574, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  }
  __pyx_t_6 = PyList_AsTuple(((PyObject*)__pyx_t_2)); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 574, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_6;
  __pyx_t_6 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("View.MemoryView.memoryview.strides.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_10suboffsets_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_10suboffsets_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_10suboffsets___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_10suboffsets___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  Py_ssize_t __pyx_v_suboffset;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t *__pyx_t_4;
  Py_ssize_t *__pyx_t_5;
  Py_ssize_t *__pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __pyx_t_1 = ((__pyx_v_self->view.suboffsets == NULL) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_self->view.ndim); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 579, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyNumber_Multiply(__pyx_tuple__19, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 579, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_r = __pyx_t_3;
    __pyx_t_3 = 0;
    goto __pyx_L0;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 581, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = (__pyx_v_self->view.suboffsets + __pyx_v_self->view.ndim);
  for (__pyx_t_6 = __pyx_v_self->view.suboffsets; __pyx_t_6 < __pyx_t_5; __pyx_t_6++) {
    __pyx_t_4 = __pyx_t_6;
    __pyx_v_suboffset = (__pyx_t_4[0]);
    __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_suboffset); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 581, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_3, (PyObject*)__pyx_t_2))) __PYX_ERR(2, 581, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __pyx_t_2 = PyList_AsTuple(((PyObject*)__pyx_t_3)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 581, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.suboffsets.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4ndim_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4ndim_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_4ndim___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4ndim___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_self->view.ndim); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 585, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview.ndim.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_8itemsize_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_8itemsize_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_8itemsize___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_8itemsize___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyInt_FromSsize_t(__pyx_v_self->view.itemsize); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 589, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview.itemsize.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_6nbytes_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_6nbytes_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_6nbytes___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_6nbytes___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_size); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 593, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_self->view.itemsize); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 593, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyNumber_Multiply(__pyx_t_1, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 593, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.nbytes.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4size_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_10memoryview_4size_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_10memoryview_4size___get__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_10memoryview_4size___get__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_v_result = NULL;
  PyObject *__pyx_v_length = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  Py_ssize_t *__pyx_t_3;
  Py_ssize_t *__pyx_t_4;
  Py_ssize_t *__pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __pyx_t_1 = (__pyx_v_self->_size == Py_None);
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __Pyx_INCREF(__pyx_int_1);
    __pyx_v_result = __pyx_int_1;

     
    __pyx_t_4 = (__pyx_v_self->view.shape + __pyx_v_self->view.ndim);
    for (__pyx_t_5 = __pyx_v_self->view.shape; __pyx_t_5 < __pyx_t_4; __pyx_t_5++) {
      __pyx_t_3 = __pyx_t_5;
      __pyx_t_6 = PyInt_FromSsize_t((__pyx_t_3[0])); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 600, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_XDECREF_SET(__pyx_v_length, __pyx_t_6);
      __pyx_t_6 = 0;

       
      __pyx_t_6 = PyNumber_InPlaceMultiply(__pyx_v_result, __pyx_v_length); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 601, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF_SET(__pyx_v_result, __pyx_t_6);
      __pyx_t_6 = 0;
    }

     
    __Pyx_INCREF(__pyx_v_result);
    __Pyx_GIVEREF(__pyx_v_result);
    __Pyx_GOTREF(__pyx_v_self->_size);
    __Pyx_DECREF(__pyx_v_self->_size);
    __pyx_v_self->_size = __pyx_v_result;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->_size);
  __pyx_r = __pyx_v_self->_size;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("View.MemoryView.memoryview.size.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_result);
  __Pyx_XDECREF(__pyx_v_length);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static Py_ssize_t __pyx_memoryview___len__(PyObject *__pyx_v_self);  
static Py_ssize_t __pyx_memoryview___len__(PyObject *__pyx_v_self) {
  Py_ssize_t __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__len__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_10__len__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static Py_ssize_t __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_10__len__(struct __pyx_memoryview_obj *__pyx_v_self) {
  Py_ssize_t __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__len__", 0);

   
  __pyx_t_1 = ((__pyx_v_self->view.ndim >= 1) != 0);
  if (__pyx_t_1) {

     
    __pyx_r = (__pyx_v_self->view.shape[0]);
    goto __pyx_L0;

     
  }

   
  __pyx_r = 0;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview___repr__(PyObject *__pyx_v_self);  
static PyObject *__pyx_memoryview___repr__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__repr__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_12__repr__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_12__repr__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__repr__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_base); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 614, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_class); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 614, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_name_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 614, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

   
  __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_builtin_id, ((PyObject *)__pyx_v_self)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 615, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);

   
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 614, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_2);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyString_Format(__pyx_kp_s_MemoryView_of_r_at_0x_x, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 614, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__repr__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview___str__(PyObject *__pyx_v_self);  
static PyObject *__pyx_memoryview___str__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__str__ (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_14__str__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_14__str__(struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__str__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_self), __pyx_n_s_base); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 618, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_class); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 618, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_name_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 618, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 618, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyString_Format(__pyx_kp_s_MemoryView_of_r_object, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 618, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__str__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview_is_c_contig(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_memoryview_is_c_contig(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("is_c_contig (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_16is_c_contig(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_16is_c_contig(struct __pyx_memoryview_obj *__pyx_v_self) {
  __Pyx_memviewslice *__pyx_v_mslice;
  __Pyx_memviewslice __pyx_v_tmp;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice *__pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("is_c_contig", 0);

   
  __pyx_t_1 = __pyx_memoryview_get_slice_from_memoryview(__pyx_v_self, (&__pyx_v_tmp)); if (unlikely(__pyx_t_1 == ((__Pyx_memviewslice *)NULL))) __PYX_ERR(2, 624, __pyx_L1_error)
  __pyx_v_mslice = __pyx_t_1;

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_memviewslice_is_contig((__pyx_v_mslice[0]), 'C', __pyx_v_self->view.ndim)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 625, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.is_c_contig", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview_is_f_contig(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_memoryview_is_f_contig(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("is_f_contig (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_18is_f_contig(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_18is_f_contig(struct __pyx_memoryview_obj *__pyx_v_self) {
  __Pyx_memviewslice *__pyx_v_mslice;
  __Pyx_memviewslice __pyx_v_tmp;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice *__pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("is_f_contig", 0);

   
  __pyx_t_1 = __pyx_memoryview_get_slice_from_memoryview(__pyx_v_self, (&__pyx_v_tmp)); if (unlikely(__pyx_t_1 == ((__Pyx_memviewslice *)NULL))) __PYX_ERR(2, 630, __pyx_L1_error)
  __pyx_v_mslice = __pyx_t_1;

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_memviewslice_is_contig((__pyx_v_mslice[0]), 'F', __pyx_v_self->view.ndim)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 631, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.is_f_contig", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview_copy(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_memoryview_copy(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("copy (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_20copy(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_20copy(struct __pyx_memoryview_obj *__pyx_v_self) {
  __Pyx_memviewslice __pyx_v_mslice;
  int __pyx_v_flags;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("copy", 0);

   
  __pyx_v_flags = (__pyx_v_self->flags & (~PyBUF_F_CONTIGUOUS));

   
  __pyx_memoryview_slice_copy(__pyx_v_self, (&__pyx_v_mslice));

   
  __pyx_t_1 = __pyx_memoryview_copy_new_contig((&__pyx_v_mslice), ((char *)"c"), __pyx_v_self->view.ndim, __pyx_v_self->view.itemsize, (__pyx_v_flags | PyBUF_C_CONTIGUOUS), __pyx_v_self->dtype_is_object); if (unlikely(PyErr_Occurred())) __PYX_ERR(2, 638, __pyx_L1_error)
  __pyx_v_mslice = __pyx_t_1;

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __pyx_memoryview_copy_object_from_slice(__pyx_v_self, (&__pyx_v_mslice)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 643, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.copy", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_memoryview_copy_fortran(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_memoryview_copy_fortran(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("copy_fortran (wrapper)", 0);
  __pyx_r = __pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_22copy_fortran(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_memoryview___pyx_pf_15View_dot_MemoryView_10memoryview_22copy_fortran(struct __pyx_memoryview_obj *__pyx_v_self) {
  __Pyx_memviewslice __pyx_v_src;
  __Pyx_memviewslice __pyx_v_dst;
  int __pyx_v_flags;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_memviewslice __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("copy_fortran", 0);

   
  __pyx_v_flags = (__pyx_v_self->flags & (~PyBUF_C_CONTIGUOUS));

   
  __pyx_memoryview_slice_copy(__pyx_v_self, (&__pyx_v_src));

   
  __pyx_t_1 = __pyx_memoryview_copy_new_contig((&__pyx_v_src), ((char *)"fortran"), __pyx_v_self->view.ndim, __pyx_v_self->view.itemsize, (__pyx_v_flags | PyBUF_F_CONTIGUOUS), __pyx_v_self->dtype_is_object); if (unlikely(PyErr_Occurred())) __PYX_ERR(2, 650, __pyx_L1_error)
  __pyx_v_dst = __pyx_t_1;

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __pyx_memoryview_copy_object_from_slice(__pyx_v_self, (&__pyx_v_dst)); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 655, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView.memoryview.copy_fortran", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_memoryview_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_pw___pyx_memoryview_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_memoryview___reduce_cython__(((struct __pyx_memoryview_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_memoryview___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__20, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 2, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_memoryview_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_pw___pyx_memoryview_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_memoryview_2__setstate_cython__(((struct __pyx_memoryview_obj *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_memoryview_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryview_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__21, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 4, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_new(PyObject *__pyx_v_o, int __pyx_v_flags, int __pyx_v_dtype_is_object, __Pyx_TypeInfo *__pyx_v_typeinfo) {
  struct __pyx_memoryview_obj *__pyx_v_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("memoryview_cwrapper", 0);

   
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_flags); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 660, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_v_dtype_is_object); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 660, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 660, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_v_o);
  __Pyx_GIVEREF(__pyx_v_o);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_o);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_t_2);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(((PyObject *)__pyx_memoryview_type), __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 660, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_result = ((struct __pyx_memoryview_obj *)__pyx_t_2);
  __pyx_t_2 = 0;

   
  __pyx_v_result->typeinfo = __pyx_v_typeinfo;

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_result));
  __pyx_r = ((PyObject *)__pyx_v_result);
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview_cwrapper", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static CYTHON_INLINE int __pyx_memoryview_check(PyObject *__pyx_v_o) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("memoryview_check", 0);

   
  __pyx_t_1 = __Pyx_TypeCheck(__pyx_v_o, __pyx_memoryview_type); 
  __pyx_r = __pyx_t_1;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *_unellipsify(PyObject *__pyx_v_index, int __pyx_v_ndim) {
  PyObject *__pyx_v_tup = NULL;
  PyObject *__pyx_v_result = NULL;
  int __pyx_v_have_slices;
  int __pyx_v_seen_ellipsis;
  CYTHON_UNUSED PyObject *__pyx_v_idx = NULL;
  PyObject *__pyx_v_item = NULL;
  Py_ssize_t __pyx_v_nslices;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  Py_ssize_t __pyx_t_5;
  PyObject *(*__pyx_t_6)(PyObject *);
  PyObject *__pyx_t_7 = NULL;
  Py_ssize_t __pyx_t_8;
  int __pyx_t_9;
  int __pyx_t_10;
  PyObject *__pyx_t_11 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("_unellipsify", 0);

   
  __pyx_t_1 = PyTuple_Check(__pyx_v_index); 
  __pyx_t_2 = ((!(__pyx_t_1 != 0)) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 674, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_v_index);
    __Pyx_GIVEREF(__pyx_v_index);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_index);
    __pyx_v_tup = __pyx_t_3;
    __pyx_t_3 = 0;

     
    goto __pyx_L3;
  }

   
    {
    __Pyx_INCREF(__pyx_v_index);
    __pyx_v_tup = __pyx_v_index;
  }
  __pyx_L3:;

   
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 678, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_result = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

   
  __pyx_v_have_slices = 0;

   
  __pyx_v_seen_ellipsis = 0;

   
  __Pyx_INCREF(__pyx_int_0);
  __pyx_t_3 = __pyx_int_0;
  if (likely(PyList_CheckExact(__pyx_v_tup)) || PyTuple_CheckExact(__pyx_v_tup)) {
    __pyx_t_4 = __pyx_v_tup; __Pyx_INCREF(__pyx_t_4); __pyx_t_5 = 0;
    __pyx_t_6 = NULL;
  } else {
    __pyx_t_5 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_v_tup); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 681, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_6 = Py_TYPE(__pyx_t_4)->tp_iternext; if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 681, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_6)) {
      if (likely(PyList_CheckExact(__pyx_t_4))) {
        if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_4)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_7 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_5); __Pyx_INCREF(__pyx_t_7); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 681, __pyx_L1_error)
        #else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_4, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 681, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
      } else {
        if (__pyx_t_5 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_7 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_5); __Pyx_INCREF(__pyx_t_7); __pyx_t_5++; if (unlikely(0 < 0)) __PYX_ERR(2, 681, __pyx_L1_error)
        #else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_4, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 681, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        #endif
      }
    } else {
      __pyx_t_7 = __pyx_t_6(__pyx_t_4);
      if (unlikely(!__pyx_t_7)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(2, 681, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_7);
    }
    __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_7);
    __pyx_t_7 = 0;
    __Pyx_INCREF(__pyx_t_3);
    __Pyx_XDECREF_SET(__pyx_v_idx, __pyx_t_3);
    __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_t_3, __pyx_int_1, 1, 0, 0); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 681, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = __pyx_t_7;
    __pyx_t_7 = 0;

     
    __pyx_t_2 = (__pyx_v_item == __pyx_builtin_Ellipsis);
    __pyx_t_1 = (__pyx_t_2 != 0);
    if (__pyx_t_1) {

       
      __pyx_t_1 = ((!(__pyx_v_seen_ellipsis != 0)) != 0);
      if (__pyx_t_1) {

         
        __pyx_t_8 = PyObject_Length(__pyx_v_tup); if (unlikely(__pyx_t_8 == ((Py_ssize_t)-1))) __PYX_ERR(2, 684, __pyx_L1_error)
        __pyx_t_7 = PyList_New(1 * ((((__pyx_v_ndim - __pyx_t_8) + 1)<0) ? 0:((__pyx_v_ndim - __pyx_t_8) + 1))); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 684, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        { Py_ssize_t __pyx_temp;
          for (__pyx_temp=0; __pyx_temp < ((__pyx_v_ndim - __pyx_t_8) + 1); __pyx_temp++) {
            __Pyx_INCREF(__pyx_slice__22);
            __Pyx_GIVEREF(__pyx_slice__22);
            PyList_SET_ITEM(__pyx_t_7, __pyx_temp, __pyx_slice__22);
          }
        }
        __pyx_t_9 = __Pyx_PyList_Extend(__pyx_v_result, __pyx_t_7); if (unlikely(__pyx_t_9 == ((int)-1))) __PYX_ERR(2, 684, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

         
        __pyx_v_seen_ellipsis = 1;

         
        goto __pyx_L7;
      }

       
        {
        __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_result, __pyx_slice__22); if (unlikely(__pyx_t_9 == ((int)-1))) __PYX_ERR(2, 687, __pyx_L1_error)
      }
      __pyx_L7:;

       
      __pyx_v_have_slices = 1;

       
      goto __pyx_L6;
    }

     
      {
      __pyx_t_2 = PySlice_Check(__pyx_v_item); 
      __pyx_t_10 = ((!(__pyx_t_2 != 0)) != 0);
      if (__pyx_t_10) {
      } else {
        __pyx_t_1 = __pyx_t_10;
        goto __pyx_L9_bool_binop_done;
      }
      __pyx_t_10 = ((!(PyIndex_Check(__pyx_v_item) != 0)) != 0);
      __pyx_t_1 = __pyx_t_10;
      __pyx_L9_bool_binop_done:;
      if (unlikely(__pyx_t_1)) {

         
        __pyx_t_7 = __Pyx_PyString_FormatSafe(__pyx_kp_s_Cannot_index_with_type_s, ((PyObject *)Py_TYPE(__pyx_v_item))); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 691, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_11 = __Pyx_PyObject_CallOneArg(__pyx_builtin_TypeError, __pyx_t_7); if (unlikely(!__pyx_t_11)) __PYX_ERR(2, 691, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_Raise(__pyx_t_11, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
        __PYX_ERR(2, 691, __pyx_L1_error)

         
      }

       
      __pyx_t_10 = (__pyx_v_have_slices != 0);
      if (!__pyx_t_10) {
      } else {
        __pyx_t_1 = __pyx_t_10;
        goto __pyx_L11_bool_binop_done;
      }
      __pyx_t_10 = PySlice_Check(__pyx_v_item); 
      __pyx_t_2 = (__pyx_t_10 != 0);
      __pyx_t_1 = __pyx_t_2;
      __pyx_L11_bool_binop_done:;
      __pyx_v_have_slices = __pyx_t_1;

       
      __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_result, __pyx_v_item); if (unlikely(__pyx_t_9 == ((int)-1))) __PYX_ERR(2, 694, __pyx_L1_error)
    }
    __pyx_L6:;

     
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

   
  __pyx_t_5 = PyList_GET_SIZE(__pyx_v_result); if (unlikely(__pyx_t_5 == ((Py_ssize_t)-1))) __PYX_ERR(2, 696, __pyx_L1_error)
  __pyx_v_nslices = (__pyx_v_ndim - __pyx_t_5);

   
  __pyx_t_1 = (__pyx_v_nslices != 0);
  if (__pyx_t_1) {

     
    __pyx_t_3 = PyList_New(1 * ((__pyx_v_nslices<0) ? 0:__pyx_v_nslices)); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 698, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    { Py_ssize_t __pyx_temp;
      for (__pyx_temp=0; __pyx_temp < __pyx_v_nslices; __pyx_temp++) {
        __Pyx_INCREF(__pyx_slice__22);
        __Pyx_GIVEREF(__pyx_slice__22);
        PyList_SET_ITEM(__pyx_t_3, __pyx_temp, __pyx_slice__22);
      }
    }
    __pyx_t_9 = __Pyx_PyList_Extend(__pyx_v_result, __pyx_t_3); if (unlikely(__pyx_t_9 == ((int)-1))) __PYX_ERR(2, 698, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  if (!__pyx_v_have_slices) {
  } else {
    __pyx_t_4 = __Pyx_PyBool_FromLong(__pyx_v_have_slices); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 700, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_3 = __pyx_t_4;
    __pyx_t_4 = 0;
    goto __pyx_L14_bool_binop_done;
  }
  __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_nslices); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 700, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = __pyx_t_4;
  __pyx_t_4 = 0;
  __pyx_L14_bool_binop_done:;
  __pyx_t_4 = PyList_AsTuple(__pyx_v_result); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 700, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_11 = PyTuple_New(2); if (unlikely(!__pyx_t_11)) __PYX_ERR(2, 700, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_11, 1, __pyx_t_4);
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_r = ((PyObject*)__pyx_t_11);
  __pyx_t_11 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_AddTraceback("View.MemoryView._unellipsify", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_tup);
  __Pyx_XDECREF(__pyx_v_result);
  __Pyx_XDECREF(__pyx_v_idx);
  __Pyx_XDECREF(__pyx_v_item);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *assert_direct_dimensions(Py_ssize_t *__pyx_v_suboffsets, int __pyx_v_ndim) {
  Py_ssize_t __pyx_v_suboffset;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t *__pyx_t_1;
  Py_ssize_t *__pyx_t_2;
  Py_ssize_t *__pyx_t_3;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("assert_direct_dimensions", 0);

   
  __pyx_t_2 = (__pyx_v_suboffsets + __pyx_v_ndim);
  for (__pyx_t_3 = __pyx_v_suboffsets; __pyx_t_3 < __pyx_t_2; __pyx_t_3++) {
    __pyx_t_1 = __pyx_t_3;
    __pyx_v_suboffset = (__pyx_t_1[0]);

     
    __pyx_t_4 = ((__pyx_v_suboffset >= 0) != 0);
    if (unlikely(__pyx_t_4)) {

       
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__23, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 705, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_Raise(__pyx_t_5, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __PYX_ERR(2, 705, __pyx_L1_error)

       
    }
  }

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.assert_direct_dimensions", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static struct __pyx_memoryview_obj *__pyx_memview_slice(struct __pyx_memoryview_obj *__pyx_v_memview, PyObject *__pyx_v_indices) {
  int __pyx_v_new_ndim;
  int __pyx_v_suboffset_dim;
  int __pyx_v_dim;
  __Pyx_memviewslice __pyx_v_src;
  __Pyx_memviewslice __pyx_v_dst;
  __Pyx_memviewslice *__pyx_v_p_src;
  struct __pyx_memoryviewslice_obj *__pyx_v_memviewsliceobj = 0;
  __Pyx_memviewslice *__pyx_v_p_dst;
  int *__pyx_v_p_suboffset_dim;
  Py_ssize_t __pyx_v_start;
  Py_ssize_t __pyx_v_stop;
  Py_ssize_t __pyx_v_step;
  int __pyx_v_have_start;
  int __pyx_v_have_stop;
  int __pyx_v_have_step;
  PyObject *__pyx_v_index = NULL;
  struct __pyx_memoryview_obj *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  struct __pyx_memoryview_obj *__pyx_t_4;
  char *__pyx_t_5;
  int __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  PyObject *__pyx_t_9 = NULL;
  Py_ssize_t __pyx_t_10;
  int __pyx_t_11;
  Py_ssize_t __pyx_t_12;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("memview_slice", 0);

   
  __pyx_v_new_ndim = 0;
  __pyx_v_suboffset_dim = -1;

   
  (void)(memset((&__pyx_v_dst), 0, (sizeof(__pyx_v_dst))));

   
  #ifndef CYTHON_WITHOUT_ASSERTIONS
  if (unlikely(!Py_OptimizeFlag)) {
    if (unlikely(!((__pyx_v_memview->view.ndim > 0) != 0))) {
      PyErr_SetNone(PyExc_AssertionError);
      __PYX_ERR(2, 724, __pyx_L1_error)
    }
  }
  #endif

   
  __pyx_t_1 = __Pyx_TypeCheck(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type); 
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    if (!(likely(((((PyObject *)__pyx_v_memview)) == Py_None) || likely(__Pyx_TypeTest(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type))))) __PYX_ERR(2, 727, __pyx_L1_error)
    __pyx_t_3 = ((PyObject *)__pyx_v_memview);
    __Pyx_INCREF(__pyx_t_3);
    __pyx_v_memviewsliceobj = ((struct __pyx_memoryviewslice_obj *)__pyx_t_3);
    __pyx_t_3 = 0;

     
    __pyx_v_p_src = (&__pyx_v_memviewsliceobj->from_slice);

     
    goto __pyx_L3;
  }

   
    {
    __pyx_memoryview_slice_copy(__pyx_v_memview, (&__pyx_v_src));

     
    __pyx_v_p_src = (&__pyx_v_src);
  }
  __pyx_L3:;

   
  __pyx_t_4 = __pyx_v_p_src->memview;
  __pyx_v_dst.memview = __pyx_t_4;

   
  __pyx_t_5 = __pyx_v_p_src->data;
  __pyx_v_dst.data = __pyx_t_5;

   
  __pyx_v_p_dst = (&__pyx_v_dst);

   
  __pyx_v_p_suboffset_dim = (&__pyx_v_suboffset_dim);

   
  __pyx_t_6 = 0;
  if (likely(PyList_CheckExact(__pyx_v_indices)) || PyTuple_CheckExact(__pyx_v_indices)) {
    __pyx_t_3 = __pyx_v_indices; __Pyx_INCREF(__pyx_t_3); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_v_indices); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 748, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_8 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(2, 748, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_9 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_7); __Pyx_INCREF(__pyx_t_9); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(2, 748, __pyx_L1_error)
        #else
        __pyx_t_9 = PySequence_ITEM(__pyx_t_3, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 748, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_9 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_7); __Pyx_INCREF(__pyx_t_9); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(2, 748, __pyx_L1_error)
        #else
        __pyx_t_9 = PySequence_ITEM(__pyx_t_3, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 748, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        #endif
      }
    } else {
      __pyx_t_9 = __pyx_t_8(__pyx_t_3);
      if (unlikely(!__pyx_t_9)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(2, 748, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_9);
    }
    __Pyx_XDECREF_SET(__pyx_v_index, __pyx_t_9);
    __pyx_t_9 = 0;
    __pyx_v_dim = __pyx_t_6;
    __pyx_t_6 = (__pyx_t_6 + 1);

     
    __pyx_t_2 = (PyIndex_Check(__pyx_v_index) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_10 = __Pyx_PyIndex_AsSsize_t(__pyx_v_index); if (unlikely((__pyx_t_10 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 753, __pyx_L1_error)

       
      __pyx_t_11 = __pyx_memoryview_slice_memviewslice(__pyx_v_p_dst, (__pyx_v_p_src->shape[__pyx_v_dim]), (__pyx_v_p_src->strides[__pyx_v_dim]), (__pyx_v_p_src->suboffsets[__pyx_v_dim]), __pyx_v_dim, __pyx_v_new_ndim, __pyx_v_p_suboffset_dim, __pyx_t_10, 0, 0, 0, 0, 0, 0); if (unlikely(__pyx_t_11 == ((int)-1))) __PYX_ERR(2, 750, __pyx_L1_error)

       
      goto __pyx_L6;
    }

     
    __pyx_t_2 = (__pyx_v_index == Py_None);
    __pyx_t_1 = (__pyx_t_2 != 0);
    if (__pyx_t_1) {

       
      (__pyx_v_p_dst->shape[__pyx_v_new_ndim]) = 1;

       
      (__pyx_v_p_dst->strides[__pyx_v_new_ndim]) = 0;

       
      (__pyx_v_p_dst->suboffsets[__pyx_v_new_ndim]) = -1L;

       
      __pyx_v_new_ndim = (__pyx_v_new_ndim + 1);

       
      goto __pyx_L6;
    }

     
      {
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_start); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 762, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 762, __pyx_L1_error)
      if (!__pyx_t_1) {
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      } else {
        __pyx_t_12 = __Pyx_PyIndex_AsSsize_t(__pyx_t_9); if (unlikely((__pyx_t_12 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 762, __pyx_L1_error)
        __pyx_t_10 = __pyx_t_12;
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        goto __pyx_L7_bool_binop_done;
      }
      __pyx_t_10 = 0;
      __pyx_L7_bool_binop_done:;
      __pyx_v_start = __pyx_t_10;

       
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_stop); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 763, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 763, __pyx_L1_error)
      if (!__pyx_t_1) {
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      } else {
        __pyx_t_12 = __Pyx_PyIndex_AsSsize_t(__pyx_t_9); if (unlikely((__pyx_t_12 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 763, __pyx_L1_error)
        __pyx_t_10 = __pyx_t_12;
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        goto __pyx_L9_bool_binop_done;
      }
      __pyx_t_10 = 0;
      __pyx_L9_bool_binop_done:;
      __pyx_v_stop = __pyx_t_10;

       
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_step); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 764, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(2, 764, __pyx_L1_error)
      if (!__pyx_t_1) {
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      } else {
        __pyx_t_12 = __Pyx_PyIndex_AsSsize_t(__pyx_t_9); if (unlikely((__pyx_t_12 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 764, __pyx_L1_error)
        __pyx_t_10 = __pyx_t_12;
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        goto __pyx_L11_bool_binop_done;
      }
      __pyx_t_10 = 0;
      __pyx_L11_bool_binop_done:;
      __pyx_v_step = __pyx_t_10;

       
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_start); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 766, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = (__pyx_t_9 != Py_None);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __pyx_v_have_start = __pyx_t_1;

       
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_stop); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 767, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = (__pyx_t_9 != Py_None);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __pyx_v_have_stop = __pyx_t_1;

       
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_index, __pyx_n_s_step); if (unlikely(!__pyx_t_9)) __PYX_ERR(2, 768, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_1 = (__pyx_t_9 != Py_None);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __pyx_v_have_step = __pyx_t_1;

       
      __pyx_t_11 = __pyx_memoryview_slice_memviewslice(__pyx_v_p_dst, (__pyx_v_p_src->shape[__pyx_v_dim]), (__pyx_v_p_src->strides[__pyx_v_dim]), (__pyx_v_p_src->suboffsets[__pyx_v_dim]), __pyx_v_dim, __pyx_v_new_ndim, __pyx_v_p_suboffset_dim, __pyx_v_start, __pyx_v_stop, __pyx_v_step, __pyx_v_have_start, __pyx_v_have_stop, __pyx_v_have_step, 1); if (unlikely(__pyx_t_11 == ((int)-1))) __PYX_ERR(2, 770, __pyx_L1_error)

       
      __pyx_v_new_ndim = (__pyx_v_new_ndim + 1);
    }
    __pyx_L6:;

     
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

   
  __pyx_t_1 = __Pyx_TypeCheck(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type); 
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __Pyx_XDECREF(((PyObject *)__pyx_r));

     
    if (unlikely(!__pyx_v_memviewsliceobj)) { __Pyx_RaiseUnboundLocalError("memviewsliceobj"); __PYX_ERR(2, 780, __pyx_L1_error) }

     
    if (unlikely(!__pyx_v_memviewsliceobj)) { __Pyx_RaiseUnboundLocalError("memviewsliceobj"); __PYX_ERR(2, 781, __pyx_L1_error) }

     
    __pyx_t_3 = __pyx_memoryview_fromslice(__pyx_v_dst, __pyx_v_new_ndim, __pyx_v_memviewsliceobj->to_object_func, __pyx_v_memviewsliceobj->to_dtype_func, __pyx_v_memview->dtype_is_object); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 779, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_memoryview_type))))) __PYX_ERR(2, 779, __pyx_L1_error)
    __pyx_r = ((struct __pyx_memoryview_obj *)__pyx_t_3);
    __pyx_t_3 = 0;
    goto __pyx_L0;

     
  }

   
    {
    __Pyx_XDECREF(((PyObject *)__pyx_r));

     
    __pyx_t_3 = __pyx_memoryview_fromslice(__pyx_v_dst, __pyx_v_new_ndim, NULL, NULL, __pyx_v_memview->dtype_is_object); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 784, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);

     
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_memoryview_type))))) __PYX_ERR(2, 784, __pyx_L1_error)
    __pyx_r = ((struct __pyx_memoryview_obj *)__pyx_t_3);
    __pyx_t_3 = 0;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("View.MemoryView.memview_slice", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_memviewsliceobj);
  __Pyx_XDECREF(__pyx_v_index);
  __Pyx_XGIVEREF((PyObject *)__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static int __pyx_memoryview_slice_memviewslice(__Pyx_memviewslice *__pyx_v_dst, Py_ssize_t __pyx_v_shape, Py_ssize_t __pyx_v_stride, Py_ssize_t __pyx_v_suboffset, int __pyx_v_dim, int __pyx_v_new_ndim, int *__pyx_v_suboffset_dim, Py_ssize_t __pyx_v_start, Py_ssize_t __pyx_v_stop, Py_ssize_t __pyx_v_step, int __pyx_v_have_start, int __pyx_v_have_stop, int __pyx_v_have_step, int __pyx_v_is_slice) {
  Py_ssize_t __pyx_v_new_shape;
  int __pyx_v_negative_step;
  int __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;

   
  __pyx_t_1 = ((!(__pyx_v_is_slice != 0)) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_1 = ((__pyx_v_start < 0) != 0);
    if (__pyx_t_1) {

       
      __pyx_v_start = (__pyx_v_start + __pyx_v_shape);

       
    }

     
    __pyx_t_1 = (0 <= __pyx_v_start);
    if (__pyx_t_1) {
      __pyx_t_1 = (__pyx_v_start < __pyx_v_shape);
    }
    __pyx_t_2 = ((!(__pyx_t_1 != 0)) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_3 = __pyx_memoryview_err_dim(__pyx_builtin_IndexError, ((char *)"Index out of bounds (axis %d)"), __pyx_v_dim); if (unlikely(__pyx_t_3 == ((int)-1))) __PYX_ERR(2, 834, __pyx_L1_error)

       
    }

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_1 = ((__pyx_v_have_step != 0) != 0);
    if (__pyx_t_1) {
    } else {
      __pyx_t_2 = __pyx_t_1;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_1 = ((__pyx_v_step < 0) != 0);
    __pyx_t_2 = __pyx_t_1;
    __pyx_L6_bool_binop_done:;
    __pyx_v_negative_step = __pyx_t_2;

     
    __pyx_t_1 = (__pyx_v_have_step != 0);
    if (__pyx_t_1) {
    } else {
      __pyx_t_2 = __pyx_t_1;
      goto __pyx_L9_bool_binop_done;
    }
    __pyx_t_1 = ((__pyx_v_step == 0) != 0);
    __pyx_t_2 = __pyx_t_1;
    __pyx_L9_bool_binop_done:;
    if (__pyx_t_2) {

       
      __pyx_t_3 = __pyx_memoryview_err_dim(__pyx_builtin_ValueError, ((char *)"Step may not be zero (axis %d)"), __pyx_v_dim); if (unlikely(__pyx_t_3 == ((int)-1))) __PYX_ERR(2, 840, __pyx_L1_error)

       
    }

     
    __pyx_t_2 = (__pyx_v_have_start != 0);
    if (__pyx_t_2) {

       
      __pyx_t_2 = ((__pyx_v_start < 0) != 0);
      if (__pyx_t_2) {

         
        __pyx_v_start = (__pyx_v_start + __pyx_v_shape);

         
        __pyx_t_2 = ((__pyx_v_start < 0) != 0);
        if (__pyx_t_2) {

           
          __pyx_v_start = 0;

           
        }

         
        goto __pyx_L12;
      }

       
      __pyx_t_2 = ((__pyx_v_start >= __pyx_v_shape) != 0);
      if (__pyx_t_2) {

         
        __pyx_t_2 = (__pyx_v_negative_step != 0);
        if (__pyx_t_2) {

           
          __pyx_v_start = (__pyx_v_shape - 1);

           
          goto __pyx_L14;
        }

         
          {
          __pyx_v_start = __pyx_v_shape;
        }
        __pyx_L14:;

         
      }
      __pyx_L12:;

       
      goto __pyx_L11;
    }

     
      {
      __pyx_t_2 = (__pyx_v_negative_step != 0);
      if (__pyx_t_2) {

         
        __pyx_v_start = (__pyx_v_shape - 1);

         
        goto __pyx_L15;
      }

       
        {
        __pyx_v_start = 0;
      }
      __pyx_L15:;
    }
    __pyx_L11:;

     
    __pyx_t_2 = (__pyx_v_have_stop != 0);
    if (__pyx_t_2) {

       
      __pyx_t_2 = ((__pyx_v_stop < 0) != 0);
      if (__pyx_t_2) {

         
        __pyx_v_stop = (__pyx_v_stop + __pyx_v_shape);

         
        __pyx_t_2 = ((__pyx_v_stop < 0) != 0);
        if (__pyx_t_2) {

           
          __pyx_v_stop = 0;

           
        }

         
        goto __pyx_L17;
      }

       
      __pyx_t_2 = ((__pyx_v_stop > __pyx_v_shape) != 0);
      if (__pyx_t_2) {

         
        __pyx_v_stop = __pyx_v_shape;

         
      }
      __pyx_L17:;

       
      goto __pyx_L16;
    }

     
      {
      __pyx_t_2 = (__pyx_v_negative_step != 0);
      if (__pyx_t_2) {

         
        __pyx_v_stop = -1L;

         
        goto __pyx_L19;
      }

       
        {
        __pyx_v_stop = __pyx_v_shape;
      }
      __pyx_L19:;
    }
    __pyx_L16:;

     
    __pyx_t_2 = ((!(__pyx_v_have_step != 0)) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_step = 1;

       
    }

     
    __pyx_v_new_shape = ((__pyx_v_stop - __pyx_v_start) / __pyx_v_step);

     
    __pyx_t_2 = (((__pyx_v_stop - __pyx_v_start) - (__pyx_v_step * __pyx_v_new_shape)) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_new_shape = (__pyx_v_new_shape + 1);

       
    }

     
    __pyx_t_2 = ((__pyx_v_new_shape < 0) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_new_shape = 0;

       
    }

     
    (__pyx_v_dst->strides[__pyx_v_new_ndim]) = (__pyx_v_stride * __pyx_v_step);

     
    (__pyx_v_dst->shape[__pyx_v_new_ndim]) = __pyx_v_new_shape;

     
    (__pyx_v_dst->suboffsets[__pyx_v_new_ndim]) = __pyx_v_suboffset;
  }
  __pyx_L3:;

   
  __pyx_t_2 = (((__pyx_v_suboffset_dim[0]) < 0) != 0);
  if (__pyx_t_2) {

     
    __pyx_v_dst->data = (__pyx_v_dst->data + (__pyx_v_start * __pyx_v_stride));

     
    goto __pyx_L23;
  }

   
    {
    __pyx_t_3 = (__pyx_v_suboffset_dim[0]);
    (__pyx_v_dst->suboffsets[__pyx_t_3]) = ((__pyx_v_dst->suboffsets[__pyx_t_3]) + (__pyx_v_start * __pyx_v_stride));
  }
  __pyx_L23:;

   
  __pyx_t_2 = ((__pyx_v_suboffset >= 0) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_2 = ((!(__pyx_v_is_slice != 0)) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_2 = ((__pyx_v_new_ndim == 0) != 0);
      if (__pyx_t_2) {

         
        __pyx_v_dst->data = ((((char **)__pyx_v_dst->data)[0]) + __pyx_v_suboffset);

         
        goto __pyx_L26;
      }

       
        {

         
        __pyx_t_3 = __pyx_memoryview_err_dim(__pyx_builtin_IndexError, ((char *)"All dimensions preceding dimension %d must be indexed and not sliced"), __pyx_v_dim); if (unlikely(__pyx_t_3 == ((int)-1))) __PYX_ERR(2, 901, __pyx_L1_error)
      }
      __pyx_L26:;

       
      goto __pyx_L25;
    }

     
      {
      (__pyx_v_suboffset_dim[0]) = __pyx_v_new_ndim;
    }
    __pyx_L25:;

     
  }

   
  __pyx_r = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  {
    #ifdef WITH_THREAD
    PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
    #endif
    __Pyx_AddTraceback("View.MemoryView.slice_memviewslice", __pyx_clineno, __pyx_lineno, __pyx_filename);
    #ifdef WITH_THREAD
    __Pyx_PyGILState_Release(__pyx_gilstate_save);
    #endif
  }
  __pyx_r = -1;
  __pyx_L0:;
  return __pyx_r;
}

 

static char *__pyx_pybuffer_index(Py_buffer *__pyx_v_view, char *__pyx_v_bufp, Py_ssize_t __pyx_v_index, Py_ssize_t __pyx_v_dim) {
  Py_ssize_t __pyx_v_shape;
  Py_ssize_t __pyx_v_stride;
  Py_ssize_t __pyx_v_suboffset;
  Py_ssize_t __pyx_v_itemsize;
  char *__pyx_v_resultp;
  char *__pyx_r;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("pybuffer_index", 0);

   
  __pyx_v_suboffset = -1L;

   
  __pyx_t_1 = __pyx_v_view->itemsize;
  __pyx_v_itemsize = __pyx_t_1;

   
  __pyx_t_2 = ((__pyx_v_view->ndim == 0) != 0);
  if (__pyx_t_2) {

     
    if (unlikely(__pyx_v_itemsize == 0)) {
      PyErr_SetString(PyExc_ZeroDivisionError, "integer division or modulo by zero");
      __PYX_ERR(2, 919, __pyx_L1_error)
    }
    else if (sizeof(Py_ssize_t) == sizeof(long) && (!(((Py_ssize_t)-1) > 0)) && unlikely(__pyx_v_itemsize == (Py_ssize_t)-1)  && unlikely(UNARY_NEG_WOULD_OVERFLOW(__pyx_v_view->len))) {
      PyErr_SetString(PyExc_OverflowError, "value too large to perform division");
      __PYX_ERR(2, 919, __pyx_L1_error)
    }
    __pyx_v_shape = __Pyx_div_Py_ssize_t(__pyx_v_view->len, __pyx_v_itemsize);

     
    __pyx_v_stride = __pyx_v_itemsize;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_v_shape = (__pyx_v_view->shape[__pyx_v_dim]);

     
    __pyx_v_stride = (__pyx_v_view->strides[__pyx_v_dim]);

     
    __pyx_t_2 = ((__pyx_v_view->suboffsets != NULL) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_suboffset = (__pyx_v_view->suboffsets[__pyx_v_dim]);

       
    }
  }
  __pyx_L3:;

   
  __pyx_t_2 = ((__pyx_v_index < 0) != 0);
  if (__pyx_t_2) {

     
    __pyx_v_index = (__pyx_v_index + (__pyx_v_view->shape[__pyx_v_dim]));

     
    __pyx_t_2 = ((__pyx_v_index < 0) != 0);
    if (unlikely(__pyx_t_2)) {

       
      __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_dim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 930, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_Out_of_bounds_on_buffer_access_a, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 930, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_builtin_IndexError, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 930, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_Raise(__pyx_t_3, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __PYX_ERR(2, 930, __pyx_L1_error)

       
    }

     
  }

   
  __pyx_t_2 = ((__pyx_v_index >= __pyx_v_shape) != 0);
  if (unlikely(__pyx_t_2)) {

     
    __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_dim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 933, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_Out_of_bounds_on_buffer_access_a, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 933, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_builtin_IndexError, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 933, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(2, 933, __pyx_L1_error)

     
  }

   
  __pyx_v_resultp = (__pyx_v_bufp + (__pyx_v_index * __pyx_v_stride));

   
  __pyx_t_2 = ((__pyx_v_suboffset >= 0) != 0);
  if (__pyx_t_2) {

     
    __pyx_v_resultp = ((((char **)__pyx_v_resultp)[0]) + __pyx_v_suboffset);

     
  }

   
  __pyx_r = __pyx_v_resultp;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("View.MemoryView.pybuffer_index", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static int __pyx_memslice_transpose(__Pyx_memviewslice *__pyx_v_memslice) {
  int __pyx_v_ndim;
  Py_ssize_t *__pyx_v_shape;
  Py_ssize_t *__pyx_v_strides;
  int __pyx_v_i;
  int __pyx_v_j;
  int __pyx_r;
  int __pyx_t_1;
  Py_ssize_t *__pyx_t_2;
  long __pyx_t_3;
  long __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  Py_ssize_t __pyx_t_6;
  int __pyx_t_7;
  int __pyx_t_8;
  int __pyx_t_9;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;

   
  __pyx_t_1 = __pyx_v_memslice->memview->view.ndim;
  __pyx_v_ndim = __pyx_t_1;

   
  __pyx_t_2 = __pyx_v_memslice->shape;
  __pyx_v_shape = __pyx_t_2;

   
  __pyx_t_2 = __pyx_v_memslice->strides;
  __pyx_v_strides = __pyx_t_2;

   
  __pyx_t_3 = __Pyx_div_long(__pyx_v_ndim, 2);
  __pyx_t_4 = __pyx_t_3;
  for (__pyx_t_1 = 0; __pyx_t_1 < __pyx_t_4; __pyx_t_1+=1) {
    __pyx_v_i = __pyx_t_1;

     
    __pyx_v_j = ((__pyx_v_ndim - 1) - __pyx_v_i);

     
    __pyx_t_5 = (__pyx_v_strides[__pyx_v_j]);
    __pyx_t_6 = (__pyx_v_strides[__pyx_v_i]);
    (__pyx_v_strides[__pyx_v_i]) = __pyx_t_5;
    (__pyx_v_strides[__pyx_v_j]) = __pyx_t_6;

     
    __pyx_t_6 = (__pyx_v_shape[__pyx_v_j]);
    __pyx_t_5 = (__pyx_v_shape[__pyx_v_i]);
    (__pyx_v_shape[__pyx_v_i]) = __pyx_t_6;
    (__pyx_v_shape[__pyx_v_j]) = __pyx_t_5;

     
    __pyx_t_8 = (((__pyx_v_memslice->suboffsets[__pyx_v_i]) >= 0) != 0);
    if (!__pyx_t_8) {
    } else {
      __pyx_t_7 = __pyx_t_8;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_8 = (((__pyx_v_memslice->suboffsets[__pyx_v_j]) >= 0) != 0);
    __pyx_t_7 = __pyx_t_8;
    __pyx_L6_bool_binop_done:;
    if (__pyx_t_7) {

       
      __pyx_t_9 = __pyx_memoryview_err(__pyx_builtin_ValueError, ((char *)"Cannot transpose memoryview with indirect dimensions")); if (unlikely(__pyx_t_9 == ((int)-1))) __PYX_ERR(2, 959, __pyx_L1_error)

       
    }
  }

   
  __pyx_r = 1;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  {
    #ifdef WITH_THREAD
    PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
    #endif
    __Pyx_AddTraceback("View.MemoryView.transpose_memslice", __pyx_clineno, __pyx_lineno, __pyx_filename);
    #ifdef WITH_THREAD
    __Pyx_PyGILState_Release(__pyx_gilstate_save);
    #endif
  }
  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}

 

 
static void __pyx_memoryviewslice___dealloc__(PyObject *__pyx_v_self);  
static void __pyx_memoryviewslice___dealloc__(PyObject *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__ (wrapper)", 0);
  __pyx_memoryviewslice___pyx_pf_15View_dot_MemoryView_16_memoryviewslice___dealloc__(((struct __pyx_memoryviewslice_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
}

static void __pyx_memoryviewslice___pyx_pf_15View_dot_MemoryView_16_memoryviewslice___dealloc__(struct __pyx_memoryviewslice_obj *__pyx_v_self) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__dealloc__", 0);

   
  __PYX_XDEC_MEMVIEW((&__pyx_v_self->from_slice), 1);

   

   
  __Pyx_RefNannyFinishContext();
}

 

static PyObject *__pyx_memoryviewslice_convert_item_to_object(struct __pyx_memoryviewslice_obj *__pyx_v_self, char *__pyx_v_itemp) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("convert_item_to_object", 0);

   
  __pyx_t_1 = ((__pyx_v_self->to_object_func != NULL) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __pyx_v_self->to_object_func(__pyx_v_itemp); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 983, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_r = __pyx_t_2;
    __pyx_t_2 = 0;
    goto __pyx_L0;

     
  }

   
    {
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_2 = __pyx_memoryview_convert_item_to_object(((struct __pyx_memoryview_obj *)__pyx_v_self), __pyx_v_itemp); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 985, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_r = __pyx_t_2;
    __pyx_t_2 = 0;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("View.MemoryView._memoryviewslice.convert_item_to_object", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryviewslice_assign_item_from_object(struct __pyx_memoryviewslice_obj *__pyx_v_self, char *__pyx_v_itemp, PyObject *__pyx_v_value) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("assign_item_from_object", 0);

   
  __pyx_t_1 = ((__pyx_v_self->to_dtype_func != NULL) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = __pyx_v_self->to_dtype_func(__pyx_v_itemp, __pyx_v_value); if (unlikely(__pyx_t_2 == ((int)0))) __PYX_ERR(2, 989, __pyx_L1_error)

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_3 = __pyx_memoryview_assign_item_from_object(((struct __pyx_memoryview_obj *)__pyx_v_self), __pyx_v_itemp, __pyx_v_value); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 991, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __pyx_L3:;

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView._memoryviewslice.assign_item_from_object", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_16_memoryviewslice_4base_1__get__(PyObject *__pyx_v_self);  
static PyObject *__pyx_pw_15View_dot_MemoryView_16_memoryviewslice_4base_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_15View_dot_MemoryView_16_memoryviewslice_4base___get__(((struct __pyx_memoryviewslice_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView_16_memoryviewslice_4base___get__(struct __pyx_memoryviewslice_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_self->from_object);
  __pyx_r = __pyx_v_self->from_object;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_memoryviewslice_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused);  
static PyObject *__pyx_pw___pyx_memoryviewslice_1__reduce_cython__(PyObject *__pyx_v_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__reduce_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_memoryviewslice___reduce_cython__(((struct __pyx_memoryviewslice_obj *)__pyx_v_self));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_memoryviewslice___reduce_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__reduce_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__24, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 2, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView._memoryviewslice.__reduce_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

 
static PyObject *__pyx_pw___pyx_memoryviewslice_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state);  
static PyObject *__pyx_pw___pyx_memoryviewslice_3__setstate_cython__(PyObject *__pyx_v_self, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__setstate_cython__ (wrapper)", 0);
  __pyx_r = __pyx_pf___pyx_memoryviewslice_2__setstate_cython__(((struct __pyx_memoryviewslice_obj *)__pyx_v_self), ((PyObject *)__pyx_v___pyx_state));

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf___pyx_memoryviewslice_2__setstate_cython__(CYTHON_UNUSED struct __pyx_memoryviewslice_obj *__pyx_v_self, CYTHON_UNUSED PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setstate_cython__", 0);

   
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_TypeError, __pyx_tuple__25, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 4, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView._memoryviewslice.__setstate_cython__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_fromslice(__Pyx_memviewslice __pyx_v_memviewslice, int __pyx_v_ndim, PyObject *(*__pyx_v_to_object_func)(char *), int (*__pyx_v_to_dtype_func)(char *, PyObject *), int __pyx_v_dtype_is_object) {
  struct __pyx_memoryviewslice_obj *__pyx_v_result = 0;
  Py_ssize_t __pyx_v_suboffset;
  PyObject *__pyx_v_length = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  __Pyx_TypeInfo *__pyx_t_4;
  Py_buffer __pyx_t_5;
  Py_ssize_t *__pyx_t_6;
  Py_ssize_t *__pyx_t_7;
  Py_ssize_t *__pyx_t_8;
  Py_ssize_t __pyx_t_9;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("memoryview_fromslice", 0);

   
  __pyx_t_1 = ((((PyObject *)__pyx_v_memviewslice.memview) == Py_None) != 0);
  if (__pyx_t_1) {

     
    __Pyx_XDECREF(__pyx_r);
    __pyx_r = Py_None; __Pyx_INCREF(Py_None);
    goto __pyx_L0;

     
  }

   
  __pyx_t_2 = __Pyx_PyBool_FromLong(__pyx_v_dtype_is_object); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1015, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1015, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  PyTuple_SET_ITEM(__pyx_t_3, 0, Py_None);
  __Pyx_INCREF(__pyx_int_0);
  __Pyx_GIVEREF(__pyx_int_0);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_int_0);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Call(((PyObject *)__pyx_memoryviewslice_type), __pyx_t_3, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1015, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_result = ((struct __pyx_memoryviewslice_obj *)__pyx_t_2);
  __pyx_t_2 = 0;

   
  __pyx_v_result->from_slice = __pyx_v_memviewslice;

   
  __PYX_INC_MEMVIEW((&__pyx_v_memviewslice), 1);

   
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v_memviewslice.memview), __pyx_n_s_base); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1020, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __Pyx_GOTREF(__pyx_v_result->from_object);
  __Pyx_DECREF(__pyx_v_result->from_object);
  __pyx_v_result->from_object = __pyx_t_2;
  __pyx_t_2 = 0;

   
  __pyx_t_4 = __pyx_v_memviewslice.memview->typeinfo;
  __pyx_v_result->__pyx_base.typeinfo = __pyx_t_4;

   
  __pyx_t_5 = __pyx_v_memviewslice.memview->view;
  __pyx_v_result->__pyx_base.view = __pyx_t_5;

   
  __pyx_v_result->__pyx_base.view.buf = ((void *)__pyx_v_memviewslice.data);

   
  __pyx_v_result->__pyx_base.view.ndim = __pyx_v_ndim;

   
  ((Py_buffer *)(&__pyx_v_result->__pyx_base.view))->obj = Py_None;

   
  Py_INCREF(Py_None);

   
  __pyx_t_1 = ((((struct __pyx_memoryview_obj *)__pyx_v_memviewslice.memview)->flags & PyBUF_WRITABLE) != 0);
  if (__pyx_t_1) {

     
    __pyx_v_result->__pyx_base.flags = PyBUF_RECORDS;

     
    goto __pyx_L4;
  }

   
    {
    __pyx_v_result->__pyx_base.flags = PyBUF_RECORDS_RO;
  }
  __pyx_L4:;

   
  __pyx_v_result->__pyx_base.view.shape = ((Py_ssize_t *)__pyx_v_result->from_slice.shape);

   
  __pyx_v_result->__pyx_base.view.strides = ((Py_ssize_t *)__pyx_v_result->from_slice.strides);

   
  __pyx_v_result->__pyx_base.view.suboffsets = NULL;

   
  __pyx_t_7 = (__pyx_v_result->from_slice.suboffsets + __pyx_v_ndim);
  for (__pyx_t_8 = __pyx_v_result->from_slice.suboffsets; __pyx_t_8 < __pyx_t_7; __pyx_t_8++) {
    __pyx_t_6 = __pyx_t_8;
    __pyx_v_suboffset = (__pyx_t_6[0]);

     
    __pyx_t_1 = ((__pyx_v_suboffset >= 0) != 0);
    if (__pyx_t_1) {

       
      __pyx_v_result->__pyx_base.view.suboffsets = ((Py_ssize_t *)__pyx_v_result->from_slice.suboffsets);

       
      goto __pyx_L6_break;

       
    }
  }
  __pyx_L6_break:;

   
  __pyx_t_9 = __pyx_v_result->__pyx_base.view.itemsize;
  __pyx_v_result->__pyx_base.view.len = __pyx_t_9;

   
  __pyx_t_7 = (__pyx_v_result->__pyx_base.view.shape + __pyx_v_ndim);
  for (__pyx_t_8 = __pyx_v_result->__pyx_base.view.shape; __pyx_t_8 < __pyx_t_7; __pyx_t_8++) {
    __pyx_t_6 = __pyx_t_8;
    __pyx_t_2 = PyInt_FromSsize_t((__pyx_t_6[0])); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1045, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_XDECREF_SET(__pyx_v_length, __pyx_t_2);
    __pyx_t_2 = 0;

     
    __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_result->__pyx_base.view.len); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1046, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyNumber_InPlaceMultiply(__pyx_t_2, __pyx_v_length); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1046, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_9 = __Pyx_PyIndex_AsSsize_t(__pyx_t_3); if (unlikely((__pyx_t_9 == (Py_ssize_t)-1) && PyErr_Occurred())) __PYX_ERR(2, 1046, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_result->__pyx_base.view.len = __pyx_t_9;
  }

   
  __pyx_v_result->to_object_func = __pyx_v_to_object_func;

   
  __pyx_v_result->to_dtype_func = __pyx_v_to_dtype_func;

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_result));
  __pyx_r = ((PyObject *)__pyx_v_result);
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.memoryview_fromslice", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_result);
  __Pyx_XDECREF(__pyx_v_length);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static __Pyx_memviewslice *__pyx_memoryview_get_slice_from_memoryview(struct __pyx_memoryview_obj *__pyx_v_memview, __Pyx_memviewslice *__pyx_v_mslice) {
  struct __pyx_memoryviewslice_obj *__pyx_v_obj = 0;
  __Pyx_memviewslice *__pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_slice_from_memview", 0);

   
  __pyx_t_1 = __Pyx_TypeCheck(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type); 
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    if (!(likely(((((PyObject *)__pyx_v_memview)) == Py_None) || likely(__Pyx_TypeTest(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type))))) __PYX_ERR(2, 1058, __pyx_L1_error)
    __pyx_t_3 = ((PyObject *)__pyx_v_memview);
    __Pyx_INCREF(__pyx_t_3);
    __pyx_v_obj = ((struct __pyx_memoryviewslice_obj *)__pyx_t_3);
    __pyx_t_3 = 0;

     
    __pyx_r = (&__pyx_v_obj->from_slice);
    goto __pyx_L0;

     
  }

   
    {
    __pyx_memoryview_slice_copy(__pyx_v_memview, __pyx_v_mslice);

     
    __pyx_r = __pyx_v_mslice;
    goto __pyx_L0;
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("View.MemoryView.get_slice_from_memview", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_obj);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static void __pyx_memoryview_slice_copy(struct __pyx_memoryview_obj *__pyx_v_memview, __Pyx_memviewslice *__pyx_v_dst) {
  int __pyx_v_dim;
  Py_ssize_t *__pyx_v_shape;
  Py_ssize_t *__pyx_v_strides;
  Py_ssize_t *__pyx_v_suboffsets;
  __Pyx_RefNannyDeclarations
  Py_ssize_t *__pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  __Pyx_RefNannySetupContext("slice_copy", 0);

   
  __pyx_t_1 = __pyx_v_memview->view.shape;
  __pyx_v_shape = __pyx_t_1;

   
  __pyx_t_1 = __pyx_v_memview->view.strides;
  __pyx_v_strides = __pyx_t_1;

   
  __pyx_t_1 = __pyx_v_memview->view.suboffsets;
  __pyx_v_suboffsets = __pyx_t_1;

   
  __pyx_v_dst->memview = ((struct __pyx_memoryview_obj *)__pyx_v_memview);

   
  __pyx_v_dst->data = ((char *)__pyx_v_memview->view.buf);

   
  __pyx_t_2 = __pyx_v_memview->view.ndim;
  __pyx_t_3 = __pyx_t_2;
  for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
    __pyx_v_dim = __pyx_t_4;

     
    (__pyx_v_dst->shape[__pyx_v_dim]) = (__pyx_v_shape[__pyx_v_dim]);

     
    (__pyx_v_dst->strides[__pyx_v_dim]) = (__pyx_v_strides[__pyx_v_dim]);

     
    if ((__pyx_v_suboffsets != 0)) {
      __pyx_t_5 = (__pyx_v_suboffsets[__pyx_v_dim]);
    } else {
      __pyx_t_5 = -1L;
    }
    (__pyx_v_dst->suboffsets[__pyx_v_dim]) = __pyx_t_5;
  }

   

   
  __Pyx_RefNannyFinishContext();
}

 

static PyObject *__pyx_memoryview_copy_object(struct __pyx_memoryview_obj *__pyx_v_memview) {
  __Pyx_memviewslice __pyx_v_memviewslice;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("memoryview_copy", 0);

   
  __pyx_memoryview_slice_copy(__pyx_v_memview, (&__pyx_v_memviewslice));

   
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __pyx_memoryview_copy_object_from_slice(__pyx_v_memview, (&__pyx_v_memviewslice)); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 1086, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.memoryview_copy", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_memoryview_copy_object_from_slice(struct __pyx_memoryview_obj *__pyx_v_memview, __Pyx_memviewslice *__pyx_v_memviewslice) {
  PyObject *(*__pyx_v_to_object_func)(char *);
  int (*__pyx_v_to_dtype_func)(char *, PyObject *);
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *(*__pyx_t_3)(char *);
  int (*__pyx_t_4)(char *, PyObject *);
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("memoryview_copy_from_slice", 0);

   
  __pyx_t_1 = __Pyx_TypeCheck(((PyObject *)__pyx_v_memview), __pyx_memoryviewslice_type); 
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

     
    __pyx_t_3 = ((struct __pyx_memoryviewslice_obj *)__pyx_v_memview)->to_object_func;
    __pyx_v_to_object_func = __pyx_t_3;

     
    __pyx_t_4 = ((struct __pyx_memoryviewslice_obj *)__pyx_v_memview)->to_dtype_func;
    __pyx_v_to_dtype_func = __pyx_t_4;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_v_to_object_func = NULL;

     
    __pyx_v_to_dtype_func = NULL;
  }
  __pyx_L3:;

   
  __Pyx_XDECREF(__pyx_r);

   
  __pyx_t_5 = __pyx_memoryview_fromslice((__pyx_v_memviewslice[0]), __pyx_v_memview->view.ndim, __pyx_v_to_object_func, __pyx_v_to_dtype_func, __pyx_v_memview->dtype_is_object); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 1103, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_r = __pyx_t_5;
  __pyx_t_5 = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView.memoryview_copy_from_slice", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static Py_ssize_t abs_py_ssize_t(Py_ssize_t __pyx_v_arg) {
  Py_ssize_t __pyx_r;
  int __pyx_t_1;

   
  __pyx_t_1 = ((__pyx_v_arg < 0) != 0);
  if (__pyx_t_1) {

     
    __pyx_r = (-__pyx_v_arg);
    goto __pyx_L0;

     
  }

   
    {
    __pyx_r = __pyx_v_arg;
    goto __pyx_L0;
  }

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static char __pyx_get_best_slice_order(__Pyx_memviewslice *__pyx_v_mslice, int __pyx_v_ndim) {
  int __pyx_v_i;
  Py_ssize_t __pyx_v_c_stride;
  Py_ssize_t __pyx_v_f_stride;
  char __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;

   
  __pyx_v_c_stride = 0;

   
  __pyx_v_f_stride = 0;

   
  for (__pyx_t_1 = (__pyx_v_ndim - 1); __pyx_t_1 > -1; __pyx_t_1-=1) {
    __pyx_v_i = __pyx_t_1;

     
    __pyx_t_2 = (((__pyx_v_mslice->shape[__pyx_v_i]) > 1) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_c_stride = (__pyx_v_mslice->strides[__pyx_v_i]);

       
      goto __pyx_L4_break;

       
    }
  }
  __pyx_L4_break:;

   
  __pyx_t_1 = __pyx_v_ndim;
  __pyx_t_3 = __pyx_t_1;
  for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
    __pyx_v_i = __pyx_t_4;

     
    __pyx_t_2 = (((__pyx_v_mslice->shape[__pyx_v_i]) > 1) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_f_stride = (__pyx_v_mslice->strides[__pyx_v_i]);

       
      goto __pyx_L7_break;

       
    }
  }
  __pyx_L7_break:;

   
  __pyx_t_2 = ((abs_py_ssize_t(__pyx_v_c_stride) <= abs_py_ssize_t(__pyx_v_f_stride)) != 0);
  if (__pyx_t_2) {

     
    __pyx_r = 'C';
    goto __pyx_L0;

     
  }

   
    {
    __pyx_r = 'F';
    goto __pyx_L0;
  }

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static void _copy_strided_to_strided(char *__pyx_v_src_data, Py_ssize_t *__pyx_v_src_strides, char *__pyx_v_dst_data, Py_ssize_t *__pyx_v_dst_strides, Py_ssize_t *__pyx_v_src_shape, Py_ssize_t *__pyx_v_dst_shape, int __pyx_v_ndim, size_t __pyx_v_itemsize) {
  CYTHON_UNUSED Py_ssize_t __pyx_v_i;
  CYTHON_UNUSED Py_ssize_t __pyx_v_src_extent;
  Py_ssize_t __pyx_v_dst_extent;
  Py_ssize_t __pyx_v_src_stride;
  Py_ssize_t __pyx_v_dst_stride;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  Py_ssize_t __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  Py_ssize_t __pyx_t_6;

   
  __pyx_v_src_extent = (__pyx_v_src_shape[0]);

   
  __pyx_v_dst_extent = (__pyx_v_dst_shape[0]);

   
  __pyx_v_src_stride = (__pyx_v_src_strides[0]);

   
  __pyx_v_dst_stride = (__pyx_v_dst_strides[0]);

   
  __pyx_t_1 = ((__pyx_v_ndim == 1) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = ((__pyx_v_src_stride > 0) != 0);
    if (__pyx_t_2) {
    } else {
      __pyx_t_1 = __pyx_t_2;
      goto __pyx_L5_bool_binop_done;
    }
    __pyx_t_2 = ((__pyx_v_dst_stride > 0) != 0);
    if (__pyx_t_2) {
    } else {
      __pyx_t_1 = __pyx_t_2;
      goto __pyx_L5_bool_binop_done;
    }

     
    __pyx_t_2 = (((size_t)__pyx_v_src_stride) == __pyx_v_itemsize);
    if (__pyx_t_2) {
      __pyx_t_2 = (__pyx_v_itemsize == ((size_t)__pyx_v_dst_stride));
    }
    __pyx_t_3 = (__pyx_t_2 != 0);
    __pyx_t_1 = __pyx_t_3;
    __pyx_L5_bool_binop_done:;

     
    if (__pyx_t_1) {

       
      (void)(memcpy(__pyx_v_dst_data, __pyx_v_src_data, (__pyx_v_itemsize * __pyx_v_dst_extent)));

       
      goto __pyx_L4;
    }

     
      {
      __pyx_t_4 = __pyx_v_dst_extent;
      __pyx_t_5 = __pyx_t_4;
      for (__pyx_t_6 = 0; __pyx_t_6 < __pyx_t_5; __pyx_t_6+=1) {
        __pyx_v_i = __pyx_t_6;

         
        (void)(memcpy(__pyx_v_dst_data, __pyx_v_src_data, __pyx_v_itemsize));

         
        __pyx_v_src_data = (__pyx_v_src_data + __pyx_v_src_stride);

         
        __pyx_v_dst_data = (__pyx_v_dst_data + __pyx_v_dst_stride);
      }
    }
    __pyx_L4:;

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_4 = __pyx_v_dst_extent;
    __pyx_t_5 = __pyx_t_4;
    for (__pyx_t_6 = 0; __pyx_t_6 < __pyx_t_5; __pyx_t_6+=1) {
      __pyx_v_i = __pyx_t_6;

       
      _copy_strided_to_strided(__pyx_v_src_data, (__pyx_v_src_strides + 1), __pyx_v_dst_data, (__pyx_v_dst_strides + 1), (__pyx_v_src_shape + 1), (__pyx_v_dst_shape + 1), (__pyx_v_ndim - 1), __pyx_v_itemsize);

       
      __pyx_v_src_data = (__pyx_v_src_data + __pyx_v_src_stride);

       
      __pyx_v_dst_data = (__pyx_v_dst_data + __pyx_v_dst_stride);
    }
  }
  __pyx_L3:;

   

   
}

 

static void copy_strided_to_strided(__Pyx_memviewslice *__pyx_v_src, __Pyx_memviewslice *__pyx_v_dst, int __pyx_v_ndim, size_t __pyx_v_itemsize) {

   
  _copy_strided_to_strided(__pyx_v_src->data, __pyx_v_src->strides, __pyx_v_dst->data, __pyx_v_dst->strides, __pyx_v_src->shape, __pyx_v_dst->shape, __pyx_v_ndim, __pyx_v_itemsize);

   

   
}

 

static Py_ssize_t __pyx_memoryview_slice_get_size(__Pyx_memviewslice *__pyx_v_src, int __pyx_v_ndim) {
  Py_ssize_t __pyx_v_shape;
  Py_ssize_t __pyx_v_size;
  Py_ssize_t __pyx_r;
  Py_ssize_t __pyx_t_1;
  Py_ssize_t *__pyx_t_2;
  Py_ssize_t *__pyx_t_3;
  Py_ssize_t *__pyx_t_4;

   
  __pyx_t_1 = __pyx_v_src->memview->view.itemsize;
  __pyx_v_size = __pyx_t_1;

   
  __pyx_t_3 = (__pyx_v_src->shape + __pyx_v_ndim);
  for (__pyx_t_4 = __pyx_v_src->shape; __pyx_t_4 < __pyx_t_3; __pyx_t_4++) {
    __pyx_t_2 = __pyx_t_4;
    __pyx_v_shape = (__pyx_t_2[0]);

     
    __pyx_v_size = (__pyx_v_size * __pyx_v_shape);
  }

   
  __pyx_r = __pyx_v_size;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static Py_ssize_t __pyx_fill_contig_strides_array(Py_ssize_t *__pyx_v_shape, Py_ssize_t *__pyx_v_strides, Py_ssize_t __pyx_v_stride, int __pyx_v_ndim, char __pyx_v_order) {
  int __pyx_v_idx;
  Py_ssize_t __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;

   
  __pyx_t_1 = ((__pyx_v_order == 'F') != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = __pyx_v_ndim;
    __pyx_t_3 = __pyx_t_2;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_idx = __pyx_t_4;

       
      (__pyx_v_strides[__pyx_v_idx]) = __pyx_v_stride;

       
      __pyx_v_stride = (__pyx_v_stride * (__pyx_v_shape[__pyx_v_idx]));
    }

     
    goto __pyx_L3;
  }

   
    {
    for (__pyx_t_2 = (__pyx_v_ndim - 1); __pyx_t_2 > -1; __pyx_t_2-=1) {
      __pyx_v_idx = __pyx_t_2;

       
      (__pyx_v_strides[__pyx_v_idx]) = __pyx_v_stride;

       
      __pyx_v_stride = (__pyx_v_stride * (__pyx_v_shape[__pyx_v_idx]));
    }
  }
  __pyx_L3:;

   
  __pyx_r = __pyx_v_stride;
  goto __pyx_L0;

   

   
  __pyx_L0:;
  return __pyx_r;
}

 

static void *__pyx_memoryview_copy_data_to_temp(__Pyx_memviewslice *__pyx_v_src, __Pyx_memviewslice *__pyx_v_tmpslice, char __pyx_v_order, int __pyx_v_ndim) {
  int __pyx_v_i;
  void *__pyx_v_result;
  size_t __pyx_v_itemsize;
  size_t __pyx_v_size;
  void *__pyx_r;
  Py_ssize_t __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  struct __pyx_memoryview_obj *__pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;

   
  __pyx_t_1 = __pyx_v_src->memview->view.itemsize;
  __pyx_v_itemsize = __pyx_t_1;

   
  __pyx_v_size = __pyx_memoryview_slice_get_size(__pyx_v_src, __pyx_v_ndim);

   
  __pyx_v_result = malloc(__pyx_v_size);

   
  __pyx_t_2 = ((!(__pyx_v_result != 0)) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_3 = __pyx_memoryview_err(__pyx_builtin_MemoryError, NULL); if (unlikely(__pyx_t_3 == ((int)-1))) __PYX_ERR(2, 1226, __pyx_L1_error)

     
  }

   
  __pyx_v_tmpslice->data = ((char *)__pyx_v_result);

   
  __pyx_t_4 = __pyx_v_src->memview;
  __pyx_v_tmpslice->memview = __pyx_t_4;

   
  __pyx_t_3 = __pyx_v_ndim;
  __pyx_t_5 = __pyx_t_3;
  for (__pyx_t_6 = 0; __pyx_t_6 < __pyx_t_5; __pyx_t_6+=1) {
    __pyx_v_i = __pyx_t_6;

     
    (__pyx_v_tmpslice->shape[__pyx_v_i]) = (__pyx_v_src->shape[__pyx_v_i]);

     
    (__pyx_v_tmpslice->suboffsets[__pyx_v_i]) = -1L;
  }

   
  (void)(__pyx_fill_contig_strides_array((&(__pyx_v_tmpslice->shape[0])), (&(__pyx_v_tmpslice->strides[0])), __pyx_v_itemsize, __pyx_v_ndim, __pyx_v_order));

   
  __pyx_t_3 = __pyx_v_ndim;
  __pyx_t_5 = __pyx_t_3;
  for (__pyx_t_6 = 0; __pyx_t_6 < __pyx_t_5; __pyx_t_6+=1) {
    __pyx_v_i = __pyx_t_6;

     
    __pyx_t_2 = (((__pyx_v_tmpslice->shape[__pyx_v_i]) == 1) != 0);
    if (__pyx_t_2) {

       
      (__pyx_v_tmpslice->strides[__pyx_v_i]) = 0;

       
    }
  }

   
  __pyx_t_2 = (__pyx_memviewslice_is_contig((__pyx_v_src[0]), __pyx_v_order, __pyx_v_ndim) != 0);
  if (__pyx_t_2) {

     
    (void)(memcpy(__pyx_v_result, __pyx_v_src->data, __pyx_v_size));

     
    goto __pyx_L9;
  }

   
    {
    copy_strided_to_strided(__pyx_v_src, __pyx_v_tmpslice, __pyx_v_ndim, __pyx_v_itemsize);
  }
  __pyx_L9:;

   
  __pyx_r = __pyx_v_result;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  {
    #ifdef WITH_THREAD
    PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
    #endif
    __Pyx_AddTraceback("View.MemoryView.copy_data_to_temp", __pyx_clineno, __pyx_lineno, __pyx_filename);
    #ifdef WITH_THREAD
    __Pyx_PyGILState_Release(__pyx_gilstate_save);
    #endif
  }
  __pyx_r = NULL;
  __pyx_L0:;
  return __pyx_r;
}

 

static int __pyx_memoryview_err_extents(int __pyx_v_i, Py_ssize_t __pyx_v_extent1, Py_ssize_t __pyx_v_extent2) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  #ifdef WITH_THREAD
  PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
  #endif
  __Pyx_RefNannySetupContext("_err_extents", 0);

   
  __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 1256, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_extent1); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1256, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_extent2); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1256, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyTuple_New(3); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 1256, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_4, 2, __pyx_t_3);
  __pyx_t_1 = 0;
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;

   
  __pyx_t_3 = __Pyx_PyString_Format(__pyx_kp_s_got_differing_extents_in_dimensi, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1255, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_builtin_ValueError, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 1255, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_Raise(__pyx_t_4, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __PYX_ERR(2, 1255, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("View.MemoryView._err_extents", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __Pyx_RefNannyFinishContext();
  #ifdef WITH_THREAD
  __Pyx_PyGILState_Release(__pyx_gilstate_save);
  #endif
  return __pyx_r;
}

 

static int __pyx_memoryview_err_dim(PyObject *__pyx_v_error, char *__pyx_v_msg, int __pyx_v_dim) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  #ifdef WITH_THREAD
  PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
  #endif
  __Pyx_RefNannySetupContext("_err_dim", 0);
  __Pyx_INCREF(__pyx_v_error);

   
  __pyx_t_2 = __Pyx_decode_c_string(__pyx_v_msg, 0, strlen(__pyx_v_msg), NULL, NULL, PyUnicode_DecodeASCII); if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_dim); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyUnicode_Format(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 1260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_INCREF(__pyx_v_error);
  __pyx_t_3 = __pyx_v_error; __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  __pyx_t_1 = (__pyx_t_2) ? __Pyx_PyObject_Call2Args(__pyx_t_3, __pyx_t_2, __pyx_t_4) : __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4);
  __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 1260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_Raise(__pyx_t_1, 0, 0, 0);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __PYX_ERR(2, 1260, __pyx_L1_error)

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("View.MemoryView._err_dim", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __Pyx_XDECREF(__pyx_v_error);
  __Pyx_RefNannyFinishContext();
  #ifdef WITH_THREAD
  __Pyx_PyGILState_Release(__pyx_gilstate_save);
  #endif
  return __pyx_r;
}

 

static int __pyx_memoryview_err(PyObject *__pyx_v_error, char *__pyx_v_msg) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  #ifdef WITH_THREAD
  PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
  #endif
  __Pyx_RefNannySetupContext("_err", 0);
  __Pyx_INCREF(__pyx_v_error);

   
  __pyx_t_1 = ((__pyx_v_msg != NULL) != 0);
  if (unlikely(__pyx_t_1)) {

     
    __pyx_t_3 = __Pyx_decode_c_string(__pyx_v_msg, 0, strlen(__pyx_v_msg), NULL, NULL, PyUnicode_DecodeASCII); if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 1265, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_v_error);
    __pyx_t_4 = __pyx_v_error; __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
      }
    }
    __pyx_t_2 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_4, __pyx_t_5, __pyx_t_3) : __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_3);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (unlikely(!__pyx_t_2)) __PYX_ERR(2, 1265, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __PYX_ERR(2, 1265, __pyx_L1_error)

     
  }

   
    {
    __Pyx_Raise(__pyx_v_error, 0, 0, 0);
    __PYX_ERR(2, 1267, __pyx_L1_error)
  }

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("View.MemoryView._err", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __Pyx_XDECREF(__pyx_v_error);
  __Pyx_RefNannyFinishContext();
  #ifdef WITH_THREAD
  __Pyx_PyGILState_Release(__pyx_gilstate_save);
  #endif
  return __pyx_r;
}

 

static int __pyx_memoryview_copy_contents(__Pyx_memviewslice __pyx_v_src, __Pyx_memviewslice __pyx_v_dst, int __pyx_v_src_ndim, int __pyx_v_dst_ndim, int __pyx_v_dtype_is_object) {
  void *__pyx_v_tmpdata;
  size_t __pyx_v_itemsize;
  int __pyx_v_i;
  char __pyx_v_order;
  int __pyx_v_broadcasting;
  int __pyx_v_direct_copy;
  __Pyx_memviewslice __pyx_v_tmp;
  int __pyx_v_ndim;
  int __pyx_r;
  Py_ssize_t __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  void *__pyx_t_7;
  int __pyx_t_8;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;

   
  __pyx_v_tmpdata = NULL;

   
  __pyx_t_1 = __pyx_v_src.memview->view.itemsize;
  __pyx_v_itemsize = __pyx_t_1;

   
  __pyx_v_order = __pyx_get_best_slice_order((&__pyx_v_src), __pyx_v_src_ndim);

   
  __pyx_v_broadcasting = 0;

   
  __pyx_v_direct_copy = 0;

   
  __pyx_t_2 = ((__pyx_v_src_ndim < __pyx_v_dst_ndim) != 0);
  if (__pyx_t_2) {

     
    __pyx_memoryview_broadcast_leading((&__pyx_v_src), __pyx_v_src_ndim, __pyx_v_dst_ndim);

     
    goto __pyx_L3;
  }

   
  __pyx_t_2 = ((__pyx_v_dst_ndim < __pyx_v_src_ndim) != 0);
  if (__pyx_t_2) {

     
    __pyx_memoryview_broadcast_leading((&__pyx_v_dst), __pyx_v_dst_ndim, __pyx_v_src_ndim);

     
  }
  __pyx_L3:;

   
  __pyx_t_3 = __pyx_v_dst_ndim;
  __pyx_t_4 = __pyx_v_src_ndim;
  if (((__pyx_t_3 > __pyx_t_4) != 0)) {
    __pyx_t_5 = __pyx_t_3;
  } else {
    __pyx_t_5 = __pyx_t_4;
  }
  __pyx_v_ndim = __pyx_t_5;

   
  __pyx_t_5 = __pyx_v_ndim;
  __pyx_t_3 = __pyx_t_5;
  for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
    __pyx_v_i = __pyx_t_4;

     
    __pyx_t_2 = (((__pyx_v_src.shape[__pyx_v_i]) != (__pyx_v_dst.shape[__pyx_v_i])) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_2 = (((__pyx_v_src.shape[__pyx_v_i]) == 1) != 0);
      if (__pyx_t_2) {

         
        __pyx_v_broadcasting = 1;

         
        (__pyx_v_src.strides[__pyx_v_i]) = 0;

         
        goto __pyx_L7;
      }

       
        {
        __pyx_t_6 = __pyx_memoryview_err_extents(__pyx_v_i, (__pyx_v_dst.shape[__pyx_v_i]), (__pyx_v_src.shape[__pyx_v_i])); if (unlikely(__pyx_t_6 == ((int)-1))) __PYX_ERR(2, 1299, __pyx_L1_error)
      }
      __pyx_L7:;

       
    }

     
    __pyx_t_2 = (((__pyx_v_src.suboffsets[__pyx_v_i]) >= 0) != 0);
    if (__pyx_t_2) {

       
      __pyx_t_6 = __pyx_memoryview_err_dim(__pyx_builtin_ValueError, ((char *)"Dimension %d is not direct"), __pyx_v_i); if (unlikely(__pyx_t_6 == ((int)-1))) __PYX_ERR(2, 1302, __pyx_L1_error)

       
    }
  }

   
  __pyx_t_2 = (__pyx_slices_overlap((&__pyx_v_src), (&__pyx_v_dst), __pyx_v_ndim, __pyx_v_itemsize) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_2 = ((!(__pyx_memviewslice_is_contig(__pyx_v_src, __pyx_v_order, __pyx_v_ndim) != 0)) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_order = __pyx_get_best_slice_order((&__pyx_v_dst), __pyx_v_ndim);

       
    }

     
    __pyx_t_7 = __pyx_memoryview_copy_data_to_temp((&__pyx_v_src), (&__pyx_v_tmp), __pyx_v_order, __pyx_v_ndim); if (unlikely(__pyx_t_7 == ((void *)NULL))) __PYX_ERR(2, 1309, __pyx_L1_error)
    __pyx_v_tmpdata = __pyx_t_7;

     
    __pyx_v_src = __pyx_v_tmp;

     
  }

   
  __pyx_t_2 = ((!(__pyx_v_broadcasting != 0)) != 0);
  if (__pyx_t_2) {

     
    __pyx_t_2 = (__pyx_memviewslice_is_contig(__pyx_v_src, 'C', __pyx_v_ndim) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_direct_copy = __pyx_memviewslice_is_contig(__pyx_v_dst, 'C', __pyx_v_ndim);

       
      goto __pyx_L12;
    }

     
    __pyx_t_2 = (__pyx_memviewslice_is_contig(__pyx_v_src, 'F', __pyx_v_ndim) != 0);
    if (__pyx_t_2) {

       
      __pyx_v_direct_copy = __pyx_memviewslice_is_contig(__pyx_v_dst, 'F', __pyx_v_ndim);

       
    }
    __pyx_L12:;

     
    __pyx_t_2 = (__pyx_v_direct_copy != 0);
    if (__pyx_t_2) {

       
      __pyx_memoryview_refcount_copying((&__pyx_v_dst), __pyx_v_dtype_is_object, __pyx_v_ndim, 0);

       
      (void)(memcpy(__pyx_v_dst.data, __pyx_v_src.data, __pyx_memoryview_slice_get_size((&__pyx_v_src), __pyx_v_ndim)));

       
      __pyx_memoryview_refcount_copying((&__pyx_v_dst), __pyx_v_dtype_is_object, __pyx_v_ndim, 1);

       
      free(__pyx_v_tmpdata);

       
      __pyx_r = 0;
      goto __pyx_L0;

       
    }

     
  }

   
  __pyx_t_2 = (__pyx_v_order == 'F');
  if (__pyx_t_2) {
    __pyx_t_2 = ('F' == __pyx_get_best_slice_order((&__pyx_v_dst), __pyx_v_ndim));
  }
  __pyx_t_8 = (__pyx_t_2 != 0);
  if (__pyx_t_8) {

     
    __pyx_t_5 = __pyx_memslice_transpose((&__pyx_v_src)); if (unlikely(__pyx_t_5 == ((int)0))) __PYX_ERR(2, 1331, __pyx_L1_error)

     
    __pyx_t_5 = __pyx_memslice_transpose((&__pyx_v_dst)); if (unlikely(__pyx_t_5 == ((int)0))) __PYX_ERR(2, 1332, __pyx_L1_error)

     
  }

   
  __pyx_memoryview_refcount_copying((&__pyx_v_dst), __pyx_v_dtype_is_object, __pyx_v_ndim, 0);

   
  copy_strided_to_strided((&__pyx_v_src), (&__pyx_v_dst), __pyx_v_ndim, __pyx_v_itemsize);

   
  __pyx_memoryview_refcount_copying((&__pyx_v_dst), __pyx_v_dtype_is_object, __pyx_v_ndim, 1);

   
  free(__pyx_v_tmpdata);

   
  __pyx_r = 0;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  {
    #ifdef WITH_THREAD
    PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
    #endif
    __Pyx_AddTraceback("View.MemoryView.memoryview_copy_contents", __pyx_clineno, __pyx_lineno, __pyx_filename);
    #ifdef WITH_THREAD
    __Pyx_PyGILState_Release(__pyx_gilstate_save);
    #endif
  }
  __pyx_r = -1;
  __pyx_L0:;
  return __pyx_r;
}

 

static void __pyx_memoryview_broadcast_leading(__Pyx_memviewslice *__pyx_v_mslice, int __pyx_v_ndim, int __pyx_v_ndim_other) {
  int __pyx_v_i;
  int __pyx_v_offset;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;

   
  __pyx_v_offset = (__pyx_v_ndim_other - __pyx_v_ndim);

   
  for (__pyx_t_1 = (__pyx_v_ndim - 1); __pyx_t_1 > -1; __pyx_t_1-=1) {
    __pyx_v_i = __pyx_t_1;

     
    (__pyx_v_mslice->shape[(__pyx_v_i + __pyx_v_offset)]) = (__pyx_v_mslice->shape[__pyx_v_i]);

     
    (__pyx_v_mslice->strides[(__pyx_v_i + __pyx_v_offset)]) = (__pyx_v_mslice->strides[__pyx_v_i]);

     
    (__pyx_v_mslice->suboffsets[(__pyx_v_i + __pyx_v_offset)]) = (__pyx_v_mslice->suboffsets[__pyx_v_i]);
  }

   
  __pyx_t_1 = __pyx_v_offset;
  __pyx_t_2 = __pyx_t_1;
  for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
    __pyx_v_i = __pyx_t_3;

     
    (__pyx_v_mslice->shape[__pyx_v_i]) = 1;

     
    (__pyx_v_mslice->strides[__pyx_v_i]) = (__pyx_v_mslice->strides[0]);

     
    (__pyx_v_mslice->suboffsets[__pyx_v_i]) = -1L;
  }

   

   
}

 

static void __pyx_memoryview_refcount_copying(__Pyx_memviewslice *__pyx_v_dst, int __pyx_v_dtype_is_object, int __pyx_v_ndim, int __pyx_v_inc) {
  int __pyx_t_1;

   
  __pyx_t_1 = (__pyx_v_dtype_is_object != 0);
  if (__pyx_t_1) {

     
    __pyx_memoryview_refcount_objects_in_slice_with_gil(__pyx_v_dst->data, __pyx_v_dst->shape, __pyx_v_dst->strides, __pyx_v_ndim, __pyx_v_inc);

     
  }

   

   
}

 

static void __pyx_memoryview_refcount_objects_in_slice_with_gil(char *__pyx_v_data, Py_ssize_t *__pyx_v_shape, Py_ssize_t *__pyx_v_strides, int __pyx_v_ndim, int __pyx_v_inc) {
  __Pyx_RefNannyDeclarations
  #ifdef WITH_THREAD
  PyGILState_STATE __pyx_gilstate_save = __Pyx_PyGILState_Ensure();
  #endif
  __Pyx_RefNannySetupContext("refcount_objects_in_slice_with_gil", 0);

   
  __pyx_memoryview_refcount_objects_in_slice(__pyx_v_data, __pyx_v_shape, __pyx_v_strides, __pyx_v_ndim, __pyx_v_inc);

   

   
  __Pyx_RefNannyFinishContext();
  #ifdef WITH_THREAD
  __Pyx_PyGILState_Release(__pyx_gilstate_save);
  #endif
}

 

static void __pyx_memoryview_refcount_objects_in_slice(char *__pyx_v_data, Py_ssize_t *__pyx_v_shape, Py_ssize_t *__pyx_v_strides, int __pyx_v_ndim, int __pyx_v_inc) {
  CYTHON_UNUSED Py_ssize_t __pyx_v_i;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  Py_ssize_t __pyx_t_2;
  Py_ssize_t __pyx_t_3;
  int __pyx_t_4;
  __Pyx_RefNannySetupContext("refcount_objects_in_slice", 0);

   
  __pyx_t_1 = (__pyx_v_shape[0]);
  __pyx_t_2 = __pyx_t_1;
  for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
    __pyx_v_i = __pyx_t_3;

     
    __pyx_t_4 = ((__pyx_v_ndim == 1) != 0);
    if (__pyx_t_4) {

       
      __pyx_t_4 = (__pyx_v_inc != 0);
      if (__pyx_t_4) {

         
        Py_INCREF((((PyObject **)__pyx_v_data)[0]));

         
        goto __pyx_L6;
      }

       
        {
        Py_DECREF((((PyObject **)__pyx_v_data)[0]));
      }
      __pyx_L6:;

       
      goto __pyx_L5;
    }

     
      {

       
      __pyx_memoryview_refcount_objects_in_slice(__pyx_v_data, (__pyx_v_shape + 1), (__pyx_v_strides + 1), (__pyx_v_ndim - 1), __pyx_v_inc);
    }
    __pyx_L5:;

     
    __pyx_v_data = (__pyx_v_data + (__pyx_v_strides[0]));
  }

   

   
  __Pyx_RefNannyFinishContext();
}

 

static void __pyx_memoryview_slice_assign_scalar(__Pyx_memviewslice *__pyx_v_dst, int __pyx_v_ndim, size_t __pyx_v_itemsize, void *__pyx_v_item, int __pyx_v_dtype_is_object) {

   
  __pyx_memoryview_refcount_copying(__pyx_v_dst, __pyx_v_dtype_is_object, __pyx_v_ndim, 0);

   
  __pyx_memoryview__slice_assign_scalar(__pyx_v_dst->data, __pyx_v_dst->shape, __pyx_v_dst->strides, __pyx_v_ndim, __pyx_v_itemsize, __pyx_v_item);

   
  __pyx_memoryview_refcount_copying(__pyx_v_dst, __pyx_v_dtype_is_object, __pyx_v_ndim, 1);

   

   
}

 

static void __pyx_memoryview__slice_assign_scalar(char *__pyx_v_data, Py_ssize_t *__pyx_v_shape, Py_ssize_t *__pyx_v_strides, int __pyx_v_ndim, size_t __pyx_v_itemsize, void *__pyx_v_item) {
  CYTHON_UNUSED Py_ssize_t __pyx_v_i;
  Py_ssize_t __pyx_v_stride;
  Py_ssize_t __pyx_v_extent;
  int __pyx_t_1;
  Py_ssize_t __pyx_t_2;
  Py_ssize_t __pyx_t_3;
  Py_ssize_t __pyx_t_4;

   
  __pyx_v_stride = (__pyx_v_strides[0]);

   
  __pyx_v_extent = (__pyx_v_shape[0]);

   
  __pyx_t_1 = ((__pyx_v_ndim == 1) != 0);
  if (__pyx_t_1) {

     
    __pyx_t_2 = __pyx_v_extent;
    __pyx_t_3 = __pyx_t_2;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_i = __pyx_t_4;

       
      (void)(memcpy(__pyx_v_data, __pyx_v_item, __pyx_v_itemsize));

       
      __pyx_v_data = (__pyx_v_data + __pyx_v_stride);
    }

     
    goto __pyx_L3;
  }

   
    {
    __pyx_t_2 = __pyx_v_extent;
    __pyx_t_3 = __pyx_t_2;
    for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
      __pyx_v_i = __pyx_t_4;

       
      __pyx_memoryview__slice_assign_scalar(__pyx_v_data, (__pyx_v_shape + 1), (__pyx_v_strides + 1), (__pyx_v_ndim - 1), __pyx_v_itemsize, __pyx_v_item);

       
      __pyx_v_data = (__pyx_v_data + __pyx_v_stride);
    }
  }
  __pyx_L3:;

   

   
}

 

 
static PyObject *__pyx_pw_15View_dot_MemoryView_1__pyx_unpickle_Enum(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds);  
static PyMethodDef __pyx_mdef_15View_dot_MemoryView_1__pyx_unpickle_Enum = {"__pyx_unpickle_Enum", (PyCFunction)(void*)(PyCFunctionWithKeywords)__pyx_pw_15View_dot_MemoryView_1__pyx_unpickle_Enum, METH_VARARGS|METH_KEYWORDS, 0};
static PyObject *__pyx_pw_15View_dot_MemoryView_1__pyx_unpickle_Enum(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v___pyx_type = 0;
  long __pyx_v___pyx_checksum;
  PyObject *__pyx_v___pyx_state = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__pyx_unpickle_Enum (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_pyx_type,&__pyx_n_s_pyx_checksum,&__pyx_n_s_pyx_state,0};
    PyObject* values[3] = {0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        CYTHON_FALLTHROUGH;
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        CYTHON_FALLTHROUGH;
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        CYTHON_FALLTHROUGH;
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_type)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        CYTHON_FALLTHROUGH;
        case  1:
        if (likely((values[1] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_checksum)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Enum", 1, 3, 3, 1); __PYX_ERR(2, 1, __pyx_L3_error)
        }
        CYTHON_FALLTHROUGH;
        case  2:
        if (likely((values[2] = __Pyx_PyDict_GetItemStr(__pyx_kwds, __pyx_n_s_pyx_state)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Enum", 1, 3, 3, 2); __PYX_ERR(2, 1, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__pyx_unpickle_Enum") < 0)) __PYX_ERR(2, 1, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v___pyx_type = values[0];
    __pyx_v___pyx_checksum = __Pyx_PyInt_As_long(values[1]); if (unlikely((__pyx_v___pyx_checksum == (long)-1) && PyErr_Occurred())) __PYX_ERR(2, 1, __pyx_L3_error)
    __pyx_v___pyx_state = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__pyx_unpickle_Enum", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(2, 1, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("View.MemoryView.__pyx_unpickle_Enum", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_15View_dot_MemoryView___pyx_unpickle_Enum(__pyx_self, __pyx_v___pyx_type, __pyx_v___pyx_checksum, __pyx_v___pyx_state);

   
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_15View_dot_MemoryView___pyx_unpickle_Enum(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v___pyx_type, long __pyx_v___pyx_checksum, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_v___pyx_PickleError = 0;
  PyObject *__pyx_v___pyx_result = 0;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Enum", 0);

   
  __pyx_t_1 = __Pyx_PyInt_From_long(__pyx_v___pyx_checksum); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = (__Pyx_PySequence_ContainsTF(__pyx_t_1, __pyx_tuple__26, Py_NE)); if (unlikely(__pyx_t_2 < 0)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (__pyx_t_3) {

     
    __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_n_s_PickleError);
    __Pyx_GIVEREF(__pyx_n_s_PickleError);
    PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_PickleError);
    __pyx_t_4 = __Pyx_Import(__pyx_n_s_pickle, __pyx_t_1, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_4, __pyx_n_s_PickleError); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 5, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_t_1);
    __pyx_v___pyx_PickleError = __pyx_t_1;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

     
    __pyx_t_1 = __Pyx_PyInt_From_long(__pyx_v___pyx_checksum); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = __Pyx_PyString_Format(__pyx_kp_s_Incompatible_checksums_0x_x_vs_0, __pyx_t_1); if (unlikely(!__pyx_t_5)) __PYX_ERR(2, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_INCREF(__pyx_v___pyx_PickleError);
    __pyx_t_1 = __pyx_v___pyx_PickleError; __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    __pyx_t_4 = (__pyx_t_6) ? __Pyx_PyObject_Call2Args(__pyx_t_1, __pyx_t_6, __pyx_t_5) : __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_5);
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 6, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_Raise(__pyx_t_4, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __PYX_ERR(2, 6, __pyx_L1_error)

     
  }

   
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_MemviewEnum_type), __pyx_n_s_new); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  __pyx_t_4 = (__pyx_t_5) ? __Pyx_PyObject_Call2Args(__pyx_t_1, __pyx_t_5, __pyx_v___pyx_type) : __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v___pyx_type);
  __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v___pyx_result = __pyx_t_4;
  __pyx_t_4 = 0;

   
  __pyx_t_3 = (__pyx_v___pyx_state != Py_None);
  __pyx_t_2 = (__pyx_t_3 != 0);
  if (__pyx_t_2) {

     
    if (!(likely(PyTuple_CheckExact(__pyx_v___pyx_state))||((__pyx_v___pyx_state) == Py_None)||((void)PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_v___pyx_state)->tp_name), 0))) __PYX_ERR(2, 9, __pyx_L1_error)
    __pyx_t_4 = __pyx_unpickle_Enum__set_state(((struct __pyx_MemviewEnum_obj *)__pyx_v___pyx_result), ((PyObject*)__pyx_v___pyx_state)); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 9, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

     
  }

   
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v___pyx_result);
  __pyx_r = __pyx_v___pyx_result;
  goto __pyx_L0;

   

   
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("View.MemoryView.__pyx_unpickle_Enum", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v___pyx_PickleError);
  __Pyx_XDECREF(__pyx_v___pyx_result);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

 

static PyObject *__pyx_unpickle_Enum__set_state(struct __pyx_MemviewEnum_obj *__pyx_v___pyx_result, PyObject *__pyx_v___pyx_state) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  Py_ssize_t __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__pyx_unpickle_Enum__set_state", 0);

   
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    __PYX_ERR(2, 12, __pyx_L1_error)
  }
  __pyx_t_1 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v___pyx_result->name);
  __Pyx_DECREF(__pyx_v___pyx_result->name);
  __pyx_v___pyx_result->name = __pyx_t_1;
  __pyx_t_1 = 0;

   
  if (unlikely(__pyx_v___pyx_state == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    __PYX_ERR(2, 13, __pyx_L1_error)
  }
  __pyx_t_3 = PyTuple_GET_SIZE(__pyx_v___pyx_state); if (unlikely(__pyx_t_3 == ((Py_ssize_t)-1))) __PYX_ERR(2, 13, __pyx_L1_error)
  __pyx_t_4 = ((__pyx_t_3 > 1) != 0);
  if (__pyx_t_4) {
  } else {
    __pyx_t_2 = __pyx_t_4;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_4 = __Pyx_HasAttr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(__pyx_t_4 == ((int)-1))) __PYX_ERR(2, 13, __pyx_L1_error)
  __pyx_t_5 = (__pyx_t_4 != 0);
  __pyx_t_2 = __pyx_t_5;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_2) {

     
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(((PyObject *)__pyx_v___pyx_result), __pyx_n_s_dict); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_update); if (unlikely(!__pyx_t_7)) __PYX_ERR(2, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (unlikely(__pyx_v___pyx_state == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(2, 14, __pyx_L1_error)
    }
    __pyx_t_6 = __Pyx_GetItemInt_Tuple(__pyx_v___pyx_state, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(2, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_7))) {
      __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_7);
      if (likely(__pyx_t_8)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
        __Pyx_INCREF(__pyx_t_8);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_7, function);
      }
    }
    __pyx_t_1 = (__pyx_t_8) ? __Pyx_PyObject_Call2Args(__pyx_t_7, __pyx_t_8, __pyx_t_6) : __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_6);
    __Pyx_XDECREF(__pyx_t_8); __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

     
  }

   

   
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("View.MemoryView.__pyx_unpickle_Enum__set_state", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
static struct __pyx_vtabstruct_array __pyx_vtable_array;

static PyObject *__pyx_tp_new_array(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_array_obj *p;
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_array_obj *)o);
  p->__pyx_vtab = __pyx_vtabptr_array;
  p->mode = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->_format = ((PyObject*)Py_None); Py_INCREF(Py_None);
  if (unlikely(__pyx_array___cinit__(o, a, k) < 0)) goto bad;
  return o;
  bad:
  Py_DECREF(o); o = 0;
  return NULL;
}

static void __pyx_tp_dealloc_array(PyObject *o) {
  struct __pyx_array_obj *p = (struct __pyx_array_obj *)o;
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && (!PyType_IS_GC(Py_TYPE(o)) || !_PyGC_FINALIZED(o))) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) + 1);
    __pyx_array___dealloc__(o);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) - 1);
    PyErr_Restore(etype, eval, etb);
  }
  Py_CLEAR(p->mode);
  Py_CLEAR(p->_format);
  (*Py_TYPE(o)->tp_free)(o);
}
static PyObject *__pyx_sq_item_array(PyObject *o, Py_ssize_t i) {
  PyObject *r;
  PyObject *x = PyInt_FromSsize_t(i); if(!x) return 0;
  r = Py_TYPE(o)->tp_as_mapping->mp_subscript(o, x);
  Py_DECREF(x);
  return r;
}

static int __pyx_mp_ass_subscript_array(PyObject *o, PyObject *i, PyObject *v) {
  if (v) {
    return __pyx_array___setitem__(o, i, v);
  }
  else {
    PyErr_Format(PyExc_NotImplementedError,
      "Subscript deletion not supported by %.200s", Py_TYPE(o)->tp_name);
    return -1;
  }
}

static PyObject *__pyx_tp_getattro_array(PyObject *o, PyObject *n) {
  PyObject *v = __Pyx_PyObject_GenericGetAttr(o, n);
  if (!v && PyErr_ExceptionMatches(PyExc_AttributeError)) {
    PyErr_Clear();
    v = __pyx_array___getattr__(o, n);
  }
  return v;
}

static PyObject *__pyx_getprop___pyx_array_memview(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_5array_7memview_1__get__(o);
}

static PyMethodDef __pyx_methods_array[] = {
  {"__getattr__", (PyCFunction)__pyx_array___getattr__, METH_O|METH_COEXIST, 0},
  {"__reduce_cython__", (PyCFunction)__pyx_pw___pyx_array_1__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw___pyx_array_3__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_array[] = {
  {(char *)"memview", __pyx_getprop___pyx_array_memview, 0, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PySequenceMethods __pyx_tp_as_sequence_array = {
  __pyx_array___len__,  
  0,  
  0,  
  __pyx_sq_item_array,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
};

static PyMappingMethods __pyx_tp_as_mapping_array = {
  __pyx_array___len__,  
  __pyx_array___getitem__,  
  __pyx_mp_ass_subscript_array,  
};

static PyBufferProcs __pyx_tp_as_buffer_array = {
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  __pyx_array_getbuffer,  
  0,  
};

static PyTypeObject __pyx_type___pyx_array = {
  PyVarObject_HEAD_INIT(0, 0)
  "simplejpeg._jpeg.array",  
  sizeof(struct __pyx_array_obj),  
  0,  
  __pyx_tp_dealloc_array,  
  #if PY_VERSION_HEX < 0x030800b4
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0,  
  #endif
  0,  
  0,  
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION >= 3
  0,  
  #endif
  0,  
  0,  
  &__pyx_tp_as_sequence_array,  
  &__pyx_tp_as_mapping_array,  
  0,  
  0,  
  0,  
  __pyx_tp_getattro_array,  
  0,  
  &__pyx_tp_as_buffer_array,  
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  __pyx_methods_array,  
  0,  
  __pyx_getsets_array,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  __pyx_tp_new_array,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  #if PY_VERSION_HEX >= 0x030400a1
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b1 && (!CYTHON_COMPILING_IN_PYPY || PYPY_VERSION_NUM >= 0x07030800)
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0,  
  #endif
  #if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX >= 0x03090000 && PY_VERSION_HEX < 0x030a0000
  0,  
  #endif
};

static PyObject *__pyx_tp_new_Enum(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_MemviewEnum_obj *p;
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_MemviewEnum_obj *)o);
  p->name = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_Enum(PyObject *o) {
  struct __pyx_MemviewEnum_obj *p = (struct __pyx_MemviewEnum_obj *)o;
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && !_PyGC_FINALIZED(o)) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->name);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_Enum(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_MemviewEnum_obj *p = (struct __pyx_MemviewEnum_obj *)o;
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_Enum(PyObject *o) {
  PyObject* tmp;
  struct __pyx_MemviewEnum_obj *p = (struct __pyx_MemviewEnum_obj *)o;
  tmp = ((PyObject*)p->name);
  p->name = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyMethodDef __pyx_methods_Enum[] = {
  {"__reduce_cython__", (PyCFunction)__pyx_pw___pyx_MemviewEnum_1__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw___pyx_MemviewEnum_3__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static PyTypeObject __pyx_type___pyx_MemviewEnum = {
  PyVarObject_HEAD_INIT(0, 0)
  "simplejpeg._jpeg.Enum",  
  sizeof(struct __pyx_MemviewEnum_obj),  
  0,  
  __pyx_tp_dealloc_Enum,  
  #if PY_VERSION_HEX < 0x030800b4
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0,  
  #endif
  0,  
  0,  
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION >= 3
  0,  
  #endif
  __pyx_MemviewEnum___repr__,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC,  
  0,  
  __pyx_tp_traverse_Enum,  
  __pyx_tp_clear_Enum,  
  0,  
  0,  
  0,  
  0,  
  __pyx_methods_Enum,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  __pyx_MemviewEnum___init__,  
  0,  
  __pyx_tp_new_Enum,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  #if PY_VERSION_HEX >= 0x030400a1
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b1 && (!CYTHON_COMPILING_IN_PYPY || PYPY_VERSION_NUM >= 0x07030800)
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0,  
  #endif
  #if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX >= 0x03090000 && PY_VERSION_HEX < 0x030a0000
  0,  
  #endif
};
static struct __pyx_vtabstruct_memoryview __pyx_vtable_memoryview;

static PyObject *__pyx_tp_new_memoryview(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_memoryview_obj *p;
  PyObject *o;
  if (likely((t->tp_flags & Py_TPFLAGS_IS_ABSTRACT) == 0)) {
    o = (*t->tp_alloc)(t, 0);
  } else {
    o = (PyObject *) PyBaseObject_Type.tp_new(t, __pyx_empty_tuple, 0);
  }
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_memoryview_obj *)o);
  p->__pyx_vtab = __pyx_vtabptr_memoryview;
  p->obj = Py_None; Py_INCREF(Py_None);
  p->_size = Py_None; Py_INCREF(Py_None);
  p->_array_interface = Py_None; Py_INCREF(Py_None);
  p->view.obj = NULL;
  if (unlikely(__pyx_memoryview___cinit__(o, a, k) < 0)) goto bad;
  return o;
  bad:
  Py_DECREF(o); o = 0;
  return NULL;
}

static void __pyx_tp_dealloc_memoryview(PyObject *o) {
  struct __pyx_memoryview_obj *p = (struct __pyx_memoryview_obj *)o;
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && !_PyGC_FINALIZED(o)) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  PyObject_GC_UnTrack(o);
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) + 1);
    __pyx_memoryview___dealloc__(o);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) - 1);
    PyErr_Restore(etype, eval, etb);
  }
  Py_CLEAR(p->obj);
  Py_CLEAR(p->_size);
  Py_CLEAR(p->_array_interface);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_memoryview(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_memoryview_obj *p = (struct __pyx_memoryview_obj *)o;
  if (p->obj) {
    e = (*v)(p->obj, a); if (e) return e;
  }
  if (p->_size) {
    e = (*v)(p->_size, a); if (e) return e;
  }
  if (p->_array_interface) {
    e = (*v)(p->_array_interface, a); if (e) return e;
  }
  if (p->view.obj) {
    e = (*v)(p->view.obj, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_memoryview(PyObject *o) {
  PyObject* tmp;
  struct __pyx_memoryview_obj *p = (struct __pyx_memoryview_obj *)o;
  tmp = ((PyObject*)p->obj);
  p->obj = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->_size);
  p->_size = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->_array_interface);
  p->_array_interface = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  Py_CLEAR(p->view.obj);
  return 0;
}
static PyObject *__pyx_sq_item_memoryview(PyObject *o, Py_ssize_t i) {
  PyObject *r;
  PyObject *x = PyInt_FromSsize_t(i); if(!x) return 0;
  r = Py_TYPE(o)->tp_as_mapping->mp_subscript(o, x);
  Py_DECREF(x);
  return r;
}

static int __pyx_mp_ass_subscript_memoryview(PyObject *o, PyObject *i, PyObject *v) {
  if (v) {
    return __pyx_memoryview___setitem__(o, i, v);
  }
  else {
    PyErr_Format(PyExc_NotImplementedError,
      "Subscript deletion not supported by %.200s", Py_TYPE(o)->tp_name);
    return -1;
  }
}

static PyObject *__pyx_getprop___pyx_memoryview_T(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_1T_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_base(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_4base_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_shape(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_5shape_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_strides(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_7strides_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_suboffsets(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_10suboffsets_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_ndim(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_4ndim_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_itemsize(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_8itemsize_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_nbytes(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_6nbytes_1__get__(o);
}

static PyObject *__pyx_getprop___pyx_memoryview_size(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_10memoryview_4size_1__get__(o);
}

static PyMethodDef __pyx_methods_memoryview[] = {
  {"is_c_contig", (PyCFunction)__pyx_memoryview_is_c_contig, METH_NOARGS, 0},
  {"is_f_contig", (PyCFunction)__pyx_memoryview_is_f_contig, METH_NOARGS, 0},
  {"copy", (PyCFunction)__pyx_memoryview_copy, METH_NOARGS, 0},
  {"copy_fortran", (PyCFunction)__pyx_memoryview_copy_fortran, METH_NOARGS, 0},
  {"__reduce_cython__", (PyCFunction)__pyx_pw___pyx_memoryview_1__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw___pyx_memoryview_3__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_memoryview[] = {
  {(char *)"T", __pyx_getprop___pyx_memoryview_T, 0, (char *)0, 0},
  {(char *)"base", __pyx_getprop___pyx_memoryview_base, 0, (char *)0, 0},
  {(char *)"shape", __pyx_getprop___pyx_memoryview_shape, 0, (char *)0, 0},
  {(char *)"strides", __pyx_getprop___pyx_memoryview_strides, 0, (char *)0, 0},
  {(char *)"suboffsets", __pyx_getprop___pyx_memoryview_suboffsets, 0, (char *)0, 0},
  {(char *)"ndim", __pyx_getprop___pyx_memoryview_ndim, 0, (char *)0, 0},
  {(char *)"itemsize", __pyx_getprop___pyx_memoryview_itemsize, 0, (char *)0, 0},
  {(char *)"nbytes", __pyx_getprop___pyx_memoryview_nbytes, 0, (char *)0, 0},
  {(char *)"size", __pyx_getprop___pyx_memoryview_size, 0, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PySequenceMethods __pyx_tp_as_sequence_memoryview = {
  __pyx_memoryview___len__,  
  0,  
  0,  
  __pyx_sq_item_memoryview,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
};

static PyMappingMethods __pyx_tp_as_mapping_memoryview = {
  __pyx_memoryview___len__,  
  __pyx_memoryview___getitem__,  
  __pyx_mp_ass_subscript_memoryview,  
};

static PyBufferProcs __pyx_tp_as_buffer_memoryview = {
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  __pyx_memoryview_getbuffer,  
  0,  
};

static PyTypeObject __pyx_type___pyx_memoryview = {
  PyVarObject_HEAD_INIT(0, 0)
  "simplejpeg._jpeg.memoryview",  
  sizeof(struct __pyx_memoryview_obj),  
  0,  
  __pyx_tp_dealloc_memoryview,  
  #if PY_VERSION_HEX < 0x030800b4
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0,  
  #endif
  0,  
  0,  
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION >= 3
  0,  
  #endif
  __pyx_memoryview___repr__,  
  0,  
  &__pyx_tp_as_sequence_memoryview,  
  &__pyx_tp_as_mapping_memoryview,  
  0,  
  0,  
  __pyx_memoryview___str__,  
  0,  
  0,  
  &__pyx_tp_as_buffer_memoryview,  
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC,  
  0,  
  __pyx_tp_traverse_memoryview,  
  __pyx_tp_clear_memoryview,  
  0,  
  0,  
  0,  
  0,  
  __pyx_methods_memoryview,  
  0,  
  __pyx_getsets_memoryview,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  __pyx_tp_new_memoryview,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  #if PY_VERSION_HEX >= 0x030400a1
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b1 && (!CYTHON_COMPILING_IN_PYPY || PYPY_VERSION_NUM >= 0x07030800)
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0,  
  #endif
  #if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX >= 0x03090000 && PY_VERSION_HEX < 0x030a0000
  0,  
  #endif
};
static struct __pyx_vtabstruct__memoryviewslice __pyx_vtable__memoryviewslice;

static PyObject *__pyx_tp_new__memoryviewslice(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_memoryviewslice_obj *p;
  PyObject *o = __pyx_tp_new_memoryview(t, a, k);
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_memoryviewslice_obj *)o);
  p->__pyx_base.__pyx_vtab = (struct __pyx_vtabstruct_memoryview*)__pyx_vtabptr__memoryviewslice;
  p->from_object = Py_None; Py_INCREF(Py_None);
  p->from_slice.memview = NULL;
  return o;
}

static void __pyx_tp_dealloc__memoryviewslice(PyObject *o) {
  struct __pyx_memoryviewslice_obj *p = (struct __pyx_memoryviewslice_obj *)o;
  #if CYTHON_USE_TP_FINALIZE
  if (unlikely(PyType_HasFeature(Py_TYPE(o), Py_TPFLAGS_HAVE_FINALIZE) && Py_TYPE(o)->tp_finalize) && !_PyGC_FINALIZED(o)) {
    if (PyObject_CallFinalizerFromDealloc(o)) return;
  }
  #endif
  PyObject_GC_UnTrack(o);
  {
    PyObject *etype, *eval, *etb;
    PyErr_Fetch(&etype, &eval, &etb);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) + 1);
    __pyx_memoryviewslice___dealloc__(o);
    __Pyx_SET_REFCNT(o, Py_REFCNT(o) - 1);
    PyErr_Restore(etype, eval, etb);
  }
  Py_CLEAR(p->from_object);
  PyObject_GC_Track(o);
  __pyx_tp_dealloc_memoryview(o);
}

static int __pyx_tp_traverse__memoryviewslice(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_memoryviewslice_obj *p = (struct __pyx_memoryviewslice_obj *)o;
  e = __pyx_tp_traverse_memoryview(o, v, a); if (e) return e;
  if (p->from_object) {
    e = (*v)(p->from_object, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear__memoryviewslice(PyObject *o) {
  PyObject* tmp;
  struct __pyx_memoryviewslice_obj *p = (struct __pyx_memoryviewslice_obj *)o;
  __pyx_tp_clear_memoryview(o);
  tmp = ((PyObject*)p->from_object);
  p->from_object = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  __PYX_XDEC_MEMVIEW(&p->from_slice, 1);
  return 0;
}

static PyObject *__pyx_getprop___pyx_memoryviewslice_base(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_15View_dot_MemoryView_16_memoryviewslice_4base_1__get__(o);
}

static PyMethodDef __pyx_methods__memoryviewslice[] = {
  {"__reduce_cython__", (PyCFunction)__pyx_pw___pyx_memoryviewslice_1__reduce_cython__, METH_NOARGS, 0},
  {"__setstate_cython__", (PyCFunction)__pyx_pw___pyx_memoryviewslice_3__setstate_cython__, METH_O, 0},
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets__memoryviewslice[] = {
  {(char *)"base", __pyx_getprop___pyx_memoryviewslice_base, 0, (char *)0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type___pyx_memoryviewslice = {
  PyVarObject_HEAD_INIT(0, 0)
  "simplejpeg._jpeg._memoryviewslice",  
  sizeof(struct __pyx_memoryviewslice_obj),  
  0,  
  __pyx_tp_dealloc__memoryviewslice,  
  #if PY_VERSION_HEX < 0x030800b4
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4
  0,  
  #endif
  0,  
  0,  
  #if PY_MAJOR_VERSION < 3
  0,  
  #endif
  #if PY_MAJOR_VERSION >= 3
  0,  
  #endif
  #if CYTHON_COMPILING_IN_PYPY
  __pyx_memoryview___repr__,  
  #else
  0,  
  #endif
  0,  
  0,  
  0,  
  0,  
  0,  
  #if CYTHON_COMPILING_IN_PYPY
  __pyx_memoryview___str__,  
  #else
  0,  
  #endif
  0,  
  0,  
  0,  
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC,  
  "Internal class for passing memoryview slices to Python",  
  __pyx_tp_traverse__memoryviewslice,  
  __pyx_tp_clear__memoryviewslice,  
  0,  
  0,  
  0,  
  0,  
  __pyx_methods__memoryviewslice,  
  0,  
  __pyx_getsets__memoryviewslice,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  __pyx_tp_new__memoryviewslice,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  0,  
  #if PY_VERSION_HEX >= 0x030400a1
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b1 && (!CYTHON_COMPILING_IN_PYPY || PYPY_VERSION_NUM >= 0x07030800)
  0,  
  #endif
  #if PY_VERSION_HEX >= 0x030800b4 && PY_VERSION_HEX < 0x03090000
  0,  
  #endif
  #if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX >= 0x03090000 && PY_VERSION_HEX < 0x030a0000
  0,  
  #endif
};

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
#if CYTHON_PEP489_MULTI_PHASE_INIT
static PyObject* __pyx_pymod_create(PyObject *spec, PyModuleDef *def);  
static int __pyx_pymod_exec__jpeg(PyObject* module);  
static PyModuleDef_Slot __pyx_moduledef_slots[] = {
  {Py_mod_create, (void*)__pyx_pymod_create},
  {Py_mod_exec, (void*)__pyx_pymod_exec__jpeg},
  {0, NULL}
};
#endif

static struct PyModuleDef __pyx_moduledef = {
    PyModuleDef_HEAD_INIT,
    "_jpeg",
    0,  
  #if CYTHON_PEP489_MULTI_PHASE_INIT
    0,  
  #else
    -1,  
  #endif
    __pyx_methods  ,
  #if CYTHON_PEP489_MULTI_PHASE_INIT
    __pyx_moduledef_slots,  
  #else
    NULL,  
  #endif
    NULL,  
    NULL,  
    NULL  
};
#endif
#ifndef CYTHON_SMALL_CODE
#if defined(__clang__)
    #define CYTHON_SMALL_CODE
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
    #define CYTHON_SMALL_CODE __attribute__((cold))
#else
    #define CYTHON_SMALL_CODE
#endif
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_kp_u_411, __pyx_k_411, sizeof(__pyx_k_411), 0, 1, 0, 0},
  {&__pyx_kp_u_420, __pyx_k_420, sizeof(__pyx_k_420), 0, 1, 0, 0},
  {&__pyx_kp_u_422, __pyx_k_422, sizeof(__pyx_k_422), 0, 1, 0, 0},
  {&__pyx_kp_u_440, __pyx_k_440, sizeof(__pyx_k_440), 0, 1, 0, 0},
  {&__pyx_kp_u_444, __pyx_k_444, sizeof(__pyx_k_444), 0, 1, 0, 0},
  {&__pyx_n_u_ABGR, __pyx_k_ABGR, sizeof(__pyx_k_ABGR), 0, 1, 0, 1},
  {&__pyx_n_u_ARGB, __pyx_k_ARGB, sizeof(__pyx_k_ARGB), 0, 1, 0, 1},
  {&__pyx_n_s_ASCII, __pyx_k_ASCII, sizeof(__pyx_k_ASCII), 0, 0, 1, 1},
  {&__pyx_n_u_BGR, __pyx_k_BGR, sizeof(__pyx_k_BGR), 0, 1, 0, 1},
  {&__pyx_n_u_BGRA, __pyx_k_BGRA, sizeof(__pyx_k_BGRA), 0, 1, 0, 1},
  {&__pyx_n_u_BGRX, __pyx_k_BGRX, sizeof(__pyx_k_BGRX), 0, 1, 0, 1},
  {&__pyx_kp_s_Buffer_view_does_not_expose_stri, __pyx_k_Buffer_view_does_not_expose_stri, sizeof(__pyx_k_Buffer_view_does_not_expose_stri), 0, 0, 1, 0},
  {&__pyx_n_u_CMYK, __pyx_k_CMYK, sizeof(__pyx_k_CMYK), 0, 1, 0, 1},
  {&__pyx_kp_s_Can_only_create_a_buffer_that_is, __pyx_k_Can_only_create_a_buffer_that_is, sizeof(__pyx_k_Can_only_create_a_buffer_that_is), 0, 0, 1, 0},
  {&__pyx_kp_s_Cannot_assign_to_read_only_memor, __pyx_k_Cannot_assign_to_read_only_memor, sizeof(__pyx_k_Cannot_assign_to_read_only_memor), 0, 0, 1, 0},
  {&__pyx_kp_s_Cannot_create_writable_memory_vi, __pyx_k_Cannot_create_writable_memory_vi, sizeof(__pyx_k_Cannot_create_writable_memory_vi), 0, 0, 1, 0},
  {&__pyx_kp_s_Cannot_index_with_type_s, __pyx_k_Cannot_index_with_type_s, sizeof(__pyx_k_Cannot_index_with_type_s), 0, 0, 1, 0},
  {&__pyx_n_s_Ellipsis, __pyx_k_Ellipsis, sizeof(__pyx_k_Ellipsis), 0, 0, 1, 1},
  {&__pyx_kp_s_Empty_shape_tuple_for_cython_arr, __pyx_k_Empty_shape_tuple_for_cython_arr, sizeof(__pyx_k_Empty_shape_tuple_for_cython_arr), 0, 0, 1, 0},
  {&__pyx_n_u_Gray, __pyx_k_Gray, sizeof(__pyx_k_Gray), 0, 1, 0, 1},
  {&__pyx_n_s_ImportError, __pyx_k_ImportError, sizeof(__pyx_k_ImportError), 0, 0, 1, 1},
  {&__pyx_kp_s_Incompatible_checksums_0x_x_vs_0, __pyx_k_Incompatible_checksums_0x_x_vs_0, sizeof(__pyx_k_Incompatible_checksums_0x_x_vs_0), 0, 0, 1, 0},
  {&__pyx_n_s_IndexError, __pyx_k_IndexError, sizeof(__pyx_k_IndexError), 0, 0, 1, 1},
  {&__pyx_kp_s_Indirect_dimensions_not_supporte, __pyx_k_Indirect_dimensions_not_supporte, sizeof(__pyx_k_Indirect_dimensions_not_supporte), 0, 0, 1, 0},
  {&__pyx_kp_s_Invalid_mode_expected_c_or_fortr, __pyx_k_Invalid_mode_expected_c_or_fortr, sizeof(__pyx_k_Invalid_mode_expected_c_or_fortr), 0, 0, 1, 0},
  {&__pyx_kp_s_Invalid_shape_in_axis_d_d, __pyx_k_Invalid_shape_in_axis_d_d, sizeof(__pyx_k_Invalid_shape_in_axis_d_d), 0, 0, 1, 0},
  {&__pyx_n_s_MemoryError, __pyx_k_MemoryError, sizeof(__pyx_k_MemoryError), 0, 0, 1, 1},
  {&__pyx_kp_s_MemoryView_of_r_at_0x_x, __pyx_k_MemoryView_of_r_at_0x_x, sizeof(__pyx_k_MemoryView_of_r_at_0x_x), 0, 0, 1, 0},
  {&__pyx_kp_s_MemoryView_of_r_object, __pyx_k_MemoryView_of_r_object, sizeof(__pyx_k_MemoryView_of_r_object), 0, 0, 1, 0},
  {&__pyx_kp_u_None, __pyx_k_None, sizeof(__pyx_k_None), 0, 1, 0, 0},
  {&__pyx_n_b_O, __pyx_k_O, sizeof(__pyx_k_O), 0, 0, 0, 1},
  {&__pyx_kp_s_Out_of_bounds_on_buffer_access_a, __pyx_k_Out_of_bounds_on_buffer_access_a, sizeof(__pyx_k_Out_of_bounds_on_buffer_access_a), 0, 0, 1, 0},
  {&__pyx_n_s_PickleError, __pyx_k_PickleError, sizeof(__pyx_k_PickleError), 0, 0, 1, 1},
  {&__pyx_n_u_RGB, __pyx_k_RGB, sizeof(__pyx_k_RGB), 0, 1, 0, 1},
  {&__pyx_n_u_RGBA, __pyx_k_RGBA, sizeof(__pyx_k_RGBA), 0, 1, 0, 1},
  {&__pyx_n_u_RGBX, __pyx_k_RGBX, sizeof(__pyx_k_RGBX), 0, 1, 0, 1},
  {&__pyx_n_s_RuntimeError, __pyx_k_RuntimeError, sizeof(__pyx_k_RuntimeError), 0, 0, 1, 1},
  {&__pyx_n_s_TypeError, __pyx_k_TypeError, sizeof(__pyx_k_TypeError), 0, 0, 1, 1},
  {&__pyx_kp_s_Unable_to_convert_item_to_object, __pyx_k_Unable_to_convert_item_to_object, sizeof(__pyx_k_Unable_to_convert_item_to_object), 0, 0, 1, 0},
  {&__pyx_n_s_ValueError, __pyx_k_ValueError, sizeof(__pyx_k_ValueError), 0, 0, 1, 1},
  {&__pyx_n_s_View_MemoryView, __pyx_k_View_MemoryView, sizeof(__pyx_k_View_MemoryView), 0, 0, 1, 1},
  {&__pyx_n_u_XBGR, __pyx_k_XBGR, sizeof(__pyx_k_XBGR), 0, 1, 0, 1},
  {&__pyx_n_u_XRGB, __pyx_k_XRGB, sizeof(__pyx_k_XRGB), 0, 1, 0, 1},
  {&__pyx_n_u_YCCK, __pyx_k_YCCK, sizeof(__pyx_k_YCCK), 0, 1, 0, 1},
  {&__pyx_n_u_YCbCr, __pyx_k_YCbCr, sizeof(__pyx_k_YCbCr), 0, 1, 0, 1},
  {&__pyx_kp_u__3, __pyx_k__3, sizeof(__pyx_k__3), 0, 1, 0, 0},
  {&__pyx_n_s_allocate_buffer, __pyx_k_allocate_buffer, sizeof(__pyx_k_allocate_buffer), 0, 0, 1, 1},
  {&__pyx_n_s_append, __pyx_k_append, sizeof(__pyx_k_append), 0, 0, 1, 1},
  {&__pyx_n_s_base, __pyx_k_base, sizeof(__pyx_k_base), 0, 0, 1, 1},
  {&__pyx_n_s_buffer, __pyx_k_buffer, sizeof(__pyx_k_buffer), 0, 0, 1, 1},
  {&__pyx_kp_u_buffer_object_must_support_buffe, __pyx_k_buffer_object_must_support_buffe, sizeof(__pyx_k_buffer_object_must_support_buffe), 0, 1, 0, 0},
  {&__pyx_n_s_bufferlen, __pyx_k_bufferlen, sizeof(__pyx_k_bufferlen), 0, 0, 1, 1},
  {&__pyx_kp_u_byte_buffer_is_too_small_to_dec, __pyx_k_byte_buffer_is_too_small_to_dec, sizeof(__pyx_k_byte_buffer_is_too_small_to_dec), 0, 1, 0, 0},
  {&__pyx_n_s_c, __pyx_k_c, sizeof(__pyx_k_c), 0, 0, 1, 1},
  {&__pyx_n_u_c, __pyx_k_c, sizeof(__pyx_k_c), 0, 1, 0, 1},
  {&__pyx_n_s_channels, __pyx_k_channels, sizeof(__pyx_k_channels), 0, 0, 1, 1},
  {&__pyx_kp_u_channels_does_not_match_given_c, __pyx_k_channels_does_not_match_given_c, sizeof(__pyx_k_channels_does_not_match_given_c), 0, 1, 0, 0},
  {&__pyx_n_s_class, __pyx_k_class, sizeof(__pyx_k_class), 0, 0, 1, 1},
  {&__pyx_n_s_cline_in_traceback, __pyx_k_cline_in_traceback, sizeof(__pyx_k_cline_in_traceback), 0, 0, 1, 1},
  {&__pyx_n_s_colorspace, __pyx_k_colorspace, sizeof(__pyx_k_colorspace), 0, 0, 1, 1},
  {&__pyx_n_s_colorspace_2, __pyx_k_colorspace_2, sizeof(__pyx_k_colorspace_2), 0, 0, 1, 1},
  {&__pyx_n_s_colorsubsampling, __pyx_k_colorsubsampling, sizeof(__pyx_k_colorsubsampling), 0, 0, 1, 1},
  {&__pyx_n_s_colorsubsampling_2, __pyx_k_colorsubsampling_2, sizeof(__pyx_k_colorsubsampling_2), 0, 0, 1, 1},
  {&__pyx_kp_s_contiguous_and_direct, __pyx_k_contiguous_and_direct, sizeof(__pyx_k_contiguous_and_direct), 0, 0, 1, 0},
  {&__pyx_kp_s_contiguous_and_indirect, __pyx_k_contiguous_and_indirect, sizeof(__pyx_k_contiguous_and_indirect), 0, 0, 1, 0},
  {&__pyx_kp_u_could_not_create_JPEG_decoder, __pyx_k_could_not_create_JPEG_decoder, sizeof(__pyx_k_could_not_create_JPEG_decoder), 0, 1, 0, 0},
  {&__pyx_kp_u_could_not_create_JPEG_encoder, __pyx_k_could_not_create_JPEG_encoder, sizeof(__pyx_k_could_not_create_JPEG_encoder), 0, 1, 0, 0},
  {&__pyx_n_u_d, __pyx_k_d, sizeof(__pyx_k_d), 0, 1, 0, 1},
  {&__pyx_n_s_data, __pyx_k_data, sizeof(__pyx_k_data), 0, 0, 1, 1},
  {&__pyx_n_s_data_len, __pyx_k_data_len, sizeof(__pyx_k_data_len), 0, 0, 1, 1},
  {&__pyx_n_s_data_p, __pyx_k_data_p, sizeof(__pyx_k_data_p), 0, 0, 1, 1},
  {&__pyx_n_s_decode_jpeg, __pyx_k_decode_jpeg, sizeof(__pyx_k_decode_jpeg), 0, 0, 1, 1},
  {&__pyx_n_s_decode_jpeg_header, __pyx_k_decode_jpeg_header, sizeof(__pyx_k_decode_jpeg_header), 0, 0, 1, 1},
  {&__pyx_n_s_decoder, __pyx_k_decoder, sizeof(__pyx_k_decoder), 0, 0, 1, 1},
  {&__pyx_n_s_dict, __pyx_k_dict, sizeof(__pyx_k_dict), 0, 0, 1, 1},
  {&__pyx_n_s_dims, __pyx_k_dims, sizeof(__pyx_k_dims), 0, 0, 1, 1},
  {&__pyx_n_s_dtype_is_object, __pyx_k_dtype_is_object, sizeof(__pyx_k_dtype_is_object), 0, 0, 1, 1},
  {&__pyx_n_s_encode, __pyx_k_encode, sizeof(__pyx_k_encode), 0, 0, 1, 1},
  {&__pyx_n_s_encode_jpeg, __pyx_k_encode_jpeg, sizeof(__pyx_k_encode_jpeg), 0, 0, 1, 1},
  {&__pyx_n_s_encoder, __pyx_k_encoder, sizeof(__pyx_k_encoder), 0, 0, 1, 1},
  {&__pyx_n_s_enumerate, __pyx_k_enumerate, sizeof(__pyx_k_enumerate), 0, 0, 1, 1},
  {&__pyx_n_s_error, __pyx_k_error, sizeof(__pyx_k_error), 0, 0, 1, 1},
  {&__pyx_n_s_fastdct, __pyx_k_fastdct, sizeof(__pyx_k_fastdct), 0, 0, 1, 1},
  {&__pyx_n_s_fastupsample, __pyx_k_fastupsample, sizeof(__pyx_k_fastupsample), 0, 0, 1, 1},
  {&__pyx_n_s_flags, __pyx_k_flags, sizeof(__pyx_k_flags), 0, 0, 1, 1},
  {&__pyx_n_s_format, __pyx_k_format, sizeof(__pyx_k_format), 0, 0, 1, 1},
  {&__pyx_n_s_fortran, __pyx_k_fortran, sizeof(__pyx_k_fortran), 0, 0, 1, 1},
  {&__pyx_n_u_fortran, __pyx_k_fortran, sizeof(__pyx_k_fortran), 0, 1, 0, 1},
  {&__pyx_n_s_frombuffer, __pyx_k_frombuffer, sizeof(__pyx_k_frombuffer), 0, 0, 1, 1},
  {&__pyx_n_s_getstate, __pyx_k_getstate, sizeof(__pyx_k_getstate), 0, 0, 1, 1},
  {&__pyx_kp_s_got_differing_extents_in_dimensi, __pyx_k_got_differing_extents_in_dimensi, sizeof(__pyx_k_got_differing_extents_in_dimensi), 0, 0, 1, 0},
  {&__pyx_n_s_height, __pyx_k_height, sizeof(__pyx_k_height), 0, 0, 1, 1},
  {&__pyx_n_s_i, __pyx_k_i, sizeof(__pyx_k_i), 0, 0, 1, 1},
  {&__pyx_n_s_id, __pyx_k_id, sizeof(__pyx_k_id), 0, 0, 1, 1},
  {&__pyx_kp_u_image, __pyx_k_image, sizeof(__pyx_k_image), 0, 1, 0, 0},
  {&__pyx_n_s_image_2, __pyx_k_image_2, sizeof(__pyx_k_image_2), 0, 0, 1, 1},
  {&__pyx_kp_u_image_must_be_C_contiguous, __pyx_k_image_must_be_C_contiguous, sizeof(__pyx_k_image_must_be_C_contiguous), 0, 1, 0, 0},
  {&__pyx_n_s_image_p, __pyx_k_image_p, sizeof(__pyx_k_image_p), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_is_cmyk, __pyx_k_is_cmyk, sizeof(__pyx_k_is_cmyk), 0, 0, 1, 1},
  {&__pyx_n_s_itemsize, __pyx_k_itemsize, sizeof(__pyx_k_itemsize), 0, 0, 1, 1},
  {&__pyx_kp_s_itemsize_0_for_cython_array, __pyx_k_itemsize_0_for_cython_array, sizeof(__pyx_k_itemsize_0_for_cython_array), 0, 0, 1, 0},
  {&__pyx_n_s_jpeg, __pyx_k_jpeg, sizeof(__pyx_k_jpeg), 0, 0, 1, 1},
  {&__pyx_n_s_jpegColorspace, __pyx_k_jpegColorspace, sizeof(__pyx_k_jpegColorspace), 0, 0, 1, 1},
  {&__pyx_n_s_jpegSubsamp, __pyx_k_jpegSubsamp, sizeof(__pyx_k_jpegSubsamp), 0, 0, 1, 1},
  {&__pyx_n_s_jpegbuf, __pyx_k_jpegbuf, sizeof(__pyx_k_jpegbuf), 0, 0, 1, 1},
  {&__pyx_n_s_jpegbufbuf, __pyx_k_jpegbufbuf, sizeof(__pyx_k_jpegbufbuf), 0, 0, 1, 1},
  {&__pyx_n_s_jpegsize, __pyx_k_jpegsize, sizeof(__pyx_k_jpegsize), 0, 0, 1, 1},
  {&__pyx_n_s_lower, __pyx_k_lower, sizeof(__pyx_k_lower), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_memview, __pyx_k_memview, sizeof(__pyx_k_memview), 0, 0, 1, 1},
  {&__pyx_n_s_min_factor, __pyx_k_min_factor, sizeof(__pyx_k_min_factor), 0, 0, 1, 1},
  {&__pyx_n_s_min_height, __pyx_k_min_height, sizeof(__pyx_k_min_height), 0, 0, 1, 1},
  {&__pyx_n_s_min_width, __pyx_k_min_width, sizeof(__pyx_k_min_width), 0, 0, 1, 1},
  {&__pyx_n_s_mode, __pyx_k_mode, sizeof(__pyx_k_mode), 0, 0, 1, 1},
  {&__pyx_n_s_msg, __pyx_k_msg, sizeof(__pyx_k_msg), 0, 0, 1, 1},
  {&__pyx_n_s_name, __pyx_k_name, sizeof(__pyx_k_name), 0, 0, 1, 1},
  {&__pyx_n_s_name_2, __pyx_k_name_2, sizeof(__pyx_k_name_2), 0, 0, 1, 1},
  {&__pyx_n_s_ndim, __pyx_k_ndim, sizeof(__pyx_k_ndim), 0, 0, 1, 1},
  {&__pyx_n_s_new, __pyx_k_new, sizeof(__pyx_k_new), 0, 0, 1, 1},
  {&__pyx_kp_s_no_default___reduce___due_to_non, __pyx_k_no_default___reduce___due_to_non, sizeof(__pyx_k_no_default___reduce___due_to_non), 0, 0, 1, 0},
  {&__pyx_n_s_np, __pyx_k_np, sizeof(__pyx_k_np), 0, 0, 1, 1},
  {&__pyx_n_s_numpy, __pyx_k_numpy, sizeof(__pyx_k_numpy), 0, 0, 1, 1},
  {&__pyx_kp_u_numpy_core_multiarray_failed_to, __pyx_k_numpy_core_multiarray_failed_to, sizeof(__pyx_k_numpy_core_multiarray_failed_to), 0, 1, 0, 0},
  {&__pyx_kp_u_numpy_core_umath_failed_to_impor, __pyx_k_numpy_core_umath_failed_to_impor, sizeof(__pyx_k_numpy_core_umath_failed_to_impor), 0, 1, 0, 0},
  {&__pyx_n_s_obj, __pyx_k_obj, sizeof(__pyx_k_obj), 0, 0, 1, 1},
  {&__pyx_n_s_out, __pyx_k_out, sizeof(__pyx_k_out), 0, 0, 1, 1},
  {&__pyx_n_s_out_p, __pyx_k_out_p, sizeof(__pyx_k_out_p), 0, 0, 1, 1},
  {&__pyx_n_s_outlen, __pyx_k_outlen, sizeof(__pyx_k_outlen), 0, 0, 1, 1},
  {&__pyx_n_s_output_colorspace, __pyx_k_output_colorspace, sizeof(__pyx_k_output_colorspace), 0, 0, 1, 1},
  {&__pyx_n_s_pack, __pyx_k_pack, sizeof(__pyx_k_pack), 0, 0, 1, 1},
  {&__pyx_n_s_pf, __pyx_k_pf, sizeof(__pyx_k_pf), 0, 0, 1, 1},
  {&__pyx_n_s_pickle, __pyx_k_pickle, sizeof(__pyx_k_pickle), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_PickleError, __pyx_k_pyx_PickleError, sizeof(__pyx_k_pyx_PickleError), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_checksum, __pyx_k_pyx_checksum, sizeof(__pyx_k_pyx_checksum), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_getbuffer, __pyx_k_pyx_getbuffer, sizeof(__pyx_k_pyx_getbuffer), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_result, __pyx_k_pyx_result, sizeof(__pyx_k_pyx_result), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_state, __pyx_k_pyx_state, sizeof(__pyx_k_pyx_state), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_type, __pyx_k_pyx_type, sizeof(__pyx_k_pyx_type), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_unpickle_Enum, __pyx_k_pyx_unpickle_Enum, sizeof(__pyx_k_pyx_unpickle_Enum), 0, 0, 1, 1},
  {&__pyx_n_s_pyx_vtable, __pyx_k_pyx_vtable, sizeof(__pyx_k_pyx_vtable), 0, 0, 1, 1},
  {&__pyx_n_s_quality, __pyx_k_quality, sizeof(__pyx_k_quality), 0, 0, 1, 1},
  {&__pyx_n_s_range, __pyx_k_range, sizeof(__pyx_k_range), 0, 0, 1, 1},
  {&__pyx_n_s_reduce, __pyx_k_reduce, sizeof(__pyx_k_reduce), 0, 0, 1, 1},
  {&__pyx_n_s_reduce_cython, __pyx_k_reduce_cython, sizeof(__pyx_k_reduce_cython), 0, 0, 1, 1},
  {&__pyx_n_s_reduce_ex, __pyx_k_reduce_ex, sizeof(__pyx_k_reduce_ex), 0, 0, 1, 1},
  {&__pyx_n_s_reshape, __pyx_k_reshape, sizeof(__pyx_k_reshape), 0, 0, 1, 1},
  {&__pyx_n_s_retcode, __pyx_k_retcode, sizeof(__pyx_k_retcode), 0, 0, 1, 1},
  {&__pyx_n_u_rgb, __pyx_k_rgb, sizeof(__pyx_k_rgb), 0, 1, 0, 1},
  {&__pyx_n_s_setstate, __pyx_k_setstate, sizeof(__pyx_k_setstate), 0, 0, 1, 1},
  {&__pyx_n_s_setstate_cython, __pyx_k_setstate_cython, sizeof(__pyx_k_setstate_cython), 0, 0, 1, 1},
  {&__pyx_n_s_shape, __pyx_k_shape, sizeof(__pyx_k_shape), 0, 0, 1, 1},
  {&__pyx_n_s_simplejpeg__jpeg, __pyx_k_simplejpeg__jpeg, sizeof(__pyx_k_simplejpeg__jpeg), 0, 0, 1, 1},
  {&__pyx_kp_s_simplejpeg__jpeg_pyx, __pyx_k_simplejpeg__jpeg_pyx, sizeof(__pyx_k_simplejpeg__jpeg_pyx), 0, 0, 1, 0},
  {&__pyx_n_s_size, __pyx_k_size, sizeof(__pyx_k_size), 0, 0, 1, 1},
  {&__pyx_n_s_start, __pyx_k_start, sizeof(__pyx_k_start), 0, 0, 1, 1},
  {&__pyx_n_s_step, __pyx_k_step, sizeof(__pyx_k_step), 0, 0, 1, 1},
  {&__pyx_n_s_stop, __pyx_k_stop, sizeof(__pyx_k_stop), 0, 0, 1, 1},
  {&__pyx_n_s_strict, __pyx_k_strict, sizeof(__pyx_k_strict), 0, 0, 1, 1},
  {&__pyx_kp_s_strided_and_direct, __pyx_k_strided_and_direct, sizeof(__pyx_k_strided_and_direct), 0, 0, 1, 0},
  {&__pyx_kp_s_strided_and_direct_or_indirect, __pyx_k_strided_and_direct_or_indirect, sizeof(__pyx_k_strided_and_direct_or_indirect), 0, 0, 1, 0},
  {&__pyx_kp_s_strided_and_indirect, __pyx_k_strided_and_indirect, sizeof(__pyx_k_strided_and_indirect), 0, 0, 1, 0},
  {&__pyx_kp_s_stringsource, __pyx_k_stringsource, sizeof(__pyx_k_stringsource), 0, 0, 1, 0},
  {&__pyx_n_s_struct, __pyx_k_struct, sizeof(__pyx_k_struct), 0, 0, 1, 1},
  {&__pyx_n_s_sub, __pyx_k_sub, sizeof(__pyx_k_sub), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_test_2, __pyx_k_test_2, sizeof(__pyx_k_test_2), 0, 0, 1, 1},
  {&__pyx_n_s_tmp, __pyx_k_tmp, sizeof(__pyx_k_tmp), 0, 0, 1, 1},
  {&__pyx_n_s_tmp_colorspace, __pyx_k_tmp_colorspace, sizeof(__pyx_k_tmp_colorspace), 0, 0, 1, 1},
  {&__pyx_n_s_tmp_p, __pyx_k_tmp_p, sizeof(__pyx_k_tmp_p), 0, 0, 1, 1},
  {&__pyx_n_s_tmplen, __pyx_k_tmplen, sizeof(__pyx_k_tmplen), 0, 0, 1, 1},
  {&__pyx_n_s_uint8, __pyx_k_uint8, sizeof(__pyx_k_uint8), 0, 0, 1, 1},
  {&__pyx_kp_s_unable_to_allocate_array_data, __pyx_k_unable_to_allocate_array_data, sizeof(__pyx_k_unable_to_allocate_array_data), 0, 0, 1, 0},
  {&__pyx_kp_s_unable_to_allocate_shape_and_str, __pyx_k_unable_to_allocate_shape_and_str, sizeof(__pyx_k_unable_to_allocate_shape_and_str), 0, 0, 1, 0},
  {&__pyx_n_u_unknown, __pyx_k_unknown, sizeof(__pyx_k_unknown), 0, 1, 0, 1},
  {&__pyx_kp_u_unknown_JPEG_error, __pyx_k_unknown_JPEG_error, sizeof(__pyx_k_unknown_JPEG_error), 0, 1, 0, 0},
  {&__pyx_n_s_unpack, __pyx_k_unpack, sizeof(__pyx_k_unpack), 0, 0, 1, 1},
  {&__pyx_n_s_update, __pyx_k_update, sizeof(__pyx_k_update), 0, 0, 1, 1},
  {&__pyx_n_s_upper, __pyx_k_upper, sizeof(__pyx_k_upper), 0, 0, 1, 1},
  {&__pyx_n_s_view, __pyx_k_view, sizeof(__pyx_k_view), 0, 0, 1, 1},
  {&__pyx_n_s_width, __pyx_k_width, sizeof(__pyx_k_width), 0, 0, 1, 1},
  {&__pyx_n_s_zip, __pyx_k_zip, sizeof(__pyx_k_zip), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static CYTHON_SMALL_CODE int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_zip = __Pyx_GetBuiltinName(__pyx_n_s_zip); if (!__pyx_builtin_zip) __PYX_ERR(0, 113, __pyx_L1_error)
  __pyx_builtin_range = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_range) __PYX_ERR(0, 180, __pyx_L1_error)
  __pyx_builtin_RuntimeError = __Pyx_GetBuiltinName(__pyx_n_s_RuntimeError); if (!__pyx_builtin_RuntimeError) __PYX_ERR(0, 232, __pyx_L1_error)
  __pyx_builtin_ValueError = __Pyx_GetBuiltinName(__pyx_n_s_ValueError); if (!__pyx_builtin_ValueError) __PYX_ERR(0, 246, __pyx_L1_error)
  __pyx_builtin_ImportError = __Pyx_GetBuiltinName(__pyx_n_s_ImportError); if (!__pyx_builtin_ImportError) __PYX_ERR(1, 944, __pyx_L1_error)
  __pyx_builtin_MemoryError = __Pyx_GetBuiltinName(__pyx_n_s_MemoryError); if (!__pyx_builtin_MemoryError) __PYX_ERR(2, 149, __pyx_L1_error)
  __pyx_builtin_enumerate = __Pyx_GetBuiltinName(__pyx_n_s_enumerate); if (!__pyx_builtin_enumerate) __PYX_ERR(2, 152, __pyx_L1_error)
  __pyx_builtin_TypeError = __Pyx_GetBuiltinName(__pyx_n_s_TypeError); if (!__pyx_builtin_TypeError) __PYX_ERR(2, 2, __pyx_L1_error)
  __pyx_builtin_Ellipsis = __Pyx_GetBuiltinName(__pyx_n_s_Ellipsis); if (!__pyx_builtin_Ellipsis) __PYX_ERR(2, 406, __pyx_L1_error)
  __pyx_builtin_id = __Pyx_GetBuiltinName(__pyx_n_s_id); if (!__pyx_builtin_id) __PYX_ERR(2, 615, __pyx_L1_error)
  __pyx_builtin_IndexError = __Pyx_GetBuiltinName(__pyx_n_s_IndexError); if (!__pyx_builtin_IndexError) __PYX_ERR(2, 834, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static CYTHON_SMALL_CODE int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

   
  __pyx_tuple_ = PyTuple_Pack(1, __pyx_kp_u_could_not_create_JPEG_decoder); if (unlikely(!__pyx_tuple_)) __PYX_ERR(0, 232, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple_);
  __Pyx_GIVEREF(__pyx_tuple_);

   
  __pyx_tuple__2 = PyTuple_Pack(1, __pyx_kp_u_buffer_object_must_support_buffe); if (unlikely(!__pyx_tuple__2)) __PYX_ERR(0, 360, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__2);
  __Pyx_GIVEREF(__pyx_tuple__2);

   
  __pyx_tuple__4 = PyTuple_Pack(1, __pyx_kp_u_image_must_be_C_contiguous); if (unlikely(!__pyx_tuple__4)) __PYX_ERR(0, 453, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__4);
  __Pyx_GIVEREF(__pyx_tuple__4);

   
  __pyx_tuple__5 = PyTuple_Pack(1, __pyx_kp_u_could_not_create_JPEG_encoder); if (unlikely(!__pyx_tuple__5)) __PYX_ERR(0, 474, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__5);
  __Pyx_GIVEREF(__pyx_tuple__5);

   
  __pyx_tuple__6 = PyTuple_Pack(1, __pyx_kp_u_numpy_core_multiarray_failed_to); if (unlikely(!__pyx_tuple__6)) __PYX_ERR(1, 944, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__6);
  __Pyx_GIVEREF(__pyx_tuple__6);

   
  __pyx_tuple__7 = PyTuple_Pack(1, __pyx_kp_u_numpy_core_umath_failed_to_impor); if (unlikely(!__pyx_tuple__7)) __PYX_ERR(1, 950, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__7);
  __Pyx_GIVEREF(__pyx_tuple__7);

   
  __pyx_tuple__8 = PyTuple_Pack(1, __pyx_kp_s_Empty_shape_tuple_for_cython_arr); if (unlikely(!__pyx_tuple__8)) __PYX_ERR(2, 134, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__8);
  __Pyx_GIVEREF(__pyx_tuple__8);

   
  __pyx_tuple__9 = PyTuple_Pack(1, __pyx_kp_s_itemsize_0_for_cython_array); if (unlikely(!__pyx_tuple__9)) __PYX_ERR(2, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__9);
  __Pyx_GIVEREF(__pyx_tuple__9);

   
  __pyx_tuple__10 = PyTuple_Pack(1, __pyx_kp_s_unable_to_allocate_shape_and_str); if (unlikely(!__pyx_tuple__10)) __PYX_ERR(2, 149, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__10);
  __Pyx_GIVEREF(__pyx_tuple__10);

   
  __pyx_tuple__11 = PyTuple_Pack(1, __pyx_kp_s_unable_to_allocate_array_data); if (unlikely(!__pyx_tuple__11)) __PYX_ERR(2, 177, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__11);
  __Pyx_GIVEREF(__pyx_tuple__11);

   
  __pyx_tuple__12 = PyTuple_Pack(1, __pyx_kp_s_Can_only_create_a_buffer_that_is); if (unlikely(!__pyx_tuple__12)) __PYX_ERR(2, 193, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__12);
  __Pyx_GIVEREF(__pyx_tuple__12);

   
  __pyx_tuple__13 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__13)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__13);
  __Pyx_GIVEREF(__pyx_tuple__13);

   
  __pyx_tuple__14 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__14)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__14);
  __Pyx_GIVEREF(__pyx_tuple__14);

   
  __pyx_tuple__15 = PyTuple_Pack(1, __pyx_kp_s_Cannot_assign_to_read_only_memor); if (unlikely(!__pyx_tuple__15)) __PYX_ERR(2, 420, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__15);
  __Pyx_GIVEREF(__pyx_tuple__15);

   
  __pyx_tuple__16 = PyTuple_Pack(1, __pyx_kp_s_Unable_to_convert_item_to_object); if (unlikely(!__pyx_tuple__16)) __PYX_ERR(2, 497, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__16);
  __Pyx_GIVEREF(__pyx_tuple__16);

   
  __pyx_tuple__17 = PyTuple_Pack(1, __pyx_kp_s_Cannot_create_writable_memory_vi); if (unlikely(!__pyx_tuple__17)) __PYX_ERR(2, 522, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__17);
  __Pyx_GIVEREF(__pyx_tuple__17);

   
  __pyx_tuple__18 = PyTuple_Pack(1, __pyx_kp_s_Buffer_view_does_not_expose_stri); if (unlikely(!__pyx_tuple__18)) __PYX_ERR(2, 572, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__18);
  __Pyx_GIVEREF(__pyx_tuple__18);

   
  __pyx_tuple__19 = PyTuple_New(1); if (unlikely(!__pyx_tuple__19)) __PYX_ERR(2, 579, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__19);
  __Pyx_INCREF(__pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_int_neg_1);
  PyTuple_SET_ITEM(__pyx_tuple__19, 0, __pyx_int_neg_1);
  __Pyx_GIVEREF(__pyx_tuple__19);

   
  __pyx_tuple__20 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__20)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__20);
  __Pyx_GIVEREF(__pyx_tuple__20);

   
  __pyx_tuple__21 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__21)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);

   
  __pyx_slice__22 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__22)) __PYX_ERR(2, 684, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__22);
  __Pyx_GIVEREF(__pyx_slice__22);

   
  __pyx_tuple__23 = PyTuple_Pack(1, __pyx_kp_s_Indirect_dimensions_not_supporte); if (unlikely(!__pyx_tuple__23)) __PYX_ERR(2, 705, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__23);
  __Pyx_GIVEREF(__pyx_tuple__23);

   
  __pyx_tuple__24 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__24)) __PYX_ERR(2, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__24);
  __Pyx_GIVEREF(__pyx_tuple__24);

   
  __pyx_tuple__25 = PyTuple_Pack(1, __pyx_kp_s_no_default___reduce___due_to_non); if (unlikely(!__pyx_tuple__25)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__25);
  __Pyx_GIVEREF(__pyx_tuple__25);
  __pyx_tuple__26 = PyTuple_Pack(3, __pyx_int_184977713, __pyx_int_136983863, __pyx_int_112105877); if (unlikely(!__pyx_tuple__26)) __PYX_ERR(2, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__26);
  __Pyx_GIVEREF(__pyx_tuple__26);

   
  __pyx_tuple__27 = PyTuple_Pack(14, __pyx_n_s_data, __pyx_n_s_min_height, __pyx_n_s_min_width, __pyx_n_s_min_factor, __pyx_n_s_strict, __pyx_n_s_data_p, __pyx_n_s_data_len, __pyx_n_s_retcode, __pyx_n_s_width, __pyx_n_s_height, __pyx_n_s_jpegSubsamp, __pyx_n_s_jpegColorspace, __pyx_n_s_decoder, __pyx_n_s_msg); if (unlikely(!__pyx_tuple__27)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__27);
  __Pyx_GIVEREF(__pyx_tuple__27);
  __pyx_codeobj__28 = (PyObject*)__Pyx_PyCode_New(5, 0, 14, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__27, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_simplejpeg__jpeg_pyx, __pyx_n_s_decode_jpeg_header, 194, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__28)) __PYX_ERR(0, 194, __pyx_L1_error)

   
  __pyx_tuple__29 = PyTuple_Pack(32, __pyx_n_s_data, __pyx_n_s_colorspace, __pyx_n_s_fastdct, __pyx_n_s_fastupsample, __pyx_n_s_min_height, __pyx_n_s_min_width, __pyx_n_s_min_factor, __pyx_n_s_buffer, __pyx_n_s_strict, __pyx_n_s_test, __pyx_n_s_data_p, __pyx_n_s_data_len, __pyx_n_s_retcode, __pyx_n_s_width, __pyx_n_s_height, __pyx_n_s_jpegSubsamp, __pyx_n_s_jpegColorspace, __pyx_n_s_decoder, __pyx_n_s_msg, __pyx_n_s_tmp_colorspace, __pyx_n_s_output_colorspace, __pyx_n_s_is_cmyk, __pyx_n_s_tmplen, __pyx_n_s_outlen, __pyx_n_s_tmp, __pyx_n_s_out, __pyx_n_s_tmp_p, __pyx_n_s_out_p, __pyx_n_s_view, __pyx_n_s_bufferlen, __pyx_n_s_dims, __pyx_n_s_flags); if (unlikely(!__pyx_tuple__29)) __PYX_ERR(0, 260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__29);
  __Pyx_GIVEREF(__pyx_tuple__29);
  __pyx_codeobj__30 = (PyObject*)__Pyx_PyCode_New(9, 0, 32, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__29, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_simplejpeg__jpeg_pyx, __pyx_n_s_decode_jpeg, 260, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__30)) __PYX_ERR(0, 260, __pyx_L1_error)

   
  __pyx_tuple__31 = PyTuple_Pack(19, __pyx_n_s_image_2, __pyx_n_s_quality, __pyx_n_s_colorspace, __pyx_n_s_colorsubsampling, __pyx_n_s_fastdct, __pyx_n_s_image_p, __pyx_n_s_retcode, __pyx_n_s_height, __pyx_n_s_width, __pyx_n_s_channels, __pyx_n_s_colorspace_2, __pyx_n_s_colorsubsampling_2, __pyx_n_s_jpegbuf, __pyx_n_s_jpegbufbuf, __pyx_n_s_jpegsize, __pyx_n_s_flags, __pyx_n_s_encoder, __pyx_n_s_msg, __pyx_n_s_jpeg); if (unlikely(!__pyx_tuple__31)) __PYX_ERR(0, 427, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__31);
  __Pyx_GIVEREF(__pyx_tuple__31);
  __pyx_codeobj__32 = (PyObject*)__Pyx_PyCode_New(5, 0, 19, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__31, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_simplejpeg__jpeg_pyx, __pyx_n_s_encode_jpeg, 427, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__32)) __PYX_ERR(0, 427, __pyx_L1_error)

   
  __pyx_tuple__33 = PyTuple_Pack(1, __pyx_kp_s_strided_and_direct_or_indirect); if (unlikely(!__pyx_tuple__33)) __PYX_ERR(2, 287, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__33);
  __Pyx_GIVEREF(__pyx_tuple__33);

   
  __pyx_tuple__34 = PyTuple_Pack(1, __pyx_kp_s_strided_and_direct); if (unlikely(!__pyx_tuple__34)) __PYX_ERR(2, 288, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__34);
  __Pyx_GIVEREF(__pyx_tuple__34);

   
  __pyx_tuple__35 = PyTuple_Pack(1, __pyx_kp_s_strided_and_indirect); if (unlikely(!__pyx_tuple__35)) __PYX_ERR(2, 289, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__35);
  __Pyx_GIVEREF(__pyx_tuple__35);

   
  __pyx_tuple__36 = PyTuple_Pack(1, __pyx_kp_s_contiguous_and_direct); if (unlikely(!__pyx_tuple__36)) __PYX_ERR(2, 292, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__36);
  __Pyx_GIVEREF(__pyx_tuple__36);

   
  __pyx_tuple__37 = PyTuple_Pack(1, __pyx_kp_s_contiguous_and_indirect); if (unlikely(!__pyx_tuple__37)) __PYX_ERR(2, 293, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__37);
  __Pyx_GIVEREF(__pyx_tuple__37);

   
  __pyx_tuple__38 = PyTuple_Pack(5, __pyx_n_s_pyx_type, __pyx_n_s_pyx_checksum, __pyx_n_s_pyx_state, __pyx_n_s_pyx_PickleError, __pyx_n_s_pyx_result); if (unlikely(!__pyx_tuple__38)) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__38);
  __Pyx_GIVEREF(__pyx_tuple__38);
  __pyx_codeobj__39 = (PyObject*)__Pyx_PyCode_New(3, 0, 5, 0, CO_OPTIMIZED|CO_NEWLOCALS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__38, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_stringsource, __pyx_n_s_pyx_unpickle_Enum, 1, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__39)) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static CYTHON_SMALL_CODE int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_112105877 = PyInt_FromLong(112105877L); if (unlikely(!__pyx_int_112105877)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_136983863 = PyInt_FromLong(136983863L); if (unlikely(!__pyx_int_136983863)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_184977713 = PyInt_FromLong(184977713L); if (unlikely(!__pyx_int_184977713)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_1 = PyInt_FromLong(-1); if (unlikely(!__pyx_int_neg_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static CYTHON_SMALL_CODE int __Pyx_modinit_global_init_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_variable_export_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_function_export_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_type_init_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_type_import_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_variable_import_code(void);  
static CYTHON_SMALL_CODE int __Pyx_modinit_function_import_code(void);  

static int __Pyx_modinit_global_init_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_global_init_code", 0);
   
  __pyx_v_10simplejpeg_5_jpeg__cnames = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg__cconst = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg_COLORSPACES = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg_COLORSPACE_NAMES = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg__snames = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg__sconst = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING_NAMES = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg__pfnames = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg__pfconst = Py_None; Py_INCREF(Py_None);
  __pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS = Py_None; Py_INCREF(Py_None);
  __pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i = Py_None; Py_INCREF(Py_None);
  __pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c = Py_None; Py_INCREF(Py_None);
  __pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name = Py_None; Py_INCREF(Py_None);
  __pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub = Py_None; Py_INCREF(Py_None);
  generic = Py_None; Py_INCREF(Py_None);
  strided = Py_None; Py_INCREF(Py_None);
  indirect = Py_None; Py_INCREF(Py_None);
  contiguous = Py_None; Py_INCREF(Py_None);
  indirect_contiguous = Py_None; Py_INCREF(Py_None);
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_variable_export_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_variable_export_code", 0);
   
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_function_export_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_function_export_code", 0);
   
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_type_init_code(void) {
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__Pyx_modinit_type_init_code", 0);
   
  __pyx_vtabptr_array = &__pyx_vtable_array;
  __pyx_vtable_array.get_memview = (PyObject *(*)(struct __pyx_array_obj *))__pyx_array_get_memview;
  if (PyType_Ready(&__pyx_type___pyx_array) < 0) __PYX_ERR(2, 106, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type___pyx_array.tp_print = 0;
  #endif
  if (__Pyx_SetVtable(__pyx_type___pyx_array.tp_dict, __pyx_vtabptr_array) < 0) __PYX_ERR(2, 106, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type___pyx_array) < 0) __PYX_ERR(2, 106, __pyx_L1_error)
  __pyx_array_type = &__pyx_type___pyx_array;
  if (PyType_Ready(&__pyx_type___pyx_MemviewEnum) < 0) __PYX_ERR(2, 280, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type___pyx_MemviewEnum.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type___pyx_MemviewEnum.tp_dictoffset && __pyx_type___pyx_MemviewEnum.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type___pyx_MemviewEnum.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type___pyx_MemviewEnum) < 0) __PYX_ERR(2, 280, __pyx_L1_error)
  __pyx_MemviewEnum_type = &__pyx_type___pyx_MemviewEnum;
  __pyx_vtabptr_memoryview = &__pyx_vtable_memoryview;
  __pyx_vtable_memoryview.get_item_pointer = (char *(*)(struct __pyx_memoryview_obj *, PyObject *))__pyx_memoryview_get_item_pointer;
  __pyx_vtable_memoryview.is_slice = (PyObject *(*)(struct __pyx_memoryview_obj *, PyObject *))__pyx_memoryview_is_slice;
  __pyx_vtable_memoryview.setitem_slice_assignment = (PyObject *(*)(struct __pyx_memoryview_obj *, PyObject *, PyObject *))__pyx_memoryview_setitem_slice_assignment;
  __pyx_vtable_memoryview.setitem_slice_assign_scalar = (PyObject *(*)(struct __pyx_memoryview_obj *, struct __pyx_memoryview_obj *, PyObject *))__pyx_memoryview_setitem_slice_assign_scalar;
  __pyx_vtable_memoryview.setitem_indexed = (PyObject *(*)(struct __pyx_memoryview_obj *, PyObject *, PyObject *))__pyx_memoryview_setitem_indexed;
  __pyx_vtable_memoryview.convert_item_to_object = (PyObject *(*)(struct __pyx_memoryview_obj *, char *))__pyx_memoryview_convert_item_to_object;
  __pyx_vtable_memoryview.assign_item_from_object = (PyObject *(*)(struct __pyx_memoryview_obj *, char *, PyObject *))__pyx_memoryview_assign_item_from_object;
  if (PyType_Ready(&__pyx_type___pyx_memoryview) < 0) __PYX_ERR(2, 331, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type___pyx_memoryview.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type___pyx_memoryview.tp_dictoffset && __pyx_type___pyx_memoryview.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type___pyx_memoryview.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (__Pyx_SetVtable(__pyx_type___pyx_memoryview.tp_dict, __pyx_vtabptr_memoryview) < 0) __PYX_ERR(2, 331, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type___pyx_memoryview) < 0) __PYX_ERR(2, 331, __pyx_L1_error)
  __pyx_memoryview_type = &__pyx_type___pyx_memoryview;
  __pyx_vtabptr__memoryviewslice = &__pyx_vtable__memoryviewslice;
  __pyx_vtable__memoryviewslice.__pyx_base = *__pyx_vtabptr_memoryview;
  __pyx_vtable__memoryviewslice.__pyx_base.convert_item_to_object = (PyObject *(*)(struct __pyx_memoryview_obj *, char *))__pyx_memoryviewslice_convert_item_to_object;
  __pyx_vtable__memoryviewslice.__pyx_base.assign_item_from_object = (PyObject *(*)(struct __pyx_memoryview_obj *, char *, PyObject *))__pyx_memoryviewslice_assign_item_from_object;
  __pyx_type___pyx_memoryviewslice.tp_base = __pyx_memoryview_type;
  if (PyType_Ready(&__pyx_type___pyx_memoryviewslice) < 0) __PYX_ERR(2, 967, __pyx_L1_error)
  #if PY_VERSION_HEX < 0x030800B1
  __pyx_type___pyx_memoryviewslice.tp_print = 0;
  #endif
  if ((CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP) && likely(!__pyx_type___pyx_memoryviewslice.tp_dictoffset && __pyx_type___pyx_memoryviewslice.tp_getattro == PyObject_GenericGetAttr)) {
    __pyx_type___pyx_memoryviewslice.tp_getattro = __Pyx_PyObject_GenericGetAttr;
  }
  if (__Pyx_SetVtable(__pyx_type___pyx_memoryviewslice.tp_dict, __pyx_vtabptr__memoryviewslice) < 0) __PYX_ERR(2, 967, __pyx_L1_error)
  if (__Pyx_setup_reduce((PyObject*)&__pyx_type___pyx_memoryviewslice) < 0) __PYX_ERR(2, 967, __pyx_L1_error)
  __pyx_memoryviewslice_type = &__pyx_type___pyx_memoryviewslice;
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_modinit_type_import_code(void) {
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__Pyx_modinit_type_import_code", 0);
   
  __pyx_t_1 = PyImport_ImportModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_t_1)) __PYX_ERR(3, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_ptype_7cpython_4type_type = __Pyx_ImportType_0_29_35(__pyx_t_1, __Pyx_BUILTIN_MODULE_NAME, "type", 
  #if defined(PYPY_VERSION_NUM) && PYPY_VERSION_NUM < 0x050B0000
  sizeof(PyTypeObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyTypeObject),
  #else
  sizeof(PyHeapTypeObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyHeapTypeObject),
  #endif
  __Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_7cpython_4type_type) __PYX_ERR(3, 9, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyImport_ImportModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_t_1)) __PYX_ERR(4, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_ptype_7cpython_4bool_bool = __Pyx_ImportType_0_29_35(__pyx_t_1, __Pyx_BUILTIN_MODULE_NAME, "bool", sizeof(PyBoolObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyBoolObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_7cpython_4bool_bool) __PYX_ERR(4, 8, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyImport_ImportModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_t_1)) __PYX_ERR(5, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_ptype_7cpython_7complex_complex = __Pyx_ImportType_0_29_35(__pyx_t_1, __Pyx_BUILTIN_MODULE_NAME, "complex", sizeof(PyComplexObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyComplexObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_7cpython_7complex_complex) __PYX_ERR(5, 15, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyImport_ImportModule("numpy"); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_ptype_5numpy_dtype = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "dtype", sizeof(PyArray_Descr), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyArray_Descr),__Pyx_ImportType_CheckSize_Ignore_0_29_35); if (!__pyx_ptype_5numpy_dtype) __PYX_ERR(1, 199, __pyx_L1_error)
  __pyx_ptype_5numpy_flatiter = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "flatiter", sizeof(PyArrayIterObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyArrayIterObject),__Pyx_ImportType_CheckSize_Ignore_0_29_35); if (!__pyx_ptype_5numpy_flatiter) __PYX_ERR(1, 222, __pyx_L1_error)
  __pyx_ptype_5numpy_broadcast = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "broadcast", sizeof(PyArrayMultiIterObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyArrayMultiIterObject),__Pyx_ImportType_CheckSize_Ignore_0_29_35); if (!__pyx_ptype_5numpy_broadcast) __PYX_ERR(1, 226, __pyx_L1_error)
  __pyx_ptype_5numpy_ndarray = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "ndarray", sizeof(PyArrayObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyArrayObject),__Pyx_ImportType_CheckSize_Ignore_0_29_35); if (!__pyx_ptype_5numpy_ndarray) __PYX_ERR(1, 238, __pyx_L1_error)
  __pyx_ptype_5numpy_generic = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "generic", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_generic) __PYX_ERR(1, 770, __pyx_L1_error)
  __pyx_ptype_5numpy_number = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "number", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_number) __PYX_ERR(1, 772, __pyx_L1_error)
  __pyx_ptype_5numpy_integer = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "integer", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_integer) __PYX_ERR(1, 774, __pyx_L1_error)
  __pyx_ptype_5numpy_signedinteger = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "signedinteger", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_signedinteger) __PYX_ERR(1, 776, __pyx_L1_error)
  __pyx_ptype_5numpy_unsignedinteger = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "unsignedinteger", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_unsignedinteger) __PYX_ERR(1, 778, __pyx_L1_error)
  __pyx_ptype_5numpy_inexact = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "inexact", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_inexact) __PYX_ERR(1, 780, __pyx_L1_error)
  __pyx_ptype_5numpy_floating = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "floating", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_floating) __PYX_ERR(1, 782, __pyx_L1_error)
  __pyx_ptype_5numpy_complexfloating = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "complexfloating", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_complexfloating) __PYX_ERR(1, 784, __pyx_L1_error)
  __pyx_ptype_5numpy_flexible = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "flexible", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_flexible) __PYX_ERR(1, 786, __pyx_L1_error)
  __pyx_ptype_5numpy_character = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "character", sizeof(PyObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyObject),__Pyx_ImportType_CheckSize_Warn_0_29_35); if (!__pyx_ptype_5numpy_character) __PYX_ERR(1, 788, __pyx_L1_error)
  __pyx_ptype_5numpy_ufunc = __Pyx_ImportType_0_29_35(__pyx_t_1, "numpy", "ufunc", sizeof(PyUFuncObject), __PYX_GET_STRUCT_ALIGNMENT_0_29_35(PyUFuncObject),__Pyx_ImportType_CheckSize_Ignore_0_29_35); if (!__pyx_ptype_5numpy_ufunc) __PYX_ERR(1, 826, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_modinit_variable_import_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_variable_import_code", 0);
   
  __Pyx_RefNannyFinishContext();
  return 0;
}

static int __Pyx_modinit_function_import_code(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_modinit_function_import_code", 0);
   
  __Pyx_RefNannyFinishContext();
  return 0;
}


#ifndef CYTHON_NO_PYINIT_EXPORT
#define __Pyx_PyMODINIT_FUNC PyMODINIT_FUNC
#elif PY_MAJOR_VERSION < 3
#ifdef __cplusplus
#define __Pyx_PyMODINIT_FUNC extern "C" void
#else
#define __Pyx_PyMODINIT_FUNC void
#endif
#else
#ifdef __cplusplus
#define __Pyx_PyMODINIT_FUNC extern "C" PyObject *
#else
#define __Pyx_PyMODINIT_FUNC PyObject *
#endif
#endif


#if PY_MAJOR_VERSION < 3
__Pyx_PyMODINIT_FUNC init_jpeg(void) CYTHON_SMALL_CODE;  
__Pyx_PyMODINIT_FUNC init_jpeg(void)
#else
__Pyx_PyMODINIT_FUNC PyInit__jpeg(void) CYTHON_SMALL_CODE;  
__Pyx_PyMODINIT_FUNC PyInit__jpeg(void)
#if CYTHON_PEP489_MULTI_PHASE_INIT
{
  return PyModuleDef_Init(&__pyx_moduledef);
}
static CYTHON_SMALL_CODE int __Pyx_check_single_interpreter(void) {
    #if PY_VERSION_HEX >= 0x030700A1
    static PY_INT64_T main_interpreter_id = -1;
    PY_INT64_T current_id = PyInterpreterState_GetID(PyThreadState_Get()->interp);
    if (main_interpreter_id == -1) {
        main_interpreter_id = current_id;
        return (unlikely(current_id == -1)) ? -1 : 0;
    } else if (unlikely(main_interpreter_id != current_id))
    #else
    static PyInterpreterState *main_interpreter = NULL;
    PyInterpreterState *current_interpreter = PyThreadState_Get()->interp;
    if (!main_interpreter) {
        main_interpreter = current_interpreter;
    } else if (unlikely(main_interpreter != current_interpreter))
    #endif
    {
        PyErr_SetString(
            PyExc_ImportError,
            "Interpreter change detected - this module can only be loaded into one interpreter per process.");
        return -1;
    }
    return 0;
}
static CYTHON_SMALL_CODE int __Pyx_copy_spec_to_module(PyObject *spec, PyObject *moddict, const char* from_name, const char* to_name, int allow_none) {
    PyObject *value = PyObject_GetAttrString(spec, from_name);
    int result = 0;
    if (likely(value)) {
        if (allow_none || value != Py_None) {
            result = PyDict_SetItemString(moddict, to_name, value);
        }
        Py_DECREF(value);
    } else if (PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Clear();
    } else {
        result = -1;
    }
    return result;
}
static CYTHON_SMALL_CODE PyObject* __pyx_pymod_create(PyObject *spec, CYTHON_UNUSED PyModuleDef *def) {
    PyObject *module = NULL, *moddict, *modname;
    if (__Pyx_check_single_interpreter())
        return NULL;
    if (__pyx_m)
        return __Pyx_NewRef(__pyx_m);
    modname = PyObject_GetAttrString(spec, "name");
    if (unlikely(!modname)) goto bad;
    module = PyModule_NewObject(modname);
    Py_DECREF(modname);
    if (unlikely(!module)) goto bad;
    moddict = PyModule_GetDict(module);
    if (unlikely(!moddict)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "loader", "__loader__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "origin", "__file__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "parent", "__package__", 1) < 0)) goto bad;
    if (unlikely(__Pyx_copy_spec_to_module(spec, moddict, "submodule_search_locations", "__path__", 0) < 0)) goto bad;
    return module;
bad:
    Py_XDECREF(module);
    return NULL;
}


static CYTHON_SMALL_CODE int __pyx_pymod_exec__jpeg(PyObject *__pyx_pyinit_module)
#endif
#endif
{
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  Py_ssize_t __pyx_t_8;
  PyObject *(*__pyx_t_9)(PyObject *);
  PyObject *(*__pyx_t_10)(PyObject *);
  PyObject *__pyx_t_11 = NULL;
  int __pyx_t_12;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  PyObject *__pyx_t_15 = NULL;
  PyObject *__pyx_t_16 = NULL;
  PyObject *__pyx_t_17 = NULL;
  PyObject *__pyx_t_18 = NULL;
  static PyThread_type_lock __pyx_t_19[8];
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  if (__pyx_m) {
    if (__pyx_m == __pyx_pyinit_module) return 0;
    PyErr_SetString(PyExc_RuntimeError, "Module '_jpeg' has already been imported. Re-initialisation is not supported.");
    return -1;
  }
  #elif PY_MAJOR_VERSION >= 3
  if (__pyx_m) return __Pyx_NewRef(__pyx_m);
  #endif
  #if CYTHON_REFNANNY
__Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
if (!__Pyx_RefNanny) {
  PyErr_Clear();
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
  if (!__Pyx_RefNanny)
      Py_FatalError("failed to import 'refnanny' module");
}
#endif
  __Pyx_RefNannySetupContext("__Pyx_PyMODINIT_FUNC PyInit__jpeg(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #ifdef __Pxy_PyFrame_Initialize_Offsets
  __Pxy_PyFrame_Initialize_Offsets();
  #endif
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(0, 1, __pyx_L1_error)
  #ifdef __Pyx_CyFunction_USED
  if (__pyx_CyFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Coroutine_USED
  if (__pyx_Coroutine_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_AsyncGen_USED
  if (__pyx_AsyncGen_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
   
   
  #if defined(WITH_THREAD) && PY_VERSION_HEX < 0x030700F0 && defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  PyEval_InitThreads();
  #endif
   
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  __pyx_m = __pyx_pyinit_module;
  Py_INCREF(__pyx_m);
  #else
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("_jpeg", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_b);
  __pyx_cython_runtime = PyImport_AddModule((char *) "cython_runtime"); if (unlikely(!__pyx_cython_runtime)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_cython_runtime);
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
   
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  if (__pyx_module_is_main_simplejpeg___jpeg) {
    if (PyObject_SetAttr(__pyx_m, __pyx_n_s_name_2, __pyx_n_s_main) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "simplejpeg._jpeg")) {
      if (unlikely(PyDict_SetItemString(modules, "simplejpeg._jpeg", __pyx_m) < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
    }
  }
  #endif
   
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
   
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
   
  (void)__Pyx_modinit_global_init_code();
  (void)__Pyx_modinit_variable_export_code();
  (void)__Pyx_modinit_function_export_code();
  if (unlikely(__Pyx_modinit_type_init_code() < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
  if (unlikely(__Pyx_modinit_type_import_code() < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
  (void)__Pyx_modinit_variable_import_code();
  (void)__Pyx_modinit_function_import_code();
   
  #if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif

   
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy, 0, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_np, __pyx_t_1) < 0) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

   
  __pyx_t_2 = __pyx_f_5numpy_import_array(); if (unlikely(__pyx_t_2 == ((int)-1))) __PYX_ERR(0, 17, __pyx_L1_error)

   
  __pyx_t_1 = PyList_New(5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 110, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_u_RGB);
  __Pyx_GIVEREF(__pyx_n_u_RGB);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_u_RGB);
  __Pyx_INCREF(__pyx_n_u_YCbCr);
  __Pyx_GIVEREF(__pyx_n_u_YCbCr);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_u_YCbCr);
  __Pyx_INCREF(__pyx_n_u_Gray);
  __Pyx_GIVEREF(__pyx_n_u_Gray);
  PyList_SET_ITEM(__pyx_t_1, 2, __pyx_n_u_Gray);
  __Pyx_INCREF(__pyx_n_u_CMYK);
  __Pyx_GIVEREF(__pyx_n_u_CMYK);
  PyList_SET_ITEM(__pyx_t_1, 3, __pyx_n_u_CMYK);
  __Pyx_INCREF(__pyx_n_u_YCCK);
  __Pyx_GIVEREF(__pyx_n_u_YCCK);
  PyList_SET_ITEM(__pyx_t_1, 4, __pyx_n_u_YCCK);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__cnames);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__cnames, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;

   
  __pyx_t_1 = __Pyx_PyInt_From_int(TJCS_RGB); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyInt_From_int(TJCS_YCbCr); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyInt_From_int(TJCS_GRAY); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = __Pyx_PyInt_From_int(TJCS_CMYK); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = __Pyx_PyInt_From_int(TJCS_YCCK); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_7 = PyList_New(5); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_1);
  PyList_SET_ITEM(__pyx_t_7, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_7, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyList_SET_ITEM(__pyx_t_7, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_5);
  PyList_SET_ITEM(__pyx_t_7, 3, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_6);
  PyList_SET_ITEM(__pyx_t_7, 4, __pyx_t_6);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__cconst);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__cconst, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_7);
  __pyx_t_7 = 0;

   
  __pyx_t_7 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg_COLORSPACES);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg_COLORSPACES, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_7);
  __pyx_t_7 = 0;

   
  __pyx_t_7 = PyTuple_New(2); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__cnames);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__cnames);
  PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_v_10simplejpeg_5_jpeg__cnames);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__cconst);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__cconst);
  PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_v_10simplejpeg_5_jpeg__cconst);
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_7, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  if (likely(PyList_CheckExact(__pyx_t_6)) || PyTuple_CheckExact(__pyx_t_6)) {
    __pyx_t_7 = __pyx_t_6; __Pyx_INCREF(__pyx_t_7); __pyx_t_8 = 0;
    __pyx_t_9 = NULL;
  } else {
    __pyx_t_8 = -1; __pyx_t_7 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_9 = Py_TYPE(__pyx_t_7)->tp_iternext; if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 113, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  for (;;) {
    if (likely(!__pyx_t_9)) {
      if (likely(PyList_CheckExact(__pyx_t_7))) {
        if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_7)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_6 = PyList_GET_ITEM(__pyx_t_7, __pyx_t_8); __Pyx_INCREF(__pyx_t_6); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 113, __pyx_L1_error)
        #else
        __pyx_t_6 = PySequence_ITEM(__pyx_t_7, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 113, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        #endif
      } else {
        if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_7)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_6 = PyTuple_GET_ITEM(__pyx_t_7, __pyx_t_8); __Pyx_INCREF(__pyx_t_6); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 113, __pyx_L1_error)
        #else
        __pyx_t_6 = PySequence_ITEM(__pyx_t_7, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 113, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        #endif
      }
    } else {
      __pyx_t_6 = __pyx_t_9(__pyx_t_7);
      if (unlikely(!__pyx_t_6)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 113, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_6);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_6))) || (PyList_CheckExact(__pyx_t_6))) {
      PyObject* sequence = __pyx_t_6;
      Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 113, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_4 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_4);
      #else
      __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 113, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 113, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_3 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 113, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_3)->tp_iternext;
      index = 0; __pyx_t_5 = __pyx_t_10(__pyx_t_3); if (unlikely(!__pyx_t_5)) goto __pyx_L4_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_5);
      index = 1; __pyx_t_4 = __pyx_t_10(__pyx_t_3); if (unlikely(!__pyx_t_4)) goto __pyx_L4_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_4);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_3), 2) < 0) __PYX_ERR(0, 113, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      goto __pyx_L5_unpacking_done;
      __pyx_L4_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 113, __pyx_L1_error)
      __pyx_L5_unpacking_done:;
    }
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_name, __pyx_t_5) < 0) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_i, __pyx_t_4) < 0) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_6, __pyx_n_s_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_GetModuleGlobalName(__pyx_t_4, __pyx_n_s_name); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_COLORSPACES, __pyx_t_4, __pyx_t_6) < 0)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_6, __pyx_n_s_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 115, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_name); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 115, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_lower); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 115, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    __pyx_t_4 = (__pyx_t_5) ? __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_5) : __Pyx_PyObject_CallNoArg(__pyx_t_3);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 115, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_COLORSPACES, __pyx_t_4, __pyx_t_6) < 0)) __PYX_ERR(0, 115, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_6, __pyx_n_s_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 116, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_name); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 116, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_upper); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 116, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    __pyx_t_4 = (__pyx_t_3) ? __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_3) : __Pyx_PyObject_CallNoArg(__pyx_t_5);
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 116, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_COLORSPACES, __pyx_t_4, __pyx_t_6) < 0)) __PYX_ERR(0, 116, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

     
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;

   
  {  
    __pyx_t_7 = PyDict_New(); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 117, __pyx_L8_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_6 = PyTuple_New(2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 117, __pyx_L8_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__cconst);
    __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__cconst);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_v_10simplejpeg_5_jpeg__cconst);
    __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__cnames);
    __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__cnames);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_v_10simplejpeg_5_jpeg__cnames);
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_6, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 117, __pyx_L8_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (likely(PyList_CheckExact(__pyx_t_4)) || PyTuple_CheckExact(__pyx_t_4)) {
      __pyx_t_6 = __pyx_t_4; __Pyx_INCREF(__pyx_t_6); __pyx_t_8 = 0;
      __pyx_t_9 = NULL;
    } else {
      __pyx_t_8 = -1; __pyx_t_6 = PyObject_GetIter(__pyx_t_4); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 117, __pyx_L8_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_9 = Py_TYPE(__pyx_t_6)->tp_iternext; if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 117, __pyx_L8_error)
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    for (;;) {
      if (likely(!__pyx_t_9)) {
        if (likely(PyList_CheckExact(__pyx_t_6))) {
          if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_6)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_4 = PyList_GET_ITEM(__pyx_t_6, __pyx_t_8); __Pyx_INCREF(__pyx_t_4); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 117, __pyx_L8_error)
          #else
          __pyx_t_4 = PySequence_ITEM(__pyx_t_6, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 117, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_4);
          #endif
        } else {
          if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_6)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_6, __pyx_t_8); __Pyx_INCREF(__pyx_t_4); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 117, __pyx_L8_error)
          #else
          __pyx_t_4 = PySequence_ITEM(__pyx_t_6, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 117, __pyx_L8_error)
          __Pyx_GOTREF(__pyx_t_4);
          #endif
        }
      } else {
        __pyx_t_4 = __pyx_t_9(__pyx_t_6);
        if (unlikely(!__pyx_t_4)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 117, __pyx_L8_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_4);
      }
      if ((likely(PyTuple_CheckExact(__pyx_t_4))) || (PyList_CheckExact(__pyx_t_4))) {
        PyObject* sequence = __pyx_t_4;
        Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
        if (unlikely(size != 2)) {
          if (size > 2) __Pyx_RaiseTooManyValuesError(2);
          else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
          __PYX_ERR(0, 117, __pyx_L8_error)
        }
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        if (likely(PyTuple_CheckExact(sequence))) {
          __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
          __pyx_t_3 = PyTuple_GET_ITEM(sequence, 1); 
        } else {
          __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
          __pyx_t_3 = PyList_GET_ITEM(sequence, 1); 
        }
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_3);
        #else
        __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 117, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_3 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 117, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_3);
        #endif
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      } else {
        Py_ssize_t index = -1;
        __pyx_t_1 = PyObject_GetIter(__pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 117, __pyx_L8_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        __pyx_t_10 = Py_TYPE(__pyx_t_1)->tp_iternext;
        index = 0; __pyx_t_5 = __pyx_t_10(__pyx_t_1); if (unlikely(!__pyx_t_5)) goto __pyx_L11_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_5);
        index = 1; __pyx_t_3 = __pyx_t_10(__pyx_t_1); if (unlikely(!__pyx_t_3)) goto __pyx_L11_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_3);
        if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_1), 2) < 0) __PYX_ERR(0, 117, __pyx_L8_error)
        __pyx_t_10 = NULL;
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        goto __pyx_L12_unpacking_done;
        __pyx_L11_unpacking_failed:;
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __pyx_t_10 = NULL;
        if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
        __PYX_ERR(0, 117, __pyx_L8_error)
        __pyx_L12_unpacking_done:;
      }
      __Pyx_XGOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i);
      __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_XGOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c);
      __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c, __pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (unlikely(PyDict_SetItem(__pyx_t_7, (PyObject*)__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i, (PyObject*)__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c))) __PYX_ERR(0, 117, __pyx_L8_error)
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c);
    __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c, Py_None);
    __Pyx_GOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i);
    __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i, Py_None);
    goto __pyx_L13_exit_scope;
    __pyx_L8_error:;
    __Pyx_GOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c);
    __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_c, Py_None);
    __Pyx_GOTREF(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i);
    __Pyx_DECREF_SET(__pyx_7genexpr__pyx_v_10simplejpeg_5_jpeg_i, Py_None);
    goto __pyx_L1_error;
    __pyx_L13_exit_scope:;
  }  
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg_COLORSPACE_NAMES);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg_COLORSPACE_NAMES, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_7);
  __pyx_t_7 = 0;

   
  __pyx_t_7 = PyList_New(6); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 121, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_INCREF(__pyx_kp_u_444);
  __Pyx_GIVEREF(__pyx_kp_u_444);
  PyList_SET_ITEM(__pyx_t_7, 0, __pyx_kp_u_444);
  __Pyx_INCREF(__pyx_kp_u_422);
  __Pyx_GIVEREF(__pyx_kp_u_422);
  PyList_SET_ITEM(__pyx_t_7, 1, __pyx_kp_u_422);
  __Pyx_INCREF(__pyx_kp_u_420);
  __Pyx_GIVEREF(__pyx_kp_u_420);
  PyList_SET_ITEM(__pyx_t_7, 2, __pyx_kp_u_420);
  __Pyx_INCREF(__pyx_n_u_Gray);
  __Pyx_GIVEREF(__pyx_n_u_Gray);
  PyList_SET_ITEM(__pyx_t_7, 3, __pyx_n_u_Gray);
  __Pyx_INCREF(__pyx_kp_u_440);
  __Pyx_GIVEREF(__pyx_kp_u_440);
  PyList_SET_ITEM(__pyx_t_7, 4, __pyx_kp_u_440);
  __Pyx_INCREF(__pyx_kp_u_411);
  __Pyx_GIVEREF(__pyx_kp_u_411);
  PyList_SET_ITEM(__pyx_t_7, 5, __pyx_kp_u_411);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__snames);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__snames, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_7);
  __pyx_t_7 = 0;

   
  __pyx_t_7 = __Pyx_PyInt_From_int(TJSAMP_444); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_6 = __Pyx_PyInt_From_int(TJSAMP_422); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_4 = __Pyx_PyInt_From_int(TJSAMP_420); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

   
  __pyx_t_3 = __Pyx_PyInt_From_int(TJSAMP_GRAY); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_PyInt_From_int(TJSAMP_440); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_1 = __Pyx_PyInt_From_int(TJSAMP_411); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 123, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

   
  __pyx_t_11 = PyList_New(6); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_7);
  PyList_SET_ITEM(__pyx_t_11, 0, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_6);
  PyList_SET_ITEM(__pyx_t_11, 1, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_4);
  PyList_SET_ITEM(__pyx_t_11, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_11, 3, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_5);
  PyList_SET_ITEM(__pyx_t_11, 4, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_1);
  PyList_SET_ITEM(__pyx_t_11, 5, __pyx_t_1);
  __pyx_t_7 = 0;
  __pyx_t_6 = 0;
  __pyx_t_4 = 0;
  __pyx_t_3 = 0;
  __pyx_t_5 = 0;
  __pyx_t_1 = 0;
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__sconst);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__sconst, __pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_11);
  __pyx_t_11 = 0;

   
  __pyx_t_11 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING, __pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_11);
  __pyx_t_11 = 0;

   
  __pyx_t_11 = PyTuple_New(2); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 125, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__snames);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__snames);
  PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_v_10simplejpeg_5_jpeg__snames);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__sconst);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__sconst);
  PyTuple_SET_ITEM(__pyx_t_11, 1, __pyx_v_10simplejpeg_5_jpeg__sconst);
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_11, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 125, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_11 = __pyx_t_1; __Pyx_INCREF(__pyx_t_11); __pyx_t_8 = 0;
    __pyx_t_9 = NULL;
  } else {
    __pyx_t_8 = -1; __pyx_t_11 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 125, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    __pyx_t_9 = Py_TYPE(__pyx_t_11)->tp_iternext; if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 125, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_9)) {
      if (likely(PyList_CheckExact(__pyx_t_11))) {
        if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_11)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_11, __pyx_t_8); __Pyx_INCREF(__pyx_t_1); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 125, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_11, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      } else {
        if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_11)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_11, __pyx_t_8); __Pyx_INCREF(__pyx_t_1); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 125, __pyx_L1_error)
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_11, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_9(__pyx_t_11);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 125, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_1))) || (PyList_CheckExact(__pyx_t_1))) {
      PyObject* sequence = __pyx_t_1;
      Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 125, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_3 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_3 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_3);
      #else
      __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_3 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      #endif
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_4 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_4)->tp_iternext;
      index = 0; __pyx_t_5 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_5)) goto __pyx_L16_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_5);
      index = 1; __pyx_t_3 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_3)) goto __pyx_L16_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_3);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_4), 2) < 0) __PYX_ERR(0, 125, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      goto __pyx_L17_unpacking_done;
      __pyx_L16_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 125, __pyx_L1_error)
      __pyx_L17_unpacking_done:;
    }
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_name, __pyx_t_5) < 0) __PYX_ERR(0, 125, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_sub, __pyx_t_3) < 0) __PYX_ERR(0, 125, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_1, __pyx_n_s_sub); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 126, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GetModuleGlobalName(__pyx_t_3, __pyx_n_s_name); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 126, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING, __pyx_t_3, __pyx_t_1) < 0)) __PYX_ERR(0, 126, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_1, __pyx_n_s_sub); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 127, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GetModuleGlobalName(__pyx_t_5, __pyx_n_s_name); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 127, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_lower); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 127, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
      }
    }
    __pyx_t_3 = (__pyx_t_5) ? __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_5) : __Pyx_PyObject_CallNoArg(__pyx_t_4);
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 127, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING, __pyx_t_3, __pyx_t_1) < 0)) __PYX_ERR(0, 127, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_1, __pyx_n_s_sub); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 128, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GetModuleGlobalName(__pyx_t_4, __pyx_n_s_name); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 128, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_upper); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 128, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    __pyx_t_3 = (__pyx_t_4) ? __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_4) : __Pyx_PyObject_CallNoArg(__pyx_t_5);
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 128, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING, __pyx_t_3, __pyx_t_1) < 0)) __PYX_ERR(0, 128, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

     
  }
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;

   
  __pyx_t_12 = __Pyx_PyObject_Append(__pyx_v_10simplejpeg_5_jpeg__snames, __pyx_n_u_unknown); if (unlikely(__pyx_t_12 == ((int)-1))) __PYX_ERR(0, 130, __pyx_L1_error)

   
  __pyx_t_11 = __Pyx_PyInt_From_int(TJ_NUMSAMP); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_12 = __Pyx_PyObject_Append(__pyx_v_10simplejpeg_5_jpeg__sconst, __pyx_t_11); if (unlikely(__pyx_t_12 == ((int)-1))) __PYX_ERR(0, 131, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;

   
  {  
    __pyx_t_11 = PyDict_New(); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 132, __pyx_L20_error)
    __Pyx_GOTREF(__pyx_t_11);
    __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 132, __pyx_L20_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__snames);
    __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__snames);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_10simplejpeg_5_jpeg__snames);
    __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__sconst);
    __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__sconst);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_10simplejpeg_5_jpeg__sconst);
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 132, __pyx_L20_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
      __pyx_t_1 = __pyx_t_3; __Pyx_INCREF(__pyx_t_1); __pyx_t_8 = 0;
      __pyx_t_9 = NULL;
    } else {
      __pyx_t_8 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 132, __pyx_L20_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_9 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 132, __pyx_L20_error)
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    for (;;) {
      if (likely(!__pyx_t_9)) {
        if (likely(PyList_CheckExact(__pyx_t_1))) {
          if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_3 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_8); __Pyx_INCREF(__pyx_t_3); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 132, __pyx_L20_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 132, __pyx_L20_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        } else {
          if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_8); __Pyx_INCREF(__pyx_t_3); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 132, __pyx_L20_error)
          #else
          __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 132, __pyx_L20_error)
          __Pyx_GOTREF(__pyx_t_3);
          #endif
        }
      } else {
        __pyx_t_3 = __pyx_t_9(__pyx_t_1);
        if (unlikely(!__pyx_t_3)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 132, __pyx_L20_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_3);
      }
      if ((likely(PyTuple_CheckExact(__pyx_t_3))) || (PyList_CheckExact(__pyx_t_3))) {
        PyObject* sequence = __pyx_t_3;
        Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
        if (unlikely(size != 2)) {
          if (size > 2) __Pyx_RaiseTooManyValuesError(2);
          else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
          __PYX_ERR(0, 132, __pyx_L20_error)
        }
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        if (likely(PyTuple_CheckExact(sequence))) {
          __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
          __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
        } else {
          __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
          __pyx_t_4 = PyList_GET_ITEM(sequence, 1); 
        }
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_4);
        #else
        __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 132, __pyx_L20_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 132, __pyx_L20_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      } else {
        Py_ssize_t index = -1;
        __pyx_t_6 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 132, __pyx_L20_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_10 = Py_TYPE(__pyx_t_6)->tp_iternext;
        index = 0; __pyx_t_5 = __pyx_t_10(__pyx_t_6); if (unlikely(!__pyx_t_5)) goto __pyx_L23_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_5);
        index = 1; __pyx_t_4 = __pyx_t_10(__pyx_t_6); if (unlikely(!__pyx_t_4)) goto __pyx_L23_unpacking_failed;
        __Pyx_GOTREF(__pyx_t_4);
        if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_6), 2) < 0) __PYX_ERR(0, 132, __pyx_L20_error)
        __pyx_t_10 = NULL;
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        goto __pyx_L24_unpacking_done;
        __pyx_L23_unpacking_failed:;
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_10 = NULL;
        if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
        __PYX_ERR(0, 132, __pyx_L20_error)
        __pyx_L24_unpacking_done:;
      }
      __Pyx_XGOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name);
      __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_XGOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub);
      __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub, __pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_4);
      __pyx_t_4 = 0;
      if (unlikely(PyDict_SetItem(__pyx_t_11, (PyObject*)__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub, (PyObject*)__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name))) __PYX_ERR(0, 132, __pyx_L20_error)
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name);
    __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name, Py_None);
    __Pyx_GOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub);
    __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub, Py_None);
    goto __pyx_L25_exit_scope;
    __pyx_L20_error:;
    __Pyx_GOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name);
    __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_name, Py_None);
    __Pyx_GOTREF(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub);
    __Pyx_DECREF_SET(__pyx_8genexpr1__pyx_v_10simplejpeg_5_jpeg_sub, Py_None);
    goto __pyx_L1_error;
    __pyx_L25_exit_scope:;
  }  
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING_NAMES);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg_SUBSAMPLING_NAMES, __pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_11);
  __pyx_t_11 = 0;

   
  __pyx_t_11 = PyList_New(12); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_INCREF(__pyx_n_u_RGB);
  __Pyx_GIVEREF(__pyx_n_u_RGB);
  PyList_SET_ITEM(__pyx_t_11, 0, __pyx_n_u_RGB);
  __Pyx_INCREF(__pyx_n_u_BGR);
  __Pyx_GIVEREF(__pyx_n_u_BGR);
  PyList_SET_ITEM(__pyx_t_11, 1, __pyx_n_u_BGR);
  __Pyx_INCREF(__pyx_n_u_RGBX);
  __Pyx_GIVEREF(__pyx_n_u_RGBX);
  PyList_SET_ITEM(__pyx_t_11, 2, __pyx_n_u_RGBX);
  __Pyx_INCREF(__pyx_n_u_BGRX);
  __Pyx_GIVEREF(__pyx_n_u_BGRX);
  PyList_SET_ITEM(__pyx_t_11, 3, __pyx_n_u_BGRX);
  __Pyx_INCREF(__pyx_n_u_XBGR);
  __Pyx_GIVEREF(__pyx_n_u_XBGR);
  PyList_SET_ITEM(__pyx_t_11, 4, __pyx_n_u_XBGR);
  __Pyx_INCREF(__pyx_n_u_XRGB);
  __Pyx_GIVEREF(__pyx_n_u_XRGB);
  PyList_SET_ITEM(__pyx_t_11, 5, __pyx_n_u_XRGB);
  __Pyx_INCREF(__pyx_n_u_Gray);
  __Pyx_GIVEREF(__pyx_n_u_Gray);
  PyList_SET_ITEM(__pyx_t_11, 6, __pyx_n_u_Gray);
  __Pyx_INCREF(__pyx_n_u_RGBA);
  __Pyx_GIVEREF(__pyx_n_u_RGBA);
  PyList_SET_ITEM(__pyx_t_11, 7, __pyx_n_u_RGBA);
  __Pyx_INCREF(__pyx_n_u_BGRA);
  __Pyx_GIVEREF(__pyx_n_u_BGRA);
  PyList_SET_ITEM(__pyx_t_11, 8, __pyx_n_u_BGRA);
  __Pyx_INCREF(__pyx_n_u_ABGR);
  __Pyx_GIVEREF(__pyx_n_u_ABGR);
  PyList_SET_ITEM(__pyx_t_11, 9, __pyx_n_u_ABGR);
  __Pyx_INCREF(__pyx_n_u_ARGB);
  __Pyx_GIVEREF(__pyx_n_u_ARGB);
  PyList_SET_ITEM(__pyx_t_11, 10, __pyx_n_u_ARGB);
  __Pyx_INCREF(__pyx_n_u_CMYK);
  __Pyx_GIVEREF(__pyx_n_u_CMYK);
  PyList_SET_ITEM(__pyx_t_11, 11, __pyx_n_u_CMYK);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__pfnames);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__pfnames, __pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_11);
  __pyx_t_11 = 0;

   
  __pyx_t_11 = __Pyx_PyInt_From_int(TJPF_RGB); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_1 = __Pyx_PyInt_From_int(TJPF_BGR); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyInt_From_int(TJPF_RGBX); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyInt_From_int(TJPF_BGRX); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

   
  __pyx_t_5 = __Pyx_PyInt_From_int(TJPF_XBGR); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 = __Pyx_PyInt_From_int(TJPF_XRGB); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_7 = __Pyx_PyInt_From_int(TJPF_GRAY); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_13 = __Pyx_PyInt_From_int(TJPF_RGBA); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 141, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_13);

   
  __pyx_t_14 = __Pyx_PyInt_From_int(TJPF_BGRA); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_14);
  __pyx_t_15 = __Pyx_PyInt_From_int(TJPF_ABGR); if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_15);
  __pyx_t_16 = __Pyx_PyInt_From_int(TJPF_ARGB); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __pyx_t_17 = __Pyx_PyInt_From_int(TJPF_CMYK); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 142, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_17);

   
  __pyx_t_18 = PyList_New(12); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_11);
  PyList_SET_ITEM(__pyx_t_18, 0, __pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_1);
  PyList_SET_ITEM(__pyx_t_18, 1, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_18, 2, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyList_SET_ITEM(__pyx_t_18, 3, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_5);
  PyList_SET_ITEM(__pyx_t_18, 4, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_6);
  PyList_SET_ITEM(__pyx_t_18, 5, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_7);
  PyList_SET_ITEM(__pyx_t_18, 6, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_13);
  PyList_SET_ITEM(__pyx_t_18, 7, __pyx_t_13);
  __Pyx_GIVEREF(__pyx_t_14);
  PyList_SET_ITEM(__pyx_t_18, 8, __pyx_t_14);
  __Pyx_GIVEREF(__pyx_t_15);
  PyList_SET_ITEM(__pyx_t_18, 9, __pyx_t_15);
  __Pyx_GIVEREF(__pyx_t_16);
  PyList_SET_ITEM(__pyx_t_18, 10, __pyx_t_16);
  __Pyx_GIVEREF(__pyx_t_17);
  PyList_SET_ITEM(__pyx_t_18, 11, __pyx_t_17);
  __pyx_t_11 = 0;
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  __pyx_t_7 = 0;
  __pyx_t_13 = 0;
  __pyx_t_14 = 0;
  __pyx_t_15 = 0;
  __pyx_t_16 = 0;
  __pyx_t_17 = 0;
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg__pfconst);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg__pfconst, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 143, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS);
  __Pyx_DECREF_SET(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = PyTuple_New(2); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__pfnames);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__pfnames);
  PyTuple_SET_ITEM(__pyx_t_18, 0, __pyx_v_10simplejpeg_5_jpeg__pfnames);
  __Pyx_INCREF(__pyx_v_10simplejpeg_5_jpeg__pfconst);
  __Pyx_GIVEREF(__pyx_v_10simplejpeg_5_jpeg__pfconst);
  PyTuple_SET_ITEM(__pyx_t_18, 1, __pyx_v_10simplejpeg_5_jpeg__pfconst);
  __pyx_t_17 = __Pyx_PyObject_Call(__pyx_builtin_zip, __pyx_t_18, NULL); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 144, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_17);
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
  if (likely(PyList_CheckExact(__pyx_t_17)) || PyTuple_CheckExact(__pyx_t_17)) {
    __pyx_t_18 = __pyx_t_17; __Pyx_INCREF(__pyx_t_18); __pyx_t_8 = 0;
    __pyx_t_9 = NULL;
  } else {
    __pyx_t_8 = -1; __pyx_t_18 = PyObject_GetIter(__pyx_t_17); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 144, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_18);
    __pyx_t_9 = Py_TYPE(__pyx_t_18)->tp_iternext; if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 144, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
  for (;;) {
    if (likely(!__pyx_t_9)) {
      if (likely(PyList_CheckExact(__pyx_t_18))) {
        if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_18)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_17 = PyList_GET_ITEM(__pyx_t_18, __pyx_t_8); __Pyx_INCREF(__pyx_t_17); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 144, __pyx_L1_error)
        #else
        __pyx_t_17 = PySequence_ITEM(__pyx_t_18, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 144, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        #endif
      } else {
        if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_18)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_17 = PyTuple_GET_ITEM(__pyx_t_18, __pyx_t_8); __Pyx_INCREF(__pyx_t_17); __pyx_t_8++; if (unlikely(0 < 0)) __PYX_ERR(0, 144, __pyx_L1_error)
        #else
        __pyx_t_17 = PySequence_ITEM(__pyx_t_18, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 144, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        #endif
      }
    } else {
      __pyx_t_17 = __pyx_t_9(__pyx_t_18);
      if (unlikely(!__pyx_t_17)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 144, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_17);
    }
    if ((likely(PyTuple_CheckExact(__pyx_t_17))) || (PyList_CheckExact(__pyx_t_17))) {
      PyObject* sequence = __pyx_t_17;
      Py_ssize_t size = __Pyx_PySequence_SIZE(sequence);
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 144, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_16 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_15 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_16 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_15 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_16);
      __Pyx_INCREF(__pyx_t_15);
      #else
      __pyx_t_16 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __pyx_t_15 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_15);
      #endif
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_14 = PyObject_GetIter(__pyx_t_17); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 144, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_14);
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_14)->tp_iternext;
      index = 0; __pyx_t_16 = __pyx_t_10(__pyx_t_14); if (unlikely(!__pyx_t_16)) goto __pyx_L28_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_16);
      index = 1; __pyx_t_15 = __pyx_t_10(__pyx_t_14); if (unlikely(!__pyx_t_15)) goto __pyx_L28_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_15);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_14), 2) < 0) __PYX_ERR(0, 144, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
      goto __pyx_L29_unpacking_done;
      __pyx_L28_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 144, __pyx_L1_error)
      __pyx_L29_unpacking_done:;
    }
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_name, __pyx_t_16) < 0) __PYX_ERR(0, 144, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_pf, __pyx_t_15) < 0) __PYX_ERR(0, 144, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_17, __pyx_n_s_pf); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 145, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_GetModuleGlobalName(__pyx_t_15, __pyx_n_s_name); if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 145, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_15);
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_t_15, __pyx_t_17) < 0)) __PYX_ERR(0, 145, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_17, __pyx_n_s_pf); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_GetModuleGlobalName(__pyx_t_16, __pyx_n_s_name); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_t_16, __pyx_n_s_lower); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_14);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    __pyx_t_16 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_14))) {
      __pyx_t_16 = PyMethod_GET_SELF(__pyx_t_14);
      if (likely(__pyx_t_16)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_14);
        __Pyx_INCREF(__pyx_t_16);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_14, function);
      }
    }
    __pyx_t_15 = (__pyx_t_16) ? __Pyx_PyObject_CallOneArg(__pyx_t_14, __pyx_t_16) : __Pyx_PyObject_CallNoArg(__pyx_t_14);
    __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;
    if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_15);
    __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_t_15, __pyx_t_17) < 0)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

     
    __Pyx_GetModuleGlobalName(__pyx_t_17, __pyx_n_s_pf); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_GetModuleGlobalName(__pyx_t_14, __pyx_n_s_name); if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_14);
    __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_14, __pyx_n_s_upper); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
    __pyx_t_14 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_16))) {
      __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_16);
      if (likely(__pyx_t_14)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
        __Pyx_INCREF(__pyx_t_14);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_16, function);
      }
    }
    __pyx_t_15 = (__pyx_t_14) ? __Pyx_PyObject_CallOneArg(__pyx_t_16, __pyx_t_14) : __Pyx_PyObject_CallNoArg(__pyx_t_16);
    __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
    if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_15);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_10simplejpeg_5_jpeg_PIXELFORMATS, __pyx_t_15, __pyx_t_17) < 0)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

     
  }
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   
  __pyx_t_18 = PyCFunction_NewEx(&__pyx_mdef_10simplejpeg_5_jpeg_1decode_jpeg_header, NULL, __pyx_n_s_simplejpeg__jpeg); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_decode_jpeg_header, __pyx_t_18) < 0) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   
  __pyx_v_10simplejpeg_5_jpeg_DECODE_BUFFER_FLAGS = ((PyBUF_SIMPLE | PyBUF_WRITABLE) | PyBUF_ANY_CONTIGUOUS);

   
  __pyx_t_18 = PyCFunction_NewEx(&__pyx_mdef_10simplejpeg_5_jpeg_3decode_jpeg, NULL, __pyx_n_s_simplejpeg__jpeg); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_decode_jpeg, __pyx_t_18) < 0) __PYX_ERR(0, 260, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   
  __pyx_t_18 = PyCFunction_NewEx(&__pyx_mdef_10simplejpeg_5_jpeg_5encode_jpeg, NULL, __pyx_n_s_simplejpeg__jpeg); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 427, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_encode_jpeg, __pyx_t_18) < 0) __PYX_ERR(0, 427, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyDict_NewPresized(0); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test_2, __pyx_t_18) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   
  __pyx_t_18 = __pyx_capsule_create(((void *)(&__pyx_array_getbuffer)), ((char *)"getbuffer(obj, view, flags)")); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 210, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem((PyObject *)__pyx_array_type->tp_dict, __pyx_n_s_pyx_getbuffer, __pyx_t_18) < 0) __PYX_ERR(2, 210, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
  PyType_Modified(__pyx_array_type);

   
  __pyx_t_18 = __Pyx_PyObject_Call(((PyObject *)__pyx_MemviewEnum_type), __pyx_tuple__33, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 287, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(generic);
  __Pyx_DECREF_SET(generic, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyObject_Call(((PyObject *)__pyx_MemviewEnum_type), __pyx_tuple__34, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 288, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(strided);
  __Pyx_DECREF_SET(strided, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyObject_Call(((PyObject *)__pyx_MemviewEnum_type), __pyx_tuple__35, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 289, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(indirect);
  __Pyx_DECREF_SET(indirect, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyObject_Call(((PyObject *)__pyx_MemviewEnum_type), __pyx_tuple__36, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 292, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(contiguous);
  __Pyx_DECREF_SET(contiguous, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_t_18 = __Pyx_PyObject_Call(((PyObject *)__pyx_MemviewEnum_type), __pyx_tuple__37, NULL); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 293, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  __Pyx_XGOTREF(indirect_contiguous);
  __Pyx_DECREF_SET(indirect_contiguous, __pyx_t_18);
  __Pyx_GIVEREF(__pyx_t_18);
  __pyx_t_18 = 0;

   
  __pyx_memoryview_thread_locks_used = 0;

   
  __pyx_t_19[0] = PyThread_allocate_lock();
  __pyx_t_19[1] = PyThread_allocate_lock();
  __pyx_t_19[2] = PyThread_allocate_lock();
  __pyx_t_19[3] = PyThread_allocate_lock();
  __pyx_t_19[4] = PyThread_allocate_lock();
  __pyx_t_19[5] = PyThread_allocate_lock();
  __pyx_t_19[6] = PyThread_allocate_lock();
  __pyx_t_19[7] = PyThread_allocate_lock();
  memcpy(&(__pyx_memoryview_thread_locks[0]), __pyx_t_19, sizeof(__pyx_memoryview_thread_locks[0]) * (8));

   
  __pyx_t_18 = __pyx_capsule_create(((void *)(&__pyx_memoryview_getbuffer)), ((char *)"getbuffer(obj, view, flags)")); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 551, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem((PyObject *)__pyx_memoryview_type->tp_dict, __pyx_n_s_pyx_getbuffer, __pyx_t_18) < 0) __PYX_ERR(2, 551, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
  PyType_Modified(__pyx_memoryview_type);

   
  __pyx_t_18 = __pyx_capsule_create(((void *)(&__pyx_memoryview_getbuffer)), ((char *)"getbuffer(obj, view, flags)")); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 997, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem((PyObject *)__pyx_memoryviewslice_type->tp_dict, __pyx_n_s_pyx_getbuffer, __pyx_t_18) < 0) __PYX_ERR(2, 997, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
  PyType_Modified(__pyx_memoryviewslice_type);

   
  __pyx_t_18 = PyCFunction_NewEx(&__pyx_mdef_15View_dot_MemoryView_1__pyx_unpickle_Enum, NULL, __pyx_n_s_View_MemoryView); if (unlikely(!__pyx_t_18)) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_18);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyx_unpickle_Enum, __pyx_t_18) < 0) __PYX_ERR(2, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;

   

   

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_13);
  __Pyx_XDECREF(__pyx_t_14);
  __Pyx_XDECREF(__pyx_t_15);
  __Pyx_XDECREF(__pyx_t_16);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_XDECREF(__pyx_t_18);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init simplejpeg._jpeg", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_CLEAR(__pyx_m);
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init simplejpeg._jpeg");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if CYTHON_PEP489_MULTI_PHASE_INIT
  return (__pyx_m != NULL) ? 0 : -1;
  #elif PY_MAJOR_VERSION >= 3
  return __pyx_m;
  #else
  return;
  #endif
}

 
 
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule(modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, "RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

 
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#endif

 
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

 
static CYTHON_INLINE PyObject* __Pyx_decode_c_string(
         const char* cstring, Py_ssize_t start, Py_ssize_t stop,
         const char* encoding, const char* errors,
         PyObject* (*decode_func)(const char *s, Py_ssize_t size, const char *errors)) {
    Py_ssize_t length;
    if (unlikely((start < 0) | (stop < 0))) {
        size_t slen = strlen(cstring);
        if (unlikely(slen > (size_t) PY_SSIZE_T_MAX)) {
            PyErr_SetString(PyExc_OverflowError,
                            "c-string too long to convert to Python");
            return NULL;
        }
        length = (Py_ssize_t) slen;
        if (start < 0) {
            start += length;
            if (start < 0)
                start = 0;
        }
        if (stop < 0)
            stop += length;
    }
    if (unlikely(stop <= start))
        return __Pyx_NewRef(__pyx_empty_unicode);
    length = stop - start;
    cstring += start;
    if (decode_func) {
        return decode_func(cstring, length, errors);
    } else {
        return PyUnicode_Decode(cstring, length, encoding, errors);
    }
}

 
static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

 
static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (__Pyx_PyUnicode_GET_LENGTH(**name) != __Pyx_PyUnicode_GET_LENGTH(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (__Pyx_PyUnicode_GET_LENGTH(**argname) != __Pyx_PyUnicode_GET_LENGTH(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

 
static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%.200s() takes %.8s %" CYTHON_FORMAT_SSIZE_T "d positional argument%.1s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = Py_TYPE(func)->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

 
#if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
}
#endif

 
#if PY_MAJOR_VERSION < 3
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        CYTHON_UNUSED PyObject *cause) {
    __Pyx_PyThreadState_declare
    Py_XINCREF(type);
    if (!value || value == Py_None)
        value = NULL;
    else
        Py_INCREF(value);
    if (!tb || tb == Py_None)
        tb = NULL;
    else {
        Py_INCREF(tb);
        if (!PyTraceBack_Check(tb)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: arg 3 must be a traceback or None");
            goto raise_error;
        }
    }
    if (PyType_Check(type)) {
#if CYTHON_COMPILING_IN_PYPY
        if (!value) {
            Py_INCREF(Py_None);
            value = Py_None;
        }
#endif
        PyErr_NormalizeException(&type, &value, &tb);
    } else {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        value = type;
        type = (PyObject*) Py_TYPE(type);
        Py_INCREF(type);
        if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: exception class must be a subclass of BaseException");
            goto raise_error;
        }
    }
    __Pyx_PyThreadState_assign
    __Pyx_ErrRestore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}
#else
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause) {
    PyObject* owned_instance = NULL;
    if (tb == Py_None) {
        tb = 0;
    } else if (tb && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto bad;
    }
    if (value == Py_None)
        value = 0;
    if (PyExceptionInstance_Check(type)) {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto bad;
        }
        value = type;
        type = (PyObject*) Py_TYPE(value);
    } else if (PyExceptionClass_Check(type)) {
        PyObject *instance_class = NULL;
        if (value && PyExceptionInstance_Check(value)) {
            instance_class = (PyObject*) Py_TYPE(value);
            if (instance_class != type) {
                int is_subclass = PyObject_IsSubclass(instance_class, type);
                if (!is_subclass) {
                    instance_class = NULL;
                } else if (unlikely(is_subclass == -1)) {
                    goto bad;
                } else {
                    type = instance_class;
                }
            }
        }
        if (!instance_class) {
            PyObject *args;
            if (!value)
                args = PyTuple_New(0);
            else if (PyTuple_Check(value)) {
                Py_INCREF(value);
                args = value;
            } else
                args = PyTuple_Pack(1, value);
            if (!args)
                goto bad;
            owned_instance = PyObject_Call(type, args, NULL);
            Py_DECREF(args);
            if (!owned_instance)
                goto bad;
            value = owned_instance;
            if (!PyExceptionInstance_Check(value)) {
                PyErr_Format(PyExc_TypeError,
                             "calling %R should have returned an instance of "
                             "BaseException, not %R",
                             type, Py_TYPE(value));
                goto bad;
            }
        }
    } else {
        PyErr_SetString(PyExc_TypeError,
            "raise: exception class must be a subclass of BaseException");
        goto bad;
    }
    if (cause) {
        PyObject *fixed_cause;
        if (cause == Py_None) {
            fixed_cause = NULL;
        } else if (PyExceptionClass_Check(cause)) {
            fixed_cause = PyObject_CallObject(cause, NULL);
            if (fixed_cause == NULL)
                goto bad;
        } else if (PyExceptionInstance_Check(cause)) {
            fixed_cause = cause;
            Py_INCREF(fixed_cause);
        } else {
            PyErr_SetString(PyExc_TypeError,
                            "exception causes must derive from "
                            "BaseException");
            goto bad;
        }
        PyException_SetCause(value, fixed_cause);
    }
    PyErr_SetObject(type, value);
    if (tb) {
#if CYTHON_FAST_THREAD_STATE
        PyThreadState *tstate = __Pyx_PyThreadState_Current;
        PyObject* tmp_tb = tstate->curexc_traceback;
        if (tb != tmp_tb) {
            Py_INCREF(tb);
            tstate->curexc_traceback = tb;
            Py_XDECREF(tmp_tb);
        }
#else
        PyObject *tmp_type, *tmp_value, *tmp_tb;
        PyErr_Fetch(&tmp_type, &tmp_value, &tmp_tb);
        Py_INCREF(tb);
        PyErr_Restore(tmp_type, tmp_value, tb);
        Py_XDECREF(tmp_tb);
#endif
    }
bad:
    Py_XDECREF(owned_instance);
    return;
}
#endif

 
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject * __Pyx_PyCFunction_FastCall(PyObject *func_obj, PyObject **args, Py_ssize_t nargs) {
    PyCFunctionObject *func = (PyCFunctionObject*)func_obj;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    int flags = PyCFunction_GET_FLAGS(func);
    assert(PyCFunction_Check(func));
    assert(METH_FASTCALL == (flags & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS | METH_STACKLESS)));
    assert(nargs >= 0);
    assert(nargs == 0 || args != NULL);
     
    assert(!PyErr_Occurred());
    if ((PY_VERSION_HEX < 0x030700A0) || unlikely(flags & METH_KEYWORDS)) {
        return (*((__Pyx_PyCFunctionFastWithKeywords)(void*)meth)) (self, args, nargs, NULL);
    } else {
        return (*((__Pyx_PyCFunctionFast)(void*)meth)) (self, args, nargs);
    }
}
#endif

 
#if CYTHON_FAST_PYCALL
static PyObject* __Pyx_PyFunction_FastCallNoKw(PyCodeObject *co, PyObject **args, Py_ssize_t na,
                                               PyObject *globals) {
    PyFrameObject *f;
    PyThreadState *tstate = __Pyx_PyThreadState_Current;
    PyObject **fastlocals;
    Py_ssize_t i;
    PyObject *result;
    assert(globals != NULL);
     
    assert(tstate != NULL);
    f = PyFrame_New(tstate, co, globals, NULL);
    if (f == NULL) {
        return NULL;
    }
    fastlocals = __Pyx_PyFrame_GetLocalsplus(f);
    for (i = 0; i < na; i++) {
        Py_INCREF(*args);
        fastlocals[i] = *args++;
    }
    result = PyEval_EvalFrameEx(f,0);
    ++tstate->recursion_depth;
    Py_DECREF(f);
    --tstate->recursion_depth;
    return result;
}
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, Py_ssize_t nargs, PyObject *kwargs) {
    PyCodeObject *co = (PyCodeObject *)PyFunction_GET_CODE(func);
    PyObject *globals = PyFunction_GET_GLOBALS(func);
    PyObject *argdefs = PyFunction_GET_DEFAULTS(func);
    PyObject *closure;
#if PY_MAJOR_VERSION >= 3
    PyObject *kwdefs;
#endif
    PyObject *kwtuple, **k;
    PyObject **d;
    Py_ssize_t nd;
    Py_ssize_t nk;
    PyObject *result;
    assert(kwargs == NULL || PyDict_Check(kwargs));
    nk = kwargs ? PyDict_Size(kwargs) : 0;
    if (Py_EnterRecursiveCall((char*)" while calling a Python object")) {
        return NULL;
    }
    if (
#if PY_MAJOR_VERSION >= 3
            co->co_kwonlyargcount == 0 &&
#endif
            likely(kwargs == NULL || nk == 0) &&
            co->co_flags == (CO_OPTIMIZED | CO_NEWLOCALS | CO_NOFREE)) {
        if (argdefs == NULL && co->co_argcount == nargs) {
            result = __Pyx_PyFunction_FastCallNoKw(co, args, nargs, globals);
            goto done;
        }
        else if (nargs == 0 && argdefs != NULL
                 && co->co_argcount == Py_SIZE(argdefs)) {
             
            args = &PyTuple_GET_ITEM(argdefs, 0);
            result =__Pyx_PyFunction_FastCallNoKw(co, args, Py_SIZE(argdefs), globals);
            goto done;
        }
    }
    if (kwargs != NULL) {
        Py_ssize_t pos, i;
        kwtuple = PyTuple_New(2 * nk);
        if (kwtuple == NULL) {
            result = NULL;
            goto done;
        }
        k = &PyTuple_GET_ITEM(kwtuple, 0);
        pos = i = 0;
        while (PyDict_Next(kwargs, &pos, &k[i], &k[i+1])) {
            Py_INCREF(k[i]);
            Py_INCREF(k[i+1]);
            i += 2;
        }
        nk = i / 2;
    }
    else {
        kwtuple = NULL;
        k = NULL;
    }
    closure = PyFunction_GET_CLOSURE(func);
#if PY_MAJOR_VERSION >= 3
    kwdefs = PyFunction_GET_KW_DEFAULTS(func);
#endif
    if (argdefs != NULL) {
        d = &PyTuple_GET_ITEM(argdefs, 0);
        nd = Py_SIZE(argdefs);
    }
    else {
        d = NULL;
        nd = 0;
    }
#if PY_MAJOR_VERSION >= 3
    result = PyEval_EvalCodeEx((PyObject*)co, globals, (PyObject *)NULL,
                               args, (int)nargs,
                               k, (int)nk,
                               d, (int)nd, kwdefs, closure);
#else
    result = PyEval_EvalCodeEx(co, globals, (PyObject *)NULL,
                               args, (int)nargs,
                               k, (int)nk,
                               d, (int)nd, closure);
#endif
    Py_XDECREF(kwtuple);
done:
    Py_LeaveRecursiveCall();
    return result;
}
#endif
#endif

 
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

 
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, &arg, 1);
    }
#endif
    if (likely(PyCFunction_Check(func))) {
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
#if CYTHON_FAST_PYCCALL
        } else if (__Pyx_PyFastCFunction_Check(func)) {
            return __Pyx_PyCFunction_FastCall(func, &arg, 1);
#endif
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_Pack(1, arg);
    if (unlikely(!args)) return NULL;
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
#endif

 
static PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    Py_ssize_t wrapped_i = i;
    if (wraparound & unlikely(i < 0)) {
        wrapped_i += PyList_GET_SIZE(o);
    }
    if ((!boundscheck) || likely(__Pyx_is_valid_index(wrapped_i, PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, wrapped_i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    Py_ssize_t wrapped_i = i;
    if (wraparound & unlikely(i < 0)) {
        wrapped_i += PyTuple_GET_SIZE(o);
    }
    if ((!boundscheck) || likely(__Pyx_is_valid_index(wrapped_i, PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, wrapped_i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i, int is_list,
                                                     CYTHON_NCP_UNUSED int wraparound,
                                                     CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS && CYTHON_USE_TYPE_SLOTS
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely(__Pyx_is_valid_index(n, PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely(__Pyx_is_valid_index(n, PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                        return NULL;
                    PyErr_Clear();
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

 
static int
__Pyx_init_memviewslice(struct __pyx_memoryview_obj *memview,
                        int ndim,
                        __Pyx_memviewslice *memviewslice,
                        int memview_is_new_reference)
{
    __Pyx_RefNannyDeclarations
    int i, retval=-1;
    Py_buffer *buf = &memview->view;
    __Pyx_RefNannySetupContext("init_memviewslice", 0);
    if (unlikely(memviewslice->memview || memviewslice->data)) {
        PyErr_SetString(PyExc_ValueError,
            "memviewslice is already initialized!");
        goto fail;
    }
    if (buf->strides) {
        for (i = 0; i < ndim; i++) {
            memviewslice->strides[i] = buf->strides[i];
        }
    } else {
        Py_ssize_t stride = buf->itemsize;
        for (i = ndim - 1; i >= 0; i--) {
            memviewslice->strides[i] = stride;
            stride *= buf->shape[i];
        }
    }
    for (i = 0; i < ndim; i++) {
        memviewslice->shape[i]   = buf->shape[i];
        if (buf->suboffsets) {
            memviewslice->suboffsets[i] = buf->suboffsets[i];
        } else {
            memviewslice->suboffsets[i] = -1;
        }
    }
    memviewslice->memview = memview;
    memviewslice->data = (char *)buf->buf;
    if (__pyx_add_acquisition_count(memview) == 0 && !memview_is_new_reference) {
        Py_INCREF(memview);
    }
    retval = 0;
    goto no_fail;
fail:
    memviewslice->memview = 0;
    memviewslice->data = 0;
    retval = -1;
no_fail:
    __Pyx_RefNannyFinishContext();
    return retval;
}
#ifndef Py_NO_RETURN
#define Py_NO_RETURN
#endif
static void __pyx_fatalerror(const char *fmt, ...) Py_NO_RETURN {
    va_list vargs;
    char msg[200];
#if PY_VERSION_HEX >= 0x030A0000 || defined(HAVE_STDARG_PROTOTYPES)
    va_start(vargs, fmt);
#else
    va_start(vargs);
#endif
    vsnprintf(msg, 200, fmt, vargs);
    va_end(vargs);
    Py_FatalError(msg);
}
static CYTHON_INLINE int
__pyx_add_acquisition_count_locked(__pyx_atomic_int *acquisition_count,
                                   PyThread_type_lock lock)
{
    int result;
    PyThread_acquire_lock(lock, 1);
    result = (*acquisition_count)++;
    PyThread_release_lock(lock);
    return result;
}
static CYTHON_INLINE int
__pyx_sub_acquisition_count_locked(__pyx_atomic_int *acquisition_count,
                                   PyThread_type_lock lock)
{
    int result;
    PyThread_acquire_lock(lock, 1);
    result = (*acquisition_count)--;
    PyThread_release_lock(lock);
    return result;
}
static CYTHON_INLINE void
__Pyx_INC_MEMVIEW(__Pyx_memviewslice *memslice, int have_gil, int lineno)
{
    int first_time;
    struct __pyx_memoryview_obj *memview = memslice->memview;
    if (unlikely(!memview || (PyObject *) memview == Py_None))
        return;
    if (unlikely(__pyx_get_slice_count(memview) < 0))
        __pyx_fatalerror("Acquisition count is %d (line %d)",
                         __pyx_get_slice_count(memview), lineno);
    first_time = __pyx_add_acquisition_count(memview) == 0;
    if (unlikely(first_time)) {
        if (have_gil) {
            Py_INCREF((PyObject *) memview);
        } else {
            PyGILState_STATE _gilstate = PyGILState_Ensure();
            Py_INCREF((PyObject *) memview);
            PyGILState_Release(_gilstate);
        }
    }
}
static CYTHON_INLINE void __Pyx_XDEC_MEMVIEW(__Pyx_memviewslice *memslice,
                                             int have_gil, int lineno) {
    int last_time;
    struct __pyx_memoryview_obj *memview = memslice->memview;
    if (unlikely(!memview || (PyObject *) memview == Py_None)) {
        memslice->memview = NULL;
        return;
    }
    if (unlikely(__pyx_get_slice_count(memview) <= 0))
        __pyx_fatalerror("Acquisition count is %d (line %d)",
                         __pyx_get_slice_count(memview), lineno);
    last_time = __pyx_sub_acquisition_count(memview) == 1;
    memslice->data = NULL;
    if (unlikely(last_time)) {
        if (have_gil) {
            Py_CLEAR(memslice->memview);
        } else {
            PyGILState_STATE _gilstate = PyGILState_Ensure();
            Py_CLEAR(memslice->memview);
            PyGILState_Release(_gilstate);
        }
    } else {
        memslice->memview = NULL;
    }
}

 
static int __Pyx__ArgTypeTest(PyObject *obj, PyTypeObject *type, const char *name, int exact)
{
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    else if (exact) {
        #if PY_MAJOR_VERSION == 2
        if ((type == &PyBaseString_Type) && likely(__Pyx_PyBaseString_CheckExact(obj))) return 1;
        #endif
    }
    else {
        if (likely(__Pyx_TypeCheck(obj, type))) return 1;
    }
    PyErr_Format(PyExc_TypeError,
        "Argument '%.200s' has incorrect type (expected %.200s, got %.200s)",
        name, type->tp_name, Py_TYPE(obj)->tp_name);
    return 0;
}

 
#if PY_MAJOR_VERSION >= 3 && !CYTHON_COMPILING_IN_PYPY
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key) {
    PyObject *value;
    value = PyDict_GetItemWithError(d, key);
    if (unlikely(!value)) {
        if (!PyErr_Occurred()) {
            if (unlikely(PyTuple_Check(key))) {
                PyObject* args = PyTuple_Pack(1, key);
                if (likely(args)) {
                    PyErr_SetObject(PyExc_KeyError, args);
                    Py_DECREF(args);
                }
            } else {
                PyErr_SetObject(PyExc_KeyError, key);
            }
        }
        return NULL;
    }
    Py_INCREF(value);
    return value;
}
#endif

 
static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type) {
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (likely(__Pyx_TypeCheck(obj, type)))
        return 1;
    PyErr_Format(PyExc_TypeError, "Cannot convert %.200s to %.200s",
                 Py_TYPE(obj)->tp_name, type->tp_name);
    return 0;
}

 
static CYTHON_INLINE int __Pyx_Is_Little_Endian(void)
{
  union {
    uint32_t u32;
    uint8_t u8[4];
  } S;
  S.u32 = 0x01020304;
  return S.u8[0] == 4;
}

 
static void __Pyx_BufFmt_Init(__Pyx_BufFmt_Context* ctx,
                              __Pyx_BufFmt_StackElem* stack,
                              __Pyx_TypeInfo* type) {
  stack[0].field = &ctx->root;
  stack[0].parent_offset = 0;
  ctx->root.type = type;
  ctx->root.name = "buffer dtype";
  ctx->root.offset = 0;
  ctx->head = stack;
  ctx->head->field = &ctx->root;
  ctx->fmt_offset = 0;
  ctx->head->parent_offset = 0;
  ctx->new_packmode = '@';
  ctx->enc_packmode = '@';
  ctx->new_count = 1;
  ctx->enc_count = 0;
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  ctx->is_valid_array = 0;
  ctx->struct_alignment = 0;
  while (type->typegroup == 'S') {
    ++ctx->head;
    ctx->head->field = type->fields;
    ctx->head->parent_offset = 0;
    type = type->fields->type;
  }
}
static int __Pyx_BufFmt_ParseNumber(const char** ts) {
    int count;
    const char* t = *ts;
    if (*t < '0' || *t > '9') {
      return -1;
    } else {
        count = *t++ - '0';
        while (*t >= '0' && *t <= '9') {
            count *= 10;
            count += *t++ - '0';
        }
    }
    *ts = t;
    return count;
}
static int __Pyx_BufFmt_ExpectNumber(const char **ts) {
    int number = __Pyx_BufFmt_ParseNumber(ts);
    if (number == -1)
        PyErr_Format(PyExc_ValueError,\
                     "Does not understand character buffer dtype format string ('%c')", **ts);
    return number;
}
static void __Pyx_BufFmt_RaiseUnexpectedChar(char ch) {
  PyErr_Format(PyExc_ValueError,
               "Unexpected format string character: '%c'", ch);
}
static const char* __Pyx_BufFmt_DescribeTypeChar(char ch, int is_complex) {
  switch (ch) {
    case '?': return "'bool'";
    case 'c': return "'char'";
    case 'b': return "'signed char'";
    case 'B': return "'unsigned char'";
    case 'h': return "'short'";
    case 'H': return "'unsigned short'";
    case 'i': return "'int'";
    case 'I': return "'unsigned int'";
    case 'l': return "'long'";
    case 'L': return "'unsigned long'";
    case 'q': return "'long long'";
    case 'Q': return "'unsigned long long'";
    case 'f': return (is_complex ? "'complex float'" : "'float'");
    case 'd': return (is_complex ? "'complex double'" : "'double'");
    case 'g': return (is_complex ? "'complex long double'" : "'long double'");
    case 'T': return "a struct";
    case 'O': return "Python object";
    case 'P': return "a pointer";
    case 's': case 'p': return "a string";
    case 0: return "end";
    default: return "unparseable format string";
  }
}
static size_t __Pyx_BufFmt_TypeCharToStandardSize(char ch, int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return 2;
    case 'i': case 'I': case 'l': case 'L': return 4;
    case 'q': case 'Q': return 8;
    case 'f': return (is_complex ? 8 : 4);
    case 'd': return (is_complex ? 16 : 8);
    case 'g': {
      PyErr_SetString(PyExc_ValueError, "Python does not define a standard format string size for long double ('g')..");
      return 0;
    }
    case 'O': case 'P': return sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static size_t __Pyx_BufFmt_TypeCharToNativeSize(char ch, int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(short);
    case 'i': case 'I': return sizeof(int);
    case 'l': case 'L': return sizeof(long);
    #ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(PY_LONG_LONG);
    #endif
    case 'f': return sizeof(float) * (is_complex ? 2 : 1);
    case 'd': return sizeof(double) * (is_complex ? 2 : 1);
    case 'g': return sizeof(long double) * (is_complex ? 2 : 1);
    case 'O': case 'P': return sizeof(void*);
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
typedef struct { char c; short x; } __Pyx_st_short;
typedef struct { char c; int x; } __Pyx_st_int;
typedef struct { char c; long x; } __Pyx_st_long;
typedef struct { char c; float x; } __Pyx_st_float;
typedef struct { char c; double x; } __Pyx_st_double;
typedef struct { char c; long double x; } __Pyx_st_longdouble;
typedef struct { char c; void *x; } __Pyx_st_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { char c; PY_LONG_LONG x; } __Pyx_st_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToAlignment(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_st_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_st_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_st_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_st_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_st_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_st_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_st_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_st_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
 
typedef struct { short x; char c; } __Pyx_pad_short;
typedef struct { int x; char c; } __Pyx_pad_int;
typedef struct { long x; char c; } __Pyx_pad_long;
typedef struct { float x; char c; } __Pyx_pad_float;
typedef struct { double x; char c; } __Pyx_pad_double;
typedef struct { long double x; char c; } __Pyx_pad_longdouble;
typedef struct { void *x; char c; } __Pyx_pad_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { PY_LONG_LONG x; char c; } __Pyx_pad_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToPadding(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_pad_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_pad_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_pad_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_pad_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_pad_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_pad_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_pad_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_pad_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static char __Pyx_BufFmt_TypeCharToGroup(char ch, int is_complex) {
  switch (ch) {
    case 'c':
        return 'H';
    case 'b': case 'h': case 'i':
    case 'l': case 'q': case 's': case 'p':
        return 'I';
    case '?': case 'B': case 'H': case 'I': case 'L': case 'Q':
        return 'U';
    case 'f': case 'd': case 'g':
        return (is_complex ? 'C' : 'R');
    case 'O':
        return 'O';
    case 'P':
        return 'P';
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
static void __Pyx_BufFmt_RaiseExpected(__Pyx_BufFmt_Context* ctx) {
  if (ctx->head == NULL || ctx->head->field == &ctx->root) {
    const char* expected;
    const char* quote;
    if (ctx->head == NULL) {
      expected = "end";
      quote = "";
    } else {
      expected = ctx->head->field->type->name;
      quote = "'";
    }
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected %s%s%s but got %s",
                 quote, expected, quote,
                 __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex));
  } else {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_StructField* parent = (ctx->head - 1)->field;
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected '%s' but got %s in '%s.%s'",
                 field->type->name, __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex),
                 parent->type->name, field->name);
  }
}
static int __Pyx_BufFmt_ProcessTypeChunk(__Pyx_BufFmt_Context* ctx) {
  char group;
  size_t size, offset, arraysize = 1;
  if (ctx->enc_type == 0) return 0;
  if (ctx->head->field->type->arraysize[0]) {
    int i, ndim = 0;
    if (ctx->enc_type == 's' || ctx->enc_type == 'p') {
        ctx->is_valid_array = ctx->head->field->type->ndim == 1;
        ndim = 1;
        if (ctx->enc_count != ctx->head->field->type->arraysize[0]) {
            PyErr_Format(PyExc_ValueError,
                         "Expected a dimension of size %zu, got %zu",
                         ctx->head->field->type->arraysize[0], ctx->enc_count);
            return -1;
        }
    }
    if (!ctx->is_valid_array) {
      PyErr_Format(PyExc_ValueError, "Expected %d dimensions, got %d",
                   ctx->head->field->type->ndim, ndim);
      return -1;
    }
    for (i = 0; i < ctx->head->field->type->ndim; i++) {
      arraysize *= ctx->head->field->type->arraysize[i];
    }
    ctx->is_valid_array = 0;
    ctx->enc_count = 1;
  }
  group = __Pyx_BufFmt_TypeCharToGroup(ctx->enc_type, ctx->is_complex);
  do {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_TypeInfo* type = field->type;
    if (ctx->enc_packmode == '@' || ctx->enc_packmode == '^') {
      size = __Pyx_BufFmt_TypeCharToNativeSize(ctx->enc_type, ctx->is_complex);
    } else {
      size = __Pyx_BufFmt_TypeCharToStandardSize(ctx->enc_type, ctx->is_complex);
    }
    if (ctx->enc_packmode == '@') {
      size_t align_at = __Pyx_BufFmt_TypeCharToAlignment(ctx->enc_type, ctx->is_complex);
      size_t align_mod_offset;
      if (align_at == 0) return -1;
      align_mod_offset = ctx->fmt_offset % align_at;
      if (align_mod_offset > 0) ctx->fmt_offset += align_at - align_mod_offset;
      if (ctx->struct_alignment == 0)
          ctx->struct_alignment = __Pyx_BufFmt_TypeCharToPadding(ctx->enc_type,
                                                                 ctx->is_complex);
    }
    if (type->size != size || type->typegroup != group) {
      if (type->typegroup == 'C' && type->fields != NULL) {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        ++ctx->head;
        ctx->head->field = type->fields;
        ctx->head->parent_offset = parent_offset;
        continue;
      }
      if ((type->typegroup == 'H' || group == 'H') && type->size == size) {
      } else {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
      }
    }
    offset = ctx->head->parent_offset + field->offset;
    if (ctx->fmt_offset != offset) {
      PyErr_Format(PyExc_ValueError,
                   "Buffer dtype mismatch; next field is at offset %" CYTHON_FORMAT_SSIZE_T "d but %" CYTHON_FORMAT_SSIZE_T "d expected",
                   (Py_ssize_t)ctx->fmt_offset, (Py_ssize_t)offset);
      return -1;
    }
    ctx->fmt_offset += size;
    if (arraysize)
      ctx->fmt_offset += (arraysize - 1) * size;
    --ctx->enc_count;
    while (1) {
      if (field == &ctx->root) {
        ctx->head = NULL;
        if (ctx->enc_count != 0) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
        }
        break;
      }
      ctx->head->field = ++field;
      if (field->type == NULL) {
        --ctx->head;
        field = ctx->head->field;
        continue;
      } else if (field->type->typegroup == 'S') {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        if (field->type->fields->type == NULL) continue;
        field = field->type->fields;
        ++ctx->head;
        ctx->head->field = field;
        ctx->head->parent_offset = parent_offset;
        break;
      } else {
        break;
      }
    }
  } while (ctx->enc_count);
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  return 0;
}
static PyObject *
__pyx_buffmt_parse_array(__Pyx_BufFmt_Context* ctx, const char** tsp)
{
    const char *ts = *tsp;
    int i = 0, number, ndim;
    ++ts;
    if (ctx->new_count != 1) {
        PyErr_SetString(PyExc_ValueError,
                        "Cannot handle repeated arrays in format string");
        return NULL;
    }
    if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
    ndim = ctx->head->field->type->ndim;
    while (*ts && *ts != ')') {
        switch (*ts) {
            case ' ': case '\f': case '\r': case '\n': case '\t': case '\v':  continue;
            default:  break;
        }
        number = __Pyx_BufFmt_ExpectNumber(&ts);
        if (number == -1) return NULL;
        if (i < ndim && (size_t) number != ctx->head->field->type->arraysize[i])
            return PyErr_Format(PyExc_ValueError,
                        "Expected a dimension of size %zu, got %d",
                        ctx->head->field->type->arraysize[i], number);
        if (*ts != ',' && *ts != ')')
            return PyErr_Format(PyExc_ValueError,
                                "Expected a comma in format string, got '%c'", *ts);
        if (*ts == ',') ts++;
        i++;
    }
    if (i != ndim)
        return PyErr_Format(PyExc_ValueError, "Expected %d dimension(s), got %d",
                            ctx->head->field->type->ndim, i);
    if (!*ts) {
        PyErr_SetString(PyExc_ValueError,
                        "Unexpected end of format string, expected ')'");
        return NULL;
    }
    ctx->is_valid_array = 1;
    ctx->new_count = 1;
    *tsp = ++ts;
    return Py_None;
}
static const char* __Pyx_BufFmt_CheckString(__Pyx_BufFmt_Context* ctx, const char* ts) {
  int got_Z = 0;
  while (1) {
    switch(*ts) {
      case 0:
        if (ctx->enc_type != 0 && ctx->head == NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        if (ctx->head != NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
        return ts;
      case ' ':
      case '\r':
      case '\n':
        ++ts;
        break;
      case '<':
        if (!__Pyx_Is_Little_Endian()) {
          PyErr_SetString(PyExc_ValueError, "Little-endian buffer not supported on big-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '>':
      case '!':
        if (__Pyx_Is_Little_Endian()) {
          PyErr_SetString(PyExc_ValueError, "Big-endian buffer not supported on little-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '=':
      case '@':
      case '^':
        ctx->new_packmode = *ts++;
        break;
      case 'T':
        {
          const char* ts_after_sub;
          size_t i, struct_count = ctx->new_count;
          size_t struct_alignment = ctx->struct_alignment;
          ctx->new_count = 1;
          ++ts;
          if (*ts != '{') {
            PyErr_SetString(PyExc_ValueError, "Buffer acquisition: Expected '{' after 'T'");
            return NULL;
          }
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0;
          ctx->enc_count = 0;
          ctx->struct_alignment = 0;
          ++ts;
          ts_after_sub = ts;
          for (i = 0; i != struct_count; ++i) {
            ts_after_sub = __Pyx_BufFmt_CheckString(ctx, ts);
            if (!ts_after_sub) return NULL;
          }
          ts = ts_after_sub;
          if (struct_alignment) ctx->struct_alignment = struct_alignment;
        }
        break;
      case '}':
        {
          size_t alignment = ctx->struct_alignment;
          ++ts;
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0;
          if (alignment && ctx->fmt_offset % alignment) {
            ctx->fmt_offset += alignment - (ctx->fmt_offset % alignment);
          }
        }
        return ts;
      case 'x':
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        ctx->fmt_offset += ctx->new_count;
        ctx->new_count = 1;
        ctx->enc_count = 0;
        ctx->enc_type = 0;
        ctx->enc_packmode = ctx->new_packmode;
        ++ts;
        break;
      case 'Z':
        got_Z = 1;
        ++ts;
        if (*ts != 'f' && *ts != 'd' && *ts != 'g') {
          __Pyx_BufFmt_RaiseUnexpectedChar('Z');
          return NULL;
        }
        CYTHON_FALLTHROUGH;
      case '?': case 'c': case 'b': case 'B': case 'h': case 'H': case 'i': case 'I':
      case 'l': case 'L': case 'q': case 'Q':
      case 'f': case 'd': case 'g':
      case 'O': case 'p':
        if ((ctx->enc_type == *ts) && (got_Z == ctx->is_complex) &&
            (ctx->enc_packmode == ctx->new_packmode) && (!ctx->is_valid_array)) {
          ctx->enc_count += ctx->new_count;
          ctx->new_count = 1;
          got_Z = 0;
          ++ts;
          break;
        }
        CYTHON_FALLTHROUGH;
      case 's':
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        ctx->enc_count = ctx->new_count;
        ctx->enc_packmode = ctx->new_packmode;
        ctx->enc_type = *ts;
        ctx->is_complex = got_Z;
        ++ts;
        ctx->new_count = 1;
        got_Z = 0;
        break;
      case ':':
        ++ts;
        while(*ts != ':') ++ts;
        ++ts;
        break;
      case '(':
        if (!__pyx_buffmt_parse_array(ctx, &ts)) return NULL;
        break;
      default:
        {
          int number = __Pyx_BufFmt_ExpectNumber(&ts);
          if (number == -1) return NULL;
          ctx->new_count = (size_t)number;
        }
    }
  }
}

 
  static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info) {
  if (unlikely(info->buf == NULL)) return;
  if (info->suboffsets == __Pyx_minusones) info->suboffsets = NULL;
  __Pyx_ReleaseBuffer(info);
}
static void __Pyx_ZeroBuffer(Py_buffer* buf) {
  buf->buf = NULL;
  buf->obj = NULL;
  buf->strides = __Pyx_zeros;
  buf->shape = __Pyx_zeros;
  buf->suboffsets = __Pyx_minusones;
}
static int __Pyx__GetBufferAndValidate(
        Py_buffer* buf, PyObject* obj,  __Pyx_TypeInfo* dtype, int flags,
        int nd, int cast, __Pyx_BufFmt_StackElem* stack)
{
  buf->buf = NULL;
  if (unlikely(__Pyx_GetBuffer(obj, buf, flags) == -1)) {
    __Pyx_ZeroBuffer(buf);
    return -1;
  }
  if (unlikely(buf->ndim != nd)) {
    PyErr_Format(PyExc_ValueError,
                 "Buffer has wrong number of dimensions (expected %d, got %d)",
                 nd, buf->ndim);
    goto fail;
  }
  if (!cast) {
    __Pyx_BufFmt_Context ctx;
    __Pyx_BufFmt_Init(&ctx, stack, dtype);
    if (!__Pyx_BufFmt_CheckString(&ctx, buf->format)) goto fail;
  }
  if (unlikely((size_t)buf->itemsize != dtype->size)) {
    PyErr_Format(PyExc_ValueError,
      "Item size of buffer (%" CYTHON_FORMAT_SSIZE_T "d byte%s) does not match size of '%s' (%" CYTHON_FORMAT_SSIZE_T "d byte%s)",
      buf->itemsize, (buf->itemsize > 1) ? "s" : "",
      dtype->name, (Py_ssize_t)dtype->size, (dtype->size > 1) ? "s" : "");
    goto fail;
  }
  if (buf->suboffsets == NULL) buf->suboffsets = __Pyx_minusones;
  return 0;
fail:;
  __Pyx_SafeReleaseBuffer(buf);
  return -1;
}

 
  static void __Pyx_RaiseBufferFallbackError(void) {
  PyErr_SetString(PyExc_ValueError,
     "Buffer acquisition failed on assignment; and then reacquiring the old buffer failed too!");
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyObject_FormatSimpleAndDecref(PyObject* s, PyObject* f) {
    if (unlikely(!s)) return NULL;
    if (likely(PyUnicode_CheckExact(s))) return s;
    #if PY_MAJOR_VERSION < 3
    if (likely(PyString_CheckExact(s))) {
        PyObject *result = PyUnicode_FromEncodedObject(s, NULL, "strict");
        Py_DECREF(s);
        return result;
    }
    #endif
    return __Pyx_PyObject_FormatAndDecref(s, f);
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_FormatAndDecref(PyObject* s, PyObject* f) {
    PyObject *result = PyObject_Format(s, f);
    Py_DECREF(s);
    return result;
}

 
  static const char DIGIT_PAIRS_10[2*10*10+1] = {
    "00010203040506070809"
    "10111213141516171819"
    "20212223242526272829"
    "30313233343536373839"
    "40414243444546474849"
    "50515253545556575859"
    "60616263646566676869"
    "70717273747576777879"
    "80818283848586878889"
    "90919293949596979899"
};
static const char DIGIT_PAIRS_8[2*8*8+1] = {
    "0001020304050607"
    "1011121314151617"
    "2021222324252627"
    "3031323334353637"
    "4041424344454647"
    "5051525354555657"
    "6061626364656667"
    "7071727374757677"
};
static const char DIGITS_HEX[2*16+1] = {
    "0123456789abcdef"
    "0123456789ABCDEF"
};

 
  static PyObject* __Pyx_PyUnicode_BuildFromAscii(Py_ssize_t ulength, char* chars, int clength,
                                                int prepend_sign, char padding_char) {
    PyObject *uval;
    Py_ssize_t uoffset = ulength - clength;
#if CYTHON_USE_UNICODE_INTERNALS
    Py_ssize_t i;
#if CYTHON_PEP393_ENABLED
    void *udata;
    uval = PyUnicode_New(ulength, 127);
    if (unlikely(!uval)) return NULL;
    udata = PyUnicode_DATA(uval);
#else
    Py_UNICODE *udata;
    uval = PyUnicode_FromUnicode(NULL, ulength);
    if (unlikely(!uval)) return NULL;
    udata = PyUnicode_AS_UNICODE(uval);
#endif
    if (uoffset > 0) {
        i = 0;
        if (prepend_sign) {
            __Pyx_PyUnicode_WRITE(PyUnicode_1BYTE_KIND, udata, 0, '-');
            i++;
        }
        for (; i < uoffset; i++) {
            __Pyx_PyUnicode_WRITE(PyUnicode_1BYTE_KIND, udata, i, padding_char);
        }
    }
    for (i=0; i < clength; i++) {
        __Pyx_PyUnicode_WRITE(PyUnicode_1BYTE_KIND, udata, uoffset+i, chars[i]);
    }
#else
    {
        PyObject *sign = NULL, *padding = NULL;
        uval = NULL;
        if (uoffset > 0) {
            prepend_sign = !!prepend_sign;
            if (uoffset > prepend_sign) {
                padding = PyUnicode_FromOrdinal(padding_char);
                if (likely(padding) && uoffset > prepend_sign + 1) {
                    PyObject *tmp;
                    PyObject *repeat = PyInt_FromSsize_t(uoffset - prepend_sign);
                    if (unlikely(!repeat)) goto done_or_error;
                    tmp = PyNumber_Multiply(padding, repeat);
                    Py_DECREF(repeat);
                    Py_DECREF(padding);
                    padding = tmp;
                }
                if (unlikely(!padding)) goto done_or_error;
            }
            if (prepend_sign) {
                sign = PyUnicode_FromOrdinal('-');
                if (unlikely(!sign)) goto done_or_error;
            }
        }
        uval = PyUnicode_DecodeASCII(chars, clength, NULL);
        if (likely(uval) && padding) {
            PyObject *tmp = PyNumber_Add(padding, uval);
            Py_DECREF(uval);
            uval = tmp;
        }
        if (likely(uval) && sign) {
            PyObject *tmp = PyNumber_Add(sign, uval);
            Py_DECREF(uval);
            uval = tmp;
        }
done_or_error:
        Py_XDECREF(padding);
        Py_XDECREF(sign);
    }
#endif
    return uval;
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyUnicode_From_int(int value, Py_ssize_t width, char padding_char, char format_char) {
    char digits[sizeof(int)*3+2];
    char *dpos, *end = digits + sizeof(int)*3+2;
    const char *hex_digits = DIGITS_HEX;
    Py_ssize_t length, ulength;
    int prepend_sign, last_one_off;
    int remaining;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const int neg_one = (int) -1, const_zero = (int) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (format_char == 'X') {
        hex_digits += 16;
        format_char = 'x';
    }
    remaining = value;
    last_one_off = 0;
    dpos = end;
    do {
        int digit_pos;
        switch (format_char) {
        case 'o':
            digit_pos = abs((int)(remaining % (8*8)));
            remaining = (int) (remaining / (8*8));
            dpos -= 2;
            memcpy(dpos, DIGIT_PAIRS_8 + digit_pos * 2, 2);
            last_one_off = (digit_pos < 8);
            break;
        case 'd':
            digit_pos = abs((int)(remaining % (10*10)));
            remaining = (int) (remaining / (10*10));
            dpos -= 2;
            memcpy(dpos, DIGIT_PAIRS_10 + digit_pos * 2, 2);
            last_one_off = (digit_pos < 10);
            break;
        case 'x':
            *(--dpos) = hex_digits[abs((int)(remaining % 16))];
            remaining = (int) (remaining / 16);
            break;
        default:
            assert(0);
            break;
        }
    } while (unlikely(remaining != 0));
    if (last_one_off) {
        assert(*dpos == '0');
        dpos++;
    }
    length = end - dpos;
    ulength = length;
    prepend_sign = 0;
    if (!is_unsigned && value <= neg_one) {
        if (padding_char == ' ' || width <= length + 1) {
            *(--dpos) = '-';
            ++length;
        } else {
            prepend_sign = 1;
        }
        ++ulength;
    }
    if (width > ulength) {
        ulength = width;
    }
    if (ulength == 1) {
        return PyUnicode_FromOrdinal(*dpos);
    }
    return __Pyx_PyUnicode_BuildFromAscii(ulength, dpos, (int) length, prepend_sign, padding_char);
}

 
  static PyObject* __Pyx_PyUnicode_Join(PyObject* value_tuple, Py_ssize_t value_count, Py_ssize_t result_ulength,
                                      CYTHON_UNUSED Py_UCS4 max_char) {
#if CYTHON_USE_UNICODE_INTERNALS && CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    PyObject *result_uval;
    int result_ukind;
    Py_ssize_t i, char_pos;
    void *result_udata;
#if CYTHON_PEP393_ENABLED
    result_uval = PyUnicode_New(result_ulength, max_char);
    if (unlikely(!result_uval)) return NULL;
    result_ukind = (max_char <= 255) ? PyUnicode_1BYTE_KIND : (max_char <= 65535) ? PyUnicode_2BYTE_KIND : PyUnicode_4BYTE_KIND;
    result_udata = PyUnicode_DATA(result_uval);
#else
    result_uval = PyUnicode_FromUnicode(NULL, result_ulength);
    if (unlikely(!result_uval)) return NULL;
    result_ukind = sizeof(Py_UNICODE);
    result_udata = PyUnicode_AS_UNICODE(result_uval);
#endif
    char_pos = 0;
    for (i=0; i < value_count; i++) {
        int ukind;
        Py_ssize_t ulength;
        void *udata;
        PyObject *uval = PyTuple_GET_ITEM(value_tuple, i);
        if (unlikely(__Pyx_PyUnicode_READY(uval)))
            goto bad;
        ulength = __Pyx_PyUnicode_GET_LENGTH(uval);
        if (unlikely(!ulength))
            continue;
        if (unlikely(char_pos + ulength < 0))
            goto overflow;
        ukind = __Pyx_PyUnicode_KIND(uval);
        udata = __Pyx_PyUnicode_DATA(uval);
        if (!CYTHON_PEP393_ENABLED || ukind == result_ukind) {
            memcpy((char *)result_udata + char_pos * result_ukind, udata, (size_t) (ulength * result_ukind));
        } else {
            #if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030300F0 || defined(_PyUnicode_FastCopyCharacters)
            _PyUnicode_FastCopyCharacters(result_uval, char_pos, uval, 0, ulength);
            #else
            Py_ssize_t j;
            for (j=0; j < ulength; j++) {
                Py_UCS4 uchar = __Pyx_PyUnicode_READ(ukind, udata, j);
                __Pyx_PyUnicode_WRITE(result_ukind, result_udata, char_pos+j, uchar);
            }
            #endif
        }
        char_pos += ulength;
    }
    return result_uval;
overflow:
    PyErr_SetString(PyExc_OverflowError, "join() result is too long for a Python string");
bad:
    Py_DECREF(result_uval);
    return NULL;
#else
    result_ulength++;
    value_count++;
    return PyUnicode_Join(__pyx_empty_unicode, value_tuple);
#endif
}

 
  #if CYTHON_USE_DICT_VERSIONS && CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PY_UINT64_T __Pyx_get_tp_dict_version(PyObject *obj) {
    PyObject *dict = Py_TYPE(obj)->tp_dict;
    return likely(dict) ? __PYX_GET_DICT_VERSION(dict) : 0;
}
static CYTHON_INLINE PY_UINT64_T __Pyx_get_object_dict_version(PyObject *obj) {
    PyObject **dictptr = NULL;
    Py_ssize_t offset = Py_TYPE(obj)->tp_dictoffset;
    if (offset) {
#if CYTHON_COMPILING_IN_CPYTHON
        dictptr = (likely(offset > 0)) ? (PyObject **) ((char *)obj + offset) : _PyObject_GetDictPtr(obj);
#else
        dictptr = _PyObject_GetDictPtr(obj);
#endif
    }
    return (dictptr && *dictptr) ? __PYX_GET_DICT_VERSION(*dictptr) : 0;
}
static CYTHON_INLINE int __Pyx_object_dict_version_matches(PyObject* obj, PY_UINT64_T tp_dict_version, PY_UINT64_T obj_dict_version) {
    PyObject *dict = Py_TYPE(obj)->tp_dict;
    if (unlikely(!dict) || unlikely(tp_dict_version != __PYX_GET_DICT_VERSION(dict)))
        return 0;
    return obj_dict_version == __Pyx_get_object_dict_version(obj);
}
#endif

 
  #if CYTHON_USE_DICT_VERSIONS
static PyObject *__Pyx__GetModuleGlobalName(PyObject *name, PY_UINT64_T *dict_version, PyObject **dict_cached_value)
#else
static CYTHON_INLINE PyObject *__Pyx__GetModuleGlobalName(PyObject *name)
#endif
{
    PyObject *result;
#if !CYTHON_AVOID_BORROWED_REFS
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030500A1
    result = _PyDict_GetItem_KnownHash(__pyx_d, name, ((PyASCIIObject *) name)->hash);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    } else if (unlikely(PyErr_Occurred())) {
        return NULL;
    }
#else
    result = PyDict_GetItem(__pyx_d, name);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    }
#endif
#else
    result = PyObject_GetItem(__pyx_d, name);
    __PYX_UPDATE_DICT_CACHE(__pyx_d, result, *dict_cached_value, *dict_version)
    if (likely(result)) {
        return __Pyx_NewRef(result);
    }
    PyErr_Clear();
#endif
    return __Pyx_GetBuiltinName(name);
}

 
  static CYTHON_UNUSED PyObject* __Pyx_PyObject_Call2Args(PyObject* function, PyObject* arg1, PyObject* arg2) {
    PyObject *args, *result = NULL;
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(function)) {
        PyObject *args[2] = {arg1, arg2};
        return __Pyx_PyFunction_FastCall(function, args, 2);
    }
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(function)) {
        PyObject *args[2] = {arg1, arg2};
        return __Pyx_PyCFunction_FastCall(function, args, 2);
    }
    #endif
    args = PyTuple_New(2);
    if (unlikely(!args)) goto done;
    Py_INCREF(arg1);
    PyTuple_SET_ITEM(args, 0, arg1);
    Py_INCREF(arg2);
    PyTuple_SET_ITEM(args, 1, arg2);
    Py_INCREF(function);
    result = __Pyx_PyObject_Call(function, args, NULL);
    Py_DECREF(args);
    Py_DECREF(function);
done:
    return result;
}

 
  static int
__pyx_memviewslice_is_contig(const __Pyx_memviewslice mvs, char order, int ndim)
{
    int i, index, step, start;
    Py_ssize_t itemsize = mvs.memview->view.itemsize;
    if (order == 'F') {
        step = 1;
        start = 0;
    } else {
        step = -1;
        start = ndim - 1;
    }
    for (i = 0; i < ndim; i++) {
        index = start + step * i;
        if (mvs.suboffsets[index] >= 0 || mvs.strides[index] != itemsize)
            return 0;
        itemsize *= mvs.shape[index];
    }
    return 1;
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyUnicode_Unicode(PyObject *obj) {
    if (unlikely(obj == Py_None))
        obj = __pyx_kp_u_None;
    return __Pyx_NewRef(obj);
}

 
  #if CYTHON_USE_EXC_INFO_STACK
static _PyErr_StackItem *
__Pyx_PyErr_GetTopmostException(PyThreadState *tstate)
{
    _PyErr_StackItem *exc_info = tstate->exc_info;
    while ((exc_info->exc_type == NULL || exc_info->exc_type == Py_None) &&
           exc_info->previous_item != NULL)
    {
        exc_info = exc_info->previous_item;
    }
    return exc_info;
}
#endif

 
  #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    #if CYTHON_USE_EXC_INFO_STACK
    _PyErr_StackItem *exc_info = __Pyx_PyErr_GetTopmostException(tstate);
    *type = exc_info->exc_type;
    *value = exc_info->exc_value;
    *tb = exc_info->exc_traceback;
    #else
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    #endif
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
}
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    #if CYTHON_USE_EXC_INFO_STACK
    _PyErr_StackItem *exc_info = tstate->exc_info;
    tmp_type = exc_info->exc_type;
    tmp_value = exc_info->exc_value;
    tmp_tb = exc_info->exc_traceback;
    exc_info->exc_type = type;
    exc_info->exc_value = value;
    exc_info->exc_traceback = tb;
    #else
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    #endif
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
#endif

 
  #if CYTHON_FAST_THREAD_STATE
static int __Pyx_PyErr_ExceptionMatchesTuple(PyObject *exc_type, PyObject *tuple) {
    Py_ssize_t i, n;
    n = PyTuple_GET_SIZE(tuple);
#if PY_MAJOR_VERSION >= 3
    for (i=0; i<n; i++) {
        if (exc_type == PyTuple_GET_ITEM(tuple, i)) return 1;
    }
#endif
    for (i=0; i<n; i++) {
        if (__Pyx_PyErr_GivenExceptionMatches(exc_type, PyTuple_GET_ITEM(tuple, i))) return 1;
    }
    return 0;
}
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err) {
    PyObject *exc_type = tstate->curexc_type;
    if (exc_type == err) return 1;
    if (unlikely(!exc_type)) return 0;
    if (unlikely(PyTuple_Check(err)))
        return __Pyx_PyErr_ExceptionMatchesTuple(exc_type, err);
    return __Pyx_PyErr_GivenExceptionMatches(exc_type, err);
}
#endif

 
  #if CYTHON_FAST_THREAD_STATE
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb)
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb)
#endif
{
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_FAST_THREAD_STATE
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_FAST_THREAD_STATE
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (local_tb) {
        if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
            goto bad;
    }
    #endif
    Py_XINCREF(local_tb);
    Py_XINCREF(local_type);
    Py_XINCREF(local_value);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_FAST_THREAD_STATE
    #if CYTHON_USE_EXC_INFO_STACK
    {
        _PyErr_StackItem *exc_info = tstate->exc_info;
        tmp_type = exc_info->exc_type;
        tmp_value = exc_info->exc_value;
        tmp_tb = exc_info->exc_traceback;
        exc_info->exc_type = local_type;
        exc_info->exc_value = local_value;
        exc_info->exc_traceback = local_tb;
    }
    #else
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    #endif
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

 
  static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
    if (s1 == s2) {
        return (equals == Py_EQ);
    } else if (PyBytes_CheckExact(s1) & PyBytes_CheckExact(s2)) {
        const char *ps1, *ps2;
        Py_ssize_t length = PyBytes_GET_SIZE(s1);
        if (length != PyBytes_GET_SIZE(s2))
            return (equals == Py_NE);
        ps1 = PyBytes_AS_STRING(s1);
        ps2 = PyBytes_AS_STRING(s2);
        if (ps1[0] != ps2[0]) {
            return (equals == Py_NE);
        } else if (length == 1) {
            return (equals == Py_EQ);
        } else {
            int result;
#if CYTHON_USE_UNICODE_INTERNALS && (PY_VERSION_HEX < 0x030B0000)
            Py_hash_t hash1, hash2;
            hash1 = ((PyBytesObject*)s1)->ob_shash;
            hash2 = ((PyBytesObject*)s2)->ob_shash;
            if (hash1 != hash2 && hash1 != -1 && hash2 != -1) {
                return (equals == Py_NE);
            }
#endif
            result = memcmp(ps1, ps2, (size_t)length);
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & PyBytes_CheckExact(s2)) {
        return (equals == Py_NE);
    } else if ((s2 == Py_None) & PyBytes_CheckExact(s1)) {
        return (equals == Py_NE);
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
#endif
}

 
  static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
#if PY_MAJOR_VERSION < 3
    PyObject* owned_ref = NULL;
#endif
    int s1_is_unicode, s2_is_unicode;
    if (s1 == s2) {
        goto return_eq;
    }
    s1_is_unicode = PyUnicode_CheckExact(s1);
    s2_is_unicode = PyUnicode_CheckExact(s2);
#if PY_MAJOR_VERSION < 3
    if ((s1_is_unicode & (!s2_is_unicode)) && PyString_CheckExact(s2)) {
        owned_ref = PyUnicode_FromObject(s2);
        if (unlikely(!owned_ref))
            return -1;
        s2 = owned_ref;
        s2_is_unicode = 1;
    } else if ((s2_is_unicode & (!s1_is_unicode)) && PyString_CheckExact(s1)) {
        owned_ref = PyUnicode_FromObject(s1);
        if (unlikely(!owned_ref))
            return -1;
        s1 = owned_ref;
        s1_is_unicode = 1;
    } else if (((!s2_is_unicode) & (!s1_is_unicode))) {
        return __Pyx_PyBytes_Equals(s1, s2, equals);
    }
#endif
    if (s1_is_unicode & s2_is_unicode) {
        Py_ssize_t length;
        int kind;
        void *data1, *data2;
        if (unlikely(__Pyx_PyUnicode_READY(s1) < 0) || unlikely(__Pyx_PyUnicode_READY(s2) < 0))
            return -1;
        length = __Pyx_PyUnicode_GET_LENGTH(s1);
        if (length != __Pyx_PyUnicode_GET_LENGTH(s2)) {
            goto return_ne;
        }
#if CYTHON_USE_UNICODE_INTERNALS
        {
            Py_hash_t hash1, hash2;
        #if CYTHON_PEP393_ENABLED
            hash1 = ((PyASCIIObject*)s1)->hash;
            hash2 = ((PyASCIIObject*)s2)->hash;
        #else
            hash1 = ((PyUnicodeObject*)s1)->hash;
            hash2 = ((PyUnicodeObject*)s2)->hash;
        #endif
            if (hash1 != hash2 && hash1 != -1 && hash2 != -1) {
                goto return_ne;
            }
        }
#endif
        kind = __Pyx_PyUnicode_KIND(s1);
        if (kind != __Pyx_PyUnicode_KIND(s2)) {
            goto return_ne;
        }
        data1 = __Pyx_PyUnicode_DATA(s1);
        data2 = __Pyx_PyUnicode_DATA(s2);
        if (__Pyx_PyUnicode_READ(kind, data1, 0) != __Pyx_PyUnicode_READ(kind, data2, 0)) {
            goto return_ne;
        } else if (length == 1) {
            goto return_eq;
        } else {
            int result = memcmp(data1, data2, (size_t)(length * kind));
            #if PY_MAJOR_VERSION < 3
            Py_XDECREF(owned_ref);
            #endif
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & s2_is_unicode) {
        goto return_ne;
    } else if ((s2 == Py_None) & s1_is_unicode) {
        goto return_ne;
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        #if PY_MAJOR_VERSION < 3
        Py_XDECREF(owned_ref);
        #endif
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
return_eq:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_EQ);
return_ne:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_NE);
#endif
}

 
  static CYTHON_INLINE Py_ssize_t __Pyx_div_Py_ssize_t(Py_ssize_t a, Py_ssize_t b) {
    Py_ssize_t q = a / b;
    Py_ssize_t r = a - q*b;
    q -= ((r != 0) & ((r ^ b) < 0));
    return q;
}

 
  static CYTHON_INLINE PyObject *__Pyx_GetAttr(PyObject *o, PyObject *n) {
#if CYTHON_USE_TYPE_SLOTS
#if PY_MAJOR_VERSION >= 3
    if (likely(PyUnicode_Check(n)))
#else
    if (likely(PyString_Check(n)))
#endif
        return __Pyx_PyObject_GetAttrStr(o, n);
#endif
    return PyObject_GetAttr(o, n);
}

 
  #if CYTHON_USE_TYPE_SLOTS
static PyObject *__Pyx_PyObject_GetIndex(PyObject *obj, PyObject* index) {
    PyObject *runerr = NULL;
    Py_ssize_t key_value;
    PySequenceMethods *m = Py_TYPE(obj)->tp_as_sequence;
    if (unlikely(!(m && m->sq_item))) {
        PyErr_Format(PyExc_TypeError, "'%.200s' object is not subscriptable", Py_TYPE(obj)->tp_name);
        return NULL;
    }
    key_value = __Pyx_PyIndex_AsSsize_t(index);
    if (likely(key_value != -1 || !(runerr = PyErr_Occurred()))) {
        return __Pyx_GetItemInt_Fast(obj, key_value, 0, 1, 1);
    }
    if (PyErr_GivenExceptionMatches(runerr, PyExc_OverflowError)) {
        PyErr_Clear();
        PyErr_Format(PyExc_IndexError, "cannot fit '%.200s' into an index-sized integer", Py_TYPE(index)->tp_name);
    }
    return NULL;
}
static PyObject *__Pyx_PyObject_GetItem(PyObject *obj, PyObject* key) {
    PyMappingMethods *m = Py_TYPE(obj)->tp_as_mapping;
    if (likely(m && m->mp_subscript)) {
        return m->mp_subscript(obj, key);
    }
    return __Pyx_PyObject_GetIndex(obj, key);
}
#endif

 
  static PyObject *__Pyx_GetAttr3Default(PyObject *d) {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    if (unlikely(!__Pyx_PyErr_ExceptionMatches(PyExc_AttributeError)))
        return NULL;
    __Pyx_PyErr_Clear();
    Py_INCREF(d);
    return d;
}
static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *o, PyObject *n, PyObject *d) {
    PyObject *r = __Pyx_GetAttr(o, n);
    return (likely(r)) ? r : __Pyx_GetAttr3Default(d);
}

 
  static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
}

 
  static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%.1s to unpack",
                 index, (index == 1) ? "" : "s");
}

 
  static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
}

 
  #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx__ExceptionSwap(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    #if CYTHON_USE_EXC_INFO_STACK
    _PyErr_StackItem *exc_info = tstate->exc_info;
    tmp_type = exc_info->exc_type;
    tmp_value = exc_info->exc_value;
    tmp_tb = exc_info->exc_traceback;
    exc_info->exc_type = *type;
    exc_info->exc_value = *value;
    exc_info->exc_traceback = *tb;
    #else
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = *type;
    tstate->exc_value = *value;
    tstate->exc_traceback = *tb;
    #endif
    *type = tmp_type;
    *value = tmp_value;
    *tb = tmp_tb;
}
#else
static CYTHON_INLINE void __Pyx_ExceptionSwap(PyObject **type, PyObject **value, PyObject **tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyErr_GetExcInfo(&tmp_type, &tmp_value, &tmp_tb);
    PyErr_SetExcInfo(*type, *value, *tb);
    *type = tmp_type;
    *value = tmp_value;
    *tb = tmp_tb;
}
#endif

 
  static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_MAJOR_VERSION < 3
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if ((1) && (strchr(__Pyx_MODULE_NAME, '.'))) {
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_MAJOR_VERSION < 3
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, (PyObject *)NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

 
  #if CYTHON_COMPILING_IN_CPYTHON
static int __Pyx_InBases(PyTypeObject *a, PyTypeObject *b) {
    while (a) {
        a = a->tp_base;
        if (a == b)
            return 1;
    }
    return b == &PyBaseObject_Type;
}
static CYTHON_INLINE int __Pyx_IsSubtype(PyTypeObject *a, PyTypeObject *b) {
    PyObject *mro;
    if (a == b) return 1;
    mro = a->tp_mro;
    if (likely(mro)) {
        Py_ssize_t i, n;
        n = PyTuple_GET_SIZE(mro);
        for (i = 0; i < n; i++) {
            if (PyTuple_GET_ITEM(mro, i) == (PyObject *)b)
                return 1;
        }
        return 0;
    }
    return __Pyx_InBases(a, b);
}
#if PY_MAJOR_VERSION == 2
static int __Pyx_inner_PyErr_GivenExceptionMatches2(PyObject *err, PyObject* exc_type1, PyObject* exc_type2) {
    PyObject *exception, *value, *tb;
    int res;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&exception, &value, &tb);
    res = exc_type1 ? PyObject_IsSubclass(err, exc_type1) : 0;
    if (unlikely(res == -1)) {
        PyErr_WriteUnraisable(err);
        res = 0;
    }
    if (!res) {
        res = PyObject_IsSubclass(err, exc_type2);
        if (unlikely(res == -1)) {
            PyErr_WriteUnraisable(err);
            res = 0;
        }
    }
    __Pyx_ErrRestore(exception, value, tb);
    return res;
}
#else
static CYTHON_INLINE int __Pyx_inner_PyErr_GivenExceptionMatches2(PyObject *err, PyObject* exc_type1, PyObject *exc_type2) {
    int res = exc_type1 ? __Pyx_IsSubtype((PyTypeObject*)err, (PyTypeObject*)exc_type1) : 0;
    if (!res) {
        res = __Pyx_IsSubtype((PyTypeObject*)err, (PyTypeObject*)exc_type2);
    }
    return res;
}
#endif
static int __Pyx_PyErr_GivenExceptionMatchesTuple(PyObject *exc_type, PyObject *tuple) {
    Py_ssize_t i, n;
    assert(PyExceptionClass_Check(exc_type));
    n = PyTuple_GET_SIZE(tuple);
#if PY_MAJOR_VERSION >= 3
    for (i=0; i<n; i++) {
        if (exc_type == PyTuple_GET_ITEM(tuple, i)) return 1;
    }
#endif
    for (i=0; i<n; i++) {
        PyObject *t = PyTuple_GET_ITEM(tuple, i);
        #if PY_MAJOR_VERSION < 3
        if (likely(exc_type == t)) return 1;
        #endif
        if (likely(PyExceptionClass_Check(t))) {
            if (__Pyx_inner_PyErr_GivenExceptionMatches2(exc_type, NULL, t)) return 1;
        } else {
        }
    }
    return 0;
}
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches(PyObject *err, PyObject* exc_type) {
    if (likely(err == exc_type)) return 1;
    if (likely(PyExceptionClass_Check(err))) {
        if (likely(PyExceptionClass_Check(exc_type))) {
            return __Pyx_inner_PyErr_GivenExceptionMatches2(err, NULL, exc_type);
        } else if (likely(PyTuple_Check(exc_type))) {
            return __Pyx_PyErr_GivenExceptionMatchesTuple(err, exc_type);
        } else {
        }
    }
    return PyErr_GivenExceptionMatches(err, exc_type);
}
static CYTHON_INLINE int __Pyx_PyErr_GivenExceptionMatches2(PyObject *err, PyObject *exc_type1, PyObject *exc_type2) {
    assert(PyExceptionClass_Check(exc_type1));
    assert(PyExceptionClass_Check(exc_type2));
    if (likely(err == exc_type1 || err == exc_type2)) return 1;
    if (likely(PyExceptionClass_Check(err))) {
        return __Pyx_inner_PyErr_GivenExceptionMatches2(err, exc_type1, exc_type2);
    }
    return (PyErr_GivenExceptionMatches(err, exc_type1) || PyErr_GivenExceptionMatches(err, exc_type2));
}
#endif

 
  #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, int inplace, int zerodivision_check) {
    (void)inplace;
    (void)zerodivision_check;
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long x;
        long a = PyInt_AS_LONG(op1);
            x = (long)((unsigned long)a + b);
            if (likely((x^a) >= 0 || (x^b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_add(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG llb = intval;
        PY_LONG_LONG lla, llx;
#endif
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            a = likely(size) ? digits[0] : 0;
            if (size == -1) a = -a;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                    CYTHON_FALLTHROUGH;
                default: return PyLong_Type.tp_as_number->nb_add(op1, op2);
            }
        }
                x = a + b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla + llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            double result;
            PyFPE_START_PROTECT("add", return NULL)
            result = ((double)a) + (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

 
  static CYTHON_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname) {
    PyErr_Format(PyExc_UnboundLocalError, "local variable '%s' referenced before assignment", varname);
}

 
  static CYTHON_INLINE long __Pyx_div_long(long a, long b) {
    long q = a / b;
    long r = a - q*b;
    q -= ((r != 0) & ((r ^ b) < 0));
    return q;
}

 
  static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

 
  static CYTHON_INLINE int __Pyx_HasAttr(PyObject *o, PyObject *n) {
    PyObject *r;
    if (unlikely(!__Pyx_PyBaseString_Check(n))) {
        PyErr_SetString(PyExc_TypeError,
                        "hasattr(): attribute name must be string");
        return -1;
    }
    r = __Pyx_GetAttr(o, n);
    if (unlikely(!r)) {
        PyErr_Clear();
        return 0;
    } else {
        Py_DECREF(r);
        return 1;
    }
}

 
  #if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject *__Pyx_RaiseGenericGetAttributeError(PyTypeObject *tp, PyObject *attr_name) {
    PyErr_Format(PyExc_AttributeError,
#if PY_MAJOR_VERSION >= 3
                 "'%.50s' object has no attribute '%U'",
                 tp->tp_name, attr_name);
#else
                 "'%.50s' object has no attribute '%.400s'",
                 tp->tp_name, PyString_AS_STRING(attr_name));
#endif
    return NULL;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_GenericGetAttrNoDict(PyObject* obj, PyObject* attr_name) {
    PyObject *descr;
    PyTypeObject *tp = Py_TYPE(obj);
    if (unlikely(!PyString_Check(attr_name))) {
        return PyObject_GenericGetAttr(obj, attr_name);
    }
    assert(!tp->tp_dictoffset);
    descr = _PyType_Lookup(tp, attr_name);
    if (unlikely(!descr)) {
        return __Pyx_RaiseGenericGetAttributeError(tp, attr_name);
    }
    Py_INCREF(descr);
    #if PY_MAJOR_VERSION < 3
    if (likely(PyType_HasFeature(Py_TYPE(descr), Py_TPFLAGS_HAVE_CLASS)))
    #endif
    {
        descrgetfunc f = Py_TYPE(descr)->tp_descr_get;
        if (unlikely(f)) {
            PyObject *res = f(descr, obj, (PyObject *)tp);
            Py_DECREF(descr);
            return res;
        }
    }
    return descr;
}
#endif

 
  #if CYTHON_USE_TYPE_SLOTS && CYTHON_USE_PYTYPE_LOOKUP && PY_VERSION_HEX < 0x03070000
static PyObject* __Pyx_PyObject_GenericGetAttr(PyObject* obj, PyObject* attr_name) {
    if (unlikely(Py_TYPE(obj)->tp_dictoffset)) {
        return PyObject_GenericGetAttr(obj, attr_name);
    }
    return __Pyx_PyObject_GenericGetAttrNoDict(obj, attr_name);
}
#endif

 
  static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
#if PY_VERSION_HEX >= 0x02070000
    PyObject *ob = PyCapsule_New(vtable, 0, 0);
#else
    PyObject *ob = PyCObject_FromVoidPtr(vtable, 0);
#endif
    if (!ob)
        goto bad;
    if (PyDict_SetItem(dict, __pyx_n_s_pyx_vtable, ob) < 0)
        goto bad;
    Py_DECREF(ob);
    return 0;
bad:
    Py_XDECREF(ob);
    return -1;
}

 
  static void __Pyx_PyObject_GetAttrStr_ClearAttributeError(void) {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    if (likely(__Pyx_PyErr_ExceptionMatches(PyExc_AttributeError)))
        __Pyx_PyErr_Clear();
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStrNoError(PyObject* obj, PyObject* attr_name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON && CYTHON_USE_TYPE_SLOTS && PY_VERSION_HEX >= 0x030700B1
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro == PyObject_GenericGetAttr)) {
        return _PyObject_GenericGetAttrWithDict(obj, attr_name, NULL, 1);
    }
#endif
    result = __Pyx_PyObject_GetAttrStr(obj, attr_name);
    if (unlikely(!result)) {
        __Pyx_PyObject_GetAttrStr_ClearAttributeError();
    }
    return result;
}

 
  static int __Pyx_setup_reduce_is_named(PyObject* meth, PyObject* name) {
  int ret;
  PyObject *name_attr;
  name_attr = __Pyx_PyObject_GetAttrStr(meth, __pyx_n_s_name_2);
  if (likely(name_attr)) {
      ret = PyObject_RichCompareBool(name_attr, name, Py_EQ);
  } else {
      ret = -1;
  }
  if (unlikely(ret < 0)) {
      PyErr_Clear();
      ret = 0;
  }
  Py_XDECREF(name_attr);
  return ret;
}
static int __Pyx_setup_reduce(PyObject* type_obj) {
    int ret = 0;
    PyObject *object_reduce = NULL;
    PyObject *object_getstate = NULL;
    PyObject *object_reduce_ex = NULL;
    PyObject *reduce = NULL;
    PyObject *reduce_ex = NULL;
    PyObject *reduce_cython = NULL;
    PyObject *setstate = NULL;
    PyObject *setstate_cython = NULL;
    PyObject *getstate = NULL;
#if CYTHON_USE_PYTYPE_LOOKUP
    getstate = _PyType_Lookup((PyTypeObject*)type_obj, __pyx_n_s_getstate);
#else
    getstate = __Pyx_PyObject_GetAttrStrNoError(type_obj, __pyx_n_s_getstate);
    if (!getstate && PyErr_Occurred()) {
        goto __PYX_BAD;
    }
#endif
    if (getstate) {
#if CYTHON_USE_PYTYPE_LOOKUP
        object_getstate = _PyType_Lookup(&PyBaseObject_Type, __pyx_n_s_getstate);
#else
        object_getstate = __Pyx_PyObject_GetAttrStrNoError((PyObject*)&PyBaseObject_Type, __pyx_n_s_getstate);
        if (!object_getstate && PyErr_Occurred()) {
            goto __PYX_BAD;
        }
#endif
        if (object_getstate != getstate) {
            goto __PYX_GOOD;
        }
    }
#if CYTHON_USE_PYTYPE_LOOKUP
    object_reduce_ex = _PyType_Lookup(&PyBaseObject_Type, __pyx_n_s_reduce_ex); if (!object_reduce_ex) goto __PYX_BAD;
#else
    object_reduce_ex = __Pyx_PyObject_GetAttrStr((PyObject*)&PyBaseObject_Type, __pyx_n_s_reduce_ex); if (!object_reduce_ex) goto __PYX_BAD;
#endif
    reduce_ex = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_reduce_ex); if (unlikely(!reduce_ex)) goto __PYX_BAD;
    if (reduce_ex == object_reduce_ex) {
#if CYTHON_USE_PYTYPE_LOOKUP
        object_reduce = _PyType_Lookup(&PyBaseObject_Type, __pyx_n_s_reduce); if (!object_reduce) goto __PYX_BAD;
#else
        object_reduce = __Pyx_PyObject_GetAttrStr((PyObject*)&PyBaseObject_Type, __pyx_n_s_reduce); if (!object_reduce) goto __PYX_BAD;
#endif
        reduce = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_reduce); if (unlikely(!reduce)) goto __PYX_BAD;
        if (reduce == object_reduce || __Pyx_setup_reduce_is_named(reduce, __pyx_n_s_reduce_cython)) {
            reduce_cython = __Pyx_PyObject_GetAttrStrNoError(type_obj, __pyx_n_s_reduce_cython);
            if (likely(reduce_cython)) {
                ret = PyDict_SetItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_reduce, reduce_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                ret = PyDict_DelItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_reduce_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
            } else if (reduce == object_reduce || PyErr_Occurred()) {
                goto __PYX_BAD;
            }
            setstate = __Pyx_PyObject_GetAttrStr(type_obj, __pyx_n_s_setstate);
            if (!setstate) PyErr_Clear();
            if (!setstate || __Pyx_setup_reduce_is_named(setstate, __pyx_n_s_setstate_cython)) {
                setstate_cython = __Pyx_PyObject_GetAttrStrNoError(type_obj, __pyx_n_s_setstate_cython);
                if (likely(setstate_cython)) {
                    ret = PyDict_SetItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_setstate, setstate_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                    ret = PyDict_DelItem(((PyTypeObject*)type_obj)->tp_dict, __pyx_n_s_setstate_cython); if (unlikely(ret < 0)) goto __PYX_BAD;
                } else if (!setstate || PyErr_Occurred()) {
                    goto __PYX_BAD;
                }
            }
            PyType_Modified((PyTypeObject*)type_obj);
        }
    }
    goto __PYX_GOOD;
__PYX_BAD:
    if (!PyErr_Occurred())
        PyErr_Format(PyExc_RuntimeError, "Unable to initialize pickling for %s", ((PyTypeObject*)type_obj)->tp_name);
    ret = -1;
__PYX_GOOD:
#if !CYTHON_USE_PYTYPE_LOOKUP
    Py_XDECREF(object_reduce);
    Py_XDECREF(object_reduce_ex);
    Py_XDECREF(object_getstate);
    Py_XDECREF(getstate);
#endif
    Py_XDECREF(reduce);
    Py_XDECREF(reduce_ex);
    Py_XDECREF(reduce_cython);
    Py_XDECREF(setstate);
    Py_XDECREF(setstate_cython);
    return ret;
}

 
  #ifndef __PYX_HAVE_RT_ImportType_0_29_35
#define __PYX_HAVE_RT_ImportType_0_29_35
static PyTypeObject *__Pyx_ImportType_0_29_35(PyObject *module, const char *module_name, const char *class_name,
    size_t size, size_t alignment, enum __Pyx_ImportType_CheckSize_0_29_35 check_size)
{
    PyObject *result = 0;
    char warning[200];
    Py_ssize_t basicsize;
    Py_ssize_t itemsize;
#ifdef Py_LIMITED_API
    PyObject *py_basicsize;
    PyObject *py_itemsize;
#endif
    result = PyObject_GetAttrString(module, class_name);
    if (!result)
        goto bad;
    if (!PyType_Check(result)) {
        PyErr_Format(PyExc_TypeError,
            "%.200s.%.200s is not a type object",
            module_name, class_name);
        goto bad;
    }
#ifndef Py_LIMITED_API
    basicsize = ((PyTypeObject *)result)->tp_basicsize;
    itemsize = ((PyTypeObject *)result)->tp_itemsize;
#else
    py_basicsize = PyObject_GetAttrString(result, "__basicsize__");
    if (!py_basicsize)
        goto bad;
    basicsize = PyLong_AsSsize_t(py_basicsize);
    Py_DECREF(py_basicsize);
    py_basicsize = 0;
    if (basicsize == (Py_ssize_t)-1 && PyErr_Occurred())
        goto bad;
    py_itemsize = PyObject_GetAttrString(result, "__itemsize__");
    if (!py_itemsize)
        goto bad;
    itemsize = PyLong_AsSsize_t(py_itemsize);
    Py_DECREF(py_itemsize);
    py_itemsize = 0;
    if (itemsize == (Py_ssize_t)-1 && PyErr_Occurred())
        goto bad;
#endif
    if (itemsize) {
        if (size % alignment) {
            alignment = size % alignment;
        }
        if (itemsize < (Py_ssize_t)alignment)
            itemsize = (Py_ssize_t)alignment;
    }
    if ((size_t)(basicsize + itemsize) < size) {
        PyErr_Format(PyExc_ValueError,
            "%.200s.%.200s size changed, may indicate binary incompatibility. "
            "Expected %zd from C header, got %zd from PyObject",
            module_name, class_name, size, basicsize);
        goto bad;
    }
    if (check_size == __Pyx_ImportType_CheckSize_Error_0_29_35 && (size_t)basicsize != size) {
        PyErr_Format(PyExc_ValueError,
            "%.200s.%.200s size changed, may indicate binary incompatibility. "
            "Expected %zd from C header, got %zd from PyObject",
            module_name, class_name, size, basicsize);
        goto bad;
    }
    else if (check_size == __Pyx_ImportType_CheckSize_Warn_0_29_35 && (size_t)basicsize > size) {
        PyOS_snprintf(warning, sizeof(warning),
            "%s.%s size changed, may indicate binary incompatibility. "
            "Expected %zd from C header, got %zd from PyObject",
            module_name, class_name, size, basicsize);
        if (PyErr_WarnEx(NULL, warning, 0) < 0) goto bad;
    }
    return (PyTypeObject *)result;
bad:
    Py_XDECREF(result);
    return NULL;
}
#endif

 
  static CYTHON_INLINE int __Pyx_IterFinish(void) {
#if CYTHON_FAST_THREAD_STATE
    PyThreadState *tstate = __Pyx_PyThreadState_Current;
    PyObject* exc_type = tstate->curexc_type;
    if (unlikely(exc_type)) {
        if (likely(__Pyx_PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) {
            PyObject *exc_value, *exc_tb;
            exc_value = tstate->curexc_value;
            exc_tb = tstate->curexc_traceback;
            tstate->curexc_type = 0;
            tstate->curexc_value = 0;
            tstate->curexc_traceback = 0;
            Py_DECREF(exc_type);
            Py_XDECREF(exc_value);
            Py_XDECREF(exc_tb);
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#else
    if (unlikely(PyErr_Occurred())) {
        if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) {
            PyErr_Clear();
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#endif
}

 
  static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected) {
    if (unlikely(retval)) {
        Py_DECREF(retval);
        __Pyx_RaiseTooManyValuesError(expected);
        return -1;
    }
    return __Pyx_IterFinish();
}

 
  #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, NULL, 0);
    }
#endif
#if defined(__Pyx_CyFunction_USED) && defined(NDEBUG)
    if (likely(PyCFunction_Check(func) || __Pyx_CyFunction_Check(func)))
#else
    if (likely(PyCFunction_Check(func)))
#endif
    {
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

 
  static int __Pyx_PyObject_GetMethod(PyObject *obj, PyObject *name, PyObject **method) {
    PyObject *attr;
#if CYTHON_UNPACK_METHODS && CYTHON_COMPILING_IN_CPYTHON && CYTHON_USE_PYTYPE_LOOKUP
    PyTypeObject *tp = Py_TYPE(obj);
    PyObject *descr;
    descrgetfunc f = NULL;
    PyObject **dictptr, *dict;
    int meth_found = 0;
    assert (*method == NULL);
    if (unlikely(tp->tp_getattro != PyObject_GenericGetAttr)) {
        attr = __Pyx_PyObject_GetAttrStr(obj, name);
        goto try_unpack;
    }
    if (unlikely(tp->tp_dict == NULL) && unlikely(PyType_Ready(tp) < 0)) {
        return 0;
    }
    descr = _PyType_Lookup(tp, name);
    if (likely(descr != NULL)) {
        Py_INCREF(descr);
#if PY_MAJOR_VERSION >= 3
        #ifdef __Pyx_CyFunction_USED
        if (likely(PyFunction_Check(descr) || (Py_TYPE(descr) == &PyMethodDescr_Type) || __Pyx_CyFunction_Check(descr)))
        #else
        if (likely(PyFunction_Check(descr) || (Py_TYPE(descr) == &PyMethodDescr_Type)))
        #endif
#else
        #ifdef __Pyx_CyFunction_USED
        if (likely(PyFunction_Check(descr) || __Pyx_CyFunction_Check(descr)))
        #else
        if (likely(PyFunction_Check(descr)))
        #endif
#endif
        {
            meth_found = 1;
        } else {
            f = Py_TYPE(descr)->tp_descr_get;
            if (f != NULL && PyDescr_IsData(descr)) {
                attr = f(descr, obj, (PyObject *)Py_TYPE(obj));
                Py_DECREF(descr);
                goto try_unpack;
            }
        }
    }
    dictptr = _PyObject_GetDictPtr(obj);
    if (dictptr != NULL && (dict = *dictptr) != NULL) {
        Py_INCREF(dict);
        attr = __Pyx_PyDict_GetItemStr(dict, name);
        if (attr != NULL) {
            Py_INCREF(attr);
            Py_DECREF(dict);
            Py_XDECREF(descr);
            goto try_unpack;
        }
        Py_DECREF(dict);
    }
    if (meth_found) {
        *method = descr;
        return 1;
    }
    if (f != NULL) {
        attr = f(descr, obj, (PyObject *)Py_TYPE(obj));
        Py_DECREF(descr);
        goto try_unpack;
    }
    if (descr != NULL) {
        *method = descr;
        return 0;
    }
    PyErr_Format(PyExc_AttributeError,
#if PY_MAJOR_VERSION >= 3
                 "'%.50s' object has no attribute '%U'",
                 tp->tp_name, name);
#else
                 "'%.50s' object has no attribute '%.400s'",
                 tp->tp_name, PyString_AS_STRING(name));
#endif
    return 0;
#else
    attr = __Pyx_PyObject_GetAttrStr(obj, name);
    goto try_unpack;
#endif
try_unpack:
#if CYTHON_UNPACK_METHODS
    if (likely(attr) && PyMethod_Check(attr) && likely(PyMethod_GET_SELF(attr) == obj)) {
        PyObject *function = PyMethod_GET_FUNCTION(attr);
        Py_INCREF(function);
        Py_DECREF(attr);
        *method = function;
        return 1;
    }
#endif
    *method = attr;
    return 0;
}

 
  static PyObject* __Pyx__PyObject_CallMethod1(PyObject* method, PyObject* arg) {
    PyObject *result = __Pyx_PyObject_CallOneArg(method, arg);
    Py_DECREF(method);
    return result;
}
static PyObject* __Pyx_PyObject_CallMethod1(PyObject* obj, PyObject* method_name, PyObject* arg) {
    PyObject *method = NULL, *result;
    int is_method = __Pyx_PyObject_GetMethod(obj, method_name, &method);
    if (likely(is_method)) {
        result = __Pyx_PyObject_Call2Args(method, obj, arg);
        Py_DECREF(method);
        return result;
    }
    if (unlikely(!method)) return NULL;
    return __Pyx__PyObject_CallMethod1(method, arg);
}

 
  static CYTHON_INLINE int __Pyx_PyObject_Append(PyObject* L, PyObject* x) {
    if (likely(PyList_CheckExact(L))) {
        if (unlikely(__Pyx_PyList_Append(L, x) < 0)) return -1;
    } else {
        PyObject* retval = __Pyx_PyObject_CallMethod1(L, __pyx_n_s_append, x);
        if (unlikely(!retval))
            return -1;
        Py_DECREF(retval);
    }
    return 0;
}

 
  #ifndef CYTHON_CLINE_IN_TRACEBACK
static int __Pyx_CLineForTraceback(CYTHON_UNUSED PyThreadState *tstate, int c_line) {
    PyObject *use_cline;
    PyObject *ptype, *pvalue, *ptraceback;
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject **cython_runtime_dict;
#endif
    if (unlikely(!__pyx_cython_runtime)) {
        return c_line;
    }
    __Pyx_ErrFetchInState(tstate, &ptype, &pvalue, &ptraceback);
#if CYTHON_COMPILING_IN_CPYTHON
    cython_runtime_dict = _PyObject_GetDictPtr(__pyx_cython_runtime);
    if (likely(cython_runtime_dict)) {
        __PYX_PY_DICT_LOOKUP_IF_MODIFIED(
            use_cline, *cython_runtime_dict,
            __Pyx_PyDict_GetItemStr(*cython_runtime_dict, __pyx_n_s_cline_in_traceback))
    } else
#endif
    {
      PyObject *use_cline_obj = __Pyx_PyObject_GetAttrStr(__pyx_cython_runtime, __pyx_n_s_cline_in_traceback);
      if (use_cline_obj) {
        use_cline = PyObject_Not(use_cline_obj) ? Py_False : Py_True;
        Py_DECREF(use_cline_obj);
      } else {
        PyErr_Clear();
        use_cline = NULL;
      }
    }
    if (!use_cline) {
        c_line = 0;
        (void) PyObject_SetAttr(__pyx_cython_runtime, __pyx_n_s_cline_in_traceback, Py_False);
    }
    else if (use_cline == Py_False || (use_cline != Py_True && PyObject_Not(use_cline) != 0)) {
        c_line = 0;
    }
    __Pyx_ErrRestoreInState(tstate, ptype, pvalue, ptraceback);
    return c_line;
}
#endif

 
  static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = start + (end - start) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, ((size_t)new_max) * sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

 
  #include "compile.h"
#include "frameobject.h"
#include "traceback.h"
#if PY_VERSION_HEX >= 0x030b00a6
  #ifndef Py_BUILD_CORE
    #define Py_BUILD_CORE 1
  #endif
  #include "internal/pycore_frame.h"
#endif
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = NULL;
    PyObject *py_funcname = NULL;
    #if PY_MAJOR_VERSION < 3
    PyObject *py_srcfile = NULL;
    py_srcfile = PyString_FromString(filename);
    if (!py_srcfile) goto bad;
    #endif
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        if (!py_funcname) goto bad;
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        if (!py_funcname) goto bad;
        funcname = PyUnicode_AsUTF8(py_funcname);
        if (!funcname) goto bad;
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        if (!py_funcname) goto bad;
        #endif
    }
    #if PY_MAJOR_VERSION < 3
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes,  
        __pyx_empty_tuple,  
        __pyx_empty_tuple,  
        __pyx_empty_tuple,  
        __pyx_empty_tuple,  
        __pyx_empty_tuple,  
        py_srcfile,    
        py_funcname,   
        py_line,
        __pyx_empty_bytes   
    );
    Py_DECREF(py_srcfile);
    #else
    py_code = PyCode_NewEmpty(filename, funcname, py_line);
    #endif
    Py_XDECREF(py_funcname);   
    return py_code;
bad:
    Py_XDECREF(py_funcname);
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(py_srcfile);
    #endif
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    PyThreadState *tstate = __Pyx_PyThreadState_Current;
    PyObject *ptype, *pvalue, *ptraceback;
    if (c_line) {
        c_line = __Pyx_CLineForTraceback(tstate, c_line);
    }
    py_code = __pyx_find_code_object(c_line ? -c_line : py_line);
    if (!py_code) {
        __Pyx_ErrFetchInState(tstate, &ptype, &pvalue, &ptraceback);
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) {
             
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
            goto bad;
        }
        __Pyx_ErrRestoreInState(tstate, ptype, pvalue, ptraceback);
        __pyx_insert_code_object(c_line ? -c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        tstate,             
        py_code,            
        __pyx_d,     
        0                   
    );
    if (!py_frame) goto bad;
    __Pyx_PyFrame_SetLineNumber(py_frame, py_line);
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

#if PY_MAJOR_VERSION < 3
static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags) {
    if (PyObject_CheckBuffer(obj)) return PyObject_GetBuffer(obj, view, flags);
        if (__Pyx_TypeCheck(obj, __pyx_array_type)) return __pyx_array_getbuffer(obj, view, flags);
        if (__Pyx_TypeCheck(obj, __pyx_memoryview_type)) return __pyx_memoryview_getbuffer(obj, view, flags);
    PyErr_Format(PyExc_TypeError, "'%.200s' does not have the buffer interface", Py_TYPE(obj)->tp_name);
    return -1;
}
static void __Pyx_ReleaseBuffer(Py_buffer *view) {
    PyObject *obj = view->obj;
    if (!obj) return;
    if (PyObject_CheckBuffer(obj)) {
        PyBuffer_Release(view);
        return;
    }
    if ((0)) {}
    view->obj = NULL;
    Py_DECREF(obj);
}
#endif


   
  static void
__pyx_get_array_memory_extents(__Pyx_memviewslice *slice,
                               void **out_start, void **out_end,
                               int ndim, size_t itemsize)
{
    char *start, *end;
    int i;
    start = end = slice->data;
    for (i = 0; i < ndim; i++) {
        Py_ssize_t stride = slice->strides[i];
        Py_ssize_t extent = slice->shape[i];
        if (extent == 0) {
            *out_start = *out_end = start;
            return;
        } else {
            if (stride > 0)
                end += stride * (extent - 1);
            else
                start += stride * (extent - 1);
        }
    }
    *out_start = start;
    *out_end = end + itemsize;
}
static int
__pyx_slices_overlap(__Pyx_memviewslice *slice1,
                     __Pyx_memviewslice *slice2,
                     int ndim, size_t itemsize)
{
    void *start1, *end1, *start2, *end2;
    __pyx_get_array_memory_extents(slice1, &start1, &end1, ndim, itemsize);
    __pyx_get_array_memory_extents(slice2, &start2, &end2, ndim, itemsize);
    return (start1 < end2) && (start2 < end1);
}

 
  static CYTHON_INLINE PyObject *
__pyx_capsule_create(void *p, CYTHON_UNUSED const char *sig)
{
    PyObject *cobj;
#if PY_VERSION_HEX >= 0x02070000
    cobj = PyCapsule_New(p, sig, NULL);
#else
    cobj = PyCObject_FromVoidPtr(p, NULL);
#endif
    return cobj;
}

 
  static int
__pyx_typeinfo_cmp(__Pyx_TypeInfo *a, __Pyx_TypeInfo *b)
{
    int i;
    if (!a || !b)
        return 0;
    if (a == b)
        return 1;
    if (a->size != b->size || a->typegroup != b->typegroup ||
            a->is_unsigned != b->is_unsigned || a->ndim != b->ndim) {
        if (a->typegroup == 'H' || b->typegroup == 'H') {
            return a->size == b->size;
        } else {
            return 0;
        }
    }
    if (a->ndim) {
        for (i = 0; i < a->ndim; i++)
            if (a->arraysize[i] != b->arraysize[i])
                return 0;
    }
    if (a->typegroup == 'S') {
        if (a->flags != b->flags)
            return 0;
        if (a->fields || b->fields) {
            if (!(a->fields && b->fields))
                return 0;
            for (i = 0; a->fields[i].type && b->fields[i].type; i++) {
                __Pyx_StructField *field_a = a->fields + i;
                __Pyx_StructField *field_b = b->fields + i;
                if (field_a->offset != field_b->offset ||
                    !__pyx_typeinfo_cmp(field_a->type, field_b->type))
                    return 0;
            }
            return !a->fields[i].type && !b->fields[i].type;
        }
    }
    return 1;
}

 
  static int
__pyx_check_strides(Py_buffer *buf, int dim, int ndim, int spec)
{
    if (buf->shape[dim] <= 1)
        return 1;
    if (buf->strides) {
        if (spec & __Pyx_MEMVIEW_CONTIG) {
            if (spec & (__Pyx_MEMVIEW_PTR|__Pyx_MEMVIEW_FULL)) {
                if (unlikely(buf->strides[dim] != sizeof(void *))) {
                    PyErr_Format(PyExc_ValueError,
                                 "Buffer is not indirectly contiguous "
                                 "in dimension %d.", dim);
                    goto fail;
                }
            } else if (unlikely(buf->strides[dim] != buf->itemsize)) {
                PyErr_SetString(PyExc_ValueError,
                                "Buffer and memoryview are not contiguous "
                                "in the same dimension.");
                goto fail;
            }
        }
        if (spec & __Pyx_MEMVIEW_FOLLOW) {
            Py_ssize_t stride = buf->strides[dim];
            if (stride < 0)
                stride = -stride;
            if (unlikely(stride < buf->itemsize)) {
                PyErr_SetString(PyExc_ValueError,
                                "Buffer and memoryview are not contiguous "
                                "in the same dimension.");
                goto fail;
            }
        }
    } else {
        if (unlikely(spec & __Pyx_MEMVIEW_CONTIG && dim != ndim - 1)) {
            PyErr_Format(PyExc_ValueError,
                         "C-contiguous buffer is not contiguous in "
                         "dimension %d", dim);
            goto fail;
        } else if (unlikely(spec & (__Pyx_MEMVIEW_PTR))) {
            PyErr_Format(PyExc_ValueError,
                         "C-contiguous buffer is not indirect in "
                         "dimension %d", dim);
            goto fail;
        } else if (unlikely(buf->suboffsets)) {
            PyErr_SetString(PyExc_ValueError,
                            "Buffer exposes suboffsets but no strides");
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}
static int
__pyx_check_suboffsets(Py_buffer *buf, int dim, CYTHON_UNUSED int ndim, int spec)
{
    if (spec & __Pyx_MEMVIEW_DIRECT) {
        if (unlikely(buf->suboffsets && buf->suboffsets[dim] >= 0)) {
            PyErr_Format(PyExc_ValueError,
                         "Buffer not compatible with direct access "
                         "in dimension %d.", dim);
            goto fail;
        }
    }
    if (spec & __Pyx_MEMVIEW_PTR) {
        if (unlikely(!buf->suboffsets || (buf->suboffsets[dim] < 0))) {
            PyErr_Format(PyExc_ValueError,
                         "Buffer is not indirectly accessible "
                         "in dimension %d.", dim);
            goto fail;
        }
    }
    return 1;
fail:
    return 0;
}
static int
__pyx_verify_contig(Py_buffer *buf, int ndim, int c_or_f_flag)
{
    int i;
    if (c_or_f_flag & __Pyx_IS_F_CONTIG) {
        Py_ssize_t stride = 1;
        for (i = 0; i < ndim; i++) {
            if (unlikely(stride * buf->itemsize != buf->strides[i]  &&  buf->shape[i] > 1)) {
                PyErr_SetString(PyExc_ValueError,
                    "Buffer not fortran contiguous.");
                goto fail;
            }
            stride = stride * buf->shape[i];
        }
    } else if (c_or_f_flag & __Pyx_IS_C_CONTIG) {
        Py_ssize_t stride = 1;
        for (i = ndim - 1; i >- 1; i--) {
            if (unlikely(stride * buf->itemsize != buf->strides[i]  &&  buf->shape[i] > 1)) {
                PyErr_SetString(PyExc_ValueError,
                    "Buffer not C contiguous.");
                goto fail;
            }
            stride = stride * buf->shape[i];
        }
    }
    return 1;
fail:
    return 0;
}
static int __Pyx_ValidateAndInit_memviewslice(
                int *axes_specs,
                int c_or_f_flag,
                int buf_flags,
                int ndim,
                __Pyx_TypeInfo *dtype,
                __Pyx_BufFmt_StackElem stack[],
                __Pyx_memviewslice *memviewslice,
                PyObject *original_obj)
{
    struct __pyx_memoryview_obj *memview, *new_memview;
    __Pyx_RefNannyDeclarations
    Py_buffer *buf;
    int i, spec = 0, retval = -1;
    __Pyx_BufFmt_Context ctx;
    int from_memoryview = __pyx_memoryview_check(original_obj);
    __Pyx_RefNannySetupContext("ValidateAndInit_memviewslice", 0);
    if (from_memoryview && __pyx_typeinfo_cmp(dtype, ((struct __pyx_memoryview_obj *)
                                                            original_obj)->typeinfo)) {
        memview = (struct __pyx_memoryview_obj *) original_obj;
        new_memview = NULL;
    } else {
        memview = (struct __pyx_memoryview_obj *) __pyx_memoryview_new(
                                            original_obj, buf_flags, 0, dtype);
        new_memview = memview;
        if (unlikely(!memview))
            goto fail;
    }
    buf = &memview->view;
    if (unlikely(buf->ndim != ndim)) {
        PyErr_Format(PyExc_ValueError,
                "Buffer has wrong number of dimensions (expected %d, got %d)",
                ndim, buf->ndim);
        goto fail;
    }
    if (new_memview) {
        __Pyx_BufFmt_Init(&ctx, stack, dtype);
        if (unlikely(!__Pyx_BufFmt_CheckString(&ctx, buf->format))) goto fail;
    }
    if (unlikely((unsigned) buf->itemsize != dtype->size)) {
        PyErr_Format(PyExc_ValueError,
                     "Item size of buffer (%" CYTHON_FORMAT_SSIZE_T "u byte%s) "
                     "does not match size of '%s' (%" CYTHON_FORMAT_SSIZE_T "u byte%s)",
                     buf->itemsize,
                     (buf->itemsize > 1) ? "s" : "",
                     dtype->name,
                     dtype->size,
                     (dtype->size > 1) ? "s" : "");
        goto fail;
    }
    if (buf->len > 0) {
        for (i = 0; i < ndim; i++) {
            spec = axes_specs[i];
            if (unlikely(!__pyx_check_strides(buf, i, ndim, spec)))
                goto fail;
            if (unlikely(!__pyx_check_suboffsets(buf, i, ndim, spec)))
                goto fail;
        }
        if (unlikely(buf->strides && !__pyx_verify_contig(buf, ndim, c_or_f_flag)))
            goto fail;
    }
    if (unlikely(__Pyx_init_memviewslice(memview, ndim, memviewslice,
                                         new_memview != NULL) == -1)) {
        goto fail;
    }
    retval = 0;
    goto no_fail;
fail:
    Py_XDECREF(new_memview);
    retval = -1;
no_fail:
    __Pyx_RefNannyFinishContext();
    return retval;
}

 
  static CYTHON_INLINE __Pyx_memviewslice __Pyx_PyObject_to_MemoryviewSlice_ds_unsigned_char__const__(PyObject *obj, int writable_flag) {
    __Pyx_memviewslice result = { 0, 0, { 0 }, { 0 }, { 0 } };
    __Pyx_BufFmt_StackElem stack[1];
    int axes_specs[] = { (__Pyx_MEMVIEW_DIRECT | __Pyx_MEMVIEW_STRIDED) };
    int retcode;
    if (obj == Py_None) {
        result.memview = (struct __pyx_memoryview_obj *) Py_None;
        return result;
    }
    retcode = __Pyx_ValidateAndInit_memviewslice(axes_specs, 0,
                                                 PyBUF_RECORDS_RO | writable_flag, 1,
                                                 &__Pyx_TypeInfo_unsigned_char__const__, stack,
                                                 &result, obj);
    if (unlikely(retcode == -1))
        goto __pyx_fail;
    return result;
__pyx_fail:
    result.memview = NULL;
    result.data = NULL;
    return result;
}

 
  #define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc)\
    {\
        func_type value = func_value;\
        if (sizeof(target_type) < sizeof(func_type)) {\
            if (unlikely(value != (func_type) (target_type) value)) {\
                func_type zero = 0;\
                if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))\
                    return (target_type) -1;\
                if (is_unsigned && unlikely(value < zero))\
                    goto raise_neg_overflow;\
                else\
                    goto raise_overflow;\
            }\
        }\
        return (target_type) value;\
    }

 
  static CYTHON_INLINE __Pyx_memviewslice __Pyx_PyObject_to_MemoryviewSlice_dsdsds_unsigned_char__const__(PyObject *obj, int writable_flag) {
    __Pyx_memviewslice result = { 0, 0, { 0 }, { 0 }, { 0 } };
    __Pyx_BufFmt_StackElem stack[1];
    int axes_specs[] = { (__Pyx_MEMVIEW_DIRECT | __Pyx_MEMVIEW_STRIDED), (__Pyx_MEMVIEW_DIRECT | __Pyx_MEMVIEW_STRIDED), (__Pyx_MEMVIEW_DIRECT | __Pyx_MEMVIEW_STRIDED) };
    int retcode;
    if (obj == Py_None) {
        result.memview = (struct __pyx_memoryview_obj *) Py_None;
        return result;
    }
    retcode = __Pyx_ValidateAndInit_memviewslice(axes_specs, 0,
                                                 PyBUF_RECORDS_RO | writable_flag, 3,
                                                 &__Pyx_TypeInfo_unsigned_char__const__, stack,
                                                 &result, obj);
    if (unlikely(retcode == -1))
        goto __pyx_fail;
    return result;
__pyx_fail:
    result.memview = NULL;
    result.data = NULL;
    return result;
}

 
  static CYTHON_INLINE PyObject *__pyx_memview_get_unsigned_char__const__(const char *itemp) {
    return (PyObject *) __Pyx_PyInt_From_unsigned_char(*(unsigned char const  *) itemp);
}

 
  #if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return ::std::complex< float >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return x + y*(__pyx_t_float_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      __pyx_t_float_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

 
  #if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eq_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sum_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_diff_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prod_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    #if 1
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        if (b.imag == 0) {
            return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else if (fabsf(b.real) >= fabsf(b.imag)) {
            if (b.real == 0 && b.imag == 0) {
                return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.imag);
            } else {
                float r = b.imag / b.real;
                float s = (float)(1.0) / (b.real + b.imag * r);
                return __pyx_t_float_complex_from_parts(
                    (a.real + a.imag * r) * s, (a.imag - a.real * r) * s);
            }
        } else {
            float r = b.real / b.imag;
            float s = (float)(1.0) / (b.imag + b.real * r);
            return __pyx_t_float_complex_from_parts(
                (a.real * r + a.imag) * s, (a.imag * r - a.real) * s);
        }
    }
    #else
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        if (b.imag == 0) {
            return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else {
            float denom = b.real * b.real + b.imag * b.imag;
            return __pyx_t_float_complex_from_parts(
                (a.real * b.real + a.imag * b.imag) / denom,
                (a.imag * b.real - a.real * b.imag) / denom);
        }
    }
    #endif
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_neg_float(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zero_float(__pyx_t_float_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conj_float(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE float __Pyx_c_abs_float(__pyx_t_float_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrtf(z.real*z.real + z.imag*z.imag);
          #else
            return hypotf(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_pow_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
            __pyx_t_float_complex z;
            float r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    float denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        return __Pyx_c_prod_float(a, a);
                    case 3:
                        z = __Pyx_c_prod_float(a, a);
                        return __Pyx_c_prod_float(z, a);
                    case 4:
                        z = __Pyx_c_prod_float(a, a);
                        return __Pyx_c_prod_float(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                } else if ((b.imag == 0) && (a.real >= 0)) {
                    z.real = powf(a.real, b.real);
                    z.imag = 0;
                    return z;
                } else if (a.real > 0) {
                    r = a.real;
                    theta = 0;
                } else {
                    r = -a.real;
                    theta = atan2f(0.0, -1.0);
                }
            } else {
                r = __Pyx_c_abs_float(a);
                theta = atan2f(a.imag, a.real);
            }
            lnr = logf(r);
            z_r = expf(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cosf(z_theta);
            z.imag = z_r * sinf(z_theta);
            return z;
        }
    #endif
#endif

 
  #if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return ::std::complex< double >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return x + y*(__pyx_t_double_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      __pyx_t_double_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

 
  #if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eq_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    #if 1
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        if (b.imag == 0) {
            return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else if (fabs(b.real) >= fabs(b.imag)) {
            if (b.real == 0 && b.imag == 0) {
                return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.imag);
            } else {
                double r = b.imag / b.real;
                double s = (double)(1.0) / (b.real + b.imag * r);
                return __pyx_t_double_complex_from_parts(
                    (a.real + a.imag * r) * s, (a.imag - a.real * r) * s);
            }
        } else {
            double r = b.real / b.imag;
            double s = (double)(1.0) / (b.imag + b.real * r);
            return __pyx_t_double_complex_from_parts(
                (a.real * r + a.imag) * s, (a.imag * r - a.real) * s);
        }
    }
    #else
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        if (b.imag == 0) {
            return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else {
            double denom = b.real * b.real + b.imag * b.imag;
            return __pyx_t_double_complex_from_parts(
                (a.real * b.real + a.imag * b.imag) / denom,
                (a.imag * b.real - a.real * b.imag) / denom);
        }
    }
    #endif
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg_double(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zero_double(__pyx_t_double_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj_double(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs_double(__pyx_t_double_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrt(z.real*z.real + z.imag*z.imag);
          #else
            return hypot(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
            __pyx_t_double_complex z;
            double r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    double denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        return __Pyx_c_prod_double(a, a);
                    case 3:
                        z = __Pyx_c_prod_double(a, a);
                        return __Pyx_c_prod_double(z, a);
                    case 4:
                        z = __Pyx_c_prod_double(a, a);
                        return __Pyx_c_prod_double(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                } else if ((b.imag == 0) && (a.real >= 0)) {
                    z.real = pow(a.real, b.real);
                    z.imag = 0;
                    return z;
                } else if (a.real > 0) {
                    r = a.real;
                    theta = 0;
                } else {
                    r = -a.real;
                    theta = atan2(0.0, -1.0);
                }
            } else {
                r = __Pyx_c_abs_double(a);
                theta = atan2(a.imag, a.real);
            }
            lnr = log(r);
            z_r = exp(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cos(z_theta);
            z.imag = z_r * sin(z_theta);
            return z;
        }
    #endif
#endif

 
  static __Pyx_memviewslice
__pyx_memoryview_copy_new_contig(const __Pyx_memviewslice *from_mvs,
                                 const char *mode, int ndim,
                                 size_t sizeof_dtype, int contig_flag,
                                 int dtype_is_object)
{
    __Pyx_RefNannyDeclarations
    int i;
    __Pyx_memviewslice new_mvs = { 0, 0, { 0 }, { 0 }, { 0 } };
    struct __pyx_memoryview_obj *from_memview = from_mvs->memview;
    Py_buffer *buf = &from_memview->view;
    PyObject *shape_tuple = NULL;
    PyObject *temp_int = NULL;
    struct __pyx_array_obj *array_obj = NULL;
    struct __pyx_memoryview_obj *memview_obj = NULL;
    __Pyx_RefNannySetupContext("__pyx_memoryview_copy_new_contig", 0);
    for (i = 0; i < ndim; i++) {
        if (unlikely(from_mvs->suboffsets[i] >= 0)) {
            PyErr_Format(PyExc_ValueError, "Cannot copy memoryview slice with "
                                           "indirect dimensions (axis %d)", i);
            goto fail;
        }
    }
    shape_tuple = PyTuple_New(ndim);
    if (unlikely(!shape_tuple)) {
        goto fail;
    }
    __Pyx_GOTREF(shape_tuple);
    for(i = 0; i < ndim; i++) {
        temp_int = PyInt_FromSsize_t(from_mvs->shape[i]);
        if(unlikely(!temp_int)) {
            goto fail;
        } else {
            PyTuple_SET_ITEM(shape_tuple, i, temp_int);
            temp_int = NULL;
        }
    }
    array_obj = __pyx_array_new(shape_tuple, sizeof_dtype, buf->format, (char *) mode, NULL);
    if (unlikely(!array_obj)) {
        goto fail;
    }
    __Pyx_GOTREF(array_obj);
    memview_obj = (struct __pyx_memoryview_obj *) __pyx_memoryview_new(
                                    (PyObject *) array_obj, contig_flag,
                                    dtype_is_object,
                                    from_mvs->memview->typeinfo);
    if (unlikely(!memview_obj))
        goto fail;
    if (unlikely(__Pyx_init_memviewslice(memview_obj, ndim, &new_mvs, 1) < 0))
        goto fail;
    if (unlikely(__pyx_memoryview_copy_contents(*from_mvs, new_mvs, ndim, ndim,
                                                dtype_is_object) < 0))
        goto fail;
    goto no_fail;
fail:
    __Pyx_XDECREF(new_mvs.memview);
    new_mvs.memview = NULL;
    new_mvs.data = NULL;
no_fail:
    __Pyx_XDECREF(shape_tuple);
    __Pyx_XDECREF(temp_int);
    __Pyx_XDECREF(array_obj);
    __Pyx_RefNannyFinishContext();
    return new_mvs;
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const int neg_one = (int) -1, const_zero = (int) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(int) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(int) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(int) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(int),
                                     little, !is_unsigned);
    }
}

 
  static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const int neg_one = (int) -1, const_zero = (int) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
                            return (int) (((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
                            return (int) (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
                            return (int) (((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030C00A7
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) ((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) ((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) ((((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const long neg_one = (long) -1, const_zero = (long) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_unsigned_char(unsigned char value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const unsigned char neg_one = (unsigned char) -1, const_zero = (unsigned char) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(unsigned char) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(unsigned char) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(unsigned char) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(unsigned char) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(unsigned char) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(unsigned char),
                                     little, !is_unsigned);
    }
}

 
  static CYTHON_INLINE PyObject* __Pyx_PyInt_From_Py_intptr_t(Py_intptr_t value) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const Py_intptr_t neg_one = (Py_intptr_t) -1, const_zero = (Py_intptr_t) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(Py_intptr_t) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(Py_intptr_t) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(Py_intptr_t) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(Py_intptr_t) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(Py_intptr_t) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(Py_intptr_t),
                                     little, !is_unsigned);
    }
}

 
  static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const long neg_one = (long) -1, const_zero = (long) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
                            return (long) (((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
                            return (long) (((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
                            return (long) (((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030C00A7
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) ((((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) ((((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) ((((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

 
  static CYTHON_INLINE char __Pyx_PyInt_As_char(PyObject *x) {
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    const char neg_one = (char) -1, const_zero = (char) 0;
#ifdef __Pyx_HAS_GCC_DIAGNOSTIC
#pragma GCC diagnostic pop
#endif
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(char) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(char, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (char) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (char) 0;
                case  1: __PYX_VERIFY_RETURN_INT(char, digit, digits[0])
                case 2:
                    if (8 * sizeof(char) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) >= 2 * PyLong_SHIFT) {
                            return (char) (((((char)digits[1]) << PyLong_SHIFT) | (char)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(char) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) >= 3 * PyLong_SHIFT) {
                            return (char) (((((((char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(char) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) >= 4 * PyLong_SHIFT) {
                            return (char) (((((((((char)digits[3]) << PyLong_SHIFT) | (char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX < 0x030C00A7
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (char) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(char) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(char, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(char) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(char, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (char) 0;
                case -1: __PYX_VERIFY_RETURN_INT(char, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(char,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(char) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 2 * PyLong_SHIFT) {
                            return (char) (((char)-1)*(((((char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(char) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 2 * PyLong_SHIFT) {
                            return (char) ((((((char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(char) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 3 * PyLong_SHIFT) {
                            return (char) (((char)-1)*(((((((char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(char) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 3 * PyLong_SHIFT) {
                            return (char) ((((((((char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(char) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 4 * PyLong_SHIFT) {
                            return (char) (((char)-1)*(((((((((char)digits[3]) << PyLong_SHIFT) | (char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(char) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(char, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(char) - 1 > 4 * PyLong_SHIFT) {
                            return (char) ((((((((((char)digits[3]) << PyLong_SHIFT) | (char)digits[2]) << PyLong_SHIFT) | (char)digits[1]) << PyLong_SHIFT) | (char)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(char) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(char, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(char) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(char, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            char val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (char) -1;
        }
    } else {
        char val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (char) -1;
        val = __Pyx_PyInt_As_char(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to char");
    return (char) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to char");
    return (char) -1;
}

 
  static int __Pyx_check_binary_version(void) {
    char ctversion[5];
    int same=1, i, found_dot;
    const char* rt_from_call = Py_GetVersion();
    PyOS_snprintf(ctversion, 5, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    found_dot = 0;
    for (i = 0; i < 4; i++) {
        if (!ctversion[i]) {
            same = (rt_from_call[i] < '0' || rt_from_call[i] > '9');
            break;
        }
        if (rt_from_call[i] != ctversion[i]) {
            same = 0;
            break;
        }
    }
    if (!same) {
        char rtversion[5] = {'\0'};
        char message[200];
        for (i=0; i<4; ++i) {
            if (rt_from_call[i] == '.') {
                if (found_dot) break;
                found_dot = 1;
            } else if (rt_from_call[i] < '0' || rt_from_call[i] > '9') {
                break;
            }
            rtversion[i] = rt_from_call[i];
        }
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

 
  static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        if (PyObject_Hash(*t->p) == -1)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE const char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
#if !CYTHON_PEP393_ENABLED
static const char* __Pyx_PyUnicode_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
    char* defenc_c;
    PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
    if (!defenc) return NULL;
    defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    {
        char* end = defenc_c + PyBytes_GET_SIZE(defenc);
        char* c;
        for (c = defenc_c; c < end; c++) {
            if ((unsigned char) (*c) >= 128) {
                PyUnicode_AsASCIIString(o);
                return NULL;
            }
        }
    }
#endif
    *length = PyBytes_GET_SIZE(defenc);
    return defenc_c;
}
#else
static CYTHON_INLINE const char* __Pyx_PyUnicode_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
    if (unlikely(__Pyx_PyUnicode_READY(o) == -1)) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    if (likely(PyUnicode_IS_ASCII(o))) {
        *length = PyUnicode_GET_LENGTH(o);
        return PyUnicode_AsUTF8(o);
    } else {
        PyUnicode_AsASCIIString(o);
        return NULL;
    }
#else
    return PyUnicode_AsUTF8AndSize(o, length);
#endif
}
#endif
#endif
static CYTHON_INLINE const char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
        return __Pyx_PyUnicode_AsStringAndSize(o, length);
    } else
#endif
#if (!CYTHON_COMPILING_IN_PYPY) || (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrueAndDecref(PyObject* x) {
    int retval;
    if (unlikely(!x)) return -1;
    retval = __Pyx_PyObject_IsTrue(x);
    Py_DECREF(x);
    return retval;
}
static PyObject* __Pyx_PyNumber_IntOrLongWrongResultType(PyObject* result, const char* type_name) {
#if PY_MAJOR_VERSION >= 3
    if (PyLong_Check(result)) {
        if (PyErr_WarnFormat(PyExc_DeprecationWarning, 1,
                "__int__ returned non-int (type %.200s).  "
                "The ability to return an instance of a strict subclass of int "
                "is deprecated, and may be removed in a future version of Python.",
                Py_TYPE(result)->tp_name)) {
            Py_DECREF(result);
            return NULL;
        }
        return result;
    }
#endif
    PyErr_Format(PyExc_TypeError,
                 "__%.4s__ returned non-%.4s (type %.200s)",
                 type_name, type_name, Py_TYPE(result)->tp_name);
    Py_DECREF(result);
    return NULL;
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x) {
#if CYTHON_USE_TYPE_SLOTS
  PyNumberMethods *m;
#endif
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_Check(x) || PyLong_Check(x)))
#else
  if (likely(PyLong_Check(x)))
#endif
    return __Pyx_NewRef(x);
#if CYTHON_USE_TYPE_SLOTS
  m = Py_TYPE(x)->tp_as_number;
  #if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = m->nb_int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = m->nb_long(x);
  }
  #else
  if (likely(m && m->nb_int)) {
    name = "int";
    res = m->nb_int(x);
  }
  #endif
#else
  if (!PyBytes_CheckExact(x) && !PyUnicode_CheckExact(x)) {
    res = PyNumber_Int(x);
  }
#endif
  if (likely(res)) {
#if PY_MAJOR_VERSION < 3
    if (unlikely(!PyInt_Check(res) && !PyLong_Check(res))) {
#else
    if (unlikely(!PyLong_CheckExact(res))) {
#endif
        return __Pyx_PyNumber_IntOrLongWrongResultType(res, name);
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
        return PyInt_AS_LONG(b);
    else
        return PyInt_AsSsize_t(b);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_USE_PYLONG_INTERNALS
    const digit* digits = ((PyLongObject*)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
        ival = likely(size) ? digits[0] : 0;
        if (size == -1) ival = -ival;
        return ival;
    } else {
      switch (size) {
         case 2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
      }
    }
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE Py_hash_t __Pyx_PyIndex_AsHash_t(PyObject* o) {
  if (sizeof(Py_hash_t) == sizeof(Py_ssize_t)) {
    return (Py_hash_t) __Pyx_PyIndex_AsSsize_t(o);
#if PY_MAJOR_VERSION < 3
  } else if (likely(PyInt_CheckExact(o))) {
    return PyInt_AS_LONG(o);
#endif
  } else {
    Py_ssize_t ival;
    PyObject *x;
    x = PyNumber_Index(o);
    if (!x) return -1;
    ival = PyInt_AsLong(x);
    Py_DECREF(x);
    return ival;
  }
}
static CYTHON_INLINE PyObject * __Pyx_PyBool_FromLong(long b) {
  return b ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False);
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif  
