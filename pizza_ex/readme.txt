

RAMON ROMERO A01700318


-------------------------------------------------


¿De cuál problema de sincronización se trata?
De los menos clasicos problemas de sincronizacion, "Dining Savages solution".


-------------------------------------------------


Define la estrategia y mecanismos que emplearás la solución
del problema. Fundamenta, de manera clara y concisa, cada
una de tus decisiones.

Usaria 3 semaforos:

mutex, para validar que la exclusion mutua, es decir que solo uno pueda afectar la localidad de memoria compartida a la vez, en este caso la cantidad de rebanadas de la pizza.

NOPIZZA, para notificar realizar la sincronizacion en cuanto se acabe la pizza = rebanadas = 0
PIZZA, para notificar que hay pizza

y una localidad de memoria compartida que actualmente para validar la cantidad de pizza restante



-------------------------------------------------


EXPLICACION

ejecutar en el siguiente orden y con los siguientes parametros:



pizzas.c

inicializa mi semaforos, no recibe ningun parametro



pizzero.c slices

rebibe como parametro la cantidad de rebanadas en las cuales divide la pizza que lleva, cuando los estudiantes se acaban la pizza



estudiantes.c n_studenta

recibe la cantidad de estudiantes que comen la pizza 


