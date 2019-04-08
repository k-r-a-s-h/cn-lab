#boiler plate
set ns [new Simulator] 

set f [open lab1.tr w]
$ns trace-all $f
set nf [open lab1.nam w]
$ns namtrace-all $nf

#creating nodes
set n0 [$ns node] 
set n1 [$ns node]
set n2 [$ns node] 
set n3 [$ns node]
set n4 [$ns node] 

#connection between nodes
$ns duplex-link $n4 $n0 1Mb 10ms RED
$ns duplex-link $n4 $n1 1Mb 10ms RED
$ns duplex-link $n4 $n2 1Mb 10ms RED
$ns duplex-link $n4 $n3 1Mb 10ms RED


#creating agent
set udp0 [new Agent/UDP]
set null0 [new Agent/Null]
$ns attach-agent $n0 $udp0
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0

set udp1 [new Agent/UDP]
set null1 [new Agent/Null]
$ns attach-agent $n1 $udp1
$ns attach-agent $n2 $null1
$ns connect $udp1 $null1

#creating traffic
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp0

#boilerplate
proc finish {} {
	global ns f nf 
	$ns flush-trace 
	close $f
	close $nf
	exit
}
$ns at 0.5 " $cbr0 start "
$ns at 10.0 " $cbr0 stop "
$ns at 0.5 " $cbr1 start "
$ns at 10.0 " $cbr1 stop "
$ns at 10.0 " finish "
$ns run
