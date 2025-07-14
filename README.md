# dynstr
Simple and 🚀BLAZINGLY🚀 fast library for working with dynamic strings in C.

# Tutorial
Dynstr provides 12 🚀BLAZINGLY🚀 fast functions for working with dynamic string.
A dynamic string is a regular C string allocated on the heap.

### DynStr_init
Just allocates empty dynamic string on the heap.
```C
DynStr ds = {0};
DynStr_init(&ds);
```
### DynStr_from
Creates dynamic string from regular C string.
```C
DynStr = {0};
DynStr_from(&ds, "dynstr");
```

### DynStr_with_capacity
Allocates n bytes of a dynamic string on the heap.
IMPORTANT NOTICE: bytes are not zeroed but `\0` placed at the beginning.
```C
DynStr ds = {0};
DynStr_with_capacity(&ds, 3);
```

### DynStr_change_capacity
Changes capacity of a dynamic string. There are 3 "modes" of changing capacity of the dynamic string.
```C
DynStr_change_capacity(&ds, 3, DYNSTR_ADD_CAPACITY); // adds 3 bytes
DynStr_change_capacity(&ds, 3, DYNSTR_SUB_CAPACITY); // subtracts 3 bytes
DynStr_change_capacity(&ds, 3, DYNSTR_ABSOLUTE_CAPACITY); // sets dynamic string capacity to 3 bytes
```

### DynStr_push_str
Pushes C string at the end of a dynamic string.
```C
DynStr_push_str(&ds, "dynstr");
```

### DynStr_push_char
Pushes char at the end of a dynamic string.
```C
DynStr_push_char(&ds, 'd');
```

### DynStr_push_array
Pushes array at the end of the dynamic string.
```C
char arr[] = {'d', 'y', 'n', 's', 't', 'r'};
DynStr_push_array(&ds, arr, 6);
```
### DynStr_push_dynstr
Pushes dynamic string at the end of a dynamic string.
```C
DynStr_push_dynstr(&ds1, &ds2); // ds2 pushed at the end of the ds1
```

### DynStr_raw_str()
Returns pointer to raw C string
```C
printf("%s", DynStr_raw_str(&ds));
```

### DynStr_length()
Returns length of a dynamic string

### DynStr_capacity()
Returns capacity of a dynamic string

### DynStr_free
Deallocates a string from the heap and sets its data pointer to NULL to avoid double-free and use-after-free vulnerabilities.
```C
DynStr_free(&ds);
```

ENTER THE TORBALLDs.
