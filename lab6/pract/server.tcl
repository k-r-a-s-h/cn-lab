set ns [new Simulator]
set f [open server.tr w]
$ns trace-all $f
set nf [open server.nam w]
$ns namtrace-all $nf

for {set i 0} {$i < 12} {incr i} {
    set n($i) [$ns node]
    $n($i) color red
}
$n(1) color yellow
$n(0) color yellow
$n(7) color blue
$n(8) color blue
$n(9) color blue
$n(10) color blue
$n(11) color blue

$ns color 1 red
$ns color 2 yellow
$ns color 3 green
$ns color 4 violet

for {set k 2} {$k <7} {incr k} {
    $ns duplex-link $n(0) $n($k) 10Mb 20ms RED
}

for {set j 7} {$j <12} {incr j} {
    $ns duplex-link $n(1) $n($j) 10Mb 20ms RED
}

$ns duplex-link $n(1) $n(0) 1.5Mb 40ms RED
$ns duplex-link-op $n(0) $n(1) orient left 
$ns duplex-link-op $n(1) $n(7) orient up
$ns duplex-link-op $n(1) $n(8) orient left-up
$ns duplex-link-op $n(1) $n(9) orient left-down
$ns duplex-link-op $n(1) $n(10) orient left
$ns duplex-link-op $n(1) $n(11) orient down

$ns duplex-link-op $n(0) $n(2) orient up
$ns duplex-link-op $n(0) $n(3) orient right-up
$ns duplex-link-op $n(0) $n(4) orient right-down
$ns duplex-link-op $n(0) $n(5) orient right
$ns duplex-link-op $n(0) $n(6) orient down

set count 2
set count2  7
for {set l 0} {$l <5} {incr l} {
    set tcp($l) [new Agent/TCP]
    set tcpsink($l) [new Agent/TCPSink]
    $ns attach-agent $n($count2) $tcp($l)
    $ns attach-agent $n($count) $tcpsink($l)
    $ns connect $tcp($l) $tcpsink($l)
    set ftp($l) [new Application/FTP]
    $ftp($l) attach-agent $tcp($l)
    
    incr count
    incr count2 
}

$tcp(1) set fid_ 1
$tcp(2) set fid_ 2
$tcp(3) set fid_ 3
$tcp(4) set fid_ 4



proc finish {} {
	global ns f nf 
	$ns flush-trace 
	close $f
	close $nf
	exit
}

$ns rtmodel-at 5.0 down $n(0) $n(1)
$ns rtmodel-at 6.0 up $n(0) $n(1) 

$ns at 0.5 " $ftp(0) start "
$ns at 1 " $ftp(1) start " 
$ns at 1.5 " $ftp(2) start "
$ns at 2 " $ftp(3) start "
$ns at 2.5 " $ftp(4) start "

$ns at 6 " $ftp(0) stop "
$ns at 6.5 " $ftp(1) stop "
$ns at 7 " $ftp(2) stop "
$ns at 7.5 " $ftp(3) stop "
$ns at 9 " $ftp(4) stop "
$ns at 10 " finish "
$ns run
