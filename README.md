# grafo
Programa de busqueda ciega y euristica

# Comandos para iniciar

Creas una nueva carpeta y dentro de ella inicias git
>> git init

Ahora obtenemos toda la informacion del repositorio
>> git pull link_repo

Para crear tu rama
>> git branch mi_rama

Para ir a tu rama
>> git checkout mi_rama

Otra opcion es crear tu rama y a la vez pasarte a ella
>> git checkout -b mi_rama

Si hemos hecho cambios y queremos subirlo a nuestra rama
>> git status //es para ver en que rama estas y 
>> git add .
>> git commit -m "Agrege un cambio"
>> git push link_repo mi_rama

Para evitar conflictos siempre actualiza con un pull
>> git pull link_repo

Los pull-request hazlos directo en github

Si existen conflictos en el pull-request al hacer merge(osea unir tu rama a master)
>> git pull link_repo
>> git status
luego te avisara en que archivos existe conflicto y tendras que resolverlos manualmente, en el archivo encontraras cosas como estas
HEAD 
======== 
borralas y guarda los cambios
>> git add .
>> git commit -m "Agrege un cambio"
>> git push link_repo mi_rama
..despues ya te dejara hacer merge en github

Para ver todos los commits
>> git log

Tambien puedes hacer pull de tu rama, para tener tus cambios
>> git pull link_repo mi_rama
