/*
 * The bootstrap compiler for Raft.
 *
 * This compiler is not intended to be compatible with raftc.
 * The only purpose is to provide raftc compilation, in the absence of raftc.
 * Nonetheless, it's able to compile some of the programs written in Raft.
 *
 * License: MIT
 */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
#error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x03060000
#error RFC requires Python 3.6+.
#else
#include <stddef.h>
#ifndef offsetof
#define offsetof(type, member) ((size_t) & ((type *)0)->member)
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
#if PY_VERSION_HEX >= 0x03030000 || \
    (PY_MAJOR_VERSION == 2 && PY_VERSION_HEX >= 0x02070000)
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
#define RFC_COMPILING_IN_PYPY 1
#define RFC_COMPILING_IN_PYSTON 0
#define RFC_COMPILING_IN_CPYTHON 0
#undef RFC_USE_TYPE_SLOTS
#define RFC_USE_TYPE_SLOTS 0
#undef RFC_USE_PYTYPE_LOOKUP
#define RFC_USE_PYTYPE_LOOKUP 0
#undef RFC_USE_ASYNC_SLOTS
#define RFC_USE_ASYNC_SLOTS 0
#undef RFC_USE_PYLIST_INTERNALS
#define RFC_USE_PYLIST_INTERNALS 0
#undef RFC_USE_UNICODE_INTERNALS
#define RFC_USE_UNICODE_INTERNALS 0
#undef RFC_USE_UNICODE_WRITER
#define RFC_USE_UNICODE_WRITER 0
#undef RFC_USE_PYLONG_INTERNALS
#define RFC_USE_PYLONG_INTERNALS 0
#undef RFC_AVOID_BORROWED_REFS
#define RFC_AVOID_BORROWED_REFS 1
#undef RFC_ASSUME_SAFE_MACROS
#define RFC_ASSUME_SAFE_MACROS 0
#undef RFC_UNPACK_METHODS
#define RFC_UNPACK_METHODS 0
#undef RFC_FAST_THREAD_STATE
#define RFC_FAST_THREAD_STATE 0
#undef RFC_FAST_PYCALL
#define RFC_FAST_PYCALL 0
#elif defined(PYSTON_VERSION)
#define RFC_COMPILING_IN_PYPY 0
#define RFC_COMPILING_IN_PYSTON 1
#define RFC_COMPILING_IN_CPYTHON 0
#ifndef RFC_USE_TYPE_SLOTS
#define RFC_USE_TYPE_SLOTS 1
#endif
#undef RFC_USE_PYTYPE_LOOKUP
#define RFC_USE_PYTYPE_LOOKUP 0
#undef RFC_USE_ASYNC_SLOTS
#define RFC_USE_ASYNC_SLOTS 0
#undef RFC_USE_PYLIST_INTERNALS
#define RFC_USE_PYLIST_INTERNALS 0
#ifndef RFC_USE_UNICODE_INTERNALS
#define RFC_USE_UNICODE_INTERNALS 1
#endif
#undef RFC_USE_UNICODE_WRITER
#define RFC_USE_UNICODE_WRITER 0
#undef RFC_USE_PYLONG_INTERNALS
#define RFC_USE_PYLONG_INTERNALS 0
#ifndef RFC_AVOID_BORROWED_REFS
#define RFC_AVOID_BORROWED_REFS 0
#endif
#ifndef RFC_ASSUME_SAFE_MACROS
#define RFC_ASSUME_SAFE_MACROS 1
#endif
#ifndef RFC_UNPACK_METHODS
#define RFC_UNPACK_METHODS 1
#endif
#undef RFC_FAST_THREAD_STATE
#define RFC_FAST_THREAD_STATE 0
#undef RFC_FAST_PYCALL
#define RFC_FAST_PYCALL 0
#else
#define RFC_COMPILING_IN_PYPY 0
#define RFC_COMPILING_IN_PYSTON 0
#define RFC_COMPILING_IN_CPYTHON 1
#ifndef RFC_USE_TYPE_SLOTS
#define RFC_USE_TYPE_SLOTS 1
#endif
#if PY_VERSION_HEX < 0x02070000
#undef RFC_USE_PYTYPE_LOOKUP
#define RFC_USE_PYTYPE_LOOKUP 0
#elif !defined(RFC_USE_PYTYPE_LOOKUP)
#define RFC_USE_PYTYPE_LOOKUP 1
#endif
#if PY_MAJOR_VERSION < 3
#undef RFC_USE_ASYNC_SLOTS
#define RFC_USE_ASYNC_SLOTS 0
#elif !defined(RFC_USE_ASYNC_SLOTS)
#define RFC_USE_ASYNC_SLOTS 1
#endif
#if PY_VERSION_HEX < 0x02070000
#undef RFC_USE_PYLONG_INTERNALS
#define RFC_USE_PYLONG_INTERNALS 0
#elif !defined(RFC_USE_PYLONG_INTERNALS)
#define RFC_USE_PYLONG_INTERNALS 1
#endif
#ifndef RFC_USE_PYLIST_INTERNALS
#define RFC_USE_PYLIST_INTERNALS 1
#endif
#ifndef RFC_USE_UNICODE_INTERNALS
#define RFC_USE_UNICODE_INTERNALS 1
#endif
#if PY_VERSION_HEX < 0x030300F0
#undef RFC_USE_UNICODE_WRITER
#define RFC_USE_UNICODE_WRITER 0
#elif !defined(RFC_USE_UNICODE_WRITER)
#define RFC_USE_UNICODE_WRITER 1
#endif
#ifndef RFC_AVOID_BORROWED_REFS
#define RFC_AVOID_BORROWED_REFS 0
#endif
#ifndef RFC_ASSUME_SAFE_MACROS
#define RFC_ASSUME_SAFE_MACROS 1
#endif
#ifndef RFC_UNPACK_METHODS
#define RFC_UNPACK_METHODS 1
#endif
#ifndef RFC_FAST_THREAD_STATE
#define RFC_FAST_THREAD_STATE 1
#endif
#ifndef RFC_FAST_PYCALL
#define RFC_FAST_PYCALL 1
#endif
#endif
#if !defined(RFC_FAST_PYCCALL)
#define RFC_FAST_PYCCALL (RFC_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if RFC_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#undef SHIFT
#undef BASE
#undef MASK
#endif
#if RFC_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && \
    !defined(Py_OptimizeFlag)
#define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define RFC_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
#define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
#define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, \
                         fline, lnos)                                      \
  PyCode_New(a + k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#define __Pyx_DefaultClassType PyClass_Type
#else
#define __Pyx_BUILTIN_MODULE_NAME "builtins"
#define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, \
                         fline, lnos)                                      \
  PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
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
#if PY_VERSION_HEX < 0x030700A0 || !defined(METH_FASTCALL)
#ifndef METH_FASTCALL
#define METH_FASTCALL 0x80
#endif
typedef PyObject *(*__Pyx_PyCFunctionFast)(PyObject *self, PyObject **args,
                                           Py_ssize_t nargs);
typedef PyObject *(*__Pyx_PyCFunctionFastWithKeywords)(PyObject *self,
                                                       PyObject **args,
                                                       Py_ssize_t nargs,
                                                       PyObject *kwnames);
#else
#define __Pyx_PyCFunctionFast _PyCFunctionFast
#define __Pyx_PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords
#endif
#if RFC_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func) \
  ((PyCFunction_Check(func) &&            \
    (METH_FASTCALL ==                     \
     (PyCFunction_GET_FLAGS(func) &       \
      ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
#define RFC_PEP393_ENABLED 1
#define __Pyx_PyUnicode_READY(op) \
  (likely(PyUnicode_IS_READY(op)) ? 0 : _PyUnicode_Ready((PyObject *)(op)))
#define __Pyx_PyUnicode_GET_LENGTH(u) PyUnicode_GET_LENGTH(u)
#define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
#define __Pyx_PyUnicode_MAX_CHAR_VALUE(u) PyUnicode_MAX_CHAR_VALUE(u)
#define __Pyx_PyUnicode_KIND(u) PyUnicode_KIND(u)
#define __Pyx_PyUnicode_DATA(u) PyUnicode_DATA(u)
#define __Pyx_PyUnicode_READ(k, d, i) PyUnicode_READ(k, d, i)
#define __Pyx_PyUnicode_WRITE(k, d, i, ch) PyUnicode_WRITE(k, d, i, ch)
#define __Pyx_PyUnicode_IS_TRUE(u)                               \
  (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) \
                                       : PyUnicode_GET_SIZE(u)))
#else
#define RFC_PEP393_ENABLED 0
#define PyUnicode_1BYTE_KIND 1
#define PyUnicode_2BYTE_KIND 2
#define PyUnicode_4BYTE_KIND 4
#define __Pyx_PyUnicode_READY(op) (0)
#define __Pyx_PyUnicode_GET_LENGTH(u) PyUnicode_GET_SIZE(u)
#define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
#define __Pyx_PyUnicode_MAX_CHAR_VALUE(u) \
  ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
#define __Pyx_PyUnicode_KIND(u) (sizeof(Py_UNICODE))
#define __Pyx_PyUnicode_DATA(u) ((void *)PyUnicode_AS_UNICODE(u))
#define __Pyx_PyUnicode_READ(k, d, i) \
  ((void)(k), (Py_UCS4)(((Py_UNICODE *)d)[i]))
#define __Pyx_PyUnicode_WRITE(k, d, i, ch) \
  (((void)(k)), ((Py_UNICODE *)d)[i] = ch)
#define __Pyx_PyUnicode_IS_TRUE(u) (0 != PyUnicode_GET_SIZE(u))
#endif
#if RFC_COMPILING_IN_PYPY
#define __Pyx_PyUnicode_Concat(a, b) PyNumber_Add(a, b)
#define __Pyx_PyUnicode_ConcatSafe(a, b) PyNumber_Add(a, b)
#else
#define __Pyx_PyUnicode_Concat(a, b) PyUnicode_Concat(a, b)
#define __Pyx_PyUnicode_ConcatSafe(a, b)                  \
  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) \
       ? PyNumber_Add(a, b)                               \
       : __Pyx_PyUnicode_Concat(a, b))
#endif
#if RFC_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
#define PyUnicode_Contains(u, s) PySequence_Contains(u, s)
#endif
#if RFC_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
#define PyByteArray_Check(obj) PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if RFC_COMPILING_IN_PYPY && !defined(PyObject_Format)
#define PyObject_Format(obj, fmt) \
  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#if RFC_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
#define PyObject_Malloc(s) PyMem_Malloc(s)
#define PyObject_Free(p) PyMem_Free(p)
#define PyObject_Realloc(p) PyMem_Realloc(p)
#endif
#if RFC_COMPILING_IN_PYSTON
#define __Pyx_PyCode_HasFreeVars(co) PyCode_HasFreeVars(co)
#define __Pyx_PyFrame_SetLineNumber(frame, lineno) \
  PyFrame_SetLineNumber(frame, lineno)
#else
#define __Pyx_PyCode_HasFreeVars(co) (PyCode_GetNumFree(co) > 0)
#define __Pyx_PyFrame_SetLineNumber(frame, lineno) (frame)->f_lineno = (lineno)
#endif
#define __Pyx_PyString_FormatSafe(a, b)                  \
  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) \
                              : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)                 \
  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) \
                              : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Format(a, b) PyUnicode_Format(a, b)
#else
#define __Pyx_PyString_Format(a, b) PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
#define PyObject_ASCII(o) PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
#define PyBaseString_Type PyUnicode_Type
#define PyStringObject PyUnicodeObject
#define PyString_Type PyUnicode_Type
#define PyString_Check PyUnicode_Check
#define PyString_CheckExact PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
#define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
#define __Pyx_PyBaseString_Check(obj) \
  (PyString_Check(obj) || PyUnicode_Check(obj))
#define __Pyx_PyBaseString_CheckExact(obj) \
  (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
#define PySet_CheckExact(obj) (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)
#if PY_MAJOR_VERSION >= 3
#define PyIntObject PyLongObject
#define PyInt_Type PyLong_Type
#define PyInt_Check(op) PyLong_Check(op)
#define PyInt_CheckExact(op) PyLong_CheckExact(op)
#define PyInt_FromString PyLong_FromString
#define PyInt_FromUnicode PyLong_FromUnicode
#define PyInt_FromLong PyLong_FromLong
#define PyInt_FromSize_t PyLong_FromSize_t
#define PyInt_FromSsize_t PyLong_FromSsize_t
#define PyInt_AsLong PyLong_AsLong
#define PyInt_AS_LONG PyLong_AS_LONG
#define PyInt_AsSsize_t PyLong_AsSsize_t
#define PyInt_AsUnsignedLongMask PyLong_AsUnsignedLongMask
#define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
#define PyNumber_Int PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
#define PyBoolObject PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && RFC_COMPILING_IN_PYPY
#ifndef PyUnicode_InternFromString
#define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
#endif
#endif
#if PY_VERSION_HEX < 0x030200A4
typedef long Py_hash_t;
#define __Pyx_PyInt_FromHash_t PyInt_FromLong
#define __Pyx_PyInt_AsHash_t PyInt_AsLong
#else
#define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
#define __Pyx_PyInt_AsHash_t PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyMethod_New(func, self, klass) \
  ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
#define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif
#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif
#if RFC_USE_ASYNC_SLOTS
#if PY_VERSION_HEX >= 0x030500B1
#define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
#define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
#else
typedef struct {
  unaryfunc am_await;
  unaryfunc am_aiter;
  unaryfunc am_anext;
} __Pyx_PyAsyncMethodsStruct;
#define __Pyx_PyType_AsAsync(obj) \
  ((__Pyx_PyAsyncMethodsStruct *)(Py_TYPE(obj)->tp_reserved))
#endif
#else
#define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef RFC_RESTRICT
#if defined(__GNUC__)
#define RFC_RESTRICT __restrict__
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#define RFC_RESTRICT __restrict
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define RFC_RESTRICT restrict
#else
#define RFC_RESTRICT
#endif
#endif
#ifndef RFC_UNUSED
#if defined(__GNUC__)
#if !(defined(__cplusplus)) || \
    (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define RFC_UNUSED __attribute__((__unused__))
#else
#define RFC_UNUSED
#endif
#elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#define RFC_UNUSED __attribute__((__unused__))
#else
#define RFC_UNUSED
#endif
#endif
#ifndef RFC_MAYBE_UNUSED_VAR
#if defined(__cplusplus)
template <class T>
void RFC_MAYBE_UNUSED_VAR(const T &) {}
#else
#define RFC_MAYBE_UNUSED_VAR(x) (void)(x)
#endif
#endif
#ifndef RFC_NCP_UNUSED
#if RFC_COMPILING_IN_CPYTHON
#define RFC_NCP_UNUSED
#else
#define RFC_NCP_UNUSED RFC_UNUSED
#endif
#endif
#define __Pyx_void_to_None(void_result) \
  ((void)(void_result), Py_INCREF(Py_None), Py_None)
#ifdef _MSC_VER
#ifndef _MSC_STDINT_H_
#if _MSC_VER < 1300
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#else
typedef unsigned __int8 uint8_t;
typedef unsigned __int32 uint32_t;
#endif
#endif
#else
#include <stdint.h>
#endif
#ifndef RFC_FALLTHROUGH
#ifdef __cplusplus
#if __has_cpp_attribute(fallthrough)
#define RFC_FALLTHROUGH [[fallthrough]]
#elif __has_cpp_attribute(clang::fallthrough)
#define RFC_FALLTHROUGH [[clang::fallthrough]]
#endif
#endif
#ifndef RFC_FALLTHROUGH
#if __has_attribute(fallthrough) || \
    (defined(__GNUC__) && defined(__attribute__))
#define RFC_FALLTHROUGH __attribute__((fallthrough))
#else
#define RFC_FALLTHROUGH
#endif
#endif
#endif

#ifndef RFC_INLINE
#if defined(__clang__)
#define RFC_INLINE __inline__ __attribute__((__unused__))
#elif defined(__GNUC__)
#define RFC_INLINE __inline__
#elif defined(_MSC_VER)
#define RFC_INLINE __inline
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define RFC_INLINE inline
#else
#define RFC_INLINE
#endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float)NAN)
#else
static RFC_INLINE float __PYX_NAN() {
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

#define __PYX_ERR(f_index, lineno, Ln_error) \
  {                                          \
    __pyx_filename = __pyx_f[f_index];       \
    __pyx_lineno = lineno;                   \
    __pyx_clineno = __LINE__;                \
    goto Ln_error;                           \
  }

#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Divide(x, y) PyNumber_TrueDivide(x, y)
#define __Pyx_PyNumber_InPlaceDivide(x, y) PyNumber_InPlaceTrueDivide(x, y)
#else
#define __Pyx_PyNumber_Divide(x, y) PyNumber_TrueDivide(x, y)
#define __Pyx_PyNumber_InPlaceDivide(x, y) PyNumber_InPlaceTrueDivide(x, y)
#endif

#ifndef __PYX_EXTERN_C
#ifdef __cplusplus
#define __PYX_EXTERN_C extern "C"
#else
#define __PYX_EXTERN_C extern
#endif
#endif

#define __PYX_HAVE__rfc
#define __PYX_HAVE_API__rfc
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define RFC_WITHOUT_ASSERTIONS
#endif

typedef struct {
  PyObject **p;
  const char *s;
  const Py_ssize_t n;
  const char *encoding;
  const char is_unicode;
  const char is_str;
  const char intern;
} __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)                       \
  ((sizeof(type) < sizeof(Py_ssize_t)) ||                               \
   (sizeof(type) > sizeof(Py_ssize_t) &&                                \
    likely(v < (type)PY_SSIZE_T_MAX || v == (type)PY_SSIZE_T_MAX) &&    \
    (!is_signed ||                                                      \
     likely(v > (type)PY_SSIZE_T_MIN || v == (type)PY_SSIZE_T_MIN))) || \
   (sizeof(type) == sizeof(Py_ssize_t) &&                               \
    (is_signed ||                                                       \
     likely(v < (type)PY_SSIZE_T_MAX || v == (type)PY_SSIZE_T_MAX))))
#if defined(__cplusplus) && __cplusplus >= 201103L
#include <cstdlib>
#define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
#define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
#define __Pyx_sst_abs(value) labs(value)
#elif defined(_MSC_VER) && defined(_M_X64)
#define __Pyx_sst_abs(value) _abs64(value)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define __Pyx_sst_abs(value) llabs(value)
#elif defined(__GNUC__)
#define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
#define __Pyx_sst_abs(value) ((value < 0) ? -value : value)
#endif
static RFC_INLINE const char *__Pyx_PyObject_AsString(PyObject *);
static RFC_INLINE const char *__Pyx_PyObject_AsStringAndSize(
    PyObject *, Py_ssize_t *length);
#define __Pyx_PyByteArray_FromString(s) \
  PyByteArray_FromStringAndSize((const char *)s, strlen((const char *)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) \
  PyByteArray_FromStringAndSize((const char *)s, l)
#define __Pyx_PyBytes_FromString PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static RFC_INLINE PyObject *__Pyx_PyUnicode_FromString(const char *);
#if PY_MAJOR_VERSION < 3
#define __Pyx_PyStr_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
#define __Pyx_PyStr_FromString __Pyx_PyUnicode_FromString
#define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsWritableString(s) ((char *)__Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableSString(s) \
  ((signed char *)__Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsWritableUString(s) \
  ((unsigned char *)__Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsSString(s) \
  ((const signed char *)__Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s) \
  ((const unsigned char *)__Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s) __Pyx_PyObject_FromString((const char *)s)
#define __Pyx_PyBytes_FromCString(s) __Pyx_PyBytes_FromString((const char *)s)
#define __Pyx_PyByteArray_FromCString(s) \
  __Pyx_PyByteArray_FromString((const char *)s)
#define __Pyx_PyStr_FromCString(s) __Pyx_PyStr_FromString((const char *)s)
#define __Pyx_PyUnicode_FromCString(s) \
  __Pyx_PyUnicode_FromString((const char *)s)
#if PY_MAJOR_VERSION < 3
static RFC_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u) {
  const Py_UNICODE *u_end = u;
  while (*u_end++)
    ;
  return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u) \
  PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
#define __Pyx_PyBool_FromLong(b) \
  ((b) ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False))
static RFC_INLINE int __Pyx_PyObject_IsTrue(PyObject *);
static RFC_INLINE PyObject *__Pyx_PyNumber_IntOrLong(PyObject *x);
static RFC_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject *);
static RFC_INLINE PyObject *__Pyx_PyInt_FromSize_t(size_t);
#if RFC_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) \
  (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float)__pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) \
  (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) \
  (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) \
  (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
  PyObject *sys;
  PyObject *default_encoding = NULL;
  PyObject *ascii_chars_u = NULL;
  PyObject *ascii_chars_b = NULL;
  const char *default_encoding_c;
  sys = PyImport_ImportModule("sys");
  if (!sys) goto bad;
  default_encoding =
      PyObject_CallMethod(sys, (char *)"getdefaultencoding", NULL);
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
    ascii_chars_b =
        PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
    if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) ||
        memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
      PyErr_Format(PyExc_ValueError,
                   "This module compiled with c_string_encoding=ascii, but "
                   "default encoding '%.200s' is not a superset of ascii.",
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
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) \
  PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) \
  PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char *__PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
  PyObject *sys;
  PyObject *default_encoding = NULL;
  char *default_encoding_c;
  sys = PyImport_ImportModule("sys");
  if (!sys) goto bad;
  default_encoding = PyObject_CallMethod(
      sys, (char *)(const char *)"getdefaultencoding", NULL);
  Py_DECREF(sys);
  if (!default_encoding) goto bad;
  default_encoding_c = PyBytes_AsString(default_encoding);
  if (!default_encoding_c) goto bad;
  __PYX_DEFAULT_STRING_ENCODING = (char *)malloc(strlen(default_encoding_c));
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

/* Test for GCC > 2.95 */
#if defined(__GNUC__) && \
    (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
#define likely(x) (x)
#define unlikely(x) (x)
#endif /* __GNUC__ */
static RFC_INLINE void __Pyx_pretend_to_initialize(void *ptr) { (void)ptr; }

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_RFC_runtime;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char *__pyx_cfilenm = __FILE__;
static const char *__pyx_filename;

static const char *__pyx_f[] = {
    "src/rfc-py/rfc.py",
};

/*--- Type declarations ---*/

/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef RFC_REFNANNY
#define RFC_REFNANNY 0
#endif
#if RFC_REFNANNY
typedef struct {
  void (*INCREF)(void *, PyObject *, int);
  void (*DECREF)(void *, PyObject *, int);
  void (*GOTREF)(void *, PyObject *, int);
  void (*GIVEREF)(void *, PyObject *, int);
  void *(*SetupContext)(const char *, int, const char *);
  void (*FinishContext)(void **);
} __Pyx_RefNannyAPIStruct;
static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
#define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
#define __Pyx_RefNannySetupContext(name, acquire_gil)                          \
  if (acquire_gil) {                                                           \
    PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();                \
    __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
    PyGILState_Release(__pyx_gilstate_save);                                   \
  } else {                                                                     \
    __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
  }
#else
#define __Pyx_RefNannySetupContext(name, acquire_gil) \
  __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
#define __Pyx_RefNannyFinishContext() \
  __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
#define __Pyx_INCREF(r) \
  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
#define __Pyx_DECREF(r) \
  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
#define __Pyx_GOTREF(r) \
  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
#define __Pyx_GIVEREF(r) \
  __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
#define __Pyx_XINCREF(r) \
  do {                   \
    if ((r) != NULL) {   \
      __Pyx_INCREF(r);   \
    }                    \
  } while (0)
#define __Pyx_XDECREF(r) \
  do {                   \
    if ((r) != NULL) {   \
      __Pyx_DECREF(r);   \
    }                    \
  } while (0)
#define __Pyx_XGOTREF(r) \
  do {                   \
    if ((r) != NULL) {   \
      __Pyx_GOTREF(r);   \
    }                    \
  } while (0)
#define __Pyx_XGIVEREF(r) \
  do {                    \
    if ((r) != NULL) {    \
      __Pyx_GIVEREF(r);   \
    }                     \
  } while (0)
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
#define __Pyx_XDECREF_SET(r, v)    \
  do {                             \
    PyObject *tmp = (PyObject *)r; \
    r = v;                         \
    __Pyx_XDECREF(tmp);            \
  } while (0)
#define __Pyx_DECREF_SET(r, v)     \
  do {                             \
    PyObject *tmp = (PyObject *)r; \
    r = v;                         \
    __Pyx_DECREF(tmp);             \
  } while (0)
#define __Pyx_CLEAR(r)                 \
  do {                                 \
    PyObject *tmp = ((PyObject *)(r)); \
    r = NULL;                          \
    __Pyx_DECREF(tmp);                 \
  } while (0)
#define __Pyx_XCLEAR(r)                  \
  do {                                   \
    if ((r) != NULL) {                   \
      PyObject *tmp = ((PyObject *)(r)); \
      r = NULL;                          \
      __Pyx_DECREF(tmp);                 \
    }                                    \
  } while (0)

/* PyObjectGetAttrStr.proto */
#if RFC_USE_TYPE_SLOTS
static RFC_INLINE PyObject *__Pyx_PyObject_GetAttrStr(PyObject *obj,
                                                      PyObject *attr_name) {
  PyTypeObject *tp = Py_TYPE(obj);
  if (likely(tp->tp_getattro)) return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
  if (likely(tp->tp_getattr))
    return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
  return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o, n) PyObject_GetAttr(o, n)
#endif

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char *func_name, int exact,
                                       Py_ssize_t num_min, Py_ssize_t num_max,
                                       Py_ssize_t num_found);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char *func_name,
                                           PyObject *kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],
                                       PyObject *kwds2, PyObject *values[],
                                       Py_ssize_t num_pos_args,
                                       const char *function_name);

/* PyObjectFormatSimple.proto */
#if RFC_COMPILING_IN_PYPY
#define __Pyx_PyObject_FormatSimple(s, f) \
  (likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) : PyObject_Format(s, f))
#elif PY_MAJOR_VERSION < 3
#define __Pyx_PyObject_FormatSimple(s, f)                     \
  (likely(PyUnicode_CheckExact(s))                            \
       ? (Py_INCREF(s), s)                                    \
       : likely(PyString_CheckExact(s))                       \
             ? PyUnicode_FromEncodedObject(s, NULL, "strict") \
             : PyObject_Format(s, f))
#elif RFC_USE_TYPE_SLOTS
#define __Pyx_PyObject_FormatSimple(s, f)                             \
  (likely(PyUnicode_CheckExact(s))                                    \
       ? (Py_INCREF(s), s)                                            \
       : likely(PyLong_CheckExact(s))                                 \
             ? PyLong_Type.tp_str(s)                                  \
             : likely(PyFloat_CheckExact(s)) ? PyFloat_Type.tp_str(s) \
                                             : PyObject_Format(s, f))
#else
#define __Pyx_PyObject_FormatSimple(s, f) \
  (likely(PyUnicode_CheckExact(s)) ? (Py_INCREF(s), s) : PyObject_Format(s, f))
#endif

/* IncludeStringH.proto */
#include <string.h>

/* JoinPyUnicode.proto */
static PyObject *__Pyx_PyUnicode_Join(PyObject *value_tuple,
                                      Py_ssize_t value_count,
                                      Py_ssize_t result_ulength,
                                      Py_UCS4 max_char);

/* PyObjectCall.proto */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_Call(PyObject *func, PyObject *arg,
                                                PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyFunctionFastCall.proto */
#if RFC_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs) \
  __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args,
                                               int nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) \
  _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#endif

/* PyCFunctionFastCall.proto */
#if RFC_FAST_PYCCALL
static RFC_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func,
                                                       PyObject **args,
                                                       Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs) (assert(0), NULL)
#endif

/* PyObjectSetAttrStr.proto */
#if RFC_USE_TYPE_SLOTS
#define __Pyx_PyObject_DelAttrStr(o, n) __Pyx_PyObject_SetAttrStr(o, n, NULL)
static RFC_INLINE int __Pyx_PyObject_SetAttrStr(PyObject *obj,
                                                PyObject *attr_name,
                                                PyObject *value) {
  PyTypeObject *tp = Py_TYPE(obj);
  if (likely(tp->tp_setattro)) return tp->tp_setattro(obj, attr_name, value);
#if PY_MAJOR_VERSION < 3
  if (likely(tp->tp_setattr))
    return tp->tp_setattr(obj, PyString_AS_STRING(attr_name), value);
#endif
  return PyObject_SetAttr(obj, attr_name, value);
}
#else
#define __Pyx_PyObject_DelAttrStr(o, n) PyObject_DelAttr(o, n)
#define __Pyx_PyObject_SetAttrStr(o, n, v) PyObject_SetAttr(o, n, v)
#endif

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list,           \
                         wraparound, boundscheck)                              \
  (__Pyx_fits_Py_ssize_t(i, type, is_signed)                                   \
       ? __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound,          \
                               boundscheck)                                    \
       : (is_list                                                              \
              ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), \
                 (PyObject *)NULL)                                             \
              : __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list,      \
                              wraparound, boundscheck)                         \
  (__Pyx_fits_Py_ssize_t(i, type, is_signed)                                   \
       ? __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) \
       : (PyErr_SetString(PyExc_IndexError, "list index out of range"),        \
          (PyObject *)NULL))
static RFC_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o,
                                                       Py_ssize_t i,
                                                       int wraparound,
                                                       int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, \
                               wraparound, boundscheck)                    \
  (__Pyx_fits_Py_ssize_t(i, type, is_signed)                               \
       ? __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound,         \
                                     boundscheck)                          \
       : (PyErr_SetString(PyExc_IndexError, "tuple index out of range"),   \
          (PyObject *)NULL))
static RFC_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o,
                                                        Py_ssize_t i,
                                                        int wraparound,
                                                        int boundscheck);
static RFC_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject *j);
static RFC_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                  int is_list, int wraparound,
                                                  int boundscheck);

/* SetItemInt.proto */
#define __Pyx_SetItemInt(o, i, v, type, is_signed, to_py_func, is_list,     \
                         wraparound, boundscheck)                           \
  (__Pyx_fits_Py_ssize_t(i, type, is_signed)                                \
       ? __Pyx_SetItemInt_Fast(o, (Py_ssize_t)i, v, is_list, wraparound,    \
                               boundscheck)                                 \
       : (is_list ? (PyErr_SetString(PyExc_IndexError,                      \
                                     "list assignment index out of range"), \
                     -1)                                                    \
                  : __Pyx_SetItemInt_Generic(o, to_py_func(i), v)))
static RFC_INLINE int __Pyx_SetItemInt_Generic(PyObject *o, PyObject *j,
                                               PyObject *v);
static RFC_INLINE int __Pyx_SetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                            PyObject *v, int is_list,
                                            int wraparound, int boundscheck);

/* PySequenceContains.proto */
static RFC_INLINE int __Pyx_PySequence_ContainsTF(PyObject *item, PyObject *seq,
                                                  int eq) {
  int result = PySequence_Contains(seq, item);
  return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

/* BytesEquals.proto */
static RFC_INLINE int __Pyx_PyBytes_Equals(PyObject *s1, PyObject *s2,
                                           int equals);

/* UnicodeEquals.proto */
static RFC_INLINE int __Pyx_PyUnicode_Equals(PyObject *s1, PyObject *s2,
                                             int equals);

/* GetModuleGlobalName.proto */
static RFC_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

/* PyObjectCallMethO.proto */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_CallMethO(PyObject *func,
                                                     PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static RFC_INLINE PyObject *__Pyx_PyObject_CallOneArg(PyObject *func,
                                                      PyObject *arg);

/* PyObjectCallNoArg.proto */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) \
  __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* PyIntBinop.proto */
#if !RFC_COMPILING_IN_PYPY
static PyObject *__Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval,
                                     int inplace);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace) \
  (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* SliceObject.proto */
static RFC_INLINE PyObject *__Pyx_PyObject_GetSlice(
    PyObject *obj, Py_ssize_t cstart, Py_ssize_t cstop, PyObject **py_start,
    PyObject **py_stop, PyObject **py_slice, int has_cstart, int has_cstop,
    int wraparound);

/* PyThreadStateGet.proto */
#if RFC_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign __pyx_tstate = PyThreadState_GET();
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#endif

/* PyErrFetchRestore.proto */
#if RFC_FAST_THREAD_STATE
#define __Pyx_ErrRestoreWithState(type, value, tb) \
  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb) \
  __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb) \
  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb) \
  __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static RFC_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate,
                                               PyObject *type, PyObject *value,
                                               PyObject *tb);
static RFC_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate,
                                             PyObject **type, PyObject **value,
                                             PyObject **tb);
#else
#define __Pyx_ErrRestoreWithState(type, value, tb) \
  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb) PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb) PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb) PyErr_Fetch(type, value, tb)
#endif

/* RaiseException.proto */
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        PyObject *cause);

/* ListCompAppend.proto */
#if RFC_USE_PYLIST_INTERNALS && RFC_ASSUME_SAFE_MACROS
static RFC_INLINE int __Pyx_ListComp_Append(PyObject *list, PyObject *x) {
  PyListObject *L = (PyListObject *)list;
  Py_ssize_t len = Py_SIZE(list);
  if (likely(L->allocated > len)) {
    Py_INCREF(x);
    PyList_SET_ITEM(list, len, x);
    Py_SIZE(list) = len + 1;
    return 0;
  }
  return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L, x) PyList_Append(L, x)
#endif

/* PyObjectLookupSpecial.proto */
#if RFC_USE_PYTYPE_LOOKUP && RFC_USE_TYPE_SLOTS
static RFC_INLINE PyObject *__Pyx_PyObject_LookupSpecial(PyObject *obj,
                                                         PyObject *attr_name) {
  PyObject *res;
  PyTypeObject *tp = Py_TYPE(obj);
#if PY_MAJOR_VERSION < 3
  if (unlikely(PyInstance_Check(obj)))
    return __Pyx_PyObject_GetAttrStr(obj, attr_name);
#endif
  res = _PyType_Lookup(tp, attr_name);
  if (likely(res)) {
    descrgetfunc f = Py_TYPE(res)->tp_descr_get;
    if (!f) {
      Py_INCREF(res);
    } else {
      res = f(res, obj, (PyObject *)tp);
    }
  } else {
    PyErr_SetObject(PyExc_AttributeError, attr_name);
  }
  return res;
}
#else
#define __Pyx_PyObject_LookupSpecial(o, n) __Pyx_PyObject_GetAttrStr(o, n)
#endif

/* SaveResetException.proto */
#if RFC_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb) \
  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static RFC_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate,
                                            PyObject **type, PyObject **value,
                                            PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb) \
  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static RFC_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate,
                                             PyObject *type, PyObject *value,
                                             PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb) PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb) PyErr_SetExcInfo(type, value, tb)
#endif

/* GetException.proto */
#if RFC_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb) \
  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type,
                               PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* None.proto */
static RFC_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname);

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject *__Pyx_ImportFrom(PyObject *module, PyObject *name);

/* CalculateMetaclass.proto */
static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass,
                                          PyObject *bases);

/* FetchCommonType.proto */
static PyTypeObject *__Pyx_FetchCommonType(PyTypeObject *type);

/* RFCFunction.proto */
#define __Pyx_CyFunction_USED 1
#include <structmember.h>
#define __Pyx_CYFUNCTION_STATICMETHOD 0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD 0x02
#define __Pyx_CYFUNCTION_CCLASS 0x04
#define __Pyx_CyFunction_GetClosure(f) \
  (((__pyx_CyFunctionObject *)(f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f) \
  (((__pyx_CyFunctionObject *)(f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f) \
  ((type *)(((__pyx_CyFunctionObject *)(f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g) \
  ((__pyx_CyFunctionObject *)(f))->defaults_getter = (g)
typedef struct {
  PyCFunctionObject func;
#if PY_VERSION_HEX < 0x030500A0
  PyObject *func_weakreflist;
#endif
  PyObject *func_dict;
  PyObject *func_name;
  PyObject *func_qualname;
  PyObject *func_doc;
  PyObject *func_globals;
  PyObject *func_code;
  PyObject *func_closure;
  PyObject *func_classobj;
  void *defaults;
  int defaults_pyobjects;
  int flags;
  PyObject *defaults_tuple;
  PyObject *defaults_kwdict;
  PyObject *(*defaults_getter)(PyObject *);
  PyObject *func_annotations;
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_NewEx(ml, flags, qualname, self, module, globals, \
                               code)                                       \
  __Pyx_CyFunction_New(__pyx_CyFunctionType, ml, flags, qualname, self,    \
                       module, globals, code)
static PyObject *__Pyx_CyFunction_New(PyTypeObject *, PyMethodDef *ml,
                                      int flags, PyObject *qualname,
                                      PyObject *self, PyObject *module,
                                      PyObject *globals, PyObject *code);
static RFC_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m, size_t size,
                                                      int pyobjects);
static RFC_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                         PyObject *tuple);
static RFC_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *m,
                                                          PyObject *dict);
static RFC_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *m,
                                                           PyObject *dict);
static int __pyx_CyFunction_init(void);

/* Py3ClassCreate.proto */
static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases,
                                           PyObject *name, PyObject *qualname,
                                           PyObject *mkw, PyObject *modname,
                                           PyObject *doc);
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name,
                                      PyObject *bases, PyObject *dict,
                                      PyObject *mkw, int calculate_metaclass,
                                      int allow_py2_metaclass);

/* PyIntBinop.proto */
#if !RFC_COMPILING_IN_PYPY
static PyObject *__Pyx_PyInt_EqObjC(PyObject *op1, PyObject *op2, long intval,
                                    int inplace);
#else
#define __Pyx_PyInt_EqObjC(op1, op2, intval, inplace) \
  PyObject_RichCompare(op1, op2, Py_EQ)
#endif

/* CLineInTraceback.proto */
static int __Pyx_CLineForTraceback(int c_line);

/* CodeObjectCache.proto */
typedef struct {
  PyCodeObject *code_object;
  int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
  int count;
  int max_count;
  __Pyx_CodeObjectCacheEntry *entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0, 0, NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry *entries,
                                     int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject *code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line, int py_line,
                               const char *filename);

/* CIntToPy.proto */
static RFC_INLINE PyObject *__Pyx_PyInt_From_long(long value);

/* CIntFromPy.proto */
static RFC_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntFromPy.proto */
static RFC_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);

/* Module declarations from 'rfc' */
#define __Pyx_MODULE_NAME "rfc"
int __pyx_module_is_main_rfc = 0;

/* Implementation of 'rfc' */
static PyObject *__pyx_builtin_open;
static PyObject *__pyx_builtin_super;
static const char __pyx_k_[] = "`";
static const char __pyx_k_B[] = "-B";
static const char __pyx_k_f[] = "f";
static const char __pyx_k_i[] = "i";
static const char __pyx_k_o[] = "-o";
static const char __pyx_k_t[] = "t";
static const char __pyx_k_w[] = "w";
static const char __pyx_k_IF[] = "IF";
static const char __pyx_k__2[] = "";
static const char __pyx_k__3[] = "#";
static const char __pyx_k__4[] = "@";
static const char __pyx_k__6[] = "[";
static const char __pyx_k__7[] = "]";
static const char __pyx_k__8[] = ";";
static const char __pyx_k_cg[] = "cg";
static const char __pyx_k_fn[] = "fn";
static const char __pyx_k_or[] = " or ";
static const char __pyx_k_os[] = "os";
static const char __pyx_k_py[] = "py";
static const char __pyx_k_rf[] = "rf";
static const char __pyx_k_DEF[] = "DEF";
static const char __pyx_k__10[] = "{";
static const char __pyx_k__12[] = "}";
static const char __pyx_k__14[] = " ";
static const char __pyx_k__15[] = ":";
static const char __pyx_k__22[] = ", ";
static const char __pyx_k__23[] = "=";
static const char __pyx_k__24[] = " = ";
static const char __pyx_k__26[] = "\"";
static const char __pyx_k__27[] = ")";
static const char __pyx_k__28[] = "&&";
static const char __pyx_k__30[] = "||";
static const char __pyx_k__32[] = "!";
static const char __pyx_k__34[] = "  ";
static const char __pyx_k__35[] = "\n";
static const char __pyx_k__36[] = "_";
static const char __pyx_k__81[] = "/";
static const char __pyx_k_and[] = " and ";
static const char __pyx_k_def[] = "def ";
static const char __pyx_k_doc[] = "__doc__";
static const char __pyx_k_exe[] = ".exe";
static const char __pyx_k_gen[] = "gen";
static const char __pyx_k_len[] = "__len__";
static const char __pyx_k_lex[] = "lex";
static const char __pyx_k_msg[] = "msg";
static const char __pyx_k_not[] = " not ";
static const char __pyx_k_o_2[] = "o";
static const char __pyx_k_res[] = "res";
static const char __pyx_k_rfc[] = "rfc";
static const char __pyx_k_run[] = "run";
static const char __pyx_k_tok[] = "tok";
static const char __pyx_k_use[] = "use";
static const char __pyx_k_ELSE[] = "ELSE";
static const char __pyx_k_Lark[] = "Lark";
static const char __pyx_k_NAME[] = "NAME";
static const char __pyx_k_PIPE[] = "PIPE";
static const char __pyx_k_TYPE[] = "TYPE";
static const char __pyx_k_True[] = "True";
static const char __pyx_k_args[] = "args";
static const char __pyx_k_code[] = "code";
static const char __pyx_k_elif[] = "elif ";
static const char __pyx_k_else[] = "else ";
static const char __pyx_k_exit[] = "__exit__";
static const char __pyx_k_file[] = "file";
static const char __pyx_k_glob[] = "glob";
static const char __pyx_k_help[] = "help";
static const char __pyx_k_init[] = "__init__";
static const char __pyx_k_lalr[] = "lalr";
static const char __pyx_k_lark[] = "lark";
static const char __pyx_k_last[] = "last";
static const char __pyx_k_line[] = "line";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_move[] = "move";
static const char __pyx_k_name[] = "name";
static const char __pyx_k_open[] = "open";
static const char __pyx_k_or_2[] = "or";
static const char __pyx_k_pass[] = "pass";
static const char __pyx_k_path[] = "path";
static const char __pyx_k_py_2[] = ".py";
static const char __pyx_k_read[] = "read";
static const char __pyx_k_rf_2[] = ".rf";
static const char __pyx_k_rf_3[] = "/**/*.rf";
static const char __pyx_k_self[] = "self";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_toks[] = "toks";
static const char __pyx_k_true[] = "true";
static const char __pyx_k_type[] = "type";
static const char __pyx_k_Alias[] = "Alias";
static const char __pyx_k_False[] = "False";
static const char __pyx_k_Token[] = "Token";
static const char __pyx_k_a_out[] = "a.out";
static const char __pyx_k_alias[] = "alias";
static const char __pyx_k_and_2[] = "and";
static const char __pyx_k_class[] = "class";
static const char __pyx_k_def_2[] = "def";
static const char __pyx_k_enter[] = "__enter__";
static const char __pyx_k_false[] = "false";
static const char __pyx_k_input[] = "input";
static const char __pyx_k_isdir[] = "isdir";
static const char __pyx_k_not_2[] = "not";
static const char __pyx_k_parse[] = "parse";
static const char __pyx_k_start[] = "start";
static const char __pyx_k_strip[] = "strip";
static const char __pyx_k_suite[] = "suite";
static const char __pyx_k_super[] = "super";
static const char __pyx_k_types[] = "types";
static const char __pyx_k_upper[] = "upper";
static const char __pyx_k_value[] = "value";
static const char __pyx_k_write[] = "write";
static const char __pyx_k_DEDENT[] = "DEDENT";
static const char __pyx_k_INDENT[] = "INDENT";
static const char __pyx_k_Parser[] = "Parser";
static const char __pyx_k_column[] = "column";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_module[] = "__module__";
static const char __pyx_k_name_2[] = "__name__";
static const char __pyx_k_nuitka[] = "nuitka";
static const char __pyx_k_output[] = "output";
static const char __pyx_k_parsed[] = "parsed";
static const char __pyx_k_parser[] = "parser";
static const char __pyx_k_r_type[] = "r#type";
static const char __pyx_k_remove[] = "remove";
static const char __pyx_k_rmtree[] = "rmtree";
static const char __pyx_k_shutil[] = "shutil";
static const char __pyx_k_stderr[] = "stderr";
static const char __pyx_k_struct[] = "struct";
static const char __pyx_k_tmpdir[] = "tmpdir";
static const char __pyx_k_Codegen[] = "Codegen";
static const char __pyx_k_TypeVar[] = " = TypeVar(\"";
static const char __pyx_k_aliases[] = "aliases";
static const char __pyx_k_compile[] = "compile";
static const char __pyx_k_content[] = "content";
static const char __pyx_k_grammar[] = "grammar";
static const char __pyx_k_keyword[] = "keyword";
static const char __pyx_k_metavar[] = "metavar";
static const char __pyx_k_mkdtemp[] = "mkdtemp";
static const char __pyx_k_newline[] = "newline";
static const char __pyx_k_prepare[] = "__prepare__";
static const char __pyx_k_pyfiles[] = "pyfiles";
static const char __pyx_k_python3[] = "python3";
static const char __pyx_k_argparse[] = "argparse";
static const char __pyx_k_basename[] = "basename";
static const char __pyx_k_epilogue[] = "epilogue";
static const char __pyx_k_filename[] = "filename";
static const char __pyx_k_import_2[] = "import";
static const char __pyx_k_is_alias[] = "is_alias";
static const char __pyx_k_prologue[] = "prologue";
static const char __pyx_k_qualname[] = "__qualname__";
static const char __pyx_k_splitext[] = "splitext";
static const char __pyx_k_tempfile[] = "tempfile";
static const char __pyx_k_DECORATOR[] = "DECORATOR";
static const char __pyx_k_SEMICOLON[] = "SEMICOLON";
static const char __pyx_k_decorated[] = "decorated";
static const char __pyx_k_decorator[] = "decorator";
static const char __pyx_k_main___py[] = "/__main__.py";
static const char __pyx_k_metaclass[] = "__metaclass__";
static const char __pyx_k_recursive[] = "recursive";
static const char __pyx_k_transform[] = "transform";
static const char __pyx_k_FormatCode[] = "FormatCode";
static const char __pyx_k_arg_parser[] = "arg_parser";
static const char __pyx_k_lark_lexer[] = "lark.lexer";
static const char __pyx_k_output_dir[] = "--output-dir=";
static const char __pyx_k_parse_args[] = "parse_args";
static const char __pyx_k_returncode[] = "returncode";
static const char __pyx_k_subprocess[] = "subprocess";
static const char __pyx_k_Codegen_gen[] = "Codegen.gen";
static const char __pyx_k_Output_file[] = "Output file";
static const char __pyx_k_Transformer[] = "Transformer";
static const char __pyx_k_class_suite[] = "class_suite";
static const char __pyx_k_description[] = "description";
static const char __pyx_k_nuitka_base[] = "nuitka_base";
static const char __pyx_k_nuitka_main[] = "nuitka_main";
static const char __pyx_k_recurse_all[] = "--recurse-all";
static const char __pyx_k_test_lambda[] = "test = lambda _: _\n";
static const char __pyx_k_transformer[] = "transformer";
static const char __pyx_k_Alias___init[] = "Alias.__init__";
static const char __pyx_k_Codegen_line[] = "Codegen.line";
static const char __pyx_k_Parser_start[] = "Parser.start";
static const char __pyx_k_Parser_suite[] = "Parser.suite";
static const char __pyx_k_add_argument[] = "add_argument";
static const char __pyx_k_compile_file[] = "compile_file";
static const char __pyx_k_suite_tokens[] = "suite_tokens";
static const char __pyx_k_Parser___init[] = "Parser.__init__";
static const char __pyx_k_indent_offset[] = "indent_offset";
static const char __pyx_k_ArgumentParser[] = "ArgumentParser";
static const char __pyx_k_Codegen___init[] = "Codegen.__init__";
static const char __pyx_k_Codegen_newline[] = "Codegen.newline";
static const char __pyx_k_already_visited[] = "already_visited";
static const char __pyx_k_Parser_decorator[] = "Parser.decorator";
static const char __pyx_k_decorator_tokens[] = "decorator_tokens";
static const char __pyx_k_foreign_keywords[] = "foreign_keywords";
static const char __pyx_k_Codegen_transform[] = "Codegen.transform";
static const char __pyx_k_src_rfc_py_rfc_py[] = "src/rfc-py/rfc.py";
static const char __pyx_k_Parser_class_suite[] = "Parser.class_suite";
static const char __pyx_k_cline_in_traceback[] = "cline_in_traceback";
static const char __pyx_k_from_typing_import[] = "from typing import *\n";
static const char __pyx_k_maybe_placeholders[] = "maybe_placeholders";
static const char __pyx_k_python_version_3_6[] = "--python-version=3.6";
static const char __pyx_k_propagate_positions[] = "propagate_positions";
static const char __pyx_k_yapf_yapflib_yapf_api[] = "yapf.yapflib.yapf_api";
static const char __pyx_k_ForeignKeywordException[] = "ForeignKeywordException";
static const char __pyx_k_Input_file_or_directory[] = "Input file or directory";
static const char __pyx_k_usage_of_foreign_keyword[] =
    "usage of foreign keyword: `";
static const char __pyx_k_if___name_____main___main[] =
    "\nif __name__ == \"__main__\": main()";
static const char __pyx_k_ForeignKeywordException___init[] =
    "ForeignKeywordException.__init__";
static const char __pyx_k_def_test_func_func_return_func[] =
    "def test(func): func(); return func\n";
static const char __pyx_k_The_bootstrap_compiler_for_Raft[] =
    "The bootstrap compiler for Raft.";
static const char __pyx_k_start_typedef_funcdef_decorated[] =
    "start: (typedef | funcdef | decorated | (import_stmt \";\") | classdef | "
    "async_funcdef)*\n\n!decorator: \"#\" \"[\" dotted_name [ \"(\" "
    "[arguments] \")\" ] \"]\"\ndecorators: decorator+\ndecorated: decorators "
    "(classdef | funcdef | async_funcdef)\n\ntypedef: \"type\" NAME [(\":\" "
    "typelist) | (\"=\" type)] \";\"\ntype: (dotted_name [\"[\" typelist "
    "\"]\"]) | \"None\"\ntypelist: type (\",\" type)*\n\nasync_funcdef: "
    "\"async\" funcdef\nfuncdef: \"fn\" NAME \"(\" parameters? \")\" [\"->\" "
    "type] suite\nstruct_funcdef: \"fn\" NAME \"(\" \"self\" [\",\" "
    "parameters] \")\" [\"->\" type] suite\n\nparameters: paramvalue (\",\" "
    "paramvalue)* [\",\" [ starparams | kwparams]]\n        | starparams\n     "
    "     | kwparams\nstarparams: \"*\" typedparam? (\",\" paramvalue)* [\",\" "
    "kwparams]\nkwparams: \"**\" typedparam\n\n?paramvalue: typedparam [\"=\" "
    "test]\n?typedparam: NAME \":\" type\n\nvarargslist: (vfpdef [\"=\" test] "
    "(\",\" vfpdef [\"=\" test])* [\",\" [ \"*\" [vfpdef] (\",\" vfpdef [\"=\" "
    "test])* [\",\" [\"**\" vfpdef [\",\"]]] | \"**\" vfpdef [\",\"]]]\n  | "
    "\"*\" [vfpdef] (\",\" vfpdef [\"=\" test])* [\",\" [\"**\" vfpdef "
    "[\",\"]]]\n  | \"**\" vfpdef [\",\"])\n\nvfpdef: NAME\n\n?stmt: "
    "simple_stmt | compound_stmt\n?simple_stmt: small_stmt \";\"\n?small_stmt: "
    "(expr_stmt | del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: "
    "testlist_star_expr (annassign | augassign (yield_expr|testlist)\n         "
    "| (\"=\" (yield_expr|testlist_star_expr))*)\nannassign: \":\" type \"=\" "
    "test\n?testlist_star_expr: (test|star_expr) (\",\" (test|star_expr))* "
    "[\",\"]\n!augassign: (\"+=\" | \"-=\" | \"*=\" | \"@=\" | \"/=\" | \"%=\" "
    "| \"&=\" | \"|=\" | \"^=\" | \"<<=\" | \">>=\" | \"**=\")\ndel_stmt: "
    "\"del\" exprlist\n?flow_stmt: break_stmt | continue_stmt | return_stmt | "
    "raise_stmt | yield_stmt\nbreak_stmt: \"break\"\ncontinue_stmt: "
    "\"continue\"\nreturn_stmt: \"return\" [testlist]\nyield_stmt: "
    "yield_expr\nraise_stmt: \"raise\" [test [\"from\" test]]\nimport_stmt: "
    "import_name | import_from\nimport_name: \"use"
    "\" dotted_as_names\nimport_from: \"from\" dotted_name \"use\" (\"*\" | "
    "\"(\" import_as_names \")\" | import_as_names)\nimport_as_name: NAME "
    "[\"as\" NAME]\ndotted_as_name: dotted_name [\"as\" "
    "NAME]\nimport_as_names: import_as_name (\",\" import_as_name)* "
    "[\",\"]\ndotted_as_names: dotted_as_name (\",\" "
    "dotted_as_name)*\ndotted_name: NAME (\".\" NAME)*\nassert_stmt: "
    "\"assert\" test [\",\" test]\n\ncompound_stmt: if_stmt | while_stmt | "
    "for_stmt | try_stmt | with_stmt | typedef | funcdef | classdef | "
    "decorated | async_stmt\nasync_stmt: \"async\" (funcdef | with_stmt | "
    "for_stmt)\nif_stmt: \"if\" test suite (\"else\" \"if\" test suite)* "
    "[\"else\" suite]\nwhile_stmt: \"while\" test suite [\"else\" "
    "suite]\nfor_stmt: \"for\" exprlist \"in\" testlist suite [\"else\" "
    "suite]\ntry_stmt: (\"try\" suite ((except_clause suite)+ [\"else\" suite] "
    "[\"finally\" suite] | \"finally\" suite))\nwith_stmt: \"with\" with_item "
    "(\",\" with_item)*  suite\nwith_item: test [\"as\" expr]\nexcept_clause: "
    "\"except\" [test [\"as\" NAME]]\n!suite: \"{\" stmt* \"}\"\n\n?test: "
    "or_test (\"if\" or_test \"else\" test)? | lambdef\n?test_nocond: or_test "
    "| lambdef_nocond\nlambdef: \"lambda\" [varargslist] \":\" "
    "test\nlambdef_nocond: \"lambda\" [varargslist] \":\" "
    "test_nocond\n?or_test: and_test (\"||\" and_test)*\n?and_test: not_test "
    "(\"&&\" not_test)*\n?not_test: \"!\" not_test -> not\n         | "
    "comparison\n?comparison: expr (_comp_op expr)*\nstar_expr: \"*\" "
    "expr\n?expr: xor_expr (\"|\" xor_expr)*\n?xor_expr: and_expr (\"^\" "
    "and_expr)*\n?and_expr: shift_expr (\"&\" shift_expr)*\n?shift_expr: "
    "arith_expr (_shift_op arith_expr)*\n?arith_expr: term (_add_op "
    "term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op factor | "
    "power\n\n!_factor_op: \"+\"|\"-\"|\"~\"\n!_add_op: "
    "\"+\"|\"-\"\n!_shift_op: \"<<\"|\">>\"\n!_mul_op: "
    "\"*\"|\"@\"|\"/\"|\"%\"|\"//\"\n!_comp_op: "
    "\"<\"|\">\"|\"==\"|\">=\"|\"<=\"|\"!=\"|\"in\"|\"is\"\n\n?power: "
    "await_expr (\"**\" factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "
    "\"await\"\n"
    "\n?atom_expr: atom_expr \"(\" [arguments] \")\"      -> funccall\n        "
    "  | atom_expr \"[\" subscriptlist \"]\"  -> getitem\n          | "
    "atom_expr \".\" NAME               -> getattr\n      | atom\n\n?atom: "
    "\"(\" [yield_expr|testlist_comp] \")\" -> tuple\n     | \"[\" "
    "[testlist_comp] \"]\"  -> list\n     | \"{\" [dictorsetmaker] \"}\" -> "
    "dict\n     | NAME -> var\n     | number | string+\n     | \"(\" test "
    "\")\"\n     | \"...\" -> ellipsis\n     | \"None\"    -> const_none\n     "
    "| \"true\"    -> const_true\n     | \"false\"   -> "
    "const_false\n\n?testlist_comp: (test|star_expr) [comp_for | (\",\" "
    "(test|star_expr))+ [\",\"] | \",\"]\nsubscriptlist: subscript (\",\" "
    "subscript)* [\",\"]\nsubscript: test | [test] \":\" [test] "
    "[sliceop]\nsliceop: \":\" [test]\nexprlist: (expr|star_expr) (\",\" "
    "(expr|star_expr))* [\",\"]\ntestlist: test (\",\" test)* "
    "[\",\"]\ndictorsetmaker: ( ((test \":\" test | \"**\" expr) (comp_for | "
    "(\",\" (test \":\" test | \"**\" expr))* [\",\"])) | ((test | star_expr) "
    "(comp_for | (\",\" (test | star_expr))* [\",\"])) )\n\nclassdef: "
    "\"struct\" NAME [\"(\" [arguments] \")\"] class_suite\n!class_suite: "
    "\"{\" (struct_funcdef | funcdef | decorated)* \"}\"\n\narguments: "
    "argvalue (\",\" argvalue)*  (\",\" [ starargs | kwargs])?\n         | "
    "starargs\n        | kwargs\n         | test comp_for\n\nstarargs: \"*\" "
    "test (\",\" \"*\" test)* (\",\" argvalue)* [\",\" kwargs]\nkwargs: \"**\" "
    "test\n\n?argvalue: test (\"=\" test)?\n\n\n\ncomp_iter: comp_for | "
    "comp_if | async_for\nasync_for: \"async\" \"for\" exprlist \"in\" or_test "
    "[comp_iter]\ncomp_for: \"for\" exprlist \"in\" or_test "
    "[comp_iter]\ncomp_if: \"if\" test_nocond [comp_iter]\n\nyield_expr: "
    "\"yield\" [yield_arg]\nyield_arg: \"from\" test | testlist\n\n\nnumber: "
    "DEC_NUMBER | HEX_NUMBER | BIN_NUMBER | OCT_NUMBER | FLOAT_NUMBER | "
    "IMAG_NUMBER\nstring: STRING | LONG_STRING\n\nNAME: "
    "/(r#)?[a-zA-Z_]\\w*/\nCOMMENT: /\\/\\/[^\\n]*/\n_NEWLINE: ( /\\r?\\n[\\t "
    "]*/ | COMMENT )+\n\n\nSTRING : /[ubf]?r?(\"(?!\"\").*?(?"
    "<!\\\\)(\\\\\\\\)*?\"|'(?!'').*?(?<!\\\\)(\\\\\\\\)*?')/i\nLONG_STRING: "
    "/[ubf]?r?(\"\"\".*?(?<!\\\\)(\\\\\\\\)*?\"\"\"|'''.*?(?<!\\\\)(\\\\\\\\)*?"
    "''')/is\n\nDEC_NUMBER: /0|[1-9]\\d*/i\nHEX_NUMBER.2: "
    "/0x[\\da-f]*/i\nOCT_NUMBER.2: /0o[0-7]*/i\nBIN_NUMBER.2 : "
    "/0b[0-1]*/i\nFLOAT_NUMBER.2: "
    "/((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2: "
    "/\\d+j/i | FLOAT_NUMBER \"j\"i\n\n%ignore /[\\t \\f]+/\n%ignore "
    "_NEWLINE\n";
static PyObject *__pyx_kp_u_;
static PyObject *__pyx_n_s_Alias;
static PyObject *__pyx_n_s_Alias___init;
static PyObject *__pyx_n_s_ArgumentParser;
static PyObject *__pyx_kp_u_B;
static PyObject *__pyx_n_s_Codegen;
static PyObject *__pyx_n_s_Codegen___init;
static PyObject *__pyx_n_s_Codegen_gen;
static PyObject *__pyx_n_s_Codegen_line;
static PyObject *__pyx_n_s_Codegen_newline;
static PyObject *__pyx_n_s_Codegen_transform;
static PyObject *__pyx_n_u_DECORATOR;
static PyObject *__pyx_n_u_DEDENT;
static PyObject *__pyx_n_u_DEF;
static PyObject *__pyx_n_u_ELSE;
static PyObject *__pyx_n_u_False;
static PyObject *__pyx_n_s_ForeignKeywordException;
static PyObject *__pyx_n_s_ForeignKeywordException___init;
static PyObject *__pyx_n_s_FormatCode;
static PyObject *__pyx_n_u_IF;
static PyObject *__pyx_n_u_INDENT;
static PyObject *__pyx_kp_u_Input_file_or_directory;
static PyObject *__pyx_n_s_Lark;
static PyObject *__pyx_n_u_NAME;
static PyObject *__pyx_kp_u_Output_file;
static PyObject *__pyx_n_s_PIPE;
static PyObject *__pyx_n_s_Parser;
static PyObject *__pyx_n_s_Parser___init;
static PyObject *__pyx_n_s_Parser_class_suite;
static PyObject *__pyx_n_s_Parser_decorator;
static PyObject *__pyx_n_s_Parser_start;
static PyObject *__pyx_n_s_Parser_suite;
static PyObject *__pyx_n_u_SEMICOLON;
static PyObject *__pyx_n_u_TYPE;
static PyObject *__pyx_kp_u_The_bootstrap_compiler_for_Raft;
static PyObject *__pyx_n_s_Token;
static PyObject *__pyx_n_s_Transformer;
static PyObject *__pyx_n_u_True;
static PyObject *__pyx_kp_u_TypeVar;
static PyObject *__pyx_kp_u__10;
static PyObject *__pyx_kp_u__12;
static PyObject *__pyx_kp_u__14;
static PyObject *__pyx_kp_u__15;
static PyObject *__pyx_kp_u__2;
static PyObject *__pyx_kp_u__22;
static PyObject *__pyx_kp_u__23;
static PyObject *__pyx_kp_u__24;
static PyObject *__pyx_kp_u__26;
static PyObject *__pyx_kp_u__27;
static PyObject *__pyx_kp_u__28;
static PyObject *__pyx_kp_u__3;
static PyObject *__pyx_kp_u__30;
static PyObject *__pyx_kp_u__32;
static PyObject *__pyx_kp_u__34;
static PyObject *__pyx_kp_u__35;
static PyObject *__pyx_n_s__36;
static PyObject *__pyx_kp_u__4;
static PyObject *__pyx_kp_u__6;
static PyObject *__pyx_kp_u__7;
static PyObject *__pyx_kp_u__8;
static PyObject *__pyx_kp_u__81;
static PyObject *__pyx_kp_u_a_out;
static PyObject *__pyx_n_s_add_argument;
static PyObject *__pyx_n_s_alias;
static PyObject *__pyx_n_s_aliases;
static PyObject *__pyx_n_s_already_visited;
static PyObject *__pyx_kp_u_and;
static PyObject *__pyx_n_u_and_2;
static PyObject *__pyx_n_s_arg_parser;
static PyObject *__pyx_n_s_argparse;
static PyObject *__pyx_n_s_args;
static PyObject *__pyx_n_s_basename;
static PyObject *__pyx_n_s_cg;
static PyObject *__pyx_n_u_class;
static PyObject *__pyx_n_s_class_suite;
static PyObject *__pyx_n_s_cline_in_traceback;
static PyObject *__pyx_n_s_code;
static PyObject *__pyx_n_s_column;
static PyObject *__pyx_n_s_compile;
static PyObject *__pyx_n_s_compile_file;
static PyObject *__pyx_n_s_content;
static PyObject *__pyx_n_u_decorated;
static PyObject *__pyx_n_s_decorator;
static PyObject *__pyx_n_s_decorator_tokens;
static PyObject *__pyx_kp_u_def;
static PyObject *__pyx_n_u_def_2;
static PyObject *__pyx_kp_u_def_test_func_func_return_func;
static PyObject *__pyx_n_s_description;
static PyObject *__pyx_n_s_doc;
static PyObject *__pyx_kp_u_elif;
static PyObject *__pyx_kp_u_else;
static PyObject *__pyx_n_s_enter;
static PyObject *__pyx_n_s_epilogue;
static PyObject *__pyx_kp_u_exe;
static PyObject *__pyx_n_s_exit;
static PyObject *__pyx_n_s_f;
static PyObject *__pyx_n_u_false;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_n_s_filename;
static PyObject *__pyx_n_u_fn;
static PyObject *__pyx_n_s_foreign_keywords;
static PyObject *__pyx_kp_u_from_typing_import;
static PyObject *__pyx_n_s_gen;
static PyObject *__pyx_n_s_glob;
static PyObject *__pyx_n_s_grammar;
static PyObject *__pyx_n_s_help;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_kp_u_if___name_____main___main;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_u_import_2;
static PyObject *__pyx_n_s_indent_offset;
static PyObject *__pyx_n_s_init;
static PyObject *__pyx_n_s_input;
static PyObject *__pyx_n_u_input;
static PyObject *__pyx_n_s_is_alias;
static PyObject *__pyx_n_s_isdir;
static PyObject *__pyx_n_s_keyword;
static PyObject *__pyx_n_u_lalr;
static PyObject *__pyx_n_s_lark;
static PyObject *__pyx_n_s_lark_lexer;
static PyObject *__pyx_n_s_last;
static PyObject *__pyx_n_s_len;
static PyObject *__pyx_n_s_lex;
static PyObject *__pyx_n_s_line;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_u_main;
static PyObject *__pyx_kp_u_main___py;
static PyObject *__pyx_n_s_maybe_placeholders;
static PyObject *__pyx_n_s_metaclass;
static PyObject *__pyx_n_s_metavar;
static PyObject *__pyx_n_s_mkdtemp;
static PyObject *__pyx_n_s_module;
static PyObject *__pyx_n_s_move;
static PyObject *__pyx_n_s_msg;
static PyObject *__pyx_n_s_name;
static PyObject *__pyx_n_s_name_2;
static PyObject *__pyx_n_s_newline;
static PyObject *__pyx_kp_u_not;
static PyObject *__pyx_n_u_not_2;
static PyObject *__pyx_n_u_nuitka;
static PyObject *__pyx_n_s_nuitka_base;
static PyObject *__pyx_n_s_nuitka_main;
static PyObject *__pyx_kp_u_o;
static PyObject *__pyx_n_s_o_2;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_kp_u_or;
static PyObject *__pyx_n_u_or_2;
static PyObject *__pyx_n_s_os;
static PyObject *__pyx_n_s_output;
static PyObject *__pyx_n_u_output;
static PyObject *__pyx_kp_u_output_dir;
static PyObject *__pyx_n_s_parse;
static PyObject *__pyx_n_s_parse_args;
static PyObject *__pyx_n_s_parsed;
static PyObject *__pyx_n_s_parser;
static PyObject *__pyx_n_u_pass;
static PyObject *__pyx_n_s_path;
static PyObject *__pyx_n_s_prepare;
static PyObject *__pyx_n_s_prologue;
static PyObject *__pyx_n_s_propagate_positions;
static PyObject *__pyx_n_s_py;
static PyObject *__pyx_kp_u_py_2;
static PyObject *__pyx_n_s_pyfiles;
static PyObject *__pyx_n_u_python3;
static PyObject *__pyx_kp_u_python_version_3_6;
static PyObject *__pyx_n_s_qualname;
static PyObject *__pyx_kp_u_r_type;
static PyObject *__pyx_n_s_read;
static PyObject *__pyx_kp_u_recurse_all;
static PyObject *__pyx_n_s_recursive;
static PyObject *__pyx_n_s_remove;
static PyObject *__pyx_n_s_res;
static PyObject *__pyx_n_s_returncode;
static PyObject *__pyx_n_s_rf;
static PyObject *__pyx_kp_u_rf_2;
static PyObject *__pyx_kp_u_rf_3;
static PyObject *__pyx_n_s_rfc;
static PyObject *__pyx_n_s_rmtree;
static PyObject *__pyx_n_s_run;
static PyObject *__pyx_n_s_self;
static PyObject *__pyx_n_s_shutil;
static PyObject *__pyx_n_s_splitext;
static PyObject *__pyx_kp_s_src_rfc_py_rfc_py;
static PyObject *__pyx_n_s_start;
static PyObject *__pyx_kp_u_start_typedef_funcdef_decorated;
static PyObject *__pyx_n_s_stderr;
static PyObject *__pyx_n_s_strip;
static PyObject *__pyx_n_u_struct;
static PyObject *__pyx_n_s_subprocess;
static PyObject *__pyx_n_s_suite;
static PyObject *__pyx_n_u_suite;
static PyObject *__pyx_n_s_suite_tokens;
static PyObject *__pyx_n_s_super;
static PyObject *__pyx_n_s_t;
static PyObject *__pyx_n_s_tempfile;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_kp_u_test_lambda;
static PyObject *__pyx_n_s_tmpdir;
static PyObject *__pyx_n_s_tok;
static PyObject *__pyx_n_s_toks;
static PyObject *__pyx_n_s_transform;
static PyObject *__pyx_n_s_transformer;
static PyObject *__pyx_n_u_true;
static PyObject *__pyx_n_s_type;
static PyObject *__pyx_n_u_type;
static PyObject *__pyx_n_s_types;
static PyObject *__pyx_n_s_upper;
static PyObject *__pyx_kp_u_usage_of_foreign_keyword;
static PyObject *__pyx_n_u_use;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_u_w;
static PyObject *__pyx_n_s_write;
static PyObject *__pyx_n_s_yapf_yapflib_yapf_api;
static PyObject *__pyx_pf_3rfc_23ForeignKeywordException___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_keyword); /* proto */
static PyObject *__pyx_pf_3rfc_5Alias___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_rf, PyObject *__pyx_v_py); /* proto */
static PyObject *__pyx_pf_3rfc_7Codegen___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_toks, PyObject *__pyx_v_parsed); /* proto */
static PyObject *__pyx_pf_3rfc_7Codegen_2newline(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_indent_offset, PyObject *__pyx_v_content); /* proto */
static PyObject *__pyx_pf_3rfc_7Codegen_4line(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_code); /* proto */
static PyObject *__pyx_pf_3rfc_7Codegen_6transform(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_toks, PyObject *__pyx_v_parsed); /* proto */
static PyObject *__pyx_pf_3rfc_7Codegen_8gen(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3rfc_gen(RFC_UNUSED PyObject *__pyx_self,
                                   PyObject *__pyx_v_toks,
                                   PyObject *__pyx_v_parsed); /* proto */
static PyObject *__pyx_pf_3rfc_6Parser___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_3rfc_6Parser_2start(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    RFC_UNUSED PyObject *__pyx_v__); /* proto */
static PyObject *__pyx_pf_3rfc_6Parser_4decorator(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v__); /* proto */
static PyObject *__pyx_pf_3rfc_6Parser_6suite(RFC_UNUSED PyObject *__pyx_self,
                                              PyObject *__pyx_v_self,
                                              PyObject *__pyx_v__); /* proto */
static PyObject *__pyx_pf_3rfc_6Parser_8class_suite(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v__); /* proto */
static PyObject *__pyx_pf_3rfc_2compile(RFC_UNUSED PyObject *__pyx_self,
                                        PyObject *__pyx_v_code); /* proto */
static PyObject *__pyx_pf_3rfc_4compile_file(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_filename); /* proto */
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_neg_1;
static PyObject *__pyx_int_neg_3;
static PyObject *__pyx_tuple__5;
static PyObject *__pyx_tuple__9;
static PyObject *__pyx_slice__25;
static PyObject *__pyx_slice__38;
static PyObject *__pyx_slice__39;
static PyObject *__pyx_slice__78;
static PyObject *__pyx_tuple__11;
static PyObject *__pyx_tuple__13;
static PyObject *__pyx_tuple__16;
static PyObject *__pyx_tuple__17;
static PyObject *__pyx_tuple__18;
static PyObject *__pyx_tuple__19;
static PyObject *__pyx_tuple__20;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__29;
static PyObject *__pyx_tuple__31;
static PyObject *__pyx_tuple__33;
static PyObject *__pyx_tuple__37;
static PyObject *__pyx_tuple__40;
static PyObject *__pyx_tuple__42;
static PyObject *__pyx_tuple__44;
static PyObject *__pyx_tuple__45;
static PyObject *__pyx_tuple__46;
static PyObject *__pyx_tuple__47;
static PyObject *__pyx_tuple__48;
static PyObject *__pyx_tuple__49;
static PyObject *__pyx_tuple__51;
static PyObject *__pyx_tuple__53;
static PyObject *__pyx_tuple__54;
static PyObject *__pyx_tuple__56;
static PyObject *__pyx_tuple__58;
static PyObject *__pyx_tuple__60;
static PyObject *__pyx_tuple__62;
static PyObject *__pyx_tuple__64;
static PyObject *__pyx_tuple__66;
static PyObject *__pyx_tuple__68;
static PyObject *__pyx_tuple__70;
static PyObject *__pyx_tuple__72;
static PyObject *__pyx_tuple__74;
static PyObject *__pyx_tuple__76;
static PyObject *__pyx_tuple__77;
static PyObject *__pyx_tuple__79;
static PyObject *__pyx_tuple__80;
static PyObject *__pyx_codeobj__41;
static PyObject *__pyx_codeobj__43;
static PyObject *__pyx_codeobj__50;
static PyObject *__pyx_codeobj__52;
static PyObject *__pyx_codeobj__55;
static PyObject *__pyx_codeobj__57;
static PyObject *__pyx_codeobj__59;
static PyObject *__pyx_codeobj__61;
static PyObject *__pyx_codeobj__63;
static PyObject *__pyx_codeobj__65;
static PyObject *__pyx_codeobj__67;
static PyObject *__pyx_codeobj__69;
static PyObject *__pyx_codeobj__71;
static PyObject *__pyx_codeobj__73;
static PyObject *__pyx_codeobj__75;

/* "rfc.py":13
 *
 * class ForeignKeywordException(Exception):
 *     def __init__(self, keyword):             # <<<<<<<<<<<<<<
 *         msg = f'usage of foreign keyword: `{keyword}`'
 *         super(Exception, self).__init__(self, msg)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_23ForeignKeywordException_1__init__(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_23ForeignKeywordException_1__init__ = {
    "__init__", (PyCFunction)__pyx_pw_3rfc_23ForeignKeywordException_1__init__,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_23ForeignKeywordException_1__init__(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_keyword = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("__init__ (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s_keyword,
                                            0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] =
                          PyDict_GetItem(__pyx_kwds, __pyx_n_s_keyword)) != 0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, 1);
            __PYX_ERR(0, 13, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "__init__") < 0))
          __PYX_ERR(0, 13, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_keyword = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 13, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.ForeignKeywordException.__init__", __pyx_clineno,
                     __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_23ForeignKeywordException___init__(
      __pyx_self, __pyx_v_self, __pyx_v_keyword);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_23ForeignKeywordException___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_keyword) {
  PyObject *__pyx_v_msg = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  Py_UCS4 __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "rfc.py":14
   * class ForeignKeywordException(Exception):
   *     def __init__(self, keyword):
   *         msg = f'usage of foreign keyword: `{keyword}`'             #
   * <<<<<<<<<<<<<< super(Exception, self).__init__(self, msg)
   *
   */
  __pyx_t_1 = PyTuple_New(3);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = 0;
  __pyx_t_3 = 127;
  __Pyx_INCREF(__pyx_kp_u_usage_of_foreign_keyword);
  __pyx_t_2 += 27;
  __Pyx_GIVEREF(__pyx_kp_u_usage_of_foreign_keyword);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_kp_u_usage_of_foreign_keyword);
  __pyx_t_4 = __Pyx_PyObject_FormatSimple(__pyx_v_keyword, __pyx_empty_unicode);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_4) > __pyx_t_3)
                  ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_4)
                  : __pyx_t_3;
  __pyx_t_2 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_4);
  __pyx_t_4 = 0;
  __Pyx_INCREF(__pyx_kp_u_);
  __pyx_t_2 += 1;
  __Pyx_GIVEREF(__pyx_kp_u_);
  PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_kp_u_);
  __pyx_t_4 = __Pyx_PyUnicode_Join(__pyx_t_1, 3, __pyx_t_2, __pyx_t_3);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_v_msg = ((PyObject *)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "rfc.py":15
   *     def __init__(self, keyword):
   *         msg = f'usage of foreign keyword: `{keyword}`'
   *         super(Exception, self).__init__(self, msg)             #
   * <<<<<<<<<<<<<<
   *
   *
   */
  __pyx_t_1 = PyTuple_New(2);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  __Pyx_GIVEREF(((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  PyTuple_SET_ITEM(__pyx_t_1, 0,
                   ((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  __Pyx_INCREF(__pyx_v_self);
  __Pyx_GIVEREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_self);
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_builtin_super, __pyx_t_1, NULL);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_init);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  __pyx_t_6 = 0;
  if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_5)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
      __pyx_t_6 = 1;
    }
  }
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_v_self, __pyx_v_msg};
    __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp + 1 - __pyx_t_6,
                                          2 + __pyx_t_6);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_v_self, __pyx_v_msg};
    __pyx_t_4 = __Pyx_PyCFunction_FastCall(
        __pyx_t_1, __pyx_temp + 1 - __pyx_t_6, 2 + __pyx_t_6);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
#endif
  {
    __pyx_t_7 = PyTuple_New(2 + __pyx_t_6);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (__pyx_t_5) {
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5);
      __pyx_t_5 = NULL;
    }
    __Pyx_INCREF(__pyx_v_self);
    __Pyx_GIVEREF(__pyx_v_self);
    PyTuple_SET_ITEM(__pyx_t_7, 0 + __pyx_t_6, __pyx_v_self);
    __Pyx_INCREF(__pyx_v_msg);
    __Pyx_GIVEREF(__pyx_v_msg);
    PyTuple_SET_ITEM(__pyx_t_7, 1 + __pyx_t_6, __pyx_v_msg);
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_7, NULL);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;

  /* "rfc.py":13
   *
   * class ForeignKeywordException(Exception):
   *     def __init__(self, keyword):             # <<<<<<<<<<<<<<
   *         msg = f'usage of foreign keyword: `{keyword}`'
   *         super(Exception, self).__init__(self, msg)
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("rfc.ForeignKeywordException.__init__", __pyx_clineno,
                     __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_msg);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":20
 * class Alias:
 *
 *     def __init__(self, rf, py):             # <<<<<<<<<<<<<<
 *         self.rf, self.py = rf, py
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_5Alias_1__init__(PyObject *__pyx_self,
                                                PyObject *__pyx_args,
                                                PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_5Alias_1__init__ = {
    "__init__", (PyCFunction)__pyx_pw_3rfc_5Alias_1__init__,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_5Alias_1__init__(PyObject *__pyx_self,
                                                PyObject *__pyx_args,
                                                PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_rf = 0;
  PyObject *__pyx_v_py = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("__init__ (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s_rf,
                                            &__pyx_n_s_py, 0};
    PyObject *values[3] = {0, 0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 3:
          values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
          RFC_FALLTHROUGH;
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_rf)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, 1);
            __PYX_ERR(0, 20, __pyx_L3_error)
          }
          RFC_FALLTHROUGH;
        case 2:
          if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_py)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, 2);
            __PYX_ERR(0, 20, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "__init__") < 0))
          __PYX_ERR(0, 20, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_self = values[0];
    __pyx_v_rf = values[1];
    __pyx_v_py = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 20, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Alias.__init__", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_5Alias___init__(__pyx_self, __pyx_v_self, __pyx_v_rf,
                                          __pyx_v_py);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_5Alias___init__(RFC_UNUSED PyObject *__pyx_self,
                                               PyObject *__pyx_v_self,
                                               PyObject *__pyx_v_rf,
                                               PyObject *__pyx_v_py) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "rfc.py":21
   *
   *     def __init__(self, rf, py):
   *         self.rf, self.py = rf, py             # <<<<<<<<<<<<<<
   *
   *
   */
  __pyx_t_1 = __pyx_v_rf;
  __Pyx_INCREF(__pyx_t_1);
  __pyx_t_2 = __pyx_v_py;
  __Pyx_INCREF(__pyx_t_2);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_rf, __pyx_t_1) < 0)
    __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_py, __pyx_t_2) < 0)
    __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":20
   * class Alias:
   *
   *     def __init__(self, rf, py):             # <<<<<<<<<<<<<<
   *         self.rf, self.py = rf, py
   *
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("rfc.Alias.__init__", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":35
 *     foreign_keywords = ['not', 'and', 'or']
 *
 *     def __init__(self, toks, parsed):             # <<<<<<<<<<<<<<
 *         self.output = [[0, '']]
 *         self.transform(toks, parsed)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_7Codegen_1__init__(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_7Codegen_1__init__ = {
    "__init__", (PyCFunction)__pyx_pw_3rfc_7Codegen_1__init__,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_7Codegen_1__init__(PyObject *__pyx_self,
                                                  PyObject *__pyx_args,
                                                  PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_toks = 0;
  PyObject *__pyx_v_parsed = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("__init__ (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s_toks,
                                            &__pyx_n_s_parsed, 0};
    PyObject *values[3] = {0, 0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 3:
          values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
          RFC_FALLTHROUGH;
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_toks)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, 1);
            __PYX_ERR(0, 35, __pyx_L3_error)
          }
          RFC_FALLTHROUGH;
        case 2:
          if (likely((values[2] =
                          PyDict_GetItem(__pyx_kwds, __pyx_n_s_parsed)) != 0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, 2);
            __PYX_ERR(0, 35, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "__init__") < 0))
          __PYX_ERR(0, 35, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_self = values[0];
    __pyx_v_toks = values[1];
    __pyx_v_parsed = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 3, 3, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 35, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Codegen.__init__", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_7Codegen___init__(__pyx_self, __pyx_v_self,
                                            __pyx_v_toks, __pyx_v_parsed);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_7Codegen___init__(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_toks, PyObject *__pyx_v_parsed) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "rfc.py":36
   *
   *     def __init__(self, toks, parsed):
   *         self.output = [[0, '']]             # <<<<<<<<<<<<<<
   *         self.transform(toks, parsed)
   *
   */
  __pyx_t_1 = PyList_New(2);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 36, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_int_0);
  __Pyx_GIVEREF(__pyx_int_0);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_int_0);
  __Pyx_INCREF(__pyx_kp_u__2);
  __Pyx_GIVEREF(__pyx_kp_u__2);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_kp_u__2);
  __pyx_t_2 = PyList_New(1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 36, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_1);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_output, __pyx_t_2) < 0)
    __PYX_ERR(0, 36, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":37
   *     def __init__(self, toks, parsed):
   *         self.output = [[0, '']]
   *         self.transform(toks, parsed)             # <<<<<<<<<<<<<<
   *
   *     def newline(self, indent_offset=0, content=''):
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_transform);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 37, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = NULL;
  __pyx_t_4 = 0;
  if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_3)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
      __pyx_t_4 = 1;
    }
  }
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp + 1 - __pyx_t_4,
                                          2 + __pyx_t_4);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_2 = __Pyx_PyCFunction_FastCall(
        __pyx_t_1, __pyx_temp + 1 - __pyx_t_4, 2 + __pyx_t_4);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
#endif
  {
    __pyx_t_5 = PyTuple_New(2 + __pyx_t_4);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (__pyx_t_3) {
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3);
      __pyx_t_3 = NULL;
    }
    __Pyx_INCREF(__pyx_v_toks);
    __Pyx_GIVEREF(__pyx_v_toks);
    PyTuple_SET_ITEM(__pyx_t_5, 0 + __pyx_t_4, __pyx_v_toks);
    __Pyx_INCREF(__pyx_v_parsed);
    __Pyx_GIVEREF(__pyx_v_parsed);
    PyTuple_SET_ITEM(__pyx_t_5, 1 + __pyx_t_4, __pyx_v_parsed);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 37, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":35
   *     foreign_keywords = ['not', 'and', 'or']
   *
   *     def __init__(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.output = [[0, '']]
   *         self.transform(toks, parsed)
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("rfc.Codegen.__init__", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":39
 *         self.transform(toks, parsed)
 *
 *     def newline(self, indent_offset=0, content=''):             #
 * <<<<<<<<<<<<<< last = self.output[-1][0] self.output += [[last +
 * indent_offset, content]]
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_7Codegen_3newline(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_7Codegen_3newline = {
    "newline", (PyCFunction)__pyx_pw_3rfc_7Codegen_3newline,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_7Codegen_3newline(PyObject *__pyx_self,
                                                 PyObject *__pyx_args,
                                                 PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_indent_offset = 0;
  PyObject *__pyx_v_content = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("newline (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {
        &__pyx_n_s_self, &__pyx_n_s_indent_offset, &__pyx_n_s_content, 0};
    PyObject *values[3] = {0, 0, 0};
    values[1] = ((PyObject *)((PyObject *)__pyx_int_0));
    values[2] = ((PyObject *)((PyObject *)__pyx_kp_u__2));
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 3:
          values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
          RFC_FALLTHROUGH;
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (kw_args > 0) {
            PyObject *value =
                PyDict_GetItem(__pyx_kwds, __pyx_n_s_indent_offset);
            if (value) {
              values[1] = value;
              kw_args--;
            }
          }
          RFC_FALLTHROUGH;
        case 2:
          if (kw_args > 0) {
            PyObject *value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_content);
            if (value) {
              values[2] = value;
              kw_args--;
            }
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "newline") < 0))
          __PYX_ERR(0, 39, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case 3:
          values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
          RFC_FALLTHROUGH;
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_self = values[0];
    __pyx_v_indent_offset = values[1];
    __pyx_v_content = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("newline", 0, 1, 3, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 39, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Codegen.newline", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_7Codegen_2newline(
      __pyx_self, __pyx_v_self, __pyx_v_indent_offset, __pyx_v_content);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_7Codegen_2newline(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_indent_offset, PyObject *__pyx_v_content) {
  PyObject *__pyx_v_last = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  __Pyx_RefNannySetupContext("newline", 0);

  /* "rfc.py":40
   *
   *     def newline(self, indent_offset=0, content=''):
   *         last = self.output[-1][0]             # <<<<<<<<<<<<<<
   *         self.output += [[last + indent_offset, content]]
   *
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_output);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_GetItemInt(__pyx_t_1, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 =
      __Pyx_GetItemInt(__pyx_t_2, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 40, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_v_last = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "rfc.py":41
   *     def newline(self, indent_offset=0, content=''):
   *         last = self.output[-1][0]
   *         self.output += [[last + indent_offset, content]]             #
   * <<<<<<<<<<<<<<
   *
   *     def line(self, code):
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_output);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyNumber_Add(__pyx_v_last, __pyx_v_indent_offset);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyList_New(2);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_2);
  PyList_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_INCREF(__pyx_v_content);
  __Pyx_GIVEREF(__pyx_v_content);
  PyList_SET_ITEM(__pyx_t_3, 1, __pyx_v_content);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyList_New(1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_2);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_output, __pyx_t_3) < 0)
    __PYX_ERR(0, 41, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;

  /* "rfc.py":39
   *         self.transform(toks, parsed)
   *
   *     def newline(self, indent_offset=0, content=''):             #
   * <<<<<<<<<<<<<< last = self.output[-1][0] self.output += [[last +
   * indent_offset, content]]
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("rfc.Codegen.newline", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_last);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":43
 *         self.output += [[last + indent_offset, content]]
 *
 *     def line(self, code):             # <<<<<<<<<<<<<<
 *         self.output[-1][1] += code
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_7Codegen_5line(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_7Codegen_5line = {
    "line", (PyCFunction)__pyx_pw_3rfc_7Codegen_5line,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_7Codegen_5line(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_code = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("line (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s_code,
                                            0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_code)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("line", 1, 2, 2, 1);
            __PYX_ERR(0, 43, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "line") < 0))
          __PYX_ERR(0, 43, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v_code = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("line", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 43, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Codegen.line", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r =
      __pyx_pf_3rfc_7Codegen_4line(__pyx_self, __pyx_v_self, __pyx_v_code);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_7Codegen_4line(RFC_UNUSED PyObject *__pyx_self,
                                              PyObject *__pyx_v_self,
                                              PyObject *__pyx_v_code) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  __Pyx_RefNannySetupContext("line", 0);

  /* "rfc.py":44
   *
   *     def line(self, code):
   *         self.output[-1][1] += code             # <<<<<<<<<<<<<<
   *
   *     def transform(self, toks, parsed):
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_output);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 44, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_GetItemInt(__pyx_t_1, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 44, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_3 = 1;
  __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_2, __pyx_t_3, Py_ssize_t, 1,
                               PyInt_FromSsize_t, 0, 1, 1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 44, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_v_code);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 44, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  if (unlikely(__Pyx_SetItemInt(__pyx_t_2, __pyx_t_3, __pyx_t_4, Py_ssize_t, 1,
                                PyInt_FromSsize_t, 0, 1, 1) < 0))
    __PYX_ERR(0, 44, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":43
   *         self.output += [[last + indent_offset, content]]
   *
   *     def line(self, code):             # <<<<<<<<<<<<<<
   *         self.output[-1][1] += code
   *
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("rfc.Codegen.line", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":46
 *         self.output[-1][1] += code
 *
 *     def transform(self, toks, parsed):             # <<<<<<<<<<<<<<
 *         self.toks = []
 *         toks = list(toks)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_7Codegen_7transform(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_7Codegen_7transform = {
    "transform", (PyCFunction)__pyx_pw_3rfc_7Codegen_7transform,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_7Codegen_7transform(PyObject *__pyx_self,
                                                   PyObject *__pyx_args,
                                                   PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v_toks = 0;
  PyObject *__pyx_v_parsed = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("transform (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s_toks,
                                            &__pyx_n_s_parsed, 0};
    PyObject *values[3] = {0, 0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 3:
          values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
          RFC_FALLTHROUGH;
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_toks)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("transform", 1, 3, 3, 1);
            __PYX_ERR(0, 46, __pyx_L3_error)
          }
          RFC_FALLTHROUGH;
        case 2:
          if (likely((values[2] =
                          PyDict_GetItem(__pyx_kwds, __pyx_n_s_parsed)) != 0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("transform", 1, 3, 3, 2);
            __PYX_ERR(0, 46, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "transform") < 0))
          __PYX_ERR(0, 46, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 3) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
    }
    __pyx_v_self = values[0];
    __pyx_v_toks = values[1];
    __pyx_v_parsed = values[2];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("transform", 1, 3, 3,
                             PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 46, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Codegen.transform", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_7Codegen_6transform(__pyx_self, __pyx_v_self,
                                              __pyx_v_toks, __pyx_v_parsed);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_7Codegen_6transform(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v_toks, PyObject *__pyx_v_parsed) {
  PyObject *__pyx_v_t = NULL;
  PyObject *__pyx_v_already_visited = NULL;
  PyObject *__pyx_v_tok = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *(*__pyx_t_3)(PyObject *);
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  PyObject *(*__pyx_t_7)(PyObject *);
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  int __pyx_t_11;
  __Pyx_RefNannySetupContext("transform", 0);
  __Pyx_INCREF(__pyx_v_toks);

  /* "rfc.py":47
   *
   *     def transform(self, toks, parsed):
   *         self.toks = []             # <<<<<<<<<<<<<<
   *         toks = list(toks)
   *         for t in toks:
   */
  __pyx_t_1 = PyList_New(0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 47, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks, __pyx_t_1) < 0)
    __PYX_ERR(0, 47, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":48
   *     def transform(self, toks, parsed):
   *         self.toks = []
   *         toks = list(toks)             # <<<<<<<<<<<<<<
   *         for t in toks:
   *             already_visited = []
   */
  __pyx_t_1 = PySequence_List(__pyx_v_toks);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 48, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF_SET(__pyx_v_toks, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":49
   *         self.toks = []
   *         toks = list(toks)
   *         for t in toks:             # <<<<<<<<<<<<<<
   *             already_visited = []
   *             for tok in parsed['decorated']:
   */
  if (likely(PyList_CheckExact(__pyx_v_toks)) ||
      PyTuple_CheckExact(__pyx_v_toks)) {
    __pyx_t_1 = __pyx_v_toks;
    __Pyx_INCREF(__pyx_t_1);
    __pyx_t_2 = 0;
    __pyx_t_3 = NULL;
  } else {
    __pyx_t_2 = -1;
    __pyx_t_1 = PyObject_GetIter(__pyx_v_toks);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 49, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = Py_TYPE(__pyx_t_1)->tp_iternext;
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 49, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_3)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
        __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2);
        __Pyx_INCREF(__pyx_t_4);
        __pyx_t_2++;
        if (unlikely(0 < 0)) __PYX_ERR(0, 49, __pyx_L1_error)
#else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2);
        __pyx_t_2++;
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 49, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
#endif
      } else {
        if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
        __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2);
        __Pyx_INCREF(__pyx_t_4);
        __pyx_t_2++;
        if (unlikely(0 < 0)) __PYX_ERR(0, 49, __pyx_L1_error)
#else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2);
        __pyx_t_2++;
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 49, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
#endif
      }
    } else {
      __pyx_t_4 = __pyx_t_3(__pyx_t_1);
      if (unlikely(!__pyx_t_4)) {
        PyObject *exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(
                  exc_type == PyExc_StopIteration ||
                  PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
            PyErr_Clear();
          else
            __PYX_ERR(0, 49, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_4);
    }
    __Pyx_XDECREF_SET(__pyx_v_t, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "rfc.py":50
     *         toks = list(toks)
     *         for t in toks:
     *             already_visited = []             # <<<<<<<<<<<<<<
     *             for tok in parsed['decorated']:
     *                 if (tok.line, tok.column) in already_visited:
     */
    __pyx_t_4 = PyList_New(0);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 50, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_XDECREF_SET(__pyx_v_already_visited, ((PyObject *)__pyx_t_4));
    __pyx_t_4 = 0;

    /* "rfc.py":51
     *         for t in toks:
     *             already_visited = []
     *             for tok in parsed['decorated']:             # <<<<<<<<<<<<<<
     *                 if (tok.line, tok.column) in already_visited:
     *                     continue
     */
    __pyx_t_4 = PyObject_GetItem(__pyx_v_parsed, __pyx_n_u_decorated);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 51, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (likely(PyList_CheckExact(__pyx_t_4)) || PyTuple_CheckExact(__pyx_t_4)) {
      __pyx_t_5 = __pyx_t_4;
      __Pyx_INCREF(__pyx_t_5);
      __pyx_t_6 = 0;
      __pyx_t_7 = NULL;
    } else {
      __pyx_t_6 = -1;
      __pyx_t_5 = PyObject_GetIter(__pyx_t_4);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 51, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_7 = Py_TYPE(__pyx_t_5)->tp_iternext;
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 51, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
    for (;;) {
      if (likely(!__pyx_t_7)) {
        if (likely(PyList_CheckExact(__pyx_t_5))) {
          if (__pyx_t_6 >= PyList_GET_SIZE(__pyx_t_5)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_4 = PyList_GET_ITEM(__pyx_t_5, __pyx_t_6);
          __Pyx_INCREF(__pyx_t_4);
          __pyx_t_6++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 51, __pyx_L1_error)
#else
          __pyx_t_4 = PySequence_ITEM(__pyx_t_5, __pyx_t_6);
          __pyx_t_6++;
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 51, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
#endif
        } else {
          if (__pyx_t_6 >= PyTuple_GET_SIZE(__pyx_t_5)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_5, __pyx_t_6);
          __Pyx_INCREF(__pyx_t_4);
          __pyx_t_6++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 51, __pyx_L1_error)
#else
          __pyx_t_4 = PySequence_ITEM(__pyx_t_5, __pyx_t_6);
          __pyx_t_6++;
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 51, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
#endif
        }
      } else {
        __pyx_t_4 = __pyx_t_7(__pyx_t_5);
        if (unlikely(!__pyx_t_4)) {
          PyObject *exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(
                    exc_type == PyExc_StopIteration ||
                    PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
              PyErr_Clear();
            else
              __PYX_ERR(0, 51, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_4);
      }
      __Pyx_XDECREF_SET(__pyx_v_tok, __pyx_t_4);
      __pyx_t_4 = 0;

      /* "rfc.py":52
       *             already_visited = []
       *             for tok in parsed['decorated']:
       *                 if (tok.line, tok.column) in already_visited: #
       * <<<<<<<<<<<<<< continue already_visited += [(tok.line, tok.column)]
       */
      __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_9 = PyTuple_New(2);
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_9, 1, __pyx_t_8);
      __pyx_t_4 = 0;
      __pyx_t_8 = 0;
      __pyx_t_10 = (__Pyx_PySequence_ContainsTF(
          __pyx_t_9, __pyx_v_already_visited, Py_EQ));
      if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 52, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9);
      __pyx_t_9 = 0;
      __pyx_t_11 = (__pyx_t_10 != 0);
      if (__pyx_t_11) {
        /* "rfc.py":53
         *             for tok in parsed['decorated']:
         *                 if (tok.line, tok.column) in already_visited:
         *                     continue             # <<<<<<<<<<<<<<
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column:
         */
        goto __pyx_L5_continue;

        /* "rfc.py":52
         *             already_visited = []
         *             for tok in parsed['decorated']:
         *                 if (tok.line, tok.column) in already_visited: #
         * <<<<<<<<<<<<<< continue already_visited += [(tok.line, tok.column)]
         */
      }

      /* "rfc.py":54
       *                 if (tok.line, tok.column) in already_visited:
       *                     continue
       *                 already_visited += [(tok.line, tok.column)] #
       * <<<<<<<<<<<<<< if tok.line == t.line and tok.column == t.column: if
       * t.value == '#':
       */
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 54, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 54, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_4 = PyTuple_New(2);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 54, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_9);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_8);
      __pyx_t_9 = 0;
      __pyx_t_8 = 0;
      __pyx_t_8 = PyList_New(1);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 54, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_4);
      PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_4);
      __pyx_t_4 = 0;
      __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_v_already_visited, __pyx_t_8);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 54, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __Pyx_DECREF_SET(__pyx_v_already_visited, ((PyObject *)__pyx_t_4));
      __pyx_t_4 = 0;

      /* "rfc.py":55
       *                     continue
       *                 already_visited += [(tok.line, tok.column)]
       *                 if tok.line == t.line and tok.column == t.column: #
       * <<<<<<<<<<<<<< if t.value == '#': self.toks += [Token('DECORATOR',
       * '@')]
       */
      __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_line);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_9 = PyObject_RichCompare(__pyx_t_4, __pyx_t_8, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_9);
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_9);
      if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9);
      __pyx_t_9 = 0;
      if (__pyx_t_10) {
      } else {
        __pyx_t_11 = __pyx_t_10;
        goto __pyx_L9_bool_binop_done;
      }
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_4 = PyObject_RichCompare(__pyx_t_9, __pyx_t_8, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_4);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9);
      __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_4);
      if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 55, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __pyx_t_11 = __pyx_t_10;
    __pyx_L9_bool_binop_done:;
      if (__pyx_t_11) {
        /* "rfc.py":56
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column:
         *                     if t.value == '#':             # <<<<<<<<<<<<<<
         *                         self.toks += [Token('DECORATOR', '@')]
         *                     elif t.value == '[':
         */
        __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 56, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __pyx_t_11 = (__Pyx_PyUnicode_Equals(__pyx_t_4, __pyx_kp_u__3, Py_EQ));
        if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 56, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_4);
        __pyx_t_4 = 0;
        if (__pyx_t_11) {
          /* "rfc.py":57
           *                 if tok.line == t.line and tok.column == t.column:
           *                     if t.value == '#':
           *                         self.toks += [Token('DECORATOR', '@')] #
           * <<<<<<<<<<<<<< elif t.value == '[': pass
           */
          __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_Token);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_tuple__5, NULL);
          if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_9);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_GIVEREF(__pyx_t_9);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_9);
          __pyx_t_9 = 0;
          __pyx_t_9 = PyNumber_InPlaceAdd(__pyx_t_4, __pyx_t_8);
          if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_9);
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_9) < 0)
            __PYX_ERR(0, 57, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_9);
          __pyx_t_9 = 0;

          /* "rfc.py":56
           *                 already_visited += [(tok.line, tok.column)]
           *                 if tok.line == t.line and tok.column == t.column:
           *                     if t.value == '#':             # <<<<<<<<<<<<<<
           *                         self.toks += [Token('DECORATOR', '@')]
           *                     elif t.value == '[':
           */
          goto __pyx_L11;
        }

        /* "rfc.py":58
         *                     if t.value == '#':
         *                         self.toks += [Token('DECORATOR', '@')]
         *                     elif t.value == '[':             # <<<<<<<<<<<<<<
         *                         pass
         *                     elif t.value == ']':
         */
        __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 58, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_11 = (__Pyx_PyUnicode_Equals(__pyx_t_9, __pyx_kp_u__6, Py_EQ));
        if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 58, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_9);
        __pyx_t_9 = 0;
        if (__pyx_t_11) {
          goto __pyx_L11;
        }

        /* "rfc.py":60
         *                     elif t.value == '[':
         *                         pass
         *                     elif t.value == ']':             # <<<<<<<<<<<<<<
         *                         self.toks += [Token('SEMICOLON', ';')]
         *                     else:
         */
        __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 60, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_11 = (__Pyx_PyUnicode_Equals(__pyx_t_9, __pyx_kp_u__7, Py_EQ));
        if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 60, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_9);
        __pyx_t_9 = 0;
        if (__pyx_t_11) {
          /* "rfc.py":61
           *                         pass
           *                     elif t.value == ']':
           *                         self.toks += [Token('SEMICOLON', ';')] #
           * <<<<<<<<<<<<<< else: self.toks += [t]
           */
          __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_9);
          __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_Token);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_tuple__9, NULL);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_GIVEREF(__pyx_t_4);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_4);
          __pyx_t_4 = 0;
          __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_9, __pyx_t_8);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_9);
          __pyx_t_9 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_4) < 0)
            __PYX_ERR(0, 61, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;

          /* "rfc.py":60
           *                     elif t.value == '[':
           *                         pass
           *                     elif t.value == ']':             #
           * <<<<<<<<<<<<<< self.toks += [Token('SEMICOLON', ';')] else:
           */
          goto __pyx_L11;
        }

        /* "rfc.py":63
         *                         self.toks += [Token('SEMICOLON', ';')]
         *                     else:
         *                         self.toks += [t]             # <<<<<<<<<<<<<<
         *
         *             for tok in parsed['suite']:
         */
        /*else*/ {
          __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 63, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 63, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_INCREF(__pyx_v_t);
          __Pyx_GIVEREF(__pyx_v_t);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_v_t);
          __pyx_t_9 = PyNumber_InPlaceAdd(__pyx_t_4, __pyx_t_8);
          if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 63, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_9);
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_9) < 0)
            __PYX_ERR(0, 63, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_9);
          __pyx_t_9 = 0;
        }
      __pyx_L11:;

        /* "rfc.py":55
         *                     continue
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column: #
         * <<<<<<<<<<<<<< if t.value == '#': self.toks += [Token('DECORATOR',
         * '@')]
         */
      }

    /* "rfc.py":51
     *         for t in toks:
     *             already_visited = []
     *             for tok in parsed['decorated']:             # <<<<<<<<<<<<<<
     *                 if (tok.line, tok.column) in already_visited:
     *                     continue
     */
    __pyx_L5_continue:;
    }
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;

    /* "rfc.py":65
     *                         self.toks += [t]
     *
     *             for tok in parsed['suite']:             # <<<<<<<<<<<<<<
     *                 if (tok.line, tok.column) in already_visited:
     *                     continue
     */
    __pyx_t_5 = PyObject_GetItem(__pyx_v_parsed, __pyx_n_u_suite);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 65, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (likely(PyList_CheckExact(__pyx_t_5)) || PyTuple_CheckExact(__pyx_t_5)) {
      __pyx_t_9 = __pyx_t_5;
      __Pyx_INCREF(__pyx_t_9);
      __pyx_t_6 = 0;
      __pyx_t_7 = NULL;
    } else {
      __pyx_t_6 = -1;
      __pyx_t_9 = PyObject_GetIter(__pyx_t_5);
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 65, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_7 = Py_TYPE(__pyx_t_9)->tp_iternext;
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 65, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
    for (;;) {
      if (likely(!__pyx_t_7)) {
        if (likely(PyList_CheckExact(__pyx_t_9))) {
          if (__pyx_t_6 >= PyList_GET_SIZE(__pyx_t_9)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_5 = PyList_GET_ITEM(__pyx_t_9, __pyx_t_6);
          __Pyx_INCREF(__pyx_t_5);
          __pyx_t_6++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 65, __pyx_L1_error)
#else
          __pyx_t_5 = PySequence_ITEM(__pyx_t_9, __pyx_t_6);
          __pyx_t_6++;
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 65, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
#endif
        } else {
          if (__pyx_t_6 >= PyTuple_GET_SIZE(__pyx_t_9)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_5 = PyTuple_GET_ITEM(__pyx_t_9, __pyx_t_6);
          __Pyx_INCREF(__pyx_t_5);
          __pyx_t_6++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 65, __pyx_L1_error)
#else
          __pyx_t_5 = PySequence_ITEM(__pyx_t_9, __pyx_t_6);
          __pyx_t_6++;
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 65, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
#endif
        }
      } else {
        __pyx_t_5 = __pyx_t_7(__pyx_t_9);
        if (unlikely(!__pyx_t_5)) {
          PyObject *exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(
                    exc_type == PyExc_StopIteration ||
                    PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
              PyErr_Clear();
            else
              __PYX_ERR(0, 65, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_5);
      }
      __Pyx_XDECREF_SET(__pyx_v_tok, __pyx_t_5);
      __pyx_t_5 = 0;

      /* "rfc.py":66
       *
       *             for tok in parsed['suite']:
       *                 if (tok.line, tok.column) in already_visited: #
       * <<<<<<<<<<<<<< continue already_visited += [(tok.line, tok.column)]
       */
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 66, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 66, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_4 = PyTuple_New(2);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 66, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_8);
      __pyx_t_5 = 0;
      __pyx_t_8 = 0;
      __pyx_t_11 = (__Pyx_PySequence_ContainsTF(
          __pyx_t_4, __pyx_v_already_visited, Py_EQ));
      if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 66, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __pyx_t_10 = (__pyx_t_11 != 0);
      if (__pyx_t_10) {
        /* "rfc.py":67
         *             for tok in parsed['suite']:
         *                 if (tok.line, tok.column) in already_visited:
         *                     continue             # <<<<<<<<<<<<<<
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column:
         */
        goto __pyx_L12_continue;

        /* "rfc.py":66
         *
         *             for tok in parsed['suite']:
         *                 if (tok.line, tok.column) in already_visited: #
         * <<<<<<<<<<<<<< continue already_visited += [(tok.line, tok.column)]
         */
      }

      /* "rfc.py":68
       *                 if (tok.line, tok.column) in already_visited:
       *                     continue
       *                 already_visited += [(tok.line, tok.column)] #
       * <<<<<<<<<<<<<< if tok.line == t.line and tok.column == t.column: if
       * t.value == '{':
       */
      __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 68, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 68, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_5 = PyTuple_New(2);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 68, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_8);
      __pyx_t_4 = 0;
      __pyx_t_8 = 0;
      __pyx_t_8 = PyList_New(1);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 68, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_GIVEREF(__pyx_t_5);
      PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyNumber_InPlaceAdd(__pyx_v_already_visited, __pyx_t_8);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 68, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __Pyx_DECREF_SET(__pyx_v_already_visited, ((PyObject *)__pyx_t_5));
      __pyx_t_5 = 0;

      /* "rfc.py":69
       *                     continue
       *                 already_visited += [(tok.line, tok.column)]
       *                 if tok.line == t.line and tok.column == t.column: #
       * <<<<<<<<<<<<<< if t.value == '{': self.toks += [Token('INDENT', None)]
       */
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_line);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_line);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_4 = PyObject_RichCompare(__pyx_t_5, __pyx_t_8, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_4);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_11 = __Pyx_PyObject_IsTrue(__pyx_t_4);
      if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      if (__pyx_t_11) {
      } else {
        __pyx_t_10 = __pyx_t_11;
        goto __pyx_L16_bool_binop_done;
      }
      __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_tok, __pyx_n_s_column);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_column);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_5 = PyObject_RichCompare(__pyx_t_4, __pyx_t_8, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_5);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_11 = __Pyx_PyObject_IsTrue(__pyx_t_5);
      if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 69, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_10 = __pyx_t_11;
    __pyx_L16_bool_binop_done:;
      if (__pyx_t_10) {
        /* "rfc.py":70
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column:
         *                     if t.value == '{':             # <<<<<<<<<<<<<<
         *                         self.toks += [Token('INDENT', None)]
         *                     elif t.value == '}':
         */
        __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 70, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_10 = (__Pyx_PyUnicode_Equals(__pyx_t_5, __pyx_kp_u__10, Py_EQ));
        if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 70, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        if (__pyx_t_10) {
          /* "rfc.py":71
           *                 if tok.line == t.line and tok.column == t.column:
           *                     if t.value == '{':
           *                         self.toks += [Token('INDENT', None)] #
           * <<<<<<<<<<<<<< elif t.value == '}': self.toks += [Token('DEDENT',
           * None)]
           */
          __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_Token);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_tuple__11, NULL);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_GIVEREF(__pyx_t_4);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_4);
          __pyx_t_4 = 0;
          __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_5, __pyx_t_8);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_4) < 0)
            __PYX_ERR(0, 71, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;

          /* "rfc.py":70
           *                 already_visited += [(tok.line, tok.column)]
           *                 if tok.line == t.line and tok.column == t.column:
           *                     if t.value == '{':             # <<<<<<<<<<<<<<
           *                         self.toks += [Token('INDENT', None)]
           *                     elif t.value == '}':
           */
          goto __pyx_L18;
        }

        /* "rfc.py":72
         *                     if t.value == '{':
         *                         self.toks += [Token('INDENT', None)]
         *                     elif t.value == '}':             # <<<<<<<<<<<<<<
         *                         self.toks += [Token('DEDENT', None)]
         *                     else:
         */
        __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 72, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __pyx_t_10 = (__Pyx_PyUnicode_Equals(__pyx_t_4, __pyx_kp_u__12, Py_EQ));
        if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 72, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_4);
        __pyx_t_4 = 0;
        if (__pyx_t_10) {
          /* "rfc.py":73
           *                         self.toks += [Token('INDENT', None)]
           *                     elif t.value == '}':
           *                         self.toks += [Token('DEDENT', None)] #
           * <<<<<<<<<<<<<< else: self.toks += [t]
           */
          __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_Token);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_8, __pyx_tuple__13, NULL);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_GIVEREF(__pyx_t_5);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_t_5);
          __pyx_t_5 = 0;
          __pyx_t_5 = PyNumber_InPlaceAdd(__pyx_t_4, __pyx_t_8);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_5) < 0)
            __PYX_ERR(0, 73, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;

          /* "rfc.py":72
           *                     if t.value == '{':
           *                         self.toks += [Token('INDENT', None)]
           *                     elif t.value == '}':             #
           * <<<<<<<<<<<<<< self.toks += [Token('DEDENT', None)] else:
           */
          goto __pyx_L18;
        }

        /* "rfc.py":75
         *                         self.toks += [Token('DEDENT', None)]
         *                     else:
         *                         self.toks += [t]             # <<<<<<<<<<<<<<
         *
         *             if (t.line, t.column) in already_visited:
         */
        /*else*/ {
          __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 75, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_8 = PyList_New(1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 75, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_INCREF(__pyx_v_t);
          __Pyx_GIVEREF(__pyx_v_t);
          PyList_SET_ITEM(__pyx_t_8, 0, __pyx_v_t);
          __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_5, __pyx_t_8);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 75, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks,
                                        __pyx_t_4) < 0)
            __PYX_ERR(0, 75, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_4);
          __pyx_t_4 = 0;
        }
      __pyx_L18:;

        /* "rfc.py":69
         *                     continue
         *                 already_visited += [(tok.line, tok.column)]
         *                 if tok.line == t.line and tok.column == t.column: #
         * <<<<<<<<<<<<<< if t.value == '{': self.toks += [Token('INDENT',
         * None)]
         */
      }

    /* "rfc.py":65
     *                         self.toks += [t]
     *
     *             for tok in parsed['suite']:             # <<<<<<<<<<<<<<
     *                 if (tok.line, tok.column) in already_visited:
     *                     continue
     */
    __pyx_L12_continue:;
    }
    __Pyx_DECREF(__pyx_t_9);
    __pyx_t_9 = 0;

    /* "rfc.py":77
     *                         self.toks += [t]
     *
     *             if (t.line, t.column) in already_visited:             #
     * <<<<<<<<<<<<<< continue
     *
     */
    __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_line);
    if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_column);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_8 = PyTuple_New(2);
    if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_GIVEREF(__pyx_t_9);
    PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_9);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_t_4);
    __pyx_t_9 = 0;
    __pyx_t_4 = 0;
    __pyx_t_10 = (__Pyx_PySequence_ContainsTF(__pyx_t_8,
                                              __pyx_v_already_visited, Py_EQ));
    if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_8);
    __pyx_t_8 = 0;
    __pyx_t_11 = (__pyx_t_10 != 0);
    if (__pyx_t_11) {
      /* "rfc.py":78
       *
       *             if (t.line, t.column) in already_visited:
       *                 continue             # <<<<<<<<<<<<<<
       *
       *             self.toks += [t]
       */
      goto __pyx_L3_continue;

      /* "rfc.py":77
       *                         self.toks += [t]
       *
       *             if (t.line, t.column) in already_visited:             #
       * <<<<<<<<<<<<<< continue
       *
       */
    }

    /* "rfc.py":80
     *                 continue
     *
     *             self.toks += [t]             # <<<<<<<<<<<<<<
     *
     *
     */
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
    if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 80, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_4 = PyList_New(1);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 80, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(__pyx_v_t);
    __Pyx_GIVEREF(__pyx_v_t);
    PyList_SET_ITEM(__pyx_t_4, 0, __pyx_v_t);
    __pyx_t_9 = PyNumber_InPlaceAdd(__pyx_t_8, __pyx_t_4);
    if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 80, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __Pyx_DECREF(__pyx_t_8);
    __pyx_t_8 = 0;
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
    if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_toks, __pyx_t_9) < 0)
      __PYX_ERR(0, 80, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_9);
    __pyx_t_9 = 0;

  /* "rfc.py":49
   *         self.toks = []
   *         toks = list(toks)
   *         for t in toks:             # <<<<<<<<<<<<<<
   *             already_visited = []
   *             for tok in parsed['decorated']:
   */
  __pyx_L3_continue:;
  }
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":46
   *         self.output[-1][1] += code
   *
   *     def transform(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.toks = []
   *         toks = list(toks)
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("rfc.Codegen.transform", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_XDECREF(__pyx_v_already_visited);
  __Pyx_XDECREF(__pyx_v_tok);
  __Pyx_XDECREF(__pyx_v_toks);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":83
 *
 *
 *     def gen(self):             # <<<<<<<<<<<<<<
 *         i = 0
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_7Codegen_9gen(PyObject *__pyx_self,
                                             PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_7Codegen_9gen = {
    "gen", (PyCFunction)__pyx_pw_3rfc_7Codegen_9gen, METH_O, 0};
static PyObject *__pyx_pw_3rfc_7Codegen_9gen(PyObject *__pyx_self,
                                             PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("gen (wrapper)", 0);
  __pyx_r = __pyx_pf_3rfc_7Codegen_8gen(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_7Codegen_8gen(RFC_UNUSED PyObject *__pyx_self,
                                             PyObject *__pyx_v_self) {
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_v_t = NULL;
  int __pyx_v_is_alias;
  PyObject *__pyx_v_alias = NULL;
  PyObject *__pyx_v_rf = NULL;
  PyObject *__pyx_v_py = NULL;
  PyObject *__pyx_v_name = NULL;
  PyObject *__pyx_v_types = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  Py_ssize_t __pyx_t_5;
  PyObject *(*__pyx_t_6)(PyObject *);
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  Py_UCS4 __pyx_t_11;
  __Pyx_RefNannySetupContext("gen", 0);

  /* "rfc.py":84
   *
   *     def gen(self):
   *         i = 0             # <<<<<<<<<<<<<<
   *
   *         while i < self.toks.__len__():
   */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_i = __pyx_int_0;

  /* "rfc.py":86
   *         i = 0
   *
   *         while i < self.toks.__len__():             # <<<<<<<<<<<<<<
   *             t = self.toks[i]
   *             is_alias = False
   */
  while (1) {
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_len);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (__pyx_t_2) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 86, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = PyObject_RichCompare(__pyx_v_i, __pyx_t_1, Py_LT);
    __Pyx_XGOTREF(__pyx_t_3);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_3);
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    if (!__pyx_t_4) break;

    /* "rfc.py":87
     *
     *         while i < self.toks.__len__():
     *             t = self.toks[i]             # <<<<<<<<<<<<<<
     *             is_alias = False
     *
     */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_1 = PyObject_GetItem(__pyx_t_3, __pyx_v_i);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_XDECREF_SET(__pyx_v_t, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "rfc.py":88
     *         while i < self.toks.__len__():
     *             t = self.toks[i]
     *             is_alias = False             # <<<<<<<<<<<<<<
     *
     *             for alias in self.aliases:
     */
    __pyx_v_is_alias = 0;

    /* "rfc.py":90
     *             is_alias = False
     *
     *             for alias in self.aliases:             # <<<<<<<<<<<<<<
     *                 rf = t.type == alias.rf.upper()
     *                 py = t.type == 'NAME' and t.value == alias.py
     */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_aliases);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 90, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
      __pyx_t_3 = __pyx_t_1;
      __Pyx_INCREF(__pyx_t_3);
      __pyx_t_5 = 0;
      __pyx_t_6 = NULL;
    } else {
      __pyx_t_5 = -1;
      __pyx_t_3 = PyObject_GetIter(__pyx_t_1);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 90, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_6 = Py_TYPE(__pyx_t_3)->tp_iternext;
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 90, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    for (;;) {
      if (likely(!__pyx_t_6)) {
        if (likely(PyList_CheckExact(__pyx_t_3))) {
          if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_3)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_5);
          __Pyx_INCREF(__pyx_t_1);
          __pyx_t_5++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 90, __pyx_L1_error)
#else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5);
          __pyx_t_5++;
          if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 90, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
#endif
        } else {
          if (__pyx_t_5 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_5);
          __Pyx_INCREF(__pyx_t_1);
          __pyx_t_5++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 90, __pyx_L1_error)
#else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5);
          __pyx_t_5++;
          if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 90, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
#endif
        }
      } else {
        __pyx_t_1 = __pyx_t_6(__pyx_t_3);
        if (unlikely(!__pyx_t_1)) {
          PyObject *exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(
                    exc_type == PyExc_StopIteration ||
                    PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
              PyErr_Clear();
            else
              __PYX_ERR(0, 90, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_1);
      }
      __Pyx_XDECREF_SET(__pyx_v_alias, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "rfc.py":91
       *
       *             for alias in self.aliases:
       *                 rf = t.type == alias.rf.upper()             #
       * <<<<<<<<<<<<<< py = t.type == 'NAME' and t.value == alias.py if rf or
       * py:
       */
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 91, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_alias, __pyx_n_s_rf);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 91, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_upper);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 91, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_8))) {
        __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_8);
        if (likely(__pyx_t_7)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_8);
          __Pyx_INCREF(__pyx_t_7);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_8, function);
        }
      }
      if (__pyx_t_7) {
        __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_8, __pyx_t_7);
        if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 91, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
      } else {
        __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_8);
        if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 91, __pyx_L1_error)
      }
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_8 = PyObject_RichCompare(__pyx_t_1, __pyx_t_2, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_8);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 91, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __Pyx_XDECREF_SET(__pyx_v_rf, __pyx_t_8);
      __pyx_t_8 = 0;

      /* "rfc.py":92
       *             for alias in self.aliases:
       *                 rf = t.type == alias.rf.upper()
       *                 py = t.type == 'NAME' and t.value == alias.py #
       * <<<<<<<<<<<<<< if rf or py: alias = alias.py if rf else alias.rf
       */
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 92, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_1 = PyObject_RichCompare(__pyx_t_2, __pyx_n_u_NAME, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_1);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1);
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 92, __pyx_L1_error)
      if (__pyx_t_4) {
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
      } else {
        __Pyx_INCREF(__pyx_t_1);
        __pyx_t_8 = __pyx_t_1;
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
        goto __pyx_L7_bool_binop_done;
      }
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_alias, __pyx_n_s_py);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 92, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_7 = PyObject_RichCompare(__pyx_t_1, __pyx_t_2, Py_EQ);
      __Pyx_XGOTREF(__pyx_t_7);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 92, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __Pyx_INCREF(__pyx_t_7);
      __pyx_t_8 = __pyx_t_7;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
    __pyx_L7_bool_binop_done:;
      __Pyx_XDECREF_SET(__pyx_v_py, __pyx_t_8);
      __pyx_t_8 = 0;

      /* "rfc.py":93
       *                 rf = t.type == alias.rf.upper()
       *                 py = t.type == 'NAME' and t.value == alias.py
       *                 if rf or py:             # <<<<<<<<<<<<<<
       *                     alias = alias.py if rf else alias.rf
       *                     self.line(alias + ' ')
       */
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_v_rf);
      if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 93, __pyx_L1_error)
      if (!__pyx_t_9) {
      } else {
        __pyx_t_4 = __pyx_t_9;
        goto __pyx_L10_bool_binop_done;
      }
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_v_py);
      if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 93, __pyx_L1_error)
      __pyx_t_4 = __pyx_t_9;
    __pyx_L10_bool_binop_done:;
      if (__pyx_t_4) {
        /* "rfc.py":94
         *                 py = t.type == 'NAME' and t.value == alias.py
         *                 if rf or py:
         *                     alias = alias.py if rf else alias.rf #
         * <<<<<<<<<<<<<< self.line(alias + ' ') is_alias = True
         */
        __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_v_rf);
        if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 94, __pyx_L1_error)
        if (__pyx_t_4) {
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_alias, __pyx_n_s_py);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 94, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __pyx_t_8 = __pyx_t_7;
          __pyx_t_7 = 0;
        } else {
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_alias, __pyx_n_s_rf);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 94, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __pyx_t_8 = __pyx_t_7;
          __pyx_t_7 = 0;
        }
        __Pyx_DECREF_SET(__pyx_v_alias, __pyx_t_8);
        __pyx_t_8 = 0;

        /* "rfc.py":95
         *                 if rf or py:
         *                     alias = alias.py if rf else alias.rf
         *                     self.line(alias + ' ')             #
         * <<<<<<<<<<<<<< is_alias = True
         *
         */
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 95, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_2 = PyNumber_Add(__pyx_v_alias, __pyx_kp_u__14);
        if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 95, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_1 = NULL;
        if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_7))) {
          __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_7);
          if (likely(__pyx_t_1)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
            __Pyx_INCREF(__pyx_t_1);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_7, function);
          }
        }
        if (!__pyx_t_1) {
          __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_2);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 95, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __Pyx_GOTREF(__pyx_t_8);
        } else {
#if RFC_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_2};
            __pyx_t_8 =
                __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 95, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_1);
            __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_8);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          } else
#endif
#if RFC_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_2};
            __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_7,
                                                   __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 95, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_1);
            __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_8);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          } else
#endif
          {
            __pyx_t_10 = PyTuple_New(1 + 1);
            if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 95, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_GIVEREF(__pyx_t_1);
            PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_1);
            __pyx_t_1 = NULL;
            __Pyx_GIVEREF(__pyx_t_2);
            PyTuple_SET_ITEM(__pyx_t_10, 0 + 1, __pyx_t_2);
            __pyx_t_2 = 0;
            __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_10, NULL);
            if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 95, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_8);
            __Pyx_DECREF(__pyx_t_10);
            __pyx_t_10 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_8);
        __pyx_t_8 = 0;

        /* "rfc.py":96
         *                     alias = alias.py if rf else alias.rf
         *                     self.line(alias + ' ')
         *                     is_alias = True             # <<<<<<<<<<<<<<
         *
         *             if is_alias:
         */
        __pyx_v_is_alias = 1;

        /* "rfc.py":93
         *                 rf = t.type == alias.rf.upper()
         *                 py = t.type == 'NAME' and t.value == alias.py
         *                 if rf or py:             # <<<<<<<<<<<<<<
         *                     alias = alias.py if rf else alias.rf
         *                     self.line(alias + ' ')
         */
      }

      /* "rfc.py":90
       *             is_alias = False
       *
       *             for alias in self.aliases:             # <<<<<<<<<<<<<<
       *                 rf = t.type == alias.rf.upper()
       *                 py = t.type == 'NAME' and t.value == alias.py
       */
    }
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;

    /* "rfc.py":98
     *                     is_alias = True
     *
     *             if is_alias:             # <<<<<<<<<<<<<<
     *                 i += 1
     *                 continue
     */
    __pyx_t_4 = (__pyx_v_is_alias != 0);
    if (__pyx_t_4) {
      /* "rfc.py":99
       *
       *             if is_alias:
       *                 i += 1             # <<<<<<<<<<<<<<
       *                 continue
       *
       */
      __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 99, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_3);
      __pyx_t_3 = 0;

      /* "rfc.py":100
       *             if is_alias:
       *                 i += 1
       *                 continue             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'INDENT':
       */
      goto __pyx_L3_continue;

      /* "rfc.py":98
       *                     is_alias = True
       *
       *             if is_alias:             # <<<<<<<<<<<<<<
       *                 i += 1
       *                 continue
       */
    }

    /* "rfc.py":102
     *                 continue
     *
     *             elif t.type == 'INDENT':             # <<<<<<<<<<<<<<
     *                 self.line(':')
     *                 if self.toks[i+1].type == 'DEDENT':
     */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 102, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_INDENT, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 102, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":103
       *
       *             elif t.type == 'INDENT':
       *                 self.line(':')             # <<<<<<<<<<<<<<
       *                 if self.toks[i+1].type == 'DEDENT':
       *                     self.line('pass')
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 103, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__16, NULL);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 103, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;

      /* "rfc.py":104
       *             elif t.type == 'INDENT':
       *                 self.line(':')
       *                 if self.toks[i+1].type == 'DEDENT':             #
       * <<<<<<<<<<<<<< self.line('pass') self.newline(1)
       */
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 0);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_7 = PyObject_GetItem(__pyx_t_8, __pyx_t_3);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_type);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_DEDENT, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (__pyx_t_4) {
        /* "rfc.py":105
         *                 self.line(':')
         *                 if self.toks[i+1].type == 'DEDENT':
         *                     self.line('pass')             # <<<<<<<<<<<<<<
         *                 self.newline(1)
         *
         */
        __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 105, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__17, NULL);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 105, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;

        /* "rfc.py":104
         *             elif t.type == 'INDENT':
         *                 self.line(':')
         *                 if self.toks[i+1].type == 'DEDENT':             #
         * <<<<<<<<<<<<<< self.line('pass') self.newline(1)
         */
      }

      /* "rfc.py":106
       *                 if self.toks[i+1].type == 'DEDENT':
       *                     self.line('pass')
       *                 self.newline(1)             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'DEDENT':
       */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 106, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__18, NULL);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 106, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;

      /* "rfc.py":102
       *                 continue
       *
       *             elif t.type == 'INDENT':             # <<<<<<<<<<<<<<
       *                 self.line(':')
       *                 if self.toks[i+1].type == 'DEDENT':
       */
      goto __pyx_L12;
    }

    /* "rfc.py":108
     *                 self.newline(1)
     *
     *             elif t.type == 'DEDENT':             # <<<<<<<<<<<<<<
     *                 self.newline(-1)
     *
     */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_DEDENT, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":109
       *
       *             elif t.type == 'DEDENT':
       *                 self.newline(-1)             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'SEMICOLON':
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 109, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__19, NULL);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 109, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;

      /* "rfc.py":108
       *                 self.newline(1)
       *
       *             elif t.type == 'DEDENT':             # <<<<<<<<<<<<<<
       *                 self.newline(-1)
       *
       */
      goto __pyx_L12;
    }

    /* "rfc.py":111
     *                 self.newline(-1)
     *
     *             elif t.type == 'SEMICOLON':             # <<<<<<<<<<<<<<
     *                 self.newline()
     *
     */
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 111, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_n_u_SEMICOLON, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 111, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":112
       *
       *             elif t.type == 'SEMICOLON':
       *                 self.newline()             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'DEF':
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_8 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
        __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_3);
        if (likely(__pyx_t_8)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
          __Pyx_INCREF(__pyx_t_8);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_3, function);
        }
      }
      if (__pyx_t_8) {
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_8);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 112, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_8);
        __pyx_t_8 = 0;
      } else {
        __pyx_t_7 = __Pyx_PyObject_CallNoArg(__pyx_t_3);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 112, __pyx_L1_error)
      }
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;

      /* "rfc.py":111
       *                 self.newline(-1)
       *
       *             elif t.type == 'SEMICOLON':             # <<<<<<<<<<<<<<
       *                 self.newline()
       *
       */
      goto __pyx_L12;
    }

    /* "rfc.py":114
     *                 self.newline()
     *
     *             elif t.type == 'DEF':             # <<<<<<<<<<<<<<
     *                 self.newline(content='def ')
     *
     */
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_n_u_DEF, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":115
       *
       *             elif t.type == 'DEF':
       *                 self.newline(content='def ')             #
       * <<<<<<<<<<<<<<
       *
       *             elif t.type == 'ELSE':
       */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 115, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_3 = PyDict_New();
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 115, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_content, __pyx_kp_u_def) < 0)
        __PYX_ERR(0, 115, __pyx_L1_error)
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_empty_tuple, __pyx_t_3);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 115, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;

      /* "rfc.py":114
       *                 self.newline()
       *
       *             elif t.type == 'DEF':             # <<<<<<<<<<<<<<
       *                 self.newline(content='def ')
       *
       */
      goto __pyx_L12;
    }

    /* "rfc.py":117
     *                 self.newline(content='def ')
     *
     *             elif t.type == 'ELSE':             # <<<<<<<<<<<<<<
     *                 if self.toks[i+1].type == 'IF':
     *                     self.line('elif ')
     */
    __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 117, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_8, __pyx_n_u_ELSE, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 117, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_8);
    __pyx_t_8 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":118
       *
       *             elif t.type == 'ELSE':
       *                 if self.toks[i+1].type == 'IF':             #
       * <<<<<<<<<<<<<< self.line('elif ') i += 1
       */
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 0);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_7 = PyObject_GetItem(__pyx_t_8, __pyx_t_3);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_type);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_IF, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (__pyx_t_4) {
        /* "rfc.py":119
         *             elif t.type == 'ELSE':
         *                 if self.toks[i+1].type == 'IF':
         *                     self.line('elif ')             # <<<<<<<<<<<<<<
         *                     i += 1
         *                 else:
         */
        __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 119, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__20, NULL);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 119, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;

        /* "rfc.py":120
         *                 if self.toks[i+1].type == 'IF':
         *                     self.line('elif ')
         *                     i += 1             # <<<<<<<<<<<<<<
         *                 else:
         *                     self.line('else ')
         */
        __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 120, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_7);
        __pyx_t_7 = 0;

        /* "rfc.py":118
         *
         *             elif t.type == 'ELSE':
         *                 if self.toks[i+1].type == 'IF':             #
         * <<<<<<<<<<<<<< self.line('elif ') i += 1
         */
        goto __pyx_L14;
      }

      /* "rfc.py":122
       *                     i += 1
       *                 else:
       *                     self.line('else ')             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'TYPE':
       */
      /*else*/ {
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 122, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__21, NULL);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 122, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
      }
    __pyx_L14:;

      /* "rfc.py":117
       *                 self.newline(content='def ')
       *
       *             elif t.type == 'ELSE':             # <<<<<<<<<<<<<<
       *                 if self.toks[i+1].type == 'IF':
       *                     self.line('elif ')
       */
      goto __pyx_L12;
    }

    /* "rfc.py":124
     *                     self.line('else ')
     *
     *             elif t.type == 'TYPE':             # <<<<<<<<<<<<<<
     *                 name = self.toks[i+1].value
     *                 i += 2
     */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_TYPE, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":125
       *
       *             elif t.type == 'TYPE':
       *                 name = self.toks[i+1].value             #
       * <<<<<<<<<<<<<< i += 2 if self.toks[i].value == ':':
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 0);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_8 = PyObject_GetItem(__pyx_t_3, __pyx_t_7);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_value);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __Pyx_XDECREF_SET(__pyx_v_name, __pyx_t_7);
      __pyx_t_7 = 0;

      /* "rfc.py":126
       *             elif t.type == 'TYPE':
       *                 name = self.toks[i+1].value
       *                 i += 2             # <<<<<<<<<<<<<<
       *                 if self.toks[i].value == ':':
       *                     types = ', '
       */
      __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_2, 2, 1);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 126, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_7);
      __pyx_t_7 = 0;

      /* "rfc.py":127
       *                 name = self.toks[i+1].value
       *                 i += 2
       *                 if self.toks[i].value == ':':             #
       * <<<<<<<<<<<<<< types = ', ' while self.toks[i].value != ';':
       */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 127, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_8 = PyObject_GetItem(__pyx_t_7, __pyx_v_i);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 127, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_value);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 127, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_kp_u__15, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 127, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      if (__pyx_t_4) {
        /* "rfc.py":128
         *                 i += 2
         *                 if self.toks[i].value == ':':
         *                     types = ', '             # <<<<<<<<<<<<<<
         *                     while self.toks[i].value != ';':
         *                         i += 1
         */
        __Pyx_INCREF(__pyx_kp_u__22);
        __Pyx_XDECREF_SET(__pyx_v_types, __pyx_kp_u__22);

        /* "rfc.py":129
         *                 if self.toks[i].value == ':':
         *                     types = ', '
         *                     while self.toks[i].value != ';':             #
         * <<<<<<<<<<<<<< i += 1 types += self.toks[i].value
         */
        while (1) {
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 129, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __pyx_t_8 = PyObject_GetItem(__pyx_t_7, __pyx_v_i);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 129, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_DECREF(__pyx_t_7);
          __pyx_t_7 = 0;
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_value);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 129, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_kp_u__8, Py_NE));
          if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 129, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_7);
          __pyx_t_7 = 0;
          if (!__pyx_t_4) break;

          /* "rfc.py":130
           *                     types = ', '
           *                     while self.toks[i].value != ';':
           *                         i += 1             # <<<<<<<<<<<<<<
           *                         types += self.toks[i].value
           *                 elif self.toks[i].value == '=':
           */
          __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 130, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_7);
          __pyx_t_7 = 0;

          /* "rfc.py":131
           *                     while self.toks[i].value != ';':
           *                         i += 1
           *                         types += self.toks[i].value             #
           * <<<<<<<<<<<<<< elif self.toks[i].value == '=':
           *                     self.newline(content=f'{name} = ')
           */
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 131, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __pyx_t_8 = PyObject_GetItem(__pyx_t_7, __pyx_v_i);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 131, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_DECREF(__pyx_t_7);
          __pyx_t_7 = 0;
          __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_value);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 131, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
          __pyx_t_8 = PyNumber_InPlaceAdd(__pyx_v_types, __pyx_t_7);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 131, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_DECREF(__pyx_t_7);
          __pyx_t_7 = 0;
          __Pyx_DECREF_SET(__pyx_v_types, __pyx_t_8);
          __pyx_t_8 = 0;
        }

        /* "rfc.py":127
         *                 name = self.toks[i+1].value
         *                 i += 2
         *                 if self.toks[i].value == ':':             #
         * <<<<<<<<<<<<<< types = ', ' while self.toks[i].value != ';':
         */
        goto __pyx_L15;
      }

      /* "rfc.py":132
       *                         i += 1
       *                         types += self.toks[i].value
       *                 elif self.toks[i].value == '=':             #
       * <<<<<<<<<<<<<< self.newline(content=f'{name} = ') i += 1
       */
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_toks);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 132, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_7 = PyObject_GetItem(__pyx_t_8, __pyx_v_i);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 132, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_value);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 132, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_8, __pyx_kp_u__23, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 132, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      if (__pyx_t_4) {
        /* "rfc.py":133
         *                         types += self.toks[i].value
         *                 elif self.toks[i].value == '=':
         *                     self.newline(content=f'{name} = ')             #
         * <<<<<<<<<<<<<< i += 1 continue
         */
        __pyx_t_8 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
        if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __pyx_t_7 = PyDict_New();
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_3 =
            __Pyx_PyObject_FormatSimple(__pyx_v_name, __pyx_empty_unicode);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_10 = __Pyx_PyUnicode_Concat(__pyx_t_3, __pyx_kp_u__24);
        if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        if (PyDict_SetItem(__pyx_t_7, __pyx_n_s_content, __pyx_t_10) < 0)
          __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10);
        __pyx_t_10 = 0;
        __pyx_t_10 =
            __Pyx_PyObject_Call(__pyx_t_8, __pyx_empty_tuple, __pyx_t_7);
        if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 133, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_8);
        __pyx_t_8 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_10);
        __pyx_t_10 = 0;

        /* "rfc.py":134
         *                 elif self.toks[i].value == '=':
         *                     self.newline(content=f'{name} = ')
         *                     i += 1             # <<<<<<<<<<<<<<
         *                     continue
         *                 else: types = ';'
         */
        __pyx_t_10 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1);
        if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 134, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_10);
        __pyx_t_10 = 0;

        /* "rfc.py":135
         *                     self.newline(content=f'{name} = ')
         *                     i += 1
         *                     continue             # <<<<<<<<<<<<<<
         *                 else: types = ';'
         *                 types = types[:-1]
         */
        goto __pyx_L3_continue;

        /* "rfc.py":132
         *                         i += 1
         *                         types += self.toks[i].value
         *                 elif self.toks[i].value == '=':             #
         * <<<<<<<<<<<<<< self.newline(content=f'{name} = ') i += 1
         */
      }

      /* "rfc.py":136
       *                     i += 1
       *                     continue
       *                 else: types = ';'             # <<<<<<<<<<<<<<
       *                 types = types[:-1]
       *                 self.newline(content=f'{name} =
       * TypeVar("{name}"{types})')
       */
      /*else*/ {
        __Pyx_INCREF(__pyx_kp_u__8);
        __Pyx_XDECREF_SET(__pyx_v_types, __pyx_kp_u__8);
      }
    __pyx_L15:;

      /* "rfc.py":137
       *                     continue
       *                 else: types = ';'
       *                 types = types[:-1]             # <<<<<<<<<<<<<<
       *                 self.newline(content=f'{name} =
       * TypeVar("{name}"{types})')
       *
       */
      __pyx_t_10 = __Pyx_PyObject_GetSlice(__pyx_v_types, 0, -1L, NULL, NULL,
                                           &__pyx_slice__25, 0, 1, 1);
      if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 137, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_DECREF_SET(__pyx_v_types, __pyx_t_10);
      __pyx_t_10 = 0;

      /* "rfc.py":138
       *                 else: types = ';'
       *                 types = types[:-1]
       *                 self.newline(content=f'{name} =
       * TypeVar("{name}"{types})')             # <<<<<<<<<<<<<<
       *
       *             elif t.type == 'NAME':
       */
      __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_newline);
      if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __pyx_t_7 = PyDict_New();
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_8 = PyTuple_New(6);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_5 = 0;
      __pyx_t_11 = 127;
      __pyx_t_3 =
          __Pyx_PyObject_FormatSimple(__pyx_v_name, __pyx_empty_unicode);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_11 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3) > __pyx_t_11)
                       ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3)
                       : __pyx_t_11;
      __pyx_t_5 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_INCREF(__pyx_kp_u_TypeVar);
      __pyx_t_5 += 12;
      __Pyx_GIVEREF(__pyx_kp_u_TypeVar);
      PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_kp_u_TypeVar);
      __pyx_t_3 =
          __Pyx_PyObject_FormatSimple(__pyx_v_name, __pyx_empty_unicode);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_11 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3) > __pyx_t_11)
                       ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3)
                       : __pyx_t_11;
      __pyx_t_5 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_8, 2, __pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_INCREF(__pyx_kp_u__26);
      __pyx_t_5 += 1;
      __Pyx_GIVEREF(__pyx_kp_u__26);
      PyTuple_SET_ITEM(__pyx_t_8, 3, __pyx_kp_u__26);
      __pyx_t_3 =
          __Pyx_PyObject_FormatSimple(__pyx_v_types, __pyx_empty_unicode);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_11 = (__Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3) > __pyx_t_11)
                       ? __Pyx_PyUnicode_MAX_CHAR_VALUE(__pyx_t_3)
                       : __pyx_t_11;
      __pyx_t_5 += __Pyx_PyUnicode_GET_LENGTH(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_8, 4, __pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_INCREF(__pyx_kp_u__27);
      __pyx_t_5 += 1;
      __Pyx_GIVEREF(__pyx_kp_u__27);
      PyTuple_SET_ITEM(__pyx_t_8, 5, __pyx_kp_u__27);
      __pyx_t_3 = __Pyx_PyUnicode_Join(__pyx_t_8, 6, __pyx_t_5, __pyx_t_11);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      if (PyDict_SetItem(__pyx_t_7, __pyx_n_s_content, __pyx_t_3) < 0)
        __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_empty_tuple, __pyx_t_7);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 138, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_10);
      __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;

      /* "rfc.py":124
       *                     self.line('else ')
       *
       *             elif t.type == 'TYPE':             # <<<<<<<<<<<<<<
       *                 name = self.toks[i+1].value
       *                 i += 2
       */
      goto __pyx_L12;
    }

    /* "rfc.py":140
     *                 self.newline(content=f'{name} =
     * TypeVar("{name}"{types})')
     *
     *             elif t.type == 'NAME':             # <<<<<<<<<<<<<<
     *                 if t.value == 'r#type':
     *                     t.value = 'type'
     */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_type);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_n_u_NAME, Py_EQ));
    if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    if (__pyx_t_4) {
      /* "rfc.py":141
       *
       *             elif t.type == 'NAME':
       *                 if t.value == 'r#type':             # <<<<<<<<<<<<<<
       *                     t.value = 'type'
       *                 if t.value in self.foreign_keywords:
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 141, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_kp_u_r_type, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 141, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (__pyx_t_4) {
        /* "rfc.py":142
         *             elif t.type == 'NAME':
         *                 if t.value == 'r#type':
         *                     t.value = 'type'             # <<<<<<<<<<<<<<
         *                 if t.value in self.foreign_keywords:
         *                     raise ForeignKeywordException(t.value)
         */
        if (__Pyx_PyObject_SetAttrStr(__pyx_v_t, __pyx_n_s_value,
                                      __pyx_n_u_type) < 0)
          __PYX_ERR(0, 142, __pyx_L1_error)

        /* "rfc.py":141
         *
         *             elif t.type == 'NAME':
         *                 if t.value == 'r#type':             # <<<<<<<<<<<<<<
         *                     t.value = 'type'
         *                 if t.value in self.foreign_keywords:
         */
      }

      /* "rfc.py":143
       *                 if t.value == 'r#type':
       *                     t.value = 'type'
       *                 if t.value in self.foreign_keywords:             #
       * <<<<<<<<<<<<<< raise ForeignKeywordException(t.value) self.line(t.value
       * + ' ')
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 143, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_7 =
          __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_foreign_keywords);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 143, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_4 = (__Pyx_PySequence_ContainsTF(__pyx_t_3, __pyx_t_7, Py_EQ));
      if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 143, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_9 = (__pyx_t_4 != 0);
      if (__pyx_t_9) {
        /* "rfc.py":144
         *                     t.value = 'type'
         *                 if t.value in self.foreign_keywords:
         *                     raise ForeignKeywordException(t.value) #
         * <<<<<<<<<<<<<< self.line(t.value + ' ')
         *
         */
        __pyx_t_3 =
            __Pyx_GetModuleGlobalName(__pyx_n_s_ForeignKeywordException);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 144, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
        if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 144, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_8 = NULL;
        if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
          __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_3);
          if (likely(__pyx_t_8)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
            __Pyx_INCREF(__pyx_t_8);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_3, function);
          }
        }
        if (!__pyx_t_8) {
          __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_10);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 144, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_10);
          __pyx_t_10 = 0;
          __Pyx_GOTREF(__pyx_t_7);
        } else {
#if RFC_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_3)) {
            PyObject *__pyx_temp[2] = {__pyx_t_8, __pyx_t_10};
            __pyx_t_7 =
                __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 144, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_8);
            __pyx_t_8 = 0;
            __Pyx_GOTREF(__pyx_t_7);
            __Pyx_DECREF(__pyx_t_10);
            __pyx_t_10 = 0;
          } else
#endif
#if RFC_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
            PyObject *__pyx_temp[2] = {__pyx_t_8, __pyx_t_10};
            __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_3,
                                                   __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 144, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_8);
            __pyx_t_8 = 0;
            __Pyx_GOTREF(__pyx_t_7);
            __Pyx_DECREF(__pyx_t_10);
            __pyx_t_10 = 0;
          } else
#endif
          {
            __pyx_t_2 = PyTuple_New(1 + 1);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 144, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_GIVEREF(__pyx_t_8);
            PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_8);
            __pyx_t_8 = NULL;
            __Pyx_GIVEREF(__pyx_t_10);
            PyTuple_SET_ITEM(__pyx_t_2, 0 + 1, __pyx_t_10);
            __pyx_t_10 = 0;
            __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_2, NULL);
            if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 144, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_7);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_Raise(__pyx_t_7, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __PYX_ERR(0, 144, __pyx_L1_error)

        /* "rfc.py":143
         *                 if t.value == 'r#type':
         *                     t.value = 'type'
         *                 if t.value in self.foreign_keywords:             #
         * <<<<<<<<<<<<<< raise ForeignKeywordException(t.value)
         *                 self.line(t.value + ' ')
         */
      }

      /* "rfc.py":145
       *                 if t.value in self.foreign_keywords:
       *                     raise ForeignKeywordException(t.value)
       *                 self.line(t.value + ' ')             # <<<<<<<<<<<<<<
       *
       *             else:
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 145, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 145, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_10 = PyNumber_Add(__pyx_t_2, __pyx_kp_u__14);
      if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 145, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
        __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
        if (likely(__pyx_t_2)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
          __Pyx_INCREF(__pyx_t_2);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_3, function);
        }
      }
      if (!__pyx_t_2) {
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_10);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 145, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10);
        __pyx_t_10 = 0;
        __Pyx_GOTREF(__pyx_t_7);
      } else {
#if RFC_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_3)) {
          PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_10};
          __pyx_t_7 =
              __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 145, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF(__pyx_t_10);
          __pyx_t_10 = 0;
        } else
#endif
#if RFC_FAST_PYCCALL
            if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
          PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_10};
          __pyx_t_7 =
              __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 145, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF(__pyx_t_10);
          __pyx_t_10 = 0;
        } else
#endif
        {
          __pyx_t_8 = PyTuple_New(1 + 1);
          if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 145, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_8);
          __Pyx_GIVEREF(__pyx_t_2);
          PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_2);
          __pyx_t_2 = NULL;
          __Pyx_GIVEREF(__pyx_t_10);
          PyTuple_SET_ITEM(__pyx_t_8, 0 + 1, __pyx_t_10);
          __pyx_t_10 = 0;
          __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_8, NULL);
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 145, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_7);
          __Pyx_DECREF(__pyx_t_8);
          __pyx_t_8 = 0;
        }
      }
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;

      /* "rfc.py":140
       *                 self.newline(content=f'{name} =
       * TypeVar("{name}"{types})')
       *
       *             elif t.type == 'NAME':             # <<<<<<<<<<<<<<
       *                 if t.value == 'r#type':
       *                     t.value = 'type'
       */
      goto __pyx_L12;
    }

    /* "rfc.py":148
     *
     *             else:
     *                 if t.value == '&&':             # <<<<<<<<<<<<<<
     *                     self.line(' and ')
     *                 elif t.value == '||':
     */
    /*else*/ {
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_9 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_kp_u__28, Py_EQ));
      if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      if (__pyx_t_9) {
        /* "rfc.py":149
         *             else:
         *                 if t.value == '&&':
         *                     self.line(' and ')             # <<<<<<<<<<<<<<
         *                 elif t.value == '||':
         *                     self.line(' or ')
         */
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 149, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__29, NULL);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 149, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;

        /* "rfc.py":148
         *
         *             else:
         *                 if t.value == '&&':             # <<<<<<<<<<<<<<
         *                     self.line(' and ')
         *                 elif t.value == '||':
         */
        goto __pyx_L20;
      }

      /* "rfc.py":150
       *                 if t.value == '&&':
       *                     self.line(' and ')
       *                 elif t.value == '||':             # <<<<<<<<<<<<<<
       *                     self.line(' or ')
       *                 elif t.value == '!':
       */
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 150, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_9 = (__Pyx_PyUnicode_Equals(__pyx_t_3, __pyx_kp_u__30, Py_EQ));
      if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 150, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (__pyx_t_9) {
        /* "rfc.py":151
         *                     self.line(' and ')
         *                 elif t.value == '||':
         *                     self.line(' or ')             # <<<<<<<<<<<<<<
         *                 elif t.value == '!':
         *                     self.line(' not ')
         */
        __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 151, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__31, NULL);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 151, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;

        /* "rfc.py":150
         *                 if t.value == '&&':
         *                     self.line(' and ')
         *                 elif t.value == '||':             # <<<<<<<<<<<<<<
         *                     self.line(' or ')
         *                 elif t.value == '!':
         */
        goto __pyx_L20;
      }

      /* "rfc.py":152
       *                 elif t.value == '||':
       *                     self.line(' or ')
       *                 elif t.value == '!':             # <<<<<<<<<<<<<<
       *                     self.line(' not ')
       *                 else:
       */
      __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_t, __pyx_n_s_value);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_9 = (__Pyx_PyUnicode_Equals(__pyx_t_7, __pyx_kp_u__32, Py_EQ));
      if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      if (__pyx_t_9) {
        /* "rfc.py":153
         *                     self.line(' or ')
         *                 elif t.value == '!':
         *                     self.line(' not ')             # <<<<<<<<<<<<<<
         *                 else:
         *                     self.line(f'{t} ')
         */
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 153, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__33, NULL);
        if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 153, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;

        /* "rfc.py":152
         *                 elif t.value == '||':
         *                     self.line(' or ')
         *                 elif t.value == '!':             # <<<<<<<<<<<<<<
         *                     self.line(' not ')
         *                 else:
         */
        goto __pyx_L20;
      }

      /* "rfc.py":155
       *                     self.line(' not ')
       *                 else:
       *                     self.line(f'{t} ')             # <<<<<<<<<<<<<<
       *
       *             i += 1
       */
      /*else*/ {
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_line);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 155, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_8 = __Pyx_PyObject_FormatSimple(__pyx_v_t, __pyx_empty_unicode);
        if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 155, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __pyx_t_10 = __Pyx_PyUnicode_Concat(__pyx_t_8, __pyx_kp_u__14);
        if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 155, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_8);
        __pyx_t_8 = 0;
        __pyx_t_8 = NULL;
        if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_7))) {
          __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_7);
          if (likely(__pyx_t_8)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
            __Pyx_INCREF(__pyx_t_8);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_7, function);
          }
        }
        if (!__pyx_t_8) {
          __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_10);
          if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 155, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_10);
          __pyx_t_10 = 0;
          __Pyx_GOTREF(__pyx_t_3);
        } else {
#if RFC_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_8, __pyx_t_10};
            __pyx_t_3 =
                __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 155, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_8);
            __pyx_t_8 = 0;
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_10);
            __pyx_t_10 = 0;
          } else
#endif
#if RFC_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_8, __pyx_t_10};
            __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_7,
                                                   __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 155, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_8);
            __pyx_t_8 = 0;
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_10);
            __pyx_t_10 = 0;
          } else
#endif
          {
            __pyx_t_2 = PyTuple_New(1 + 1);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 155, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_GIVEREF(__pyx_t_8);
            PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_8);
            __pyx_t_8 = NULL;
            __Pyx_GIVEREF(__pyx_t_10);
            PyTuple_SET_ITEM(__pyx_t_2, 0 + 1, __pyx_t_10);
            __pyx_t_10 = 0;
            __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_2, NULL);
            if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 155, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
      }
    __pyx_L20:;
    }
  __pyx_L12:;

    /* "rfc.py":157
     *                     self.line(f'{t} ')
     *
     *             i += 1             # <<<<<<<<<<<<<<
     *
     *         self.output = ['  ' * e[0] + e[1].strip() for e in self.output]
     */
    __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 157, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_3);
    __pyx_t_3 = 0;
  __pyx_L3_continue:;
  }

  /* "rfc.py":159
   *             i += 1
   *
   *         self.output = ['  ' * e[0] + e[1].strip() for e in self.output] #
   * <<<<<<<<<<<<<< return '\n'.join(self.output)
   *
   */
  { /* enter inner scope */
    PyObject *__pyx_7genexpr__pyx_v_e = NULL;
    __pyx_t_3 = PyList_New(0);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 159, __pyx_L23_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_output);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (likely(PyList_CheckExact(__pyx_t_7)) || PyTuple_CheckExact(__pyx_t_7)) {
      __pyx_t_2 = __pyx_t_7;
      __Pyx_INCREF(__pyx_t_2);
      __pyx_t_5 = 0;
      __pyx_t_6 = NULL;
    } else {
      __pyx_t_5 = -1;
      __pyx_t_2 = PyObject_GetIter(__pyx_t_7);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_6 = Py_TYPE(__pyx_t_2)->tp_iternext;
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 159, __pyx_L23_error)
    }
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    for (;;) {
      if (likely(!__pyx_t_6)) {
        if (likely(PyList_CheckExact(__pyx_t_2))) {
          if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_2)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_7 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_5);
          __Pyx_INCREF(__pyx_t_7);
          __pyx_t_5++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 159, __pyx_L23_error)
#else
          __pyx_t_7 = PySequence_ITEM(__pyx_t_2, __pyx_t_5);
          __pyx_t_5++;
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
          __Pyx_GOTREF(__pyx_t_7);
#endif
        } else {
          if (__pyx_t_5 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_7 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_5);
          __Pyx_INCREF(__pyx_t_7);
          __pyx_t_5++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 159, __pyx_L23_error)
#else
          __pyx_t_7 = PySequence_ITEM(__pyx_t_2, __pyx_t_5);
          __pyx_t_5++;
          if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
          __Pyx_GOTREF(__pyx_t_7);
#endif
        }
      } else {
        __pyx_t_7 = __pyx_t_6(__pyx_t_2);
        if (unlikely(!__pyx_t_7)) {
          PyObject *exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(
                    exc_type == PyExc_StopIteration ||
                    PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
              PyErr_Clear();
            else
              __PYX_ERR(0, 159, __pyx_L23_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_7);
      }
      __Pyx_XDECREF_SET(__pyx_7genexpr__pyx_v_e, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = __Pyx_GetItemInt(__pyx_7genexpr__pyx_v_e, 0, long, 1,
                                   __Pyx_PyInt_From_long, 0, 0, 1);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_10 = PyNumber_Multiply(__pyx_kp_u__34, __pyx_t_7);
      if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_8 = __Pyx_GetItemInt(__pyx_7genexpr__pyx_v_e, 1, long, 1,
                                   __Pyx_PyInt_From_long, 0, 0, 1);
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_8);
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_strip);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
      __pyx_t_8 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
        __pyx_t_8 = PyMethod_GET_SELF(__pyx_t_1);
        if (likely(__pyx_t_8)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_1);
          __Pyx_INCREF(__pyx_t_8);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_1, function);
        }
      }
      if (__pyx_t_8) {
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_8);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
        __Pyx_DECREF(__pyx_t_8);
        __pyx_t_8 = 0;
      } else {
        __pyx_t_7 = __Pyx_PyObject_CallNoArg(__pyx_t_1);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 159, __pyx_L23_error)
      }
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_t_1 = PyNumber_Add(__pyx_t_10, __pyx_t_7);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_10);
      __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      if (unlikely(__Pyx_ListComp_Append(__pyx_t_3, (PyObject *)__pyx_t_1)))
        __PYX_ERR(0, 159, __pyx_L23_error)
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
    }
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_7genexpr__pyx_v_e);
    goto __pyx_L26_exit_scope;
  __pyx_L23_error:;
    __Pyx_XDECREF(__pyx_7genexpr__pyx_v_e);
    goto __pyx_L1_error;
  __pyx_L26_exit_scope:;
  } /* exit inner scope */
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_output, __pyx_t_3) < 0)
    __PYX_ERR(0, 159, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;

  /* "rfc.py":160
   *
   *         self.output = ['  ' * e[0] + e[1].strip() for e in self.output]
   *         return '\n'.join(self.output)             # <<<<<<<<<<<<<<
   *
   *
   */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_output);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyUnicode_Join(__pyx_kp_u__35, __pyx_t_3);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_r = __pyx_t_2;
  __pyx_t_2 = 0;
  goto __pyx_L0;

/* "rfc.py":83
 *
 *
 *     def gen(self):             # <<<<<<<<<<<<<<
 *         i = 0
 *
 */

/* function exit code */
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_AddTraceback("rfc.Codegen.gen", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_XDECREF(__pyx_v_alias);
  __Pyx_XDECREF(__pyx_v_rf);
  __Pyx_XDECREF(__pyx_v_py);
  __Pyx_XDECREF(__pyx_v_name);
  __Pyx_XDECREF(__pyx_v_types);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":163
 *
 *
 * def gen(toks, parsed):             # <<<<<<<<<<<<<<
 *     cg = Codegen(toks, parsed)
 *     return cg.gen()
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_1gen(PyObject *__pyx_self, PyObject *__pyx_args,
                                    PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_1gen = {
    "gen", (PyCFunction)__pyx_pw_3rfc_1gen, METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_1gen(PyObject *__pyx_self, PyObject *__pyx_args,
                                    PyObject *__pyx_kwds) {
  PyObject *__pyx_v_toks = 0;
  PyObject *__pyx_v_parsed = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("gen (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_toks, &__pyx_n_s_parsed,
                                            0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_toks)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] =
                          PyDict_GetItem(__pyx_kwds, __pyx_n_s_parsed)) != 0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("gen", 1, 2, 2, 1);
            __PYX_ERR(0, 163, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "gen") < 0))
          __PYX_ERR(0, 163, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_toks = values[0];
    __pyx_v_parsed = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("gen", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 163, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.gen", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_gen(__pyx_self, __pyx_v_toks, __pyx_v_parsed);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_gen(RFC_UNUSED PyObject *__pyx_self,
                                   PyObject *__pyx_v_toks,
                                   PyObject *__pyx_v_parsed) {
  PyObject *__pyx_v_cg = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  __Pyx_RefNannySetupContext("gen", 0);

  /* "rfc.py":164
   *
   * def gen(toks, parsed):
   *     cg = Codegen(toks, parsed)             # <<<<<<<<<<<<<<
   *     return cg.gen()
   *
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Codegen);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 164, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = NULL;
  __pyx_t_4 = 0;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_4 = 1;
    }
  }
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp + 1 - __pyx_t_4,
                                          2 + __pyx_t_4);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 164, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(
        __pyx_t_2, __pyx_temp + 1 - __pyx_t_4, 2 + __pyx_t_4);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 164, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3);
    __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
#endif
  {
    __pyx_t_5 = PyTuple_New(2 + __pyx_t_4);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 164, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (__pyx_t_3) {
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3);
      __pyx_t_3 = NULL;
    }
    __Pyx_INCREF(__pyx_v_toks);
    __Pyx_GIVEREF(__pyx_v_toks);
    PyTuple_SET_ITEM(__pyx_t_5, 0 + __pyx_t_4, __pyx_v_toks);
    __Pyx_INCREF(__pyx_v_parsed);
    __Pyx_GIVEREF(__pyx_v_parsed);
    PyTuple_SET_ITEM(__pyx_t_5, 1 + __pyx_t_4, __pyx_v_parsed);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 164, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_v_cg = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "rfc.py":165
   * def gen(toks, parsed):
   *     cg = Codegen(toks, parsed)
   *     return cg.gen()             # <<<<<<<<<<<<<<
   *
   *
   */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_cg, __pyx_n_s_gen);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 165, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = NULL;
  if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_5) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_5);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 165, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 165, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

/* "rfc.py":163
 *
 *
 * def gen(toks, parsed):             # <<<<<<<<<<<<<<
 *     cg = Codegen(toks, parsed)
 *     return cg.gen()
 */

/* function exit code */
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("rfc.gen", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_cg);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":172
 * class Parser(Transformer):
 *
 *     def __init__(self):             # <<<<<<<<<<<<<<
 *         self.decorator_tokens = []
 *         self.suite_tokens = []
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_6Parser_1__init__(
    PyObject *__pyx_self, PyObject *__pyx_v_self); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_6Parser_1__init__ = {
    "__init__", (PyCFunction)__pyx_pw_3rfc_6Parser_1__init__, METH_O, 0};
static PyObject *__pyx_pw_3rfc_6Parser_1__init__(PyObject *__pyx_self,
                                                 PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("__init__ (wrapper)",
                                                        0);
  __pyx_r =
      __pyx_pf_3rfc_6Parser___init__(__pyx_self, ((PyObject *)__pyx_v_self));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_6Parser___init__(RFC_UNUSED PyObject *__pyx_self,
                                                PyObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "rfc.py":173
   *
   *     def __init__(self):
   *         self.decorator_tokens = []             # <<<<<<<<<<<<<<
   *         self.suite_tokens = []
   *
   */
  __pyx_t_1 = PyList_New(0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 173, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_decorator_tokens,
                                __pyx_t_1) < 0)
    __PYX_ERR(0, 173, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":174
   *     def __init__(self):
   *         self.decorator_tokens = []
   *         self.suite_tokens = []             # <<<<<<<<<<<<<<
   *
   *     def start(self, _):
   */
  __pyx_t_1 = PyList_New(0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 174, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens,
                                __pyx_t_1) < 0)
    __PYX_ERR(0, 174, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":172
   * class Parser(Transformer):
   *
   *     def __init__(self):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens = []
   *         self.suite_tokens = []
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("rfc.Parser.__init__", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":176
 *         self.suite_tokens = []
 *
 *     def start(self, _):             # <<<<<<<<<<<<<<
 *         return {
 *             'decorated': self.decorator_tokens,
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_6Parser_3start(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_6Parser_3start = {
    "start", (PyCFunction)__pyx_pw_3rfc_6Parser_3start,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_6Parser_3start(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  RFC_UNUSED PyObject *__pyx_v__ = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("start (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s__36, 0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__36)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("start", 1, 2, 2, 1);
            __PYX_ERR(0, 176, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "start") < 0))
          __PYX_ERR(0, 176, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v__ = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("start", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 176, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Parser.start", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_6Parser_2start(__pyx_self, __pyx_v_self, __pyx_v__);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_6Parser_2start(RFC_UNUSED PyObject *__pyx_self,
                                              PyObject *__pyx_v_self,
                                              RFC_UNUSED PyObject *__pyx_v__) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  __Pyx_RefNannySetupContext("start", 0);

  /* "rfc.py":177
   *
   *     def start(self, _):
   *         return {             # <<<<<<<<<<<<<<
   *             'decorated': self.decorator_tokens,
   *             'suite': self.suite_tokens,
   */
  __Pyx_XDECREF(__pyx_r);

  /* "rfc.py":178
   *     def start(self, _):
   *         return {
   *             'decorated': self.decorator_tokens,             #
   * <<<<<<<<<<<<<< 'suite': self.suite_tokens,
   *         }
   */
  __pyx_t_1 = PyDict_New();
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 178, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_decorator_tokens);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 178, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_u_decorated, __pyx_t_2) < 0)
    __PYX_ERR(0, 178, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":179
   *         return {
   *             'decorated': self.decorator_tokens,
   *             'suite': self.suite_tokens,             # <<<<<<<<<<<<<<
   *         }
   *
   */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 179, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_u_suite, __pyx_t_2) < 0)
    __PYX_ERR(0, 178, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

/* "rfc.py":176
 *         self.suite_tokens = []
 *
 *     def start(self, _):             # <<<<<<<<<<<<<<
 *         return {
 *             'decorated': self.decorator_tokens,
 */

/* function exit code */
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("rfc.Parser.start", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":182
 *         }
 *
 *     def decorator(self, _):             # <<<<<<<<<<<<<<
 *         self.decorator_tokens += [_[0], _[1], _[-1]]
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_6Parser_5decorator(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_6Parser_5decorator = {
    "decorator", (PyCFunction)__pyx_pw_3rfc_6Parser_5decorator,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_6Parser_5decorator(PyObject *__pyx_self,
                                                  PyObject *__pyx_args,
                                                  PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v__ = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("decorator (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s__36, 0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__36)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("decorator", 1, 2, 2, 1);
            __PYX_ERR(0, 182, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "decorator") < 0))
          __PYX_ERR(0, 182, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v__ = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("decorator", 1, 2, 2,
                             PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 182, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Parser.decorator", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r =
      __pyx_pf_3rfc_6Parser_4decorator(__pyx_self, __pyx_v_self, __pyx_v__);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_6Parser_4decorator(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v__) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  __Pyx_RefNannySetupContext("decorator", 0);

  /* "rfc.py":183
   *
   *     def decorator(self, _):
   *         self.decorator_tokens += [_[0], _[1], _[-1]]             #
   * <<<<<<<<<<<<<<
   *
   *     def suite(self, _):
   */
  __pyx_t_1 =
      __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_decorator_tokens);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_GetItemInt(__pyx_v__, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 =
      __Pyx_GetItemInt(__pyx_v__, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 =
      __Pyx_GetItemInt(__pyx_v__, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyList_New(3);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_2);
  PyList_SET_ITEM(__pyx_t_5, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyList_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_5);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_decorator_tokens,
                                __pyx_t_4) < 0)
    __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;

  /* "rfc.py":182
   *         }
   *
   *     def decorator(self, _):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("rfc.Parser.decorator", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":185
 *         self.decorator_tokens += [_[0], _[1], _[-1]]
 *
 *     def suite(self, _):             # <<<<<<<<<<<<<<
 *         self.suite_tokens += [_[0], _[-1]]
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_6Parser_7suite(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_6Parser_7suite = {
    "suite", (PyCFunction)__pyx_pw_3rfc_6Parser_7suite,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_6Parser_7suite(PyObject *__pyx_self,
                                              PyObject *__pyx_args,
                                              PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v__ = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("suite (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s__36, 0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__36)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("suite", 1, 2, 2, 1);
            __PYX_ERR(0, 185, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "suite") < 0))
          __PYX_ERR(0, 185, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v__ = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("suite", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 185, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Parser.suite", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_3rfc_6Parser_6suite(__pyx_self, __pyx_v_self, __pyx_v__);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_6Parser_6suite(RFC_UNUSED PyObject *__pyx_self,
                                              PyObject *__pyx_v_self,
                                              PyObject *__pyx_v__) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  __Pyx_RefNannySetupContext("suite", 0);

  /* "rfc.py":186
   *
   *     def suite(self, _):
   *         self.suite_tokens += [_[0], _[-1]]             # <<<<<<<<<<<<<<
   *
   *     def class_suite(self, _):
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_GetItemInt(__pyx_v__, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 =
      __Pyx_GetItemInt(__pyx_v__, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyList_New(2);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_2);
  PyList_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_4);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens,
                                __pyx_t_3) < 0)
    __PYX_ERR(0, 186, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;

  /* "rfc.py":185
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   *     def suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("rfc.Parser.suite", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":188
 *         self.suite_tokens += [_[0], _[-1]]
 *
 *     def class_suite(self, _):             # <<<<<<<<<<<<<<
 *         self.suite_tokens += [_[0], _[-1]]
 *
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_6Parser_9class_suite(
    PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_6Parser_9class_suite = {
    "class_suite", (PyCFunction)__pyx_pw_3rfc_6Parser_9class_suite,
    METH_VARARGS | METH_KEYWORDS, 0};
static PyObject *__pyx_pw_3rfc_6Parser_9class_suite(PyObject *__pyx_self,
                                                    PyObject *__pyx_args,
                                                    PyObject *__pyx_kwds) {
  PyObject *__pyx_v_self = 0;
  PyObject *__pyx_v__ = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("class_suite (wrapper)",
                                                        0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_self, &__pyx_n_s__36, 0};
    PyObject *values[2] = {0, 0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 2:
          values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
          RFC_FALLTHROUGH;
        case 1:
          values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
          RFC_FALLTHROUGH;
        case 0:
          break;
        default:
          goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case 0:
          if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_self)) !=
                     0))
            kw_args--;
          else
            goto __pyx_L5_argtuple_error;
          RFC_FALLTHROUGH;
        case 1:
          if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__36)) !=
                     0))
            kw_args--;
          else {
            __Pyx_RaiseArgtupleInvalid("class_suite", 1, 2, 2, 1);
            __PYX_ERR(0, 188, __pyx_L3_error)
          }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames,
                                                 0, values, pos_args,
                                                 "class_suite") < 0))
          __PYX_ERR(0, 188, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_self = values[0];
    __pyx_v__ = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
__pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("class_suite", 1, 2, 2,
                             PyTuple_GET_SIZE(__pyx_args));
  __PYX_ERR(0, 188, __pyx_L3_error)
__pyx_L3_error:;
  __Pyx_AddTraceback("rfc.Parser.class_suite", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
__pyx_L4_argument_unpacking_done:;
  __pyx_r =
      __pyx_pf_3rfc_6Parser_8class_suite(__pyx_self, __pyx_v_self, __pyx_v__);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_6Parser_8class_suite(
    RFC_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_self,
    PyObject *__pyx_v__) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  __Pyx_RefNannySetupContext("class_suite", 0);

  /* "rfc.py":189
   *
   *     def class_suite(self, _):
   *         self.suite_tokens += [_[0], _[-1]]             # <<<<<<<<<<<<<<
   *
   * grammar = 'start: (typedef | funcdef | decorated | (import_stmt ";") |
   * classdef | async_funcdef)*\n\n!decorator: "#" "[" dotted_name [ "("
   * [arguments] ")" ] "]"\ndecorators: decorator+\ndecorated: decorators
   * (classdef | funcdef | async_funcdef)\n\ntypedef: "type" NAME [(":"
   * typelist) | ("=" type)] ";"\ntype: (dotted_name ["[" typelist "]"]) |
   * "None"\ntypelist: type ("," type)*\n\nasync_funcdef: "async"
   * funcdef\nfuncdef: "fn" NAME "(" parameters? ")" ["->" type]
   * suite\nstruct_funcdef: "fn" NAME "(" "self" ["," parameters] ")" ["->"
   * type] suite\n\nparameters: paramvalue ("," paramvalue)* ["," [ starparams |
   * kwparams]]\n        | starparams\n          | kwparams\nstarparams: "*"
   * typedparam? ("," paramvalue)* ["," kwparams]\nkwparams: "**"
   * typedparam\n\n?paramvalue: typedparam ["=" test]\n?typedparam: NAME ":"
   * type\n\nvarargslist: (vfpdef ["=" test] ("," vfpdef ["=" test])* ["," [ "*"
   * [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef [","]]] | "**" vfpdef
   * [","]]]\n  | "*" [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef
   * [","]]]\n  | "**" vfpdef [","])\n\nvfpdef: NAME\n\n?stmt: simple_stmt |
   * compound_stmt\n?simple_stmt: small_stmt ";"\n?small_stmt: (expr_stmt |
   * del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: testlist_star_expr
   * (annassign | augassign (yield_expr|testlist)\n         | ("="
   * (yield_expr|testlist_star_expr))*)\nannassign: ":" type "="
   * test\n?testlist_star_expr: (test|star_expr) ("," (test|star_expr))*
   * [","]\n!augassign: ("+=" | "-=" | "*=" | "@=" | "/=" | "%=" | "&=" | "|=" |
   * "^=" | "<<=" | ">>=" | "**=")\ndel_stmt: "del" exprlist\n?flow_stmt:
   * break_stmt | continue_stmt | return_stmt | raise_stmt |
   * yield_stmt\nbreak_stmt: "break"\ncontinue_stmt: "continue"\nreturn_stmt:
   * "return" [testlist]\nyield_stmt: yield_expr\nraise_stmt: "raise" [test
   * ["from" test]]\nimport_stmt: import_name | import_from\nimport_name: "use"
   * dotted_as_names\nimport_from: "from" dotted_name "use" ("*" | "("
   * import_as_names ")" | import_as_names)\nimport_as_name: NAME ["as"
   * NAME]\ndotted_as_name: dotted_name ["as" NAME]\nimport_as_names:
   * import_as_name ("," import_as_name)* [","]\ndotted_as_names: dotted_as_name
   * ("," dotted_as_name)*\ndotted_name: NAME ("." NAME)*\nassert_stmt: "assert"
   * test ["," test]\n\ncompound_stmt: if_stmt | while_stmt | for_stmt |
   * try_stmt | with_stmt | typedef | funcdef | classdef | decorated |
   * async_stmt\nasync_stmt: "async" (funcdef | with_stmt | for_stmt)\nif_stmt:
   * "if" test suite ("else" "if" test suite)* ["else" suite]\nwhile_stmt:
   * "while" test suite ["else" suite]\nfor_stmt: "for" exprlist "in" testlist
   * suite ["else" suite]\ntry_stmt: ("try" suite ((except_clause suite)+
   * ["else" suite] ["finally" suite] | "finally" suite))\nwith_stmt: "with"
   * with_item ("," with_item)*  suite\nwith_item: test ["as"
   * expr]\nexcept_clause: "except" [test ["as" NAME]]\n!suite: "{" stmt*
   * "}"\n\n?test: or_test ("if" or_test "else" test)? | lambdef\n?test_nocond:
   * or_test | lambdef_nocond\nlambdef: "lambda" [varargslist] ":"
   * test\nlambdef_nocond: "lambda" [varargslist] ":" test_nocond\n?or_test:
   * and_test ("||" and_test)*\n?and_test: not_test ("&&" not_test)*\n?not_test:
   * "!" not_test -> not\n         | comparison\n?comparison: expr (_comp_op
   * expr)*\nstar_expr: "*" expr\n?expr: xor_expr ("|" xor_expr)*\n?xor_expr:
   * and_expr ("^" and_expr)*\n?and_expr: shift_expr ("&"
   * shift_expr)*\n?shift_expr: arith_expr (_shift_op arith_expr)*\n?arith_expr:
   * term (_add_op term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op
   * factor | power\n\n!_factor_op: "+"|"-"|"~"\n!_add_op: "+"|"-"\n!_shift_op:
   * "<<"|">>"\n!_mul_op: "*"|"@"|"/"|"%"|"//"\n!_comp_op:
   * "<"|">"|"=="|">="|"<="|"!="|"in"|"is"\n\n?power: await_expr ("**"
   * factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "await"\n\n?atom_expr:
   * atom_expr "(" [arguments] ")"      -> funccall\n          | atom_expr "["
   * subscriptlist "]"  -> getitem\n          | atom_expr "." NAME -> getattr\n
   * | atom\n\n?atom: "(" [yield_expr|testlist_comp] ")" -> tuple\n     | "["
   * [testlist_comp] "]"  -> list\n     | "{" [dictorsetmaker] "}" -> dict\n |
   * NAME -> var\n     | number | string+\n     | "(" test ")"\n     | "..." ->
   * ellipsis\n     | "None"    -> const_none\n     | "true"    -> const_true\n
   * | "false"   -> const_false\n\n?testlist_comp: (test|star_expr) [comp_for |
   * ("," (test|star_expr))+ [","] | ","]\nsubscriptlist: subscript (","
   * subscript)* [","]\nsubscript: test | [test] ":" [test] [sliceop]\nsliceop:
   * ":" [test]\nexprlist: (expr|star_expr) ("," (expr|star_expr))*
   * [","]\ntestlist: test ("," test)* [","]\ndictorsetmaker: ( ((test ":" test
   * | "**" expr) (comp_for | ("," (test ":" test | "**" expr))* [","])) |
   * ((test | star_expr) (comp_for | ("," (test | star_expr))* [","]))
   * )\n\nclassdef: "struct" NAME ["(" [arguments] ")"]
   * class_suite\n!class_suite: "{" (struct_funcdef | funcdef | decorated)*
   * "}"\n\narguments: argvalue ("," argvalue)*  ("," [ starargs | kwargs])?\n
   * | starargs\n        | kwargs\n         | test comp_for\n\nstarargs: "*"
   * test ("," "*" test)* ("," argvalue)* ["," kwargs]\nkwargs: "**"
   * test\n\n?argvalue: test ("=" test)?\n\n\n\ncomp_iter: comp_for | comp_if |
   * async_for\nasync_for: "async" "for" exprlist "in" or_test
   * [comp_iter]\ncomp_for: "for" exprlist "in" or_test [comp_iter]\ncomp_if:
   * "if" test_nocond [comp_iter]\n\nyield_expr: "yield" [yield_arg]\nyield_arg:
   * "from" test | testlist\n\n\nnumber: DEC_NUMBER | HEX_NUMBER | BIN_NUMBER |
   * OCT_NUMBER | FLOAT_NUMBER | IMAG_NUMBER\nstring: STRING |
   * LONG_STRING\n\nNAME: /(r#)?[a-zA-Z_]\\w*[inserted by RFC to avoid comment
   * closer]/\nCOMMENT: /\\/\\/[^\\n]*[inserted by RFC to avoid comment
   * closer]/\n_NEWLINE: ( /\\r?\\n[\\t ]*[inserted by RFC to avoid comment
   * closer]/ | COMMENT )+\n\n\nSTRING :
   * /[ubf]?r?("(?!"").*?(?<!\\\\)(\\\\\\\\)*?"|\'(?!\'\').*?(?<!\\\\)(\\\\\\\\)*?\')/i\nLONG_STRING:
   * /[ubf]?r?(""".*?(?<!\\\\)(\\\\\\\\)*?"""|\'\'\'.*?(?<!\\\\)(\\\\\\\\)*?\'\'\')/is\n\nDEC_NUMBER:
   * /0|[1-9]\\d*[inserted by RFC to avoid comment closer]/i\nHEX_NUMBER.2:
   * /0x[\\da-f]*[inserted by RFC to avoid comment closer]/i\nOCT_NUMBER.2:
   * /0o[0-7]*[inserted by RFC to avoid comment closer]/i\nBIN_NUMBER.2 :
   * /0b[0-1]*[inserted by RFC to avoid comment closer]/i\nFLOAT_NUMBER.2:
   * /((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2:
   * /\\d+j/i | FLOAT_NUMBER "j"i\n\n%ignore /[\\t \\f]+/\n%ignore _NEWLINE\n'
   */
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 =
      __Pyx_GetItemInt(__pyx_v__, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 =
      __Pyx_GetItemInt(__pyx_v__, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyList_New(2);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_2);
  PyList_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_4, 1, __pyx_t_3);
  __pyx_t_2 = 0;
  __pyx_t_3 = 0;
  __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_4);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_self, __pyx_n_s_suite_tokens,
                                __pyx_t_3) < 0)
    __PYX_ERR(0, 189, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;

  /* "rfc.py":188
   *         self.suite_tokens += [_[0], _[-1]]
   *
   *     def class_suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */

  /* function exit code */
  __pyx_r = Py_None;
  __Pyx_INCREF(Py_None);
  goto __pyx_L0;
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("rfc.Parser.class_suite", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":201
 *
 *
 * def compile(code):             # <<<<<<<<<<<<<<
 *     toks = parser.lex(code)
 *     parsed = parser.parse(code)
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_3compile(PyObject *__pyx_self,
                                        PyObject *__pyx_v_code); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_3compile = {
    "compile", (PyCFunction)__pyx_pw_3rfc_3compile, METH_O, 0};
static PyObject *__pyx_pw_3rfc_3compile(PyObject *__pyx_self,
                                        PyObject *__pyx_v_code) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext("compile (wrapper)", 0);
  __pyx_r = __pyx_pf_3rfc_2compile(__pyx_self, ((PyObject *)__pyx_v_code));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_2compile(RFC_UNUSED PyObject *__pyx_self,
                                        PyObject *__pyx_v_code) {
  PyObject *__pyx_v_toks = NULL;
  PyObject *__pyx_v_parsed = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  __Pyx_RefNannySetupContext("compile", 0);

  /* "rfc.py":202
   *
   * def compile(code):
   *     toks = parser.lex(code)             # <<<<<<<<<<<<<<
   *     parsed = parser.parse(code)
   *     return gen(toks, parsed)
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_parser);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 202, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_lex);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 202, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_code);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
#if RFC_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_code};
      __pyx_t_1 =
          __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
#endif
#if RFC_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_code};
      __pyx_t_1 =
          __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
#endif
    {
      __pyx_t_4 = PyTuple_New(1 + 1);
      if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
      __pyx_t_2 = NULL;
      __Pyx_INCREF(__pyx_v_code);
      __Pyx_GIVEREF(__pyx_v_code);
      PyTuple_SET_ITEM(__pyx_t_4, 0 + 1, __pyx_v_code);
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_4, NULL);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 202, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_v_toks = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "rfc.py":203
   * def compile(code):
   *     toks = parser.lex(code)
   *     parsed = parser.parse(code)             # <<<<<<<<<<<<<<
   *     return gen(toks, parsed)
   *
   */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_parser);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 203, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_parse);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 203, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_code);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
#if RFC_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_code};
      __pyx_t_1 =
          __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 203, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
#endif
#if RFC_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_code};
      __pyx_t_1 =
          __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 203, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
#endif
    {
      __pyx_t_2 = PyTuple_New(1 + 1);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 203, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
      __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_code);
      __Pyx_GIVEREF(__pyx_v_code);
      PyTuple_SET_ITEM(__pyx_t_2, 0 + 1, __pyx_v_code);
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, NULL);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 203, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_v_parsed = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "rfc.py":204
   *     toks = parser.lex(code)
   *     parsed = parser.parse(code)
   *     return gen(toks, parsed)             # <<<<<<<<<<<<<<
   *
   *
   */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_gen);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 204, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = NULL;
  __pyx_t_5 = 0;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_2)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
      __pyx_t_5 = 1;
    }
  }
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[3] = {__pyx_t_2, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - __pyx_t_5,
                                          2 + __pyx_t_5);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 204, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[3] = {__pyx_t_2, __pyx_v_toks, __pyx_v_parsed};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(
        __pyx_t_4, __pyx_temp + 1 - __pyx_t_5, 2 + __pyx_t_5);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 204, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
#endif
  {
    __pyx_t_3 = PyTuple_New(2 + __pyx_t_5);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 204, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (__pyx_t_2) {
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
      __pyx_t_2 = NULL;
    }
    __Pyx_INCREF(__pyx_v_toks);
    __Pyx_GIVEREF(__pyx_v_toks);
    PyTuple_SET_ITEM(__pyx_t_3, 0 + __pyx_t_5, __pyx_v_toks);
    __Pyx_INCREF(__pyx_v_parsed);
    __Pyx_GIVEREF(__pyx_v_parsed);
    PyTuple_SET_ITEM(__pyx_t_3, 1 + __pyx_t_5, __pyx_v_parsed);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_3, NULL);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 204, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3);
    __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

/* "rfc.py":201
 *
 *
 * def compile(code):             # <<<<<<<<<<<<<<
 *     toks = parser.lex(code)
 *     parsed = parser.parse(code)
 */

/* function exit code */
__pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("rfc.compile", __pyx_clineno, __pyx_lineno,
                     __pyx_filename);
  __pyx_r = NULL;
__pyx_L0:;
  __Pyx_XDECREF(__pyx_v_toks);
  __Pyx_XDECREF(__pyx_v_parsed);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "rfc.py":207
 *
 *
 * def compile_file(filename):             # <<<<<<<<<<<<<<
 *     with open(filename) as file:
 *         code = file.read()
 */

/* Python wrapper */
static PyObject *__pyx_pw_3rfc_5compile_file(
    PyObject *__pyx_self, PyObject *__pyx_v_filename); /*proto*/
static PyMethodDef __pyx_mdef_3rfc_5compile_file = {
    "compile_file", (PyCFunction)__pyx_pw_3rfc_5compile_file, METH_O, 0};
static PyObject *__pyx_pw_3rfc_5compile_file(PyObject *__pyx_self,
                                             PyObject *__pyx_v_filename) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext(
      "compile_file (wrapper)", 0);
  __pyx_r =
      __pyx_pf_3rfc_4compile_file(__pyx_self, ((PyObject *)__pyx_v_filename));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_3rfc_4compile_file(RFC_UNUSED PyObject *__pyx_self,
                                             PyObject *__pyx_v_filename) {
  PyObject *__pyx_v_file = NULL;
  PyObject *__pyx_v_code = NULL;
  PyObject *__pyx_v_output = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  int __pyx_t_11;
  PyObject *__pyx_t_12 = NULL;
  __Pyx_RefNannySetupContext("compile_file", 0);

  /* "rfc.py":208
   *
   * def compile_file(filename):
   *     with open(filename) as file:             # <<<<<<<<<<<<<<
   *         code = file.read()
   *         output = compile(code)
   */
  /*with:*/ {
    __pyx_t_1 = PyTuple_New(1);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_filename);
    __Pyx_GIVEREF(__pyx_v_filename);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_filename);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_1, NULL);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_3 = __Pyx_PyObject_LookupSpecial(__pyx_t_2, __pyx_n_s_exit);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = __Pyx_PyObject_LookupSpecial(__pyx_t_2, __pyx_n_s_enter);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 208, __pyx_L3_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = NULL;
    if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_5)) {
        PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
      }
    }
    if (__pyx_t_5) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_5);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L3_error)
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_4);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L3_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = __pyx_t_1;
    __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    /*try:*/ {{__Pyx_PyThreadState_declare __Pyx_PyThreadState_assign
                   __Pyx_ExceptionSave(&__pyx_t_6, &__pyx_t_7, &__pyx_t_8);
    __Pyx_XGOTREF(__pyx_t_6);
    __Pyx_XGOTREF(__pyx_t_7);
    __Pyx_XGOTREF(__pyx_t_8);
    /*try:*/ {
      __pyx_v_file = __pyx_t_4;
      __pyx_t_4 = 0;

      /* "rfc.py":209
       * def compile_file(filename):
       *     with open(filename) as file:
       *         code = file.read()             # <<<<<<<<<<<<<<
       *         output = compile(code)
       *     assert filename[-3:] == '.rf'
       */
      __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_file, __pyx_n_s_read);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 209, __pyx_L7_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_1 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
        __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_2);
        if (likely(__pyx_t_1)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
          __Pyx_INCREF(__pyx_t_1);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_2, function);
        }
      }
      if (__pyx_t_1) {
        __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_1);
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 209, __pyx_L7_error)
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
      } else {
        __pyx_t_4 = __Pyx_PyObject_CallNoArg(__pyx_t_2);
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 209, __pyx_L7_error)
      }
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_v_code = __pyx_t_4;
      __pyx_t_4 = 0;

      /* "rfc.py":210
       *     with open(filename) as file:
       *         code = file.read()
       *         output = compile(code)             # <<<<<<<<<<<<<<
       *     assert filename[-3:] == '.rf'
       *     return (filename[:-3] + '.py', FormatCode(output)[0])
       */
      __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_compile);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 210, __pyx_L7_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_1 = NULL;
      if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
        __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_2);
        if (likely(__pyx_t_1)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
          __Pyx_INCREF(__pyx_t_1);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_2, function);
        }
      }
      if (!__pyx_t_1) {
        __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_code);
        if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 210, __pyx_L7_error)
        __Pyx_GOTREF(__pyx_t_4);
      } else {
#if RFC_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_2)) {
          PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_code};
          __pyx_t_4 =
              __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 210, __pyx_L7_error)
          __Pyx_XDECREF(__pyx_t_1);
          __pyx_t_1 = 0;
          __Pyx_GOTREF(__pyx_t_4);
        } else
#endif
#if RFC_FAST_PYCCALL
            if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
          PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_code};
          __pyx_t_4 =
              __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 210, __pyx_L7_error)
          __Pyx_XDECREF(__pyx_t_1);
          __pyx_t_1 = 0;
          __Pyx_GOTREF(__pyx_t_4);
        } else
#endif
        {
          __pyx_t_5 = PyTuple_New(1 + 1);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 210, __pyx_L7_error)
          __Pyx_GOTREF(__pyx_t_5);
          __Pyx_GIVEREF(__pyx_t_1);
          PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
          __pyx_t_1 = NULL;
          __Pyx_INCREF(__pyx_v_code);
          __Pyx_GIVEREF(__pyx_v_code);
          PyTuple_SET_ITEM(__pyx_t_5, 0 + 1, __pyx_v_code);
          __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL);
          if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 210, __pyx_L7_error)
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
        }
      }
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_v_output = __pyx_t_4;
      __pyx_t_4 = 0;

      /* "rfc.py":208
       *
       * def compile_file(filename):
       *     with open(filename) as file:             # <<<<<<<<<<<<<<
       *         code = file.read()
       *         output = compile(code)
       */
    }
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_XDECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    __Pyx_XDECREF(__pyx_t_8);
    __pyx_t_8 = 0;
    goto __pyx_L12_try_end;
  __pyx_L7_error:;
    __Pyx_PyThreadState_assign __Pyx_XDECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_XDECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_4);
    __pyx_t_4 = 0;
    /*except:*/ {
      __Pyx_AddTraceback("rfc.compile_file", __pyx_clineno, __pyx_lineno,
                         __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_4, &__pyx_t_2, &__pyx_t_5) < 0)
        __PYX_ERR(0, 208, __pyx_L9_except_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_1 = PyTuple_Pack(3, __pyx_t_4, __pyx_t_2, __pyx_t_5);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L9_except_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_1, NULL);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 208, __pyx_L9_except_error)
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_9);
      __pyx_t_9 = 0;
      if (__pyx_t_10 < 0) __PYX_ERR(0, 208, __pyx_L9_except_error)
      __pyx_t_11 = ((!(__pyx_t_10 != 0)) != 0);
      if (__pyx_t_11) {
        __Pyx_GIVEREF(__pyx_t_4);
        __Pyx_GIVEREF(__pyx_t_2);
        __Pyx_XGIVEREF(__pyx_t_5);
        __Pyx_ErrRestoreWithState(__pyx_t_4, __pyx_t_2, __pyx_t_5);
        __pyx_t_4 = 0;
        __pyx_t_2 = 0;
        __pyx_t_5 = 0;
        __PYX_ERR(0, 208, __pyx_L9_except_error)
      }
      __Pyx_DECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      goto __pyx_L8_exception_handled;
    }
  __pyx_L9_except_error:;
    __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_6);
    __Pyx_XGIVEREF(__pyx_t_7);
    __Pyx_XGIVEREF(__pyx_t_8);
    __Pyx_ExceptionReset(__pyx_t_6, __pyx_t_7, __pyx_t_8);
    goto __pyx_L1_error;
  __pyx_L8_exception_handled:;
    __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_6);
    __Pyx_XGIVEREF(__pyx_t_7);
    __Pyx_XGIVEREF(__pyx_t_8);
    __Pyx_ExceptionReset(__pyx_t_6, __pyx_t_7, __pyx_t_8);
  __pyx_L12_try_end:;
  }
}
/*finally:*/ {
  /*normal exit:*/ {
    if (__pyx_t_3) {
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__37, NULL);
      __Pyx_DECREF(__pyx_t_3);
      __pyx_t_3 = 0;
      if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 208, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_DECREF(__pyx_t_8);
      __pyx_t_8 = 0;
    }
    goto __pyx_L6;
  }
__pyx_L6:;
}
goto __pyx_L16;
__pyx_L3_error:;
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
goto __pyx_L1_error;
__pyx_L16:;
}

/* "rfc.py":211
 *         code = file.read()
 *         output = compile(code)
 *     assert filename[-3:] == '.rf'             # <<<<<<<<<<<<<<
 *     return (filename[:-3] + '.py', FormatCode(output)[0])
 *
 */
#ifndef RFC_WITHOUT_ASSERTIONS
if (unlikely(!Py_OptimizeFlag)) {
  __pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_filename, -3L, 0, NULL, NULL,
                                      &__pyx_slice__38, 1, 0, 1);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_11 = (__Pyx_PyUnicode_Equals(__pyx_t_5, __pyx_kp_u_rf_2, Py_EQ));
  if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  if (unlikely(!__pyx_t_11)) {
    PyErr_SetNone(PyExc_AssertionError);
    __PYX_ERR(0, 211, __pyx_L1_error)
  }
}
#endif

/* "rfc.py":212
 *         output = compile(code)
 *     assert filename[-3:] == '.rf'
 *     return (filename[:-3] + '.py', FormatCode(output)[0])             #
 * <<<<<<<<<<<<<<
 *
 * if __name__ == "__main__":
 */
__Pyx_XDECREF(__pyx_r);
__pyx_t_5 = __Pyx_PyObject_GetSlice(__pyx_v_filename, 0, -3L, NULL, NULL,
                                    &__pyx_slice__39, 0, 1, 1);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__pyx_t_2 = PyNumber_Add(__pyx_t_5, __pyx_kp_u_py_2);
if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 212, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_2);
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_FormatCode);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 212, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
if (unlikely(!__pyx_v_output)) {
  __Pyx_RaiseUnboundLocalError("output");
  __PYX_ERR(0, 212, __pyx_L1_error)
}
__pyx_t_1 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
  __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_4);
  if (likely(__pyx_t_1)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
    __Pyx_INCREF(__pyx_t_1);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_4, function);
  }
}
if (!__pyx_t_1) {
  __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_output);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
} else {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_output};
    __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_output};
    __pyx_t_5 =
        __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
#endif
  {
    __pyx_t_12 = PyTuple_New(1 + 1);
    if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 212, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_1);
    __pyx_t_1 = NULL;
    __Pyx_INCREF(__pyx_v_output);
    __Pyx_GIVEREF(__pyx_v_output);
    PyTuple_SET_ITEM(__pyx_t_12, 0 + 1, __pyx_v_output);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_12, NULL);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_12);
    __pyx_t_12 = 0;
  }
}
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
__pyx_t_4 =
    __Pyx_GetItemInt(__pyx_t_5, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 212, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__pyx_t_5 = PyTuple_New(2);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 212, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__Pyx_GIVEREF(__pyx_t_2);
PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2);
__Pyx_GIVEREF(__pyx_t_4);
PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_4);
__pyx_t_2 = 0;
__pyx_t_4 = 0;
__pyx_r = __pyx_t_5;
__pyx_t_5 = 0;
goto __pyx_L0;

/* "rfc.py":207
 *
 *
 * def compile_file(filename):             # <<<<<<<<<<<<<<
 *     with open(filename) as file:
 *         code = file.read()
 */

/* function exit code */
__pyx_L1_error:;
__Pyx_XDECREF(__pyx_t_1);
__Pyx_XDECREF(__pyx_t_2);
__Pyx_XDECREF(__pyx_t_4);
__Pyx_XDECREF(__pyx_t_5);
__Pyx_XDECREF(__pyx_t_12);
__Pyx_AddTraceback("rfc.compile_file", __pyx_clineno, __pyx_lineno,
                   __pyx_filename);
__pyx_r = NULL;
__pyx_L0:;
__Pyx_XDECREF(__pyx_v_file);
__Pyx_XDECREF(__pyx_v_code);
__Pyx_XDECREF(__pyx_v_output);
__Pyx_XGIVEREF(__pyx_r);
__Pyx_RefNannyFinishContext();
return __pyx_r;
}

static PyMethodDef __pyx_methods[] = {{0, 0, 0, 0}};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
#if PY_VERSION_HEX < 0x03020000
    {PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
#else
    PyModuleDef_HEAD_INIT,
#endif
    "rfc",
    0,  /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL  /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
    {&__pyx_kp_u_, __pyx_k_, sizeof(__pyx_k_), 0, 1, 0, 0},
    {&__pyx_n_s_Alias, __pyx_k_Alias, sizeof(__pyx_k_Alias), 0, 0, 1, 1},
    {&__pyx_n_s_Alias___init, __pyx_k_Alias___init,
     sizeof(__pyx_k_Alias___init), 0, 0, 1, 1},
    {&__pyx_n_s_ArgumentParser, __pyx_k_ArgumentParser,
     sizeof(__pyx_k_ArgumentParser), 0, 0, 1, 1},
    {&__pyx_kp_u_B, __pyx_k_B, sizeof(__pyx_k_B), 0, 1, 0, 0},
    {&__pyx_n_s_Codegen, __pyx_k_Codegen, sizeof(__pyx_k_Codegen), 0, 0, 1, 1},
    {&__pyx_n_s_Codegen___init, __pyx_k_Codegen___init,
     sizeof(__pyx_k_Codegen___init), 0, 0, 1, 1},
    {&__pyx_n_s_Codegen_gen, __pyx_k_Codegen_gen, sizeof(__pyx_k_Codegen_gen),
     0, 0, 1, 1},
    {&__pyx_n_s_Codegen_line, __pyx_k_Codegen_line,
     sizeof(__pyx_k_Codegen_line), 0, 0, 1, 1},
    {&__pyx_n_s_Codegen_newline, __pyx_k_Codegen_newline,
     sizeof(__pyx_k_Codegen_newline), 0, 0, 1, 1},
    {&__pyx_n_s_Codegen_transform, __pyx_k_Codegen_transform,
     sizeof(__pyx_k_Codegen_transform), 0, 0, 1, 1},
    {&__pyx_n_u_DECORATOR, __pyx_k_DECORATOR, sizeof(__pyx_k_DECORATOR), 0, 1,
     0, 1},
    {&__pyx_n_u_DEDENT, __pyx_k_DEDENT, sizeof(__pyx_k_DEDENT), 0, 1, 0, 1},
    {&__pyx_n_u_DEF, __pyx_k_DEF, sizeof(__pyx_k_DEF), 0, 1, 0, 1},
    {&__pyx_n_u_ELSE, __pyx_k_ELSE, sizeof(__pyx_k_ELSE), 0, 1, 0, 1},
    {&__pyx_n_u_False, __pyx_k_False, sizeof(__pyx_k_False), 0, 1, 0, 1},
    {&__pyx_n_s_ForeignKeywordException, __pyx_k_ForeignKeywordException,
     sizeof(__pyx_k_ForeignKeywordException), 0, 0, 1, 1},
    {&__pyx_n_s_ForeignKeywordException___init,
     __pyx_k_ForeignKeywordException___init,
     sizeof(__pyx_k_ForeignKeywordException___init), 0, 0, 1, 1},
    {&__pyx_n_s_FormatCode, __pyx_k_FormatCode, sizeof(__pyx_k_FormatCode), 0,
     0, 1, 1},
    {&__pyx_n_u_IF, __pyx_k_IF, sizeof(__pyx_k_IF), 0, 1, 0, 1},
    {&__pyx_n_u_INDENT, __pyx_k_INDENT, sizeof(__pyx_k_INDENT), 0, 1, 0, 1},
    {&__pyx_kp_u_Input_file_or_directory, __pyx_k_Input_file_or_directory,
     sizeof(__pyx_k_Input_file_or_directory), 0, 1, 0, 0},
    {&__pyx_n_s_Lark, __pyx_k_Lark, sizeof(__pyx_k_Lark), 0, 0, 1, 1},
    {&__pyx_n_u_NAME, __pyx_k_NAME, sizeof(__pyx_k_NAME), 0, 1, 0, 1},
    {&__pyx_kp_u_Output_file, __pyx_k_Output_file, sizeof(__pyx_k_Output_file),
     0, 1, 0, 0},
    {&__pyx_n_s_PIPE, __pyx_k_PIPE, sizeof(__pyx_k_PIPE), 0, 0, 1, 1},
    {&__pyx_n_s_Parser, __pyx_k_Parser, sizeof(__pyx_k_Parser), 0, 0, 1, 1},
    {&__pyx_n_s_Parser___init, __pyx_k_Parser___init,
     sizeof(__pyx_k_Parser___init), 0, 0, 1, 1},
    {&__pyx_n_s_Parser_class_suite, __pyx_k_Parser_class_suite,
     sizeof(__pyx_k_Parser_class_suite), 0, 0, 1, 1},
    {&__pyx_n_s_Parser_decorator, __pyx_k_Parser_decorator,
     sizeof(__pyx_k_Parser_decorator), 0, 0, 1, 1},
    {&__pyx_n_s_Parser_start, __pyx_k_Parser_start,
     sizeof(__pyx_k_Parser_start), 0, 0, 1, 1},
    {&__pyx_n_s_Parser_suite, __pyx_k_Parser_suite,
     sizeof(__pyx_k_Parser_suite), 0, 0, 1, 1},
    {&__pyx_n_u_SEMICOLON, __pyx_k_SEMICOLON, sizeof(__pyx_k_SEMICOLON), 0, 1,
     0, 1},
    {&__pyx_n_u_TYPE, __pyx_k_TYPE, sizeof(__pyx_k_TYPE), 0, 1, 0, 1},
    {&__pyx_kp_u_The_bootstrap_compiler_for_Raft,
     __pyx_k_The_bootstrap_compiler_for_Raft,
     sizeof(__pyx_k_The_bootstrap_compiler_for_Raft), 0, 1, 0, 0},
    {&__pyx_n_s_Token, __pyx_k_Token, sizeof(__pyx_k_Token), 0, 0, 1, 1},
    {&__pyx_n_s_Transformer, __pyx_k_Transformer, sizeof(__pyx_k_Transformer),
     0, 0, 1, 1},
    {&__pyx_n_u_True, __pyx_k_True, sizeof(__pyx_k_True), 0, 1, 0, 1},
    {&__pyx_kp_u_TypeVar, __pyx_k_TypeVar, sizeof(__pyx_k_TypeVar), 0, 1, 0, 0},
    {&__pyx_kp_u__10, __pyx_k__10, sizeof(__pyx_k__10), 0, 1, 0, 0},
    {&__pyx_kp_u__12, __pyx_k__12, sizeof(__pyx_k__12), 0, 1, 0, 0},
    {&__pyx_kp_u__14, __pyx_k__14, sizeof(__pyx_k__14), 0, 1, 0, 0},
    {&__pyx_kp_u__15, __pyx_k__15, sizeof(__pyx_k__15), 0, 1, 0, 0},
    {&__pyx_kp_u__2, __pyx_k__2, sizeof(__pyx_k__2), 0, 1, 0, 0},
    {&__pyx_kp_u__22, __pyx_k__22, sizeof(__pyx_k__22), 0, 1, 0, 0},
    {&__pyx_kp_u__23, __pyx_k__23, sizeof(__pyx_k__23), 0, 1, 0, 0},
    {&__pyx_kp_u__24, __pyx_k__24, sizeof(__pyx_k__24), 0, 1, 0, 0},
    {&__pyx_kp_u__26, __pyx_k__26, sizeof(__pyx_k__26), 0, 1, 0, 0},
    {&__pyx_kp_u__27, __pyx_k__27, sizeof(__pyx_k__27), 0, 1, 0, 0},
    {&__pyx_kp_u__28, __pyx_k__28, sizeof(__pyx_k__28), 0, 1, 0, 0},
    {&__pyx_kp_u__3, __pyx_k__3, sizeof(__pyx_k__3), 0, 1, 0, 0},
    {&__pyx_kp_u__30, __pyx_k__30, sizeof(__pyx_k__30), 0, 1, 0, 0},
    {&__pyx_kp_u__32, __pyx_k__32, sizeof(__pyx_k__32), 0, 1, 0, 0},
    {&__pyx_kp_u__34, __pyx_k__34, sizeof(__pyx_k__34), 0, 1, 0, 0},
    {&__pyx_kp_u__35, __pyx_k__35, sizeof(__pyx_k__35), 0, 1, 0, 0},
    {&__pyx_n_s__36, __pyx_k__36, sizeof(__pyx_k__36), 0, 0, 1, 1},
    {&__pyx_kp_u__4, __pyx_k__4, sizeof(__pyx_k__4), 0, 1, 0, 0},
    {&__pyx_kp_u__6, __pyx_k__6, sizeof(__pyx_k__6), 0, 1, 0, 0},
    {&__pyx_kp_u__7, __pyx_k__7, sizeof(__pyx_k__7), 0, 1, 0, 0},
    {&__pyx_kp_u__8, __pyx_k__8, sizeof(__pyx_k__8), 0, 1, 0, 0},
    {&__pyx_kp_u__81, __pyx_k__81, sizeof(__pyx_k__81), 0, 1, 0, 0},
    {&__pyx_kp_u_a_out, __pyx_k_a_out, sizeof(__pyx_k_a_out), 0, 1, 0, 0},
    {&__pyx_n_s_add_argument, __pyx_k_add_argument,
     sizeof(__pyx_k_add_argument), 0, 0, 1, 1},
    {&__pyx_n_s_alias, __pyx_k_alias, sizeof(__pyx_k_alias), 0, 0, 1, 1},
    {&__pyx_n_s_aliases, __pyx_k_aliases, sizeof(__pyx_k_aliases), 0, 0, 1, 1},
    {&__pyx_n_s_already_visited, __pyx_k_already_visited,
     sizeof(__pyx_k_already_visited), 0, 0, 1, 1},
    {&__pyx_kp_u_and, __pyx_k_and, sizeof(__pyx_k_and), 0, 1, 0, 0},
    {&__pyx_n_u_and_2, __pyx_k_and_2, sizeof(__pyx_k_and_2), 0, 1, 0, 1},
    {&__pyx_n_s_arg_parser, __pyx_k_arg_parser, sizeof(__pyx_k_arg_parser), 0,
     0, 1, 1},
    {&__pyx_n_s_argparse, __pyx_k_argparse, sizeof(__pyx_k_argparse), 0, 0, 1,
     1},
    {&__pyx_n_s_args, __pyx_k_args, sizeof(__pyx_k_args), 0, 0, 1, 1},
    {&__pyx_n_s_basename, __pyx_k_basename, sizeof(__pyx_k_basename), 0, 0, 1,
     1},
    {&__pyx_n_s_cg, __pyx_k_cg, sizeof(__pyx_k_cg), 0, 0, 1, 1},
    {&__pyx_n_u_class, __pyx_k_class, sizeof(__pyx_k_class), 0, 1, 0, 1},
    {&__pyx_n_s_class_suite, __pyx_k_class_suite, sizeof(__pyx_k_class_suite),
     0, 0, 1, 1},
    {&__pyx_n_s_cline_in_traceback, __pyx_k_cline_in_traceback,
     sizeof(__pyx_k_cline_in_traceback), 0, 0, 1, 1},
    {&__pyx_n_s_code, __pyx_k_code, sizeof(__pyx_k_code), 0, 0, 1, 1},
    {&__pyx_n_s_column, __pyx_k_column, sizeof(__pyx_k_column), 0, 0, 1, 1},
    {&__pyx_n_s_compile, __pyx_k_compile, sizeof(__pyx_k_compile), 0, 0, 1, 1},
    {&__pyx_n_s_compile_file, __pyx_k_compile_file,
     sizeof(__pyx_k_compile_file), 0, 0, 1, 1},
    {&__pyx_n_s_content, __pyx_k_content, sizeof(__pyx_k_content), 0, 0, 1, 1},
    {&__pyx_n_u_decorated, __pyx_k_decorated, sizeof(__pyx_k_decorated), 0, 1,
     0, 1},
    {&__pyx_n_s_decorator, __pyx_k_decorator, sizeof(__pyx_k_decorator), 0, 0,
     1, 1},
    {&__pyx_n_s_decorator_tokens, __pyx_k_decorator_tokens,
     sizeof(__pyx_k_decorator_tokens), 0, 0, 1, 1},
    {&__pyx_kp_u_def, __pyx_k_def, sizeof(__pyx_k_def), 0, 1, 0, 0},
    {&__pyx_n_u_def_2, __pyx_k_def_2, sizeof(__pyx_k_def_2), 0, 1, 0, 1},
    {&__pyx_kp_u_def_test_func_func_return_func,
     __pyx_k_def_test_func_func_return_func,
     sizeof(__pyx_k_def_test_func_func_return_func), 0, 1, 0, 0},
    {&__pyx_n_s_description, __pyx_k_description, sizeof(__pyx_k_description),
     0, 0, 1, 1},
    {&__pyx_n_s_doc, __pyx_k_doc, sizeof(__pyx_k_doc), 0, 0, 1, 1},
    {&__pyx_kp_u_elif, __pyx_k_elif, sizeof(__pyx_k_elif), 0, 1, 0, 0},
    {&__pyx_kp_u_else, __pyx_k_else, sizeof(__pyx_k_else), 0, 1, 0, 0},
    {&__pyx_n_s_enter, __pyx_k_enter, sizeof(__pyx_k_enter), 0, 0, 1, 1},
    {&__pyx_n_s_epilogue, __pyx_k_epilogue, sizeof(__pyx_k_epilogue), 0, 0, 1,
     1},
    {&__pyx_kp_u_exe, __pyx_k_exe, sizeof(__pyx_k_exe), 0, 1, 0, 0},
    {&__pyx_n_s_exit, __pyx_k_exit, sizeof(__pyx_k_exit), 0, 0, 1, 1},
    {&__pyx_n_s_f, __pyx_k_f, sizeof(__pyx_k_f), 0, 0, 1, 1},
    {&__pyx_n_u_false, __pyx_k_false, sizeof(__pyx_k_false), 0, 1, 0, 1},
    {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
    {&__pyx_n_s_filename, __pyx_k_filename, sizeof(__pyx_k_filename), 0, 0, 1,
     1},
    {&__pyx_n_u_fn, __pyx_k_fn, sizeof(__pyx_k_fn), 0, 1, 0, 1},
    {&__pyx_n_s_foreign_keywords, __pyx_k_foreign_keywords,
     sizeof(__pyx_k_foreign_keywords), 0, 0, 1, 1},
    {&__pyx_kp_u_from_typing_import, __pyx_k_from_typing_import,
     sizeof(__pyx_k_from_typing_import), 0, 1, 0, 0},
    {&__pyx_n_s_gen, __pyx_k_gen, sizeof(__pyx_k_gen), 0, 0, 1, 1},
    {&__pyx_n_s_glob, __pyx_k_glob, sizeof(__pyx_k_glob), 0, 0, 1, 1},
    {&__pyx_n_s_grammar, __pyx_k_grammar, sizeof(__pyx_k_grammar), 0, 0, 1, 1},
    {&__pyx_n_s_help, __pyx_k_help, sizeof(__pyx_k_help), 0, 0, 1, 1},
    {&__pyx_n_s_i, __pyx_k_i, sizeof(__pyx_k_i), 0, 0, 1, 1},
    {&__pyx_kp_u_if___name_____main___main, __pyx_k_if___name_____main___main,
     sizeof(__pyx_k_if___name_____main___main), 0, 1, 0, 0},
    {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
    {&__pyx_n_u_import_2, __pyx_k_import_2, sizeof(__pyx_k_import_2), 0, 1, 0,
     1},
    {&__pyx_n_s_indent_offset, __pyx_k_indent_offset,
     sizeof(__pyx_k_indent_offset), 0, 0, 1, 1},
    {&__pyx_n_s_init, __pyx_k_init, sizeof(__pyx_k_init), 0, 0, 1, 1},
    {&__pyx_n_s_input, __pyx_k_input, sizeof(__pyx_k_input), 0, 0, 1, 1},
    {&__pyx_n_u_input, __pyx_k_input, sizeof(__pyx_k_input), 0, 1, 0, 1},
    {&__pyx_n_s_is_alias, __pyx_k_is_alias, sizeof(__pyx_k_is_alias), 0, 0, 1,
     1},
    {&__pyx_n_s_isdir, __pyx_k_isdir, sizeof(__pyx_k_isdir), 0, 0, 1, 1},
    {&__pyx_n_s_keyword, __pyx_k_keyword, sizeof(__pyx_k_keyword), 0, 0, 1, 1},
    {&__pyx_n_u_lalr, __pyx_k_lalr, sizeof(__pyx_k_lalr), 0, 1, 0, 1},
    {&__pyx_n_s_lark, __pyx_k_lark, sizeof(__pyx_k_lark), 0, 0, 1, 1},
    {&__pyx_n_s_lark_lexer, __pyx_k_lark_lexer, sizeof(__pyx_k_lark_lexer), 0,
     0, 1, 1},
    {&__pyx_n_s_last, __pyx_k_last, sizeof(__pyx_k_last), 0, 0, 1, 1},
    {&__pyx_n_s_len, __pyx_k_len, sizeof(__pyx_k_len), 0, 0, 1, 1},
    {&__pyx_n_s_lex, __pyx_k_lex, sizeof(__pyx_k_lex), 0, 0, 1, 1},
    {&__pyx_n_s_line, __pyx_k_line, sizeof(__pyx_k_line), 0, 0, 1, 1},
    {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
    {&__pyx_n_u_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 1, 0, 1},
    {&__pyx_kp_u_main___py, __pyx_k_main___py, sizeof(__pyx_k_main___py), 0, 1,
     0, 0},
    {&__pyx_n_s_maybe_placeholders, __pyx_k_maybe_placeholders,
     sizeof(__pyx_k_maybe_placeholders), 0, 0, 1, 1},
    {&__pyx_n_s_metaclass, __pyx_k_metaclass, sizeof(__pyx_k_metaclass), 0, 0,
     1, 1},
    {&__pyx_n_s_metavar, __pyx_k_metavar, sizeof(__pyx_k_metavar), 0, 0, 1, 1},
    {&__pyx_n_s_mkdtemp, __pyx_k_mkdtemp, sizeof(__pyx_k_mkdtemp), 0, 0, 1, 1},
    {&__pyx_n_s_module, __pyx_k_module, sizeof(__pyx_k_module), 0, 0, 1, 1},
    {&__pyx_n_s_move, __pyx_k_move, sizeof(__pyx_k_move), 0, 0, 1, 1},
    {&__pyx_n_s_msg, __pyx_k_msg, sizeof(__pyx_k_msg), 0, 0, 1, 1},
    {&__pyx_n_s_name, __pyx_k_name, sizeof(__pyx_k_name), 0, 0, 1, 1},
    {&__pyx_n_s_name_2, __pyx_k_name_2, sizeof(__pyx_k_name_2), 0, 0, 1, 1},
    {&__pyx_n_s_newline, __pyx_k_newline, sizeof(__pyx_k_newline), 0, 0, 1, 1},
    {&__pyx_kp_u_not, __pyx_k_not, sizeof(__pyx_k_not), 0, 1, 0, 0},
    {&__pyx_n_u_not_2, __pyx_k_not_2, sizeof(__pyx_k_not_2), 0, 1, 0, 1},
    {&__pyx_n_u_nuitka, __pyx_k_nuitka, sizeof(__pyx_k_nuitka), 0, 1, 0, 1},
    {&__pyx_n_s_nuitka_base, __pyx_k_nuitka_base, sizeof(__pyx_k_nuitka_base),
     0, 0, 1, 1},
    {&__pyx_n_s_nuitka_main, __pyx_k_nuitka_main, sizeof(__pyx_k_nuitka_main),
     0, 0, 1, 1},
    {&__pyx_kp_u_o, __pyx_k_o, sizeof(__pyx_k_o), 0, 1, 0, 0},
    {&__pyx_n_s_o_2, __pyx_k_o_2, sizeof(__pyx_k_o_2), 0, 0, 1, 1},
    {&__pyx_n_s_open, __pyx_k_open, sizeof(__pyx_k_open), 0, 0, 1, 1},
    {&__pyx_kp_u_or, __pyx_k_or, sizeof(__pyx_k_or), 0, 1, 0, 0},
    {&__pyx_n_u_or_2, __pyx_k_or_2, sizeof(__pyx_k_or_2), 0, 1, 0, 1},
    {&__pyx_n_s_os, __pyx_k_os, sizeof(__pyx_k_os), 0, 0, 1, 1},
    {&__pyx_n_s_output, __pyx_k_output, sizeof(__pyx_k_output), 0, 0, 1, 1},
    {&__pyx_n_u_output, __pyx_k_output, sizeof(__pyx_k_output), 0, 1, 0, 1},
    {&__pyx_kp_u_output_dir, __pyx_k_output_dir, sizeof(__pyx_k_output_dir), 0,
     1, 0, 0},
    {&__pyx_n_s_parse, __pyx_k_parse, sizeof(__pyx_k_parse), 0, 0, 1, 1},
    {&__pyx_n_s_parse_args, __pyx_k_parse_args, sizeof(__pyx_k_parse_args), 0,
     0, 1, 1},
    {&__pyx_n_s_parsed, __pyx_k_parsed, sizeof(__pyx_k_parsed), 0, 0, 1, 1},
    {&__pyx_n_s_parser, __pyx_k_parser, sizeof(__pyx_k_parser), 0, 0, 1, 1},
    {&__pyx_n_u_pass, __pyx_k_pass, sizeof(__pyx_k_pass), 0, 1, 0, 1},
    {&__pyx_n_s_path, __pyx_k_path, sizeof(__pyx_k_path), 0, 0, 1, 1},
    {&__pyx_n_s_prepare, __pyx_k_prepare, sizeof(__pyx_k_prepare), 0, 0, 1, 1},
    {&__pyx_n_s_prologue, __pyx_k_prologue, sizeof(__pyx_k_prologue), 0, 0, 1,
     1},
    {&__pyx_n_s_propagate_positions, __pyx_k_propagate_positions,
     sizeof(__pyx_k_propagate_positions), 0, 0, 1, 1},
    {&__pyx_n_s_py, __pyx_k_py, sizeof(__pyx_k_py), 0, 0, 1, 1},
    {&__pyx_kp_u_py_2, __pyx_k_py_2, sizeof(__pyx_k_py_2), 0, 1, 0, 0},
    {&__pyx_n_s_pyfiles, __pyx_k_pyfiles, sizeof(__pyx_k_pyfiles), 0, 0, 1, 1},
    {&__pyx_n_u_python3, __pyx_k_python3, sizeof(__pyx_k_python3), 0, 1, 0, 1},
    {&__pyx_kp_u_python_version_3_6, __pyx_k_python_version_3_6,
     sizeof(__pyx_k_python_version_3_6), 0, 1, 0, 0},
    {&__pyx_n_s_qualname, __pyx_k_qualname, sizeof(__pyx_k_qualname), 0, 0, 1,
     1},
    {&__pyx_kp_u_r_type, __pyx_k_r_type, sizeof(__pyx_k_r_type), 0, 1, 0, 0},
    {&__pyx_n_s_read, __pyx_k_read, sizeof(__pyx_k_read), 0, 0, 1, 1},
    {&__pyx_kp_u_recurse_all, __pyx_k_recurse_all, sizeof(__pyx_k_recurse_all),
     0, 1, 0, 0},
    {&__pyx_n_s_recursive, __pyx_k_recursive, sizeof(__pyx_k_recursive), 0, 0,
     1, 1},
    {&__pyx_n_s_remove, __pyx_k_remove, sizeof(__pyx_k_remove), 0, 0, 1, 1},
    {&__pyx_n_s_res, __pyx_k_res, sizeof(__pyx_k_res), 0, 0, 1, 1},
    {&__pyx_n_s_returncode, __pyx_k_returncode, sizeof(__pyx_k_returncode), 0,
     0, 1, 1},
    {&__pyx_n_s_rf, __pyx_k_rf, sizeof(__pyx_k_rf), 0, 0, 1, 1},
    {&__pyx_kp_u_rf_2, __pyx_k_rf_2, sizeof(__pyx_k_rf_2), 0, 1, 0, 0},
    {&__pyx_kp_u_rf_3, __pyx_k_rf_3, sizeof(__pyx_k_rf_3), 0, 1, 0, 0},
    {&__pyx_n_s_rfc, __pyx_k_rfc, sizeof(__pyx_k_rfc), 0, 0, 1, 1},
    {&__pyx_n_s_rmtree, __pyx_k_rmtree, sizeof(__pyx_k_rmtree), 0, 0, 1, 1},
    {&__pyx_n_s_run, __pyx_k_run, sizeof(__pyx_k_run), 0, 0, 1, 1},
    {&__pyx_n_s_self, __pyx_k_self, sizeof(__pyx_k_self), 0, 0, 1, 1},
    {&__pyx_n_s_shutil, __pyx_k_shutil, sizeof(__pyx_k_shutil), 0, 0, 1, 1},
    {&__pyx_n_s_splitext, __pyx_k_splitext, sizeof(__pyx_k_splitext), 0, 0, 1,
     1},
    {&__pyx_kp_s_src_rfc_py_rfc_py, __pyx_k_src_rfc_py_rfc_py,
     sizeof(__pyx_k_src_rfc_py_rfc_py), 0, 0, 1, 0},
    {&__pyx_n_s_start, __pyx_k_start, sizeof(__pyx_k_start), 0, 0, 1, 1},
    {&__pyx_kp_u_start_typedef_funcdef_decorated,
     __pyx_k_start_typedef_funcdef_decorated,
     sizeof(__pyx_k_start_typedef_funcdef_decorated), 0, 1, 0, 0},
    {&__pyx_n_s_stderr, __pyx_k_stderr, sizeof(__pyx_k_stderr), 0, 0, 1, 1},
    {&__pyx_n_s_strip, __pyx_k_strip, sizeof(__pyx_k_strip), 0, 0, 1, 1},
    {&__pyx_n_u_struct, __pyx_k_struct, sizeof(__pyx_k_struct), 0, 1, 0, 1},
    {&__pyx_n_s_subprocess, __pyx_k_subprocess, sizeof(__pyx_k_subprocess), 0,
     0, 1, 1},
    {&__pyx_n_s_suite, __pyx_k_suite, sizeof(__pyx_k_suite), 0, 0, 1, 1},
    {&__pyx_n_u_suite, __pyx_k_suite, sizeof(__pyx_k_suite), 0, 1, 0, 1},
    {&__pyx_n_s_suite_tokens, __pyx_k_suite_tokens,
     sizeof(__pyx_k_suite_tokens), 0, 0, 1, 1},
    {&__pyx_n_s_super, __pyx_k_super, sizeof(__pyx_k_super), 0, 0, 1, 1},
    {&__pyx_n_s_t, __pyx_k_t, sizeof(__pyx_k_t), 0, 0, 1, 1},
    {&__pyx_n_s_tempfile, __pyx_k_tempfile, sizeof(__pyx_k_tempfile), 0, 0, 1,
     1},
    {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
    {&__pyx_kp_u_test_lambda, __pyx_k_test_lambda, sizeof(__pyx_k_test_lambda),
     0, 1, 0, 0},
    {&__pyx_n_s_tmpdir, __pyx_k_tmpdir, sizeof(__pyx_k_tmpdir), 0, 0, 1, 1},
    {&__pyx_n_s_tok, __pyx_k_tok, sizeof(__pyx_k_tok), 0, 0, 1, 1},
    {&__pyx_n_s_toks, __pyx_k_toks, sizeof(__pyx_k_toks), 0, 0, 1, 1},
    {&__pyx_n_s_transform, __pyx_k_transform, sizeof(__pyx_k_transform), 0, 0,
     1, 1},
    {&__pyx_n_s_transformer, __pyx_k_transformer, sizeof(__pyx_k_transformer),
     0, 0, 1, 1},
    {&__pyx_n_u_true, __pyx_k_true, sizeof(__pyx_k_true), 0, 1, 0, 1},
    {&__pyx_n_s_type, __pyx_k_type, sizeof(__pyx_k_type), 0, 0, 1, 1},
    {&__pyx_n_u_type, __pyx_k_type, sizeof(__pyx_k_type), 0, 1, 0, 1},
    {&__pyx_n_s_types, __pyx_k_types, sizeof(__pyx_k_types), 0, 0, 1, 1},
    {&__pyx_n_s_upper, __pyx_k_upper, sizeof(__pyx_k_upper), 0, 0, 1, 1},
    {&__pyx_kp_u_usage_of_foreign_keyword, __pyx_k_usage_of_foreign_keyword,
     sizeof(__pyx_k_usage_of_foreign_keyword), 0, 1, 0, 0},
    {&__pyx_n_u_use, __pyx_k_use, sizeof(__pyx_k_use), 0, 1, 0, 1},
    {&__pyx_n_s_value, __pyx_k_value, sizeof(__pyx_k_value), 0, 0, 1, 1},
    {&__pyx_n_u_w, __pyx_k_w, sizeof(__pyx_k_w), 0, 1, 0, 1},
    {&__pyx_n_s_write, __pyx_k_write, sizeof(__pyx_k_write), 0, 0, 1, 1},
    {&__pyx_n_s_yapf_yapflib_yapf_api, __pyx_k_yapf_yapflib_yapf_api,
     sizeof(__pyx_k_yapf_yapflib_yapf_api), 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0}};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s_open);
  if (!__pyx_builtin_open) __PYX_ERR(0, 235, __pyx_L1_error)
  __pyx_builtin_super = __Pyx_GetBuiltinName(__pyx_n_s_super);
  if (!__pyx_builtin_super) __PYX_ERR(0, 15, __pyx_L1_error)
  return 0;
__pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations __Pyx_RefNannySetupContext(
      "__Pyx_InitCachedConstants", 0);

  /* "rfc.py":57
   *                 if tok.line == t.line and tok.column == t.column:
   *                     if t.value == '#':
   *                         self.toks += [Token('DECORATOR', '@')] #
   * <<<<<<<<<<<<<< elif t.value == '[': pass
   */
  __pyx_tuple__5 = PyTuple_Pack(2, __pyx_n_u_DECORATOR, __pyx_kp_u__4);
  if (unlikely(!__pyx_tuple__5)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__5);
  __Pyx_GIVEREF(__pyx_tuple__5);

  /* "rfc.py":61
   *                         pass
   *                     elif t.value == ']':
   *                         self.toks += [Token('SEMICOLON', ';')] #
   * <<<<<<<<<<<<<< else: self.toks += [t]
   */
  __pyx_tuple__9 = PyTuple_Pack(2, __pyx_n_u_SEMICOLON, __pyx_kp_u__8);
  if (unlikely(!__pyx_tuple__9)) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__9);
  __Pyx_GIVEREF(__pyx_tuple__9);

  /* "rfc.py":71
   *                 if tok.line == t.line and tok.column == t.column:
   *                     if t.value == '{':
   *                         self.toks += [Token('INDENT', None)]             #
   * <<<<<<<<<<<<<< elif t.value == '}': self.toks += [Token('DEDENT', None)]
   */
  __pyx_tuple__11 = PyTuple_Pack(2, __pyx_n_u_INDENT, Py_None);
  if (unlikely(!__pyx_tuple__11)) __PYX_ERR(0, 71, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__11);
  __Pyx_GIVEREF(__pyx_tuple__11);

  /* "rfc.py":73
   *                         self.toks += [Token('INDENT', None)]
   *                     elif t.value == '}':
   *                         self.toks += [Token('DEDENT', None)]             #
   * <<<<<<<<<<<<<< else: self.toks += [t]
   */
  __pyx_tuple__13 = PyTuple_Pack(2, __pyx_n_u_DEDENT, Py_None);
  if (unlikely(!__pyx_tuple__13)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__13);
  __Pyx_GIVEREF(__pyx_tuple__13);

  /* "rfc.py":103
   *
   *             elif t.type == 'INDENT':
   *                 self.line(':')             # <<<<<<<<<<<<<<
   *                 if self.toks[i+1].type == 'DEDENT':
   *                     self.line('pass')
   */
  __pyx_tuple__16 = PyTuple_Pack(1, __pyx_kp_u__15);
  if (unlikely(!__pyx_tuple__16)) __PYX_ERR(0, 103, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__16);
  __Pyx_GIVEREF(__pyx_tuple__16);

  /* "rfc.py":105
   *                 self.line(':')
   *                 if self.toks[i+1].type == 'DEDENT':
   *                     self.line('pass')             # <<<<<<<<<<<<<<
   *                 self.newline(1)
   *
   */
  __pyx_tuple__17 = PyTuple_Pack(1, __pyx_n_u_pass);
  if (unlikely(!__pyx_tuple__17)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__17);
  __Pyx_GIVEREF(__pyx_tuple__17);

  /* "rfc.py":106
   *                 if self.toks[i+1].type == 'DEDENT':
   *                     self.line('pass')
   *                 self.newline(1)             # <<<<<<<<<<<<<<
   *
   *             elif t.type == 'DEDENT':
   */
  __pyx_tuple__18 = PyTuple_Pack(1, __pyx_int_1);
  if (unlikely(!__pyx_tuple__18)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__18);
  __Pyx_GIVEREF(__pyx_tuple__18);

  /* "rfc.py":109
   *
   *             elif t.type == 'DEDENT':
   *                 self.newline(-1)             # <<<<<<<<<<<<<<
   *
   *             elif t.type == 'SEMICOLON':
   */
  __pyx_tuple__19 = PyTuple_Pack(1, __pyx_int_neg_1);
  if (unlikely(!__pyx_tuple__19)) __PYX_ERR(0, 109, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__19);
  __Pyx_GIVEREF(__pyx_tuple__19);

  /* "rfc.py":119
   *             elif t.type == 'ELSE':
   *                 if self.toks[i+1].type == 'IF':
   *                     self.line('elif ')             # <<<<<<<<<<<<<<
   *                     i += 1
   *                 else:
   */
  __pyx_tuple__20 = PyTuple_Pack(1, __pyx_kp_u_elif);
  if (unlikely(!__pyx_tuple__20)) __PYX_ERR(0, 119, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__20);
  __Pyx_GIVEREF(__pyx_tuple__20);

  /* "rfc.py":122
   *                     i += 1
   *                 else:
   *                     self.line('else ')             # <<<<<<<<<<<<<<
   *
   *             elif t.type == 'TYPE':
   */
  __pyx_tuple__21 = PyTuple_Pack(1, __pyx_kp_u_else);
  if (unlikely(!__pyx_tuple__21)) __PYX_ERR(0, 122, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);

  /* "rfc.py":137
   *                     continue
   *                 else: types = ';'
   *                 types = types[:-1]             # <<<<<<<<<<<<<<
   *                 self.newline(content=f'{name} = TypeVar("{name}"{types})')
   *
   */
  __pyx_slice__25 = PySlice_New(Py_None, __pyx_int_neg_1, Py_None);
  if (unlikely(!__pyx_slice__25)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__25);
  __Pyx_GIVEREF(__pyx_slice__25);

  /* "rfc.py":149
   *             else:
   *                 if t.value == '&&':
   *                     self.line(' and ')             # <<<<<<<<<<<<<<
   *                 elif t.value == '||':
   *                     self.line(' or ')
   */
  __pyx_tuple__29 = PyTuple_Pack(1, __pyx_kp_u_and);
  if (unlikely(!__pyx_tuple__29)) __PYX_ERR(0, 149, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__29);
  __Pyx_GIVEREF(__pyx_tuple__29);

  /* "rfc.py":151
   *                     self.line(' and ')
   *                 elif t.value == '||':
   *                     self.line(' or ')             # <<<<<<<<<<<<<<
   *                 elif t.value == '!':
   *                     self.line(' not ')
   */
  __pyx_tuple__31 = PyTuple_Pack(1, __pyx_kp_u_or);
  if (unlikely(!__pyx_tuple__31)) __PYX_ERR(0, 151, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__31);
  __Pyx_GIVEREF(__pyx_tuple__31);

  /* "rfc.py":153
   *                     self.line(' or ')
   *                 elif t.value == '!':
   *                     self.line(' not ')             # <<<<<<<<<<<<<<
   *                 else:
   *                     self.line(f'{t} ')
   */
  __pyx_tuple__33 = PyTuple_Pack(1, __pyx_kp_u_not);
  if (unlikely(!__pyx_tuple__33)) __PYX_ERR(0, 153, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__33);
  __Pyx_GIVEREF(__pyx_tuple__33);

  /* "rfc.py":208
   *
   * def compile_file(filename):
   *     with open(filename) as file:             # <<<<<<<<<<<<<<
   *         code = file.read()
   *         output = compile(code)
   */
  __pyx_tuple__37 = PyTuple_Pack(3, Py_None, Py_None, Py_None);
  if (unlikely(!__pyx_tuple__37)) __PYX_ERR(0, 208, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__37);
  __Pyx_GIVEREF(__pyx_tuple__37);

  /* "rfc.py":211
   *         code = file.read()
   *         output = compile(code)
   *     assert filename[-3:] == '.rf'             # <<<<<<<<<<<<<<
   *     return (filename[:-3] + '.py', FormatCode(output)[0])
   *
   */
  __pyx_slice__38 = PySlice_New(__pyx_int_neg_3, Py_None, Py_None);
  if (unlikely(!__pyx_slice__38)) __PYX_ERR(0, 211, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__38);
  __Pyx_GIVEREF(__pyx_slice__38);

  /* "rfc.py":212
   *         output = compile(code)
   *     assert filename[-3:] == '.rf'
   *     return (filename[:-3] + '.py', FormatCode(output)[0])             #
   * <<<<<<<<<<<<<<
   *
   * if __name__ == "__main__":
   */
  __pyx_slice__39 = PySlice_New(Py_None, __pyx_int_neg_3, Py_None);
  if (unlikely(!__pyx_slice__39)) __PYX_ERR(0, 212, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__39);
  __Pyx_GIVEREF(__pyx_slice__39);

  /* "rfc.py":13
   *
   * class ForeignKeywordException(Exception):
   *     def __init__(self, keyword):             # <<<<<<<<<<<<<<
   *         msg = f'usage of foreign keyword: `{keyword}`'
   *         super(Exception, self).__init__(self, msg)
   */
  __pyx_tuple__40 =
      PyTuple_Pack(3, __pyx_n_s_self, __pyx_n_s_keyword, __pyx_n_s_msg);
  if (unlikely(!__pyx_tuple__40)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__40);
  __Pyx_GIVEREF(__pyx_tuple__40);
  __pyx_codeobj__41 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__40, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_init, 13, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__41)) __PYX_ERR(0, 13, __pyx_L1_error)

  /* "rfc.py":20
   * class Alias:
   *
   *     def __init__(self, rf, py):             # <<<<<<<<<<<<<<
   *         self.rf, self.py = rf, py
   *
   */
  __pyx_tuple__42 = PyTuple_Pack(3, __pyx_n_s_self, __pyx_n_s_rf, __pyx_n_s_py);
  if (unlikely(!__pyx_tuple__42)) __PYX_ERR(0, 20, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__42);
  __Pyx_GIVEREF(__pyx_tuple__42);
  __pyx_codeobj__43 = (PyObject *)__Pyx_PyCode_New(
      3, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__42, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_init, 20, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__43)) __PYX_ERR(0, 20, __pyx_L1_error)

  /* "rfc.py":26
   * class Codegen:
   *     aliases = [
   *         Alias('use', 'import'),             # <<<<<<<<<<<<<<
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),
   */
  __pyx_tuple__44 = PyTuple_Pack(2, __pyx_n_u_use, __pyx_n_u_import_2);
  if (unlikely(!__pyx_tuple__44)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__44);
  __Pyx_GIVEREF(__pyx_tuple__44);

  /* "rfc.py":27
   *     aliases = [
   *         Alias('use', 'import'),
   *         Alias('fn', 'def'),             # <<<<<<<<<<<<<<
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),
   */
  __pyx_tuple__45 = PyTuple_Pack(2, __pyx_n_u_fn, __pyx_n_u_def_2);
  if (unlikely(!__pyx_tuple__45)) __PYX_ERR(0, 27, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__45);
  __Pyx_GIVEREF(__pyx_tuple__45);

  /* "rfc.py":28
   *         Alias('use', 'import'),
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),             # <<<<<<<<<<<<<<
   *         Alias('true', 'True'),
   *         Alias('false', 'False'),
   */
  __pyx_tuple__46 = PyTuple_Pack(2, __pyx_n_u_struct, __pyx_n_u_class);
  if (unlikely(!__pyx_tuple__46)) __PYX_ERR(0, 28, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__46);
  __Pyx_GIVEREF(__pyx_tuple__46);

  /* "rfc.py":29
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),             # <<<<<<<<<<<<<<
   *         Alias('false', 'False'),
   *     ]
   */
  __pyx_tuple__47 = PyTuple_Pack(2, __pyx_n_u_true, __pyx_n_u_True);
  if (unlikely(!__pyx_tuple__47)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__47);
  __Pyx_GIVEREF(__pyx_tuple__47);

  /* "rfc.py":30
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),
   *         Alias('false', 'False'),             # <<<<<<<<<<<<<<
   *     ]
   *
   */
  __pyx_tuple__48 = PyTuple_Pack(2, __pyx_n_u_false, __pyx_n_u_False);
  if (unlikely(!__pyx_tuple__48)) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__48);
  __Pyx_GIVEREF(__pyx_tuple__48);

  /* "rfc.py":35
   *     foreign_keywords = ['not', 'and', 'or']
   *
   *     def __init__(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.output = [[0, '']]
   *         self.transform(toks, parsed)
   */
  __pyx_tuple__49 =
      PyTuple_Pack(3, __pyx_n_s_self, __pyx_n_s_toks, __pyx_n_s_parsed);
  if (unlikely(!__pyx_tuple__49)) __PYX_ERR(0, 35, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__49);
  __Pyx_GIVEREF(__pyx_tuple__49);
  __pyx_codeobj__50 = (PyObject *)__Pyx_PyCode_New(
      3, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__49, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_init, 35, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__50)) __PYX_ERR(0, 35, __pyx_L1_error)

  /* "rfc.py":39
   *         self.transform(toks, parsed)
   *
   *     def newline(self, indent_offset=0, content=''):             #
   * <<<<<<<<<<<<<< last = self.output[-1][0] self.output += [[last +
   * indent_offset, content]]
   */
  __pyx_tuple__51 = PyTuple_Pack(4, __pyx_n_s_self, __pyx_n_s_indent_offset,
                                 __pyx_n_s_content, __pyx_n_s_last);
  if (unlikely(!__pyx_tuple__51)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__51);
  __Pyx_GIVEREF(__pyx_tuple__51);
  __pyx_codeobj__52 = (PyObject *)__Pyx_PyCode_New(
      3, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__51, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_newline, 39, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__52)) __PYX_ERR(0, 39, __pyx_L1_error)
  __pyx_tuple__53 =
      PyTuple_Pack(2, ((PyObject *)__pyx_int_0), ((PyObject *)__pyx_kp_u__2));
  if (unlikely(!__pyx_tuple__53)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__53);
  __Pyx_GIVEREF(__pyx_tuple__53);

  /* "rfc.py":43
   *         self.output += [[last + indent_offset, content]]
   *
   *     def line(self, code):             # <<<<<<<<<<<<<<
   *         self.output[-1][1] += code
   *
   */
  __pyx_tuple__54 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s_code);
  if (unlikely(!__pyx_tuple__54)) __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__54);
  __Pyx_GIVEREF(__pyx_tuple__54);
  __pyx_codeobj__55 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__54, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_line, 43, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__55)) __PYX_ERR(0, 43, __pyx_L1_error)

  /* "rfc.py":46
   *         self.output[-1][1] += code
   *
   *     def transform(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.toks = []
   *         toks = list(toks)
   */
  __pyx_tuple__56 =
      PyTuple_Pack(6, __pyx_n_s_self, __pyx_n_s_toks, __pyx_n_s_parsed,
                   __pyx_n_s_t, __pyx_n_s_already_visited, __pyx_n_s_tok);
  if (unlikely(!__pyx_tuple__56)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__56);
  __Pyx_GIVEREF(__pyx_tuple__56);
  __pyx_codeobj__57 = (PyObject *)__Pyx_PyCode_New(
      3, 0, 6, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__56, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_transform, 46, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__57)) __PYX_ERR(0, 46, __pyx_L1_error)

  /* "rfc.py":83
   *
   *
   *     def gen(self):             # <<<<<<<<<<<<<<
   *         i = 0
   *
   */
  __pyx_tuple__58 =
      PyTuple_Pack(9, __pyx_n_s_self, __pyx_n_s_i, __pyx_n_s_t,
                   __pyx_n_s_is_alias, __pyx_n_s_alias, __pyx_n_s_rf,
                   __pyx_n_s_py, __pyx_n_s_name, __pyx_n_s_types);
  if (unlikely(!__pyx_tuple__58)) __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__58);
  __Pyx_GIVEREF(__pyx_tuple__58);
  __pyx_codeobj__59 = (PyObject *)__Pyx_PyCode_New(
      1, 0, 9, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__58, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_gen, 83, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__59)) __PYX_ERR(0, 83, __pyx_L1_error)

  /* "rfc.py":163
   *
   *
   * def gen(toks, parsed):             # <<<<<<<<<<<<<<
   *     cg = Codegen(toks, parsed)
   *     return cg.gen()
   */
  __pyx_tuple__60 =
      PyTuple_Pack(3, __pyx_n_s_toks, __pyx_n_s_parsed, __pyx_n_s_cg);
  if (unlikely(!__pyx_tuple__60)) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__60);
  __Pyx_GIVEREF(__pyx_tuple__60);
  __pyx_codeobj__61 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__60, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_gen, 163, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__61)) __PYX_ERR(0, 163, __pyx_L1_error)

  /* "rfc.py":172
   * class Parser(Transformer):
   *
   *     def __init__(self):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens = []
   *         self.suite_tokens = []
   */
  __pyx_tuple__62 = PyTuple_Pack(1, __pyx_n_s_self);
  if (unlikely(!__pyx_tuple__62)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__62);
  __Pyx_GIVEREF(__pyx_tuple__62);
  __pyx_codeobj__63 = (PyObject *)__Pyx_PyCode_New(
      1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__62, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_init, 172, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__63)) __PYX_ERR(0, 172, __pyx_L1_error)

  /* "rfc.py":176
   *         self.suite_tokens = []
   *
   *     def start(self, _):             # <<<<<<<<<<<<<<
   *         return {
   *             'decorated': self.decorator_tokens,
   */
  __pyx_tuple__64 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s__36);
  if (unlikely(!__pyx_tuple__64)) __PYX_ERR(0, 176, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__64);
  __Pyx_GIVEREF(__pyx_tuple__64);
  __pyx_codeobj__65 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__64, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_start, 176, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__65)) __PYX_ERR(0, 176, __pyx_L1_error)

  /* "rfc.py":182
   *         }
   *
   *     def decorator(self, _):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   */
  __pyx_tuple__66 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s__36);
  if (unlikely(!__pyx_tuple__66)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__66);
  __Pyx_GIVEREF(__pyx_tuple__66);
  __pyx_codeobj__67 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__66, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_decorator, 182,
      __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__67)) __PYX_ERR(0, 182, __pyx_L1_error)

  /* "rfc.py":185
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   *     def suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */
  __pyx_tuple__68 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s__36);
  if (unlikely(!__pyx_tuple__68)) __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__68);
  __Pyx_GIVEREF(__pyx_tuple__68);
  __pyx_codeobj__69 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__68, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_suite, 185, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__69)) __PYX_ERR(0, 185, __pyx_L1_error)

  /* "rfc.py":188
   *         self.suite_tokens += [_[0], _[-1]]
   *
   *     def class_suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */
  __pyx_tuple__70 = PyTuple_Pack(2, __pyx_n_s_self, __pyx_n_s__36);
  if (unlikely(!__pyx_tuple__70)) __PYX_ERR(0, 188, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__70);
  __Pyx_GIVEREF(__pyx_tuple__70);
  __pyx_codeobj__71 = (PyObject *)__Pyx_PyCode_New(
      2, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__70, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_class_suite, 188,
      __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__71)) __PYX_ERR(0, 188, __pyx_L1_error)

  /* "rfc.py":201
   *
   *
   * def compile(code):             # <<<<<<<<<<<<<<
   *     toks = parser.lex(code)
   *     parsed = parser.parse(code)
   */
  __pyx_tuple__72 =
      PyTuple_Pack(3, __pyx_n_s_code, __pyx_n_s_toks, __pyx_n_s_parsed);
  if (unlikely(!__pyx_tuple__72)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__72);
  __Pyx_GIVEREF(__pyx_tuple__72);
  __pyx_codeobj__73 = (PyObject *)__Pyx_PyCode_New(
      1, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__72, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_compile, 201, __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__73)) __PYX_ERR(0, 201, __pyx_L1_error)

  /* "rfc.py":207
   *
   *
   * def compile_file(filename):             # <<<<<<<<<<<<<<
   *     with open(filename) as file:
   *         code = file.read()
   */
  __pyx_tuple__74 = PyTuple_Pack(4, __pyx_n_s_filename, __pyx_n_s_file,
                                 __pyx_n_s_code, __pyx_n_s_output);
  if (unlikely(!__pyx_tuple__74)) __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__74);
  __Pyx_GIVEREF(__pyx_tuple__74);
  __pyx_codeobj__75 = (PyObject *)__Pyx_PyCode_New(
      1, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_tuple__74, __pyx_empty_tuple, __pyx_empty_tuple,
      __pyx_kp_s_src_rfc_py_rfc_py, __pyx_n_s_compile_file, 207,
      __pyx_empty_bytes);
  if (unlikely(!__pyx_codeobj__75)) __PYX_ERR(0, 207, __pyx_L1_error)

  /* "rfc.py":216
   * if __name__ == "__main__":
   *     arg_parser = ArgumentParser(description='The bootstrap compiler for
   * Raft.') arg_parser.add_argument('input', help='Input file or directory') #
   * <<<<<<<<<<<<<< arg_parser.add_argument('-o', metavar='output', help='Output
   * file') args = arg_parser.parse_args()
   */
  __pyx_tuple__76 = PyTuple_Pack(1, __pyx_n_u_input);
  if (unlikely(!__pyx_tuple__76)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__76);
  __Pyx_GIVEREF(__pyx_tuple__76);

  /* "rfc.py":217
   *     arg_parser = ArgumentParser(description='The bootstrap compiler for
   * Raft.') arg_parser.add_argument('input', help='Input file or directory')
   *     arg_parser.add_argument('-o', metavar='output', help='Output file') #
   * <<<<<<<<<<<<<< args = arg_parser.parse_args()
   *
   */
  __pyx_tuple__77 = PyTuple_Pack(1, __pyx_kp_u_o);
  if (unlikely(!__pyx_tuple__77)) __PYX_ERR(0, 217, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__77);
  __Pyx_GIVEREF(__pyx_tuple__77);

  /* "rfc.py":228
   *         nuitka_main = args.input + '/__main__.py'
   *     else:
   *         nuitka_main = args.input[:-3] + '.py'             # <<<<<<<<<<<<<<
   *         pyfiles += [compile_file(args.input)]
   *
   */
  __pyx_slice__78 = PySlice_New(Py_None, __pyx_int_neg_3, Py_None);
  if (unlikely(!__pyx_slice__78)) __PYX_ERR(0, 228, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__78);
  __Pyx_GIVEREF(__pyx_slice__78);

  /* "rfc.py":235
   *
   *     for f in pyfiles:
   *         with open(f[0], 'w') as file: file.write(prologue + 'def
   * test(func): func(); return func\n' + f[1])             # <<<<<<<<<<<<<<
   *
   *     if run(['python3', '-B', nuitka_main]).returncode == 0:
   */
  __pyx_tuple__79 = PyTuple_Pack(3, Py_None, Py_None, Py_None);
  if (unlikely(!__pyx_tuple__79)) __PYX_ERR(0, 235, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__79);
  __Pyx_GIVEREF(__pyx_tuple__79);

  /* "rfc.py":239
   *     if run(['python3', '-B', nuitka_main]).returncode == 0:
   *         for f in pyfiles:
   *             with open(f[0], 'w') as file: file.write(prologue + 'test =
   * lambda _: _\n' + f[1] + epilogue)             # <<<<<<<<<<<<<<
   *
   *         nuitka_base = path.splitext(path.basename(nuitka_main))[0]
   */
  __pyx_tuple__80 = PyTuple_Pack(3, Py_None, Py_None, Py_None);
  if (unlikely(!__pyx_tuple__80)) __PYX_ERR(0, 239, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__80);
  __Pyx_GIVEREF(__pyx_tuple__80);
  __Pyx_RefNannyFinishContext();
  return 0;
__pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  __pyx_int_0 = PyInt_FromLong(0);
  if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1);
  if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2 = PyInt_FromLong(2);
  if (unlikely(!__pyx_int_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_1 = PyInt_FromLong(-1);
  if (unlikely(!__pyx_int_neg_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_3 = PyInt_FromLong(-3);
  if (unlikely(!__pyx_int_neg_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
__pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initrfc(void); /*proto*/
PyMODINIT_FUNC initrfc(void)
#else
PyMODINIT_FUNC PyInit_rfc(void); /*proto*/
PyMODINIT_FUNC PyInit_rfc(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  int __pyx_t_9;
  Py_ssize_t __pyx_t_10;
  PyObject *(*__pyx_t_11)(PyObject *);
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  PyObject *__pyx_t_15 = NULL;
  PyObject *__pyx_t_16 = NULL;
  int __pyx_t_17;
  __Pyx_RefNannyDeclarations
#if RFC_REFNANNY
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
    PyErr_Clear();
    __Pyx_RefNanny = __Pyx_RefNannyImportAPI("RFC.Runtime.refnanny");
    if (!__Pyx_RefNanny) Py_FatalError("failed to import 'refnanny' module");
  }
#endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_rfc(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_tuple = PyTuple_New(0);
  if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0);
  if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0);
  if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(0, 1, __pyx_L1_error)
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
#ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
#endif
/*--- Library function declarations ---*/
/*--- Threads initialization code ---*/
#if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
#ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
#endif
#endif
/*--- Module creation code ---*/
#if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("rfc", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  Py_XINCREF(__pyx_m);
#else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
#endif
  if (unlikely(!__pyx_m)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_d = PyModule_GetDict(__pyx_m);
  if (unlikely(!__pyx_d)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME);
  if (unlikely(!__pyx_b)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_RFC_runtime = PyImport_AddModule((char *)"RFC_runtime");
  if (unlikely(!__pyx_RFC_runtime)) __PYX_ERR(0, 1, __pyx_L1_error)
#if RFC_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
#endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0)
    __PYX_ERR(0, 1, __pyx_L1_error);
  /*--- Initialize various global constants etc. ---*/
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
#if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || \
                             __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0)
    __PYX_ERR(0, 1, __pyx_L1_error)
#endif
  if (__pyx_module_is_main_rfc) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0)
      __PYX_ERR(0, 1, __pyx_L1_error)
  }
#if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict();
    if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "rfc")) {
      if (unlikely(PyDict_SetItemString(modules, "rfc", __pyx_m) < 0))
        __PYX_ERR(0, 1, __pyx_L1_error)
    }
  }
#endif
  /*--- Builtin init code ---*/
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Constants init code ---*/
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
/*--- Global init code ---*/
/*--- Variable export code ---*/
/*--- Function export code ---*/
/*--- Type init code ---*/
/*--- Type import code ---*/
/*--- Variable import code ---*/
/*--- Function import code ---*/
/*--- Execution code ---*/
#if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
#endif

  /* "rfc.py":1
   * import os             # <<<<<<<<<<<<<<
   *
   * from tempfile import mkdtemp
   */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_os, 0, 0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_os, __pyx_t_1) < 0)
    __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":3
   * import os
   *
   * from tempfile import mkdtemp             # <<<<<<<<<<<<<<
   * from glob import glob
   * from os import path
   */
  __pyx_t_1 = PyList_New(1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_mkdtemp);
  __Pyx_GIVEREF(__pyx_n_s_mkdtemp);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_mkdtemp);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_tempfile, __pyx_t_1, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_mkdtemp);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_mkdtemp, __pyx_t_1) < 0)
    __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":4
   *
   * from tempfile import mkdtemp
   * from glob import glob             # <<<<<<<<<<<<<<
   * from os import path
   * from argparse import ArgumentParser
   */
  __pyx_t_2 = PyList_New(1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_glob);
  __Pyx_GIVEREF(__pyx_n_s_glob);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_glob);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_glob, __pyx_t_2, 0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_glob);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_glob, __pyx_t_2) < 0)
    __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":5
   * from tempfile import mkdtemp
   * from glob import glob
   * from os import path             # <<<<<<<<<<<<<<
   * from argparse import ArgumentParser
   * from yapf.yapflib.yapf_api import FormatCode
   */
  __pyx_t_1 = PyList_New(1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_path);
  __Pyx_GIVEREF(__pyx_n_s_path);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_path);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_os, __pyx_t_1, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_path);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_path, __pyx_t_1) < 0)
    __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":6
   * from glob import glob
   * from os import path
   * from argparse import ArgumentParser             # <<<<<<<<<<<<<<
   * from yapf.yapflib.yapf_api import FormatCode
   * from lark.lexer import Token
   */
  __pyx_t_2 = PyList_New(1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_ArgumentParser);
  __Pyx_GIVEREF(__pyx_n_s_ArgumentParser);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_ArgumentParser);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_argparse, __pyx_t_2, 0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_ArgumentParser);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_ArgumentParser, __pyx_t_2) < 0)
    __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":7
   * from os import path
   * from argparse import ArgumentParser
   * from yapf.yapflib.yapf_api import FormatCode             # <<<<<<<<<<<<<<
   * from lark.lexer import Token
   * from subprocess import run, PIPE
   */
  __pyx_t_1 = PyList_New(1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_FormatCode);
  __Pyx_GIVEREF(__pyx_n_s_FormatCode);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_FormatCode);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_yapf_yapflib_yapf_api, __pyx_t_1, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_FormatCode);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_FormatCode, __pyx_t_1) < 0)
    __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":8
   * from argparse import ArgumentParser
   * from yapf.yapflib.yapf_api import FormatCode
   * from lark.lexer import Token             # <<<<<<<<<<<<<<
   * from subprocess import run, PIPE
   * from shutil import rmtree, move
   */
  __pyx_t_2 = PyList_New(1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_Token);
  __Pyx_GIVEREF(__pyx_n_s_Token);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_Token);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_lark_lexer, __pyx_t_2, 0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_Token);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Token, __pyx_t_2) < 0)
    __PYX_ERR(0, 8, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":9
   * from yapf.yapflib.yapf_api import FormatCode
   * from lark.lexer import Token
   * from subprocess import run, PIPE             # <<<<<<<<<<<<<<
   * from shutil import rmtree, move
   *
   */
  __pyx_t_1 = PyList_New(2);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_run);
  __Pyx_GIVEREF(__pyx_n_s_run);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_run);
  __Pyx_INCREF(__pyx_n_s_PIPE);
  __Pyx_GIVEREF(__pyx_n_s_PIPE);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_PIPE);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_subprocess, __pyx_t_1, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_run);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_run, __pyx_t_1) < 0)
    __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_PIPE);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_PIPE, __pyx_t_1) < 0)
    __PYX_ERR(0, 9, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":10
   * from lark.lexer import Token
   * from subprocess import run, PIPE
   * from shutil import rmtree, move             # <<<<<<<<<<<<<<
   *
   * class ForeignKeywordException(Exception):
   */
  __pyx_t_2 = PyList_New(2);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_rmtree);
  __Pyx_GIVEREF(__pyx_n_s_rmtree);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_rmtree);
  __Pyx_INCREF(__pyx_n_s_move);
  __Pyx_GIVEREF(__pyx_n_s_move);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_n_s_move);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_shutil, __pyx_t_2, 0);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_rmtree);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_rmtree, __pyx_t_2) < 0)
    __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_move);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_move, __pyx_t_2) < 0)
    __PYX_ERR(0, 10, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":12
   * from shutil import rmtree, move
   *
   * class ForeignKeywordException(Exception):             # <<<<<<<<<<<<<<
   *     def __init__(self, keyword):
   *         msg = f'usage of foreign keyword: `{keyword}`'
   */
  __pyx_t_1 = PyTuple_New(1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  __Pyx_GIVEREF(((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  PyTuple_SET_ITEM(__pyx_t_1, 0,
                   ((PyObject *)(&((PyTypeObject *)PyExc_Exception)[0])));
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_Py3MetaclassPrepare(
      __pyx_t_2, __pyx_t_1, __pyx_n_s_ForeignKeywordException,
      __pyx_n_s_ForeignKeywordException, (PyObject *)NULL, __pyx_n_s_rfc,
      (PyObject *)NULL);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "rfc.py":13
   *
   * class ForeignKeywordException(Exception):
   *     def __init__(self, keyword):             # <<<<<<<<<<<<<<
   *         msg = f'usage of foreign keyword: `{keyword}`'
   *         super(Exception, self).__init__(self, msg)
   */
  __pyx_t_4 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_23ForeignKeywordException_1__init__, 0,
      __pyx_n_s_ForeignKeywordException___init, NULL, __pyx_n_s_rfc, __pyx_d,
      ((PyObject *)__pyx_codeobj__41));
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyObject_SetItem(__pyx_t_3, __pyx_n_s_init, __pyx_t_4) < 0)
    __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;

  /* "rfc.py":12
   * from shutil import rmtree, move
   *
   * class ForeignKeywordException(Exception):             # <<<<<<<<<<<<<<
   *     def __init__(self, keyword):
   *         msg = f'usage of foreign keyword: `{keyword}`'
   */
  __pyx_t_4 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_ForeignKeywordException,
                                   __pyx_t_1, __pyx_t_3, NULL, 0, 0);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_ForeignKeywordException, __pyx_t_4) < 0)
    __PYX_ERR(0, 12, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":18
   *
   *
   * class Alias:             # <<<<<<<<<<<<<<
   *
   *     def __init__(self, rf, py):
   */
  __pyx_t_1 = __Pyx_Py3MetaclassPrepare(
      (PyObject *)NULL, __pyx_empty_tuple, __pyx_n_s_Alias, __pyx_n_s_Alias,
      (PyObject *)NULL, __pyx_n_s_rfc, (PyObject *)NULL);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

  /* "rfc.py":20
   * class Alias:
   *
   *     def __init__(self, rf, py):             # <<<<<<<<<<<<<<
   *         self.rf, self.py = rf, py
   *
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_5Alias_1__init__, 0, __pyx_n_s_Alias___init, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__43));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 20, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_init, __pyx_t_2) < 0)
    __PYX_ERR(0, 20, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":18
   *
   *
   * class Alias:             # <<<<<<<<<<<<<<
   *
   *     def __init__(self, rf, py):
   */
  __pyx_t_2 = __Pyx_Py3ClassCreate(((PyObject *)&__Pyx_DefaultClassType),
                                   __pyx_n_s_Alias, __pyx_empty_tuple,
                                   __pyx_t_1, NULL, 0, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Alias, __pyx_t_2) < 0)
    __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":24
   *
   *
   * class Codegen:             # <<<<<<<<<<<<<<
   *     aliases = [
   *         Alias('use', 'import'),
   */
  __pyx_t_1 = __Pyx_Py3MetaclassPrepare(
      (PyObject *)NULL, __pyx_empty_tuple, __pyx_n_s_Codegen, __pyx_n_s_Codegen,
      (PyObject *)NULL, __pyx_n_s_rfc, (PyObject *)NULL);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

  /* "rfc.py":26
   * class Codegen:
   *     aliases = [
   *         Alias('use', 'import'),             # <<<<<<<<<<<<<<
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Alias);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__44, NULL);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 26, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":27
   *     aliases = [
   *         Alias('use', 'import'),
   *         Alias('fn', 'def'),             # <<<<<<<<<<<<<<
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Alias);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 27, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__45, NULL);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 27, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":28
   *         Alias('use', 'import'),
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),             # <<<<<<<<<<<<<<
   *         Alias('true', 'True'),
   *         Alias('false', 'False'),
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Alias);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 28, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__46, NULL);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 28, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":29
   *         Alias('fn', 'def'),
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),             # <<<<<<<<<<<<<<
   *         Alias('false', 'False'),
   *     ]
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Alias);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__47, NULL);
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":30
   *         Alias('struct', 'class'),
   *         Alias('true', 'True'),
   *         Alias('false', 'False'),             # <<<<<<<<<<<<<<
   *     ]
   *
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Alias);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__48, NULL);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 30, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":25
   *
   * class Codegen:
   *     aliases = [             # <<<<<<<<<<<<<<
   *         Alias('use', 'import'),
   *         Alias('fn', 'def'),
   */
  __pyx_t_2 = PyList_New(5);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_4);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_5);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_6);
  PyList_SET_ITEM(__pyx_t_2, 3, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_7);
  PyList_SET_ITEM(__pyx_t_2, 4, __pyx_t_7);
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  __pyx_t_7 = 0;
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_aliases, __pyx_t_2) < 0)
    __PYX_ERR(0, 25, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":33
   *     ]
   *
   *     foreign_keywords = ['not', 'and', 'or']             # <<<<<<<<<<<<<<
   *
   *     def __init__(self, toks, parsed):
   */
  __pyx_t_2 = PyList_New(3);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_u_not_2);
  __Pyx_GIVEREF(__pyx_n_u_not_2);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_u_not_2);
  __Pyx_INCREF(__pyx_n_u_and_2);
  __Pyx_GIVEREF(__pyx_n_u_and_2);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_n_u_and_2);
  __Pyx_INCREF(__pyx_n_u_or_2);
  __Pyx_GIVEREF(__pyx_n_u_or_2);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_n_u_or_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_foreign_keywords, __pyx_t_2) < 0)
    __PYX_ERR(0, 33, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":35
   *     foreign_keywords = ['not', 'and', 'or']
   *
   *     def __init__(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.output = [[0, '']]
   *         self.transform(toks, parsed)
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_7Codegen_1__init__, 0, __pyx_n_s_Codegen___init, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__50));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 35, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_init, __pyx_t_2) < 0)
    __PYX_ERR(0, 35, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":39
   *         self.transform(toks, parsed)
   *
   *     def newline(self, indent_offset=0, content=''):             #
   * <<<<<<<<<<<<<< last = self.output[-1][0] self.output += [[last +
   * indent_offset, content]]
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_7Codegen_3newline, 0, __pyx_n_s_Codegen_newline, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__52));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_CyFunction_SetDefaultsTuple(__pyx_t_2, __pyx_tuple__53);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_newline, __pyx_t_2) < 0)
    __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":43
   *         self.output += [[last + indent_offset, content]]
   *
   *     def line(self, code):             # <<<<<<<<<<<<<<
   *         self.output[-1][1] += code
   *
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_7Codegen_5line, 0, __pyx_n_s_Codegen_line, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__55));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_line, __pyx_t_2) < 0)
    __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":46
   *         self.output[-1][1] += code
   *
   *     def transform(self, toks, parsed):             # <<<<<<<<<<<<<<
   *         self.toks = []
   *         toks = list(toks)
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_7Codegen_7transform, 0, __pyx_n_s_Codegen_transform,
      NULL, __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__57));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_transform, __pyx_t_2) < 0)
    __PYX_ERR(0, 46, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":83
   *
   *
   *     def gen(self):             # <<<<<<<<<<<<<<
   *         i = 0
   *
   */
  __pyx_t_2 = __Pyx_CyFunction_NewEx(&__pyx_mdef_3rfc_7Codegen_9gen, 0,
                                     __pyx_n_s_Codegen_gen, NULL, __pyx_n_s_rfc,
                                     __pyx_d, ((PyObject *)__pyx_codeobj__59));
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyObject_SetItem(__pyx_t_1, __pyx_n_s_gen, __pyx_t_2) < 0)
    __PYX_ERR(0, 83, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":24
   *
   *
   * class Codegen:             # <<<<<<<<<<<<<<
   *     aliases = [
   *         Alias('use', 'import'),
   */
  __pyx_t_2 = __Pyx_Py3ClassCreate(((PyObject *)&__Pyx_DefaultClassType),
                                   __pyx_n_s_Codegen, __pyx_empty_tuple,
                                   __pyx_t_1, NULL, 0, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Codegen, __pyx_t_2) < 0)
    __PYX_ERR(0, 24, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":163
   *
   *
   * def gen(toks, parsed):             # <<<<<<<<<<<<<<
   *     cg = Codegen(toks, parsed)
   *     return cg.gen()
   */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_3rfc_1gen, 0, __pyx_n_s_gen,
                                     NULL, __pyx_n_s_rfc, __pyx_d,
                                     ((PyObject *)__pyx_codeobj__61));
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_gen, __pyx_t_1) < 0)
    __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":168
   *
   *
   * from lark import Lark, Transformer             # <<<<<<<<<<<<<<
   *
   * class Parser(Transformer):
   */
  __pyx_t_1 = PyList_New(2);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_Lark);
  __Pyx_GIVEREF(__pyx_n_s_Lark);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_Lark);
  __Pyx_INCREF(__pyx_n_s_Transformer);
  __Pyx_GIVEREF(__pyx_n_s_Transformer);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_Transformer);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_lark, __pyx_t_1, 0);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_Lark);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Lark, __pyx_t_1) < 0)
    __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_Transformer);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Transformer, __pyx_t_1) < 0)
    __PYX_ERR(0, 168, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":170
   * from lark import Lark, Transformer
   *
   * class Parser(Transformer):             # <<<<<<<<<<<<<<
   *
   *     def __init__(self):
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_Transformer);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyTuple_New(1);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_CalculateMetaclass(NULL, __pyx_t_1);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = __Pyx_Py3MetaclassPrepare(__pyx_t_2, __pyx_t_1, __pyx_n_s_Parser,
                                        __pyx_n_s_Parser, (PyObject *)NULL,
                                        __pyx_n_s_rfc, (PyObject *)NULL);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);

  /* "rfc.py":172
   * class Parser(Transformer):
   *
   *     def __init__(self):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens = []
   *         self.suite_tokens = []
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_6Parser_1__init__, 0, __pyx_n_s_Parser___init, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__63));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_7, __pyx_n_s_init, __pyx_t_6) < 0)
    __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":176
   *         self.suite_tokens = []
   *
   *     def start(self, _):             # <<<<<<<<<<<<<<
   *         return {
   *             'decorated': self.decorator_tokens,
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_6Parser_3start, 0, __pyx_n_s_Parser_start, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__65));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 176, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_7, __pyx_n_s_start, __pyx_t_6) < 0)
    __PYX_ERR(0, 176, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":182
   *         }
   *
   *     def decorator(self, _):             # <<<<<<<<<<<<<<
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_6Parser_5decorator, 0, __pyx_n_s_Parser_decorator, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__67));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_7, __pyx_n_s_decorator, __pyx_t_6) < 0)
    __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":185
   *         self.decorator_tokens += [_[0], _[1], _[-1]]
   *
   *     def suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_6Parser_7suite, 0, __pyx_n_s_Parser_suite, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__69));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_7, __pyx_n_s_suite, __pyx_t_6) < 0)
    __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":188
   *         self.suite_tokens += [_[0], _[-1]]
   *
   *     def class_suite(self, _):             # <<<<<<<<<<<<<<
   *         self.suite_tokens += [_[0], _[-1]]
   *
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_6Parser_9class_suite, 0, __pyx_n_s_Parser_class_suite,
      NULL, __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__71));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 188, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyObject_SetItem(__pyx_t_7, __pyx_n_s_class_suite, __pyx_t_6) < 0)
    __PYX_ERR(0, 188, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":170
   * from lark import Lark, Transformer
   *
   * class Parser(Transformer):             # <<<<<<<<<<<<<<
   *
   *     def __init__(self):
   */
  __pyx_t_6 = __Pyx_Py3ClassCreate(__pyx_t_2, __pyx_n_s_Parser, __pyx_t_1,
                                   __pyx_t_7, NULL, 0, 0);
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_Parser, __pyx_t_6) < 0)
    __PYX_ERR(0, 170, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_7);
  __pyx_t_7 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;

  /* "rfc.py":191
   *         self.suite_tokens += [_[0], _[-1]]
   *
   * grammar = 'start: (typedef | funcdef | decorated | (import_stmt ";") |
   * classdef | async_funcdef)*\n\n!decorator: "#" "[" dotted_name [ "("
   * [arguments] ")" ] "]"\ndecorators: decorator+\ndecorated: decorators
   * (classdef | funcdef | async_funcdef)\n\ntypedef: "type" NAME [(":"
   * typelist) | ("=" type)] ";"\ntype: (dotted_name ["[" typelist "]"]) |
   * "None"\ntypelist: type ("," type)*\n\nasync_funcdef: "async"
   * funcdef\nfuncdef: "fn" NAME "(" parameters? ")" ["->" type]
   * suite\nstruct_funcdef: "fn" NAME "(" "self" ["," parameters] ")" ["->"
   * type] suite\n\nparameters: paramvalue ("," paramvalue)* ["," [ starparams |
   * kwparams]]\n        | starparams\n          | kwparams\nstarparams: "*"
   * typedparam? ("," paramvalue)* ["," kwparams]\nkwparams: "**"
   * typedparam\n\n?paramvalue: typedparam ["=" test]\n?typedparam: NAME ":"
   * type\n\nvarargslist: (vfpdef ["=" test] ("," vfpdef ["=" test])* ["," [ "*"
   * [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef [","]]] | "**" vfpdef
   * [","]]]\n  | "*" [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef
   * [","]]]\n  | "**" vfpdef [","])\n\nvfpdef: NAME\n\n?stmt: simple_stmt |
   * compound_stmt\n?simple_stmt: small_stmt ";"\n?small_stmt: (expr_stmt |
   * del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: testlist_star_expr
   * (annassign | augassign (yield_expr|testlist)\n         | ("="
   * (yield_expr|testlist_star_expr))*)\nannassign: ":" type "="
   * test\n?testlist_star_expr: (test|star_expr) ("," (test|star_expr))*
   * [","]\n!augassign: ("+=" | "-=" | "*=" | "@=" | "/=" | "%=" | "&=" | "|=" |
   * "^=" | "<<=" | ">>=" | "**=")\ndel_stmt: "del" exprlist\n?flow_stmt:
   * break_stmt | continue_stmt | return_stmt | raise_stmt |
   * yield_stmt\nbreak_stmt: "break"\ncontinue_stmt: "continue"\nreturn_stmt:
   * "return" [testlist]\nyield_stmt: yield_expr\nraise_stmt: "raise" [test
   * ["from" test]]\nimport_stmt: import_name | import_from\nimport_name: "use"
   * dotted_as_names\nimport_from: "from" dotted_name "use" ("*" | "("
   * import_as_names ")" | import_as_names)\nimport_as_name: NAME ["as"
   * NAME]\ndotted_as_name: dotted_name ["as" NAME]\nimport_as_names:
   * import_as_name ("," import_as_name)* [","]\ndotted_as_names: dotted_as_name
   * ("," dotted_as_name)*\ndotted_name: NAME ("." NAME)*\nassert_stmt: "assert"
   * test ["," test]\n\ncompound_stmt: if_stmt | while_stmt | for_stmt |
   * try_stmt | with_stmt | typedef | funcdef | classdef | decorated |
   * async_stmt\nasync_stmt: "async" (funcdef | with_stmt | for_stmt)\nif_stmt:
   * "if" test suite ("else" "if" test suite)* ["else" suite]\nwhile_stmt:
   * "while" test suite ["else" suite]\nfor_stmt: "for" exprlist "in" testlist
   * suite ["else" suite]\ntry_stmt: ("try" suite ((except_clause suite)+
   * ["else" suite] ["finally" suite] | "finally" suite))\nwith_stmt: "with"
   * with_item ("," with_item)*  suite\nwith_item: test ["as"
   * expr]\nexcept_clause: "except" [test ["as" NAME]]\n!suite: "{" stmt*
   * "}"\n\n?test: or_test ("if" or_test "else" test)? | lambdef\n?test_nocond:
   * or_test | lambdef_nocond\nlambdef: "lambda" [varargslist] ":"
   * test\nlambdef_nocond: "lambda" [varargslist] ":" test_nocond\n?or_test:
   * and_test ("||" and_test)*\n?and_test: not_test ("&&" not_test)*\n?not_test:
   * "!" not_test -> not\n         | comparison\n?comparison: expr (_comp_op
   * expr)*\nstar_expr: "*" expr\n?expr: xor_expr ("|" xor_expr)*\n?xor_expr:
   * and_expr ("^" and_expr)*\n?and_expr: shift_expr ("&"
   * shift_expr)*\n?shift_expr: arith_expr (_shift_op arith_expr)*\n?arith_expr:
   * term (_add_op term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op
   * factor | power\n\n!_factor_op: "+"|"-"|"~"\n!_add_op: "+"|"-"\n!_shift_op:
   * "<<"|">>"\n!_mul_op: "*"|"@"|"/"|"%"|"//"\n!_comp_op:
   * "<"|">"|"=="|">="|"<="|"!="|"in"|"is"\n\n?power: await_expr ("**"
   * factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "await"\n\n?atom_expr:
   * atom_expr "(" [arguments] ")"      -> funccall\n          | atom_expr "["
   * subscriptlist "]"  -> getitem\n          | atom_expr "." NAME -> getattr\n
   * | atom\n\n?atom: "(" [yield_expr|testlist_comp] ")" -> tuple\n     | "["
   * [testlist_comp] "]"  -> list\n     | "{" [dictorsetmaker] "}" -> dict\n |
   * NAME -> var\n     | number | string+\n     | "(" test ")"\n     | "..." ->
   * ellipsis\n     | "None"    -> const_none\n     | "true"    -> const_true\n
   * | "false"   -> const_false\n\n?testlist_comp: (test|star_expr) [comp_for |
   * ("," (test|star_expr))+ [","] | ","]\nsubscriptlist: subscript (","
   * subscript)* [","]\nsubscript: test | [test] ":" [test] [sliceop]\nsliceop:
   * ":" [test]\nexprlist: (expr|star_expr) ("," (expr|star_expr))*
   * [","]\ntestlist: test ("," test)* [","]\ndictorsetmaker: ( ((test ":" test
   * | "**" expr) (comp_for | ("," (test ":" test | "**" expr))* [","])) |
   * ((test | star_expr) (comp_for | ("," (test | star_expr))* [","]))
   * )\n\nclassdef: "struct" NAME ["(" [arguments] ")"]
   * class_suite\n!class_suite: "{" (struct_funcdef | funcdef | decorated)*
   * "}"\n\narguments: argvalue ("," argvalue)*  ("," [ starargs | kwargs])?\n
   * | starargs\n        | kwargs\n         | test comp_for\n\nstarargs: "*"
   * test ("," "*" test)* ("," argvalue)* ["," kwargs]\nkwargs: "**"
   * test\n\n?argvalue: test ("=" test)?\n\n\n\ncomp_iter: comp_for | comp_if |
   * async_for\nasync_for: "async" "for" exprlist "in" or_test
   * [comp_iter]\ncomp_for: "for" exprlist "in" or_test [comp_iter]\ncomp_if:
   * "if" test_nocond [comp_iter]\n\nyield_expr: "yield" [yield_arg]\nyield_arg:
   * "from" test | testlist\n\n\nnumber: DEC_NUMBER | HEX_NUMBER | BIN_NUMBER |
   * OCT_NUMBER | FLOAT_NUMBER | IMAG_NUMBER\nstring: STRING |
   * LONG_STRING\n\nNAME: /(r#)?[a-zA-Z_]\\w*[inserted by RFC to avoid comment
   * closer]/\nCOMMENT: /\\/\\/[^\\n]*[inserted by RFC to avoid comment
   * closer]/\n_NEWLINE: ( /\\r?\\n[\\t ]*[inserted by RFC to avoid comment
   * closer]/ | COMMENT )+\n\n\nSTRING :
   * /[ubf]?r?("(?!"").*?(?<!\\\\)(\\\\\\\\)*?"|\'(?!\'\').*?(?<!\\\\)(\\\\\\\\)*?\')/i\nLONG_STRING:
   * /[ubf]?r?(""".*?(?<!\\\\)(\\\\\\\\)*?"""|\'\'\'.*?(?<!\\\\)(\\\\\\\\)*?\'\'\')/is\n\nDEC_NUMBER:
   * /0|[1-9]\\d*[inserted by RFC to avoid comment closer]/i\nHEX_NUMBER.2:
   * /0x[\\da-f]*[inserted by RFC to avoid comment closer]/i\nOCT_NUMBER.2:
   * /0o[0-7]*[inserted by RFC to avoid comment closer]/i\nBIN_NUMBER.2 :
   * /0b[0-1]*[inserted by RFC to avoid comment closer]/i\nFLOAT_NUMBER.2:
   * /((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2:
   * /\\d+j/i | FLOAT_NUMBER "j"i\n\n%ignore /[\\t \\f]+/\n%ignore _NEWLINE\n'
   * # <<<<<<<<<<<<<<
   *
   * parser = Lark(
   */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_grammar,
                     __pyx_kp_u_start_typedef_funcdef_decorated) < 0)
    __PYX_ERR(0, 191, __pyx_L1_error)

  /* "rfc.py":193
   * grammar = 'start: (typedef | funcdef | decorated | (import_stmt ";") |
   * classdef | async_funcdef)*\n\n!decorator: "#" "[" dotted_name [ "("
   * [arguments] ")" ] "]"\ndecorators: decorator+\ndecorated: decorators
   * (classdef | funcdef | async_funcdef)\n\ntypedef: "type" NAME [(":"
   * typelist) | ("=" type)] ";"\ntype: (dotted_name ["[" typelist "]"]) |
   * "None"\ntypelist: type ("," type)*\n\nasync_funcdef: "async"
   * funcdef\nfuncdef: "fn" NAME "(" parameters? ")" ["->" type]
   * suite\nstruct_funcdef: "fn" NAME "(" "self" ["," parameters] ")" ["->"
   * type] suite\n\nparameters: paramvalue ("," paramvalue)* ["," [ starparams |
   * kwparams]]\n        | starparams\n          | kwparams\nstarparams: "*"
   * typedparam? ("," paramvalue)* ["," kwparams]\nkwparams: "**"
   * typedparam\n\n?paramvalue: typedparam ["=" test]\n?typedparam: NAME ":"
   * type\n\nvarargslist: (vfpdef ["=" test] ("," vfpdef ["=" test])* ["," [ "*"
   * [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef [","]]] | "**" vfpdef
   * [","]]]\n  | "*" [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef
   * [","]]]\n  | "**" vfpdef [","])\n\nvfpdef: NAME\n\n?stmt: simple_stmt |
   * compound_stmt\n?simple_stmt: small_stmt ";"\n?small_stmt: (expr_stmt |
   * del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: testlist_star_expr
   * (annassign | augassign (yield_expr|testlist)\n         | ("="
   * (yield_expr|testlist_star_expr))*)\nannassign: ":" type "="
   * test\n?testlist_star_expr: (test|star_expr) ("," (test|star_expr))*
   * [","]\n!augassign: ("+=" | "-=" | "*=" | "@=" | "/=" | "%=" | "&=" | "|=" |
   * "^=" | "<<=" | ">>=" | "**=")\ndel_stmt: "del" exprlist\n?flow_stmt:
   * break_stmt | continue_stmt | return_stmt | raise_stmt |
   * yield_stmt\nbreak_stmt: "break"\ncontinue_stmt: "continue"\nreturn_stmt:
   * "return" [testlist]\nyield_stmt: yield_expr\nraise_stmt: "raise" [test
   * ["from" test]]\nimport_stmt: import_name | import_from\nimport_name: "use"
   * dotted_as_names\nimport_from: "from" dotted_name "use" ("*" | "("
   * import_as_names ")" | import_as_names)\nimport_as_name: NAME ["as"
   * NAME]\ndotted_as_name: dotted_name ["as" NAME]\nimport_as_names:
   * import_as_name ("," import_as_name)* [","]\ndotted_as_names: dotted_as_name
   * ("," dotted_as_name)*\ndotted_name: NAME ("." NAME)*\nassert_stmt: "assert"
   * test ["," test]\n\ncompound_stmt: if_stmt | while_stmt | for_stmt |
   * try_stmt | with_stmt | typedef | funcdef | classdef | decorated |
   * async_stmt\nasync_stmt: "async" (funcdef | with_stmt | for_stmt)\nif_stmt:
   * "if" test suite ("else" "if" test suite)* ["else" suite]\nwhile_stmt:
   * "while" test suite ["else" suite]\nfor_stmt: "for" exprlist "in" testlist
   * suite ["else" suite]\ntry_stmt: ("try" suite ((except_clause suite)+
   * ["else" suite] ["finally" suite] | "finally" suite))\nwith_stmt: "with"
   * with_item ("," with_item)*  suite\nwith_item: test ["as"
   * expr]\nexcept_clause: "except" [test ["as" NAME]]\n!suite: "{" stmt*
   * "}"\n\n?test: or_test ("if" or_test "else" test)? | lambdef\n?test_nocond:
   * or_test | lambdef_nocond\nlambdef: "lambda" [varargslist] ":"
   * test\nlambdef_nocond: "lambda" [varargslist] ":" test_nocond\n?or_test:
   * and_test ("||" and_test)*\n?and_test: not_test ("&&" not_test)*\n?not_test:
   * "!" not_test -> not\n         | comparison\n?comparison: expr (_comp_op
   * expr)*\nstar_expr: "*" expr\n?expr: xor_expr ("|" xor_expr)*\n?xor_expr:
   * and_expr ("^" and_expr)*\n?and_expr: shift_expr ("&"
   * shift_expr)*\n?shift_expr: arith_expr (_shift_op arith_expr)*\n?arith_expr:
   * term (_add_op term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op
   * factor | power\n\n!_factor_op: "+"|"-"|"~"\n!_add_op: "+"|"-"\n!_shift_op:
   * "<<"|">>"\n!_mul_op: "*"|"@"|"/"|"%"|"//"\n!_comp_op:
   * "<"|">"|"=="|">="|"<="|"!="|"in"|"is"\n\n?power: await_expr ("**"
   * factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "await"\n\n?atom_expr:
   * atom_expr "(" [arguments] ")"      -> funccall\n          | atom_expr "["
   * subscriptlist "]"  -> getitem\n          | atom_expr "." NAME -> getattr\n
   * | atom\n\n?atom: "(" [yield_expr|testlist_comp] ")" -> tuple\n     | "["
   * [testlist_comp] "]"  -> list\n     | "{" [dictorsetmaker] "}" -> dict\n |
   * NAME -> var\n     | number | string+\n     | "(" test ")"\n     | "..." ->
   * ellipsis\n     | "None"    -> const_none\n     | "true"    -> const_true\n
   * | "false"   -> const_false\n\n?testlist_comp: (test|star_expr) [comp_for |
   * ("," (test|star_expr))+ [","] | ","]\nsubscriptlist: subscript (","
   * subscript)* [","]\nsubscript: test | [test] ":" [test] [sliceop]\nsliceop:
   * ":" [test]\nexprlist: (expr|star_expr) ("," (expr|star_expr))*
   * [","]\ntestlist: test ("," test)* [","]\ndictorsetmaker: ( ((test ":" test
   * | "**" expr) (comp_for | ("," (test ":" test | "**" expr))* [","])) |
   * ((test | star_expr) (comp_for | ("," (test | star_expr))* [","]))
   * )\n\nclassdef: "struct" NAME ["(" [arguments] ")"]
   * class_suite\n!class_suite: "{" (struct_funcdef | funcdef | decorated)*
   * "}"\n\narguments: argvalue ("," argvalue)*  ("," [ starargs | kwargs])?\n
   * | starargs\n        | kwargs\n         | test comp_for\n\nstarargs: "*"
   * test ("," "*" test)* ("," argvalue)* ["," kwargs]\nkwargs: "**"
   * test\n\n?argvalue: test ("=" test)?\n\n\n\ncomp_iter: comp_for | comp_if |
   * async_for\nasync_for: "async" "for" exprlist "in" or_test
   * [comp_iter]\ncomp_for: "for" exprlist "in" or_test [comp_iter]\ncomp_if:
   * "if" test_nocond [comp_iter]\n\nyield_expr: "yield" [yield_arg]\nyield_arg:
   * "from" test | testlist\n\n\nnumber: DEC_NUMBER | HEX_NUMBER | BIN_NUMBER |
   * OCT_NUMBER | FLOAT_NUMBER | IMAG_NUMBER\nstring: STRING |
   * LONG_STRING\n\nNAME: /(r#)?[a-zA-Z_]\\w*[inserted by RFC to avoid comment
   * closer]/\nCOMMENT: /\\/\\/[^\\n]*[inserted by RFC to avoid comment
   * closer]/\n_NEWLINE: ( /\\r?\\n[\\t ]*[inserted by RFC to avoid comment
   * closer]/ | COMMENT )+\n\n\nSTRING :
   * /[ubf]?r?("(?!"").*?(?<!\\\\)(\\\\\\\\)*?"|\'(?!\'\').*?(?<!\\\\)(\\\\\\\\)*?\')/i\nLONG_STRING:
   * /[ubf]?r?(""".*?(?<!\\\\)(\\\\\\\\)*?"""|\'\'\'.*?(?<!\\\\)(\\\\\\\\)*?\'\'\')/is\n\nDEC_NUMBER:
   * /0|[1-9]\\d*[inserted by RFC to avoid comment closer]/i\nHEX_NUMBER.2:
   * /0x[\\da-f]*[inserted by RFC to avoid comment closer]/i\nOCT_NUMBER.2:
   * /0o[0-7]*[inserted by RFC to avoid comment closer]/i\nBIN_NUMBER.2 :
   * /0b[0-1]*[inserted by RFC to avoid comment closer]/i\nFLOAT_NUMBER.2:
   * /((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2:
   * /\\d+j/i | FLOAT_NUMBER "j"i\n\n%ignore /[\\t \\f]+/\n%ignore _NEWLINE\n'
   *
   * parser = Lark(             # <<<<<<<<<<<<<<
   *     grammar, parser='lalr',
   *     propagate_positions=True,
   */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_Lark);
  if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 193, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

  /* "rfc.py":194
   *
   * parser = Lark(
   *     grammar, parser='lalr',             # <<<<<<<<<<<<<<
   *     propagate_positions=True,
   *     maybe_placeholders=True,
   */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_grammar);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);

  /* "rfc.py":193
   * grammar = 'start: (typedef | funcdef | decorated | (import_stmt ";") |
   * classdef | async_funcdef)*\n\n!decorator: "#" "[" dotted_name [ "("
   * [arguments] ")" ] "]"\ndecorators: decorator+\ndecorated: decorators
   * (classdef | funcdef | async_funcdef)\n\ntypedef: "type" NAME [(":"
   * typelist) | ("=" type)] ";"\ntype: (dotted_name ["[" typelist "]"]) |
   * "None"\ntypelist: type ("," type)*\n\nasync_funcdef: "async"
   * funcdef\nfuncdef: "fn" NAME "(" parameters? ")" ["->" type]
   * suite\nstruct_funcdef: "fn" NAME "(" "self" ["," parameters] ")" ["->"
   * type] suite\n\nparameters: paramvalue ("," paramvalue)* ["," [ starparams |
   * kwparams]]\n        | starparams\n          | kwparams\nstarparams: "*"
   * typedparam? ("," paramvalue)* ["," kwparams]\nkwparams: "**"
   * typedparam\n\n?paramvalue: typedparam ["=" test]\n?typedparam: NAME ":"
   * type\n\nvarargslist: (vfpdef ["=" test] ("," vfpdef ["=" test])* ["," [ "*"
   * [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef [","]]] | "**" vfpdef
   * [","]]]\n  | "*" [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef
   * [","]]]\n  | "**" vfpdef [","])\n\nvfpdef: NAME\n\n?stmt: simple_stmt |
   * compound_stmt\n?simple_stmt: small_stmt ";"\n?small_stmt: (expr_stmt |
   * del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: testlist_star_expr
   * (annassign | augassign (yield_expr|testlist)\n         | ("="
   * (yield_expr|testlist_star_expr))*)\nannassign: ":" type "="
   * test\n?testlist_star_expr: (test|star_expr) ("," (test|star_expr))*
   * [","]\n!augassign: ("+=" | "-=" | "*=" | "@=" | "/=" | "%=" | "&=" | "|=" |
   * "^=" | "<<=" | ">>=" | "**=")\ndel_stmt: "del" exprlist\n?flow_stmt:
   * break_stmt | continue_stmt | return_stmt | raise_stmt |
   * yield_stmt\nbreak_stmt: "break"\ncontinue_stmt: "continue"\nreturn_stmt:
   * "return" [testlist]\nyield_stmt: yield_expr\nraise_stmt: "raise" [test
   * ["from" test]]\nimport_stmt: import_name | import_from\nimport_name: "use"
   * dotted_as_names\nimport_from: "from" dotted_name "use" ("*" | "("
   * import_as_names ")" | import_as_names)\nimport_as_name: NAME ["as"
   * NAME]\ndotted_as_name: dotted_name ["as" NAME]\nimport_as_names:
   * import_as_name ("," import_as_name)* [","]\ndotted_as_names: dotted_as_name
   * ("," dotted_as_name)*\ndotted_name: NAME ("." NAME)*\nassert_stmt: "assert"
   * test ["," test]\n\ncompound_stmt: if_stmt | while_stmt | for_stmt |
   * try_stmt | with_stmt | typedef | funcdef | classdef | decorated |
   * async_stmt\nasync_stmt: "async" (funcdef | with_stmt | for_stmt)\nif_stmt:
   * "if" test suite ("else" "if" test suite)* ["else" suite]\nwhile_stmt:
   * "while" test suite ["else" suite]\nfor_stmt: "for" exprlist "in" testlist
   * suite ["else" suite]\ntry_stmt: ("try" suite ((except_clause suite)+
   * ["else" suite] ["finally" suite] | "finally" suite))\nwith_stmt: "with"
   * with_item ("," with_item)*  suite\nwith_item: test ["as"
   * expr]\nexcept_clause: "except" [test ["as" NAME]]\n!suite: "{" stmt*
   * "}"\n\n?test: or_test ("if" or_test "else" test)? | lambdef\n?test_nocond:
   * or_test | lambdef_nocond\nlambdef: "lambda" [varargslist] ":"
   * test\nlambdef_nocond: "lambda" [varargslist] ":" test_nocond\n?or_test:
   * and_test ("||" and_test)*\n?and_test: not_test ("&&" not_test)*\n?not_test:
   * "!" not_test -> not\n         | comparison\n?comparison: expr (_comp_op
   * expr)*\nstar_expr: "*" expr\n?expr: xor_expr ("|" xor_expr)*\n?xor_expr:
   * and_expr ("^" and_expr)*\n?and_expr: shift_expr ("&"
   * shift_expr)*\n?shift_expr: arith_expr (_shift_op arith_expr)*\n?arith_expr:
   * term (_add_op term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op
   * factor | power\n\n!_factor_op: "+"|"-"|"~"\n!_add_op: "+"|"-"\n!_shift_op:
   * "<<"|">>"\n!_mul_op: "*"|"@"|"/"|"%"|"//"\n!_comp_op:
   * "<"|">"|"=="|">="|"<="|"!="|"in"|"is"\n\n?power: await_expr ("**"
   * factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "await"\n\n?atom_expr:
   * atom_expr "(" [arguments] ")"      -> funccall\n          | atom_expr "["
   * subscriptlist "]"  -> getitem\n          | atom_expr "." NAME -> getattr\n
   * | atom\n\n?atom: "(" [yield_expr|testlist_comp] ")" -> tuple\n     | "["
   * [testlist_comp] "]"  -> list\n     | "{" [dictorsetmaker] "}" -> dict\n |
   * NAME -> var\n     | number | string+\n     | "(" test ")"\n     | "..." ->
   * ellipsis\n     | "None"    -> const_none\n     | "true"    -> const_true\n
   * | "false"   -> const_false\n\n?testlist_comp: (test|star_expr) [comp_for |
   * ("," (test|star_expr))+ [","] | ","]\nsubscriptlist: subscript (","
   * subscript)* [","]\nsubscript: test | [test] ":" [test] [sliceop]\nsliceop:
   * ":" [test]\nexprlist: (expr|star_expr) ("," (expr|star_expr))*
   * [","]\ntestlist: test ("," test)* [","]\ndictorsetmaker: ( ((test ":" test
   * | "**" expr) (comp_for | ("," (test ":" test | "**" expr))* [","])) |
   * ((test | star_expr) (comp_for | ("," (test | star_expr))* [","]))
   * )\n\nclassdef: "struct" NAME ["(" [arguments] ")"]
   * class_suite\n!class_suite: "{" (struct_funcdef | funcdef | decorated)*
   * "}"\n\narguments: argvalue ("," argvalue)*  ("," [ starargs | kwargs])?\n
   * | starargs\n        | kwargs\n         | test comp_for\n\nstarargs: "*"
   * test ("," "*" test)* ("," argvalue)* ["," kwargs]\nkwargs: "**"
   * test\n\n?argvalue: test ("=" test)?\n\n\n\ncomp_iter: comp_for | comp_if |
   * async_for\nasync_for: "async" "for" exprlist "in" or_test
   * [comp_iter]\ncomp_for: "for" exprlist "in" or_test [comp_iter]\ncomp_if:
   * "if" test_nocond [comp_iter]\n\nyield_expr: "yield" [yield_arg]\nyield_arg:
   * "from" test | testlist\n\n\nnumber: DEC_NUMBER | HEX_NUMBER | BIN_NUMBER |
   * OCT_NUMBER | FLOAT_NUMBER | IMAG_NUMBER\nstring: STRING |
   * LONG_STRING\n\nNAME: /(r#)?[a-zA-Z_]\\w*[inserted by RFC to avoid comment
   * closer]/\nCOMMENT: /\\/\\/[^\\n]*[inserted by RFC to avoid comment
   * closer]/\n_NEWLINE: ( /\\r?\\n[\\t ]*[inserted by RFC to avoid comment
   * closer]/ | COMMENT )+\n\n\nSTRING :
   * /[ubf]?r?("(?!"").*?(?<!\\\\)(\\\\\\\\)*?"|\'(?!\'\').*?(?<!\\\\)(\\\\\\\\)*?\')/i\nLONG_STRING:
   * /[ubf]?r?(""".*?(?<!\\\\)(\\\\\\\\)*?"""|\'\'\'.*?(?<!\\\\)(\\\\\\\\)*?\'\'\')/is\n\nDEC_NUMBER:
   * /0|[1-9]\\d*[inserted by RFC to avoid comment closer]/i\nHEX_NUMBER.2:
   * /0x[\\da-f]*[inserted by RFC to avoid comment closer]/i\nOCT_NUMBER.2:
   * /0o[0-7]*[inserted by RFC to avoid comment closer]/i\nBIN_NUMBER.2 :
   * /0b[0-1]*[inserted by RFC to avoid comment closer]/i\nFLOAT_NUMBER.2:
   * /((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2:
   * /\\d+j/i | FLOAT_NUMBER "j"i\n\n%ignore /[\\t \\f]+/\n%ignore _NEWLINE\n'
   *
   * parser = Lark(             # <<<<<<<<<<<<<<
   *     grammar, parser='lalr',
   *     propagate_positions=True,
   */
  __pyx_t_7 = PyTuple_New(1);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 193, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2);
  __pyx_t_2 = 0;

  /* "rfc.py":194
   *
   * parser = Lark(
   *     grammar, parser='lalr',             # <<<<<<<<<<<<<<
   *     propagate_positions=True,
   *     maybe_placeholders=True,
   */
  __pyx_t_2 = PyDict_New();
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_parser, __pyx_n_u_lalr) < 0)
    __PYX_ERR(0, 194, __pyx_L1_error)

  /* "rfc.py":195
   * parser = Lark(
   *     grammar, parser='lalr',
   *     propagate_positions=True,             # <<<<<<<<<<<<<<
   *     maybe_placeholders=True,
   *     transformer=Parser()
   */
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_propagate_positions, Py_True) < 0)
    __PYX_ERR(0, 194, __pyx_L1_error)

  /* "rfc.py":196
   *     grammar, parser='lalr',
   *     propagate_positions=True,
   *     maybe_placeholders=True,             # <<<<<<<<<<<<<<
   *     transformer=Parser()
   * )
   */
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_maybe_placeholders, Py_True) < 0)
    __PYX_ERR(0, 194, __pyx_L1_error)

  /* "rfc.py":197
   *     propagate_positions=True,
   *     maybe_placeholders=True,
   *     transformer=Parser()             # <<<<<<<<<<<<<<
   * )
   *
   */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_Parser);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_4 = NULL;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_4)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_4);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
  } else {
    __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_5);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 197, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_transformer, __pyx_t_6) < 0)
    __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":193
   * grammar = 'start: (typedef | funcdef | decorated | (import_stmt ";") |
   * classdef | async_funcdef)*\n\n!decorator: "#" "[" dotted_name [ "("
   * [arguments] ")" ] "]"\ndecorators: decorator+\ndecorated: decorators
   * (classdef | funcdef | async_funcdef)\n\ntypedef: "type" NAME [(":"
   * typelist) | ("=" type)] ";"\ntype: (dotted_name ["[" typelist "]"]) |
   * "None"\ntypelist: type ("," type)*\n\nasync_funcdef: "async"
   * funcdef\nfuncdef: "fn" NAME "(" parameters? ")" ["->" type]
   * suite\nstruct_funcdef: "fn" NAME "(" "self" ["," parameters] ")" ["->"
   * type] suite\n\nparameters: paramvalue ("," paramvalue)* ["," [ starparams |
   * kwparams]]\n        | starparams\n          | kwparams\nstarparams: "*"
   * typedparam? ("," paramvalue)* ["," kwparams]\nkwparams: "**"
   * typedparam\n\n?paramvalue: typedparam ["=" test]\n?typedparam: NAME ":"
   * type\n\nvarargslist: (vfpdef ["=" test] ("," vfpdef ["=" test])* ["," [ "*"
   * [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef [","]]] | "**" vfpdef
   * [","]]]\n  | "*" [vfpdef] ("," vfpdef ["=" test])* ["," ["**" vfpdef
   * [","]]]\n  | "**" vfpdef [","])\n\nvfpdef: NAME\n\n?stmt: simple_stmt |
   * compound_stmt\n?simple_stmt: small_stmt ";"\n?small_stmt: (expr_stmt |
   * del_stmt | flow_stmt | assert_stmt)\n?expr_stmt: testlist_star_expr
   * (annassign | augassign (yield_expr|testlist)\n         | ("="
   * (yield_expr|testlist_star_expr))*)\nannassign: ":" type "="
   * test\n?testlist_star_expr: (test|star_expr) ("," (test|star_expr))*
   * [","]\n!augassign: ("+=" | "-=" | "*=" | "@=" | "/=" | "%=" | "&=" | "|=" |
   * "^=" | "<<=" | ">>=" | "**=")\ndel_stmt: "del" exprlist\n?flow_stmt:
   * break_stmt | continue_stmt | return_stmt | raise_stmt |
   * yield_stmt\nbreak_stmt: "break"\ncontinue_stmt: "continue"\nreturn_stmt:
   * "return" [testlist]\nyield_stmt: yield_expr\nraise_stmt: "raise" [test
   * ["from" test]]\nimport_stmt: import_name | import_from\nimport_name: "use"
   * dotted_as_names\nimport_from: "from" dotted_name "use" ("*" | "("
   * import_as_names ")" | import_as_names)\nimport_as_name: NAME ["as"
   * NAME]\ndotted_as_name: dotted_name ["as" NAME]\nimport_as_names:
   * import_as_name ("," import_as_name)* [","]\ndotted_as_names: dotted_as_name
   * ("," dotted_as_name)*\ndotted_name: NAME ("." NAME)*\nassert_stmt: "assert"
   * test ["," test]\n\ncompound_stmt: if_stmt | while_stmt | for_stmt |
   * try_stmt | with_stmt | typedef | funcdef | classdef | decorated |
   * async_stmt\nasync_stmt: "async" (funcdef | with_stmt | for_stmt)\nif_stmt:
   * "if" test suite ("else" "if" test suite)* ["else" suite]\nwhile_stmt:
   * "while" test suite ["else" suite]\nfor_stmt: "for" exprlist "in" testlist
   * suite ["else" suite]\ntry_stmt: ("try" suite ((except_clause suite)+
   * ["else" suite] ["finally" suite] | "finally" suite))\nwith_stmt: "with"
   * with_item ("," with_item)*  suite\nwith_item: test ["as"
   * expr]\nexcept_clause: "except" [test ["as" NAME]]\n!suite: "{" stmt*
   * "}"\n\n?test: or_test ("if" or_test "else" test)? | lambdef\n?test_nocond:
   * or_test | lambdef_nocond\nlambdef: "lambda" [varargslist] ":"
   * test\nlambdef_nocond: "lambda" [varargslist] ":" test_nocond\n?or_test:
   * and_test ("||" and_test)*\n?and_test: not_test ("&&" not_test)*\n?not_test:
   * "!" not_test -> not\n         | comparison\n?comparison: expr (_comp_op
   * expr)*\nstar_expr: "*" expr\n?expr: xor_expr ("|" xor_expr)*\n?xor_expr:
   * and_expr ("^" and_expr)*\n?and_expr: shift_expr ("&"
   * shift_expr)*\n?shift_expr: arith_expr (_shift_op arith_expr)*\n?arith_expr:
   * term (_add_op term)*\n?term: factor (_mul_op factor)*\n?factor: _factor_op
   * factor | power\n\n!_factor_op: "+"|"-"|"~"\n!_add_op: "+"|"-"\n!_shift_op:
   * "<<"|">>"\n!_mul_op: "*"|"@"|"/"|"%"|"//"\n!_comp_op:
   * "<"|">"|"=="|">="|"<="|"!="|"in"|"is"\n\n?power: await_expr ("**"
   * factor)?\n?await_expr: AWAIT? atom_expr\nAWAIT: "await"\n\n?atom_expr:
   * atom_expr "(" [arguments] ")"      -> funccall\n          | atom_expr "["
   * subscriptlist "]"  -> getitem\n          | atom_expr "." NAME -> getattr\n
   * | atom\n\n?atom: "(" [yield_expr|testlist_comp] ")" -> tuple\n     | "["
   * [testlist_comp] "]"  -> list\n     | "{" [dictorsetmaker] "}" -> dict\n |
   * NAME -> var\n     | number | string+\n     | "(" test ")"\n     | "..." ->
   * ellipsis\n     | "None"    -> const_none\n     | "true"    -> const_true\n
   * | "false"   -> const_false\n\n?testlist_comp: (test|star_expr) [comp_for |
   * ("," (test|star_expr))+ [","] | ","]\nsubscriptlist: subscript (","
   * subscript)* [","]\nsubscript: test | [test] ":" [test] [sliceop]\nsliceop:
   * ":" [test]\nexprlist: (expr|star_expr) ("," (expr|star_expr))*
   * [","]\ntestlist: test ("," test)* [","]\ndictorsetmaker: ( ((test ":" test
   * | "**" expr) (comp_for | ("," (test ":" test | "**" expr))* [","])) |
   * ((test | star_expr) (comp_for | ("," (test | star_expr))* [","]))
   * )\n\nclassdef: "struct" NAME ["(" [arguments] ")"]
   * class_suite\n!class_suite: "{" (struct_funcdef | funcdef | decorated)*
   * "}"\n\narguments: argvalue ("," argvalue)*  ("," [ starargs | kwargs])?\n
   * | starargs\n        | kwargs\n         | test comp_for\n\nstarargs: "*"
   * test ("," "*" test)* ("," argvalue)* ["," kwargs]\nkwargs: "**"
   * test\n\n?argvalue: test ("=" test)?\n\n\n\ncomp_iter: comp_for | comp_if |
   * async_for\nasync_for: "async" "for" exprlist "in" or_test
   * [comp_iter]\ncomp_for: "for" exprlist "in" or_test [comp_iter]\ncomp_if:
   * "if" test_nocond [comp_iter]\n\nyield_expr: "yield" [yield_arg]\nyield_arg:
   * "from" test | testlist\n\n\nnumber: DEC_NUMBER | HEX_NUMBER | BIN_NUMBER |
   * OCT_NUMBER | FLOAT_NUMBER | IMAG_NUMBER\nstring: STRING |
   * LONG_STRING\n\nNAME: /(r#)?[a-zA-Z_]\\w*[inserted by RFC to avoid comment
   * closer]/\nCOMMENT: /\\/\\/[^\\n]*[inserted by RFC to avoid comment
   * closer]/\n_NEWLINE: ( /\\r?\\n[\\t ]*[inserted by RFC to avoid comment
   * closer]/ | COMMENT )+\n\n\nSTRING :
   * /[ubf]?r?("(?!"").*?(?<!\\\\)(\\\\\\\\)*?"|\'(?!\'\').*?(?<!\\\\)(\\\\\\\\)*?\')/i\nLONG_STRING:
   * /[ubf]?r?(""".*?(?<!\\\\)(\\\\\\\\)*?"""|\'\'\'.*?(?<!\\\\)(\\\\\\\\)*?\'\'\')/is\n\nDEC_NUMBER:
   * /0|[1-9]\\d*[inserted by RFC to avoid comment closer]/i\nHEX_NUMBER.2:
   * /0x[\\da-f]*[inserted by RFC to avoid comment closer]/i\nOCT_NUMBER.2:
   * /0o[0-7]*[inserted by RFC to avoid comment closer]/i\nBIN_NUMBER.2 :
   * /0b[0-1]*[inserted by RFC to avoid comment closer]/i\nFLOAT_NUMBER.2:
   * /((\\d+\\.\\d*|\\.\\d+)(e[-+]?\\d+)?|\\d+(e[-+]?\\d+))/i\nIMAG_NUMBER.2:
   * /\\d+j/i | FLOAT_NUMBER "j"i\n\n%ignore /[\\t \\f]+/\n%ignore _NEWLINE\n'
   *
   * parser = Lark(             # <<<<<<<<<<<<<<
   *     grammar, parser='lalr',
   *     propagate_positions=True,
   */
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_7, __pyx_t_2);
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 193, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_7);
  __pyx_t_7 = 0;
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_parser, __pyx_t_6) < 0)
    __PYX_ERR(0, 193, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":201
   *
   *
   * def compile(code):             # <<<<<<<<<<<<<<
   *     toks = parser.lex(code)
   *     parsed = parser.parse(code)
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(&__pyx_mdef_3rfc_3compile, 0,
                                     __pyx_n_s_compile, NULL, __pyx_n_s_rfc,
                                     __pyx_d, ((PyObject *)__pyx_codeobj__73));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_compile, __pyx_t_6) < 0)
    __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":207
   *
   *
   * def compile_file(filename):             # <<<<<<<<<<<<<<
   *     with open(filename) as file:
   *         code = file.read()
   */
  __pyx_t_6 = __Pyx_CyFunction_NewEx(
      &__pyx_mdef_3rfc_5compile_file, 0, __pyx_n_s_compile_file, NULL,
      __pyx_n_s_rfc, __pyx_d, ((PyObject *)__pyx_codeobj__75));
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_compile_file, __pyx_t_6) < 0)
    __PYX_ERR(0, 207, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;

  /* "rfc.py":214
   *     return (filename[:-3] + '.py', FormatCode(output)[0])
   *
   * if __name__ == "__main__":             # <<<<<<<<<<<<<<
   *     arg_parser = ArgumentParser(description='The bootstrap compiler for
   * Raft.') arg_parser.add_argument('input', help='Input file or directory')
   */
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_name_2);
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_8 = (__Pyx_PyUnicode_Equals(__pyx_t_6, __pyx_n_u_main, Py_EQ));
  if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;
  if (__pyx_t_8) {
    /* "rfc.py":215
     *
     * if __name__ == "__main__":
     *     arg_parser = ArgumentParser(description='The bootstrap compiler for
     * Raft.')             # <<<<<<<<<<<<<< arg_parser.add_argument('input',
     * help='Input file or directory') arg_parser.add_argument('-o',
     * metavar='output', help='Output file')
     */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_ArgumentParser);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_2 = PyDict_New();
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_description,
                       __pyx_kp_u_The_bootstrap_compiler_for_Raft) < 0)
      __PYX_ERR(0, 215, __pyx_L1_error)
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_empty_tuple, __pyx_t_2);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_arg_parser, __pyx_t_7) < 0)
      __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;

    /* "rfc.py":216
     * if __name__ == "__main__":
     *     arg_parser = ArgumentParser(description='The bootstrap compiler for
     * Raft.') arg_parser.add_argument('input', help='Input file or directory')
     * # <<<<<<<<<<<<<< arg_parser.add_argument('-o', metavar='output',
     * help='Output file') args = arg_parser.parse_args()
     */
    __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_arg_parser);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_add_argument);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    __pyx_t_7 = PyDict_New();
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (PyDict_SetItem(__pyx_t_7, __pyx_n_s_help,
                       __pyx_kp_u_Input_file_or_directory) < 0)
      __PYX_ERR(0, 216, __pyx_L1_error)
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__76, __pyx_t_7);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;

    /* "rfc.py":217
     *     arg_parser = ArgumentParser(description='The bootstrap compiler for
     * Raft.') arg_parser.add_argument('input', help='Input file or directory')
     *     arg_parser.add_argument('-o', metavar='output', help='Output file')
     * # <<<<<<<<<<<<<< args = arg_parser.parse_args()
     *
     */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_arg_parser);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_add_argument);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_6 = PyDict_New();
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    if (PyDict_SetItem(__pyx_t_6, __pyx_n_s_metavar, __pyx_n_u_output) < 0)
      __PYX_ERR(0, 217, __pyx_L1_error)
    if (PyDict_SetItem(__pyx_t_6, __pyx_n_s_help, __pyx_kp_u_Output_file) < 0)
      __PYX_ERR(0, 217, __pyx_L1_error)
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_tuple__77, __pyx_t_6);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;

    /* "rfc.py":218
     *     arg_parser.add_argument('input', help='Input file or directory')
     *     arg_parser.add_argument('-o', metavar='output', help='Output file')
     *     args = arg_parser.parse_args()             # <<<<<<<<<<<<<<
     *
     *     if not args.o: args.o = 'a.out'
     */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_arg_parser);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_parse_args);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_6 = NULL;
    if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_7);
      if (likely(__pyx_t_6)) {
        PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_7, function);
      }
    }
    if (__pyx_t_6) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_6);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 218, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
    } else {
      __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_7);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 218, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_args, __pyx_t_2) < 0)
      __PYX_ERR(0, 218, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;

    /* "rfc.py":220
     *     args = arg_parser.parse_args()
     *
     *     if not args.o: args.o = 'a.out'             # <<<<<<<<<<<<<<
     *     pyfiles = []
     *
     */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_o_2);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_7);
    if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    __pyx_t_9 = ((!__pyx_t_8) != 0);
    if (__pyx_t_9) {
      __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 220, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      if (__Pyx_PyObject_SetAttrStr(__pyx_t_7, __pyx_n_s_o_2,
                                    __pyx_kp_u_a_out) < 0)
        __PYX_ERR(0, 220, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
    }

    /* "rfc.py":221
     *
     *     if not args.o: args.o = 'a.out'
     *     pyfiles = []             # <<<<<<<<<<<<<<
     *
     *     if path.isdir(args.input):
     */
    __pyx_t_7 = PyList_New(0);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 221, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyfiles, __pyx_t_7) < 0)
      __PYX_ERR(0, 221, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;

    /* "rfc.py":223
     *     pyfiles = []
     *
     *     if path.isdir(args.input):             # <<<<<<<<<<<<<<
     *         for file in glob(args.input + '/[inserted by RFC to avoid comment
     * start]**[inserted by RFC to avoid comment closer]/[inserted by RFC to
     * avoid comment start]*.rf', recursive=True): pyfiles +=
     * [compile_file(file)]
     */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_path);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_isdir);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
    if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_input);
    if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_2)) {
        PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_1);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 223, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else {
#if RFC_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_1};
        __pyx_t_7 =
            __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp + 1 - 1, 1 + 1);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
      } else
#endif
#if RFC_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_1};
        __pyx_t_7 =
            __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp + 1 - 1, 1 + 1);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
      } else
#endif
      {
        __pyx_t_5 = PyTuple_New(1 + 1);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2);
        __pyx_t_2 = NULL;
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_5, 0 + 1, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_5, NULL);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 223, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_7);
    if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;
    if (__pyx_t_9) {
      /* "rfc.py":224
       *
       *     if path.isdir(args.input):
       *         for file in glob(args.input + '/[inserted by RFC to avoid
       * comment start]**[inserted by RFC to avoid comment closer]/[inserted by
       * RFC to avoid comment start]*.rf', recursive=True):             #
       * <<<<<<<<<<<<<< pyfiles += [compile_file(file)] nuitka_main = args.input
       * + '/__main__.py'
       */
      __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_glob);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_input);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = PyNumber_Add(__pyx_t_5, __pyx_kp_u_rf_3);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyTuple_New(1);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = PyDict_New();
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      if (PyDict_SetItem(__pyx_t_6, __pyx_n_s_recursive, Py_True) < 0)
        __PYX_ERR(0, 224, __pyx_L1_error)
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_5, __pyx_t_6);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      if (likely(PyList_CheckExact(__pyx_t_1)) ||
          PyTuple_CheckExact(__pyx_t_1)) {
        __pyx_t_6 = __pyx_t_1;
        __Pyx_INCREF(__pyx_t_6);
        __pyx_t_10 = 0;
        __pyx_t_11 = NULL;
      } else {
        __pyx_t_10 = -1;
        __pyx_t_6 = PyObject_GetIter(__pyx_t_1);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_11 = Py_TYPE(__pyx_t_6)->tp_iternext;
        if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 224, __pyx_L1_error)
      }
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      for (;;) {
        if (likely(!__pyx_t_11)) {
          if (likely(PyList_CheckExact(__pyx_t_6))) {
            if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_6)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
            __pyx_t_1 = PyList_GET_ITEM(__pyx_t_6, __pyx_t_10);
            __Pyx_INCREF(__pyx_t_1);
            __pyx_t_10++;
            if (unlikely(0 < 0)) __PYX_ERR(0, 224, __pyx_L1_error)
#else
            __pyx_t_1 = PySequence_ITEM(__pyx_t_6, __pyx_t_10);
            __pyx_t_10++;
            if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 224, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
#endif
          } else {
            if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_6)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
            __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_6, __pyx_t_10);
            __Pyx_INCREF(__pyx_t_1);
            __pyx_t_10++;
            if (unlikely(0 < 0)) __PYX_ERR(0, 224, __pyx_L1_error)
#else
            __pyx_t_1 = PySequence_ITEM(__pyx_t_6, __pyx_t_10);
            __pyx_t_10++;
            if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 224, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
#endif
          }
        } else {
          __pyx_t_1 = __pyx_t_11(__pyx_t_6);
          if (unlikely(!__pyx_t_1)) {
            PyObject *exc_type = PyErr_Occurred();
            if (exc_type) {
              if (likely(exc_type == PyExc_StopIteration ||
                         PyErr_GivenExceptionMatches(exc_type,
                                                     PyExc_StopIteration)))
                PyErr_Clear();
              else
                __PYX_ERR(0, 224, __pyx_L1_error)
            }
            break;
          }
          __Pyx_GOTREF(__pyx_t_1);
        }
        if (PyDict_SetItem(__pyx_d, __pyx_n_s_file, __pyx_t_1) < 0)
          __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;

        /* "rfc.py":225
         *     if path.isdir(args.input):
         *         for file in glob(args.input + '/[inserted by RFC to avoid
         * comment start]**[inserted by RFC to avoid comment closer]/[inserted
         * by RFC to avoid comment start]*.rf', recursive=True): pyfiles +=
         * [compile_file(file)]             # <<<<<<<<<<<<<< nuitka_main =
         * args.input + '/__main__.py' else:
         */
        __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_pyfiles);
        if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_compile_file);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_file);
        if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_4 = NULL;
        if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
          __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_7);
          if (likely(__pyx_t_4)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
            __Pyx_INCREF(__pyx_t_4);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_7, function);
          }
        }
        if (!__pyx_t_4) {
          __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_2);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __Pyx_GOTREF(__pyx_t_5);
        } else {
#if RFC_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
            __pyx_t_5 =
                __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_4);
            __pyx_t_4 = 0;
            __Pyx_GOTREF(__pyx_t_5);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          } else
#endif
#if RFC_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
            __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_7,
                                                   __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_4);
            __pyx_t_4 = 0;
            __Pyx_GOTREF(__pyx_t_5);
            __Pyx_DECREF(__pyx_t_2);
            __pyx_t_2 = 0;
          } else
#endif
          {
            __pyx_t_3 = PyTuple_New(1 + 1);
            if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 225, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_GIVEREF(__pyx_t_4);
            PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4);
            __pyx_t_4 = NULL;
            __Pyx_GIVEREF(__pyx_t_2);
            PyTuple_SET_ITEM(__pyx_t_3, 0 + 1, __pyx_t_2);
            __pyx_t_2 = 0;
            __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_3, NULL);
            if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_5);
            __Pyx_DECREF(__pyx_t_3);
            __pyx_t_3 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __pyx_t_7 = PyList_New(1);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GIVEREF(__pyx_t_5);
        PyList_SET_ITEM(__pyx_t_7, 0, __pyx_t_5);
        __pyx_t_5 = 0;
        __pyx_t_5 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_7);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyfiles, __pyx_t_5) < 0)
          __PYX_ERR(0, 225, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;

        /* "rfc.py":224
         *
         *     if path.isdir(args.input):
         *         for file in glob(args.input + '/[inserted by RFC to avoid
         * comment start]**[inserted by RFC to avoid comment closer]/[inserted
         * by RFC to avoid comment start]*.rf', recursive=True):             #
         * <<<<<<<<<<<<<< pyfiles += [compile_file(file)] nuitka_main =
         * args.input + '/__main__.py'
         */
      }
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;

      /* "rfc.py":226
       *         for file in glob(args.input + '/[inserted by RFC to avoid
       * comment start]**[inserted by RFC to avoid comment closer]/[inserted by
       * RFC to avoid comment start]*.rf', recursive=True): pyfiles +=
       * [compile_file(file)] nuitka_main = args.input + '/__main__.py' #
       * <<<<<<<<<<<<<< else: nuitka_main = args.input[:-3] + '.py'
       */
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 226, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_input);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 226, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = PyNumber_Add(__pyx_t_5, __pyx_kp_u_main___py);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 226, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      if (PyDict_SetItem(__pyx_d, __pyx_n_s_nuitka_main, __pyx_t_6) < 0)
        __PYX_ERR(0, 226, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;

      /* "rfc.py":223
       *     pyfiles = []
       *
       *     if path.isdir(args.input):             # <<<<<<<<<<<<<<
       *         for file in glob(args.input + '/[inserted by RFC to avoid
       * comment start]**[inserted by RFC to avoid comment closer]/[inserted by
       * RFC to avoid comment start]*.rf', recursive=True): pyfiles +=
       * [compile_file(file)]
       */
      goto __pyx_L4;
    }

    /* "rfc.py":228
     *         nuitka_main = args.input + '/__main__.py'
     *     else:
     *         nuitka_main = args.input[:-3] + '.py'             #
     * <<<<<<<<<<<<<< pyfiles += [compile_file(args.input)]
     *
     */
    /*else*/ {
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 228, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_input);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 228, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = __Pyx_PyObject_GetSlice(__pyx_t_5, 0, -3L, NULL, NULL,
                                          &__pyx_slice__78, 0, 1, 1);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 228, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyNumber_Add(__pyx_t_6, __pyx_kp_u_py_2);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 228, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      if (PyDict_SetItem(__pyx_d, __pyx_n_s_nuitka_main, __pyx_t_5) < 0)
        __PYX_ERR(0, 228, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;

      /* "rfc.py":229
       *     else:
       *         nuitka_main = args.input[:-3] + '.py'
       *         pyfiles += [compile_file(args.input)]             #
       * <<<<<<<<<<<<<<
       *
       *     prologue = 'from typing import *\n'
       */
      __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_pyfiles);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_compile_file);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
      if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_input);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_t_1 = NULL;
      if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
        __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_7);
        if (likely(__pyx_t_1)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
          __Pyx_INCREF(__pyx_t_1);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_7, function);
        }
      }
      if (!__pyx_t_1) {
        __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_3);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 229, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_6);
      } else {
#if RFC_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_7)) {
          PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_3};
          __pyx_t_6 =
              __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 229, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_1);
          __pyx_t_1 = 0;
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_3);
          __pyx_t_3 = 0;
        } else
#endif
#if RFC_FAST_PYCCALL
            if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
          PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_3};
          __pyx_t_6 =
              __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 229, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_1);
          __pyx_t_1 = 0;
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_3);
          __pyx_t_3 = 0;
        } else
#endif
        {
          __pyx_t_2 = PyTuple_New(1 + 1);
          if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 229, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_GIVEREF(__pyx_t_1);
          PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
          __pyx_t_1 = NULL;
          __Pyx_GIVEREF(__pyx_t_3);
          PyTuple_SET_ITEM(__pyx_t_2, 0 + 1, __pyx_t_3);
          __pyx_t_3 = 0;
          __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_2, NULL);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 229, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
        }
      }
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = PyList_New(1);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_6);
      PyList_SET_ITEM(__pyx_t_7, 0, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = PyNumber_InPlaceAdd(__pyx_t_5, __pyx_t_7);
      if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      if (PyDict_SetItem(__pyx_d, __pyx_n_s_pyfiles, __pyx_t_6) < 0)
        __PYX_ERR(0, 229, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
    }
  __pyx_L4:;

    /* "rfc.py":231
     *         pyfiles += [compile_file(args.input)]
     *
     *     prologue = 'from typing import *\n'             # <<<<<<<<<<<<<<
     *     epilogue = '\nif __name__ == "__main__": main()'
     *
     */
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_prologue,
                       __pyx_kp_u_from_typing_import) < 0)
      __PYX_ERR(0, 231, __pyx_L1_error)

    /* "rfc.py":232
     *
     *     prologue = 'from typing import *\n'
     *     epilogue = '\nif __name__ == "__main__": main()'             #
     * <<<<<<<<<<<<<<
     *
     *     for f in pyfiles:
     */
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_epilogue,
                       __pyx_kp_u_if___name_____main___main) < 0)
      __PYX_ERR(0, 232, __pyx_L1_error)

    /* "rfc.py":234
     *     epilogue = '\nif __name__ == "__main__": main()'
     *
     *     for f in pyfiles:             # <<<<<<<<<<<<<<
     *         with open(f[0], 'w') as file: file.write(prologue + 'def
     * test(func): func(); return func\n' + f[1])
     *
     */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_pyfiles);
    if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 234, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    if (likely(PyList_CheckExact(__pyx_t_6)) || PyTuple_CheckExact(__pyx_t_6)) {
      __pyx_t_7 = __pyx_t_6;
      __Pyx_INCREF(__pyx_t_7);
      __pyx_t_10 = 0;
      __pyx_t_11 = NULL;
    } else {
      __pyx_t_10 = -1;
      __pyx_t_7 = PyObject_GetIter(__pyx_t_6);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 234, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_11 = Py_TYPE(__pyx_t_7)->tp_iternext;
      if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 234, __pyx_L1_error)
    }
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    for (;;) {
      if (likely(!__pyx_t_11)) {
        if (likely(PyList_CheckExact(__pyx_t_7))) {
          if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_7)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_6 = PyList_GET_ITEM(__pyx_t_7, __pyx_t_10);
          __Pyx_INCREF(__pyx_t_6);
          __pyx_t_10++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 234, __pyx_L1_error)
#else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_7, __pyx_t_10);
          __pyx_t_10++;
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 234, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
#endif
        } else {
          if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_7)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
          __pyx_t_6 = PyTuple_GET_ITEM(__pyx_t_7, __pyx_t_10);
          __Pyx_INCREF(__pyx_t_6);
          __pyx_t_10++;
          if (unlikely(0 < 0)) __PYX_ERR(0, 234, __pyx_L1_error)
#else
          __pyx_t_6 = PySequence_ITEM(__pyx_t_7, __pyx_t_10);
          __pyx_t_10++;
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 234, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
#endif
        }
      } else {
        __pyx_t_6 = __pyx_t_11(__pyx_t_7);
        if (unlikely(!__pyx_t_6)) {
          PyObject *exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(
                    exc_type == PyExc_StopIteration ||
                    PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
              PyErr_Clear();
            else
              __PYX_ERR(0, 234, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_6);
      }
      if (PyDict_SetItem(__pyx_d, __pyx_n_s_f, __pyx_t_6) < 0)
        __PYX_ERR(0, 234, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;

      /* "rfc.py":235
       *
       *     for f in pyfiles:
       *         with open(f[0], 'w') as file: file.write(prologue + 'def
       * test(func): func(); return func\n' + f[1])             # <<<<<<<<<<<<<<
       *
       *     if run(['python3', '-B', nuitka_main]).returncode == 0:
       */
      /*with:*/ {
        __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_f);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_5 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1,
                                     __Pyx_PyInt_From_long, 0, 0, 1);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_6 = PyTuple_New(2);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_5);
        PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_5);
        __Pyx_INCREF(__pyx_n_u_w);
        __Pyx_GIVEREF(__pyx_n_u_w);
        PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_n_u_w);
        __pyx_t_5 = 0;
        __pyx_t_5 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_6, NULL);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_12 = __Pyx_PyObject_LookupSpecial(__pyx_t_5, __pyx_n_s_exit);
        if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __pyx_t_2 = __Pyx_PyObject_LookupSpecial(__pyx_t_5, __pyx_n_s_enter);
        if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 235, __pyx_L9_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_3 = NULL;
        if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
          __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
          if (likely(__pyx_t_3)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
            __Pyx_INCREF(__pyx_t_3);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_2, function);
          }
        }
        if (__pyx_t_3) {
          __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 235, __pyx_L9_error)
          __Pyx_DECREF(__pyx_t_3);
          __pyx_t_3 = 0;
        } else {
          __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_2);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 235, __pyx_L9_error)
        }
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_2 = __pyx_t_6;
        __pyx_t_6 = 0;
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        /*try:*/ {
            {__Pyx_PyThreadState_declare __Pyx_PyThreadState_assign
                 __Pyx_ExceptionSave(&__pyx_t_13, &__pyx_t_14, &__pyx_t_15);
        __Pyx_XGOTREF(__pyx_t_13);
        __Pyx_XGOTREF(__pyx_t_14);
        __Pyx_XGOTREF(__pyx_t_15);
        /*try:*/ {
          if (PyDict_SetItem(__pyx_d, __pyx_n_s_file, __pyx_t_2) < 0)
            __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_file);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_write);
          if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_prologue);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_3 = PyNumber_Add(__pyx_t_5,
                                   __pyx_kp_u_def_test_func_func_return_func);
          if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_f);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_5, 1, long, 1,
                                       __Pyx_PyInt_From_long, 0, 0, 1);
          if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          __pyx_t_5 = PyNumber_Add(__pyx_t_3, __pyx_t_1);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L15_error)
          __Pyx_GOTREF(__pyx_t_5);
          __Pyx_DECREF(__pyx_t_3);
          __pyx_t_3 = 0;
          __Pyx_DECREF(__pyx_t_1);
          __pyx_t_1 = 0;
          __pyx_t_1 = NULL;
          if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
            __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_6);
            if (likely(__pyx_t_1)) {
              PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_6);
              __Pyx_INCREF(__pyx_t_1);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_6, function);
            }
          }
          if (!__pyx_t_1) {
            __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_5);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 235, __pyx_L15_error)
            __Pyx_DECREF(__pyx_t_5);
            __pyx_t_5 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else {
#if RFC_FAST_PYCALL
            if (PyFunction_Check(__pyx_t_6)) {
              PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_5};
              __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_6,
                                                    __pyx_temp + 1 - 1, 1 + 1);
              if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 235, __pyx_L15_error)
              __Pyx_XDECREF(__pyx_t_1);
              __pyx_t_1 = 0;
              __Pyx_GOTREF(__pyx_t_2);
              __Pyx_DECREF(__pyx_t_5);
              __pyx_t_5 = 0;
            } else
#endif
#if RFC_FAST_PYCCALL
                if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
              PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_5};
              __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_6,
                                                     __pyx_temp + 1 - 1, 1 + 1);
              if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 235, __pyx_L15_error)
              __Pyx_XDECREF(__pyx_t_1);
              __pyx_t_1 = 0;
              __Pyx_GOTREF(__pyx_t_2);
              __Pyx_DECREF(__pyx_t_5);
              __pyx_t_5 = 0;
            } else
#endif
            {
              __pyx_t_3 = PyTuple_New(1 + 1);
              if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 235, __pyx_L15_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_GIVEREF(__pyx_t_1);
              PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1);
              __pyx_t_1 = NULL;
              __Pyx_GIVEREF(__pyx_t_5);
              PyTuple_SET_ITEM(__pyx_t_3, 0 + 1, __pyx_t_5);
              __pyx_t_5 = 0;
              __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_3, NULL);
              if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 235, __pyx_L15_error)
              __Pyx_GOTREF(__pyx_t_2);
              __Pyx_DECREF(__pyx_t_3);
              __pyx_t_3 = 0;
            }
          }
          __Pyx_DECREF(__pyx_t_6);
          __pyx_t_6 = 0;
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
        }
        __Pyx_XDECREF(__pyx_t_13);
        __pyx_t_13 = 0;
        __Pyx_XDECREF(__pyx_t_14);
        __pyx_t_14 = 0;
        __Pyx_XDECREF(__pyx_t_15);
        __pyx_t_15 = 0;
        goto __pyx_L22_try_end;
      __pyx_L15_error:;
        __Pyx_PyThreadState_assign __Pyx_XDECREF(__pyx_t_4);
        __pyx_t_4 = 0;
        __Pyx_XDECREF(__pyx_t_1);
        __pyx_t_1 = 0;
        __Pyx_XDECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        __Pyx_XDECREF(__pyx_t_3);
        __pyx_t_3 = 0;
        __Pyx_XDECREF(__pyx_t_6);
        __pyx_t_6 = 0;
        __Pyx_XDECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        /*except:*/ {
          __Pyx_AddTraceback("rfc", __pyx_clineno, __pyx_lineno,
                             __pyx_filename);
          if (__Pyx_GetException(&__pyx_t_2, &__pyx_t_6, &__pyx_t_3) < 0)
            __PYX_ERR(0, 235, __pyx_L17_except_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_GOTREF(__pyx_t_3);
          __pyx_t_5 = PyTuple_Pack(3, __pyx_t_2, __pyx_t_6, __pyx_t_3);
          if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 235, __pyx_L17_except_error)
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_16 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_5, NULL);
          __Pyx_DECREF(__pyx_t_12);
          __pyx_t_12 = 0;
          __Pyx_DECREF(__pyx_t_5);
          __pyx_t_5 = 0;
          if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 235, __pyx_L17_except_error)
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_16);
          __Pyx_DECREF(__pyx_t_16);
          __pyx_t_16 = 0;
          if (__pyx_t_9 < 0) __PYX_ERR(0, 235, __pyx_L17_except_error)
          __pyx_t_8 = ((!(__pyx_t_9 != 0)) != 0);
          if (__pyx_t_8) {
            __Pyx_GIVEREF(__pyx_t_2);
            __Pyx_GIVEREF(__pyx_t_6);
            __Pyx_XGIVEREF(__pyx_t_3);
            __Pyx_ErrRestoreWithState(__pyx_t_2, __pyx_t_6, __pyx_t_3);
            __pyx_t_2 = 0;
            __pyx_t_6 = 0;
            __pyx_t_3 = 0;
            __PYX_ERR(0, 235, __pyx_L17_except_error)
          }
          __Pyx_DECREF(__pyx_t_2);
          __pyx_t_2 = 0;
          __Pyx_DECREF(__pyx_t_6);
          __pyx_t_6 = 0;
          __Pyx_DECREF(__pyx_t_3);
          __pyx_t_3 = 0;
          goto __pyx_L16_exception_handled;
        }
      __pyx_L17_except_error:;
        __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_13);
        __Pyx_XGIVEREF(__pyx_t_14);
        __Pyx_XGIVEREF(__pyx_t_15);
        __Pyx_ExceptionReset(__pyx_t_13, __pyx_t_14, __pyx_t_15);
        goto __pyx_L1_error;
      __pyx_L16_exception_handled:;
        __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_13);
        __Pyx_XGIVEREF(__pyx_t_14);
        __Pyx_XGIVEREF(__pyx_t_15);
        __Pyx_ExceptionReset(__pyx_t_13, __pyx_t_14, __pyx_t_15);
      __pyx_L22_try_end:;
      }
    }
    /*finally:*/ {
      /*normal exit:*/ {
        if (__pyx_t_12) {
          __pyx_t_15 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_tuple__79, NULL);
          __Pyx_DECREF(__pyx_t_12);
          __pyx_t_12 = 0;
          if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 235, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_15);
          __Pyx_DECREF(__pyx_t_15);
          __pyx_t_15 = 0;
        }
        goto __pyx_L14;
      }
    __pyx_L14:;
    }
    goto __pyx_L26;
  __pyx_L9_error:;
    __Pyx_DECREF(__pyx_t_12);
    __pyx_t_12 = 0;
    goto __pyx_L1_error;
  __pyx_L26:;
  }

  /* "rfc.py":234
   *     epilogue = '\nif __name__ == "__main__": main()'
   *
   *     for f in pyfiles:             # <<<<<<<<<<<<<<
   *         with open(f[0], 'w') as file: file.write(prologue + 'def
   * test(func): func(); return func\n' + f[1])
   *
   */
}
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;

/* "rfc.py":237
 *         with open(f[0], 'w') as file: file.write(prologue + 'def test(func):
 * func(); return func\n' + f[1])
 *
 *     if run(['python3', '-B', nuitka_main]).returncode == 0:             #
 * <<<<<<<<<<<<<< for f in pyfiles: with open(f[0], 'w') as file:
 * file.write(prologue + 'test = lambda _: _\n' + f[1] + epilogue)
 */
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_run);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_nuitka_main);
if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_6);
__pyx_t_2 = PyList_New(3);
if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_2);
__Pyx_INCREF(__pyx_n_u_python3);
__Pyx_GIVEREF(__pyx_n_u_python3);
PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_u_python3);
__Pyx_INCREF(__pyx_kp_u_B);
__Pyx_GIVEREF(__pyx_kp_u_B);
PyList_SET_ITEM(__pyx_t_2, 1, __pyx_kp_u_B);
__Pyx_GIVEREF(__pyx_t_6);
PyList_SET_ITEM(__pyx_t_2, 2, __pyx_t_6);
__pyx_t_6 = 0;
__pyx_t_6 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
  __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_3);
  if (likely(__pyx_t_6)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
    __Pyx_INCREF(__pyx_t_6);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_3, function);
  }
}
if (!__pyx_t_6) {
  __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 237, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_GOTREF(__pyx_t_7);
} else {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
    __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 237, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
    __pyx_t_7 =
        __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 237, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
  {
    __pyx_t_5 = PyTuple_New(1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 237, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_6);
    __pyx_t_6 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 0 + 1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL);
    if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 237, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  }
}
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
__pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_returncode);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;
__pyx_t_7 = __Pyx_PyInt_EqObjC(__pyx_t_3, __pyx_int_0, 0, 0);
if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_7);
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
__pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_7);
if (unlikely(__pyx_t_8 < 0)) __PYX_ERR(0, 237, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;
if (__pyx_t_8) {
  /* "rfc.py":238
   *
   *     if run(['python3', '-B', nuitka_main]).returncode == 0:
   *         for f in pyfiles:             # <<<<<<<<<<<<<<
   *             with open(f[0], 'w') as file: file.write(prologue + 'test =
   * lambda _: _\n' + f[1] + epilogue)
   *
   */
  __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_pyfiles);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 238, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  if (likely(PyList_CheckExact(__pyx_t_7)) || PyTuple_CheckExact(__pyx_t_7)) {
    __pyx_t_3 = __pyx_t_7;
    __Pyx_INCREF(__pyx_t_3);
    __pyx_t_10 = 0;
    __pyx_t_11 = NULL;
  } else {
    __pyx_t_10 = -1;
    __pyx_t_3 = PyObject_GetIter(__pyx_t_7);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 238, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_11 = Py_TYPE(__pyx_t_3)->tp_iternext;
    if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 238, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_7);
  __pyx_t_7 = 0;
  for (;;) {
    if (likely(!__pyx_t_11)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_3)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
        __pyx_t_7 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_10);
        __Pyx_INCREF(__pyx_t_7);
        __pyx_t_10++;
        if (unlikely(0 < 0)) __PYX_ERR(0, 238, __pyx_L1_error)
#else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_3, __pyx_t_10);
        __pyx_t_10++;
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 238, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
#endif
      } else {
        if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
        __pyx_t_7 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_10);
        __Pyx_INCREF(__pyx_t_7);
        __pyx_t_10++;
        if (unlikely(0 < 0)) __PYX_ERR(0, 238, __pyx_L1_error)
#else
        __pyx_t_7 = PySequence_ITEM(__pyx_t_3, __pyx_t_10);
        __pyx_t_10++;
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 238, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
#endif
      }
    } else {
      __pyx_t_7 = __pyx_t_11(__pyx_t_3);
      if (unlikely(!__pyx_t_7)) {
        PyObject *exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(
                  exc_type == PyExc_StopIteration ||
                  PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
            PyErr_Clear();
          else
            __PYX_ERR(0, 238, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_7);
    }
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_f, __pyx_t_7) < 0)
      __PYX_ERR(0, 238, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7);
    __pyx_t_7 = 0;

    /* "rfc.py":239
     *     if run(['python3', '-B', nuitka_main]).returncode == 0:
     *         for f in pyfiles:
     *             with open(f[0], 'w') as file: file.write(prologue + 'test =
     * lambda _: _\n' + f[1] + epilogue)             # <<<<<<<<<<<<<<
     *
     *         nuitka_base = path.splitext(path.basename(nuitka_main))[0]
     */
    /*with:*/ {
      __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_f);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_5 = __Pyx_GetItemInt(__pyx_t_7, 0, long, 1, __Pyx_PyInt_From_long,
                                   0, 0, 1);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_7 = PyTuple_New(2);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5);
      __Pyx_INCREF(__pyx_n_u_w);
      __Pyx_GIVEREF(__pyx_n_u_w);
      PyTuple_SET_ITEM(__pyx_t_7, 1, __pyx_n_u_w);
      __pyx_t_5 = 0;
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_7, NULL);
      if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_12 = __Pyx_PyObject_LookupSpecial(__pyx_t_5, __pyx_n_s_exit);
      if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __pyx_t_2 = __Pyx_PyObject_LookupSpecial(__pyx_t_5, __pyx_n_s_enter);
      if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 239, __pyx_L30_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_6 = NULL;
      if (RFC_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
        __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_2);
        if (likely(__pyx_t_6)) {
          PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
          __Pyx_INCREF(__pyx_t_6);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_2, function);
        }
      }
      if (__pyx_t_6) {
        __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_6);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 239, __pyx_L30_error)
        __Pyx_DECREF(__pyx_t_6);
        __pyx_t_6 = 0;
      } else {
        __pyx_t_7 = __Pyx_PyObject_CallNoArg(__pyx_t_2);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 239, __pyx_L30_error)
      }
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = __pyx_t_7;
      __pyx_t_7 = 0;
      __Pyx_DECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      /*try:*/ {{__Pyx_PyThreadState_declare __Pyx_PyThreadState_assign
                     __Pyx_ExceptionSave(&__pyx_t_15, &__pyx_t_14, &__pyx_t_13);
      __Pyx_XGOTREF(__pyx_t_15);
      __Pyx_XGOTREF(__pyx_t_14);
      __Pyx_XGOTREF(__pyx_t_13);
      /*try:*/ {
        if (PyDict_SetItem(__pyx_d, __pyx_n_s_file, __pyx_t_2) < 0)
          __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_DECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_file);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_write);
        if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_prologue);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_6 = PyNumber_Add(__pyx_t_5, __pyx_kp_u_test_lambda);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_f);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_5, 1, long, 1,
                                     __Pyx_PyInt_From_long, 0, 0, 1);
        if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        __pyx_t_5 = PyNumber_Add(__pyx_t_6, __pyx_t_1);
        if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_6);
        __pyx_t_6 = 0;
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_epilogue);
        if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_6 = PyNumber_Add(__pyx_t_5, __pyx_t_1);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 239, __pyx_L36_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        __Pyx_DECREF(__pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_1 = NULL;
        if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
          __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_7);
          if (likely(__pyx_t_1)) {
            PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
            __Pyx_INCREF(__pyx_t_1);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_7, function);
          }
        }
        if (!__pyx_t_1) {
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_6);
          if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 239, __pyx_L36_error)
          __Pyx_DECREF(__pyx_t_6);
          __pyx_t_6 = 0;
          __Pyx_GOTREF(__pyx_t_2);
        } else {
#if RFC_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_6};
            __pyx_t_2 =
                __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 239, __pyx_L36_error)
            __Pyx_XDECREF(__pyx_t_1);
            __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_6);
            __pyx_t_6 = 0;
          } else
#endif
#if RFC_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_6};
            __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_7,
                                                   __pyx_temp + 1 - 1, 1 + 1);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 239, __pyx_L36_error)
            __Pyx_XDECREF(__pyx_t_1);
            __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_6);
            __pyx_t_6 = 0;
          } else
#endif
          {
            __pyx_t_5 = PyTuple_New(1 + 1);
            if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L36_error)
            __Pyx_GOTREF(__pyx_t_5);
            __Pyx_GIVEREF(__pyx_t_1);
            PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
            __pyx_t_1 = NULL;
            __Pyx_GIVEREF(__pyx_t_6);
            PyTuple_SET_ITEM(__pyx_t_5, 0 + 1, __pyx_t_6);
            __pyx_t_6 = 0;
            __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_5, NULL);
            if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 239, __pyx_L36_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_5);
            __pyx_t_5 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_2);
        __pyx_t_2 = 0;
      }
      __Pyx_XDECREF(__pyx_t_15);
      __pyx_t_15 = 0;
      __Pyx_XDECREF(__pyx_t_14);
      __pyx_t_14 = 0;
      __Pyx_XDECREF(__pyx_t_13);
      __pyx_t_13 = 0;
      goto __pyx_L43_try_end;
    __pyx_L36_error:;
      __Pyx_PyThreadState_assign __Pyx_XDECREF(__pyx_t_4);
      __pyx_t_4 = 0;
      __Pyx_XDECREF(__pyx_t_1);
      __pyx_t_1 = 0;
      __Pyx_XDECREF(__pyx_t_6);
      __pyx_t_6 = 0;
      __Pyx_XDECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_XDECREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __Pyx_XDECREF(__pyx_t_2);
      __pyx_t_2 = 0;
      /*except:*/ {
        __Pyx_AddTraceback("rfc", __pyx_clineno, __pyx_lineno, __pyx_filename);
        if (__Pyx_GetException(&__pyx_t_2, &__pyx_t_7, &__pyx_t_5) < 0)
          __PYX_ERR(0, 239, __pyx_L38_except_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_6 = PyTuple_Pack(3, __pyx_t_2, __pyx_t_7, __pyx_t_5);
        if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 239, __pyx_L38_except_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_16 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_6, NULL);
        __Pyx_DECREF(__pyx_t_12);
        __pyx_t_12 = 0;
        __Pyx_DECREF(__pyx_t_6);
        __pyx_t_6 = 0;
        if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 239, __pyx_L38_except_error)
        __Pyx_GOTREF(__pyx_t_16);
        __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_16);
        __Pyx_DECREF(__pyx_t_16);
        __pyx_t_16 = 0;
        if (__pyx_t_8 < 0) __PYX_ERR(0, 239, __pyx_L38_except_error)
        __pyx_t_9 = ((!(__pyx_t_8 != 0)) != 0);
        if (__pyx_t_9) {
          __Pyx_GIVEREF(__pyx_t_2);
          __Pyx_GIVEREF(__pyx_t_7);
          __Pyx_XGIVEREF(__pyx_t_5);
          __Pyx_ErrRestoreWithState(__pyx_t_2, __pyx_t_7, __pyx_t_5);
          __pyx_t_2 = 0;
          __pyx_t_7 = 0;
          __pyx_t_5 = 0;
          __PYX_ERR(0, 239, __pyx_L38_except_error)
        }
        __Pyx_DECREF(__pyx_t_2);
        __pyx_t_2 = 0;
        __Pyx_DECREF(__pyx_t_7);
        __pyx_t_7 = 0;
        __Pyx_DECREF(__pyx_t_5);
        __pyx_t_5 = 0;
        goto __pyx_L37_exception_handled;
      }
    __pyx_L38_except_error:;
      __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_15);
      __Pyx_XGIVEREF(__pyx_t_14);
      __Pyx_XGIVEREF(__pyx_t_13);
      __Pyx_ExceptionReset(__pyx_t_15, __pyx_t_14, __pyx_t_13);
      goto __pyx_L1_error;
    __pyx_L37_exception_handled:;
      __Pyx_PyThreadState_assign __Pyx_XGIVEREF(__pyx_t_15);
      __Pyx_XGIVEREF(__pyx_t_14);
      __Pyx_XGIVEREF(__pyx_t_13);
      __Pyx_ExceptionReset(__pyx_t_15, __pyx_t_14, __pyx_t_13);
    __pyx_L43_try_end:;
    }
  }
  /*finally:*/ {
    /*normal exit:*/ {
      if (__pyx_t_12) {
        __pyx_t_13 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_tuple__80, NULL);
        __Pyx_DECREF(__pyx_t_12);
        __pyx_t_12 = 0;
        if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 239, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_13);
        __Pyx_DECREF(__pyx_t_13);
        __pyx_t_13 = 0;
      }
      goto __pyx_L35;
    }
  __pyx_L35:;
  }
  goto __pyx_L47;
__pyx_L30_error:;
  __Pyx_DECREF(__pyx_t_12);
  __pyx_t_12 = 0;
  goto __pyx_L1_error;
__pyx_L47:;
}

/* "rfc.py":238
 *
 *     if run(['python3', '-B', nuitka_main]).returncode == 0:
 *         for f in pyfiles:             # <<<<<<<<<<<<<<
 *             with open(f[0], 'w') as file: file.write(prologue + 'test =
 * lambda _: _\n' + f[1] + epilogue)
 *
 */
}
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;

/* "rfc.py":241
 *             with open(f[0], 'w') as file: file.write(prologue + 'test =
 * lambda _: _\n' + f[1] + epilogue)
 *
 *         nuitka_base = path.splitext(path.basename(nuitka_main))[0] #
 * <<<<<<<<<<<<<< tmpdir = mkdtemp() run(['nuitka', nuitka_main,
 * '--recurse-all', '--python-version=3.6', f'--output-dir={tmpdir}'],
 * stderr=PIPE)
 */
__pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_path);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_splitext);
if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_7);
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_path);
if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_2);
__pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_basename);
if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_6);
__Pyx_DECREF(__pyx_t_2);
__pyx_t_2 = 0;
__pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_nuitka_main);
if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_2);
__pyx_t_1 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
  __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_6);
  if (likely(__pyx_t_1)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_6);
    __Pyx_INCREF(__pyx_t_1);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_6, function);
  }
}
if (!__pyx_t_1) {
  __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_2);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_GOTREF(__pyx_t_5);
} else {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_6)) {
    PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_2};
    __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
    PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_2};
    __pyx_t_5 =
        __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1);
    __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
  {
    __pyx_t_4 = PyTuple_New(1 + 1);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
    __pyx_t_1 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_4, 0 + 1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_4, NULL);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
  }
}
__Pyx_DECREF(__pyx_t_6);
__pyx_t_6 = 0;
__pyx_t_6 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
  __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_7);
  if (likely(__pyx_t_6)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_7);
    __Pyx_INCREF(__pyx_t_6);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_7, function);
  }
}
if (!__pyx_t_6) {
  __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_5);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 241, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __Pyx_GOTREF(__pyx_t_3);
} else {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_7)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_5};
    __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_5};
    __pyx_t_3 =
        __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  } else
#endif
  {
    __pyx_t_4 = PyTuple_New(1 + 1);
    if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_6);
    __pyx_t_6 = NULL;
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_4, 0 + 1, __pyx_t_5);
    __pyx_t_5 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_4, NULL);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4);
    __pyx_t_4 = 0;
  }
}
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;
__pyx_t_7 =
    __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_7);
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
if (PyDict_SetItem(__pyx_d, __pyx_n_s_nuitka_base, __pyx_t_7) < 0)
  __PYX_ERR(0, 241, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;

/* "rfc.py":242
 *
 *         nuitka_base = path.splitext(path.basename(nuitka_main))[0]
 *         tmpdir = mkdtemp()             # <<<<<<<<<<<<<<
 *         run(['nuitka', nuitka_main, '--recurse-all', '--python-version=3.6',
 * f'--output-dir={tmpdir}'], stderr=PIPE) res = tmpdir + '/' + nuitka_base +
 * '.exe'
 */
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_mkdtemp);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 242, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__pyx_t_4 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
  __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_3);
  if (likely(__pyx_t_4)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_3);
    __Pyx_INCREF(__pyx_t_4);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_3, function);
  }
}
if (__pyx_t_4) {
  __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 242, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4);
  __pyx_t_4 = 0;
} else {
  __pyx_t_7 = __Pyx_PyObject_CallNoArg(__pyx_t_3);
  if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 242, __pyx_L1_error)
}
__Pyx_GOTREF(__pyx_t_7);
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
if (PyDict_SetItem(__pyx_d, __pyx_n_s_tmpdir, __pyx_t_7) < 0)
  __PYX_ERR(0, 242, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;

/* "rfc.py":243
 *         nuitka_base = path.splitext(path.basename(nuitka_main))[0]
 *         tmpdir = mkdtemp()
 *         run(['nuitka', nuitka_main, '--recurse-all', '--python-version=3.6',
 * f'--output-dir={tmpdir}'], stderr=PIPE)             # <<<<<<<<<<<<<< res =
 * tmpdir + '/' + nuitka_base + '.exe' move(res, args.o)
 */
__pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_run);
if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_7);
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_nuitka_main);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_tmpdir);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__pyx_t_5 = __Pyx_PyObject_FormatSimple(__pyx_t_4, __pyx_empty_unicode);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
__pyx_t_4 = __Pyx_PyUnicode_Concat(__pyx_kp_u_output_dir, __pyx_t_5);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__pyx_t_5 = PyList_New(5);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__Pyx_INCREF(__pyx_n_u_nuitka);
__Pyx_GIVEREF(__pyx_n_u_nuitka);
PyList_SET_ITEM(__pyx_t_5, 0, __pyx_n_u_nuitka);
__Pyx_GIVEREF(__pyx_t_3);
PyList_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
__Pyx_INCREF(__pyx_kp_u_recurse_all);
__Pyx_GIVEREF(__pyx_kp_u_recurse_all);
PyList_SET_ITEM(__pyx_t_5, 2, __pyx_kp_u_recurse_all);
__Pyx_INCREF(__pyx_kp_u_python_version_3_6);
__Pyx_GIVEREF(__pyx_kp_u_python_version_3_6);
PyList_SET_ITEM(__pyx_t_5, 3, __pyx_kp_u_python_version_3_6);
__Pyx_GIVEREF(__pyx_t_4);
PyList_SET_ITEM(__pyx_t_5, 4, __pyx_t_4);
__pyx_t_3 = 0;
__pyx_t_4 = 0;
__pyx_t_4 = PyTuple_New(1);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__Pyx_GIVEREF(__pyx_t_5);
PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5);
__pyx_t_5 = 0;
__pyx_t_5 = PyDict_New();
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_PIPE);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
if (PyDict_SetItem(__pyx_t_5, __pyx_n_s_stderr, __pyx_t_3) < 0)
  __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
__pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_4, __pyx_t_5);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 243, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;

/* "rfc.py":244
 *         tmpdir = mkdtemp()
 *         run(['nuitka', nuitka_main, '--recurse-all', '--python-version=3.6',
 * f'--output-dir={tmpdir}'], stderr=PIPE) res = tmpdir + '/' + nuitka_base +
 * '.exe'             # <<<<<<<<<<<<<< move(res, args.o)
 *
 */
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_tmpdir);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__pyx_t_5 = PyNumber_Add(__pyx_t_3, __pyx_kp_u__81);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_nuitka_base);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__pyx_t_4 = PyNumber_Add(__pyx_t_5, __pyx_t_3);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__Pyx_DECREF(__pyx_t_5);
__pyx_t_5 = 0;
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
__pyx_t_3 = PyNumber_Add(__pyx_t_4, __pyx_kp_u_exe);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
if (PyDict_SetItem(__pyx_d, __pyx_n_s_res, __pyx_t_3) < 0)
  __PYX_ERR(0, 244, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;

/* "rfc.py":245
 *         run(['nuitka', nuitka_main, '--recurse-all', '--python-version=3.6',
 * f'--output-dir={tmpdir}'], stderr=PIPE) res = tmpdir + '/' + nuitka_base +
 * '.exe' move(res, args.o)             # <<<<<<<<<<<<<<
 *
 *     rmtree(tmpdir)
 */
__pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_move);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 245, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_res);
if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 245, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_5);
__pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_args);
if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 245, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_7);
__pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_o_2);
if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 245, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_6);
__Pyx_DECREF(__pyx_t_7);
__pyx_t_7 = 0;
__pyx_t_7 = NULL;
__pyx_t_17 = 0;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
  __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_4);
  if (likely(__pyx_t_7)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
    __Pyx_INCREF(__pyx_t_7);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_4, function);
    __pyx_t_17 = 1;
  }
}
#if RFC_FAST_PYCALL
if (PyFunction_Check(__pyx_t_4)) {
  PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_t_5, __pyx_t_6};
  __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - __pyx_t_17,
                                        2 + __pyx_t_17);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 245, __pyx_L1_error)
  __Pyx_XDECREF(__pyx_t_7);
  __pyx_t_7 = 0;
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;
} else
#endif
#if RFC_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
  PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_t_5, __pyx_t_6};
  __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - __pyx_t_17,
                                         2 + __pyx_t_17);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 245, __pyx_L1_error)
  __Pyx_XDECREF(__pyx_t_7);
  __pyx_t_7 = 0;
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __Pyx_DECREF(__pyx_t_6);
  __pyx_t_6 = 0;
} else
#endif
{
  __pyx_t_2 = PyTuple_New(2 + __pyx_t_17);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 245, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (__pyx_t_7) {
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_7);
    __pyx_t_7 = NULL;
  }
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_2, 0 + __pyx_t_17, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_2, 1 + __pyx_t_17, __pyx_t_6);
  __pyx_t_5 = 0;
  __pyx_t_6 = 0;
  __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_2, NULL);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 245, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
}
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;

/* "rfc.py":237
 *         with open(f[0], 'w') as file: file.write(prologue + 'def test(func):
 * func(); return func\n' + f[1])
 *
 *     if run(['python3', '-B', nuitka_main]).returncode == 0:             #
 * <<<<<<<<<<<<<< for f in pyfiles: with open(f[0], 'w') as file:
 * file.write(prologue + 'test = lambda _: _\n' + f[1] + epilogue)
 */
}

/* "rfc.py":247
 *         move(res, args.o)
 *
 *     rmtree(tmpdir)             # <<<<<<<<<<<<<<
 *     for file in pyfiles: os.remove(file[0])
 */
__pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_rmtree);
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 247, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
__pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_tmpdir);
if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 247, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_2);
__pyx_t_6 = NULL;
if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
  __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_4);
  if (likely(__pyx_t_6)) {
    PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_4);
    __Pyx_INCREF(__pyx_t_6);
    __Pyx_INCREF(function);
    __Pyx_DECREF_SET(__pyx_t_4, function);
  }
}
if (!__pyx_t_6) {
  __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_2);
  if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 247, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_GOTREF(__pyx_t_3);
} else {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
    __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 247, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
#if RFC_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
    PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
    __pyx_t_3 =
        __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp + 1 - 1, 1 + 1);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 247, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2);
    __pyx_t_2 = 0;
  } else
#endif
  {
    __pyx_t_5 = PyTuple_New(1 + 1);
    if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 247, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_6);
    __pyx_t_6 = NULL;
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_5, 0 + 1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 247, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_5);
    __pyx_t_5 = 0;
  }
}
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;

/* "rfc.py":248
 *
 *     rmtree(tmpdir)
 *     for file in pyfiles: os.remove(file[0])             # <<<<<<<<<<<<<<
 */
__pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_pyfiles);
if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_3);
if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
  __pyx_t_4 = __pyx_t_3;
  __Pyx_INCREF(__pyx_t_4);
  __pyx_t_10 = 0;
  __pyx_t_11 = NULL;
} else {
  __pyx_t_10 = -1;
  __pyx_t_4 = PyObject_GetIter(__pyx_t_3);
  if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_11 = Py_TYPE(__pyx_t_4)->tp_iternext;
  if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 248, __pyx_L1_error)
}
__Pyx_DECREF(__pyx_t_3);
__pyx_t_3 = 0;
for (;;) {
  if (likely(!__pyx_t_11)) {
    if (likely(PyList_CheckExact(__pyx_t_4))) {
      if (__pyx_t_10 >= PyList_GET_SIZE(__pyx_t_4)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
      __pyx_t_3 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_10);
      __Pyx_INCREF(__pyx_t_3);
      __pyx_t_10++;
      if (unlikely(0 < 0)) __PYX_ERR(0, 248, __pyx_L1_error)
#else
      __pyx_t_3 = PySequence_ITEM(__pyx_t_4, __pyx_t_10);
      __pyx_t_10++;
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
#endif
    } else {
      if (__pyx_t_10 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
      __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_10);
      __Pyx_INCREF(__pyx_t_3);
      __pyx_t_10++;
      if (unlikely(0 < 0)) __PYX_ERR(0, 248, __pyx_L1_error)
#else
      __pyx_t_3 = PySequence_ITEM(__pyx_t_4, __pyx_t_10);
      __pyx_t_10++;
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
#endif
    }
  } else {
    __pyx_t_3 = __pyx_t_11(__pyx_t_4);
    if (unlikely(!__pyx_t_3)) {
      PyObject *exc_type = PyErr_Occurred();
      if (exc_type) {
        if (likely(exc_type == PyExc_StopIteration ||
                   PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)))
          PyErr_Clear();
        else
          __PYX_ERR(0, 248, __pyx_L1_error)
      }
      break;
    }
    __Pyx_GOTREF(__pyx_t_3);
  }
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_file, __pyx_t_3) < 0)
    __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_os);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_remove);
  if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_file);
  if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_6 =
      __Pyx_GetItemInt(__pyx_t_5, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1);
  if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 248, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_5);
  __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (RFC_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject *function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_6);
    if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6);
    __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
  } else {
#if RFC_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_6};
      __pyx_t_3 =
          __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
    } else
#endif
#if RFC_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_6};
      __pyx_t_3 =
          __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp + 1 - 1, 1 + 1);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_6);
      __pyx_t_6 = 0;
    } else
#endif
    {
      __pyx_t_7 = PyTuple_New(1 + 1);
      if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5);
      __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_7, 0 + 1, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_7, NULL);
      if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_7);
      __pyx_t_7 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3);
  __pyx_t_3 = 0;
}
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;

/* "rfc.py":214
 *     return (filename[:-3] + '.py', FormatCode(output)[0])
 *
 * if __name__ == "__main__":             # <<<<<<<<<<<<<<
 *     arg_parser = ArgumentParser(description='The bootstrap compiler for
 * Raft.') arg_parser.add_argument('input', help='Input file or directory')
 */
}

/* "rfc.py":1
 * import os             # <<<<<<<<<<<<<<
 *
 * from tempfile import mkdtemp
 */
__pyx_t_4 = PyDict_New();
if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 1, __pyx_L1_error)
__Pyx_GOTREF(__pyx_t_4);
if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_4) < 0)
  __PYX_ERR(0, 1, __pyx_L1_error)
__Pyx_DECREF(__pyx_t_4);
__pyx_t_4 = 0;

/*--- Wrapped vars code ---*/

goto __pyx_L0;
__pyx_L1_error:;
__Pyx_XDECREF(__pyx_t_1);
__Pyx_XDECREF(__pyx_t_2);
__Pyx_XDECREF(__pyx_t_3);
__Pyx_XDECREF(__pyx_t_4);
__Pyx_XDECREF(__pyx_t_5);
__Pyx_XDECREF(__pyx_t_6);
__Pyx_XDECREF(__pyx_t_7);
if (__pyx_m) {
  if (__pyx_d) {
    __Pyx_AddTraceback("init rfc", 0, __pyx_lineno, __pyx_filename);
  }
  Py_DECREF(__pyx_m);
  __pyx_m = 0;
} else if (!PyErr_Occurred()) {
  PyErr_SetString(PyExc_ImportError, "init rfc");
}
__pyx_L0:;
__Pyx_RefNannyFinishContext();
#if PY_MAJOR_VERSION < 3
return;
#else
return __pyx_m;
#endif
}

/* --- Runtime support code --- */
/* Refnanny */
#if RFC_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
  PyObject *m = NULL, *p = NULL;
  void *r = NULL;
  m = PyImport_ImportModule((char *)modname);
  if (!m) goto end;
  p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
  if (!p) goto end;
  r = PyLong_AsVoidPtr(p);
end:
  Py_XDECREF(p);
  Py_XDECREF(m);
  return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

/* GetBuiltinName */
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
  PyObject *result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
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

/* RaiseArgTupleInvalid */
static void __Pyx_RaiseArgtupleInvalid(const char *func_name, int exact,
                                       Py_ssize_t num_min, Py_ssize_t num_max,
                                       Py_ssize_t num_found) {
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
               "%.200s() takes %.8s %" RFC_FORMAT_SSIZE_T
               "d positional argument%.1s (%" RFC_FORMAT_SSIZE_T "d given)",
               func_name, more_or_less, num_expected,
               (num_expected == 1) ? "" : "s", num_found);
}

/* RaiseDoubleKeywords */
static void __Pyx_RaiseDoubleKeywordsError(const char *func_name,
                                           PyObject *kw_name) {
  PyErr_Format(PyExc_TypeError,
#if PY_MAJOR_VERSION >= 3
               "%s() got multiple values for keyword argument '%U'", func_name,
               kw_name);
#else
               "%s() got multiple values for keyword argument '%s'", func_name,
               PyString_AsString(kw_name));
#endif
}

/* ParseKeywords */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],
                                       PyObject *kwds2, PyObject *values[],
                                       Py_ssize_t num_pos_args,
                                       const char *function_name) {
  PyObject *key = 0, *value = 0;
  Py_ssize_t pos = 0;
  PyObject ***name;
  PyObject ***first_kw_arg = argnames + num_pos_args;
  while (PyDict_Next(kwds, &pos, &key, &value)) {
    name = first_kw_arg;
    while (*name && (**name != key)) name++;
    if (*name) {
      values[name - argnames] = value;
      continue;
    }
    name = first_kw_arg;
#if PY_MAJOR_VERSION < 3
    if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
      while (*name) {
        if ((RFC_COMPILING_IN_PYPY ||
             PyString_GET_SIZE(**name) == PyString_GET_SIZE(key)) &&
            _PyString_Eq(**name, key)) {
          values[name - argnames] = value;
          break;
        }
        name++;
      }
      if (*name)
        continue;
      else {
        PyObject ***argname = argnames;
        while (argname != first_kw_arg) {
          if ((**argname == key) ||
              ((RFC_COMPILING_IN_PYPY ||
                PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key)) &&
               _PyString_Eq(**argname, key))) {
            goto arg_passed_twice;
          }
          argname++;
        }
      }
    } else
#endif
        if (likely(PyUnicode_Check(key))) {
      while (*name) {
        int cmp = (**name == key)
                      ? 0
                      :
#if !RFC_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                      (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key))
                          ? 1
                          :
#endif
                          PyUnicode_Compare(**name, key);
        if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
        if (cmp == 0) {
          values[name - argnames] = value;
          break;
        }
        name++;
      }
      if (*name)
        continue;
      else {
        PyObject ***argname = argnames;
        while (argname != first_kw_arg) {
          int cmp = (**argname == key) ? 0 :
#if !RFC_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                                       (PyUnicode_GET_SIZE(**argname) !=
                                        PyUnicode_GET_SIZE(key))
                                           ? 1
                                           :
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
  PyErr_Format(PyExc_TypeError, "%.200s() keywords must be strings",
               function_name);
  goto bad;
invalid_keyword:
  PyErr_Format(PyExc_TypeError,
#if PY_MAJOR_VERSION < 3
               "%.200s() got an unexpected keyword argument '%.200s'",
               function_name, PyString_AsString(key));
#else
               "%s() got an unexpected keyword argument '%U'", function_name,
               key);
#endif
bad:
  return -1;
}

/* JoinPyUnicode */
static PyObject *__Pyx_PyUnicode_Join(PyObject *value_tuple,
                                      Py_ssize_t value_count,
                                      Py_ssize_t result_ulength,
                                      RFC_UNUSED Py_UCS4 max_char) {
#if RFC_USE_UNICODE_INTERNALS && RFC_ASSUME_SAFE_MACROS && \
    !RFC_AVOID_BORROWED_REFS
  PyObject *result_uval;
  int result_ukind;
  Py_ssize_t i, char_pos;
  void *result_udata;
#if RFC_PEP393_ENABLED
  result_uval = PyUnicode_New(result_ulength, max_char);
  if (unlikely(!result_uval)) return NULL;
  result_ukind = (max_char <= 255) ? PyUnicode_1BYTE_KIND
                                   : (max_char <= 65535) ? PyUnicode_2BYTE_KIND
                                                         : PyUnicode_4BYTE_KIND;
  result_udata = PyUnicode_DATA(result_uval);
#else
  result_uval = PyUnicode_FromUnicode(NULL, result_ulength);
  if (unlikely(!result_uval)) return NULL;
  result_ukind = sizeof(Py_UNICODE);
  result_udata = PyUnicode_AS_UNICODE(result_uval);
#endif
  char_pos = 0;
  for (i = 0; i < value_count; i++) {
    int ukind;
    Py_ssize_t ulength;
    void *udata;
    PyObject *uval = PyTuple_GET_ITEM(value_tuple, i);
    if (unlikely(__Pyx_PyUnicode_READY(uval))) goto bad;
    ulength = __Pyx_PyUnicode_GET_LENGTH(uval);
    if (unlikely(!ulength)) continue;
    if (unlikely(char_pos + ulength < 0)) goto overflow;
    ukind = __Pyx_PyUnicode_KIND(uval);
    udata = __Pyx_PyUnicode_DATA(uval);
    if (!RFC_PEP393_ENABLED || ukind == result_ukind) {
      memcpy((char *)result_udata + char_pos * result_ukind, udata,
             ulength * result_ukind);
    } else {
#if RFC_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x030300F0
      _PyUnicode_FastCopyCharacters(result_uval, char_pos, uval, 0, ulength);
#else
      Py_ssize_t j;
      for (j = 0; j < ulength; j++) {
        Py_UCS4 uchar = __Pyx_PyUnicode_READ(ukind, udata, j);
        __Pyx_PyUnicode_WRITE(result_ukind, result_udata, char_pos + j, uchar);
      }
#endif
    }
    char_pos += ulength;
  }
  return result_uval;
overflow:
  PyErr_SetString(PyExc_OverflowError,
                  "join() result is too long for a Python string");
bad:
  Py_DECREF(result_uval);
  return NULL;
#else
  result_ulength++;
  value_count++;
  return PyUnicode_Join(__pyx_empty_unicode, value_tuple);
#endif
}

/* PyObjectCall */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_Call(PyObject *func, PyObject *arg,
                                                PyObject *kw) {
  PyObject *result;
  ternaryfunc call = func->ob_type->tp_call;
  if (unlikely(!call)) return PyObject_Call(func, arg, kw);
  if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object")))
    return NULL;
  result = (*call)(func, arg, kw);
  Py_LeaveRecursiveCall();
  if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
    PyErr_SetString(PyExc_SystemError,
                    "NULL result without error in PyObject_Call");
  }
  return result;
}
#endif

/* PyFunctionFastCall */
#if RFC_FAST_PYCALL
#include "frameobject.h"
static PyObject *__Pyx_PyFunction_FastCallNoKw(PyCodeObject *co,
                                               PyObject **args, Py_ssize_t na,
                                               PyObject *globals) {
  PyFrameObject *f;
  PyThreadState *tstate = PyThreadState_GET();
  PyObject **fastlocals;
  Py_ssize_t i;
  PyObject *result;
  assert(globals != NULL);
  /* XXX Perhaps we should create a specialized
     PyFrame_New() that doesn't take locals, but does
     take builtins without sanity checking them.
     */
  assert(tstate != NULL);
  f = PyFrame_New(tstate, co, globals, NULL);
  if (f == NULL) {
    return NULL;
  }
  fastlocals = f->f_localsplus;
  for (i = 0; i < na; i++) {
    Py_INCREF(*args);
    fastlocals[i] = *args++;
  }
  result = PyEval_EvalFrameEx(f, 0);
  ++tstate->recursion_depth;
  Py_DECREF(f);
  --tstate->recursion_depth;
  return result;
}
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args,
                                               int nargs, PyObject *kwargs) {
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
  if (Py_EnterRecursiveCall((char *)" while calling a Python object")) {
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
    } else if (nargs == 0 && argdefs != NULL &&
               co->co_argcount == Py_SIZE(argdefs)) {
      /* function called with no arguments, but all parameters have
         a default value: use default values as arguments .*/
      args = &PyTuple_GET_ITEM(argdefs, 0);
      result =
          __Pyx_PyFunction_FastCallNoKw(co, args, Py_SIZE(argdefs), globals);
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
    while (PyDict_Next(kwargs, &pos, &k[i], &k[i + 1])) {
      Py_INCREF(k[i]);
      Py_INCREF(k[i + 1]);
      i += 2;
    }
    nk = i / 2;
  } else {
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
  } else {
    d = NULL;
    nd = 0;
  }
#if PY_MAJOR_VERSION >= 3
  result = PyEval_EvalCodeEx((PyObject *)co, globals, (PyObject *)NULL, args,
                             nargs, k, (int)nk, d, (int)nd, kwdefs, closure);
#else
  result = PyEval_EvalCodeEx(co, globals, (PyObject *)NULL, args, nargs, k,
                             (int)nk, d, (int)nd, closure);
#endif
  Py_XDECREF(kwtuple);
done:
  Py_LeaveRecursiveCall();
  return result;
}
#endif
#endif

/* PyCFunctionFastCall */
#if RFC_FAST_PYCCALL
static RFC_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func_obj,
                                                       PyObject **args,
                                                       Py_ssize_t nargs) {
  PyCFunctionObject *func = (PyCFunctionObject *)func_obj;
  PyCFunction meth = PyCFunction_GET_FUNCTION(func);
  PyObject *self = PyCFunction_GET_SELF(func);
  int flags = PyCFunction_GET_FLAGS(func);
  assert(PyCFunction_Check(func));
  assert(METH_FASTCALL ==
         (flags & ~(METH_CLASS | METH_STATIC | METH_COEXIST | METH_KEYWORDS)));
  assert(nargs >= 0);
  assert(nargs == 0 || args != NULL);
  /* _PyCFunction_FastCallDict() must not be called with an exception set,
     because it may clear it (directly or indirectly) and so the
     caller loses its exception */
  assert(!PyErr_Occurred());
  if ((PY_VERSION_HEX < 0x030700A0) || unlikely(flags & METH_KEYWORDS)) {
    return (*((__Pyx_PyCFunctionFastWithKeywords)meth))(self, args, nargs,
                                                        NULL);
  } else {
    return (*((__Pyx_PyCFunctionFast)meth))(self, args, nargs);
  }
}
#endif

/* GetItemInt */
static RFC_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject *j) {
  PyObject *r;
  if (!j) return NULL;
  r = PyObject_GetItem(o, j);
  Py_DECREF(j);
  return r;
}
static RFC_INLINE PyObject *__Pyx_GetItemInt_List_Fast(
    PyObject *o, Py_ssize_t i, RFC_NCP_UNUSED int wraparound,
    RFC_NCP_UNUSED int boundscheck) {
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
  Py_ssize_t wrapped_i = i;
  if (wraparound & unlikely(i < 0)) {
    wrapped_i += PyList_GET_SIZE(o);
  }
  if ((!boundscheck) ||
      likely((0 <= wrapped_i) & (wrapped_i < PyList_GET_SIZE(o)))) {
    PyObject *r = PyList_GET_ITEM(o, wrapped_i);
    Py_INCREF(r);
    return r;
  }
  return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
  return PySequence_GetItem(o, i);
#endif
}
static RFC_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(
    PyObject *o, Py_ssize_t i, RFC_NCP_UNUSED int wraparound,
    RFC_NCP_UNUSED int boundscheck) {
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
  Py_ssize_t wrapped_i = i;
  if (wraparound & unlikely(i < 0)) {
    wrapped_i += PyTuple_GET_SIZE(o);
  }
  if ((!boundscheck) ||
      likely((0 <= wrapped_i) & (wrapped_i < PyTuple_GET_SIZE(o)))) {
    PyObject *r = PyTuple_GET_ITEM(o, wrapped_i);
    Py_INCREF(r);
    return r;
  }
  return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
  return PySequence_GetItem(o, i);
#endif
}
static RFC_INLINE PyObject *__Pyx_GetItemInt_Fast(
    PyObject *o, Py_ssize_t i, int is_list, RFC_NCP_UNUSED int wraparound,
    RFC_NCP_UNUSED int boundscheck) {
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS && RFC_USE_TYPE_SLOTS
  if (is_list || PyList_CheckExact(o)) {
    Py_ssize_t n =
        ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
    if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
      PyObject *r = PyList_GET_ITEM(o, n);
      Py_INCREF(r);
      return r;
    }
  } else if (PyTuple_CheckExact(o)) {
    Py_ssize_t n =
        ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
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
          if (!PyErr_ExceptionMatches(PyExc_OverflowError)) return NULL;
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

/* SetItemInt */
static RFC_INLINE int __Pyx_SetItemInt_Generic(PyObject *o, PyObject *j,
                                               PyObject *v) {
  int r;
  if (!j) return -1;
  r = PyObject_SetItem(o, j, v);
  Py_DECREF(j);
  return r;
}
static RFC_INLINE int __Pyx_SetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                            PyObject *v, int is_list,
                                            RFC_NCP_UNUSED int wraparound,
                                            RFC_NCP_UNUSED int boundscheck) {
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS && RFC_USE_TYPE_SLOTS
  if (is_list || PyList_CheckExact(o)) {
    Py_ssize_t n =
        (!wraparound) ? i : ((likely(i >= 0)) ? i : i + PyList_GET_SIZE(o));
    if ((!boundscheck) || likely((n >= 0) & (n < PyList_GET_SIZE(o)))) {
      PyObject *old = PyList_GET_ITEM(o, n);
      Py_INCREF(v);
      PyList_SET_ITEM(o, n, v);
      Py_DECREF(old);
      return 1;
    }
  } else {
    PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
    if (likely(m && m->sq_ass_item)) {
      if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
        Py_ssize_t l = m->sq_length(o);
        if (likely(l >= 0)) {
          i += l;
        } else {
          if (!PyErr_ExceptionMatches(PyExc_OverflowError)) return -1;
          PyErr_Clear();
        }
      }
      return m->sq_ass_item(o, i, v);
    }
  }
#else
#if RFC_COMPILING_IN_PYPY
  if (is_list || (PySequence_Check(o) && !PyDict_Check(o))) {
#else
  if (is_list || PySequence_Check(o)) {
#endif
    return PySequence_SetItem(o, i, v);
  }
#endif
  return __Pyx_SetItemInt_Generic(o, PyInt_FromSsize_t(i), v);
}

/* BytesEquals */
static RFC_INLINE int __Pyx_PyBytes_Equals(PyObject *s1, PyObject *s2,
                                           int equals) {
#if RFC_COMPILING_IN_PYPY
  return PyObject_RichCompareBool(s1, s2, equals);
#else
  if (s1 == s2) {
    return (equals == Py_EQ);
  } else if (PyBytes_CheckExact(s1) & PyBytes_CheckExact(s2)) {
    const char *ps1, *ps2;
    Py_ssize_t length = PyBytes_GET_SIZE(s1);
    if (length != PyBytes_GET_SIZE(s2)) return (equals == Py_NE);
    ps1 = PyBytes_AS_STRING(s1);
    ps2 = PyBytes_AS_STRING(s2);
    if (ps1[0] != ps2[0]) {
      return (equals == Py_NE);
    } else if (length == 1) {
      return (equals == Py_EQ);
    } else {
      int result;
#if RFC_USE_UNICODE_INTERNALS
      Py_hash_t hash1, hash2;
      hash1 = ((PyBytesObject *)s1)->ob_shash;
      hash2 = ((PyBytesObject *)s2)->ob_shash;
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
    PyObject *py_result = PyObject_RichCompare(s1, s2, equals);
    if (!py_result) return -1;
    result = __Pyx_PyObject_IsTrue(py_result);
    Py_DECREF(py_result);
    return result;
  }
#endif
}

/* UnicodeEquals */
static RFC_INLINE int __Pyx_PyUnicode_Equals(PyObject *s1, PyObject *s2,
                                             int equals) {
#if RFC_COMPILING_IN_PYPY
  return PyObject_RichCompareBool(s1, s2, equals);
#else
#if PY_MAJOR_VERSION < 3
  PyObject *owned_ref = NULL;
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
    if (unlikely(!owned_ref)) return -1;
    s2 = owned_ref;
    s2_is_unicode = 1;
  } else if ((s2_is_unicode & (!s1_is_unicode)) && PyString_CheckExact(s1)) {
    owned_ref = PyUnicode_FromObject(s1);
    if (unlikely(!owned_ref)) return -1;
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
    if (unlikely(__Pyx_PyUnicode_READY(s1) < 0) ||
        unlikely(__Pyx_PyUnicode_READY(s2) < 0))
      return -1;
    length = __Pyx_PyUnicode_GET_LENGTH(s1);
    if (length != __Pyx_PyUnicode_GET_LENGTH(s2)) {
      goto return_ne;
    }
#if RFC_USE_UNICODE_INTERNALS
    {
      Py_hash_t hash1, hash2;
#if RFC_PEP393_ENABLED
      hash1 = ((PyASCIIObject *)s1)->hash;
      hash2 = ((PyASCIIObject *)s2)->hash;
#else
      hash1 = ((PyUnicodeObject *)s1)->hash;
      hash2 = ((PyUnicodeObject *)s2)->hash;
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
    if (__Pyx_PyUnicode_READ(kind, data1, 0) !=
        __Pyx_PyUnicode_READ(kind, data2, 0)) {
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
    PyObject *py_result = PyObject_RichCompare(s1, s2, equals);
    if (!py_result) return -1;
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

/* GetModuleGlobalName */
static RFC_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
  PyObject *result;
#if !RFC_AVOID_BORROWED_REFS
  result = PyDict_GetItem(__pyx_d, name);
  if (likely(result)) {
    Py_INCREF(result);
  } else {
#else
  result = PyObject_GetItem(__pyx_d, name);
  if (!result) {
    PyErr_Clear();
#endif
    result = __Pyx_GetBuiltinName(name);
  }
  return result;
}

/* PyObjectCallMethO */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_CallMethO(PyObject *func,
                                                     PyObject *arg) {
  PyObject *self, *result;
  PyCFunction cfunc;
  cfunc = PyCFunction_GET_FUNCTION(func);
  self = PyCFunction_GET_SELF(func);
  if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object")))
    return NULL;
  result = cfunc(self, arg);
  Py_LeaveRecursiveCall();
  if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
    PyErr_SetString(PyExc_SystemError,
                    "NULL result without error in PyObject_Call");
  }
  return result;
}
#endif

/* PyObjectCallOneArg */
#if RFC_COMPILING_IN_CPYTHON
static PyObject *__Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
  PyObject *result;
  PyObject *args = PyTuple_New(1);
  if (unlikely(!args)) return NULL;
  Py_INCREF(arg);
  PyTuple_SET_ITEM(args, 0, arg);
  result = __Pyx_PyObject_Call(func, args, NULL);
  Py_DECREF(args);
  return result;
}
static RFC_INLINE PyObject *__Pyx_PyObject_CallOneArg(PyObject *func,
                                                      PyObject *arg) {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(func)) {
    return __Pyx_PyFunction_FastCall(func, &arg, 1);
  }
#endif
  if (likely(PyCFunction_Check(func))) {
    if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
      return __Pyx_PyObject_CallMethO(func, arg);
#if RFC_FAST_PYCCALL
    } else if (PyCFunction_GET_FLAGS(func) & METH_FASTCALL) {
      return __Pyx_PyCFunction_FastCall(func, &arg, 1);
#endif
    }
  }
  return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static RFC_INLINE PyObject *__Pyx_PyObject_CallOneArg(PyObject *func,
                                                      PyObject *arg) {
  PyObject *result;
  PyObject *args = PyTuple_Pack(1, arg);
  if (unlikely(!args)) return NULL;
  result = __Pyx_PyObject_Call(func, args, NULL);
  Py_DECREF(args);
  return result;
}
#endif

/* PyObjectCallNoArg */
#if RFC_COMPILING_IN_CPYTHON
static RFC_INLINE PyObject *__Pyx_PyObject_CallNoArg(PyObject *func) {
#if RFC_FAST_PYCALL
  if (PyFunction_Check(func)) {
    return __Pyx_PyFunction_FastCall(func, NULL, 0);
  }
#endif
#ifdef __Pyx_CyFunction_USED
  if (likely(PyCFunction_Check(func) ||
             PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
  if (likely(PyCFunction_Check(func))) {
#endif
    if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
      return __Pyx_PyObject_CallMethO(func, NULL);
    }
  }
  return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

/* PyIntBinop */
#if !RFC_COMPILING_IN_PYPY
static PyObject *__Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2,
                                     RFC_UNUSED long intval,
                                     RFC_UNUSED int inplace) {
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(op1))) {
    const long b = intval;
    long x;
    long a = PyInt_AS_LONG(op1);
    x = (long)((unsigned long)a + b);
    if (likely((x ^ a) >= 0 || (x ^ b) >= 0)) return PyInt_FromLong(x);
    return PyLong_Type.tp_as_number->nb_add(op1, op2);
  }
#endif
#if RFC_USE_PYLONG_INTERNALS
  if (likely(PyLong_CheckExact(op1))) {
    const long b = intval;
    long a, x;
#ifdef HAVE_LONG_LONG
    const PY_LONG_LONG llb = intval;
    PY_LONG_LONG lla, llx;
#endif
    const digit *digits = ((PyLongObject *)op1)->ob_digit;
    const Py_ssize_t size = Py_SIZE(op1);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
      a = likely(size) ? digits[0] : 0;
      if (size == -1) a = -a;
    } else {
      switch (size) {
        case -2:
          if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
            a = -(long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
            lla = -(PY_LONG_LONG)(
                ((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        case 2:
          if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
            a = (long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
            lla = (PY_LONG_LONG)(
                ((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        case -3:
          if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
            a = -(long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                           (unsigned long)digits[1])
                          << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
            lla = -(PY_LONG_LONG)(
                ((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) |
                   (unsigned PY_LONG_LONG)digits[1])
                  << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        case 3:
          if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
            a = (long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                          (unsigned long)digits[1])
                         << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
            lla = (PY_LONG_LONG)(
                ((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) |
                   (unsigned PY_LONG_LONG)digits[1])
                  << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        case -4:
          if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
            a = -(long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                             (unsigned long)digits[2])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[1])
                          << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
            lla = -(PY_LONG_LONG)(
                ((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) |
                     (unsigned PY_LONG_LONG)digits[2])
                    << PyLong_SHIFT) |
                   (unsigned PY_LONG_LONG)digits[1])
                  << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        case 4:
          if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
            a = (long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                            (unsigned long)digits[2])
                           << PyLong_SHIFT) |
                          (unsigned long)digits[1])
                         << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
#ifdef HAVE_LONG_LONG
          } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
            lla = (PY_LONG_LONG)(
                ((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) |
                     (unsigned PY_LONG_LONG)digits[2])
                    << PyLong_SHIFT) |
                   (unsigned PY_LONG_LONG)digits[1])
                  << PyLong_SHIFT) |
                 (unsigned PY_LONG_LONG)digits[0]));
            goto long_long;
#endif
          }
        default:
          return PyLong_Type.tp_as_number->nb_add(op1, op2);
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
    PyFPE_START_PROTECT("add", return NULL) result = ((double)a) + (double)b;
    PyFPE_END_PROTECT(result) return PyFloat_FromDouble(result);
  }
  return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

/* SliceObject */
static RFC_INLINE PyObject *__Pyx_PyObject_GetSlice(
    PyObject *obj, Py_ssize_t cstart, Py_ssize_t cstop, PyObject **_py_start,
    PyObject **_py_stop, PyObject **_py_slice, int has_cstart, int has_cstop,
    RFC_UNUSED int wraparound) {
#if RFC_USE_TYPE_SLOTS
  PyMappingMethods *mp;
#if PY_MAJOR_VERSION < 3
  PySequenceMethods *ms = Py_TYPE(obj)->tp_as_sequence;
  if (likely(ms && ms->sq_slice)) {
    if (!has_cstart) {
      if (_py_start && (*_py_start != Py_None)) {
        cstart = __Pyx_PyIndex_AsSsize_t(*_py_start);
        if ((cstart == (Py_ssize_t)-1) && PyErr_Occurred()) goto bad;
      } else
        cstart = 0;
    }
    if (!has_cstop) {
      if (_py_stop && (*_py_stop != Py_None)) {
        cstop = __Pyx_PyIndex_AsSsize_t(*_py_stop);
        if ((cstop == (Py_ssize_t)-1) && PyErr_Occurred()) goto bad;
      } else
        cstop = PY_SSIZE_T_MAX;
    }
    if (wraparound && unlikely((cstart < 0) | (cstop < 0)) &&
        likely(ms->sq_length)) {
      Py_ssize_t l = ms->sq_length(obj);
      if (likely(l >= 0)) {
        if (cstop < 0) {
          cstop += l;
          if (cstop < 0) cstop = 0;
        }
        if (cstart < 0) {
          cstart += l;
          if (cstart < 0) cstart = 0;
        }
      } else {
        if (!PyErr_ExceptionMatches(PyExc_OverflowError)) goto bad;
        PyErr_Clear();
      }
    }
    return ms->sq_slice(obj, cstart, cstop);
  }
#endif
  mp = Py_TYPE(obj)->tp_as_mapping;
  if (likely(mp && mp->mp_subscript))
#endif
  {
    PyObject *result;
    PyObject *py_slice, *py_start, *py_stop;
    if (_py_slice) {
      py_slice = *_py_slice;
    } else {
      PyObject *owned_start = NULL;
      PyObject *owned_stop = NULL;
      if (_py_start) {
        py_start = *_py_start;
      } else {
        if (has_cstart) {
          owned_start = py_start = PyInt_FromSsize_t(cstart);
          if (unlikely(!py_start)) goto bad;
        } else
          py_start = Py_None;
      }
      if (_py_stop) {
        py_stop = *_py_stop;
      } else {
        if (has_cstop) {
          owned_stop = py_stop = PyInt_FromSsize_t(cstop);
          if (unlikely(!py_stop)) {
            Py_XDECREF(owned_start);
            goto bad;
          }
        } else
          py_stop = Py_None;
      }
      py_slice = PySlice_New(py_start, py_stop, Py_None);
      Py_XDECREF(owned_start);
      Py_XDECREF(owned_stop);
      if (unlikely(!py_slice)) goto bad;
    }
#if RFC_USE_TYPE_SLOTS
    result = mp->mp_subscript(obj, py_slice);
#else
    result = PyObject_GetItem(obj, py_slice);
#endif
    if (!_py_slice) {
      Py_DECREF(py_slice);
    }
    return result;
  }
  PyErr_Format(PyExc_TypeError, "'%.200s' object is unsliceable",
               Py_TYPE(obj)->tp_name);
bad:
  return NULL;
}

/* PyErrFetchRestore */
#if RFC_FAST_THREAD_STATE
static RFC_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate,
                                               PyObject *type, PyObject *value,
                                               PyObject *tb) {
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
static RFC_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate,
                                             PyObject **type, PyObject **value,
                                             PyObject **tb) {
  *type = tstate->curexc_type;
  *value = tstate->curexc_value;
  *tb = tstate->curexc_traceback;
  tstate->curexc_type = 0;
  tstate->curexc_value = 0;
  tstate->curexc_traceback = 0;
}
#endif

/* RaiseException */
#if PY_MAJOR_VERSION < 3
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        RFC_UNUSED PyObject *cause) {
  __Pyx_PyThreadState_declare Py_XINCREF(type);
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
#if RFC_COMPILING_IN_PYPY
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
    type = (PyObject *)Py_TYPE(type);
    Py_INCREF(type);
    if (!PyType_IsSubtype((PyTypeObject *)type,
                          (PyTypeObject *)PyExc_BaseException)) {
      PyErr_SetString(
          PyExc_TypeError,
          "raise: exception class must be a subclass of BaseException");
      goto raise_error;
    }
  }
  __Pyx_PyThreadState_assign __Pyx_ErrRestore(type, value, tb);
  return;
raise_error:
  Py_XDECREF(value);
  Py_XDECREF(type);
  Py_XDECREF(tb);
  return;
}
#else
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        PyObject *cause) {
  PyObject *owned_instance = NULL;
  if (tb == Py_None) {
    tb = 0;
  } else if (tb && !PyTraceBack_Check(tb)) {
    PyErr_SetString(PyExc_TypeError,
                    "raise: arg 3 must be a traceback or None");
    goto bad;
  }
  if (value == Py_None) value = 0;
  if (PyExceptionInstance_Check(type)) {
    if (value) {
      PyErr_SetString(PyExc_TypeError,
                      "instance exception may not have a separate value");
      goto bad;
    }
    value = type;
    type = (PyObject *)Py_TYPE(value);
  } else if (PyExceptionClass_Check(type)) {
    PyObject *instance_class = NULL;
    if (value && PyExceptionInstance_Check(value)) {
      instance_class = (PyObject *)Py_TYPE(value);
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
      if (!args) goto bad;
      owned_instance = PyObject_Call(type, args, NULL);
      Py_DECREF(args);
      if (!owned_instance) goto bad;
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
    PyErr_SetString(
        PyExc_TypeError,
        "raise: exception class must be a subclass of BaseException");
    goto bad;
  }
#if PY_VERSION_HEX >= 0x03030000
  if (cause) {
#else
  if (cause && cause != Py_None) {
#endif
    PyObject *fixed_cause;
    if (cause == Py_None) {
      fixed_cause = NULL;
    } else if (PyExceptionClass_Check(cause)) {
      fixed_cause = PyObject_CallObject(cause, NULL);
      if (fixed_cause == NULL) goto bad;
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
#if RFC_COMPILING_IN_PYPY
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyErr_Fetch(&tmp_type, &tmp_value, &tmp_tb);
    Py_INCREF(tb);
    PyErr_Restore(tmp_type, tmp_value, tb);
    Py_XDECREF(tmp_tb);
#else
    PyThreadState *tstate = PyThreadState_GET();
    PyObject *tmp_tb = tstate->curexc_traceback;
    if (tb != tmp_tb) {
      Py_INCREF(tb);
      tstate->curexc_traceback = tb;
      Py_XDECREF(tmp_tb);
    }
#endif
  }
bad:
  Py_XDECREF(owned_instance);
  return;
}
#endif

/* SaveResetException */
#if RFC_FAST_THREAD_STATE
static RFC_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate,
                                            PyObject **type, PyObject **value,
                                            PyObject **tb) {
  *type = tstate->exc_type;
  *value = tstate->exc_value;
  *tb = tstate->exc_traceback;
  Py_XINCREF(*type);
  Py_XINCREF(*value);
  Py_XINCREF(*tb);
}
static RFC_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate,
                                             PyObject *type, PyObject *value,
                                             PyObject *tb) {
  PyObject *tmp_type, *tmp_value, *tmp_tb;
  tmp_type = tstate->exc_type;
  tmp_value = tstate->exc_value;
  tmp_tb = tstate->exc_traceback;
  tstate->exc_type = type;
  tstate->exc_value = value;
  tstate->exc_traceback = tb;
  Py_XDECREF(tmp_type);
  Py_XDECREF(tmp_value);
  Py_XDECREF(tmp_tb);
}
#endif

/* GetException */
#if RFC_FAST_THREAD_STATE
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type,
                               PyObject **value, PyObject **tb) {
#else
static int __Pyx_GetException(PyObject **type, PyObject **value,
                              PyObject **tb) {
#endif
  PyObject *local_type, *local_value, *local_tb;
#if RFC_FAST_THREAD_STATE
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
#if RFC_FAST_THREAD_STATE
  if (unlikely(tstate->curexc_type))
#else
  if (unlikely(PyErr_Occurred()))
#endif
    goto bad;
#if PY_MAJOR_VERSION >= 3
  if (local_tb) {
    if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0)) goto bad;
  }
#endif
  Py_XINCREF(local_tb);
  Py_XINCREF(local_type);
  Py_XINCREF(local_value);
  *type = local_type;
  *value = local_value;
  *tb = local_tb;
#if RFC_FAST_THREAD_STATE
  tmp_type = tstate->exc_type;
  tmp_value = tstate->exc_value;
  tmp_tb = tstate->exc_traceback;
  tstate->exc_type = local_type;
  tstate->exc_value = local_value;
  tstate->exc_traceback = local_tb;
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

/* None */
static RFC_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname) {
  PyErr_Format(PyExc_UnboundLocalError,
               "local variable '%s' referenced before assignment", varname);
}

/* Import */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
  PyObject *empty_list = 0;
  PyObject *module = 0;
  PyObject *global_dict = 0;
  PyObject *empty_dict = 0;
  PyObject *list;
#if PY_VERSION_HEX < 0x03030000
  PyObject *py_import;
  py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
  if (!py_import) goto bad;
#endif
  if (from_list)
    list = from_list;
  else {
    empty_list = PyList_New(0);
    if (!empty_list) goto bad;
    list = empty_list;
  }
  global_dict = PyModule_GetDict(__pyx_m);
  if (!global_dict) goto bad;
  empty_dict = PyDict_New();
  if (!empty_dict) goto bad;
  {
#if PY_MAJOR_VERSION >= 3
    if (level == -1) {
      if (strchr(__Pyx_MODULE_NAME, '.')) {
#if PY_VERSION_HEX < 0x03030000
        PyObject *py_level = PyInt_FromLong(1);
        if (!py_level) goto bad;
        module = PyObject_CallFunctionObjArgs(py_import, name, global_dict,
                                              empty_dict, list, py_level, NULL);
        Py_DECREF(py_level);
#else
        module = PyImport_ImportModuleLevelObject(name, global_dict, empty_dict,
                                                  list, 1);
#endif
        if (!module) {
          if (!PyErr_ExceptionMatches(PyExc_ImportError)) goto bad;
          PyErr_Clear();
        }
      }
      level = 0;
    }
#endif
    if (!module) {
#if PY_VERSION_HEX < 0x03030000
      PyObject *py_level = PyInt_FromLong(level);
      if (!py_level) goto bad;
      module = PyObject_CallFunctionObjArgs(py_import, name, global_dict,
                                            empty_dict, list, py_level, NULL);
      Py_DECREF(py_level);
#else
      module = PyImport_ImportModuleLevelObject(name, global_dict, empty_dict,
                                                list, level);
#endif
    }
  }
bad:
#if PY_VERSION_HEX < 0x03030000
  Py_XDECREF(py_import);
#endif
  Py_XDECREF(empty_list);
  Py_XDECREF(empty_dict);
  return module;
}

/* ImportFrom */
static PyObject *__Pyx_ImportFrom(PyObject *module, PyObject *name) {
  PyObject *value = __Pyx_PyObject_GetAttrStr(module, name);
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

/* CalculateMetaclass */
static PyObject *__Pyx_CalculateMetaclass(PyTypeObject *metaclass,
                                          PyObject *bases) {
  Py_ssize_t i, nbases = PyTuple_GET_SIZE(bases);
  for (i = 0; i < nbases; i++) {
    PyTypeObject *tmptype;
    PyObject *tmp = PyTuple_GET_ITEM(bases, i);
    tmptype = Py_TYPE(tmp);
#if PY_MAJOR_VERSION < 3
    if (tmptype == &PyClass_Type) continue;
#endif
    if (!metaclass) {
      metaclass = tmptype;
      continue;
    }
    if (PyType_IsSubtype(metaclass, tmptype)) continue;
    if (PyType_IsSubtype(tmptype, metaclass)) {
      metaclass = tmptype;
      continue;
    }
    PyErr_SetString(PyExc_TypeError,
                    "metaclass conflict: "
                    "the metaclass of a derived class "
                    "must be a (non-strict) subclass "
                    "of the metaclasses of all its bases");
    return NULL;
  }
  if (!metaclass) {
#if PY_MAJOR_VERSION < 3
    metaclass = &PyClass_Type;
#else
    metaclass = &PyType_Type;
#endif
  }
  Py_INCREF((PyObject *)metaclass);
  return (PyObject *)metaclass;
}

/* FetchCommonType */
static PyTypeObject *__Pyx_FetchCommonType(PyTypeObject *type) {
  PyObject *fake_module;
  PyTypeObject *cached_type = NULL;
  fake_module = PyImport_AddModule((char *)"_RFC_1_0");
  if (!fake_module) return NULL;
  Py_INCREF(fake_module);
  cached_type =
      (PyTypeObject *)PyObject_GetAttrString(fake_module, type->tp_name);
  if (cached_type) {
    if (!PyType_Check((PyObject *)cached_type)) {
      PyErr_Format(PyExc_TypeError,
                   "Shared RFC type %.200s is not a type object",
                   type->tp_name);
      goto bad;
    }
    if (cached_type->tp_basicsize != type->tp_basicsize) {
      PyErr_Format(PyExc_TypeError,
                   "Shared RFC type %.200s has the wrong size, try recompiling",
                   type->tp_name);
      goto bad;
    }
  } else {
    if (!PyErr_ExceptionMatches(PyExc_AttributeError)) goto bad;
    PyErr_Clear();
    if (PyType_Ready(type) < 0) goto bad;
    if (PyObject_SetAttrString(fake_module, type->tp_name, (PyObject *)type) <
        0)
      goto bad;
    Py_INCREF(type);
    cached_type = type;
  }
done:
  Py_DECREF(fake_module);
  return cached_type;
bad:
  Py_XDECREF(cached_type);
  cached_type = NULL;
  goto done;
}

/* RFCFunction */
static PyObject *__Pyx_CyFunction_get_doc(__pyx_CyFunctionObject *op,
                                          RFC_UNUSED void *closure) {
  if (unlikely(op->func_doc == NULL)) {
    if (op->func.m_ml->ml_doc) {
#if PY_MAJOR_VERSION >= 3
      op->func_doc = PyUnicode_FromString(op->func.m_ml->ml_doc);
#else
      op->func_doc = PyString_FromString(op->func.m_ml->ml_doc);
#endif
      if (unlikely(op->func_doc == NULL)) return NULL;
    } else {
      Py_INCREF(Py_None);
      return Py_None;
    }
  }
  Py_INCREF(op->func_doc);
  return op->func_doc;
}
static int __Pyx_CyFunction_set_doc(__pyx_CyFunctionObject *op,
                                    PyObject *value) {
  PyObject *tmp = op->func_doc;
  if (value == NULL) {
    value = Py_None;
  }
  Py_INCREF(value);
  op->func_doc = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_name(__pyx_CyFunctionObject *op) {
  if (unlikely(op->func_name == NULL)) {
#if PY_MAJOR_VERSION >= 3
    op->func_name = PyUnicode_InternFromString(op->func.m_ml->ml_name);
#else
    op->func_name = PyString_InternFromString(op->func.m_ml->ml_name);
#endif
    if (unlikely(op->func_name == NULL)) return NULL;
  }
  Py_INCREF(op->func_name);
  return op->func_name;
}
static int __Pyx_CyFunction_set_name(__pyx_CyFunctionObject *op,
                                     PyObject *value) {
  PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
  if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
  if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
    PyErr_SetString(PyExc_TypeError, "__name__ must be set to a string object");
    return -1;
  }
  tmp = op->func_name;
  Py_INCREF(value);
  op->func_name = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_qualname(__pyx_CyFunctionObject *op) {
  Py_INCREF(op->func_qualname);
  return op->func_qualname;
}
static int __Pyx_CyFunction_set_qualname(__pyx_CyFunctionObject *op,
                                         PyObject *value) {
  PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
  if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
  if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
    PyErr_SetString(PyExc_TypeError,
                    "__qualname__ must be set to a string object");
    return -1;
  }
  tmp = op->func_qualname;
  Py_INCREF(value);
  op->func_qualname = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_self(__pyx_CyFunctionObject *m,
                                           RFC_UNUSED void *closure) {
  PyObject *self;
  self = m->func_closure;
  if (self == NULL) self = Py_None;
  Py_INCREF(self);
  return self;
}
static PyObject *__Pyx_CyFunction_get_dict(__pyx_CyFunctionObject *op) {
  if (unlikely(op->func_dict == NULL)) {
    op->func_dict = PyDict_New();
    if (unlikely(op->func_dict == NULL)) return NULL;
  }
  Py_INCREF(op->func_dict);
  return op->func_dict;
}
static int __Pyx_CyFunction_set_dict(__pyx_CyFunctionObject *op,
                                     PyObject *value) {
  PyObject *tmp;
  if (unlikely(value == NULL)) {
    PyErr_SetString(PyExc_TypeError,
                    "function's dictionary may not be deleted");
    return -1;
  }
  if (unlikely(!PyDict_Check(value))) {
    PyErr_SetString(PyExc_TypeError,
                    "setting function's dictionary to a non-dict");
    return -1;
  }
  tmp = op->func_dict;
  Py_INCREF(value);
  op->func_dict = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_globals(__pyx_CyFunctionObject *op) {
  Py_INCREF(op->func_globals);
  return op->func_globals;
}
static PyObject *__Pyx_CyFunction_get_closure(
    RFC_UNUSED __pyx_CyFunctionObject *op) {
  Py_INCREF(Py_None);
  return Py_None;
}
static PyObject *__Pyx_CyFunction_get_code(__pyx_CyFunctionObject *op) {
  PyObject *result = (op->func_code) ? op->func_code : Py_None;
  Py_INCREF(result);
  return result;
}
static int __Pyx_CyFunction_init_defaults(__pyx_CyFunctionObject *op) {
  int result = 0;
  PyObject *res = op->defaults_getter((PyObject *)op);
  if (unlikely(!res)) return -1;
#if RFC_ASSUME_SAFE_MACROS && !RFC_AVOID_BORROWED_REFS
  op->defaults_tuple = PyTuple_GET_ITEM(res, 0);
  Py_INCREF(op->defaults_tuple);
  op->defaults_kwdict = PyTuple_GET_ITEM(res, 1);
  Py_INCREF(op->defaults_kwdict);
#else
  op->defaults_tuple = PySequence_ITEM(res, 0);
  if (unlikely(!op->defaults_tuple))
    result = -1;
  else {
    op->defaults_kwdict = PySequence_ITEM(res, 1);
    if (unlikely(!op->defaults_kwdict)) result = -1;
  }
#endif
  Py_DECREF(res);
  return result;
}
static int __Pyx_CyFunction_set_defaults(__pyx_CyFunctionObject *op,
                                         PyObject *value) {
  PyObject *tmp;
  if (!value) {
    value = Py_None;
  } else if (value != Py_None && !PyTuple_Check(value)) {
    PyErr_SetString(PyExc_TypeError,
                    "__defaults__ must be set to a tuple object");
    return -1;
  }
  Py_INCREF(value);
  tmp = op->defaults_tuple;
  op->defaults_tuple = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_defaults(__pyx_CyFunctionObject *op) {
  PyObject *result = op->defaults_tuple;
  if (unlikely(!result)) {
    if (op->defaults_getter) {
      if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
      result = op->defaults_tuple;
    } else {
      result = Py_None;
    }
  }
  Py_INCREF(result);
  return result;
}
static int __Pyx_CyFunction_set_kwdefaults(__pyx_CyFunctionObject *op,
                                           PyObject *value) {
  PyObject *tmp;
  if (!value) {
    value = Py_None;
  } else if (value != Py_None && !PyDict_Check(value)) {
    PyErr_SetString(PyExc_TypeError,
                    "__kwdefaults__ must be set to a dict object");
    return -1;
  }
  Py_INCREF(value);
  tmp = op->defaults_kwdict;
  op->defaults_kwdict = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_kwdefaults(__pyx_CyFunctionObject *op) {
  PyObject *result = op->defaults_kwdict;
  if (unlikely(!result)) {
    if (op->defaults_getter) {
      if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
      result = op->defaults_kwdict;
    } else {
      result = Py_None;
    }
  }
  Py_INCREF(result);
  return result;
}
static int __Pyx_CyFunction_set_annotations(__pyx_CyFunctionObject *op,
                                            PyObject *value) {
  PyObject *tmp;
  if (!value || value == Py_None) {
    value = NULL;
  } else if (!PyDict_Check(value)) {
    PyErr_SetString(PyExc_TypeError,
                    "__annotations__ must be set to a dict object");
    return -1;
  }
  Py_XINCREF(value);
  tmp = op->func_annotations;
  op->func_annotations = value;
  Py_XDECREF(tmp);
  return 0;
}
static PyObject *__Pyx_CyFunction_get_annotations(__pyx_CyFunctionObject *op) {
  PyObject *result = op->func_annotations;
  if (unlikely(!result)) {
    result = PyDict_New();
    if (unlikely(!result)) return NULL;
    op->func_annotations = result;
  }
  Py_INCREF(result);
  return result;
}
static PyGetSetDef __pyx_CyFunction_getsets[] = {
    {(char *)"func_doc", (getter)__Pyx_CyFunction_get_doc,
     (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *)"__doc__", (getter)__Pyx_CyFunction_get_doc,
     (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *)"func_name", (getter)__Pyx_CyFunction_get_name,
     (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *)"__name__", (getter)__Pyx_CyFunction_get_name,
     (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *)"__qualname__", (getter)__Pyx_CyFunction_get_qualname,
     (setter)__Pyx_CyFunction_set_qualname, 0, 0},
    {(char *)"__self__", (getter)__Pyx_CyFunction_get_self, 0, 0, 0},
    {(char *)"func_dict", (getter)__Pyx_CyFunction_get_dict,
     (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *)"__dict__", (getter)__Pyx_CyFunction_get_dict,
     (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *)"func_globals", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *)"__globals__", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *)"func_closure", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *)"__closure__", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *)"func_code", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *)"__code__", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *)"func_defaults", (getter)__Pyx_CyFunction_get_defaults,
     (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *)"__defaults__", (getter)__Pyx_CyFunction_get_defaults,
     (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *)"__kwdefaults__", (getter)__Pyx_CyFunction_get_kwdefaults,
     (setter)__Pyx_CyFunction_set_kwdefaults, 0, 0},
    {(char *)"__annotations__", (getter)__Pyx_CyFunction_get_annotations,
     (setter)__Pyx_CyFunction_set_annotations, 0, 0},
    {0, 0, 0, 0, 0}};
static PyMemberDef __pyx_CyFunction_members[] = {
    {(char *)"__module__", T_OBJECT,
     offsetof(__pyx_CyFunctionObject, func.m_module), PY_WRITE_RESTRICTED, 0},
    {0, 0, 0, 0, 0}};
static PyObject *__Pyx_CyFunction_reduce(__pyx_CyFunctionObject *m,
                                         RFC_UNUSED PyObject *args) {
#if PY_MAJOR_VERSION >= 3
  return PyUnicode_FromString(m->func.m_ml->ml_name);
#else
  return PyString_FromString(m->func.m_ml->ml_name);
#endif
}
static PyMethodDef __pyx_CyFunction_methods[] = {
    {"__reduce__", (PyCFunction)__Pyx_CyFunction_reduce, METH_VARARGS, 0},
    {0, 0, 0, 0}};
#if PY_VERSION_HEX < 0x030500A0
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func_weakreflist)
#else
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func.m_weakreflist)
#endif
static PyObject *__Pyx_CyFunction_New(PyTypeObject *type, PyMethodDef *ml,
                                      int flags, PyObject *qualname,
                                      PyObject *closure, PyObject *module,
                                      PyObject *globals, PyObject *code) {
  __pyx_CyFunctionObject *op = PyObject_GC_New(__pyx_CyFunctionObject, type);
  if (op == NULL) return NULL;
  op->flags = flags;
  __Pyx_CyFunction_weakreflist(op) = NULL;
  op->func.m_ml = ml;
  op->func.m_self = (PyObject *)op;
  Py_XINCREF(closure);
  op->func_closure = closure;
  Py_XINCREF(module);
  op->func.m_module = module;
  op->func_dict = NULL;
  op->func_name = NULL;
  Py_INCREF(qualname);
  op->func_qualname = qualname;
  op->func_doc = NULL;
  op->func_classobj = NULL;
  op->func_globals = globals;
  Py_INCREF(op->func_globals);
  Py_XINCREF(code);
  op->func_code = code;
  op->defaults_pyobjects = 0;
  op->defaults = NULL;
  op->defaults_tuple = NULL;
  op->defaults_kwdict = NULL;
  op->defaults_getter = NULL;
  op->func_annotations = NULL;
  PyObject_GC_Track(op);
  return (PyObject *)op;
}
static int __Pyx_CyFunction_clear(__pyx_CyFunctionObject *m) {
  Py_CLEAR(m->func_closure);
  Py_CLEAR(m->func.m_module);
  Py_CLEAR(m->func_dict);
  Py_CLEAR(m->func_name);
  Py_CLEAR(m->func_qualname);
  Py_CLEAR(m->func_doc);
  Py_CLEAR(m->func_globals);
  Py_CLEAR(m->func_code);
  Py_CLEAR(m->func_classobj);
  Py_CLEAR(m->defaults_tuple);
  Py_CLEAR(m->defaults_kwdict);
  Py_CLEAR(m->func_annotations);
  if (m->defaults) {
    PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
    int i;
    for (i = 0; i < m->defaults_pyobjects; i++) Py_XDECREF(pydefaults[i]);
    PyObject_Free(m->defaults);
    m->defaults = NULL;
  }
  return 0;
}
static void __Pyx_CyFunction_dealloc(__pyx_CyFunctionObject *m) {
  PyObject_GC_UnTrack(m);
  if (__Pyx_CyFunction_weakreflist(m) != NULL)
    PyObject_ClearWeakRefs((PyObject *)m);
  __Pyx_CyFunction_clear(m);
  PyObject_GC_Del(m);
}
static int __Pyx_CyFunction_traverse(__pyx_CyFunctionObject *m, visitproc visit,
                                     void *arg) {
  Py_VISIT(m->func_closure);
  Py_VISIT(m->func.m_module);
  Py_VISIT(m->func_dict);
  Py_VISIT(m->func_name);
  Py_VISIT(m->func_qualname);
  Py_VISIT(m->func_doc);
  Py_VISIT(m->func_globals);
  Py_VISIT(m->func_code);
  Py_VISIT(m->func_classobj);
  Py_VISIT(m->defaults_tuple);
  Py_VISIT(m->defaults_kwdict);
  if (m->defaults) {
    PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
    int i;
    for (i = 0; i < m->defaults_pyobjects; i++) Py_VISIT(pydefaults[i]);
  }
  return 0;
}
static PyObject *__Pyx_CyFunction_descr_get(PyObject *func, PyObject *obj,
                                            PyObject *type) {
  __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *)func;
  if (m->flags & __Pyx_CYFUNCTION_STATICMETHOD) {
    Py_INCREF(func);
    return func;
  }
  if (m->flags & __Pyx_CYFUNCTION_CLASSMETHOD) {
    if (type == NULL) type = (PyObject *)(Py_TYPE(obj));
    return __Pyx_PyMethod_New(func, type, (PyObject *)(Py_TYPE(type)));
  }
  if (obj == Py_None) obj = NULL;
  return __Pyx_PyMethod_New(func, obj, type);
}
static PyObject *__Pyx_CyFunction_repr(__pyx_CyFunctionObject *op) {
#if PY_MAJOR_VERSION >= 3
  return PyUnicode_FromFormat("<cyfunction %U at %p>", op->func_qualname,
                              (void *)op);
#else
  return PyString_FromFormat("<cyfunction %s at %p>",
                             PyString_AsString(op->func_qualname), (void *)op);
#endif
}
static PyObject *__Pyx_CyFunction_CallMethod(PyObject *func, PyObject *self,
                                             PyObject *arg, PyObject *kw) {
  PyCFunctionObject *f = (PyCFunctionObject *)func;
  PyCFunction meth = f->m_ml->ml_meth;
  Py_ssize_t size;
  switch (f->m_ml->ml_flags &
          (METH_VARARGS | METH_KEYWORDS | METH_NOARGS | METH_O)) {
    case METH_VARARGS:
      if (likely(kw == NULL || PyDict_Size(kw) == 0)) return (*meth)(self, arg);
      break;
    case METH_VARARGS | METH_KEYWORDS:
      return (*(PyCFunctionWithKeywords)meth)(self, arg, kw);
    case METH_NOARGS:
      if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
        size = PyTuple_GET_SIZE(arg);
        if (likely(size == 0)) return (*meth)(self, NULL);
        PyErr_Format(PyExc_TypeError,
                     "%.200s() takes no arguments (%" RFC_FORMAT_SSIZE_T
                     "d given)",
                     f->m_ml->ml_name, size);
        return NULL;
      }
      break;
    case METH_O:
      if (likely(kw == NULL || PyDict_Size(kw) == 0)) {
        size = PyTuple_GET_SIZE(arg);
        if (likely(size == 1)) {
          PyObject *result, *arg0 = PySequence_ITEM(arg, 0);
          if (unlikely(!arg0)) return NULL;
          result = (*meth)(self, arg0);
          Py_DECREF(arg0);
          return result;
        }
        PyErr_Format(PyExc_TypeError,
                     "%.200s() takes exactly one argument (%" RFC_FORMAT_SSIZE_T
                     "d given)",
                     f->m_ml->ml_name, size);
        return NULL;
      }
      break;
    default:
      PyErr_SetString(PyExc_SystemError,
                      "Bad call flags in "
                      "__Pyx_CyFunction_Call. METH_OLDARGS is no "
                      "longer supported!");
      return NULL;
  }
  PyErr_Format(PyExc_TypeError, "%.200s() takes no keyword arguments",
               f->m_ml->ml_name);
  return NULL;
}
static RFC_INLINE PyObject *__Pyx_CyFunction_Call(PyObject *func, PyObject *arg,
                                                  PyObject *kw) {
  return __Pyx_CyFunction_CallMethod(func, ((PyCFunctionObject *)func)->m_self,
                                     arg, kw);
}
static PyObject *__Pyx_CyFunction_CallAsMethod(PyObject *func, PyObject *args,
                                               PyObject *kw) {
  PyObject *result;
  __pyx_CyFunctionObject *cyfunc = (__pyx_CyFunctionObject *)func;
  if ((cyfunc->flags & __Pyx_CYFUNCTION_CCLASS) &&
      !(cyfunc->flags & __Pyx_CYFUNCTION_STATICMETHOD)) {
    Py_ssize_t argc;
    PyObject *new_args;
    PyObject *self;
    argc = PyTuple_GET_SIZE(args);
    new_args = PyTuple_GetSlice(args, 1, argc);
    if (unlikely(!new_args)) return NULL;
    self = PyTuple_GetItem(args, 0);
    if (unlikely(!self)) {
      Py_DECREF(new_args);
      return NULL;
    }
    result = __Pyx_CyFunction_CallMethod(func, self, new_args, kw);
    Py_DECREF(new_args);
  } else {
    result = __Pyx_CyFunction_Call(func, args, kw);
  }
  return result;
}
static PyTypeObject __pyx_CyFunctionType_type = {
  PyVarObject_HEAD_INIT(0, 0) "RFC_function_or_method",
  sizeof(__pyx_CyFunctionObject),
  0,
  (destructor)__Pyx_CyFunction_dealloc,
  0,
  0,
  0,
#if PY_MAJOR_VERSION < 3
  0,
#else
  0,
#endif
  (reprfunc)__Pyx_CyFunction_repr,
  0,
  0,
  0,
  0,
  __Pyx_CyFunction_CallAsMethod,
  0,
  0,
  0,
  0,
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
  0,
  (traverseproc)__Pyx_CyFunction_traverse,
  (inquiry)__Pyx_CyFunction_clear,
  0,
#if PY_VERSION_HEX < 0x030500A0
  offsetof(__pyx_CyFunctionObject, func_weakreflist),
#else
  offsetof(PyCFunctionObject, m_weakreflist),
#endif
  0,
  0,
  __pyx_CyFunction_methods,
  __pyx_CyFunction_members,
  __pyx_CyFunction_getsets,
  0,
  0,
  __Pyx_CyFunction_descr_get,
  0,
  offsetof(__pyx_CyFunctionObject, func_dict),
  0,
  0,
  0,
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
};
static int __pyx_CyFunction_init(void) {
  __pyx_CyFunctionType = __Pyx_FetchCommonType(&__pyx_CyFunctionType_type);
  if (__pyx_CyFunctionType == NULL) {
    return -1;
  }
  return 0;
}
static RFC_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *func,
                                                      size_t size,
                                                      int pyobjects) {
  __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *)func;
  m->defaults = PyObject_Malloc(size);
  if (!m->defaults) return PyErr_NoMemory();
  memset(m->defaults, 0, size);
  m->defaults_pyobjects = pyobjects;
  return m->defaults;
}
static RFC_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *func,
                                                         PyObject *tuple) {
  __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *)func;
  m->defaults_tuple = tuple;
  Py_INCREF(tuple);
}
static RFC_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *func,
                                                          PyObject *dict) {
  __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *)func;
  m->defaults_kwdict = dict;
  Py_INCREF(dict);
}
static RFC_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *func,
                                                           PyObject *dict) {
  __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *)func;
  m->func_annotations = dict;
  Py_INCREF(dict);
}

/* Py3ClassCreate */
static PyObject *__Pyx_Py3MetaclassPrepare(PyObject *metaclass, PyObject *bases,
                                           PyObject *name, PyObject *qualname,
                                           PyObject *mkw, PyObject *modname,
                                           PyObject *doc) {
  PyObject *ns;
  if (metaclass) {
    PyObject *prep = __Pyx_PyObject_GetAttrStr(metaclass, __pyx_n_s_prepare);
    if (prep) {
      PyObject *pargs = PyTuple_Pack(2, name, bases);
      if (unlikely(!pargs)) {
        Py_DECREF(prep);
        return NULL;
      }
      ns = PyObject_Call(prep, pargs, mkw);
      Py_DECREF(prep);
      Py_DECREF(pargs);
    } else {
      if (unlikely(!PyErr_ExceptionMatches(PyExc_AttributeError))) return NULL;
      PyErr_Clear();
      ns = PyDict_New();
    }
  } else {
    ns = PyDict_New();
  }
  if (unlikely(!ns)) return NULL;
  if (unlikely(PyObject_SetItem(ns, __pyx_n_s_module, modname) < 0)) goto bad;
  if (unlikely(PyObject_SetItem(ns, __pyx_n_s_qualname, qualname) < 0))
    goto bad;
  if (unlikely(doc && PyObject_SetItem(ns, __pyx_n_s_doc, doc) < 0)) goto bad;
  return ns;
bad:
  Py_DECREF(ns);
  return NULL;
}
static PyObject *__Pyx_Py3ClassCreate(PyObject *metaclass, PyObject *name,
                                      PyObject *bases, PyObject *dict,
                                      PyObject *mkw, int calculate_metaclass,
                                      int allow_py2_metaclass) {
  PyObject *result, *margs;
  PyObject *owned_metaclass = NULL;
  if (allow_py2_metaclass) {
    owned_metaclass = PyObject_GetItem(dict, __pyx_n_s_metaclass);
    if (owned_metaclass) {
      metaclass = owned_metaclass;
    } else if (likely(PyErr_ExceptionMatches(PyExc_KeyError))) {
      PyErr_Clear();
    } else {
      return NULL;
    }
  }
  if (calculate_metaclass && (!metaclass || PyType_Check(metaclass))) {
    metaclass = __Pyx_CalculateMetaclass((PyTypeObject *)metaclass, bases);
    Py_XDECREF(owned_metaclass);
    if (unlikely(!metaclass)) return NULL;
    owned_metaclass = metaclass;
  }
  margs = PyTuple_Pack(3, name, bases, dict);
  if (unlikely(!margs)) {
    result = NULL;
  } else {
    result = PyObject_Call(metaclass, margs, mkw);
    Py_DECREF(margs);
  }
  Py_XDECREF(owned_metaclass);
  return result;
}

/* PyIntBinop */
#if !RFC_COMPILING_IN_PYPY
static PyObject *__Pyx_PyInt_EqObjC(PyObject *op1, PyObject *op2,
                                    RFC_UNUSED long intval,
                                    RFC_UNUSED int inplace) {
  if (op1 == op2) {
    Py_RETURN_TRUE;
  }
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(op1))) {
    const long b = intval;
    long a = PyInt_AS_LONG(op1);
    if (a == b) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;
    }
  }
#endif
#if RFC_USE_PYLONG_INTERNALS
  if (likely(PyLong_CheckExact(op1))) {
    const long b = intval;
    long a;
    const digit *digits = ((PyLongObject *)op1)->ob_digit;
    const Py_ssize_t size = Py_SIZE(op1);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
      a = likely(size) ? digits[0] : 0;
      if (size == -1) a = -a;
    } else {
      switch (size) {
        case -2:
          if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
            a = -(long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
          }
        case 2:
          if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
            a = (long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
          }
        case -3:
          if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
            a = -(long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                           (unsigned long)digits[1])
                          << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
          }
        case 3:
          if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
            a = (long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                          (unsigned long)digits[1])
                         << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
          }
        case -4:
          if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
            a = -(long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                             (unsigned long)digits[2])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[1])
                          << PyLong_SHIFT) |
                         (unsigned long)digits[0]));
            break;
          }
        case 4:
          if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
            a = (long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                            (unsigned long)digits[2])
                           << PyLong_SHIFT) |
                          (unsigned long)digits[1])
                         << PyLong_SHIFT) |
                        (unsigned long)digits[0]));
            break;
          }
#if PyLong_SHIFT < 30 && PyLong_SHIFT != 15
        default:
          return PyLong_Type.tp_richcompare(op1, op2, Py_EQ);
#else
        default:
          Py_RETURN_FALSE;
#endif
      }
    }
    if (a == b) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;
    }
  }
#endif
  if (PyFloat_CheckExact(op1)) {
    const long b = intval;
    double a = PyFloat_AS_DOUBLE(op1);
    if ((double)a == (double)b) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;
    }
  }
  return PyObject_RichCompare(op1, op2, Py_EQ);
}
#endif

/* CLineInTraceback */
static int __Pyx_CLineForTraceback(int c_line) {
#ifdef RFC_CLINE_IN_TRACEBACK
  return ((RFC_CLINE_IN_TRACEBACK)) ? c_line : 0;
#else
  PyObject *use_cline;
#if RFC_COMPILING_IN_CPYTHON
  PyObject **RFC_runtime_dict = _PyObject_GetDictPtr(__pyx_RFC_runtime);
  if (likely(RFC_runtime_dict)) {
    use_cline = PyDict_GetItem(*RFC_runtime_dict, __pyx_n_s_cline_in_traceback);
  } else
#endif
  {
    PyObject *ptype, *pvalue, *ptraceback;
    PyObject *use_cline_obj;
    PyErr_Fetch(&ptype, &pvalue, &ptraceback);
    use_cline_obj = __Pyx_PyObject_GetAttrStr(__pyx_RFC_runtime,
                                              __pyx_n_s_cline_in_traceback);
    if (use_cline_obj) {
      use_cline = PyObject_Not(use_cline_obj) ? Py_False : Py_True;
      Py_DECREF(use_cline_obj);
    } else {
      use_cline = NULL;
    }
    PyErr_Restore(ptype, pvalue, ptraceback);
  }
  if (!use_cline) {
    c_line = 0;
    PyObject_SetAttr(__pyx_RFC_runtime, __pyx_n_s_cline_in_traceback, Py_False);
  } else if (PyObject_Not(use_cline) != 0) {
    c_line = 0;
  }
  return c_line;
#endif
}

/* CodeObjectCache */
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry *entries,
                                     int count, int code_line) {
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
  PyCodeObject *code_object;
  int pos;
  if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
    return NULL;
  }
  pos = __pyx_bisect_code_objects(__pyx_code_cache.entries,
                                  __pyx_code_cache.count, code_line);
  if (unlikely(pos >= __pyx_code_cache.count) ||
      unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
    return NULL;
  }
  code_object = __pyx_code_cache.entries[pos].code_object;
  Py_INCREF(code_object);
  return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject *code_object) {
  int pos, i;
  __Pyx_CodeObjectCacheEntry *entries = __pyx_code_cache.entries;
  if (unlikely(!code_line)) {
    return;
  }
  if (unlikely(!entries)) {
    entries = (__Pyx_CodeObjectCacheEntry *)PyMem_Malloc(
        64 * sizeof(__Pyx_CodeObjectCacheEntry));
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
  pos = __pyx_bisect_code_objects(__pyx_code_cache.entries,
                                  __pyx_code_cache.count, code_line);
  if ((pos < __pyx_code_cache.count) &&
      unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
    PyCodeObject *tmp = entries[pos].code_object;
    entries[pos].code_object = code_object;
    Py_DECREF(tmp);
    return;
  }
  if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
    int new_max = __pyx_code_cache.max_count + 64;
    entries = (__Pyx_CodeObjectCacheEntry *)PyMem_Realloc(
        __pyx_code_cache.entries,
        (size_t)new_max * sizeof(__Pyx_CodeObjectCacheEntry));
    if (unlikely(!entries)) {
      return;
    }
    __pyx_code_cache.entries = entries;
    __pyx_code_cache.max_count = new_max;
  }
  for (i = __pyx_code_cache.count; i > pos; i--) {
    entries[i] = entries[i - 1];
  }
  entries[pos].code_line = code_line;
  entries[pos].code_object = code_object;
  __pyx_code_cache.count++;
  Py_INCREF(code_object);
}

/* AddTraceback */
#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject *__Pyx_CreateCodeObjectForTraceback(const char *funcname,
                                                        int c_line, int py_line,
                                                        const char *filename) {
  PyCodeObject *py_code = 0;
  PyObject *py_srcfile = 0;
  PyObject *py_funcname = 0;
#if PY_MAJOR_VERSION < 3
  py_srcfile = PyString_FromString(filename);
#else
  py_srcfile = PyUnicode_FromString(filename);
#endif
  if (!py_srcfile) goto bad;
  if (c_line) {
#if PY_MAJOR_VERSION < 3
    py_funcname =
        PyString_FromFormat("%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
#else
    py_funcname =
        PyUnicode_FromFormat("%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
#endif
  } else {
#if PY_MAJOR_VERSION < 3
    py_funcname = PyString_FromString(funcname);
#else
    py_funcname = PyUnicode_FromString(funcname);
#endif
  }
  if (!py_funcname) goto bad;
  py_code =
      __Pyx_PyCode_New(0, 0, 0, 0, 0, __pyx_empty_bytes, /*PyObject *code,*/
                       __pyx_empty_tuple,                /*PyObject *consts,*/
                       __pyx_empty_tuple,                /*PyObject *names,*/
                       __pyx_empty_tuple,                /*PyObject *varnames,*/
                       __pyx_empty_tuple,                /*PyObject *freevars,*/
                       __pyx_empty_tuple,                /*PyObject *cellvars,*/
                       py_srcfile,                       /*PyObject *filename,*/
                       py_funcname,                      /*PyObject *name,*/
                       py_line, __pyx_empty_bytes        /*PyObject *lnotab*/
      );
  Py_DECREF(py_srcfile);
  Py_DECREF(py_funcname);
  return py_code;
bad:
  Py_XDECREF(py_srcfile);
  Py_XDECREF(py_funcname);
  return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line, int py_line,
                               const char *filename) {
  PyCodeObject *py_code = 0;
  PyFrameObject *py_frame = 0;
  if (c_line) {
    c_line = __Pyx_CLineForTraceback(c_line);
  }
  py_code = __pyx_find_code_object(c_line ? -c_line : py_line);
  if (!py_code) {
    py_code =
        __Pyx_CreateCodeObjectForTraceback(funcname, c_line, py_line, filename);
    if (!py_code) goto bad;
    __pyx_insert_code_object(c_line ? -c_line : py_line, py_code);
  }
  py_frame = PyFrame_New(PyThreadState_GET(), /*PyThreadState *tstate,*/
                         py_code,             /*PyCodeObject *code,*/
                         __pyx_d,             /*PyObject *globals,*/
                         0                    /*PyObject *locals*/
  );
  if (!py_frame) goto bad;
  __Pyx_PyFrame_SetLineNumber(py_frame, py_line);
  PyTraceBack_Here(py_frame);
bad:
  Py_XDECREF(py_code);
  Py_XDECREF(py_frame);
}

/* None */
#ifdef __FreeBSD__
#include <floatingpoint.h>
#endif
#if PY_MAJOR_VERSION < 3
int main(int argc, char **argv) {
#elif defined(WIN32) || defined(MS_WINDOWS)
int wmain(int argc, wchar_t **argv) {
#else
static int __Pyx_main(int argc, wchar_t **argv) {
#endif
  /* 754 requires that FP exceptions run in "no stop" mode by default,
   * and until C vendors implement C99's ways to control FP exceptions,
   * Python requires non-stop mode.  Alas, some platforms enable FP
   * exceptions by default.  Here we disable them.
   */
#ifdef __FreeBSD__
  fp_except_t m;
  m = fpgetmask();
  fpsetmask(m & ~FP_X_OFL);
#endif
  if (argc && argv) Py_SetProgramName(argv[0]);
  Py_Initialize();
  if (argc && argv) PySys_SetArgv(argc, argv);
  {
    PyObject *m = NULL;
    __pyx_module_is_main_rfc = 1;
#if PY_MAJOR_VERSION < 3
    initrfc();
#else
    m = PyInit_rfc();
#endif
    if (PyErr_Occurred()) {
      PyErr_Print();
#if PY_MAJOR_VERSION < 3
      if (Py_FlushLine()) PyErr_Clear();
#endif
      return 1;
    }
    Py_XDECREF(m);
  }
  Py_Finalize();
  return 0;
}
#if PY_MAJOR_VERSION >= 3 && !defined(WIN32) && !defined(MS_WINDOWS)
#include <locale.h>
static wchar_t *__Pyx_char2wchar(char *arg) {
  wchar_t *res;
#ifdef HAVE_BROKEN_MBSTOWCS
  /* Some platforms have a broken implementation of
   * mbstowcs which does not count the characters that
   * would result from conversion.  Use an upper bound.
   */
  size_t argsize = strlen(arg);
#else
  size_t argsize = mbstowcs(NULL, arg, 0);
#endif
  size_t count;
  unsigned char *in;
  wchar_t *out;
#ifdef HAVE_MBRTOWC
  mbstate_t mbs;
#endif
  if (argsize != (size_t)-1) {
    res = (wchar_t *)malloc((argsize + 1) * sizeof(wchar_t));
    if (!res) goto oom;
    count = mbstowcs(res, arg, argsize + 1);
    if (count != (size_t)-1) {
      wchar_t *tmp;
      /* Only use the result if it contains no
         surrogate characters. */
      for (tmp = res; *tmp != 0 && (*tmp < 0xd800 || *tmp > 0xdfff); tmp++)
        ;
      if (*tmp == 0) return res;
    }
    free(res);
  }
#ifdef HAVE_MBRTOWC
  /* Overallocate; as multi-byte characters are in the argument, the
     actual output could use less memory. */
  argsize = strlen(arg) + 1;
  res = (wchar_t *)malloc(argsize * sizeof(wchar_t));
  if (!res) goto oom;
  in = (unsigned char *)arg;
  out = res;
  memset(&mbs, 0, sizeof mbs);
  while (argsize) {
    size_t converted = mbrtowc(out, (char *)in, argsize, &mbs);
    if (converted == 0) break;
    if (converted == (size_t)-2) {
      /* Incomplete character. This should never happen,
         since we provide everything that we have -
         unless there is a bug in the C library, or I
         misunderstood how mbrtowc works. */
      fprintf(stderr, "unexpected mbrtowc result -2\\n");
      free(res);
      return NULL;
    }
    if (converted == (size_t)-1) {
      /* Conversion error. Escape as UTF-8b, and start over
         in the initial shift state. */
      *out++ = 0xdc00 + *in++;
      argsize--;
      memset(&mbs, 0, sizeof mbs);
      continue;
    }
    if (*out >= 0xd800 && *out <= 0xdfff) {
      /* Surrogate character.  Escape the original
         byte sequence with surrogateescape. */
      argsize -= converted;
      while (converted--) *out++ = 0xdc00 + *in++;
      continue;
    }
    in += converted;
    argsize -= converted;
    out++;
  }
#else
  /* Cannot use C locale for escaping; manually escape as if charset
     is ASCII (i.e. escape all bytes > 128. This will still roundtrip
     correctly in the locale's charset, which must be an ASCII superset. */
  res = (wchar_t *)malloc((strlen(arg) + 1) * sizeof(wchar_t));
  if (!res) goto oom;
  in = (unsigned char *)arg;
  out = res;
  while (*in)
    if (*in < 128)
      *out++ = *in++;
    else
      *out++ = 0xdc00 + *in++;
  *out = 0;
#endif
  return res;
oom:
  fprintf(stderr, "out of memory\\n");
  return NULL;
}
int main(int argc, char **argv) {
  if (!argc) {
    return __Pyx_main(0, NULL);
  } else {
    int i, res;
    wchar_t **argv_copy = (wchar_t **)malloc(sizeof(wchar_t *) * argc);
    wchar_t **argv_copy2 = (wchar_t **)malloc(sizeof(wchar_t *) * argc);
    char *oldloc = strdup(setlocale(LC_ALL, NULL));
    if (!argv_copy || !argv_copy2 || !oldloc) {
      fprintf(stderr, "out of memory\\n");
      free(argv_copy);
      free(argv_copy2);
      free(oldloc);
      return 1;
    }
    res = 0;
    setlocale(LC_ALL, "");
    for (i = 0; i < argc; i++) {
      argv_copy2[i] = argv_copy[i] = __Pyx_char2wchar(argv[i]);
      if (!argv_copy[i]) res = 1;
    }
    setlocale(LC_ALL, oldloc);
    free(oldloc);
    if (res == 0) res = __Pyx_main(argc, argv_copy);
    for (i = 0; i < argc; i++) {
      free(argv_copy2[i]);
    }
    free(argv_copy);
    free(argv_copy2);
    return res;
  }
}
#endif

/* CIntToPy */
static RFC_INLINE PyObject *__Pyx_PyInt_From_long(long value) {
  const long neg_one = (long)-1, const_zero = (long)0;
  const int is_unsigned = neg_one > const_zero;
  if (is_unsigned) {
    if (sizeof(long) < sizeof(long)) {
      return PyInt_FromLong((long)value);
    } else if (sizeof(long) <= sizeof(unsigned long)) {
      return PyLong_FromUnsignedLong((unsigned long)value);
#ifdef HAVE_LONG_LONG
    } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
      return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG)value);
#endif
    }
  } else {
    if (sizeof(long) <= sizeof(long)) {
      return PyInt_FromLong((long)value);
#ifdef HAVE_LONG_LONG
    } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
      return PyLong_FromLongLong((PY_LONG_LONG)value);
#endif
    }
  }
  {
    int one = 1;
    int little = (int)*(unsigned char *)&one;
    unsigned char *bytes = (unsigned char *)&value;
    return _PyLong_FromByteArray(bytes, sizeof(long), little, !is_unsigned);
  }
}

/* CIntFromPyVerify */
#define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value) \
  __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value) \
  __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc) \
  {                                                                       \
    func_type value = func_value;                                         \
    if (sizeof(target_type) < sizeof(func_type)) {                        \
      if (unlikely(value != (func_type)(target_type)value)) {             \
        func_type zero = 0;                                               \
        if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))  \
          return (target_type)-1;                                         \
        if (is_unsigned && unlikely(value < zero))                        \
          goto raise_neg_overflow;                                        \
        else                                                              \
          goto raise_overflow;                                            \
      }                                                                   \
    }                                                                     \
    return (target_type)value;                                            \
  }

/* CIntFromPy */
static RFC_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
  const long neg_one = (long)-1, const_zero = (long)0;
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
      return (long)val;
    }
  } else
#endif
      if (likely(PyLong_Check(x))) {
    if (is_unsigned) {
#if RFC_USE_PYLONG_INTERNALS
      const digit *digits = ((PyLongObject *)x)->ob_digit;
      switch (Py_SIZE(x)) {
        case 0:
          return (long)0;
        case 1:
          __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
        case 2:
          if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((unsigned long)digits[1]) << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
              return (long)(((((long)digits[1]) << PyLong_SHIFT) |
                             (long)digits[0]));
            }
          }
          break;
        case 3:
          if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
              return (long)((
                  (((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1])
                   << PyLong_SHIFT) |
                  (long)digits[0]));
            }
          }
          break;
        case 4:
          if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                        (unsigned long)digits[2])
                       << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
              return (long)((
                  (((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2])
                     << PyLong_SHIFT) |
                    (long)digits[1])
                   << PyLong_SHIFT) |
                  (long)digits[0]));
            }
          }
          break;
      }
#endif
#if RFC_COMPILING_IN_CPYTHON
      if (unlikely(Py_SIZE(x) < 0)) {
        goto raise_neg_overflow;
      }
#else
      {
        int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
        if (unlikely(result < 0)) return (long)-1;
        if (unlikely(result == 1)) goto raise_neg_overflow;
      }
#endif
      if (sizeof(long) <= sizeof(unsigned long)) {
        __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long,
                                    PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
      } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
        __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG,
                                    PyLong_AsUnsignedLongLong(x))
#endif
      }
    } else {
#if RFC_USE_PYLONG_INTERNALS
      const digit *digits = ((PyLongObject *)x)->ob_digit;
      switch (Py_SIZE(x)) {
        case 0:
          return (long)0;
        case -1:
          __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit)(-(sdigit)digits[0]))
        case 1:
          __PYX_VERIFY_RETURN_INT(long, digit, +digits[0])
        case -2:
          if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, long,
                  -(long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
              return (long)(((long)-1) * (((((long)digits[1]) << PyLong_SHIFT) |
                                           (long)digits[0])));
            }
          }
          break;
        case 2:
          if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((unsigned long)digits[1]) << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
              return (long)((
                  ((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
            }
          }
          break;
        case -3:
          if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, long,
                  -(long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                             (unsigned long)digits[1])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
              return (long)(((long)-1) *
                            (((((((long)digits[2]) << PyLong_SHIFT) |
                                (long)digits[1])
                               << PyLong_SHIFT) |
                              (long)digits[0])));
            }
          }
          break;
        case 3:
          if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
              return (long)((
                  ((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1])
                    << PyLong_SHIFT) |
                   (long)digits[0])));
            }
          }
          break;
        case -4:
          if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, long,
                  -(long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                               (unsigned long)digits[2])
                              << PyLong_SHIFT) |
                             (unsigned long)digits[1])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
              return (long)(((long)-1) *
                            (((((((((long)digits[3]) << PyLong_SHIFT) |
                                  (long)digits[2])
                                 << PyLong_SHIFT) |
                                (long)digits[1])
                               << PyLong_SHIFT) |
                              (long)digits[0])));
            }
          }
          break;
        case 4:
          if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  long, unsigned long,
                  (((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                        (unsigned long)digits[2])
                       << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
              return (long)((
                  ((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2])
                      << PyLong_SHIFT) |
                     (long)digits[1])
                    << PyLong_SHIFT) |
                   (long)digits[0])));
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
#if RFC_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
      PyErr_SetString(PyExc_RuntimeError,
                      "_PyLong_AsByteArray() not available in PyPy, cannot "
                      "convert large numbers");
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
        int one = 1;
        int is_little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&val;
        int ret = _PyLong_AsByteArray((PyLongObject *)v, bytes, sizeof(val),
                                      is_little, !is_unsigned);
        Py_DECREF(v);
        if (likely(!ret)) return val;
      }
#endif
      return (long)-1;
    }
  } else {
    long val;
    PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
    if (!tmp) return (long)-1;
    val = __Pyx_PyInt_As_long(tmp);
    Py_DECREF(tmp);
    return val;
  }
raise_overflow:
  PyErr_SetString(PyExc_OverflowError, "value too large to convert to long");
  return (long)-1;
raise_neg_overflow:
  PyErr_SetString(PyExc_OverflowError, "can't convert negative value to long");
  return (long)-1;
}

/* CIntFromPy */
static RFC_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
  const int neg_one = (int)-1, const_zero = (int)0;
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
      return (int)val;
    }
  } else
#endif
      if (likely(PyLong_Check(x))) {
    if (is_unsigned) {
#if RFC_USE_PYLONG_INTERNALS
      const digit *digits = ((PyLongObject *)x)->ob_digit;
      switch (Py_SIZE(x)) {
        case 0:
          return (int)0;
        case 1:
          __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
        case 2:
          if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((unsigned long)digits[1]) << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
              return (
                  int)(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
            }
          }
          break;
        case 3:
          if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
              return (
                  int)(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1])
                         << PyLong_SHIFT) |
                        (int)digits[0]));
            }
          }
          break;
        case 4:
          if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                        (unsigned long)digits[2])
                       << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
              return (
                  int)(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2])
                           << PyLong_SHIFT) |
                          (int)digits[1])
                         << PyLong_SHIFT) |
                        (int)digits[0]));
            }
          }
          break;
      }
#endif
#if RFC_COMPILING_IN_CPYTHON
      if (unlikely(Py_SIZE(x) < 0)) {
        goto raise_neg_overflow;
      }
#else
      {
        int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
        if (unlikely(result < 0)) return (int)-1;
        if (unlikely(result == 1)) goto raise_neg_overflow;
      }
#endif
      if (sizeof(int) <= sizeof(unsigned long)) {
        __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long,
                                    PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
      } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
        __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG,
                                    PyLong_AsUnsignedLongLong(x))
#endif
      }
    } else {
#if RFC_USE_PYLONG_INTERNALS
      const digit *digits = ((PyLongObject *)x)->ob_digit;
      switch (Py_SIZE(x)) {
        case 0:
          return (int)0;
        case -1:
          __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit)(-(sdigit)digits[0]))
        case 1:
          __PYX_VERIFY_RETURN_INT(int, digit, +digits[0])
        case -2:
          if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, long,
                  -(long)(((((unsigned long)digits[1]) << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
              return (int)(((int)-1) * (((((int)digits[1]) << PyLong_SHIFT) |
                                         (int)digits[0])));
            }
          }
          break;
        case 2:
          if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((unsigned long)digits[1]) << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
              return (
                  int)((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
            }
          }
          break;
        case -3:
          if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, long,
                  -(long)(((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                             (unsigned long)digits[1])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
              return (
                  int)(((int)-1) *
                       (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1])
                          << PyLong_SHIFT) |
                         (int)digits[0])));
            }
          }
          break;
        case 3:
          if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((((unsigned long)digits[2]) << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
              return (
                  int)((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1])
                          << PyLong_SHIFT) |
                         (int)digits[0])));
            }
          }
          break;
        case -4:
          if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, long,
                  -(long)(((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                               (unsigned long)digits[2])
                              << PyLong_SHIFT) |
                             (unsigned long)digits[1])
                            << PyLong_SHIFT) |
                           (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
              return (int)(((int)-1) *
                           (((((((((int)digits[3]) << PyLong_SHIFT) |
                                 (int)digits[2])
                                << PyLong_SHIFT) |
                               (int)digits[1])
                              << PyLong_SHIFT) |
                             (int)digits[0])));
            }
          }
          break;
        case 4:
          if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
            if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
              __PYX_VERIFY_RETURN_INT(
                  int, unsigned long,
                  (((((((((unsigned long)digits[3]) << PyLong_SHIFT) |
                        (unsigned long)digits[2])
                       << PyLong_SHIFT) |
                      (unsigned long)digits[1])
                     << PyLong_SHIFT) |
                    (unsigned long)digits[0])))
            } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
              return (int)((
                  ((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2])
                      << PyLong_SHIFT) |
                     (int)digits[1])
                    << PyLong_SHIFT) |
                   (int)digits[0])));
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
#if RFC_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
      PyErr_SetString(PyExc_RuntimeError,
                      "_PyLong_AsByteArray() not available in PyPy, cannot "
                      "convert large numbers");
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
        int one = 1;
        int is_little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&val;
        int ret = _PyLong_AsByteArray((PyLongObject *)v, bytes, sizeof(val),
                                      is_little, !is_unsigned);
        Py_DECREF(v);
        if (likely(!ret)) return val;
      }
#endif
      return (int)-1;
    }
  } else {
    int val;
    PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
    if (!tmp) return (int)-1;
    val = __Pyx_PyInt_As_int(tmp);
    Py_DECREF(tmp);
    return val;
  }
raise_overflow:
  PyErr_SetString(PyExc_OverflowError, "value too large to convert to int");
  return (int)-1;
raise_neg_overflow:
  PyErr_SetString(PyExc_OverflowError, "can't convert negative value to int");
  return (int)-1;
}

/* CheckBinaryVersion */
static int __Pyx_check_binary_version(void) {
  char ctversion[4], rtversion[4];
  PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
  PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
  if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
    char message[200];
    PyOS_snprintf(message, sizeof(message),
                  "compiletime version %s of module '%.100s' "
                  "does not match runtime version %s",
                  ctversion, __Pyx_MODULE_NAME, rtversion);
    return PyErr_WarnEx(NULL, message, 1);
  }
  return 0;
}

/* InitStrings */
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
    if (!*t->p) return -1;
    if (PyObject_Hash(*t->p) == -1) PyErr_Clear();
    ++t;
  }
  return 0;
}

static RFC_INLINE PyObject *__Pyx_PyUnicode_FromString(const char *c_str) {
  return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static RFC_INLINE const char *__Pyx_PyObject_AsString(PyObject *o) {
  Py_ssize_t ignore;
  return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static RFC_INLINE const char *__Pyx_PyObject_AsStringAndSize(
    PyObject *o, Py_ssize_t *length) {
#if RFC_COMPILING_IN_CPYTHON && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || \
                                 __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
      __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
      PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
    char *defenc_c;
    PyObject *defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
    if (!defenc) return NULL;
    defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    {
      char *end = defenc_c + PyBytes_GET_SIZE(defenc);
      char *c;
      for (c = defenc_c; c < end; c++) {
        if ((unsigned char)(*c) >= 128) {
          PyUnicode_AsASCIIString(o);
          return NULL;
        }
      }
    }
#endif
    *length = PyBytes_GET_SIZE(defenc);
    return defenc_c;
#else
    if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
    if (PyUnicode_IS_ASCII(o)) {
      *length = PyUnicode_GET_LENGTH(o);
      return PyUnicode_AsUTF8(o);
    } else {
      PyUnicode_AsASCIIString(o);
      return NULL;
    }
#else
    return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
  } else
#endif
#if (!RFC_COMPILING_IN_PYPY) || \
    (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
      if (PyByteArray_Check(o)) {
    *length = PyByteArray_GET_SIZE(o);
    return PyByteArray_AS_STRING(o);
  } else
#endif
  {
    char *result;
    int r = PyBytes_AsStringAndSize(o, &result, length);
    if (unlikely(r < 0)) {
      return NULL;
    } else {
      return result;
    }
  }
}
static RFC_INLINE int __Pyx_PyObject_IsTrue(PyObject *x) {
  int is_true = x == Py_True;
  if (is_true | (x == Py_False) | (x == Py_None))
    return is_true;
  else
    return PyObject_IsTrue(x);
}
static RFC_INLINE PyObject *__Pyx_PyNumber_IntOrLong(PyObject *x) {
#if RFC_USE_TYPE_SLOTS
  PyNumberMethods *m;
#endif
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return __Pyx_NewRef(x);
#if RFC_USE_TYPE_SLOTS
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  } else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
#else
  res = PyNumber_Int(x);
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError, "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError, "an integer is required");
  }
  return res;
}
static RFC_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject *b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
      return PyInt_AS_LONG(b);
    else
      return PyInt_AsSsize_t(x);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
#if RFC_USE_PYLONG_INTERNALS
    const digit *digits = ((PyLongObject *)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
      ival = likely(size) ? digits[0] : 0;
      if (size == -1) ival = -ival;
      return ival;
    } else {
      switch (size) {
        case 2:
          if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
            return (Py_ssize_t)(
                ((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
          }
          break;
        case -2:
          if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
            return -(Py_ssize_t)(
                ((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
          }
          break;
        case 3:
          if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
            return (Py_ssize_t)(
                ((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1])
                  << PyLong_SHIFT) |
                 (size_t)digits[0]));
          }
          break;
        case -3:
          if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
            return -(Py_ssize_t)(
                ((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1])
                  << PyLong_SHIFT) |
                 (size_t)digits[0]));
          }
          break;
        case 4:
          if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
            return (Py_ssize_t)(
                ((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2])
                    << PyLong_SHIFT) |
                   (size_t)digits[1])
                  << PyLong_SHIFT) |
                 (size_t)digits[0]));
          }
          break;
        case -4:
          if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
            return -(Py_ssize_t)(
                ((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2])
                    << PyLong_SHIFT) |
                   (size_t)digits[1])
                  << PyLong_SHIFT) |
                 (size_t)digits[0]));
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
static RFC_INLINE PyObject *__Pyx_PyInt_FromSize_t(size_t ival) {
  return PyInt_FromSize_t(ival);
}

#endif /* Py_PYTHON_H */
