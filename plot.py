import pandas as pd
import matplotlib.pyplot as plt

# Carregando os dados
data = pd.read_csv('results.csv', header=None)
data.columns = ['Fitness']

# Média, desvio padrão e mediana
mean = data['Fitness'].mean()
std = data['Fitness'].std()
median = data['Fitness'].median()

print(f'Mean: {mean}')
print(f'Standard Deviation: {std}')
print(f'Median: {median}')

# Minímo e Máximo
min_fitness = data['Fitness'].min()
max_fitness = data['Fitness'].max()

print(f'Min: {min_fitness}')
print(f'Max: {max_fitness}')

# Criando uma figura com dois subplots (1 linha, 2 colunas)
fig, axs = plt.subplots(1, 2, figsize=(12, 6))

# Histograma de Frequências
axs[0].hist(data['Fitness'], bins=10, alpha=0.5)
axs[0].set_title('Histogram')

# Box Plot
axs[1].boxplot(data['Fitness'])
axs[1].set_title('Boxplot')

# Mostrando os gráficos
plt.tight_layout()  # para garantir um bom espaçamento entre os plots
plt.show()
