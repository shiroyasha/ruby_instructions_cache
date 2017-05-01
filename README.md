# Ruby Instructions Cache

Compiling Ruby files is not a trivial operation. Caching the compiled
instructions can improve the startup performance of your applications.

This project is only a toy project for benchmarking and trying out new ideas.

Based on:
- https://github.com/Shopify/bootsnap
- https://github.com/ko1/yomikomu

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'ruby_instructions_cache'
```

## Usage

Add the following line right after the `require "bundler/setup"` line in your
application:

``` ruby
require "bundler/setup"

require "ruby_instructions_cache"

RubyInstructionsCache.setup!
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then,
run `rake rspec` to run the tests. You can also run `bin/console` for an
interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`.
To release a new version, update the version number in `version.rb`, and then
run `bundle exec rake release`, which will create a git tag for the version,
push git commits and tags, and push the `.gem` file
to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/shiroyasha/ruby_instructions_cache. This project is intended
to be a safe, welcoming space for collaboration, and contributors are expected
to adhere to the [Contributor Covenant](contributor-covenant.org) code of
conduct.

## License

The gem is available as open source under the terms of the
[MIT License](http://opensource.org/licenses/MIT).
