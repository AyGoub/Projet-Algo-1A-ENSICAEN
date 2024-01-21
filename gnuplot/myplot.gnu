set title "Comparaison entre le temps d'execution de Triviale et Inversion "
set xlabel ("Nombre de couleurs dans la table")
set ylabel ("temps en seconde")
plot "sourcedifferente.data" using 1:2 with lines title "Triviale" ,\
    "sourcedifferente.data" using 1:3 with lines title "Inversion"