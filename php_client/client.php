<?php 
public function post_msg($msg){
		error_reporting(E_ALL);
		set_time_limit(0);

		$ser_addr = '211.149.189.154';
		$cli_addr='192.168.0.105';
		$ser_port = 65535;
		$cli_port= 65533;

		if( ($ser_sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP)) === false) {
			echo "ser_socket_create() failed :reason:" . socket_strerror(socket_last_error()) . "\n";
		}

		if( ($cli_sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP)) === false) {
			echo "cli_socket_create() failed :reason:" . socket_strerror(socket_last_error()) . "\n";
		}

		$len=1024;
		$re=socket_sendto($cli_sock, $msg, $len, 0, $ser_addr, $ser_port);
		socket_close($cli_sock);

?>