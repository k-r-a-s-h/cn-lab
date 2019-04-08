#boiler plate
set ns [new Simulator] 

set f [open out.tr w]
$ns trace-all $f
set nf [open out.nam w]
$ns namtrace-all $nf

$ns color 0 Green
$ns color 1 Blue

#creating nodes
for {set i 0} {$i < 7} {incr i} {
	set n($i) [$ns node]
	$n($i) color red
}
for {set i 7} {$i < 12} {incr i} {
	set n($i) [$ns node]
	$n($i) color green
}


for {set i 2} {$i < 7} {incr i} {
	$ns duplex-link $n($i) $n(0) 10Mb 20ms RED
	$ns duplex-link-op $n($i) $n(0) orient left
}
for {set i 7} {$i < 12} {incr i} {
	$ns duplex-link $n($i) $n(1) 10Mb 20ms RED
	$ns duplex-link-op $n($i) $n(1) orient right
}
$ns duplex-link $n(0) $n(1) 1.5Mb 40ms RED
$ns duplex-link-op $n(0) $n(1) orient down

set tcp0 [new Agent/TCP]
$ns attach-agent $n(8) $tcp0
set tcp1 [new Agent/TCP]
$ns attach-agent $n(8) $tcp1
set tcp2 [new Agent/TCP]
$ns attach-agent $n(8) $tcp2
set tcp3 [new Agent/TCP]
$ns attach-agent $n(8) $tcp3
set tcp4 [new Agent/TCP]
$ns attach-agent $n(8) $tcp4

$tcp0 set fid_ 0
$tcp1 set fid_ 1
$tcp0 set fid_ 0
$tcp1 set fid_ 1
$tcp0 set fid_ 0

set sink0 [new Agent/TCPSink]
set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]
set sink4 [new Agent/TCPSink]
$ns attach-agent $n(2) $sink0
$ns attach-agent $n(3) $sink1
$ns attach-agent $n(4) $sink2
$ns attach-agent $n(5) $sink3
$ns attach-agent $n(6) $sink4

$ns connect $tcp0 $sink0
$ns connect $tcp1 $sink1 
$ns connect $tcp2 $sink2 
$ns connect $tcp3 $sink3 
$ns connect $tcp4 $sink4

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp4

#boilerplate
proc finish {} {
	global ns f nf 
	$ns flush-trace 
	close $f
	close $nf
	exit
}
#rt model
#$ns rtmodel-at 2.0 down $n0 $n1
#$ns rtmodel-at 3.0 up $n0 $n1

$ns at 0.5 " $ftp0 start "
$ns at 10.0 " $ftp0 stop "
$ns at 0.5 " $ftp1 start "
$ns at 10.0 " $ftp1 stop "
$ns at 0.5 " $ftp2 start "
$ns at 10.0 " $ftp2 stop "
$ns at 0.5 " $ftp3 start "
$ns at 10.0 " $ftp3 stop "
$ns at 0.5 " $ftp4 start "
$ns at 10.0 " $ftp4 stop "

$ns at 10.0 " finish "
$ns run  

