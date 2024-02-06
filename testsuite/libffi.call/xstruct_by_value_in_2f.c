/* Area:	ffi_call
   Purpose:	Check structures passed by value.
   Limitations:	none.
   PR:		TBD
   Originator:	TBD  */

/* { dg-do run } */
#define NUM_ELEMS 2
#define ELEM_TYPE float
#define FFI_ELEM_TYPE ffi_type_float

#include "xstruct_by_value_in.inc"
