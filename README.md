PROYECTO

Estructuras:

-> Red:
    - Map *totalUsuarios: Mapa que guarda a todos los usuarios con su respectiva información.
    - int Cantidad: Variable de tipo int que guarda la cantidad de usuarios que hay en la aplicación.
    - char UsuarioIngresado[100]: variable de tipo char que almacena el nombre de usuario de la persona que ingresó.

-> usuario:
    - char nombre[100]: variable de tipo char que almacena el nombre de la persona.
    - char apodo[100]: variable de tipo char que almacena el nombre de usuario, importante para el ingreso a la cuenta.
    - char contrasena[100]: variable de tipo char que almacena la contraseña del usuario, importante para el ingreso de la cuenta.
    - int edad: variable de tipo int que almacena la edad del usuario.
    - char identidadG[100]: variable de tipo char que almacena la identidad de genero de la persona.
    - char intenciones[100]: variable de tipo char que almacena las intenciones del usuario, es decir buscar amigos/as, pareja o un encuentro en la app.
    - tipoGustos *gustos: variable de tipo tipoGustos (estructura creada por nosotros) que almacena los gustos del usuario.
    - List *fav: variable de tipo Lista que almacena a las personas que al usuario le llamaron la atención.
    - List *match: variable de tipo Lista que almacena a las personas que el usuario hizo match.
    - Map *chat: variable de tipo Mapa que almacena los mensajes que tiene el usuario.
    - int compatibilidad: variable de tipo int que almacena la copatbilidad que tiene con los usuarios.

-> tipoGustos:
    - char orientacionS[100]: variable de tipo char que almacena la orientación sexual del usuario.   
    char generofav[100]: variable de tipo char que almacena el genero musical favorito del usuario.
    char colorfav[100]: variable de tipo char que almacena el color favorito del usuario.
    char PelLib[100]: variable de tipo char que almacena la preferencia entre libros o peliculas del usuario.
    char casaSalir[100]: variable de tipo char que almacena la preferencia entre quedarse en casa o salir del usuario.
    char estacionfav[100]: variable de tipo char que almacena la estación del año favorita del usuario.
    char liqfav[100]: variable de tipo char que almacena el bebestible favorito del usuario ente el té, cafe o bebida.
    char playaMontana[100]: variable de tipo char que almacena la preferencia entre la playa o la montaña del usuario.
    char depVid[100]; variable de tipo char que almacena la preferencia entre hacer deporte o jugar videojuegos del usuario.
    char PerroGato[100]; variable de tipo char que almacena la preferencia entre perros o gatos del usuario.
    char comida[100]; variable de tipo char que almacena la dieta del usuario entre vegano, vegetariano o carnivoro.

Instrucciones para correr el programa:
-> Primero debemos abrir el terminal donde debemos escribir gcc *.c -o Proyecto luego debemos poner ./Proyecto.exe para ejecutar el programa.

    - Se nos mostrará la página de inicio de la aplicación, donde podremos registrarnos, iniciar sesión o salir de la app.

1. Registrar Usuario [registrarUsuario(Red *total)]: Se leerán los datos ingresados por el usuario, su apodo el cual será el nombre de usuario, se revisa que el nombre ingresado no existe anteriormente y una contraseña, luego se ingresará al mapa de personas y ya será parte de la base de datos de la aplicación. Cabe recalcar que el usuario deberá rellenar todos los campos solicitados o no se completará el registro. (LISTO).

2. Ingreso de Usuario [ingresarApp(Red *total)]: Se le solicitará el nombre de usuario, el cual se comparará en el mapa del resto de usuarios para ver si existe o no, si no existe se pedirá crear un nuevo registro, en cambio si existe se le pedirá la contraseña, donde esta también se comprobará que sea correcta para poder acceder al menú principal, en caso contrario, el usuario volverá a la página de ingreso. (LISTO).

3. Ingresar Perfil [ingresarPerfil(Red *total)]: Se ingresa a la estructura del usuario y se imprime la información del usuario y sus gustos. (LISTO).

-> Ya iniciando sesión, aparecerá el menú principal, donde se encontrará la funciones que el usuario puede utilizar, estas son:

4. Editar Perfil [editarPerfil(Red *total)]: El usuario podrá editar cualquier campo de la información personal, tales como su nombre de usuario, nombre completo, contraseña, intención e identidad sexual. Cabe recalcar que se verifica que el nombre completo y nombre usuario no existan dentro de la base de datos, en caso contrario se pide que ingrese nuevamente nueva información, y en el caso de la edad este no se puede editar por seguridad. (LISTO).

5. Editar Gustos [EditarGustos(Red *total)]: Se ingresa a la estructura del usuario y se le pregunta qué campo de gustos desea editar y se le entregan las opciones que debe elegir para realizar el cambio. (LISTO).

6. Buscar Personas [BuscarPersonas(Red *total)]: Esta función tendrá un submenú donde el usuario ingrese si prefiere a alguien con características similares/distintas o buscar según tus 3 gustos más importantes. (LISTO).

7. Lista Favoritos [ListFav(Red *total)]: Se ingresa al mapa de las personas y luego a su lista de favoritos la cual aparecerá en pantalla. (LISTO).

8. Lista Match [ListMatch(Red *total)]: En esta función se compara la lista de favoritos de los usuarios, si 2 usuarios se tienen mutuamente en la lista se ingresará automáticamente en una nueva lista de match la cual el usuario podrá ingresar y aparecerán los perfiles de aquellas personas que también le agregaron a su lista de favoritos y tendrás la opción de enviar un mensaje, donde el usuario deberá ingresar el nombre de usuario al cual desea enviarle el mensaje, luego escribir el mensaje y seleccionar la opción de enviar. (LISTO).

9. Buzón [Mensajes()]:En esta opción se mostrará los mensajes que ha recibido el usuario y el nombre de usuario de quien le mandó el mensaje. A través de un mapa donde el key serán ambos usuarios y el value será una lista que guarde los mensajes, así si es necesario mostrar la conversación completa será mucho más fácil, además cuando el usuario busque la conversación con aquella persona será más eficiente. (NO LISTO).

10. Top 10 [Top10(Red *total)]: En esta opción se comparará el usuario con las personas en el sistema y se mostrará una tabla de 10 usuario que tienen la mejor compatibilidad, es decir con quien tiene más gustos en común. (PROBLEMAS).

11. Salir: El usuario sale de la aplicación.



(*) Comentarios: La función que muestra el top10 del usuario la comentamos ya que si se compila, se cae, además la función de mostrar mensajes no está creada, por lo que si se escoge esa opción, volverá al menú principal.
