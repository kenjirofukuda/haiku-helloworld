# 
includes = ENV["BEINCLUDES"].split(/;/)
puts "clang"
includes.each { | each |
  puts "-I"
  puts each
}
