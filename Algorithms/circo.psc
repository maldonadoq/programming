Proceso EntradaCirco
    Definir edad Como Entero
    Definir precio, total Como Real
    
    Escribir "Ingrese el precio de la entrada:"
    Leer precio
    
    Escribir "Ingrese la edad:"
    Leer edad
    
    total <- precio
    
    Si edad < 10 Entonces
        total <- precio - (precio * 0.25)
    FinSi
    
    Escribir "Total a pagar: ", total
FinProceso