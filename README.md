# /proc/seconds – Linux Kernel Module

Karina Hernández  
317346404
Sistemas Operativos

## 📖 Descripción

Este proyecto implementa un módulo sencillo del kernel de Linux que crea el archivo virtual:

```
/proc/seconds
```

El archivo muestra el número de segundos transcurridos desde que el módulo fue cargado en el kernel.


---

## Funcionamiento

Cuando el módulo se carga (`insmod`):

1. Se guarda el valor actual de `jiffies`.
2. Se crea la entrada `/proc/seconds`.

Cada vez que se ejecuta:

```bash
cat /proc/seconds
```

El kernel:

- Calcula la diferencia entre los `jiffies` actuales y los iniciales.
- Divide el resultado entre `HZ` (ticks por segundo).
- Devuelve los segundos transcurridos.

Cuando el módulo se descarga (`rmmod`), la entrada en `/proc` se elimina.

---

## Requisitos

Instalar dependencias:

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```

Secure Boot configurado (si está habilitado, el módulo debe estar firmado)

---

## Compilación

Desde la carpeta del proyecto:

```bash
make
```

Esto generará el archivo:

```
seconds.ko
```

---

## Uso

### Cargar el módulo

```bash
sudo insmod seconds.ko
```

### Funcionamiento

```bash
cat /proc/seconds
```

### Descargar el módulo

```bash
sudo rmmod seconds
```

### Ver mensajes del kernel

```bash
sudo journalctl -k -n 50 --no-pager | grep -i seconds
```

---

## Secure Boot

Si Secure Boot está habilitado, el módulo debe ser firmado antes de cargarse.

Para verificarlo:

```bash
mokutil --sb-state
```

Este módulo fue firmado utilizando una Machine Owner Key (MOK).

---


## Referencias

- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). *Operating System Concepts* (10th ed.). Wiley.
- Linux Kernel Documentation – `/proc` filesystem.
- Love, R. (2010). *Linux Kernel Development* (3rd ed.). Addison-Wesley.
