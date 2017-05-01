require "mkmf"

$CFLAGS << " -O3 "
$CFLAGS << " -std=c99"

create_makefile("ruby_instructions_cache/ruby_instructions_cache")
