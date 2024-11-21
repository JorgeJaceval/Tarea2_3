import random
import string
import os

# Función para escribir los datos generados en un archivo
def write_data(dataset_num, S1, S2):
    filename = f"Test/dataset_{dataset_num}.txt"
    with open(filename, "a") as f:
        f.write(f"{S1},{S2}\n")

# i escoje cuál dataset se ejecutará
def Dataset(size):
    # Dataset 1: S1 vacío y S2 de largo variable
    os.remove(f"Test/dataset_1.txt")
    print("Generando Dataset 1")
    for _ in range(10):  # Generar 10 casos
        length = size # Tamaño variable de S2 entre 5 y 20
        S1 = ""
        S2 = ''.join(random.choices(string.ascii_lowercase, k=length))
        write_data(1, S1, S2)

    # Dataset 2: S2 vacío y S1 de largo variable
    os.remove(f"Test/dataset_2.txt")
    print("Generando Dataset 2")
    for _ in range(10):  # Generar 10 casos
        length = size  # Tamaño variable de S1 entre 5 y 20
        S1 = ''.join(random.choices(string.ascii_lowercase, k=length))
        S2 = ""
        write_data(2, S1, S2)
    
    # Dataset 3: S1 y S2 con caracteres repetidos, mismo tamaño
    os.remove(f"Test/dataset_3.txt")
    print("Generando Dataset 3")
    for _ in range(10):  # Generar 10 casos
        length = size  # Tamaño fijo entre 5 y 20
        char1 = random.choice(string.ascii_lowercase)
        char2 = random.choice(string.ascii_lowercase)
        S1 = char1 * length
        S2 = char2 * length
        write_data(3, S1, S2)

    # Dataset 4: S1 es una transposición por pares de S2
    os.remove(f"Test/dataset_4.txt")
    print("Generando Dataset 4")
    for _ in range(10):  # Generar 10 casos
        length = size
        S2 = ''.join(random.choices(string.ascii_lowercase, k=length))
        S1 = ''.join(S2[i+1] + S2[i] for i in range(0, length, 2))  # Transposición por pares
        write_data(4, S1, S2)

    # Dataset 5: Aleatorios mismo tamaño
    os.remove(f"Test/dataset_5.txt")
    
    print("Generando Dataset 5")

    # Longitud fija para las cadenas
    longitud_fija = size

    for _ in range(10):  # Generar 10 casos
        # Generar una cadena S1 de longitud fija con caracteres aleatorios
        S1 = ''.join(random.choices(string.ascii_lowercase, k=longitud_fija))
        
        # Generar una cadena S2 con un patrón similar pero con algunas modificaciones aleatorias
        S2 = ''.join(random.choices(string.ascii_lowercase, k=longitud_fija))
        
        # Escribir las cadenas en el archivo
        write_data(5, S1, S2)

Dataset(12) 

#Probar con 2, 4, 6, 8, 10, 12 (Caracteres en string)