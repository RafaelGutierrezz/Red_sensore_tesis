<?php
	Class dbObj{
		/* Database connection start */
		var $dbhost = "db4free.net";
		var $username = "administrador1";
		var $password = "ANGIE23ENERO";
		var $dbname = "redc02";
		var $conn;
		function getConnstring() {
			$con = mysqli_connect($this->dbhost, $this->username, $this->password, $this->dbname) or die("Connection failed: " . mysqli_connect_error());

			/* check connection */
			if (mysqli_connect_errno()) {
				printf("Connect failed: %s\n", mysqli_connect_error());
				exit();
			} else {
				$this->conn = $con;
			}
			return $this->conn;
		}
	}
?>
