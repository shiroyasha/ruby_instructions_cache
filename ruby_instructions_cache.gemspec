# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'ruby_instructions_cache/version'

Gem::Specification.new do |spec|
  spec.name          = "ruby_instructions_cache"
  spec.version       = RubyInstructionsCache::VERSION
  spec.authors       = ["Igor Šarčević"]
  spec.email         = ["igor@renderedtext.com"]

  spec.summary       = %q{Cache compiled Ruby files}
  spec.description   = %q{Cache compiled Ruby files}
  spec.homepage      = "https://github.com/shiroyasha/ruby_instructions_cache"
  spec.license       = "MIT"

  spec.extensions    = ["ext/ruby_instructions_cache/extconf.rb"]

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.10"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rspec"
end
