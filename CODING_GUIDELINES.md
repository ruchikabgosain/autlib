-   Use capitals for macros and constants and prefix with "AUT".
    e.g. `AUT_STATE_T`, `AUT_FORCEINLINE`
-   Use camelcase prefixed with "aut" and suffixed with "_t" for struct, enums and   typedefs. 
    e.g. `autDescriptor_t`, `autState_t`
-   All functions should lower case, underscore separated and prefixed with
    "aut".
    e.g. `aut_read()`, `aut_get_descriptor()`
-   Functions operating on structs should include the struct name after "aut".
    e.g `aut_descriptor_get_initstate()` retrieves the initstate out of an `autDescriptor_t`
-   Accessor functions should return the member of the struct instead of writing to a pointer argument
    e.g use
    ```c
    autDescriptor_t aut_get_descriptor(aut_t *aut);
    ````
    instead of
    ```c
    void aut_get_descriptor(aut_t *lts, autDescriptor **d);
    ```
-   All non-accessor functions should return `autError_t`
    e.g 
    ```c
    autError_t aut_read();
    ```
    The only exception to this rule are the `destroy` functions. See below.
-   All defined structs should be accompanied by create and destroy methods
    e.g For a struct `autX_t` the following functions must be defined:
    ```c
    autError_t aut_x_create(autX_t **p, ...);
    void aut_x_destroy(autX_t **p);
    ```
-   A `destroy` function should always set its argument to point to `NULL`

-   In both function declarations and function definitions, the modifiers and return type should be in a line of their own, preceding the function name and arguments list.
    e.g use
    ```c
    static inline void 
    aut_do_something_important( aut_t *aut);
    ```
    instead of
    ```c
    static inline void aut_do_something_important( aut_t *aut);
    ```