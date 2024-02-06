/* Area:	ffi_call
   Purpose:	Check structures passed by value.
   Limitations:	none.
   PR:		TBD
   Originator:	TBD  */

#include "ffitest.h"
typedef struct
{
  ELEM_TYPE a;
#if NUM_ELEMS > 1
  ELEM_TYPE b;
#endif
#if NUM_ELEMS > 2
  ELEM_TYPE c;
#endif
#if NUM_ELEMS > 3
  ELEM_TYPE d;
#endif
#if NUM_ELEMS > 4
  ELEM_TYPE e;
#endif
#if NUM_ELEMS > 5
  ELEM_TYPE f;
#endif
#if NUM_ELEMS > 6
  ELEM_TYPE g;
#endif
#if NUM_ELEMS > 7
  ELEM_TYPE h;
#endif
#if NUM_ELEMS > 8
  ELEM_TYPE i;
#endif
} test_structure_y;

static test_structure_y ABI_ATTR structy (void)
{
  test_structure_y s;
  s.a = (ELEM_TYPE)1.0;
#if NUM_ELEMS > 1
  s.b = (ELEM_TYPE)2.0;
#endif
#if NUM_ELEMS > 2
  s.c = (ELEM_TYPE)3.0;
#endif
#if NUM_ELEMS > 3
  s.d = (ELEM_TYPE)4.0;
#endif
#if NUM_ELEMS > 4
  s.e = (ELEM_TYPE)5.0;
#endif
#if NUM_ELEMS > 5
  s.f = (ELEM_TYPE)6.0;
#endif
#if NUM_ELEMS > 6
  s.g = (ELEM_TYPE)7.0;
#endif
#if NUM_ELEMS > 7
  s.h = (ELEM_TYPE)8.0;
#endif
#if NUM_ELEMS > 8
  s.i = (ELEM_TYPE)9.0;
#endif
  return s;
}

int main (void)
{
  ffi_cif cif;
  ffi_type tsy_type;
  ffi_type *tsy_type_elements[NUM_ELEMS+1];

  /* This is a hack to get a properly aligned result buffer */
  test_structure_y *tsy_result =
    (test_structure_y *) malloc (sizeof(test_structure_y));

  tsy_type.size = 0;
  tsy_type.alignment = 0;
  tsy_type.type = FFI_TYPE_STRUCT;
  tsy_type.elements = tsy_type_elements;

  tsy_type_elements[0] = &FFI_ELEM_TYPE;
#if NUM_ELEMS > 1
  tsy_type_elements[1] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 2
  tsy_type_elements[2] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 3
  tsy_type_elements[3] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 4
  tsy_type_elements[4] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 5
  tsy_type_elements[5] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 6
  tsy_type_elements[6] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 7
  tsy_type_elements[7] = &FFI_ELEM_TYPE;
#endif
#if NUM_ELEMS > 8
  tsy_type_elements[8] = &FFI_ELEM_TYPE;
#endif
  tsy_type_elements[NUM_ELEMS] = NULL;

  /* Initialize the cif */
  CHECK(ffi_prep_cif(&cif, ABI_NUM, 0, &tsy_type, NULL) == FFI_OK);

  ffi_call(&cif, FFI_FN(structy), tsy_result, NULL);

  printf("%g\n", tsy_result->a);
#if NUM_ELEMS > 1
  printf("%g\n", tsy_result->b);
#endif
#if NUM_ELEMS > 2
  printf("%g\n", tsy_result->c);
#endif
#if NUM_ELEMS > 3
  printf("%g\n", tsy_result->d);
#endif
#if NUM_ELEMS > 4
  printf("%g\n", tsy_result->e);
#endif
#if NUM_ELEMS > 5
  printf("%g\n", tsy_result->f);
#endif
#if NUM_ELEMS > 6
  printf("%g\n", tsy_result->g);
#endif
#if NUM_ELEMS > 7
  printf("%g\n", tsy_result->h);
#endif
#if NUM_ELEMS > 8
  printf("%g\n", tsy_result->i);
#endif


  CHECK(tsy_result->a == (ELEM_TYPE)1.0);
#if NUM_ELEMS > 1
  CHECK(tsy_result->b == (ELEM_TYPE)2.0);
#endif
#if NUM_ELEMS > 2
  CHECK(tsy_result->c == (ELEM_TYPE)3.0);
#endif
#if NUM_ELEMS > 3
  CHECK(tsy_result->d == (ELEM_TYPE)4.0);
#endif
#if NUM_ELEMS > 4
  CHECK(tsy_result->e == (ELEM_TYPE)5.0);
#endif
#if NUM_ELEMS > 5
  CHECK(tsy_result->f == (ELEM_TYPE)6.0);
#endif
#if NUM_ELEMS > 6
  CHECK(tsy_result->g == (ELEM_TYPE)7.0);
#endif
#if NUM_ELEMS > 7
  CHECK(tsy_result->h == (ELEM_TYPE)8.0);
#endif
#if NUM_ELEMS > 8
  CHECK(tsy_result->i == (ELEM_TYPE)9.0);
#endif

  free (tsy_result);
  exit(0);
}
