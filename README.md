Proyecto

1. Registrar Usuario [registrarUsuario(Red *total)]: Se leerán los datos ingresados por el usuario, su apodo el cual será el nombre de usuario, se revisa que el nombre ingresado no existe anteriormente y una contraseña, luego se ingresará al mapa de personas y ya será parte de la base de datos de la aplicación. Cabe recalcar que el usuario deberá rellenar todos los campos solicitados o no se completará el registro. (LISTO).

2. Ingreso de Usuario [ingresarApp(Red *total)]: Se le solicitará el nombre de usuario, el cual se comparará en el mapa del resto de usuarios para ver si existe o no, si no existe se pedirá crear un nuevo registro, en cambio si existe se le pedirá la contraseña, donde esta también se comprobará que sea correcta para poder acceder al menú principal, en caso contrario, el usuario volverá a la página de ingreso. (LISTO).

3. Ingresar Perfil [ingresarPerfil(Red *total)]: Se ingresa a la estructura del usuario y se imprime la información del usuario y sus gustos. (LISTO).

4. Editar Perfil [editarPerfil(Red *total)]: El usuario podrá editar cualquier campo de la información personal, tales como su nombre de usuario, nombre completo, contraseña, intención e identidad sexual. Cabe recalcar que se verifica que el nombre completo y nombre usuario no existan dentro de la base de datos, en caso contrario se pide que ingrese nuevamente nueva información, y en el caso de la edad este no se puede editar por seguridad. (LISTO).

5. Editar Gustos [EditarGustos(Red *total)]: Se ingresa a la estructura del usuario y se le pregunta qué campo de gustos desea editar y se le entregan las opciones que debe elegir para realizar el cambio. (LISTO).

6. Buscar Personas [BuscarPersonas(Red *total)]: Esta función tendrá un submenú donde el usuario ingrese si prefiere a alguien con características similares/distintas o buscar según tus 3 gustos más importantes. (LISTO).

7. Lista Favoritos [ListFav(Red *total)]: Se ingresa al mapa de las personas y luego a su lista de favoritos la cual aparecerá en pantalla. (LISTO).

8. Lista Match [ListMatch(Red *total)]: En esta función se compara la lista de favoritos de los usuarios, si 2 usuarios se tienen mutuamente en la lista se ingresará automáticamente en una nueva lista de match la cual el usuario podrá ingresar y aparecerán los perfiles de aquellas personas que también le agregaron a su lista de favoritos y tendrás la opción de enviar un mensaje, donde el usuario deberá ingresar el nombre de usuario al cual desea enviarle el mensaje, luego escribir el mensaje y seleccionar la opción de enviar. (LISTO).

9. Buzón [Mensajes()]:En esta opción se mostrará los mensajes que ha recibido el usuario y el nombre de usuario de quien le mandó el mensaje. A través de un mapa donde el key serán ambos usuarios y el value será una lista que guarde los mensajes, así si es necesario mostrar la conversación completa será mucho más fácil, además cuando el usuario busque la conversación con aquella persona será más eficiente. (NO LISTO).

10. Top 10 [Top10(Red *total)]: En esta opción se comparará el usuario con las personas en el sistema y se mostrará una tabla de 10 usuario que tienen la mejor compatibilidad, es decir con quien tiene más gustos en común. (NO LISTO).
