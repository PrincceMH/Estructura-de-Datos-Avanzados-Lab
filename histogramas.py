import matplotlib.pyplot as plt

# Función para leer el histograma desde un archivo de texto plano (TXT)
def read_distance_histogram(dimension):
    distances = []
    frequencies = []

    filename = f'distance_histogram_d{dimension}.txt'

    with open(filename, 'r') as txtfile:
        lines = txtfile.readlines()
        for line in lines:
            if line.strip():  # Ignorar líneas en blanco
                parts = line.strip().split()
                distance = int(parts[1].replace(',', ''))  # Eliminar la coma antes de convertir a entero
                frequency = int(parts[-1])
                distances.append(distance)
                frequencies.append(frequency)

    return distances, frequencies

# Función para graficar el histograma con mejor resolución
def plot_histogram(distances, frequencies, dimension):
    plt.figure(figsize=(10, 6))  # Ajustar el tamaño de la figura
    plt.bar(distances, frequencies, width=1.0, color='skyblue')  # Colores y estilo
    plt.title(f'Distance Histogram for Dimension {dimension}', fontsize=14)
    plt.xlabel('DISTANCIA', fontsize=12)
    plt.ylabel('FRECUENCIA', fontsize=12)
    plt.xticks(fontsize=10)  # Tamaño de las etiquetas en el eje x
    plt.yticks(fontsize=10)  # Tamaño de las etiquetas en el eje y
    plt.grid(axis='y', linestyle='--', alpha=0.7)  # Líneas de cuadrícula
    plt.savefig(f'distance_histogram_d{dimension}.png', dpi=300, bbox_inches='tight')  # Guardar la imagen en alta resolución
    plt.show()

if __name__ == "__main__":
    dimensions = [10, 50, 100, 500, 1000, 2000, 5000]

    for dimension in dimensions:
        distances, frequencies = read_distance_histogram(dimension)
        plot_histogram(distances, frequencies, dimension)
