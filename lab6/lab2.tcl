#boiler plate
set ns [new Simulator] 

set f [open out.tr w]
$ns trace-all $f
set nf [open out.nam w]
$ns namtrace-all $nf

#creating nodes
for {set i 0} {$i < 4} {incr i} {
	set n$i [$ns node]
}

$ns color 0 Green
$ns color 1 Blue

#connection between nodes

$ns duplex-link $n0 $n1 1Mb 10ms RED 
$ns duplex-link $n1 $n2 1Mb 10ms RED 
$ns duplex-link $n2 $n3 1Mb 10ms RED 
$ns duplex-link $n3 $n0 1Mb 10ms RED 

$ns duplex-link-op $n0 $n1 orient left
$ns duplex-link-op $n1 $n2 orient up 
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n0 orient down


#creating agent
set tcp0 [new Agent/TCP]
set sink0 [new Agent/TCPSink]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $sink0
$ns connect $tcp0 $sink0

set tcp1 [new Agent/TCP]
set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $tcp1
$ns attach-agent $n3 $sink1
$ns connect $tcp1 $sink1

#creating traffic
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

$tcp0 set fid_ 0
$tcp1 set fid_ 1

#boilerplate
proc finish {} {
	global ns f nf 
	$ns flush-trace 
	close $f
	close $nf
	exit
}
#rt model
$ns rtmodel-at 2.0 down $n0 $n1
$ns rtmodel-at 3.0 up $n0 $n1

$ns at 0.5 " $ftp0 start "
$ns at 10.0 " $ftp0 stop "
$ns at 0.5 " $ftp1 start "
$ns at 10.0 " $ftp1 stop "
$ns at 10.0 " finish "
$ns run
