#!/usr/bin/env ruby
#
require "serialport"

if ARGV.size < 1
	puts "$0 <serialport>"
	exit 1
end

port_str = ARGV[0]
baud_rate = 115200

sp = SerialPort.new(port_str, baud_rate, 8,1,SerialPort::NONE);

puts "--REQ"
sp.write("123456789012345")
puts "--RESP (CTRL-C to stop)"

while true do
   while (i = sp.gets.chomp) do      
      puts i
    end
end
 
sp.close      
