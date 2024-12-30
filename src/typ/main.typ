#import "@preview/minerva-report-fcfm:0.2.1" as minerva
#import "meta.typ" as meta

#show: minerva.report.with(
  meta,
  showrules: true,
)

//#minerva.abstract[
//]

#outline()

= Introducción

= Desarrollo

= Resultados

= Análisis

= Conclusión

= Anexo

/*
= Escribiendo simples párrafos
Typst toma bastante de Markdown y secuencias de caracteres especiales puedes dar
estilo al texto, por ejemplo, puedes usar negrita *abc*, itálica _oooo_ y
mono-espaciado `typst watch main.typ`.

Un párrafo nuevo se hace simplemente con 2 saltos de línea.

== El símbolo igual `=` se usa para crear un heading
En LaTeX se usa `\` para utilizar comandos, en Typst usamos `#`, hay muchas
utilidades como emoji #emoji.face.happy

= Elementos
== Ecuaciones
Las ecuaciones dentro de línea se hacen con símbolos peso `$`, así:
$sqrt(epsilon/phi + c/d)$

Y en su propia línea con `$ x $`, los espacios son importantes:
$ sqrt(epsilon/phi + c/d) $

== Figuras y referencias
Una figura se introduce con `figure`:
#figure(
  caption: "Una tabla dentro de una figura.",
  table(columns: 2)[nombre][tiempo][Viajar a la U][30 minutos]
) <mi-tabla>

A la tabla le agregamos `<mi-tabla>` para poder referenciar la tabla con @mi-tabla

= Necesitas más ayuda?
La documentación de typst es muy buena explicando los conceptos claves para usarlo.
- Puedes partir leyendo el tutorial: https://typst.app/docs/tutorial/
- Si tienes experiencia en LaTeX, entonces la guía para usuarios de LaTeX es un buen punto de partida: https://typst.app/docs/guides/guide-for-latex-users/
- Para consultas específicas, está el servidor de Discord de Typst: https://discord.gg/2uDybryKPe

= Show rule
El template incluye algunas show rules opcionales, más documentación en el #link("https://github.com/Dav1com/minerva-report-fcfm/blob/v0.2.0/README.md")[README.md] o en #link("https://typst.app/universe/package/minerva-report-fcfm/0.2.0")[Typst Universe].

== Números con coma decimal
#[
  #show: minerva.formato-numeros-es

  Aquí una ecuación con decimales:
  $ pi = 3.14 $
]
*/