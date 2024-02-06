/* Area:	ffi_call
   Purpose:	Check structures.
   Limitations:	none.
   PR:		none.
   Originator:	From the original ffitest.c  */

/* { dg-do run } */
#include "ffitest.h"

typedef struct
{
  float d01;
  float d02;
  float d03;
} test_structure_1;

static test_structure_1 ABI_ATTR struct1(test_structure_1 ts)
{
  ts.d01 = 1.0;
  ts.d02 = 2.0;
  ts.d03 = 3.0;

  return ts;
}

int main (void)
{
  ffi_cif cif;
  ffi_type *args[MAX_ARGS];
  void *values[MAX_ARGS];
  ffi_type ts1_type;
  ffi_type *ts1_type_elements[4];

  test_structure_1 ts1_arg;

  /* This is a hack to get a properly aligned result buffer */
  test_structure_1 *ts1_result =
    (test_structure_1 *) malloc (sizeof(test_structure_1));

  ts1_type.size = 0;
  ts1_type.alignment = 0;
  ts1_type.type = FFI_TYPE_STRUCT;
  ts1_type.elements = ts1_type_elements;
  ts1_type_elements[0] = &ffi_type_float;
  ts1_type_elements[1] = &ffi_type_float;
  ts1_type_elements[2] = &ffi_type_float;
  ts1_type_elements[3] = NULL;

  args[0] = &ts1_type;
  values[0] = &ts1_arg;

  /* Initialize the cif */
  CHECK(ffi_prep_cif(&cif, ABI_NUM, 1,
		     &ts1_type, args) == FFI_OK);

  ts1_arg.d01 = 20.0;
  ts1_arg.d02 = 21.0;
  ts1_arg.d03 = 22.0;

  ffi_call(&cif, FFI_FN(struct1), ts1_result, values);

  CHECK(ts1_result->d01 == 1.0);
  CHECK(ts1_result->d02 == 2.0);
  CHECK(ts1_result->d03 == 3.0);

  /* This will fail if ffi_call isn't passing the struct by value. */
  CHECK(ts1_arg.d01 == 20.0);
  CHECK(ts1_arg.d02 == 21.0);
  CHECK(ts1_arg.d03 == 22.0);

  free (ts1_result);
  exit(0);
}
