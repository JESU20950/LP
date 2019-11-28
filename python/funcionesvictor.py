#!/usr/bin/python3
from staticmap import StaticMap, CircleMarker, Line
import pandas as pd
import networkx as nx
import math




grafo = None
matrizBloques = [[[] for i in range(60)] for j in range(22)] #60*22 bloques

def crearGrafo():
    global grafo
    grafo = nx.Graph()

def calcularXY(lat, lon):
    """La longitud va de -180 a 180 dividido en 60 zonas, dando 6 grados por zona
        La latitud va de -90 (S) a 90(N) dividido en 21 zonas de 8 grados y una de 12 (la que esta mas al norte)
        Cada grado de latitud puede variar de 110.567km a"""
    x = int((lon + 180)/6)
    y = int((lat - 90)/8)*-1
    #Como ya incluimos -180 en la parte superior de la matriz, no es necesario incluir el +180 (tampoco deberia ser posible)    
    if lon == 180:
        x = 59
    #Como la última division es mas grande, 
    if y > 21:
        y = 21
    listaXY = []
    listaXY.append(x)
    listaXY.append(y)
    return listaXY	

def listaCercanos(d, lat, lon):
    lista = []
    #seria las medidas del bloque de lat y lon
    lonKm = kmDegreeLon(lat) * 6
    latKm = kmDegreeLat() * 8
    #Ahora calculamos cuandos bloques tenemos que leer N, S, E, O y el bloque de lat y lon
    bloquesNS = math.ceil(d/latKm)
    bloquesEO = math.ceil(d/lonKm)
    yIni = 0
    xIni = 0
    if bloquesEO > 30:
        bloquesEO = 30
    if bloquesNS > 11:
        bloquesNS = 11
    listaXY = calcularXY(lat, lon)
    if listaXY[1] - bloquesNS < 0:
        yIni = 22 + listaXY[1] - bloquesNS
    else:
        yIni = listaXY[1] - bloquesNS
    if listaXY[0] - bloquesEO < 0:
        xIni = 60 + listaXY[0] - bloquesEO
    else:
        xIni = listaXY[0] - bloquesEO
    for y in range(0,bloquesNS*2+1):
        yFinal = yIni + y
        if yFinal > 21:
            yFinal = yFinal-22
        for x in range(0,bloquesEO*2+1):
            xFinal = xIni + x
            if xFinal > 59:
                xFinal = xFinal - 60
            aux = [xFinal,yFinal]
            lista.append(aux)
    return lista

def kmDegreeLon(lat):
    """Determina la distancia por grado de latitud dependiendo de la longitud en la que se encuentre
        Grado de longitud en el ecuador = 111.321"""
    return math.cos(lat*math.pi / 180) * 111.321

def kmDegreeLat():
    """Distancia de latitud por grado"""
    return 110.574

def calcularDistKm(lat1, lon1, lat2, lon2):
    #radio tierra en Km   
    radi = 6371
    dLat = (lat2-lat1)*math.pi/180
    dLon = (lon2-lon1)*math.pi/180
    a = math.sin(dLat/2) * math.sin(dLat/2) + math.cos(lat1*math.pi/180) * math.cos(lat2*math.pi/180) * math.sin(dLon/2) * math.sin(dLon/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    #Distancia en Km    
    return radi * c

def leerArchivo(distancia = 300, poblacion = 100000):
    """Crea el grafo y lo inicializa. Con poblacion = 30000 y distancia = 300 -> T. exe. = 17 sec. aprox.""" 
    url = 'https://github.com/jordi-petit/lp-graphbot-2019/blob/master/dades/worldcitiespop.csv.gz?raw=true'
    city = 'City' 
    lon = 'Longitude'
    lat = 'Latitude'
    popu = 'Population'
    df = pd.read_csv(url, compression='gzip', usecols=[city, popu, lon, lat])
    #dpPop = df.dropna(subset=[popu])
    dpPop = df[df[popu] >= poblacion]
    crearGrafo()
    global grafo
    i=0
    for row in dpPop.itertuples():
        zonaXY = calcularXY(row.Latitude, row.Longitude)
        global matrizBloques
        grafo.add_node(i, latitude=row.Latitude, longitude = row.Longitude, population = row.Population, city = row.City)
        matrizBloques[zonaXY[1]][zonaXY[0]].append(i)
        i += 1
    for x in list(grafo.nodes()):
        lat1 = grafo.node[x]['latitude']
        lon1 = grafo.node[x]['longitude']
        listaBloques = listaCercanos(distancia, lat1, lon1)
        for y in listaBloques:
            for z in matrizBloques[y[1]][y[0]]:
                if x < z:
                    dist = calcularDistKm(lat1,lon1,grafo.node[z]['latitude'],grafo.node[z]['longitude'])
                    if dist < distancia:
                        grafo.add_weighted_edges_from([(x,z,dist)])
    #dibujarMapa(dpPop)
    #Ahora dividimos las zonas en sus respectivos

def dibujarPlotpop(distancia, lat, lon):    
    myMap = StaticMap(600, 600)
    tam = 3
    listaC = listaCercanos(distancia, lat, lon)
    global matrizBloques
    for x in listaC:
        for y in matrizBloques[x[1]][x[0]]:
            latAux = grafo.node[y]['latitude']
            lonAux = grafo.node[y]['longitude']
            dist = calcularDistKm(lat,lon,latAux,lonAux)
            if dist < distancia:
                marker = CircleMarker((lonAux, latAux), 'red', math.ceil(grafo.node[y]['population']/(30000*tam))+1)
                myMap.add_marker(marker)
    image = myMap.render()
    image.save('plotpop.png')

def dibujarPlotgraph(distancia, lat, lon):    
    myMap = StaticMap(600, 600)
    listaC = listaCercanos(distancia, lat, lon)
    global matrizBloques
    listaNodos = []
    for x in listaC:
        for y in matrizBloques[x[1]][x[0]]:
            latAux = grafo.node[y]['latitude']
            lonAux = grafo.node[y]['longitude']
            dist = calcularDistKm(lat,lon,latAux,lonAux)
            if dist < distancia:
                listaNodos.append(y)
                marker = CircleMarker((lonAux, latAux), 'red', 3)
                myMap.add_marker(marker)
    gAux = grafo.subgraph(listaNodos)
    for x in list(gAux.edges()):
        myMap.add_line(Line(((gAux.node[x[0]]['longitude'],gAux.node[x[0]]['latitude']),(gAux.node[x[1]]['longitude'],gAux.node[x[1]]['latitude'])),'blue',1))
    image = myMap.render()
    image.save('plotgraph.png')

def getGrafoActual():
    global grafo
    return grafo

def getCC():
    global grafo
    return list(nx.connected_components(grafo))

#print(time.strftime("%H:%M:%S"))

#print("a")
#leerArchivo()
#print("b")
#dibujarPlotpop(1000,41,2)
#print("c")

#print(time.strftime("%H:%M:%S"))
#print(grafo.number_of_nodes())
#print(grafo.number_of_edges())
#print(calcularDistKm(0,0,-90,-180))
#leerArchivo()
#for x in matrizBloques[3][31]:
    #print(x.City)
    #print(x.Latitude)
    #print(x.Longitude)
