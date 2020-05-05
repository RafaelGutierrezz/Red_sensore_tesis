<?php
class conexion
{
	private $servidor;
	private $usuario;
	private $contrasena;
	private $basedatos;
	public  $conexion;

	public function __construct(){
		$this->servidor   = "db4free.net";
		$this->usuario	  = "administrador1";
		$this->contrasena = "ANGIE23ENERO";
		$this->basedatos  = "redc02";

	}

	function conectar(){
		$this->conexion = new PDO("mysql:host=$this->servidor;dbname=$this->basedatos","$this->usuario","$this->contrasena");
	}

	function cerrar(){
		$this->conexion->close();
	}
}
?>
