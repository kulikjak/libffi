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

static test_structure_x ABI_ATTR structx (void)
{
  test_structure_x s;
  for (int i = 0; i < NUM_ELEMS; i++)
        s.data[i] = (ELEM_TYPE)i+1;
  return s;
}

int main (void)
{
  ffi_cif cif;
  ffi_type tsx_type;
  ffi_type *tsx_type_elements[NUM_ELEMS+1];

  /* This is a hack to get a properly aligned result buffer */
  test_structure_x *tsx_result =
    (test_structure_x *) malloc (sizeof(test_structure_x));

  tsx_type.size = 0;
  tsx_type.alignment = 0;
  tsx_type.type = FFI_TYPE_STRUCT;
  tsx_type.elements = tsx_type_elements;

  for (int i = 0; i < NUM_ELEMS; i++) {
    tsx_type_elements[i] = &FFI_ELEM_TYPE;
  }
  tsx_type_elements[NUM_ELEMS] = NULL;

  /* Initialize the cif */
  CHECK(ffi_prep_cif(&cif, ABI_NUM, 0, &tsx_type, NULL) == FFI_OK);

  ffi_call(&cif, FFI_FN(structx), tsx_result, NULL);

  for (int i = 0; i < NUM_ELEMS; i++) {
    printf("%g\n", tsx_result->data[i]);
  }

  for (int i = 0; i < NUM_ELEMS; i++) {
    CHECK(tsx_result->data[i] == (ELEM_TYPE)i+1);
  }
  
  free (tsx_result);
  exit(0);
}
