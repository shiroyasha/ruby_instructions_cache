#include <ruby.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ric is short for RubyInstructionsCache */

static VALUE mRIC;

/* forward declarations */
static VALUE ric_load_iseq(VALUE, VALUE);
static int   ric_save_to_file(const char*, VALUE);
static VALUE ric_load_from_file(const char*);
static char* ric_cache_key(const char*);

void Init_ruby_instructions_cache(void) {
  mRIC = rb_define_module("RubyInstructionsCache");

  rb_define_module_function(mRIC, "load_iseq", ric_load_iseq, 1);
}

static VALUE
ric_load_iseq(VALUE self, VALUE path) {
  char cache_path[255];

  VALUE iseq    = NULL;
  VALUE binary  = NULL;
  VALUE mRubyVM = rb_const_get(rb_cObject, rb_intern("RubyVM"));
  VALUE mIseq   = rb_const_get(mRubyVM, rb_intern("InstructionSequence"));

  char* cache_key = ric_cache_key(RSTRING_PTR(path));

  sprintf(cache_path, ".ruby_binaries/%s", cache_key);

  if(access(cache_path, R_OK) == 0) {
    /* printf("[RIC] Loading %s from cache.\n", RSTRING_PTR(path)); */

    binary = ric_load_from_file(cache_path);
    iseq = rb_funcall(mIseq, rb_intern("load_from_binary"), 1, binary);
  } else {
    /* printf("[RIC] Compiling %s -> %s.\n", RSTRING_PTR(path), cache_path); */

    iseq = rb_funcall(mIseq, rb_intern("compile_file"), 1, path);
    binary = rb_funcall(iseq, rb_intern("to_binary"), 0);

    ric_save_to_file(cache_path, binary);
  }

  free(cache_key);
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

static VALUE
ric_load_from_file(const char* path) {
  VALUE ret = NULL;
  char *file_contents;
  long input_file_size;
  FILE *fd = fopen(path, "rb"); /* rb - read binary */

  fseek(fd, 0, SEEK_END);
  input_file_size = ftell(fd);
  rewind(fd);

  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, fd);
  fclose(fd);

  ret = rb_str_new_static(file_contents, input_file_size);

  /* free(file_contents); */
  return ret;
}

static char*
ric_cache_key(const char* file_path) {
  char* cache_key = strdup(file_path);

  for(int i=0; i < strlen(cache_key); i++) {
    if(cache_key[i] == '/') { cache_key[i] = '0'; }
  }

  return cache_key;
}
