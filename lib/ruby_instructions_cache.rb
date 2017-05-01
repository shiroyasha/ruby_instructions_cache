require "ruby_instructions_cache/version"

module RubyInstructionsCache

  # require native functions
  require_relative "ruby_instructions_cache/ruby_instructions_cache"

  def self.setup!
    # This method is called when Ruby tries to load a file
    ::RubyVM::InstructionSequence.define_singleton_method(:load_iseq) do |path|
      ::RubyInstructionsCache.load_iseq(path)
    end
  end

end
