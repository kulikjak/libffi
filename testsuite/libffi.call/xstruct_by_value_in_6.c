/* Area:	ffi_call
   Purpose:	Check structures passed by value.
   Limitations:	none.
   PR:		TBD
   Originator:	TBD  */

/* { dg-do run } */
#define NUM_ELEMS 6
#define ELEM_TYPE double
#define FFI_ELEM_TYPE ffi_type_double

#include "xstruct_by_value_in.inc"
