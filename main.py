import os
import subprocess

# Compilar os arquivos .cpp
subprocess.run(['g++', 'main.cpp', 'entities/*.cpp', 'components/*.cpp', '-o', 'main'])

# Listar os arquivos .txt em ./input/
txt_files = [f for f in os.listdir('./input/') if f.endswith('.txt')]


# Executar o programa compilado para cada arquivo .txt
for txt_file in txt_files:
    subprocess.run(['./main', os.path.join('./input/', txt_file), "-m"])