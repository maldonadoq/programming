Proceso CalcularIMC
	// === DECLARACIÓN DE VARIABLES ===
	Definir peso, altura, imc Como Real
	Definir nombre Como Cadena
	
	// === ENTRADA DE DATOS ===
	Escribir "=== Calculadora de IMC ==="
	Escribir "Ingresa tu nombre: "
	Leer nombre
	Escribir "Ingresa tu peso en kg (ej: 70.5): "
	Leer peso
	Escribir "Ingresa tu altura en metros (ej: 1.75): "
	Leer altura
	
	// === PROCESAMIENTO ===
	imc <- peso / (altura ^ 2)
	// === SALIDA DE RESULTADOS === 
	Escribir "--- Resultado para: ", nombre, " ---"
	Escribir "Tu IMC es: ", imc
FinProceso