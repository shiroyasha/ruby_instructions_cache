require "rake/extensiontask"

gemspec = Gem::Specification.load('ruby_instructions_cache.gemspec')

Rake::ExtensionTask.new do |ext|
  ext.name = "ruby_instructions_cache"
  ext.ext_dir = "ext/ruby_instructions_cache"
  ext.lib_dir = "lib/ruby_instructions_cache"
  ext.gem_spec = gemspec
end

task(:default => :compile)
