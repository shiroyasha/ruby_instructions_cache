require "ruby_instructions_cache/version"
require "fileutils"

module RubyInstructionsCache

  # require native functions
  require_relative "ruby_instructions_cache/ruby_instructions_cache"

  def self.setup!(compiled_ruby_path = nil)
    compiled_ruby_path ||= File.join(Dir.pwd, ".ruby_binaries")

    log("Storing compiled binaries into #{compiled_ruby_path}.")

    FileUtils.mkdir_p(compiled_ruby_path)

    # This method is called when Ruby tries to load a file
    ::RubyVM::InstructionSequence.define_singleton_method(:load_iseq) do |path|
      ::RubyInstructionsCache.load_iseq(path)
    end
  end

  def self.log(message)
    puts "[RubyInstructionsCache] #{message}"
  end

end
