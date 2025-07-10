#ifndef _DYNSTR_H
#define _DYNSTR_H
#define DYNSTR_IMPLEMENTATION

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define DYNSTR_ADD_CAPACITY 0
#define DYNSTR_SUB_CAPACITY 1
#define DYNSTR_ABSOLUTE_CAPACITY 2

#define DS_LENGTH ds->length // DS stands for dynamic string
#define DS_CAPACITY ds->capacity
#define DS_PTR ds->ptr
#define DS_ENDPTR (DS_PTR + DS_LENGTH)
#define DS_END *DS_ENDPTR
#define ALLOC_CHECK_NULL(ptr) if(!ptr) return errno;

typedef struct {
  char *ptr;
  size_t length;
  size_t capacity;
} DynStr;

int DynStr_init(DynStr *ds);
int DynStr_from(DynStr *ds, char *str);
int DynStr_with_capacity(DynStr *ds, size_t capacity);
int DynStr_change_capacity(DynStr *ds, size_t delta, int mode);
int DynStr_push_str(DynStr *ds, char *str);
int DynStr_push_char(DynStr *ds, char ch);
int DynStr_push_array(DynStr *ds, char *arr, size_t len);
int DynStr_push_dynstr(DynStr *ds, DynStr *ads);
void DynStr_free(DynStr *ds);

#ifdef DYNSTR_IMPLEMENTATION

int DynStr_init(DynStr *ds) {
  DS_PTR = (char*)malloc(1);
  ALLOC_CHECK_NULL(DS_PTR);
  DS_CAPACITY = 0;
  DS_LENGTH = 0;
  *DS_PTR = '\0';
  return EXIT_SUCCESS;
}

void DynStr_free(DynStr *ds) {
  free(DS_PTR);
  DS_PTR = NULL;
  DS_LENGTH = 0;
  DS_CAPACITY = 0;
}

int DynStr_with_capacity(DynStr *ds, size_t capacity) {
  DS_PTR = (char*)malloc(capacity + 1);
  ALLOC_CHECK_NULL(DS_PTR);
  DS_CAPACITY = capacity;
  DS_LENGTH = 0;
  *DS_PTR = '\0';
  return EXIT_SUCCESS;
}

int DynStr_from(DynStr *ds, char *str) {
  int ret = DynStr_with_capacity(ds, strlen(str));
  if(ret) return ret;
  ret = DynStr_push_str(ds, str);
  if(ret) return ret;
  return 0;
}

int DynStr_change_capacity(DynStr *ds, size_t delta, int mode) {
  switch(mode) {
    case DYNSTR_ADD_CAPACITY: {
      DS_CAPACITY += delta;
      break;
    }

    case DYNSTR_SUB_CAPACITY: {
      DS_CAPACITY -= delta;
      if(DS_LENGTH > DS_CAPACITY) DS_LENGTH = DS_CAPACITY;
      break;
    }

    case DYNSTR_ABSOLUTE_CAPACITY: {
      DS_CAPACITY = delta;
      if(DS_LENGTH > DS_CAPACITY) DS_LENGTH = DS_CAPACITY;
      break;
    }

    default: {
      return -1;
    }
  }
  DS_PTR = (char*)realloc(DS_PTR, DS_CAPACITY + 1);
  ALLOC_CHECK_NULL(DS_PTR);
  return 0;
}


int DynStr_push_str(DynStr *ds, char *str) {
  size_t len = strlen(str);
  if((DS_CAPACITY - DS_LENGTH) < len) {
    int ret = DynStr_change_capacity(ds, len, DYNSTR_ADD_CAPACITY);
    if(ret) return ret;
  }
  memcpy(DS_ENDPTR, str, len);
  DS_LENGTH += len;
  DS_END = '\0';
  return 0;
}

int DynStr_push_char(DynStr *ds, char ch) {
  if(DS_CAPACITY == DS_LENGTH) {
    int ret = DynStr_change_capacity(ds, 1, DYNSTR_ADD_CAPACITY);
    if(ret) return ret;
  }
  DS_END = ch;
  DS_LENGTH++;
  DS_END = '\0';
  return 0;
}

int DynStr_push_array(DynStr *ds, char *arr, size_t len) {
  if((DS_CAPACITY - DS_LENGTH) < len) {
    int ret = DynStr_change_capacity(ds, len, DYNSTR_ADD_CAPACITY);
    if(ret) return ret;
  }
  memcpy(DS_ENDPTR, arr, len);
  DS_LENGTH += len;
  DS_END = '\0';
  return 0;
}

int DynStr_push_dynstr(DynStr *ds, DynStr *ads) {
  return DynStr_push_str(ds, ads->ptr);
}

#endif

#endif
