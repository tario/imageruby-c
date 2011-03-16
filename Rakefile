require 'rubygems'
require 'rake'
require 'rake/testtask'
require 'rake/rdoctask'
require 'rake/gempackagetask'

spec = Gem::Specification.new do |s|
  s.name = 'imagecruby'
  s.version = '0.0.1'
  s.author = 'Dario Seminara'
  s.email = 'robertodarioseminara@gmail.com'
  s.platform = Gem::Platform::RUBY
  s.summary = 'C implementation of some of the ImageRuby methods'
  s.homepage = "http://github.com/tario/imagecruby"
  s.has_rdoc = true
  s.extra_rdoc_files = [ 'README' ]
  s.rdoc_options << '--main' << 'README'
  s.extensions = FileList["ext/**/extconf.rb"].to_a
  s.files = Dir.glob("{examples,lib,test}/**/*.rb") + Dir.glob("ext/**/*.c") + Dir.glob("ext/**/*.h") + Dir.glob("ext/**/extconf.rb") +
    [ 'LICENSE', 'AUTHORS', 'CHANGELOG', 'README', 'Rakefile', 'TODO' ]
end

desc 'Run tests'
task :default => [ :test ]

Rake::TestTask.new('test') do |t|
  t.libs << 'test'
  t.pattern = '{test}/**/test_*.rb'
  t.verbose = true
end

desc 'Generate RDoc'
Rake::RDocTask.new :rdoc do |rd|
  rd.rdoc_dir = 'doc'
  rd.rdoc_files.add 'lib', 'ext', 'README'
  rd.main = 'README'
end

desc 'Build Gem'
Rake::GemPackageTask.new spec do |pkg|
  pkg.need_tar = true
end

desc 'Clean up'
task :clean => [ :clobber_rdoc, :clobber_package ]

desc 'Clean up'
task :clobber => [ :clean ]