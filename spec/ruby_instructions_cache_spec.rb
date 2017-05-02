require "spec_helper"

describe RubyInstructionsCache do
  it "has a version number" do
    expect(RubyInstructionsCache::VERSION).not_to be_nil
  end

  before(:all) do
    RubyInstructionsCache.setup!
  end

  it "does not break file loading" do
    load "./spec/a.rb"

    a = Animal.new("Tiger")
    puts a.speak
  end
end
