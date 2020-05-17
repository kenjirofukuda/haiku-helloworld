# coding: utf-8
# adhook link generator

source_dir = "src"
target_files = Dir.glob(["**/*.cpp", "**/*.h"], base: source_dir).sort
puts "# タブ幅 4の閲覧"
target_files.each do | f |
  url = "#{source_dir}/#{f}?ts=4"
  puts "* [#{f}](#{url})"
end
