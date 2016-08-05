#/usr/bin/env ruby
# encoding: utf-8

basename = ARGV[0]
varBaseName = basename[0,1].downcase + basename[1..-1]

@digits = 0
def writeByte(byte)
	if byte.is_a? Integer then
		if byte > 255 then
			num = byte
			bytes = []
			while num > 0
				bytes.push num & 0xff
				num >>= 8
			end
			bytes.reverse_each {|item| writeByte item}
		elsif byte < 0 then
			num = byte
			bytes = []
			while num < -1
				bytes.push num & 0xff
				num >>= 8
			end
			bytes.reverse_each {|item| writeByte item}
		else
			if (@digits > 0) && (@digits % 16 == 0) then
				print "\n "
			elsif @digits % 16 == 8 then
				print " "
			end
			print " 0x#{byte.to_s(16).rjust(2, '0')},"
			@digits += 1
		end
	elsif byte.is_a? String then
		byte.each_codepoint {|cp| writeByte cp}
	elsif byte.is_a? Array then
		byte.each {|item| writeByte item}
	else
		raise TypeError, "argument must be an Integer, a String, or an Array of them"
	end
end

print "#include <stdlib.h>\n\nconst unsigned char #{varBaseName}_image[] = {\n "
@digits = 0
File.open("#{basename}.pbm", "rb") {|f|
	f.each_byte {|ch| writeByte ch}
}
print "\n};\n\n"


@digits = 0
mode = 0
print "const unsigned char #{varBaseName}_index[] = {\n "
File.open("#{basename}.pfi", "r") {|f|
	f.each_line {|line|
		line.chomp!
		if mode == 0 then
			if line == "F1" then
				writeByte "F4\n"
				mode = 1
			elsif line == "F4" then
				mode = 5
				break
			else
				raise "invalid format"
			end
		elsif mode < 3 then
			if line !~ /^#/ then
				writeByte "#{line}\n"
				mode += 1
			end
		else
			if (mode == 3) && (line !~ /^#/) then
				writeByte 0xff
				mode = 4
			end
			if mode == 4 then
				charDat = line.split
				char = charDat.shift
				if char.length == 1 then
					if char.ord <= 0xff then writeByte 0 end
					writeByte char
				else
					if char.to_i(16) < 256 then writeByte 0 end
					writeByte char.to_i(16)
				end
				writeByte charDat.length
				writeByte charDat.map {|item| item.to_i}
			end
		end
	}
}
if mode == 5 then
	File.open("#{basename}.pfi", "rb") {|f|
		f.each_byte {|ch| writeByte ch}
	}
end
print "\n};\n\n"
print "const size_t #{varBaseName}_image_size = sizeof #{varBaseName}_image;\n"
print "const size_t #{varBaseName}_index_size = sizeof #{varBaseName}_index;\n"
