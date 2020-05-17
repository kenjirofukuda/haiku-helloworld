# coding: utf-8
# adhook link generator

repo = "https://github.com/kenjirofukuda/haiku-helloworld"
source_dir = "src"
target_files = Dir.glob(["**/*.cpp", "**/*.h"], base: source_dir).sort
puts "# タブ幅 4の閲覧"
target_files.each do | f |
  url = "#{repo}/blob/master/#{source_dir}/#{f}?ts=4"
  puts "* [#{f}](#{url} #{f})"
end
