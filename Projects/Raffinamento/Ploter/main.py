import matplotlib.pyplot as plt
import pandas as pd



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
        self.origin = origin
        self.end = end


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


def showCell0Ds(cells):
    print("Cell0Ds:")
    for cell in cells:                            # Itera su ogni oggetto Cell0Ds nella lista cells
        print(f"ID: {cell.id}, Marker: {cell.marker}, X: {cell.x}, Y: {cell.y}")


def showCell1Ds(cells):
    print("Cell1Ds:")
    for cell in cells:                            # Itera su ogni oggetto Cell1Ds nella lista cells
        print(f"ID: {cell.id}, Marker: {cell.marker}, Origin: {cell.origin}, End: {cell.end}")


def plotCell0Ds(cell0ds):
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
    plt.scatter(x_values, y_values, c=marker_colors)

    # Assegna ai punti del grafico il valore d'id associato
    for i, id in enumerate(ids):                  # Annota ogni punto con il relativo ID
        plt.annotate(str(id), (x_values[i], y_values[i]), textcoords="offset points", xytext=(0,10), ha='center')

    # Etichette degli assi e titolo del grafico
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Cell0Ds Plot')

    # Aggiungi la legenda con i marker colorati
    plt.legend(handles=legend_elements, title='Marker', bbox_to_anchor=(1.05, 1), loc='upper left')

    plt.axis('equal')                             # Imposta gli assi in modo che abbiano la stessa scala
    plt.show()                                    # Mostra il grafico


def plotCell1Ds(cell0ds, cell1ds):
    x_values = [cell.x for cell in cell0ds]       # Crea una lista di valori X prendendo il valore X da ogni oggetto Cell0Ds nella lista cell0ds
    y_values = [cell.y for cell in cell0ds]       # Crea una lista di valori Y prendendo il valore Y da ogni oggetto Cell0Ds nella lista cell0ds
    colors = [cell.marker for cell in cell0ds]    # Crea una lista di colori prendendo il valore del marker da ogni oggetto Cell0Ds nella lista cell0ds

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
    plt.show()                                    # Mostra il grafico





file_path0 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Test1\\Cell0Ds.csv"
file_path1 = "D:\\PoliTo\\Matematica\\3-Anno\\Programmazione_e_calcolo_scientifico\\Progetto\\Progetto_PCS_FMV\\Projects\\Raffinamento\\Dataset\\Test1\\Cell1Ds.csv"
Cella0 = importCell0Ds(file_path0)
Cella1 = importCell1Ds(file_path1)

if Cella0 is not None:
    showCell0Ds(Cella0)
if Cella1 is not None:
    showCell1Ds(Cella1)

plotCell0Ds(Cella0)
plotCell1Ds(Cella0, Cella1)