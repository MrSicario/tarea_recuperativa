#import "@preview/minerva-report-fcfm:0.2.1" as minerva

#let titulo = "Tarea Recuperativa"
#let subtitulo = "Hashing Perfecto"
#let tema = "Informe de Implementación"

#let departamento = minerva.departamentos.dcc
#let curso = "CC4102 - Diseño y Análisis de Algoritmos"

#let fechas = ( // diccionario de fechas, si la portada no soporta
  realización: "30 de Diciembre de 2024",
  entrega: minerva.formato-fecha(datetime.today())
)
#let lugar = "Santiago, Chile"

#let autores = ("Manuel Saavedra")
#let equipo-docente = ( // diccionario con distintos valores soportados:
  Profesor: "Benjamín Bustos", // arreglo de strings
  Auxiliares: ("Máximo Flores Valenzuela", "Sergio Rojas H."), // un único miembro como string
  Ayudantes: ("Claudio Gaete M.", "Martina Mora", "Matías Rivera")
)
