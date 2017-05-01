#include <ruby.h>

#include <stdio.h>

/* ric is short for RubyInstructionsCache */

static VALUE mRIC;

/* forward declarations */
static VALUE ric_load_iseq(VALUE);

void Init_ruby_instructions_cache(void) {
  mRIC = rb_define_module("RubyInstructionsCache");

  rb_define_module_function(mRIC, "load_iseq", ric_load_iseq, 1);
}

VALUE ric_load_iseq(VALUE path) {
  printf("Hello World\n");

  return Qnil;
}
