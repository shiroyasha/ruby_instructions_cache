#include <ruby.h>

#include <stdio.h>

/* ric is short for RubyInstructionsCache */

static VALUE mRIC;

/* forward declarations */
static VALUE ric_load_iseq(VALUE, VALUE);
static int ric_save_to_file(const char*, VALUE);

void Init_ruby_instructions_cache(void) {
  mRIC = rb_define_module("RubyInstructionsCache");

  rb_define_module_function(mRIC, "load_iseq", ric_load_iseq, 1);
}

static VALUE
ric_load_iseq(VALUE self, VALUE path) {
  static int file_no = 0;
  char cache_path[255];

  VALUE mRubyVM = rb_const_get(rb_cObject, rb_intern("RubyVM"));
  VALUE mIseq   = rb_const_get(mRubyVM, rb_intern("InstructionSequence"));
  VALUE iseq    = rb_funcall(mIseq, rb_intern("compile_file"), 1, path);

  VALUE binary = rb_funcall(iseq, rb_intern("to_binary"), 0);

  file_no++;


  sprintf(cache_path, ".ruby_binaries/f_%d", file_no);

  printf("Saving cache of %s to %s\n", RSTRING_PTR(path), cache_path);

  ric_save_to_file(cache_path, binary);

  return iseq;
}

static int
ric_save_to_file(const char* path, VALUE ruby_binary) {
  FILE *fd = fopen(path, "wb"); /* wb - write binary */

  const char* data = RSTRING_PTR(ruby_binary);
  int len          = RSTRING_LEN(ruby_binary);

  fwrite(data, len, 1, fd);
  fclose(fd);

  /* TODO: handle errors */
  return 0;
}
