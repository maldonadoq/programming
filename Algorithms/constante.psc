Proceso UsarConstante
	// PSeInt no tiene palabra clave para constantes,
	// pero por convención se usan nombres en MAYÚSCULAS
	Definir NPI Como Real
	NPI <- 3.14159
	
	Definir radio Como Real
	Definir area Como Real
	radio <- 5
	area <- NPI * radio ^ 2
	Escribir "Área del círculo: ", area
FinProceso	