/* Area:	ffi_call
   Purpose:	Check structures passed by value.
   Limitations:	none.
   PR:		TBD
   Originator:	TBD  */

#include "ffitest.h"
typedef struct
{
  ELEM_TYPE data[NUM_ELEMS];
} test_structure_x;

static ELEM_TYPE ABI_ATTR sumstructx (test_structure_x in)
{
  ELEM_TYPE sum = 0;
  for (int i = 0; i < NUM_ELEMS; i++)
    sum += in.data[i];
  return sum;
}

int main (void)
{
  ffi_cif cif;
  ffi_type *args[MAX_ARGS];
  void *values[MAX_ARGS];
  ELEM_TYPE checksum = 0;
  ELEM_TYPE retval;
  ffi_type tsx_type;
  ffi_type *tsx_type_elements[NUM_ELEMS+1];

  test_structure_x tsx_arg;

  tsx_type.size = 0;
  tsx_type.alignment = 0;
  tsx_type.type = FFI_TYPE_STRUCT;
  tsx_type.elements = tsx_type_elements;

  for (int i = 0; i < NUM_ELEMS; i++) {
    tsx_type_elements[i] = &FFI_ELEM_TYPE;
  }
  tsx_type_elements[NUM_ELEMS] = NULL;

  args[0] = &tsx_type;
  values[0] = &tsx_arg;

  /* Initialize the cif */
  CHECK(ffi_prep_cif(&cif, ABI_NUM, 1, &FFI_ELEM_TYPE, args) == FFI_OK);

  for (int i = 0; i < NUM_ELEMS; i++) {
    tsx_arg.data[i] = (ELEM_TYPE)i+1;
    checksum += (ELEM_TYPE)i+1;
  }

  ffi_call(&cif, FFI_FN(sumstructx), &retval, values);

  printf("%g\n", retval);

  CHECK(retval - checksum < 0.0001);

  exit(0);
}
