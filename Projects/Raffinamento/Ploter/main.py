import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import pandas as pd
import numpy as np



class Cell0Ds:
    def __init__(self, id, marker, x, y):
        self.id = int(id)
        self.marker = int(marker)
        self.x = x
        self.y = y


class Cell1Ds:
    def __init__(self, id, marker, origin, end):
        self.id = int(id)
        self.marker = int(marker)
        self.origin = int(origin)
        self.end = int(end)


class Cell2Ds:
    def __init__(self, id, marker, vertices, edges):
        self.id = int(id)
        self.marker = int(marker)
        self.vertices = np.array(vertices, dtype=int)
        self.edges = np.array(edges, dtype=int)


def importCell0Ds(file_path):
    try:
        df = pd.read_csv(file_path, sep=' ')      # Importa il file CSV specificato nel percorso file_path, separando le colonne per spazio
        Cella = []                                # Inizializza una lista vuota chiamata "Cella" per memorizzare gli oggetti Cell0Ds
        for index, row in df.iterrows():          # Itera su ogni riga del dataframe df
            id = row['Id']                        # Leggi il valore della colonna 'Id' nella riga corrente
            marker = row['Marker']                # Leggi il valore della colonna 'Marker' nella riga corrente
            x = row['X']                          # Leggi il valore della colonna 'X' nella riga corrente
            y = row['Y']                          # Leggi il valore della colonna 'Y' nella riga corrente
            dati = Cell0Ds(id, marker, x, y)      # Crea un oggetto Cell0Ds con i valori letti dalla riga corrente
            Cella.append(dati)                    # Aggiungi l'oggetto Cell0Ds alla lista "Cella"
        return Cella                              # Restituisci la lista "Cella" contenente tutti gli oggetti Cell0Ds
    except FileNotFoundError:                     # Se viene sollevata un'eccezione di tipo FileNotFoundError
        print("File non trovato.")
        return None                               # Restituisci None per segnalare un fallimento nell'importazione dei dati
    except Exception as e:                        # Se viene sollevata un'eccezione generica
        print(f"Si è verificato un errore durante l'importazione dei dati: {e}")
        return None                               # Restituisci None per segnalare un fallimento nell'importazione dei dati


def importCell1Ds(file_path):
    try:
        df = pd.read_csv(file_path, sep=' ')      # Importa il file CSV specificato nel percorso file_path, separando le colonne per spazio
        Cella = []                                # Inizializza una lista vuota chiamata "Cella" per memorizzare gli oggetti Cell1Ds
        for index, row in df.iterrows():          # Itera su ogni riga del dataframe df
            id = row['Id']                        # Leggi il valore della colonna 'Id' nella riga corrente
            marker = row['Marker']                # Leggi il valore della colonna 'Marker' nella riga corrente
            origin = row['Origin']                # Leggi il valore della colonna 'Origin' nella riga corrente
            end = row['End']                      # Leggi il valore della colonna 'End' nella riga corrente
            dati = Cell1Ds(id, marker, origin, end)# Crea un oggetto Cell1Ds con i valori letti dalla riga corrente
            Cella.append(dati)                    # Aggiungi l'oggetto Cell1Ds alla lista "Cella"
        return Cella                              # Restituisci la lista "Cella" contenente tutti gli oggetti Cell1Ds
    except FileNotFoundError:                     # Se viene sollevata un'eccezione di tipo FileNotFoundError
        print("File non trovato.")
        return None                               # Restituisci None per segnalare un fallimento nell'importazione dei dati
    except Exception as e:                        # Se viene sollevata un'eccezione generica
        print(f"Si è verificato un errore durante l'importazione dei dati: {e}")
        return None                               # Restituisci None per segnalare un fallimento nell'importazione dei dati


def importCell2Ds(file_path):
    try:
        dt = pd.read_csv(file_path, skiprows=1, delimiter=' ', header=None)
        df = pd.DataFrame()
        for index, row in dt.iterrows():
            if len(row) == 8:
                new_row = pd.DataFrame({
                    'id': row[0],
                    'marker': row[1],
                    'v1': row[2],
                    'v2': row[3],
                    'v3': row[4],
                    'e1': row[5],
                    'e2': row[6],
                    'e3': row[7]
                }, index=[index])
                flag=0
            elif len(row) == 7:
                new_row = pd.DataFrame({
                    'id': row[0],
                    'v1': row[1],
                    'v2': row[2],
                    'v3': row[3],
                    'e1': row[4],
                    'e2': row[5],
                    'e3': row[6]
                }, index=[index])
                flag = 1
            else:
                print("Formato file non valido")
            df = pd.concat([df, new_row])
        Cella = []
        for index, row in df.iterrows():
            id = row['id']
            if flag == 1:
                marker = 0
            else:
                marker = row['marker']
            vertices = row[['v1', 'v2', 'v3']]
            edges = row[['e1', 'e2', 'e3']]
            dati = Cell2Ds(id, marker, vertices, edges)
            Cella.append(dati)
        return Cella
    except FileNotFoundError:
        print(f"File '{file_path}' not found")
    except Exception as e:
        print(f"An error occurred: {e}")


def showCell0Ds(cells):
    print("Cell0Ds:")
    for cell in cells:                            # Itera su ogni oggetto Cell0Ds nella lista cells
        print(f"ID: {cell.id}, Marker: {cell.marker}, X: {cell.x}, Y: {cell.y}")


def showCell1Ds(cells):
    print("Cell1Ds:")
    for cell in cells:                            # Itera su ogni oggetto Cell1Ds nella lista cells
        print(f"ID: {cell.id}, Marker: {cell.marker}, Origin: {cell.origin}, End: {cell.end}")


def showCell2Ds(cells):
    print("Cell2Ds:")
    for cell in cells:                            # Itera su ogni oggetto Cell1Ds nella lista cells
        print(f"ID: {cell.id}, Marker: {cell.marker}, Vertices: {cell.vertices}, Edges: {cell.edges}")


def showCells(cell0ds, cell1ds, cell2ds):
    showCell0Ds(cell0ds)
    showCell1Ds(cell1ds)
    showCell2Ds(cell2ds)

def plotCell0Ds(cell0ds, cell1ds):
    x_values = [cell.x for cell in cell0ds]       # Crea una lista di valori X prendendo il valore X da ogni oggetto Cell0Ds nella lista cells
    y_values = [cell.y for cell in cell0ds]       # Crea una lista di valori Y prendendo il valore Y da ogni oggetto Cell0Ds nella lista cells
    colors = [cell.marker for cell in cell0ds]    # Crea una lista di colori prendendo il valore del marker da ogni oggetto Cell0Ds nella lista cells
    ids = [cell.id for cell in cell0ds]           # Crea una lista d'ID prendendo l'ID da ogni oggetto Cell0Ds nella lista cells

    # Mappa di colori per associare ciascun valore del marker a un colore specifico
    color_map = {5: 'red', 6: 'green', 7: 'orange', 8: 'yellow', 0: 'blue', 1: 'purple', 2: 'pink', 3: 'gray', 4: 'aquamarine'}

    # Crea una lista di elementi legenda per ogni colore/marker presente nella mappa dei colori
    legend_elements = [
        plt.Line2D([0], [0], marker='o', color='w', label=str(marker), markerfacecolor=color_map[marker], markersize=10)
        for marker in color_map
    ]

    # Ottieni il colore corrispondente al valore del marker della Cell0Ds corrente
    marker_colors = [color_map.get(marker, 'black') for marker in colors]
    # Disegna un grafico a dispersione dei punti con colori basati sui marker
    plt.scatter(x_values, y_values, c=marker_colors, marker='s', s=10)

    for cell in cell1ds:
        origin_id = cell.origin
        end_id = cell.end

        origin = None
        for cell0d in cell0ds:
            if cell0d.id == origin_id:
                origin = cell0d
                break

        end = None
        for cell0d in cell0ds:
            if cell0d.id == end_id:
                end = cell0d
                break

        plt.plot([origin.x, end.x], [origin.y, end.y], color='lightgray', linewidth=1)

    # Etichette degli assi e titolo del grafico
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Cell0Ds Plot')

    # Aggiungi la legenda con i marker colorati
    plt.legend(handles=legend_elements, title='Marker', bbox_to_anchor=(1.05, 1), loc='upper left')

    plt.axis('equal')                             # Imposta gli assi in modo che abbiano la stessa scala


def plotCell1Ds(cell0ds, cell1ds):
    x_values = [cell.x for cell in cell0ds]       # Crea una lista di valori X prendendo il valore X da ogni oggetto Cell0Ds nella lista cell0ds
    y_values = [cell.y for cell in cell0ds]       # Crea una lista di valori Y prendendo il valore Y da ogni oggetto Cell0Ds nella lista cell0ds

    # Mappa di colori per associare ciascun valore del marker a un colore specifico
    color_map = {5: 'red', 6: 'green', 7: 'orange', 8: 'yellow', 0: 'blue'}

    # Crea una lista di elementi legenda per ogni colore/marker presente nella mappa dei colori
    legend_elements = [
        plt.Line2D([0], [0], marker='o', color='w', label=str(marker),
                   markerfacecolor=color_map[marker], markersize=10)
        for marker in color_map
    ]

    for cell in cell1ds:                          # Itera su ogni oggetto Cell1Ds nella lista cell1ds
        # Ottieni l'ID di origin e di end dalla Cell1Ds corrente che sono in realtà le id dei punti di Cell0D
        origin_id = cell.origin
        end_id = cell.end

        # Trova l'oggetto Cell0Ds corrispondente all'ID di origin
        origin = None
        for cell0d in cell0ds:
            if cell0d.id == origin_id:
                origin = cell0d
                break

        # Trova l'oggetto Cell0Ds corrispondente all'ID di end
        end = None
        for cell0d in cell0ds:
            if cell0d.id == end_id:
                end = cell0d
                break

        if origin is not None and end is not None:# Se sono stati trovati sia l'origine che l'estremità
            # Ottieni il colore corrispondente al valore del marker della Cell1Ds corrente
            marker_color = color_map.get(cell.marker, 'black')
            # Disegna una linea che collega i punti di origin e di end utilizzando il colore del marker
            plt.plot([origin.x, end.x], [origin.y, end.y], color=marker_color, linewidth=1)

    # Etichette degli assi e titolo del grafico
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Cell1Ds Plot')

    # Aggiungi la legenda con i marker colorati
    plt.legend(handles=legend_elements, title='Marker', bbox_to_anchor=(1.05, 1), loc='upper left')

    plt.axis('equal')                             # Imposta gli assi in modo che abbiano la stessa scala


def plotCell2Ds(cell0ds, cell1ds, cell2ds):
    x_values = [cell.x for cell in cell0ds]
    y_values = [cell.y for cell in cell0ds]

    max_marker = max(cell2ds, key=lambda cell: cell.marker).marker
    gradient_values = np.linspace(0, 1, max_marker + 1)

    cmap = mcolors.LinearSegmentedColormap.from_list('my_cmap', ['white', 'darkgray'], N=max_marker+1)

    color_map = {marker: cmap(gradient_values[marker]) for marker in range(max_marker + 1)}
    legend_elements = [
        plt.Line2D([0], [0], marker='o', color='w', label=str(marker),
                   markerfacecolor=color_map[marker], markersize=10)
        for marker in color_map
    ]

    for cell in cell1ds:
        origin_id = cell.origin
        end_id = cell.end

        origin = None
        for cell0d in cell0ds:
            if cell0d.id == origin_id:
                origin = cell0d
                break

        end = None
        for cell0d in cell0ds:
            if cell0d.id == end_id:
                end = cell0d
                break

        plt.plot([origin.x, end.x], [origin.y, end.y], color='black', linewidth=1)

    for cell in cell2ds:
        vertices_ids = cell.vertices
        marker = cell.marker

        vertices = []
        for vertex_id in vertices_ids:
            for cell0d in cell0ds:
                if cell0d.id == vertex_id:
                    vertices.append(cell0d)
                    break

        x_coords = [vertex.x for vertex in vertices]
        y_coords = [vertex.y for vertex in vertices]

        plt.fill(x_coords, y_coords, color=color_map[marker], alpha=0.5)

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Cell2Ds Plot')
    plt.legend(handles=legend_elements, title='Marker', bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.axis('equal')


def plot(cell0ds, cell1ds, cell2ds):
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 3, 1)
    plotCell0Ds(cell0ds, cell1ds)

    plt.subplot(1, 3, 2)
    plotCell1Ds(cell0ds, cell1ds)

    plt.subplot(1, 3, 3)
    plotCell2Ds(cell0ds, cell1ds, cell2ds)

    plt.tight_layout()
    plt.show()



def Vplot(cell0ds_in, cell1ds_in, cell2ds_in, cell0ds_out, cell1ds_out, cell2ds_out):
    plt.figure(figsize=(12, 8))

    plt.subplot(2, 3, 1)
    plotCell0Ds(cell0ds_in, cell1ds_in)

    plt.subplot(2, 3, 2)
    plotCell1Ds(cell0ds_in, cell1ds_in)

    plt.subplot(2, 3, 3)
    plotCell2Ds(cell0ds_in, cell1ds_in, cell2ds_in)

    plt.subplot(2, 3, 4)
    plotCell0Ds(cell0ds_out, cell1ds_out)

    plt.subplot(2, 3, 5)
    plotCell1Ds(cell0ds_out, cell1ds_out)

    plt.subplot(2, 3, 6)
    plotCell2Ds(cell0ds_out, cell1ds_out, cell2ds_out)

    plt.tight_layout()
    plt.show()




file_IN_path0 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Test1\\Cell0Ds.csv"
file_IN_path1 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Test1\\Cell1Ds.csv"
file_IN_path2 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Test1\\Cell2Ds.csv"
Cella0_IN = importCell0Ds(file_IN_path0)
Cella1_IN = importCell1Ds(file_IN_path1)
Cella2_IN = importCell2Ds(file_IN_path2)

file_OUT_path0 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell0Ds.csv"
file_OUT_path1 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell1Ds.csv"
file_OUT_path2 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Output\\Cell2Ds.csv"
Cella0_OUT = importCell0Ds(file_OUT_path0)
Cella1_OUT = importCell1Ds(file_OUT_path1)
Cella2_OUT = importCell2Ds(file_OUT_path2)

#showCells(Cella0, Cella1, Cella2)

Vplot(Cella0_IN, Cella1_IN, Cella2_IN, Cella0_OUT, Cella1_OUT, Cella2_OUT)
#plot(Cella0_IN, Cella1_IN, Cella2_IN)
#plot(Cella0_OUT, Cella1_OUT, Cella2_OUT)